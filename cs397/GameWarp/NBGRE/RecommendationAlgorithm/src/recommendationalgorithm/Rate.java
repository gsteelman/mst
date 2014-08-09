// BEGINNING OF FILE -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// @file Rate.java
// @desc A file containing the mechanisms for storing user ratings into the UPI
// @date 11 Dec 2010
// @auth Game Warp Algorithm Team
////////////////////////////////////////////////////////////////////////////////
package recommendationalgorithm;

import java.util.Iterator;

////////////////////////////////////////////////////////////////////////////////
// @class Rate
// @desc Update the UPI with information for a user's rating of a game
////////////////////////////////////////////////////////////////////////////////
public class Rate
{
  //////////////////////////////////////////////////////////////////////////////
  // @func public static void main( String [] args )
  // @desc Handles a user rating a game in the system
  // @pre The parameters have been verified for correctness by main.java
  // @param String accNum - The username of the user who rated the game
  // @param String gURI - The game URI for the rated game
  // @param double newRating - The rating given to the game by the user
  // @param GameDatabase gameDB - A reference to the game database
  // @return String - The results of the rating (success/failure)
  //////////////////////////////////////////////////////////////////////////////
  public String driver( String accNum, 
                        String gURI,
                        String comment,
                        double newRating,
                        GameDatabase gameDB
                      )
  {
    String results;

    // Set up the UPI information
    UPI_Interface UPI = new UPI_Interface( gameDB );
    UPI.setAccNum( accNum );
    UPI.getUserScores();

    // Set up the game information
    Game ratedGame = new Game( gURI );
    ratedGame.getGameInformation( gameDB );
    UPI.setGameURI( gURI );
    UPI.getGlobalGameScores();

    // Rate the game
    if ( rateGame( UPI, ratedGame, comment, newRating ) == false )
    {
      results = "Unable to write rating to the database (One possibly already exists).";
      results += "\n" + UPI.eMsg;
      results += "\n" + UPI.eExp.getMessage();
    }

    else
    {
      // Verify the game was rated and stored properly
      if( !verifyRateGame( UPI, ratedGame, comment, newRating ) )
      {
        results = "Verification of storage of accurate results of rated game failed.";
        results += "\n" + UPI.eMsg;
        results += "\nEXCEPTION: " + UPI.eExp.getMessage();
      }

      else
      {
        results = "Your game has been rated.";
      }
    }
    
    return results;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func protected double runningAverage()
  // @desc Calculates a new average for given information
  // @param double numRatings, the number of ratings before adding the new one
  // @param double currentScore, the score before adding the new score
  // @param double addedScore, the score to add
  // @return double, the new average
  //////////////////////////////////////////////////////////////////////////////
  protected double runningAverage( double numRatings, double currentScore, double addedScore )
  {
    double newAverage = (currentScore * numRatings / (numRatings + 1)) + (addedScore / (numRatings + 1));

    return newAverage;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private void rateGame( UPI_Interface UPI, game ratedGame, double newRating )
  // @desc The main function for the recommendation algorithm. Handles command
  //       line parameter parsing and algorithm flow
  // @pre The parameters have been verified for correctness by main.java
  // @param UPI_Interface UPI - An initilized UPI_Interface with the user's scores
  //                            already loaded properly using getUserScores()
  // @param Game ratedGame - The game that was rated by the user
  // @param String comment - The user's comment for the game
  // @param double newRating - The rating given to the game by the user
  // @return boolean - The results of the rating (success/failure)
  //////////////////////////////////////////////////////////////////////////////
  protected boolean rateGame( UPI_Interface UPI,
                              Game ratedGame,
                              String comment,
                              double newRating
                            )
  {
    // Refer to the pseudo code on the site for this, check documentation on
    // classes
    // 1 - update values in UPI's arrays.
    //     + for the following things, this means update the average scores for the user and the count, the formula is on the site
    //     - for each ratedGame's game genres update corresponding element in UPI.GameGenreScores[]
    //     - for each ratedGame's theatrical genres update corresponding element in UPI.TheatricalGenreScores[]
    //     - for each ratedGame's attribute update corresponding element in UPI.AttributeScores[]
    // 2 - update global score and rated count for game in UPI

    // See if the user has already rated this game
    String sqlQuery = "SELECT * FROM UserGameRatings WHERE AccountNumber = '" + UPI.getAccNum() + "'" +
                      " AND GameURI = '" + ratedGame.getGameURI() + "'";
    UPI.MySQLQuery( sqlQuery );
    if ( UPI.eFlag == true )
    {
      return false;
    }

    try
    {
      // Move to the last row in the result.
      // If there are no rows, last returns false, which is what we want
      boolean userHasRatedThisGameBefore = UPI.MySQLQueryResult.last();

      if( userHasRatedThisGameBefore )
      {
        // Let the program know that we didn't actually overwrite the rating
        return false;
      }
      else
      {
        // Add this rating to the database for the specific user
        if( comment.length() > 0 )
        {
          sqlQuery = "INSERT INTO UserGameRatings ( AccountNumber, GameURI, Rating, Comment ) VALUES ( '"
                + UPI.getAccNum() + "'" +
          ", '" + ratedGame.getGameURI() + "'" +
          ", '" + Double.toString( newRating ) + "'" +
          ", '" + comment + "');";
        }

        else
        {
          sqlQuery = "INSERT INTO UserGameRatings ( AccountNumber, GameURI, Rating ) VALUES ( '"
                + UPI.getAccNum() + "'" +
          ", '" + ratedGame.getGameURI() + "'" +
          ", '" + Double.toString( newRating ) + "');";
        }

        UPI.MySQLUpdate( sqlQuery );
        if ( UPI.eFlag == true )
        {
          return false;
        }

        // Acquire the previous number of ratings this game had and its overall score
        // Then update it to reflect this new rating
        UPI.getGlobalGameScores();
        UPI.globalGameScore = runningAverage((double)UPI.globalNumGameRatings,
                                             UPI.globalGameScore,
                                             newRating);
        UPI.globalNumGameRatings++;

        // Loop through all the attributes listed in this game
        for ( int j = 0; j < ratedGame.attributes.size(); j++ )
        {
          // Get the name of an attribute for the current game
          Attribute gameAttribute = ratedGame.attributes.get( j );

          // Get the user's score for that attribute and the number of games for that attribute they have rated
          double attributeScore = UPI.attributeScores.get( gameAttribute.getName() ).getScore();
          int numAttributeRatings = UPI.attributeScores.get( gameAttribute.getName() ).getNumScores();

          // Update the user's scores for attributes and number of attributes rated to reflect this game's rating
          attributeScore = runningAverage((double)numAttributeRatings,
                                          attributeScore,
                                          newRating);
          numAttributeRatings++;

          // Write updated values back to the UPI arrays
          Attribute attr = UPI.attributeScores.get( gameAttribute.getName() );
          attr.setScore( attributeScore );
          attr.setNumScores( numAttributeRatings );
          UPI.attributeScores.put( gameAttribute.getName(), attr );
        }

        // Loop through all the theatrical genres listed in this game
        for ( int j = 0; j < ratedGame.theatricalGenres.size(); j++ )
        {
          // Get the name of a theatrical genre for the current game
          Genre gameTheatrical = ratedGame.theatricalGenres.get( j );

          // Get the user's score for that theatrical genre and the number of games for that genre they have rated
          double theatricalScore = UPI.theatricalGenreScores.get( gameTheatrical.getName() ).getScore();
          int numTheatricalRatings = UPI.theatricalGenreScores.get( gameTheatrical.getName() ).getNumScores();

          // Update the user's scores for theatrical genres and number of theatrical genres rated to reflect this game's rating
          theatricalScore = runningAverage((double)numTheatricalRatings,
                                           theatricalScore,
                                           newRating);
          numTheatricalRatings++;

          // Rewrite these new values back to the UPI arrays
          Genre tgenre = UPI.theatricalGenreScores.get( gameTheatrical.getName() );
          tgenre.setNumScores( numTheatricalRatings );
          tgenre.setScore( theatricalScore );
          UPI.theatricalGenreScores.put( gameTheatrical.getName(), tgenre );
        }

        // Loop through all the game genres listed in this game
        for ( int j = 0; j < ratedGame.gameGenres.size(); j++ )
        {
          // Get the name of a genre for the current game
          Genre gameGenre = ratedGame.gameGenres.get( j );

          // An iterator across all genres
          Iterator<Genre> genreIterator = UPI.gameGenreScores.iterator();
          boolean foundUsersGenreScore = false;

          // Loop through the UPI.GameGenreScores to get the user's score for that
          // genre and the number of games for that genre they have rated
          while ( !foundUsersGenreScore && genreIterator.hasNext() )
          {
            // Look at the next possible genre to update a score for from all
            // the genres in the database
            Genre potentialGenre = genreIterator.next();

            // Check if the genre from the full list in the database matches
            // the genre this game has
            if( potentialGenre.getName().equals( gameGenre.getName() ) )
            {
              foundUsersGenreScore   = true;
              double genreScore      = potentialGenre.getScore();
              int   numGenreRatings  = potentialGenre.getNumScores();

              // Update the user's scores for genres and number of genres rated to reflect this game's rating
              genreScore = runningAverage((double)numGenreRatings,
                                          genreScore,
                                          newRating);
              numGenreRatings++;

              // Write these new values back to the UPI arrays
              UPI.gameGenreScores.remove( potentialGenre );
              potentialGenre.setScore( genreScore );
              potentialGenre.setNumScores( numGenreRatings );
              UPI.gameGenreScores.add( potentialGenre );
            }
          }
        }

        // Write UPI's user-specific arrays back to the database
        System.out.println("Before writeUserScores()\n");

        UPI.writeUserScores();
        System.out.println("After writeUserScores()\n");

        // Write UPI's game-specific arrays back to the database
        UPI.writeGlobalGameScores();
      }
    }

    catch ( Exception e )
    {
      return false;
    }

    return true;
  }


  //////////////////////////////////////////////////////////////////////////////
  // @func private boolean verifyRateGame( UPI_Interface UPI, game ratedGame, double newRating )
  // @desc Verified whether or not the user's new game rating was correctly added to the database
  // @pre  the rateGame function has been called already
  // @param UPI_Interface UPI - the UPI interface object for a specific user
  //        Game ratedGame - the game that the user has just rated
  //        String comment - the user's comment on the game
  //        double newRating - the rating that the user gave to the game
  // @ret true - if the new game rating exists in the database
  // @ret false - if the new game rating doesn't exist in the database
  //////////////////////////////////////////////////////////////////////////////
  protected boolean verifyRateGame( UPI_Interface UPI,
                                    Game ratedGame,
                                    String comment,
                                    double newRating
                                  )
  {
    // Query the database and make sure that the score got recorded properly
    String sqlQuery = "SELECT * FROM UserGameRatings WHERE AccountNumber = '" + UPI.getAccNum() + "'" +
    " AND GameURI = '" + ratedGame.getGameURI() + "'";
    UPI.MySQLQuery( sqlQuery );
    if ( UPI.eFlag == true )
    {
      return false;
    }

    try
    {
      // There should be only one row returned from this query, so lets look at it
      boolean tupleExists = UPI.MySQLQueryResult.last();

      if( !tupleExists )
      {
        // No tuple exists and thus the rating wasn't recorded
        return false;
      }

      else
      {
        // Check to see if the rating value is correct
        int ratingValue = UPI.MySQLQueryResult.getInt( "Rating" );
        if( ratingValue != newRating )
        {
          return false;
        }

        // Check to see if the comment is correct (only matters if a comment exists)
        if( comment.length() > 0 )
        {
          String commentValue = UPI.MySQLQueryResult.getString( "Comment" );
          if( !commentValue.equals( comment ) )
          {
            return false;
          }
        }
      }
    }

    catch( Exception e )
    {
      // Error reading from database
      return false;
    }

    // If we made it this far, that means all our criteria for verification passed
    return true;
  }
}

// END OF FILE -----------------------------------------------------------------

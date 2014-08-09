// BEGINNING OF FILE -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// @file Recommend.java
// @desc The recommendation algorithm for the Game Warp Recommendation Engine
// @date 11 Dec 2010
// @auth Game Warp Algorithm Team
////////////////////////////////////////////////////////////////////////////////
package recommendationalgorithm;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.SortedSet;
import java.util.TreeSet;

////////////////////////////////////////////////////////////////////////////////
// @class recommend
// @desc The class to run the Game Warp recommendation algorithm
////////////////////////////////////////////////////////////////////////////////
public class Recommend
{
  // Create a user profile information database interface
  private UPI_Interface UPI;
  private GameDatabase  gameDB;

  // This is pre-calculated information for the possible permutations for
  // a three-tuple. A general function isn't really necessary for now.
  private final int PERMUTATION_THREE[][] =
  {
      {1,1,1},{1,1,0},{1,0,1},{0,1,1},{1,0,0},{0,1,0},{0,0,1}
  };

  // The number of genres to use to try to match to the user's tastes
  private final int NUM_GENRES_TO_REC = 3;
  // The number of games to list as "top recommendations" to the user
  private final int NUM_GAMES_TO_REC  = 5;
  // The number of games to grab from the database
  private final int NUM_GAMES_TO_GRAB = 15;
  // The threshold below which a game doesn't fall into "TopMatchedGames" and falls into "NicheGames"
  private final double LOWEST_ACCEPTABLE_RATING = 6.2;
  // The number of games with no matching user information to look for
  private final int NUM_NULL_GAMES    = 2;

  private final String gameDelim = " | ";      // Separates gameURIs in results string
  private final String categoryDelim = " || "; // Separates sets of gameURIs (top, niche) in results string

  // A set containing games matched to user tastes and their associated algorithm scores.
  private SortedSet<MatchedGame> genreMatchedGames = new TreeSet<MatchedGame>();

  // Games that are the optimal match to user taste (X) 
  private ArrayList<Game> topMatchedGames = new ArrayList<Game>();

  // Games that are niche games the user might like (Z)
  private ArrayList<Game> nicheGames = new ArrayList<Game>();

  // Games that are recommended to the user to fill NULL values in SQL tables
  private ArrayList<Game> nullGames = new ArrayList<Game>();

  // An ArrayList containing information on the user's favorite genres
  private ArrayList<Genre> userTopGenres = new ArrayList<Genre>();

  // A list containing the next best possible subset of genres from
  // UserTopGenres and the associated index for the permutation array stored
  private ArrayList<Genre> userNextBestGenres = new ArrayList<Genre>();
  private int              permutationIndex   = 0;

  private final double attributeMultiplier  = 0.3; // Weight attributes to 30% of recommendation score
  private final double theatricalMultiplier = 0.2; // Weight theatrical genres to 20% of recommendation score
  private final double genreMultiplier      = 0.4; // Weight game genres to 40% of recommendation score
  private final double gameRatingMultiplier = 0.1; // Weight overall average user score to 10% of recommendation score

  // The processed string to send back to the web
  private String results = "";

  //////////////////////////////////////////////////////////////////////////////
  // @func public Recommend( GameDatabase gameDB )
  // @desc Constructor
  // @param GameDatabase gameDB - The game database to use for recommendation info
  //////////////////////////////////////////////////////////////////////////////
  public Recommend ( GameDatabase gameDB )
  {
    UPI = new UPI_Interface( gameDB );
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public Recommend( GameDatabase gameDB )
  // @desc Constructor
  // @param GameDatabase gameDB - The game database to use for recommendation info
  //////////////////////////////////////////////////////////////////////////////
  public Recommend ( GameDatabase gameDB, String acctNumber )
  {
    UPI = new UPI_Interface( gameDB );
    UPI.setAccNum(acctNumber);
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void driver( String accNum )
  // @desc Gets game URIs for recommendations for the account with accNum
  // @pre  Assumes the correctness of parameters verified from Main.java
  // @param String accNum - the account number of the current user
  // @return String - The results of the recommendation processing
  //////////////////////////////////////////////////////////////////////////////
  public String driver( String accNum )
  {
    // Set the user ID
    UPI.setAccNum( accNum );

    // Get the number of games the user has rated
    UPI.getNumGamesRated();
    if ( UPI.eFlag == true )
    {
      results = "Recommend: Couldn't get number of games rated by account number " + UPI.getAccNum();
      results += "\n" + UPI.eMsg;
      results += "\n" + UPI.eExp.getMessage();
      return results;
    }

    // If the user hasn't rated any games
    if ( UPI.numGamesRated <= 0 )
    {
      // use questionnaire data
      UPI.getUserQuestionnaires();
      if ( UPI.eFlag == true )
      {
        results = "Recommend: Couldn't get questionnaire data for account number " + UPI.getAccNum();
        results += "\n" + UPI.eMsg;
        results += "\n" + UPI.eExp.getMessage();
        return results;
      }
    }

    else
    {
      // Get the user's rated game's data
      UPI.getUserScores();
      if ( UPI.eFlag == true )
      {
        results = "Recommend: Couldn't get user score data for account number " + UPI.getAccNum();
        results += "\n" + UPI.eMsg;
        results += "\n" + UPI.eExp.getMessage();
        return results;
      }
    }

    // Now get a listing of previous games played (to filter them out)
    UPI.getGamesRated();
    if ( UPI.eFlag == true )
    {
      results = "Recommend: Couldn't get list of rated games for account number " + UPI.getAccNum();
      results += "\n" + UPI.eMsg;
      results += "\n" + UPI.eExp.getMessage();
      return results;
    }

    // Get the user's top genres
    seedTopGenres();

    // While we can still add more games to the genre matched games
    while ( genreMatchedGames.size() < NUM_GAMES_TO_GRAB )
    {
      nextGenrePermutation();
      findGenreMatchedGames();
    }

    // Score each of the genre matched games with our relative weights
    scoreGenreMatchedGames();

    // Clear out just in case
    results = "";

    // Get the best of the genre matched games
    getTopMatchedGames();

    // Get the niche games
    getNicheGames();

    // Get the null games
    getNULLGames();

    return results;
  }


  //////////////////////////////////////////////////////////////////////////////
  // @func private void seedTopGenres()
  // @desc Finds the top NUM_GENRES_TO_REC for the user and stores in
  //       UserTopGenres
  // @pre The UPI genre scores function has already filled the set and the info
  //      in the set is sorted (seems as if this should be the case right now)
  //////////////////////////////////////////////////////////////////////////////
  protected void seedTopGenres()
  {
    Iterator<Genre> genreIter = UPI.gameGenreScores.iterator();

    for ( int i = 0; i < NUM_GENRES_TO_REC; i++ )
    {
      if ( genreIter.hasNext() )
      {
        userTopGenres.add( genreIter.next() );
      }
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private void nextGenrePermutation()
  // @desc From the UserTopGenres, seeds UserNextBestGenres with the next best
  //       set of genres for that user.
  // @note EX: UserTopGenres = { FPS, 7, RPG, 8, Platformer, 9 }
  //       0: UserNextBestGenres = { Platformer, RPG, FPS }
  //       1: UserNextBestGenres = { Platformer, RPG }
  //       2: UserNextBestGenres = { Platformer, FPS }
  //       3: UserNextBestGenres = { RPG, FPS }
  //       4: UserNextBestGenres = { Platformer }
  //       5: UserNextBestGenres = { RPG }
  //       6: UserNextBestGenres = { FPS }
  //////////////////////////////////////////////////////////////////////////////
  protected void nextGenrePermutation()
  {
    userNextBestGenres.clear();

    // For each entry in the user's top list, check to see if the permutation
    // includes the genre

    for ( int i = 0; i < userTopGenres.size(); i++ )
    {
      if ( PERMUTATION_THREE[permutationIndex][i] == 1 )
      {
        userNextBestGenres.add( userTopGenres.get( i ) );
      }
    }

    permutationIndex ++;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private void findGenreMatchedGames
  // @desc Searches the game database for games matching all genres in
  //       UserNextBestGenres and appends to GenreMatchedGames.
  //////////////////////////////////////////////////////////////////////////////
  protected void findGenreMatchedGames()
  {
    ArrayList<Game> newGames = gameDB.getGames(userTopGenres, null, null);

    for ( Game game : newGames )
    {
      // Don't recommend a game they've already rated
      if ( UPI.gamesRated.contains( game.getGameURI() ) )
      {
        continue;
      }

      // Create and store a MatchedGame for the game matching all genres,
      // theatrical genres, and attributes
      MatchedGame newMatch = new MatchedGame();

      newMatch.setGame( game );

      genreMatchedGames.add( newMatch );
    }
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
  // @func private void scoreGenreMatchedGames
  // @desc For each GenreMatchedGame, scores the game depending on the algorithm
  //////////////////////////////////////////////////////////////////////////////
  protected void scoreGenreMatchedGames()
  {
    Iterator<MatchedGame> matchGameIter = genreMatchedGames.iterator();
    MatchedGame currMatch;
    Game currentGame;
    TreeSet<MatchedGame> newGenreMatchedSet = new TreeSet<MatchedGame>();

    // As long as there is another matched game to iterate through, the loop continues
    while ( matchGameIter.hasNext() )
    {
      currMatch   = matchGameIter.next();
      currentGame = currMatch.getGame();

      // Default the current game's scores to 5 (on a 10 point scale)
      // just in case the game has no attributes / theatrical genres
      // (Having a score of 5 assumes that it is average)
      double currentGameAttributeScore  = 5;
      double currentGameTheatricalScore = 5;
      double currentGameGenreScore      = 5;
      int    numMatchingGenres          = 0;

      // ^^^^^^^^^ not sure this is necessary?

      // Modify the game's attribute score based on past ratings
      for ( int j = 0; j < currentGame.attributes.size(); j++ )
      {
        // Get the name of an attribute for the current game
        Attribute gameAttribute = currentGame.attributes.get( j );

        // Get the user's score for that attribute
        double attributeScore = UPI.attributeScores.get( gameAttribute.getName() ).getScore();
        
        // Calculate the running average of the attribute scores where j+1
        // is the new total number of game ratings to factor in and j is the
        // number of games the previous average is based on

        double newRating = runningAverage( j, currentGameAttributeScore, attributeScore );
        currentGameAttributeScore = newRating;
      }

      // Modify the game's theatrical genre score based on past ratings
      for ( int j = 0; j < currentGame.theatricalGenres.size(); j++ )
      {
        // Get the name of a theatrical genre for the current game
        Genre gameTheatrical = currentGame.theatricalGenres.get( j );

        // Get the user's score for the theatrical genre
        double theatricalScore = UPI.theatricalGenreScores.get( gameTheatrical.getName() ).getScore();
        
        // Calculate the running average of the theatrical genre scores where j+1
        // is the new total number of game ratings to factor in and j is the
        // number of games the previous average is based on

        double newRating = runningAverage( j, currentGameTheatricalScore, theatricalScore );
        currentGameTheatricalScore = newRating;
      }

      // Modify the game's genre score based on past ratings
      for ( int j = 0; j < currentGame.gameGenres.size(); j++ )
      {
        // Get the name of the genre for the current game
        Genre gameGenre = currentGame.gameGenres.get( j );

        // Loop through the UPI.GameGenreScores to get the user's score for that genre
        boolean         foundUsersGenreScore  = false;
        Iterator<Genre> genreIterator         = UPI.gameGenreScores.iterator();

        while ( !foundUsersGenreScore && genreIterator.hasNext() )
        {
          Genre potentialGenre = genreIterator.next();

          // Check to see if the genre we are looking at in the set
          // is the same as the variable gameGenre
          if ( potentialGenre.getName().equals(gameGenre.getName() ) )
          {
            foundUsersGenreScore = true;
            double genreScore = potentialGenre.getScore();
            
            // Calculate the running average of the genre scores where j+1
            // is the new total number of game ratings to factor in and j is the
            // number of games the previous average is based on

            double newRating = runningAverage( j, currentGameGenreScore, genreScore );
            currentGameGenreScore  = newRating;

            // Increment the matching genres counter if this genre is part of the user's
            // top genre list (switched to look for genre and not string)
            if ( userTopGenres.contains( potentialGenre ) )
            {
              numMatchingGenres++;
            }
          }
        }
      }

      // Modify the game's genre score based on the number of matching genres
      // If only 1 genre matched, then this multiplier will equal 1, if 2 genres
      // then this multiplier will equal 1.1, 3 results in 1.2, etc.
      double matchingGenreMultiplier = 1 + (0.1 * (numMatchingGenres - 1)) ;
      currentGameGenreScore *= matchingGenreMultiplier;

      // Calculate the game's overall weighted score
      currMatch.setScore( attributeMultiplier  * currentGameAttributeScore +
                          theatricalMultiplier * currentGameTheatricalScore +
                          genreMultiplier      * currentGameGenreScore +
                          gameRatingMultiplier * currentGame.getGameScore()
                        );
      
      newGenreMatchedSet.add( currMatch );
    }

    genreMatchedGames = newGenreMatchedSet;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private void getTopMatchedGames
  // @desc Gets the highest scored NUM_GAMES_TO_REC with a global rating of
  //       greater than LOWEST_ACCEPTABLE_RATING and adds to the TopMatchedGames
  //       and update the result string
  // @pre  This function should be called BEFORE getNiche and getNULL for the
  //       parsing function in main
  //////////////////////////////////////////////////////////////////////////////
  
  protected void getTopMatchedGames()
  {
    Iterator<MatchedGame> matchedIter = genreMatchedGames.iterator();
    MatchedGame currGame;

    while ( matchedIter.hasNext() && topMatchedGames.size() < NUM_GAMES_TO_REC )
    {
      currGame = matchedIter.next();

      // If the current game's score is above the lowest accepted rating,
      // add it to the list of matched games and remove the game from the set
      if ( currGame.getGame().getGameScore() >= LOWEST_ACCEPTABLE_RATING )
      {
        topMatchedGames.add( currGame.getGame() );

        results += currGame.getGame().getGameURI() + gameDelim;

        genreMatchedGames.remove( currGame );
      }

      else
      {
        // In this case, add the game to the niche category for usage in that
        // function
        nicheGames.add( currGame.getGame() );
      }
    }

    // Now add the category delimiter to the results string to indicate the
    // new one
    results += categoryDelim;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private void getNicheGames
  // @desc Puts the niche games stored during getTopMatchedGames and adds to
  //       the result string
  // @pre  This function should run AFTER getTopMatchedGames and BEFORE getNULL.
  //////////////////////////////////////////////////////////////////////////////
  protected void getNicheGames()
  {
    for (int i = 0; i < nicheGames.size(); i++)
    {
      results += nicheGames.get( i ).getGameURI() + gameDelim;
    }

    results += categoryDelim;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private void getNULLGames
  // @desc Searches the database for up to NUM_NULL_GAMES games which have no
  //       information from this user and stores them in NULLGames
  // @note How this function works hasn't been decided exactly yet
  //////////////////////////////////////////////////////////////////////////////
  protected void getNULLGames()
  {
    //TODO:Something.  Anything.  Maybe Random?
    nullGames.add( new Game( "SomeRandomGame" + NUM_NULL_GAMES ) );
  }


  // Accessors and mutators

  public SortedSet<MatchedGame> getGenreMatchedGames()
  {

    return genreMatchedGames;

  }

  // Games that are the optimal match to user taste (X)
  public ArrayList<Game> getTopMatchedGamesObject()
  {

    return topMatchedGames;

  }

  // Games that are niche games the user might like (Z)
  public ArrayList<Game> getNicheGamesObject()
  {

    return nicheGames;

  }

  // Games that are recommended to the user to fill NULL values in SQL tables
  public ArrayList<Game> getNullGamesObject()
  {

    return nullGames;

  }

  // An ArrayList containing information on the user's favorite genres
  public ArrayList<Genre> getUserTopGenres()
  {

    return userTopGenres;

  }

  // A list containing the next best possible subset of genres from
  // UserTopGenres and the associated index for the permutation array stored
  public ArrayList<Genre> getUserNextBestGenres()
  {

    return userNextBestGenres;

  }

  public int getPermutationIndex()
  {

    return permutationIndex;
    
  }

  public int getNumGenresToRec()
  {
   return NUM_GENRES_TO_REC;
  }

  public int getNumGamesToRec()
  {
    return NUM_GAMES_TO_REC;
  }

  public int getNumGamesToGrab()
  {
    return NUM_GAMES_TO_GRAB;
  }

  public double getLowestAcceptableRating()
  {
    return LOWEST_ACCEPTABLE_RATING;
  }

  public int getNumNullGames()
  {
    return NUM_NULL_GAMES;
  }

  public UPI_Interface getUPIInterface()
  {
    return UPI;
  }

  public String getResult()
  {
    return results;
  }

  public String getGameDelim()
  {
    return gameDelim;
  }

  public String getCategoryDelim()
  {
    return categoryDelim;
  }

  public double getLowScore()
  {
    return LOWEST_ACCEPTABLE_RATING;
  }
}
// END OF FILE -----------------------------------------------------------------

// BEGINNING OF FILE -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// @file Main.java
// @desc The recommendation algorithm for the Game Warp Recommendation Engine
// @date 11 Dec 2010
// @auth Game Warp Algorithm Team
////////////////////////////////////////////////////////////////////////////////
package recommendationalgorithm;

import java.io.*;

public class Main
{
  //////////////////////////////////////////////////////////////////////////////
  // @func public static void main( String[] args )
  // @desc The main function for the Game Warp system actions
  // @param String[] args - the command line parameters passed in
  // @note [0] - String 0 or 1
  //             0: Run the recommendation algorithm with the passed parameters
  //             1: Run the rating algorithm with the passed parameters
  // @note For Recommendation algorithm the parameter list needs to be:
  //             "0, <username>, <results storage location>"
  // @note For Rating algorithm the parameter list needs to be:
  //             "1, <username>, <gameURI>, <new rating>, <comment>, <results storage location>"
  //////////////////////////////////////////////////////////////////////////////
  public static void main( String[] args )
  {
    

    int    operationType = Integer.valueOf( args[0] );
    String username      = args[1];
    String gameURI       = "";
    double newRating     = 0.0;
    String newComment    = "";
    String filePath      = "";
    String Results       = "";
    
    //storeResults( "Starting main", filePath );
    

    try
    {
      // Fill in values for variables depending on the operation type
      if ( operationType == 0 )
      {
        filePath = args[2] + "/" + username;
      }

      else if ( operationType == 1 )
      {
        gameURI    = args[2];
        newRating  = Double.valueOf( args[3] );
        newComment = args[4];
        filePath   = args[5] + "/" + username;
      }

      storeResults( "Parameters assigned", filePath );
    }

    catch ( Exception e )
    {
      Results = "Error in setting default values from command line parameters.";
      Results += " \nEXCEPTION: " + e.getMessage();

      storeResults( Results, filePath );
      return;
    }

    GameDatabase gameDB  = new GameDatabase();
 storeResults( "gamedb initialized. ", filePath );

    try
    {
      // Check each argument, if the result sent back isn't ""
      // it means there was an error, take care of it
     

      Results = checkArgs( operationType,
                           username,
                           gameURI,
                           newRating,
                           newComment,
                           filePath,
                           gameDB
                         );
      storeResults( "arguments checked. ", filePath );
      if ( Results.compareTo( "" ) != 0 )
      {
        storeResults( Results, filePath );
        return;
      }
    }

    catch ( Exception e )
    {
      Results = "Error in checking the command line arguments for validity.";
      Results += " \nEXCEPTION: " + e.getMessage();

      storeResults( Results, filePath );
      return;
    }

    storeResults( "checking username", filePath );
    // Set up the UPI Interface
    UPI_Interface UPI = new UPI_Interface( gameDB );
    UPI.setAccNum( UPI.getAccNumFromUsername( username ) );
    storeResults( "queried for acc num from username", filePath );

    if ( UPI.eFlag == true )
    {
      Results = UPI.eMsg;
      Results += " \n EXCEPTION: " + UPI.eExp.getMessage();
      storeResults( Results, filePath );
      return;
    }

    if ( operationType == 0 )
    {
      try
      {
        storeResults( "running recommender", filePath );
        Recommend Recommender = new Recommend( gameDB );
        Results = Recommender.driver( UPI.getAccNum() );
        storeResults( "recommender run", filePath );
      }

      catch ( Exception e )
      {
        Results = "Couldn't perform the recommendation.";
        Results += " \n EXCEPTION: " + e.getMessage();
      }
    }

    else if ( operationType == 1 )
    {
      try
      {
        storeResults( "running rater", filePath );
        Rate Rater = new Rate();
        Results = Rater.driver( UPI.getAccNum(),
                                gameURI,
                                newComment,
                                newRating,
                                gameDB
                              );
        storeResults( "rater run", filePath );
      }

      catch ( Exception e )
      {
        Results = "Couldn't perform the rating.";
        Results += " \n EXCEPTION: " + e.getMessage();
      }
    }

    storeResults( Results, filePath );
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private static String checkArgs( int operationType,
  //                                        String username,
  //                                        String gameURI,
  //                                        double newRating,
  //                                        String newComment,
  //                                        String filePath,
  //                                        GameDatabase gameDB
  //                                       )
  // @desc Checks the command line arguments for correctness
  // @param String[] args - the command line arguments
  // @ret true - if the command line arguments are as expected
  // @ret false - if the command line arguments are not as expected
  //////////////////////////////////////////////////////////////////////////////
  private static String checkArgs( int operationType,
                                   String username,
                                   String gameURI,
                                   double newRating,
                                   String newComment,
                                   String filePath,
                                   GameDatabase gameDB
                                 )
  {
    String rtnMsg = "";

    // Check the operation type
    if ( operationType != 0 && operationType != 1 )
    {
      rtnMsg = "Invalid operation type: " + Integer.toString( operationType ) + ".";
      return rtnMsg;
    }

    storeResults( "checkArgs: op type checked", filePath );

    // Check to make sure the username exists in the database
    UPI_Interface UPI = new UPI_Interface( gameDB );
    UPI.MySQLQuery( "SELECT UserName FROM Account WHERE UserName = '" + username + "'" );

    storeResults( "checkArgs: username query finished", filePath );

    if ( UPI.eFlag == true )
    {
      rtnMsg = UPI.eMsg;
      rtnMsg += " \n EXCEPTION: " + UPI.eExp.getMessage();
      return rtnMsg;
    }

    else
    {
      try
      {
        // Resulting set only has one row of data, with only one column
        if ( !UPI.MySQLQueryResult.next() )
        {
          rtnMsg = "UserName " + username + " does not exist in the database.";
          return rtnMsg;
        }

        storeResults( "checkArgs: UPI made sure that username exists", filePath );
      }

      catch ( Exception e )
      {
        rtnMsg = "Failed to parse the check for username existence for user " + username;
        rtnMsg += " \n EXCEPTION: " + e.getMessage();
        return rtnMsg;
      }
    }

    storeResults( "checkArgs: checking file permissions", filePath );
    // Check to make sure we can make the output file
    File outputFile = new File( filePath + ".txt" );
    try
    {
      // If the file already exists...
      if ( outputFile.exists() == true )
      {
        storeResults( "checkArgs: file already exists", filePath );
        // See if we can write
        if ( outputFile.canWrite() == false )
        {
          rtnMsg = "Can't write to " + filePath + ".txt output file.";
          return rtnMsg;
        }
      }

      // Try to create a new file since it doesn't exist, make sure we can
      else if ( outputFile.createNewFile() == false)
      {
        rtnMsg = "Can't create " + filePath + ".txt output file.";
        return rtnMsg;
      }
    }

    catch ( Exception e )
    {
      rtnMsg = "Failed to check for username " + username + "'s previous results.";
      rtnMsg += " \n EXCEPTION: " + e.getMessage();
      return rtnMsg;
    }

    // If doing a rating, range check and stuff on everything
    if ( operationType == 1 )
    {
      // Make sure the game URI exists in the game database
      if( !gameDB.gameExists( gameURI ) )
      {
        rtnMsg = "Invalid game URI. Game " + gameURI + " does not exist in the database.";
        return rtnMsg;
      }

      // Make sure the rating is between 0 and 10
      else if ( newRating < 0 || newRating > 10 )
      {
        rtnMsg = "Invalid rating for the game. " + newRating + " is out of bounds.";
        return rtnMsg;
      }

      // Make sure the comment isn't longer than the size of a MEDIUM_TEXT field
      else if ( newComment.length() > 16777215 )
      {
        rtnMsg = "Comment too large. Make the comment smaller.";
        return rtnMsg;
      }
    }

    /**
     * TODO: Check to make sure the GameDB is a valid game database     *
     */

    return rtnMsg;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private static boolean storeResults( String Results, String filePath)
  // @desc Writes the string Results to the filePath
  // @pre  Validity of output path has been verified by checkArgs
  // @param String Results - the String to write to file
  // @param String filePath - the location to write the Results to
  // @post Creates a file called username.txt in the directory filePath
  //////////////////////////////////////////////////////////////////////////////
  private static boolean storeResults( String Results, String filePath)
  {
    File outputFile = new File( filePath + ".txt");

    try
    {
      BufferedWriter writer = new BufferedWriter( new FileWriter( outputFile, true ) );

      // Newline
      // writer.newLine();

      // Results
      writer.write( Results );
      //writer.append( Results );


      // Another newline
      writer.newLine();

      // Close the writer
      writer.close();
    }

    catch ( Exception e )
    {
      return false;
    }

    return true;
  }
}

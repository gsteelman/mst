// BEGINNING OF FILE -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// @file UPI_Interface.java
// @desc Interface for interacting with the user profile information database.
// @date 11 Dec 2010
// @auth Game Warp Algorithm Team
////////////////////////////////////////////////////////////////////////////////
package recommendationalgorithm;

//import java.sql.Connection;
//import java.sql.DriverManager;
import java.sql.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;

//import com.mysql.jdbc.MySQLConnection;
//import com.mysql.jdbc.Connection;
//import com.mysql.jdbc.Driver;
//import com.mysql.jdbc.
///import com.mysql.jdbc.Connection;

////////////////////////////////////////////////////////////////////////////////
// @class UPI_Interface
// @desc Interface for interacting with the user profile information database.
////////////////////////////////////////////////////////////////////////////////
public class UPI_Interface
{
  // MySQL UPI credentials -----------------------------------------------------
  private String MySQLURL = "jdbc:mysql://localhost:3306/miner012";
  //private String MySQLURL = "jdbc:mysql://mysql.minersoft.org:3306/miner012";
  private String MySQLUID = "miner012";
  private String MySQLPWD = "joeminer";

  // The GameDatabase associated with the project
  private GameDatabase gameDB;
  final protected static String gameURIPrefix = "http://www.gamewarp.org/#";
  final protected static String genreURIPrefix = "http://www.gamewarp.org/genre#";
  final protected static String tgenreURIPrefix = "http://www.gamewarp.org/tgenre#";
  final protected static String tagURIPrefix = "http://www.gamewarp.org/tags#";
  final protected static String platformURIPrefix = "http://www.gamewarp.org/platform#";
  final protected static String personalityURIPrefix = "http://www.gamewarp.org/personality#";
  final protected static String rdfsURIPrefix = "http://www.w3.org/2000/01/rdf-schema#";

  // User specific UPI member data ---------------------------------------------
  // The specific user's account number
  private String accountNumber = "";

  // The number of games account number accountNumber has rated in the database
  public int numGamesRated = 0;

  // Stores the list of game URIs accountNumber has rated in the database
  public ArrayList<String> gamesRated = new ArrayList<String>();

  // Stores the user's Game genre ratings and number of times it was used
  public SortedSet<Genre> gameGenreScores = new TreeSet<Genre>();

  // Stores the user's Theatrical genre ratings and number of times it was used
  public Map<String, Genre> theatricalGenreScores = new HashMap<String, Genre>();

  // Stores the user's Attribute ratings and number of times it was used
  public Map<String, Attribute> attributeScores = new HashMap<String, Attribute>();

  // Game specific UPI member data ---------------------------------------------
  // The specific game's URI
  private String gameURI;

  // Stores a game's global average score and number of times it's been rated
  public double globalGameScore;
  public int    globalNumGameRatings;

  // Store the ResultSet from the last query to the SQL databases
  public java.sql.ResultSet  MySQLQueryResult;
  public Connection          MySQLQueryConnection;
  //public com.mysql.jdbc.Connection MySQLQueryConnection;

  // Misc error handling -------------------------------------------------------
  // Stores the error flag and text for the last operation
  public boolean   eFlag = false;
  public String    eMsg  = "";
  public Exception eExp;

  //////////////////////////////////////////////////////////////////////////////
  // @func public UPI_Interface(GameDatabase gameDB)
  // @desc Constructor
  // @param GameDatabase gameDB - the game database to use with this UPI_Interface
  //////////////////////////////////////////////////////////////////////////////
  public UPI_Interface( GameDatabase gameDB )
  {
    this.gameDB = gameDB;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public String getAccNum()
  // @desc Gets the account number currently in use by the interface
  // @return String - the account number currently in use by the interface
  //////////////////////////////////////////////////////////////////////////////
  public String getAccNum()
  {
    return accountNumber;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void setAccNum( String newAccNum )
  // @desc Sets the account number to the specified account number
  // @param String newAccNum - The account number to set to
  //////////////////////////////////////////////////////////////////////////////
  public void setAccNum( String newAccNum )
  {
    accountNumber = newAccNum;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public String getAccNumFromUsername( String username )
  // @desc Gets the account number associated with a username for ease of use
  // @return String - the accountNumber associated with the specified username in the database
  //////////////////////////////////////////////////////////////////////////////
  public String getAccNumFromUsername( String username )
  {
    String theAccNum = "";
    String query     = "SELECT AccountNumber FROM Account WHERE UserName = '" + username + "'";

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return theAccNum;
    }

    try
    {
      // Check to make sure we got results from the query
      if ( MySQLQueryResult.isLast() )
      {
        setErrors( "Username " + username + " doesn't have an account number.", null );
        return theAccNum;
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure there is an account number for username " + username + " results were retreived.", e );
      return theAccNum;
    }

    try
    {
      // Resulting set only has one row of data, with only one number
      while ( MySQLQueryResult.next() )
      {
        theAccNum = MySQLQueryResult.getString( 1 );
      }

      if ( theAccNum.equals( "" ) )
      {
        setErrors( "The account number for username " + username + " does not exist or is blank.", null );
        return theAccNum;
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse the account number for user " + username, e );
      return theAccNum;
    }

    return theAccNum;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getNumGamesRated()
  // @desc Gets the number of games rated by the current account number
  // @pre  The account number has been properly set by setAccNum()
  // @post Stores the number of games rated by the user in numGamesRated
  //////////////////////////////////////////////////////////////////////////////
  public void getNumGamesRated()
  {
    numGamesRated = -1;
    String query  = "SELECT COUNT(*) FROM UserGameRatings WHERE AccountNumber = '" + getAccNum() + "'";

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Resulting set only has one row of data, with only one column
      while ( MySQLQueryResult.next() )
      {
        numGamesRated = MySQLQueryResult.getInt( 1 );
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse the number of games rated by user " + getAccNum(), e );
      return;
    }

    if ( numGamesRated == -1 )
    {
      setErrors( "The number of games rated by account number " + getAccNum() + " could not be retreived.", null );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getGameGenreScores()
  // @desc Queries the UPI database and retrieves all game genre scores and
  //       number of uses for the current user
  // @pre The account number has been properly set by setAccNum()
  // @post Stores the game genre names, scores, and number of uses in GameGenreScores
  //////////////////////////////////////////////////////////////////////////////
  public void getGameGenreScores()
  {
    gameGenreScores.clear();
    String query    = "SELECT * FROM UserProfileGenres WHERE AccountNumber = '" + getAccNum() + "'";
    Genre currGenre = new Genre();

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Check to make sure we got results from the query
      if ( MySQLQueryResult.isLast() )
      {
        setErrors( "Failed to get the game genre scores for " + getAccNum(), null );
        return;
      }
    }

    catch ( Exception e ){
      setErrors( "Error checking to make sure game genres were retreived.", e );
      return;
    }

    try
    {
      // Add the genre scores for the current user one by one to GameGenreScores
      System.out.println("MySQLQueryResult = " + MySQLQueryResult.toString());
      while ( MySQLQueryResult.next() )
      {
        // tuples look like <AccountNumber, Genre, Score, NumberRatings>
        // Set the name of the genre
        currGenre.setName( genreURIPrefix + MySQLQueryResult.getString( 2 ) );
        System.out.println("currGenre = " + currGenre.getName());

        // Set the score of the genre
        currGenre.setScore( MySQLQueryResult.getDouble( 3 ) );
        System.out.println("currGenre = " + currGenre.getScore());
        
        // Set the number of ratings of the genre
        currGenre.setNumScores( MySQLQueryResult.getInt( 4 ));
        System.out.println("currGenre = " + currGenre.getNumScores());
        
        // Add the genre with scores to the list of genres, make sure it wasn't already there
        gameGenreScores.add( currGenre );
        System.out.println("gameGenreScores.size() = " + gameGenreScores.size());
       // }
        //if ( !gameGenreScores.add( currGenre ) )
        //{
          //setErrors( "The specified genre already exists in the genre set. Something went wrong.", null );
          //return;
        //}
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse and store the game genre scores for user " + getAccNum(), e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void writeGameGenreScores()
  // @desc Writes the numbers in GameGenreScores to the UPI database for the current user
  // @pre  GameGenreScores has been seeded with data by getGameGenreScores
  // @pre The account number has not been changed since getGameGenreScores was called
  // @note This operation is irreversible! Use extreme caution!
  //////////////////////////////////////////////////////////////////////////////
  public void writeGameGenreScores()
  {
	  System.out.println("In writeGameGenreScores");
	  System.out.println("gameGenreScores.size() = " + gameGenreScores.size());
    try
    {
      // Check to make sure genre parameters are valid before writing

      Iterator<Genre> genreIter = gameGenreScores.iterator();
  	
      System.out.println("after genreIter");
      for (Iterator<Genre> it = gameGenreScores.iterator(); it.hasNext(); ) {
    	    //System.out.println(it.next());
    	    Genre currGenre = it.next();
            
            String query = "UPDATE UserProfileGenres SET " +
            "Score = '" + Double.toString( currGenre.getScore() ) + "'" +
            ", NumberRatings = '" + Integer.toString( currGenre.getNumScores() ) + "'" +
            " WHERE Genre = " +
            "'" + currGenre.getName().substring( currGenre.getName().indexOf( "#" ) +1 ) + "'" +
            " AND AccountNumber = " +
            "'" + getAccNum() + "';";

    System.out.println("Query: " + query);    	    
    	}
      while( genreIter.hasNext() )
      {
    	//System.out.println("Index of genreIter = " + genreIter.nextIndex());
        System.out.println("In first while");
        // Check the genre parameters and make sure they're valid
        Genre currGenre = genreIter.next();

        // Make sure the genre has a valid name
        if ( !gameDB.genreExists( currGenre.getName() ) )
        {
          System.out.println("gameDB.genreExists( currGenre.getName() ) = " + gameDB.genreExists( currGenre.getName() ));
          System.out.println("gameURI = " + currGenre.getName());
          System.out.println("Before First error check.");

          setErrors( "A genre called " + currGenre.getName() + " does not exist in the database.", null );
          return;
        }
        // Make sure the genre has a valid score
        else if ( currGenre.getScore() < 0 || currGenre.getScore() > 10 )
        {
            System.out.println("Before Second error check.");
          setErrors( "A genre score of " + currGenre.getScore() + " is out of range for genre " + currGenre.getName() + ".", null );
          return;
        }
        // Make sure the genre has a valid number of scores
        else if ( currGenre.getNumScores() < 0 )
        {
            System.out.println("Before Third error check.");
          setErrors( "A number of ratings of " + currGenre.getNumScores() + " for genre " + currGenre.getName() + " is not valid.", null );
          return;
        }
        System.out.println("After all error checks.");

      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure genre parameters are OK before writing to database.", e );
      return;
    }

    try
    {
      System.out.println("In second try block.");
      // Create the query to store the updated numbers for the current genre
      Iterator<Genre> genreIter = gameGenreScores.iterator();

      while( genreIter.hasNext() )
      {
        Genre currGenre = genreIter.next();
        String query = "UPDATE UserProfileGenres SET " +
                "Score = '" + Double.toString( currGenre.getScore() ) + "'" +
                ", NumberRatings = '" + Integer.toString( currGenre.getNumScores() ) + "'" +
                " WHERE Genre = " +
                "'" + currGenre.getName().substring( currGenre.getName().indexOf( "#" ) +1 ) + "'" +
                " AND AccountNumber = " +
                "'" + getAccNum() + "';";
    
        System.out.println("Query: " + query);
        System.out.println("eflag before query = " + eFlag);
        MySQLUpdate( query );
        System.out.println("eFlag after query = " + eFlag);
        if ( eFlag == true )
        {
          return;
        }
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Something went wrong trying to write the genre scores to the database.", e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getTheatricalGenreScores()
  // @desc Queries the UPI database and retrieves all theatrical genre scores and
  //       number of uses for the current user
  // @pre The account number has been properly set by setAccNum()
  // @post Stores the theatrical genre names, scores, and number of uses in TheatricalGenreScores
  //////////////////////////////////////////////////////////////////////////////
  public void getTheatricalGenreScores()
  {
    theatricalGenreScores.clear();
    String query = "SELECT * FROM UserProfileTheatricalGenres WHERE AccountNumber = '" + getAccNum() + "'";

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Check to make sure we got results from the query
      if ( MySQLQueryResult.isLast() )
      {
        setErrors( "Failed to get the theatrical genre scores for " + getAccNum(), null );
        return;
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure theatrical genres were retreived.", e );
      return;
    }

    try
    {
      // Add the genre scores for the current user one by one to TheatricalGenreScores
      while ( MySQLQueryResult.next() )
      {
        // tuples look like <AccountNumber, Genre, Score, NumberRatings>
        Genre genre = new Genre();

        // Set the score of the theatrical genre
        genre.setScore( MySQLQueryResult.getDouble( 3 ) );

        // Set the number of ratings of the theatrical genre
        genre.setNumScores( MySQLQueryResult.getInt( 4 ) );

        // Set the name of the theatrical genre and map it to the score and number of ratings
        genre.setName( tgenreURIPrefix + MySQLQueryResult.getString( 2 ) );
        theatricalGenreScores.put( genre.getName(), genre );

        clearErrors();
      }
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse and store the theatrical genre scores for user " + getAccNum(), e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void writeTheatricalGenreScores()
  // @desc Writes the numbers in TheatricalGenreScores to the UPI database for the current user
  // @pre  TheatricalGenreScores has been seeded with data by getTheatricalGenreScores
  // @pre The account number has not been changed since getTheatricalGenreScores was called
  // @note This operation is irreversible! Use extreme caution!
  //////////////////////////////////////////////////////////////////////////////
  public void writeTheatricalGenreScores()
  {
    ArrayList<String> allTGenres = gameDB.listTGenres();

    try
    {
      // Check to make sure theatrical genre parameters are valid before writing
      Iterator<String> allTGenresIter = allTGenres.iterator();

      while( allTGenresIter.hasNext() )
      {
        String tGenreName = allTGenresIter.next();

        // Make sure the theatrical genre has a valid name
        if ( !gameDB.tgenreExists( tgenreURIPrefix + tGenreName ) )
        {
          setErrors( "A theatrical genre called " + tGenreName + " does not exist in the database.", null );
          return;
        }

        // Make sure the theatrical genre has a valid score
        double tGenreScore = theatricalGenreScores.get( tGenreName ).getScore();
        if ( tGenreScore < 0 || tGenreScore > 10 )
        {
          setErrors( "A theatrical genre score of " + Double.toString( tGenreScore ) + " is out of range for theatrical genre " + tGenreName + ".", null );
          return;
        }

        // Make sure the theatrical genre has a valid number of scores
        int tGenreRatings = theatricalGenreScores.get( tGenreName ).getNumScores();
        if ( tGenreRatings < 0 )
        {
          setErrors( "A number of ratings of " + Integer.toString( tGenreRatings ) + " for genre " + tGenreName + " is not valid.", null );
          return;
        }
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure theatrical genre parameters are OK before writing to database.", e );
      return;
    }

    try
    {
      // Write scores to the database
      Iterator<String> allTGenresIter = allTGenres.iterator();

      while( allTGenresIter.hasNext() )
      {
        String tGenreName  = allTGenresIter.next();
        double tGenreScore = theatricalGenreScores.get(tGenreName).getScore();
        int tGenreRatings  = theatricalGenreScores.get(tGenreName).getNumScores();

        String query = "UPDATE UserProfileTheatricalGenres SET " +
                "Score = '" + Double.toString( tGenreScore ) + "'" +
                ", NumberRatings = '" + Integer.toString( tGenreRatings ) + "'" +
                " WHERE Genre = " +
                "'" +	tGenreName.substring( tGenreName.indexOf( "#" ) +1 ) + "'" +
                " AND AccountNumber = " +
                "'" + getAccNum() + "';";
        System.out.println("Query: " + query);
        MySQLUpdate( query );
        if ( eFlag == true )
        {
          return;
        }
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Something went wrong trying to write the theatrical genre scores to the database.", e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getAttributeScores()
  // @desc Queries the UPI database and retrieves all attribute scores and
  //       number of uses for the current user
  // @pre The account number has been properly set by setAccNum()
  // @post Stores the attribute names, scores, and number of uses in TheatricalGenreScores
  //////////////////////////////////////////////////////////////////////////////
  public void getAttributeScores()
  {
    attributeScores.clear();
    String query = "SELECT * FROM UserProfileAttributes WHERE AccountNumber = '" + getAccNum() + "'";

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Check to make sure we got results from the query
      if ( MySQLQueryResult.isLast() )
      {
        setErrors( "Failed to get the attribute scores for " + getAccNum(), null );
        return;
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure attributes were retreived.", e );
      return;
    }

    try
    {
      // Add the attribute scores for the current user one by one to AttributeScores
      while ( MySQLQueryResult.next() )
      {
        // tuples look like <AccountNumber, Attribute, Score, NumberRatings>
        Attribute attribute = new Attribute();

        // Set the score of the attribute
        attribute.setScore( MySQLQueryResult.getDouble( 3 ) );

        // Set the number of ratings of the attribute
        attribute.setNumScores( MySQLQueryResult.getInt( 4 ) );

        // Set the name and map to the attribute object
        attribute.setName( tagURIPrefix + MySQLQueryResult.getString( 2 ) );
        attributeScores.put( attribute.getName(), attribute );
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse and store the attribute scores for user " + getAccNum(), e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void writeAttributeScores()
  // @desc Writes the numbers in AttributeScores to the UPI database for the current user
  // @pre  AttributeScores has been seeded with data by getAttributeScores
  // @pre The account number has not been changed since getAttributeScores was called
  // @note This operation is irreversible! Use extreme caution!
  //////////////////////////////////////////////////////////////////////////////
  public void writeAttributeScores()
  {
    try
    {
      // Check to make sure attribute parameters are valid before writing
      Set<String> attrSet = attributeScores.keySet();

      for ( String attrName : attrSet )
      {
        // CAN'T DO THIS PART because the SQL doesn't know if it needs to append
        // the tagURIPrefix or the persURIPrefix because of things just being
        // stored as "sword" or "foxMcCloud"
        // Make sure the attribute has a valid name
        // if( !gameDB.attributeExists( tagURIPrefix + attrName ) )
        // {
          // setErrors( "An attribute called " + attrName + " does not exist in the database.", null );
          // return;
        // }

        // Make sure the attribute has a valid score
        double attributeScore = attributeScores.get( attrName ).getScore();
        if( attributeScore < 0 || attributeScore > 10 )
        {
          setErrors( "A theatrical genre score of " + attributeScore + " is out of range for theatrical genre " + attrName + ".", null );
          return;
        }

        // Make sure the attributee has a valid number of scores
        int attributeRatings = attributeScores.get( attrName ).getNumScores();
        if ( attributeRatings < 0 )
        {
          setErrors( "A number of ratings of " + attributeRatings + " for genre " + attrName + " is not valid.", null );
          return;
        }
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure attribute parameters are OK before writing to database. ", e );
      return;
    }

    try
    {
      // Write scores to the database
      Set<String> attrSet = attributeScores.keySet();

      for ( String attrName : attrSet )
      {
        double attributeScore = attributeScores.get(attrName).getScore();
        int attributeRatings  = attributeScores.get(attrName).getNumScores();

        String query = "UPDATE UserProfileAttributes SET " +
                "Score = '"   + Double.toString( attributeScore ) + "'" +
                ", NumberRatings = '" + Integer.toString( attributeRatings ) + "'" +
                " WHERE Attribute = " +
                "'" + attrName.substring( attrName.indexOf( "#" ) +1 ) + "'" +
                " AND AccountNumber = " +
                "'" + getAccNum() + "';";

        System.out.println("Query: " + query);
        
        MySQLUpdate( query );
        if ( eFlag == true )
        {
          return;
        }
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Something went wrong trying to write the attribute scores to the database.", e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getUserScores()
  // @desc Get all relevant user data from the UPI database for the current user
  // @pre The account number has been properly set by setAccNum()
  //////////////////////////////////////////////////////////////////////////////
  public void getUserScores()
  {
    getNumGamesRated();
    if ( eFlag == true )
    {
      return;
    }

    getGameGenreScores();
    if ( eFlag == true )
    {
      return;
    }

    getTheatricalGenreScores();
    if ( eFlag == true )
    {
      return;
    }

    getAttributeScores();
    if ( eFlag == true )
    {
      return;
    }

    getGamesRated();
    if ( eFlag == true )
    {
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void writeUserScores()
  // @desc Writes all relevant user data to the UPI database for the current user
  // @pre the user ID has been set
  // @pre  GameGenreScores has been seeded with data by getGameGenreScores
  // @pre  TheatricalGenreScores has been seeded with data by getTheatricalGenreScores
  // @pre  AttributeScores has been seeded with data by getAttributeScores
  // @post Writes all relevant user data to the UPI database for the current user
  // @note This operation is irreversible! Use extreme caution!
  //////////////////////////////////////////////////////////////////////////////
  public void writeUserScores()
  {
	  System.out.println("Before writeGameGenreScores()\n");
    writeGameGenreScores();
    System.out.println("After writeGameGenreScores()\n");
    System.out.println("eFlag after writeGameGenreScores = " + eFlag);
    if ( eFlag == true )
    {
      return;
    }
    System.out.println("Before writeTheatricalGenreScores()\n");
    writeTheatricalGenreScores();
    System.out.println("After writeTheatricalGenreScores()\n");
    if ( eFlag == true )
    {
      return;
    }
    System.out.println("Before writeAttributeScores()\n");
    writeAttributeScores();
    System.out.println("After writeAttributeScores()\n");
    if ( eFlag == true )
    {
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getUserScores()
  // @desc Get all relevant user data from the UPI database for the current user
  // @pre The account number has been properly set by setAccNum()
  //////////////////////////////////////////////////////////////////////////////
  public void getUserQuestionnaires()
  {
    getUserGenreQuestionnaire();
    if ( eFlag == true )
    {
      return;
    }

    getUserTheatricalGenreQuestionnaire();
    if ( eFlag == true )
    {
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getUserGenreQuestionnaire()
  // @desc Queries the UPI database and retrieves all game genre questionnaire data
  //       for the current user
  // @pre The account number has been properly set by setAccNum()
  // @post Stores the genre questionnaire data in gameGenreScores
  //////////////////////////////////////////////////////////////////////////////
  public void getUserGenreQuestionnaire()
  {
    gameGenreScores.clear();
    String query    = "SELECT * FROM GameGenreQuestionnaire WHERE AccountNumber = '" + getAccNum() + "'";
    Genre currGenre = new Genre();

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Check to make sure we got results from the query
      if ( MySQLQueryResult.isLast() )
      {
        setErrors( "Failed to get the game genre questionnaire data for " + getAccNum(), null );
        return;
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure game genre questionnaire data was retreived.", e );
      return;
    }

    try
    {
      java.sql.ResultSetMetaData MySQLQueryResultMetaData = MySQLQueryResult.getMetaData();

      // Add the genre scores for the current user one by one to GameGenreScores
      while ( MySQLQueryResult.next() )
      {
        // tuples look like <AccountNumber, Action, Adventure, ActionAdventure, Driving, RolePlaying, Simulation, Sport, Strategy, Puzzle, Shooter, Rhythm, Party, Platformer>
        for ( int i = 0; i < MySQLQueryResultMetaData.getColumnCount(); i++ )
        {
          currGenre.setName( genreURIPrefix + MySQLQueryResultMetaData.getColumnName( i ) );
          currGenre.setScore( MySQLQueryResult.getDouble( i ) );
          currGenre.setNumScores( 0 );

          // Add the genre with scores to the list of genres, make sure it wasn't already there
          if ( !gameGenreScores.add( currGenre ) )
          {
            setErrors( "The specified genre numbers from genre questionnaire already exists in the genre set. Something went wrong.", null );
            return;
          }
        }
      }
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse and store the game genre questionnaire data for user " + getAccNum(), null );
      return;
    }

    query = "SELECT * FROM GameSubGenreQuestionnaire WHERE AccountNumber = '" + getAccNum() + "'";

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Check to make sure we got results from the query
      if ( MySQLQueryResult.isLast() )
      {
        setErrors( "Failed to get the game sub genre questionnaire data for " + getAccNum(), null );
        return;
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure sub game genre questionnaire data was retreived.", e );
      return;
    }

    try
    {
      java.sql.ResultSetMetaData MySQLQueryResultMetaData = MySQLQueryResult.getMetaData();

      // Add the genre scores for the current user one by one to GameGenreScores
      while ( MySQLQueryResult.next() )
      {
        for ( int i = 0; i < MySQLQueryResultMetaData.getColumnCount(); i++ )
        {
          currGenre.setName( genreURIPrefix + MySQLQueryResultMetaData.getColumnName( i ) );
          currGenre.setScore( MySQLQueryResult.getDouble( i ) );
          currGenre.setNumScores( 0 );

          // Add the genre with scores to the list of genres, make sure it wasn't already there
          if ( !gameGenreScores.add( currGenre ) )
          {
            setErrors( "The specified genre numbers from genre questionnaire already exists in the genre set. Something went wrong.", null );
            return;
          }
        }
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse and store the game genre questionnaire data for user " + getAccNum(), e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getUserGenreQuestionnaire()
  // @desc Queries the UPI database and retrieves all game genre questionnaire data
  //       for the current user
  // @pre The account number has been properly set by setAccNum()
  // @post Stores the genre questionnaire data in gameGenreScores
  //////////////////////////////////////////////////////////////////////////////
  public void getUserTheatricalGenreQuestionnaire()
  {
    // Get the user genre questionnaire data
    theatricalGenreScores.clear();
    String query    = "SELECT * FROM TheatricalGenreQuestionnaire WHERE AccountNumber = '" + getAccNum() + "'";
    Genre currGenre = new Genre();

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Check to make sure we got results from the query
      if ( MySQLQueryResult.isLast() )
      {
        setErrors( "Failed to get the theatrical genre questionnaire data for " + getAccNum(), null );
        return;
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure theatrical genre questionnaire data was retreived.", e );
      return;
    }

    try
    {
      java.sql.ResultSetMetaData MySQLQueryResultMetaData = MySQLQueryResult.getMetaData();

      String currTGenre = "";

      while ( MySQLQueryResult.next() )
      {
        // Set the name of the genre
        for ( int i = 0; i < MySQLQueryResultMetaData.getColumnCount(); i++ )
        {
          currTGenre = MySQLQueryResultMetaData.getColumnName( i );
          currGenre.setName( tgenreURIPrefix + currTGenre );
          currGenre.setScore( MySQLQueryResult.getDouble( i ) );
          currGenre.setNumScores( 0 );

          // Add the genre with scores to the list of genres, make sure it wasn't already there
          theatricalGenreScores.put( currTGenre, currGenre );
        }
      }
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse and store the theatrical genre questionnaire data for user " + getAccNum(), null );
      return;
    }

    // Get the user genre questionnaire data
    query = "SELECT * FROM TheatricalSubGenreQuestionnaire WHERE AccountNumber = '" + getAccNum() + "'";

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Check to make sure we got results from the query
      if ( MySQLQueryResult.isLast() )
      {
        setErrors( "Failed to get the theatrical sub genre questionnaire data for " + getAccNum(), null );
        return;
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure theatrical sub genre questionnaire data was retreived.", e );
      return;
    }

    try
    {
      java.sql.ResultSetMetaData MySQLQueryResultMetaData = MySQLQueryResult.getMetaData();

      String currTGenre = "";

      while ( MySQLQueryResult.next() )
      {
        // Set the name of the genre
        for ( int i = 0; i < MySQLQueryResultMetaData.getColumnCount(); i++ )
        {
          currTGenre = MySQLQueryResultMetaData.getColumnName( i );
          currGenre.setName( tgenreURIPrefix + currTGenre );
          currGenre.setScore( MySQLQueryResult.getDouble( i ) );
          currGenre.setNumScores( 0 );

          // Add the genre with scores to the list of genres, make sure it wasn't already there
          theatricalGenreScores.put( currTGenre, currGenre );
        }
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse and store the theatrical sub genre questionnaire data for user " + getAccNum(), e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public String getGameURI()
  // @desc Gets the game URI currently in use by the interface
  // @return String - the game URI currently in use by the interface
  //////////////////////////////////////////////////////////////////////////////
  public String getGameURI()
  {
    return gameURI;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void setGameURI( String newGameURI )
  // @desc Sets the game URI currently in use by the interface
  // @return String - the user ID currently in use by the interface
  //////////////////////////////////////////////////////////////////////////////
  public void setGameURI( String newGameURI )
  {
    gameURI = newGameURI;
  }  

  //////////////////////////////////////////////////////////////////////////////
  // @func getGlobalGameScores()
  // @desc Gets the scores and number of ratings globally by all users for the current game
  // @return String - the user ID currently in use by the interface
  //////////////////////////////////////////////////////////////////////////////
  public void getGlobalGameScores()
  {
    globalGameScore      = 0.0;
    globalNumGameRatings = 0;

    String query = "SELECT * FROM GlobalGameRatings WHERE GameURI = '" + getGameURI() + "'";

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Check to make sure we got results from the query
      if ( MySQLQueryResult.isLast() )
      {
        setErrors( "Failed to get the game scores for " + getGameURI(), null );
        return;
      }
    }

    catch ( Exception e )
    {
      setErrors( "Error checking to make sure game scores were retreived.", e );
      return;
    }

    try
    {
      // Add the genre scores for the current user one by one to TheatricalGenreScores
      while ( MySQLQueryResult.next() )
      {
        // tuples look like <GameURI, RatingAverage, NumberOfRatings>
        // Set the game score
        globalGameScore = MySQLQueryResult.getDouble( 2 );

        // Set the number of ratings
        globalNumGameRatings = MySQLQueryResult.getInt( 3 );
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse and store the scores for game " + getGameURI(), e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void writeGlobalGameScores()
  // @desc Writes the numbers in GlobalGameScores to the UPI database for the current game
  // @pre  GlobalGameScores has been seeded with data by getGameGenreScores
  // @note This operation is irreversible! Use extreme caution!
  //////////////////////////////////////////////////////////////////////////////
  public void writeGlobalGameScores()
  {
    try
    {
      if ( globalGameScore < 0 || globalGameScore > 10 )
      {
        setErrors( "globalGameScore of " + globalGameScore + " is out of valid range.", null );
        return;
      }

      else if ( globalNumGameRatings < 0)
      {
        setErrors( "globalNumGameRatings of " + globalNumGameRatings + " is out of valid range.", null );
        return;
      }

      else if( !gameDB.gameExists( getGameURI() ) )
      {
        setErrors( "Invalid game URI. Game " + gameURI + " does not exist in the database.", null );
        return;
      }
    }
    
    catch ( Exception e )
    {
      setErrors( "Error checking to make sure global game score parameters are OK before writing to database. ", e );
      return;
    }

    try
    {
    	
        String query = "SELECT * FROM GlobalGameRatings WHERE GameURI = " +
              "'" + getGameURI() + "'";
        MySQLQuery( query );
        if ( eFlag == true )
        {
          return;
        }

        // Move to the last row in the result.
        // If there are no rows, last returns false, which is what we want
        boolean gameHasGlobalRating = MySQLQueryResult.last();

      //String query = "";
      if ( gameHasGlobalRating )
      {
          query = "UPDATE GlobalGameRatings SET " +
              "RatingAverage = '"   + Double.toString( globalGameScore ) + "'" +
              ", NumberOfRatings = '" + Integer.toString( globalNumGameRatings ) + "'" +
              " WHERE GameURI = " +
              "'" + getGameURI() + "';";
          query = "UPDATE GlobalGameRatings SET " +
          "RatingAverage = '10'" +
          ", NumberOfRatings = '2'" +
          " WHERE GameURI = " +
          "'" + getGameURI() + "';";
          System.out.println("Query: " + query);
      }
      else
      {
    	  query = "INSERT INTO GlobalGameRatings ( GameURI, RatingAverage, NumberOfRatings) VALUES ( '"
                + getGameURI() + "'" +
          ", '" + Double.toString( globalGameScore ) + "'" +
          ", '" + Integer.toString( globalNumGameRatings ) + "');";
    	  System.out.println("Query: " + query);
      }

      MySQLUpdate( query );
      
      System.out.println("After query eflag = " + eFlag);
      
      if ( eFlag == true )
      {
        return;
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse and store the global game data for game " + getGameURI(), e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getGameScores()
  // @desc Gets a list of all game URIs rated by the current account number
  // @pre The account number has been properly set by setAccNum()
  // @post Stores the list of all game URIs raed by the current account number in GamesRated
  //////////////////////////////////////////////////////////////////////////////
  public void getGamesRated()
  {
    gamesRated.clear();
    String query = "SELECT * FROM GlobalGameRatings WHERE AccountNumber = '" + getAccNum() + "'";

    MySQLQuery( query );
    if ( eFlag == true )
    {
      return;
    }

    try
    {
      // Add each game to the gamesRated list
      while ( MySQLQueryResult.next() )
      {
        gamesRated.add( MySQLQueryResult.getString( 2 ) );
      }

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Failed to parse the list of games rated by account " + getAccNum(), e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void LinkUp()
  // @desc Connects to the Game Warp User Profile Information Database
  // @note Stores the connection in MySQLQueryConnection
  //////////////////////////////////////////////////////////////////////////////
  public void LinkUp()
  {
    try
    {
      Class.forName( "com.mysql.jdbc.Driver" ).newInstance();
      //Class.forName( "org.gjt.mm.mysql.Driver" ).newInstance();

      //MySQLQueryConnection = DriverManager.getConnection( MySQLURL, MySQLUID, MySQLPWD );
      MySQLQueryConnection = DriverManager.getConnection("jdbc:mysql://localhost:3306/miner012?user=miner012&password=joeminer");

      System.out.println("Connection: " + MySQLQueryConnection.toString());

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Unable to connect to the SQL database.", e );
      return;
    }

    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void MySQLQuery( String query )
  // @desc Executes a generic MySQL query and stores the results in a ResultSet
  // @param String query - The SQL query to be executed
  // @note Stores the results in MySQLQueryResult
  // @note Use with SELECT
  //////////////////////////////////////////////////////////////////////////////
  public void MySQLQuery( String query )
  {
    LinkUp();    
    if( eFlag == true )
    {
      return; //System.out.println( eExp.getMessage() );
    }

    java.sql.Statement s = null;
    MySQLQueryResult     = null;

    try
    {
      s = MySQLQueryConnection.createStatement();
      MySQLQueryResult = s.executeQuery ( query );

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Query \"" + query + "\" failed.", e );
      return;
    }

    return;
  }


  //////////////////////////////////////////////////////////////////////////////
  // @func public void MySQLUpdate( String query )
  // @desc Executes a generic MySQL update and stores the results in a ResultSet
  // @param String query - The SQL query to be executed
  // @note Use for INSERT, UPDATE, or DELETE
  //////////////////////////////////////////////////////////////////////////////
  public void MySQLUpdate( String query )
  {
    LinkUp();    
    if( eFlag == true )
    {
      System.out.println( eExp.getMessage() );
      return; //System.out.println( eExp.getMessage() );
    }

    java.sql.Statement s = null;
    MySQLQueryResult     = null;

    try
    {
      System.out.println("Query :" +query);
      s = MySQLQueryConnection.createStatement();
      s.executeUpdate( query );

      clearErrors();
    }

    catch ( Exception e )
    {
      setErrors( "Query \"" + query + "\" failed.", e );
      return;
    }

    return;
  }   
  
  //////////////////////////////////////////////////////////////////////////////
  // @func private void clearErrors()
  // @desc clears the error flag and message
  //////////////////////////////////////////////////////////////////////////////
  protected void clearErrors()
  {
    eFlag = false;
    eMsg  = "";
    eExp  = null;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private void setErrors( String newErrorMsg )
  // @desc sets the error flag and message
  // @param String newErrorMsg - The new error message to store
  //////////////////////////////////////////////////////////////////////////////
  protected void setErrors( String newErrorMsg, Exception newException )
  {
    eFlag = true;
    eMsg  = newErrorMsg;
    eExp  = newException;
  }
}

// END OF FILE -----------------------------------------------------------------

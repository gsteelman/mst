// BEGINNING OF FILE -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// @file Game.java
// @desc A class to store game information gathered from the UPI
// @date 26 Nov 2010
// @auth Game Warp Algorithm Team
////////////////////////////////////////////////////////////////////////////////

package recommendationalgorithm;

import java.util.ArrayList;

import com.hp.hpl.jena.query.Query;
import com.hp.hpl.jena.query.QueryExecution;
import com.hp.hpl.jena.query.QueryExecutionFactory;
import com.hp.hpl.jena.query.QueryFactory;
import com.hp.hpl.jena.query.ResultSet;

////////////////////////////////////////////////////////////////////////////////
// @class Game
// @desc Storage for game information
////////////////////////////////////////////////////////////////////////////////
public class Game
{
  private String gameURI;

  // Stores the game's game genres
  public ArrayList<Genre> gameGenres = new ArrayList<Genre>();

  // Stores the game's theatrical genres
  public ArrayList<Genre> theatricalGenres = new ArrayList<Genre>();

  // A list of the attributes the game has
  public ArrayList<Attribute> attributes = new ArrayList<Attribute>();

  // Stores the global rating for the game and the number of users who rated it
  private double gameScore;
  private int    numScores;  

  //////////////////////////////////////////////////////////////////////////////
  // @func public game()
  // @desc Constructor
  //////////////////////////////////////////////////////////////////////////////
  public Game(String gURI )
  {
    gameURI = gURI;
  }

  public String getGameURI()
  {
    return gameURI;
  }

  public void setGameScore( double newGameScore )
  {
    gameScore = newGameScore;
  }

  public double getGameScore()
  {
    return gameScore;
  }

  public void setNumScores( int newNumScores )
  {
    numScores = newNumScores;
  }

  protected int getNumScores()
  {
    return numScores;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public void getGameInformation()
  // @desc Gets all attached game information from the game database for a specifc game
  //       and stores it in the appropriate member data arrays
  //////////////////////////////////////////////////////////////////////////////
  public void getGameInformation(GameDatabase db)
  {
	  Query q;
	  QueryExecution qe;
	  ResultSet results;
	      q       = QueryFactory.create( "SELECT ?genre WHERE { " + gameURI + " a ?genre.}" );
	      qe      = QueryExecutionFactory.create( q, db.getModel());
	      results = qe.execSelect();
	      while ( results.hasNext() )
	      {
	        Genre g = new Genre();
	        g.setName( results.next().toString() );
	        gameGenres.add( g );
	      }
	      
	      q       = QueryFactory.create( "SELECT ?genre WHERE { " + gameURI + " <http://www.gamewarp.org/tags#tgenre> ?genre.}" );
	      qe      = QueryExecutionFactory.create( q, db.getModel() );
	      results = qe.execSelect();
	      while ( results.hasNext() )
	      {
	        Genre g = new Genre();
	        g.setName( results.next().toString() );
	        theatricalGenres.add( g );
	      }
	      
	      q       = QueryFactory.create( "SELECT ?attr WHERE { " + gameURI + " <http://www.gamewarp.org/tags#tags> ?attr.}" );
	      qe      = QueryExecutionFactory.create( q, db.getModel() );
	      results = qe.execSelect();
	      while ( results.hasNext() )
	      {
	        Attribute attr = new Attribute();
	        attr.setName( results.next().toString() );
	        attributes.add( attr );
	      }
    //TODO: Write this function!
    // Connect to the UPI and get the game's global score and number of ratings

    // Need to do this still
  }
}

// END OF FILE -----------------------------------------------------------------

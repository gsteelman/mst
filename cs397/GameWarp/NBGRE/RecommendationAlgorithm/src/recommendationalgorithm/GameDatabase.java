// BEGINNING OF FILE -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// @file GameDatabase.java
// @desc The interface for the game database
// @date 11 Dec 2010
// @auth Game Warp Algorithm Team
////////////////////////////////////////////////////////////////////////////////
package recommendationalgorithm;

import java.io.File;
import java.io.FileInputStream;
import java.util.ArrayList;

import com.hp.hpl.jena.query.Query;
import com.hp.hpl.jena.query.QueryExecution;
import com.hp.hpl.jena.query.QueryExecutionFactory;
import com.hp.hpl.jena.query.QueryFactory;
import com.hp.hpl.jena.query.ResultSet;
import com.hp.hpl.jena.rdf.model.Model;
import com.hp.hpl.jena.rdf.model.ModelFactory;
import com.hp.hpl.jena.rdf.model.ModelMaker;
import com.hp.hpl.jena.rdf.model.NodeIterator;
import com.hp.hpl.jena.rdf.model.ResIterator;
import com.hp.hpl.jena.vocabulary.RDF;
import java.io.BufferedWriter;
import java.io.FileWriter;

////////////////////////////////////////////////////////////////////////////////
// @class GameDatbase
// @desc  The interface to the semantic game database for the Game Warp project
////////////////////////////////////////////////////////////////////////////////
public class GameDatabase
{
  public Model model;
  private ModelMaker maker;
  final private static String DBNAME = "gamedb.rdf"; 
  final private static File   DBDIR  = new File( "db" );

  //////////////////////////////////////////////////////////////////////////////
  // @func GameDatabase
  // @desc The constructor for the GameDatabase object. Creates the database
  //       if it doesn't already exist
  //////////////////////////////////////////////////////////////////////////////
  GameDatabase()
  {
    try
    {
      if( !DBDIR.exists() )
      {
        DBDIR.mkdir();
      }

      maker = ModelFactory.createMemModelMaker();
      model = maker.createDefaultModel();

      model.read(new FileInputStream(DBDIR.getAbsolutePath()+File.separator+DBNAME), null);
    }

    catch ( Exception e )
    {
      File outputFile = new File( "./GAMEDBERROR.txt");

      try
      {
        BufferedWriter writer = new BufferedWriter( new FileWriter( outputFile ) );

        writer.write( "GAME DB CONSTRUCTOR CALLED YEAAAAAH" );
        writer.newLine();
        //writer.write( e.getStackTrace().toString() );
        writer.newLine();
        writer.close();
      }

      catch ( Exception d )
      {

      }

      e.printStackTrace();
    }
  }

  public Model getModel(){
	  return model;
  }
  
  //////////////////////////////////////////////////////////////////////////////
  // @func public static void main(String[] args)
  // @desc The main function for the GameDatabase, constructs the game database
  //       when called. Only call when you want to reconstruct the database
  // @param String[] args - The command line arguments
  //////////////////////////////////////////////////////////////////////////////
  public static void main(String[] args)
  {
    if( !DBDIR.exists() )
    {
      System.out.println( "Database created at " + DBDIR.getAbsolutePath() );
      DBDIR.mkdir();
    }
    
    System.out.println( DBDIR.getAbsolutePath() );
    System.out.flush();
    ModelMaker maker = ModelFactory.createFileModelMaker( DBDIR.getAbsolutePath() );
    Model model      = maker.createModel( DBNAME, false );

    try
    {
      model.read( new FileInputStream( new File( "games.n3" ) ), null, "N3" );
    } 
    
    catch ( Exception e )
    {
      e.printStackTrace();
    }

    model.close();
    maker.close();
    
    GameDatabase gdb = new GameDatabase();
    System.out.println( gdb.gameExists("http://www.gamewarp.org/game#traumaCenterUnderTheKnife") + " should be true." );
    System.out.println( gdb.gameExists("http://www.gamewarp.org/game#castlevaniaSymphonyOfTheMSTStudents") + " should be false." );

    System.out.println( gdb.genreExists("http://www.gamewarp.org/genre#simulation") + " should be true." );
    System.out.println( gdb.genreExists("http://www.gamewarp.org/game#castlevaniaSymphonyOfTheNight") + " should be false." );

    for ( String s : gdb.listTGenres() )
    {
      System.out.println( s );
    }
    
    for ( String s : gdb.listGameGenres() )
    {
      System.out.println( s );
    }
    
    for ( String s : gdb.listGames() )
    {
      System.out.println( s );
    }
    
    //TODO:  Test last method.
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private ArrayList<String> listGames()
  // @desc Returns a list of strings with the URIs for every attribute in the database
  //////////////////////////////////////////////////////////////////////////////
  protected ArrayList<String> listGames()
  {
    ResIterator iter = model.listResourcesWithProperty( model.createProperty( "http://www.w3.org/1999/02/22-rdf-syntax-ns#type" ) );

    ArrayList<String> ret = new ArrayList<String>();

    while ( iter.hasNext() )
    {
      ret.add( iter.next().toString() );
    }

    return ret;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private ArrayList<String> listGameGenres()
  // @desc Returns a list of strings with the URIs for every game genre in the database
  //////////////////////////////////////////////////////////////////////////////
  protected ArrayList<String> listGameGenres()
  {
    NodeIterator iter = model.listObjectsOfProperty( model.createProperty( "http://www.w3.org/1999/02/22-rdf-syntax-ns#type" ) );

    ArrayList<String> ret = new ArrayList<String>();

    while ( iter.hasNext() )
    {
      ret.add( iter.next().toString() );
    }

    return ret;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func private ArrayList<String>listTGenres(
  // @desc Returns a list of strings with the URIs for every theatrical genre in the database
  //////////////////////////////////////////////////////////////////////////////
  public ArrayList<String>listTGenres()
  {
    NodeIterator iter = model.listObjectsOfProperty( model.createProperty( "http://www.gamewarp.org/tags#tgenre" ) );

    ArrayList<String> ret = new ArrayList<String>();

    while ( iter.hasNext() )
    {
      ret.add( iter.next().toString() );
    }

    return ret;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public boolean gameExists( String gameURI )
  // @desc Returns whether or not a game exists in the database
  // @param String gameURI - the gameURI to check for existence of
  // @return true - if the game with gameURI exists in the database
  // @return false - otherwise
  //////////////////////////////////////////////////////////////////////////////
  public boolean gameExists( String gameURI )
  {
    return model.contains( model.createResource( gameURI ), null );
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public boolean genreExists( String genreName )
  // @desc Returns whether or not a genre exists in the database
  // @param String genreName - the URI of the genre to check existence of
  // @return true - if the genre with genreName exists in the database
  // @return false - otherwise
  //////////////////////////////////////////////////////////////////////////////
  public boolean genreExists( String genreName )
  {
    return model.contains( null, RDF.type, model.createResource( genreName ) );
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public boolean tgenreExists( String tGenreName )
  // @desc Returns whether or not a theatrical genre exists in the database
  // @param String tGenreName - the URI of the theattrical genre to check existence of
  // @return true - if the theatrical genre with tGenreName exists in the database
  // @return false - otherwise
  //////////////////////////////////////////////////////////////////////////////
  public boolean tgenreExists( String tGenreName )
  {
    return listTGenres().contains( tGenreName );
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public boolean attributeExists( String attrName )
  // @desc Returns whether or not an attribute exists in the database
  // @param String attrName - the URI of the attribute to check existence of
  // @return true - if the attribute with attrname exists in the database
  // @return false - otherwise
  //////////////////////////////////////////////////////////////////////////////
  public boolean attributeExists( String attrName )
  {
    return model.contains( null, model.createProperty( "http://www.gamewarp.org/tags#tags" ), model.createResource( attrName ) );
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public ArrayList<Game> getGames( ArrayList<Genre> gGenres,
  //			                                  ArrayList<Genre> tGenres,
  //                                        ArrayList<Attribute> attributes
  //                                       )
  // @desc Returns a list of Games who are listed with
  //       every game genre in gGenres
  //       every theatrical genre in tGenres
  //       every attribute in attributes
  // @param ArrayList<Genre> gGenres - A list of game genre URIs to match for this game
  // @param ArrayList<Genre> tGenres - A list of theatrical genre URIs to match for this game
  // @param ArrayList<Attribute> attributes - A list of attribute URIs to match for this game
  // @return ArrayList<Game> - A list of Games who have all the genres, theatrical
  //                           genres, and attributes listed in the function parameters
  public ArrayList<Game> getGames( ArrayList<Genre> gGenres,
                                   ArrayList<Genre> tGenres,
                                   ArrayList<Attribute> attributes
                                 )
  {
    StringBuilder queryBuilder = new StringBuilder();

    queryBuilder.append( "SELECT ?game WHERE {?game " );
    if ( gGenres != null )
    {
      for ( Genre g : gGenres )
      {
        queryBuilder.append( " a " + g.getName() + "; " );
      }
    }

    if ( tGenres != null )
    {
      for ( Genre g : tGenres )
      {
        queryBuilder.append( " <http://www.gamewarp.org/tags#tgenre> " + g.getName() + "; " );
      }
    }

    if ( attributes != null )
    {
      for ( Attribute attr : attributes )
      {
        queryBuilder.append( " <http://www.gamewarp.org/tags#tags> " + attr.getName() + "; " );
      }
    }

    queryBuilder.replace( queryBuilder.lastIndexOf( ";" ), queryBuilder.lastIndexOf( ";" ), "." );

    Query q                  = QueryFactory.create( queryBuilder.toString() );
    QueryExecution qe        = QueryExecutionFactory.create( q, model );
    ResultSet results        = qe.execSelect();
    ArrayList<Game> gameList = new ArrayList<Game>();

    // Add all found games to the list
    while ( results.hasNext() )
    {
      gameList.add( new Game( results.next().toString() ) );
    }

    // Populate each found game with its attributes, theatrical genres, and attributes
    for ( int i = 0; i < gameList.size(); i++ )
    {
      Game game = gameList.get( i );
      
      q       = QueryFactory.create( "SELECT ?genre WHERE { " + game.getGameURI() + " a ?genre.}" );
      qe      = QueryExecutionFactory.create( q, model );
      results = qe.execSelect();
      while ( results.hasNext() )
      {
        Genre g = new Genre();
        g.setName( results.next().toString() );
        game.gameGenres.add( g );
      }
      
      q       = QueryFactory.create( "SELECT ?genre WHERE { " + game.getGameURI() + " <http://www.gamewarp.org/tags#tgenre> ?genre.}" );
      qe      = QueryExecutionFactory.create( q, model );
      results = qe.execSelect();
      while ( results.hasNext() )
      {
        Genre g = new Genre();
        g.setName( results.next().toString() );
        game.theatricalGenres.add( g );
      }
      
      q       = QueryFactory.create( "SELECT ?attr WHERE { " + game.getGameURI() + " <http://www.gamewarp.org/tags#tags> ?attr.}" );
      qe      = QueryExecutionFactory.create( q, model );
      results = qe.execSelect();
      while ( results.hasNext() )
      {
        Attribute attr = new Attribute();
        attr.setName( results.next().toString() );
        game.attributes.add( attr );
      }

      gameList.set( i, game );
    }

    return gameList;
  }
}

// END OF FILE -----------------------------------------------------------------

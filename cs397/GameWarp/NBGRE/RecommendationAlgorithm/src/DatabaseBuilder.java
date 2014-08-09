import java.io.File;
import java.io.FileInputStream;

import com.hp.hpl.jena.rdf.model.Model;
import com.hp.hpl.jena.rdf.model.ModelFactory;
import com.hp.hpl.jena.rdf.model.ModelMaker;


public class DatabaseBuilder {

	final private static String DBNAME = "gamedb.rdf"; 
	final private static File   DBDIR  = new File( "db" );

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

	}
}

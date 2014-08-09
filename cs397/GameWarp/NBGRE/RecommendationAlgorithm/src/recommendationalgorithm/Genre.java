// BEGINNING OF FILE -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// @file Genre.java
// @desc A class to hold genre information
// @date 11 Dec 2010
// @auth Game Warp Algorithm Team
////////////////////////////////////////////////////////////////////////////////

package recommendationalgorithm;

////////////////////////////////////////////////////////////////////////////////
// @class Genre
// @desc Holds genre information
////////////////////////////////////////////////////////////////////////////////
public class Genre implements Comparable<Genre>
{
  private String genreName;   // The genre's identifier name
  private double genreScore;  // The genre's average numeric score
  private int    numScores;   // The number of times this genre has been used

  // basic constructor
  public Genre()
  {
  }

  // constructor that I'm using for test cases in UPI_InterfaceTest.java
  public Genre(String name, double score, int theNumScores)
  {
    genreName = name;
    genreScore = score;
    numScores = theNumScores;
  }

  //////////////////////////////////////////////////////////////////////////////
  // @func public int compareTo(genre rhs)
  // @desc The implementation of comparison for the genre class (for sorting)
  // @param Genre RHS - A genre to compare against
  //////////////////////////////////////////////////////////////////////////////
  public int compareTo( Genre RHS )
  {
	return ( genreName.equals( RHS.getName() ) ) ? ( 1 ) : ( 0 );
	//return Double.compare( genreScore, RHS.getScore() );
  }
  
  public void setName( String newName )
  {
    genreName = newName;
  }

  public String getName()
  {
    return genreName;
  }

  public void setScore( double newScore )
  {
    genreScore = newScore;
  }

  public double getScore()
  {
    return genreScore;
  }

  public void setNumScores( int newScore )
  {
    numScores = newScore;
  }

  public int getNumScores()
  {
    return numScores;
  }
}

// END OF FILE -----------------------------------------------------------------

// BEGINNING OF FILE -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// @file Attribute.java
// @desc A class to store game information gathered from the UPI
// @date 11 Dec 2010
// @auth Game Warp Algorithm Team
////////////////////////////////////////////////////////////////////////////////

package recommendationalgorithm;

////////////////////////////////////////////////////////////////////////////////
// @class Attribute
// @desc Storage for attribute information
////////////////////////////////////////////////////////////////////////////////
public class Attribute
{
  private double score;
  private int    numScores;
  private String name;

  // basic constructor
  public Attribute()
  {
  }

  // constructor that I'm using for test cases in UPI_InterfaceTest.java
  public Attribute(String theName, double theScore, int theNumScores)
  {
    name = theName;
    score = theScore;
    numScores = theNumScores;
  }

  public String getName()
  {
    return name;
  }

  public void setName(String name)
  {
    this.name = name;
  }

  public int getNumScores()
  {
    return numScores;
  }

  public void setNumScores(int numScores)
  {
    this.numScores = numScores;
  }

  public double getScore()
  {
    return score;
  }

  public void setScore(double score)
  {
    this.score = score;
  }

}

// END OF FILE -----------------------------------------------------------------

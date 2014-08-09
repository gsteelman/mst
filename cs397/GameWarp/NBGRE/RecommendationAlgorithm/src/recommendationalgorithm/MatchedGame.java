// BEGINNING OF FILE -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// @file MatchedGame.java
// @desc A class to hold a game and its relative (weighted) score
// @date 11 Dec 2010
// @auth Game Warp Algorithm Team
////////////////////////////////////////////////////////////////////////////////

package recommendationalgorithm;

////////////////////////////////////////////////////////////////////////////////
// @class MatchedGame
// @desc Holds a game and its relative weighted score by The Algorithm
////////////////////////////////////////////////////////////////////////////////
public class MatchedGame implements Comparable<MatchedGame>
{
  private Game   gameMatch; // The game that is weighted
  private double gameScore = -1.0; // The weighted score for the game

  //////////////////////////////////////////////////////////////////////////////
  // @func public int compareTo( MatchedGame RHS )
  // @desc The implementation of comparison for the MatchedGame class (for sorting)
  // @param MatchedGame RHS - A MatchedGame to compare against
  //////////////////////////////////////////////////////////////////////////////
  public int compareTo( MatchedGame RHS )
  {
    // TODO Possibly fix the return value on the string compareToIgnoreCase
    // because the string compareTo function returns a negative number if LHS comes
    // before RHS alphabetically, thus what we are doing should be giving us a
    // reverse alphabetical sort
    int rtnVal = Double.compare( gameScore, RHS.getScore() );
    return ( rtnVal != 0 ) ? ( rtnVal ) : ( gameMatch.getGameURI().compareToIgnoreCase( RHS.getGame().getGameURI() ) );
  }

  public void setGame( Game newGame )
  {
    gameMatch = newGame;
  }

  public Game getGame()
  {
    return gameMatch;
  }

  public void setScore( double newScore )
  {
    gameScore = newScore;
  }

  public double getScore()
  {
    return gameScore;
  }
}

// END OF FILE -----------------------------------------------------------------

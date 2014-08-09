///////////////////////////////////////////////////////////////////////////////
/// @file puzzleboard.h
/// @author Gary Steelman, CS153-B
/// @edited 1 May 08
/// @brief Puzzleboard class prototype file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn PuzzleBoard()
/// @brief Constructor for the PuzzleBoard class
/// @pre None.
/// @post Instantiates a new PuzzleBoard class
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn puzzleBox( unsigned int i, unsigned int j )
/// @brief Returns one box of the puzzle
/// @pre A PuzzleBoard class exists.
/// @post Returns one box of the puzzle
/// @return A QLineEdit, one of the boxes of the puzzle
///////////////////////////////////////////////////////////////////////////////

#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H
#include <QtGui>

class PuzzleBoard : public QWidget
{
  Q_OBJECT
  public:
    PuzzleBoard();
    QLineEdit * puzzleBox( unsigned int i, unsigned int j );
    
  private:
    QLineEdit *** m_puzzleBox;
};

#endif

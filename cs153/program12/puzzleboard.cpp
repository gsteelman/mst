///////////////////////////////////////////////////////////////////////////////
/// @file puzzleboard.cpp
/// @author Gary Steelman, CS153-B
/// @edited 23 Apr 2008
/// @brief PuzzleBoard class implementation file
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

#ifndef PUZZLEBOARD_CPP
#define PUZZLEBOARD_CPP

#include "puzzleboard.h"

PuzzleBoard::PuzzleBoard()
{
  m_puzzleBox = new QLineEdit**[9];
  for( unsigned int i = 0; i < 9; i++ )
  {
    m_puzzleBox[i] = new QLineEdit*[9];
    for( unsigned int j = 0; j < 9; j++ )
    {
      m_puzzleBox[i][j] = new QLineEdit();
      if
      (
        (i < 3 && j > 2 && j < 6) ||
        (i > 2 && i < 6 && j < 3) ||
        (i > 2 && i < 6 && j > 5) ||
        (i > 5 && j > 2 && j < 6)
      )
      {
        QPalette p = m_puzzleBox[i][j]->palette();
        p.setColor
        (
          QPalette::Active,
          static_cast<QPalette::ColorRole>(9),
          QColor( Qt::lightGray )
        );
        m_puzzleBox[i][j]->setPalette( p );
      }
      
      unsigned int box_size = 50;
      m_puzzleBox[i][j]->setMaximumHeight( box_size );
      m_puzzleBox[i][j]->setMinimumHeight( box_size );
      m_puzzleBox[i][j]->setMaximumWidth( box_size );
      m_puzzleBox[i][j]->setMinimumWidth( box_size );
      m_puzzleBox[i][j]->setMaxLength( 1 );
      m_puzzleBox[i][j]->setFont(QFont("courier",40,QFont::Bold));
      m_puzzleBox[i][j]->setAlignment( Qt::AlignCenter );
    }
  }
}

//This simply returns a particular puzzle square
QLineEdit * PuzzleBoard::puzzleBox( unsigned int i, unsigned int j )
{
  return m_puzzleBox[i][j];
}

#endif

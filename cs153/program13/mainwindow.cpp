///////////////////////////////////////////////////////////////////////////////
/// @file mainwindow.cpp
/// @author Gary Steelman, CS153-B
/// @edited 7 May 08
/// @brief Exception class function implementation file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn MainWindow()
/// @brief Constructor for the MainWindow class
/// @pre None.
/// @post Instantiates a new MainWindow class
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_file_new()
/// @brief Code to be executed when the user selects File->New from the menu
/// @pre A MainWindow object exists
/// @post Instantiates a different puzzle based on user difficulty settings
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_file_open()
/// @brief Code to be executed when the user selects File->Open from the menu
/// @pre A MainWindow object exists
/// @post Opens a saved puzzle
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_file_save()
/// @brief Code to be executed when the user selects File->Save from the menu
/// @pre A MainWindow object exists
/// @post Saves the user's progress on the current puzzle to a file
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_file_exit()
/// @brief Code to be executed when the user selects File->Exit from the menu
/// @pre A MainWindow object exists
/// @post Closes the MainWindow and ends the program
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_difficulty_novice()
/// @brief Code to be executed when the user selects Difficulty->Novice from the menu
/// @pre A MainWindow object exists
/// @post Changes the difficulty of the puzzle to novice 
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_difficulty_intermediate()
/// @brief Code to be executed when the user selects Difficulty->Intermediate from the menu
/// @pre A MainWindow object exists
/// @post Changes the difficulty of the puzzle to intermediate 
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_difficulty_expert()
/// @brief Code to be executed when the user selects Difficulty->Expert from the menu
/// @pre A MainWindow object exists
/// @post Changes the difficulty of the puzzle to expert
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_help_solve()
/// @brief Code to be executed when the user selects Help->Solve from the menu
/// @pre A MainWindow object exists
/// @post Solves the puzzle and displays the answer to the user
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn slot_help_about()
/// @brief Code to be executed when the user selects Help->About from the menu
/// @pre A MainWindow object exists
/// @post Displays the about for the solver
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn createActions()
/// @brief Connects the menu actions to their respective coded functions
/// @pre A MainWindow object exists
/// @post The menu has each option connected to its code
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn createMenus()
/// @brief Creates the menu system and its submenus
/// @pre A MainWindow object exists
/// @post Creates the menu system and its submenus
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn open( QString fileName )
/// @brief Opens a saved puzzle
/// @pre A MainWindow object exists
/// @post Opens a saved puzzle
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Solve (unsigned int boxValue, bool puzzleDefined, int rowPos, int colPos)
/// @brief Solves the sudoku puzzle
/// @pre An instantiated sudoku puzzle exists
/// @post Solves the sudoku puzzle
/// @param unsigned int boxValue is the 9x9 array of numbers for the sudoku
/// @param bool puzzleDefined is the 9x9 array of booleans with true in the 
///   locations that have pre defined puzzle numbers
/// @param int rowPos is the horizontal position in a row
/// @param int colPos is the vertical position in a column
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn relocateSpot(unsigned int boxValue[][9], int & rowPos, int & colPos, bool puzzleDefined[][9] )
/// @pre An instantiated sudoku puzzle exists
/// @post moves the location we're trying to insert to backward to a legal spot
/// @param int boxValue is the array of values for the sudoku puzzle
/// @param int rowPos is the current position horizontally in the row
/// @param int colPos is the current position vertically in the column
/// @param bool puzzleDefined is the array of pre-defined positions
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn moveForward( int & rowPos, int & colPos )
/// @pre An instantiated sudoku puzzle exists
/// @post moves rowPos and colPos forward to the first non-predefined spot
/// @param int rowPos is the current position horizontally in the row
/// @param int colPos is the current position vertically in the column
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn checkCol( unsigned int boxValue[][9], int rowPos, unsigned int numInsert )
/// @pre An instantiated sudoku puzzle exists
/// @post Checks the current column for the number we're trying to insert
/// @param int boxValue is the array of values for the sudoku puzzle
/// @param int rowPos is the current position horizontally in the row
/// @param unsigned int numInsert is the number we're trying to insert 
/// @return true if the insertion is legal, false otherwise
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn checkRow( unsigned int boxValue[][9], int colPos, unsigned int numInsert )
/// @pre An instantiated sudoku puzzle exists
/// @post Checks the current row for the number we're trying to insert
/// @param int boxValue is the array of values for the sudoku puzzle
/// @param int colPos is the current position horizontally in the column
/// @param unsigned int numInsert is the number we're trying to insert 
/// @return true if the insertion is legal, false otherwise
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn checkBox( unsigned int boxValue[][9], int rowPos, int colPos, unsigned int numInsert )
/// @pre An instantiated sudoku puzzle exists
/// @post Checks the current row for the number we're trying to insert
/// @param int boxValue is the array of values for the sudoku puzzle
/// @param int rowPos is the current position horizontally in the row
/// @param int colPos is the current position horizontally in the column
/// @param unsigned int numInsert is the number we're trying to insert 
/// @return true if the insertion is legal, false otherwise
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn print(unsigned int board[][9], bool puzzleDefined[][9])
/// @brief Prints out the puzzle to the command prompt
/// @pre A MainWindow object exists
/// @post Prints out the puzzle to the command prompt
/// @param unsigned int board is the array of numbers for the sudoku board
/// @param bool puzzleDefined is the array of pre-defined positions
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn checkFull( unsigned int boxValue[][9] )
/// @brief checks to see if the sudoku puzzle is full or not
/// @pre A MainWindow object exists
/// @post Returns true if the puzzle is full, false otherwise
/// @param unsigned int boxValue[][9] is the array of uints to check
/// @return true if the puzzle is full, false otherwise
///////////////////////////////////////////////////////////////////////////////

#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

#include "mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow()
{
  window = new QWidget;
  setCentralWidget( window );
  setWindowTitle( "Ç∑Ç«Ç≠ (Sudoku)" );
  setWindowIcon( QIcon( ":/icon.gif" ) );
  QGridLayout * layout = new QGridLayout;
  puzzleBoard = new PuzzleBoard();
  
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      layout->addWidget(puzzleBoard->puzzleBox(i,j),i,j,1,1);
    }
  }
  
  window->setLayout( layout );
  createActions();
  createMenus();
}

//This function creates all of the QAction objects
void MainWindow::createActions()
{
  //This creates a new QAction object and specifies the text to appear on it
  action_file_new = new QAction( tr( "&New" ), this);
  
  //This text appears as an extra description when a user hovers over the menu item
  action_file_new->setStatusTip( tr( "Create a new puzzle" ) );
  
  //The slot_file_new function is called whenever the triggered SIGNAL is thrown
  connect( action_file_new, SIGNAL( triggered() ), this, SLOT( slot_file_new() ) );
  
  action_file_open = new QAction( tr( "&Open" ), this );
  action_file_open->setStatusTip( tr( "Open a saved puzzle" ) );
  connect( action_file_open, SIGNAL( triggered() ), this, SLOT( slot_file_open() ) );
  
  action_file_save = new QAction( tr( "&Save" ), this );
  action_file_save->setStatusTip( tr( "Save your current puzzle" ) );
  connect( action_file_save, SIGNAL( triggered() ), this, SLOT( slot_file_save() ) );
  
  action_file_exit = new QAction( tr( "&Exit" ), this );
  action_file_exit->setStatusTip( tr( "Exit Sudoku" ) );
  connect( action_file_exit, SIGNAL( triggered() ), this, SLOT( slot_file_exit() ) );
  
  //Sets difficulty to novice
  action_difficulty_novice = new QAction( tr( "&Novice" ), this );
  action_difficulty_novice->setStatusTip( tr( "Play Sudoku at a novice difficulty" ) );
  action_difficulty_novice->setCheckable( true );
  action_difficulty_novice->setChecked( true );
  connect
  (
    action_difficulty_novice,
    SIGNAL(triggered()),
    this,
    SLOT(slot_difficulty_novice())
  );
  
  //Sets difficulty to itermediate
  action_difficulty_intermediate = new QAction( tr( "&Intermediate" ), this );
  action_difficulty_intermediate->setStatusTip
  (
    tr( "Play Sudoku at an intermediate difficulty" )
  );
  action_difficulty_intermediate->setCheckable( true );
  connect
  (
    action_difficulty_intermediate,
    SIGNAL( triggered() ),
    this,
    SLOT( slot_difficulty_intermediate() )
  );
  
  //Sets difficulty to expert
  action_difficulty_expert = new QAction( tr( "&Expert" ), this );
  action_difficulty_expert->setStatusTip( tr( "Play Sudoku at an expert difficulty" ) );
  action_difficulty_expert->setCheckable( true );
  connect
  (
    action_difficulty_expert,
    SIGNAL( triggered() ),
    this,
    SLOT( slot_difficulty_expert() )
  );
  
  action_help_solve = new QAction( tr( "&Solve" ), this );
  action_help_solve->setStatusTip( tr( "Show this puzzle's solution" ) );
  connect( action_help_solve, SIGNAL( triggered() ), this, SLOT( slot_help_solve() ) );
  
  action_help_about = new QAction( tr( "&About" ), this );
  action_help_about->setStatusTip( tr( "Show information about this Sudoku software" ) );
  connect( action_help_about, SIGNAL( triggered() ), this, SLOT( slot_help_about() ) );
}

//This function creates all of the QMenus and adds the QAction objects into them
void MainWindow::createMenus()
{
  menu_file = menuBar()->addMenu( tr( "&File" ) );
  menu_file->addAction( action_file_new );
  menu_file->addAction( action_file_open );
  menu_file->addAction( action_file_save );
  menu_file->addAction( action_file_exit );
  
  menu_difficulty = menuBar()->addMenu( tr( "&Difficulty" ) );
  menu_difficulty->addAction( action_difficulty_novice );
  menu_difficulty->addAction( action_difficulty_intermediate );
  menu_difficulty->addAction( action_difficulty_expert );
  
  menu_help = menuBar()->addMenu( tr( "&Help" ) );
  menu_help->addAction( action_help_solve );
  menu_help->addAction( action_help_about );
}

//Whenever a user selects to receive a new Sudoku puzzle, we want to
//randomly generate a puzzle based on the difficulty level they have
//selected. In this function, the code checks to see which difficulty
//the user has selected and it then loads one of the three available
//puzzles
void MainWindow::slot_file_new()
{
  //seeds the random number generator
  qsrand((QTime::currentTime()).msec());
  
  //selects a random number and adds it to the filename string
  QString fileName;
  fileName.setNum( qrand() % 3 );
  
  //based on the userÅfs selected difficulty it appends a suffix
  if( action_difficulty_novice->isChecked() )
  {
    fileName.append( ".novice" );
  }
  
  else if( action_difficulty_intermediate->isChecked() )
  {
    fileName.append( ".intermediate" );
  }
  
  else
  {
    fileName.append( ".expert" );
  }
  
  //we then try to load one of the puzzles onto our board
  open( fileName );
}
//Displays a pop-up window
void MainWindow::slot_help_about()
{
  QMessageBox::about
  (
    this,
    tr("About Ç∑Ç«Ç≠"),
    tr("This Ç∑Ç«Ç≠ (sudoku) puzzle solver was written by Gary Steelman")
  );
}

//This function reads in a Sudoku puzzle file and puts its contents
//onto the applications puzzle board
void MainWindow::open( QString fileName )
{
  QFile file;
  file.setFileName( fileName );
  if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
  {
    //error
    return;
  }
  
  //QTextStreams work just like the file streams you are familiar with
  QTextStream in( &file );
  QChar character;
  
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      in >> character;
      //checks to see if the character is a P. PÅfs are puzzle defined
      //and can not be changed by the user.
      if( character == 'P' )
      {
        //if it was a P, then we place that number on the board and
        //disable the users ability to write or edit that box.
        in >> character;
        puzzleBoard->puzzleBox( i, j )->setText( character );
        QPalette p = puzzleBoard->puzzleBox( i, j )->palette();
        p.setColor( QPalette::Text, QColor( Qt::darkGray ) );
        puzzleBoard->puzzleBox( i, j )->setPalette( p );
        puzzleBoard->puzzleBox( i, j )->setReadOnly( true );
      }
      else
      {
        //if it wasnÅft a P, then it is a user editable box
        in >> character;
        
        //if the next character is an X, then the square is blank
        if( character == 'X' )
        {
          puzzleBoard->puzzleBox( i, j )->clear();
        }
        
        //otherwise, place the users number into the square
        else
        {
          puzzleBoard->puzzleBox( i, j )->setText( character );
        }
        
      QPalette p = puzzleBoard->puzzleBox( i, j )->palette();
      p.setColor( QPalette::Text, QColor( Qt::black ) );
      puzzleBoard->puzzleBox( i, j )->setPalette( p );
      puzzleBoard->puzzleBox( i, j )->setReadOnly( false );
      }
    }
  }
}

//This function loads a saved file
void MainWindow::slot_file_open()
{
  //This is our previously defined open function
  open
  (
    //This opens up a dialog box that allows the user browse his or her
    //drives for .sudoku files. It then returns a string containing
    //the filename that the user has selected
    QFileDialog::getOpenFileName
    (
      this,
      tr("Open a saved Sudoku puzzle"),
      "",
      tr("Sudoku puzzles (*.sudoku)")
    )
  );
}

//When the user selects this the program exits
void MainWindow::slot_file_exit()
{
  close();
}

//Sets the selected difficulty level to novice
void MainWindow::slot_difficulty_novice()
{
  action_difficulty_novice->setChecked( true );
  action_difficulty_intermediate->setChecked( false );
  action_difficulty_expert->setChecked( false );
}

//Sets the selected difficulty level to intermediate
void MainWindow::slot_difficulty_intermediate()
{
  action_difficulty_novice->setChecked( false );
  action_difficulty_intermediate->setChecked( true );
  action_difficulty_expert->setChecked( false );
}

//Sets the selected difficulty level to expert
void MainWindow::slot_difficulty_expert()
{
  action_difficulty_novice->setChecked( false );
  action_difficulty_intermediate->setChecked( false );
  action_difficulty_expert->setChecked( true );
}

//Saves the puzzles current state to a file
void MainWindow::slot_file_save()
{
  //This opens up a dialog box that allows the user to browse his or
  //her drives for a suitable location and filename to save into.
  QString fileName =
  QFileDialog::getSaveFileName
  (
    this,
    tr("Save your Sudoku puzzle"),
    "",
    tr("Sudoku puzzles (*.sudoku)")
  );
  
  QFile file;
  file.setFileName( fileName );
  
  if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
  {
    // error
    return;
  }
  
  QTextStream out( &file );
  QChar character;
  //Once the file is opened and accessible, we begin writing out the
  //puzzleÅfs contents. Each square is read. If a square is puzzle-
  //defined then a P and then the number is written out. If the square
  //is user-defined then a U and then the number is written out. If
  //the user has left a square blank then a U and X are written out to
  // indicate that it is empty user-defined square.
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      if( puzzleBoard->puzzleBox( i, j )->isReadOnly() )
      {
        character = 'P';
        out << character;
        out << puzzleBoard->puzzleBox( i, j )->displayText();
      }
      
      else
      {
        character = 'U';
        out << character;
        
        if( puzzleBoard->puzzleBox( i, j )->displayText().size() < 1 )
        {
          character = 'X';
          out << character;
        }
        
        else
        {
          out << puzzleBoard->puzzleBox( i, j )->displayText();
        }
      }
    }
  }
}

//Eventually this function will solve the puzzle. For the moment, it
//only does two things. One, it reads the contents of the puzzle and
//stores all of the number values into the boxValue array. Two, it
//determines if the square is puzzle defined or user editable and
//stores that in the Boolean array. Your solver function will use
//these arrays to work its magic.
void MainWindow::slot_help_solve()
{
  bool puzzleDefined[9][9];
  unsigned int boxValue[9][9];
  
  // This takes everything out of the user interface
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      if( puzzleBoard->puzzleBox( i, j )->isReadOnly() )
      {
        puzzleDefined[i][j] = true;
        boxValue[i][j] =
        puzzleBoard->puzzleBox( i, j )->displayText().toUInt();
      }
      
      else
      {
        if( puzzleBoard->puzzleBox( i, j )->displayText().size() < 1 )
        {
          boxValue[i][j] = 0;
        }
        
        else
        {
          boxValue[i][j] =
          puzzleBoard->puzzleBox( i, j )->displayText().toUInt();
        }
      }
    }
  }
  
  ///////////////////////////////////////////////////////////////////////
  // The Sudoku puzzle function goes below this comment
  
  Solve( boxValue, puzzleDefined, 0, 0 );
  
  // The Sudoku puzzle function goes above this comment
  ///////////////////////////////////////////////////////////////////////
  
  // This puts everything back into the user interface
  for( unsigned int i = 0; i < 9; i++ )
  {
    for( unsigned int j = 0; j < 9; j++ )
    {
      QString text;
      text.setNum( boxValue[i][j] );
      puzzleBoard->puzzleBox( i, j )->setText( text );
    }
  }
}

//Solves the sudoku puzzle
void MainWindow::Solve ( unsigned int boxValue[][9], bool puzzleDefined[][9], int rowPos, int colPos )
{
  unsigned int numInsert;
  
  if ( checkEmpty( boxValue ) == true)
  {
    return;
  }
  
  if ( checkFull( boxValue ) == true)
  {
    return;
  }
  
  else
  {
    //Loop until we find a spot that isn't predefined
    while (puzzleDefined[colPos][rowPos] == true)
    {
      moveForward( rowPos, colPos, boxValue );
      
      if ( checkFull( boxValue ) == true)
      {
        return;
      }
    }
    
    numInsert = boxValue[colPos][rowPos];
    
    //Loop until we find the smallest number to fit into the current spot
    while ( 
         checkCol( boxValue, rowPos, colPos, numInsert ) == false
      || checkRow( boxValue, rowPos, colPos, numInsert ) == false
      || checkBox( boxValue, rowPos, colPos, numInsert ) == false
      || numInsert == 0
    )
    {
      numInsert+=1;
    }
    
    //If we went over the limit on the number to put into this spot
    if (numInsert > 9)
    {
      //need to drop back to a good spot and try again
      relocateSpot(boxValue, rowPos, colPos, puzzleDefined );
      
      if ( checkFull( boxValue ) == true )
      {
        return;
      }
      
      else if (puzzleDefined[colPos][rowPos] != true)
      {
        boxValue[colPos][rowPos] = boxValue[colPos][rowPos] + 1;
      }
      
      Solve( boxValue, puzzleDefined, rowPos, colPos );
    }
    
    else
    {
      if (puzzleDefined[colPos][rowPos] != true)
      {
        boxValue[colPos][rowPos] = numInsert;
      }
    }
    
    //Now that we've taken care of this iteration, move onto the next spot
    if ( checkFull( boxValue ) == true )
    {
      return;
    }
      
    do
    {
      moveForward( rowPos, colPos, boxValue );
      
      if ( checkFull( boxValue ) == true )
      {
        return;
      }
      
    } while (puzzleDefined[colPos][rowPos] == true);
    
    Solve( boxValue, puzzleDefined, rowPos, colPos );
  }
  
  return;
}

//relocates the rowPos and colPos to a spot that doesn't have a predefined value
void MainWindow::relocateSpot(unsigned int boxValue[][9], int & rowPos, int & colPos, bool puzzleDefined[][9] )
{
  do
  {
    //if (boxValue[colPos][rowPos] == 9 && puzzleDefined[colPos][rowPos] != true)
    if (puzzleDefined[colPos][rowPos] != true)
    {
      boxValue[colPos][rowPos] = 0;
    }
    
    if (rowPos == 0 && colPos != 0)
    {
      rowPos = 8;
      colPos-=1;
    }
    
    //This case shouldn't ever technically be reached, let's hope it doesn't get
    else if (rowPos == 0 && colPos == 0)
    {
      rowPos = 0;
      colPos = 0;
      
      return;
    }
    
    else
    {
      rowPos-=1;
    }
    
  } while (puzzleDefined[colPos][rowPos] == true || boxValue[colPos][rowPos] == 9);

  if ( checkFull( boxValue ) == true )
  {
    return;
  }
  
  return;
}

void MainWindow::moveForward( int & rowPos, int & colPos, unsigned int boxValue[][9] )
{  
  if ( checkFull( boxValue ) == true )
  {
    return;
  }
  
  //If we're all the way to the right, but not the bottom
  else if (rowPos == 8 && colPos != 8)
  {
    rowPos = 0;
    colPos+=1;
  }
  
  //If we're not all the way to the right, then just move a spot over
  else
  {
    rowPos+=1;
  }
  
  return;
}

bool MainWindow::checkCol( unsigned int boxValue[][9], int rowPos, int colPos, unsigned int numInsert )
{
  //Checks to see if the value can be inserted into the current spot
  //Loops through the column
  for (int i = 0; i < 9; i++)
  {
    //The number we're trying to insert is in the column, increment by 1 and try again
    if (boxValue[i][rowPos] == numInsert && i != colPos)
    {
      return false;
    }
  }
  
  return true;
}

bool MainWindow::checkRow( unsigned int boxValue[][9], int rowPos, int colPos, unsigned int numInsert )
{
  //Loops through the row
  for (int i = 0; i < 9; i++)
  {
    //The number we're trying to insert is in the row, increment by 1 and try again
    if (boxValue[colPos][i] == numInsert && i != rowPos)
    {
      return false;
    }
  }
  
  return true;
}

bool MainWindow::checkBox( unsigned int boxValue[][9], int rowPos, int colPos, unsigned int numInsert )
{  
  int boxNumHorStart = ((rowPos / 3) * 3);
  int boxNumVerStart = ((colPos / 3) * 3);
  
  //loops through the top left, top middle, top right, etc checking for
  //if the number is in the box that the number we're trying to insert
  //is in, if so, increment by 1 and try again
  for (int i = boxNumVerStart; i < boxNumVerStart + 3; i++)
  {
    for (int j = boxNumHorStart; j < boxNumHorStart + 3; j++)
    {
      if (boxValue[i][j] == numInsert && (i != colPos && j != rowPos))
      {
        return false;
      }
    }
  }
  
  return true;
}

//if the box is full, returns true, otherwise false
bool MainWindow::checkFull( unsigned int boxValue[][9] )
{
  for (int i = 0; i < 9; i++ )
  {
    for (int j = 0; j < 9; j++ )
    {
      if ( boxValue[i][j] == 0 )
      {
        return false;
      }
    }
  }
  
  return true;
}

bool MainWindow::checkEmpty( unsigned int boxValue[][9] )
{
  for (int i = 0; i < 9; i++ )
  {
    for (int j = 0; j < 9; j++ )
    {
      if ( boxValue[i][j] != 0 )
      {
        return false;
      }
    }
  }
  
  return true;
}

void MainWindow::print(unsigned int board[][9], bool puzzleDefined[][9])
{
  int tempCount = 0;
  int rowCount = 0;

  for (int i = 0; i < 9; i++) 
  {
    cout << "    " << i;
    tempCount++;
    
    if (tempCount % 3 == 0) 
    {
      cout << " ";
    }
  }

  tempCount = 0;
  cout << endl;
  
  for (int i = 0; i < 9; i++) 
  {
    cout << i << " ";
    
    for (int j = 0; j < 9; j++) 
    {
      if (tempCount == 3) 
      {
        cout << " ";
        tempCount = 0;
      }

    tempCount++;
    cout << "[";

    if (puzzleDefined[i][j] == true) 
    {
      cout << "*" << board[i][j] << "*";
    } 
    
    else 
    {
      cout << " " << board[i][j] << " ";
    }

  cout << "]";
  }

  tempCount = 0;
  rowCount++;

  if (rowCount % 3 == 0) 
  {
    cout << endl;
  }

  cout << endl;
  }
  
  return;
}
#endif

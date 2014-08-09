///////////////////////////////////////////////////////////////////////////////
/// @file mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "puzzleBoard.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT
  public:
    MainWindow();
    
  private slots:
    void slot_file_new();
    void slot_file_open();
    void slot_file_save();
    void slot_file_exit();
    void slot_difficulty_novice();
    void slot_difficulty_intermediate();
    void slot_difficulty_expert();
    void slot_help_solve();
    void slot_help_about();
    
  private:
    QWidget * window;
    PuzzleBoard * puzzleBoard;
    QMenu * menu_file;
    QMenu * menu_difficulty;
    QMenu * menu_help;
    QAction * action_file_new;
    QAction * action_file_open;
    QAction * action_file_save;
    QAction * action_file_exit;
    QAction * action_difficulty_novice;
    QAction * action_difficulty_intermediate;
    QAction * action_difficulty_expert;
    QAction * action_help_solve;
    QAction * action_help_about;
    void createActions();
    void createMenus();
    void open( QString fileName );
    
    void Solve ( unsigned int boxValue[][9], bool puzzleDefined[][9], int rowPos, int colPos);
    void relocateSpot(unsigned int boxValue[][9], int & rowPos, int & colPos, bool puzzleDefined[][9] );
    void moveForward( int & rowPos, int & colPos, unsigned int boxValue[][9]  );
    bool checkCol( unsigned int boxValue[][9], int rowPos, int colPos, unsigned int numInsert );
    bool checkRow( unsigned int boxValue[][9], int rowPos, int colPos, unsigned int numInsert );
    bool checkBox( unsigned int boxValue[][9], int rowPos, int colPos, unsigned int numInsert );
    bool checkFull( unsigned int boxValue[][9] );
    bool checkEmpty( unsigned int boxValue[][9] );
    void print(unsigned int boxValue[][9], bool puzzleDefined[][9]);
    
};

#endif

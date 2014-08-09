///////////////////////////////////////////////////////////////////////////////
/// @file mainwindow.h
/// @author Gary Steelman, CS153-B
/// @edited 23 Apr 2008
/// @brief Prototype file for the main window of the sudoku solver
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
};

#endif

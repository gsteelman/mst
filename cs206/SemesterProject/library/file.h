//////////////////////////////////////////////////////////////////////
/// @file file.h
/// @author Jeremy Davidson
/// @brief -- Simple file read/write interface
//////////////////////////////////////////////////////////////////////
/// @class File
/// @brief -- File read/write, including de/encryption
//////////////////////////////////////////////////////////////////////
/// @fn File()
/// @brief -- Loads nothing
//////////////////////////////////////////////////////////////////////
/// @fn File(string filename)
/// @brief -- Loads the file given by "filename"
//////////////////////////////////////////////////////////////////////
/// @fn ~File()
/// @brief -- Closes the file WITHOUT saving changes.
//////////////////////////////////////////////////////////////////////
/// @fn void open(string filename)
/// @brief -- Opens the file given by "filename"
/// @param string filename -- Name of file to open
/// @note -- With regards to newline characters, only '\n' characters
///          are parsed. If a text file is created in Windows, it
///          will use the expanded CRLF, which contains a '\n', and
///          will be parsed properly, but will also leave the remnants
///          of the CRLF behind in the strings.
///          To maximize flexibility and ensure a straight read ->
///          save operation does NOT modify the file in any way,
///          the class does NOT handle expanded newlines.
//////////////////////////////////////////////////////////////////////
/// @fn void reopen()
/// @brief -- Reopens the file using m_filename
//////////////////////////////////////////////////////////////////////
/// @fn void close(bool save_changes = false)
/// @brief -- Closes the file, saving changes if save_changes is true
/// @param bool save_changes -- Saves changes to m_filename
//////////////////////////////////////////////////////////////////////
/// @fn string & get_line(unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
//////////////////////////////////////////////////////////////////////
/// @fn string & operator[](unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
//////////////////////////////////////////////////////////////////////
/// @fn void insert_line(unsigned int line, string str, bool break_lines = true)
/// @brief -- Inserts str AT "line", shifting all the data back.
/// @param unsigned int line -- Position to insert line.
/// @param string str -- String to insert.
/// @param bool break_lines -- Option to parse input for '\n' characters
///                            and break into multiple lines.
///                            If true, this guarantees that if the data
///                            were exported and then re-imported, it would
///                            come back exactly as it left.
///                            If false, this makes no such guarantee.
//////////////////////////////////////////////////////////////////////
/// @fn void insert_lines(unsigned int line, vector<string> str, bool break_lines = true)
/// @brief -- Inserts str AT "line", shifting all the data back.
/// @param unsigned int line -- Position to insert line.
/// @param vector<string> str -- Strings to insert.
/// @param bool break_lines -- Option to parse input for '\n' characters
///                            and break into multiple lines.
///                            If true, this guarantees that if the data
///                            were exported and then re-imported, it would
///                            come back exactly as it left.
///                            If false, this makes no such guarantee.
//////////////////////////////////////////////////////////////////////
/// @fn void insert_lines(unsigned int line, deque<string> str, bool break_lines = true)
/// @brief -- Inserts str AT "line", shifting all the data back.
/// @param unsigned int line -- Position to insert line.
/// @param deque<string> str str -- Strings to insert.
/// @param bool break_lines -- Option to parse input for '\n' characters
///                            and break into multiple lines.
///                            If true, this guarantees that if the data
///                            were exported and then re-imported, it would
///                            come back exactly as it left.
///                            If false, this makes no such guarantee.
//////////////////////////////////////////////////////////////////////
/// @fn void erase_line(unsigned int line)
/// @brief -- Deletes line at "line"
/// @param unsigned int line -- Position to erase line.
//////////////////////////////////////////////////////////////////////
/// @fn void erase_lines(unsigned int line, unsigned int num)
/// @brief -- Deletes "num" lines starting at "line"
/// @param unsigned int line -- Position to erase from.
/// @param unsigned int num -- Number of lines to erase.
//////////////////////////////////////////////////////////////////////
/// @fn void set_data(string file_data)
/// @brief -- Set the data to the raw string "file_data"
/// @param string file_data -- The data to set
//////////////////////////////////////////////////////////////////////
/// @fn void set_data(deque<string> file_data)
/// @brief -- Set the data to the vector of lines "file_data"
/// @param deque<string> file_data -- The data to set
//////////////////////////////////////////////////////////////////////
/// @fn void set_data(vector<string> file_data)
/// @brief -- Set the data to the vector of lines "file_data"
/// @param vector<string> file_data -- The data to set
//////////////////////////////////////////////////////////////////////
/// @fn string get_raw_data()
/// @brief -- Returns a string containing the raw data in the file
///           '\n' characters will be maintained.
//////////////////////////////////////////////////////////////////////
/// @fn deque<string> get_data()
/// @brief -- Returns a deque containing the string-parsed data
///           in the file. '\n' characters will NOT be maintained.
//////////////////////////////////////////////////////////////////////
/// @fn vector<string> get_data_vector()
/// @brief -- Returns a vector containing the string-parsed data
///           in the file. '\n' characters will NOT be maintained.
//////////////////////////////////////////////////////////////////////
/// @fn void set_cipher(string cipher)
/// @brief -- Set the encryption cipher to "cipher"
/// @param string cipher -- The string to set for the cipher
//////////////////////////////////////////////////////////////////////
/// @fn string get_cipher()
/// @brief -- Retrieves the encryption cipher
//////////////////////////////////////////////////////////////////////
/// @fn string get_filename()
/// @brief -- Retrieves the filename
//////////////////////////////////////////////////////////////////////
/// @fn unsigned int num_lines()
/// @brief -- Retrieve the number of lines in the file
//////////////////////////////////////////////////////////////////////
/// @fn bool empty()
/// @brief -- Is the file empty?
//////////////////////////////////////////////////////////////////////
/// @fn void clear()
/// @brief -- Make the file empty.
//////////////////////////////////////////////////////////////////////
/// @fn bool error()
/// @brief -- Was there an error on read/write?
//////////////////////////////////////////////////////////////////////
/// @fn void load_file()
/// @brief -- Opens the file at "m_filename"
//////////////////////////////////////////////////////////////////////
/// @fn void save_file()
/// @brief -- Saves the file to "m_filename"
//////////////////////////////////////////////////////////////////////
/// @fn void save_file(string filename)
/// @brief -- Saves the file to "filename" and adjusts m_filename
//////////////////////////////////////////////////////////////////////
/// @fn string encrypt()
/// @brief -- Encrypts the file data using m_cipher
//////////////////////////////////////////////////////////////////////
/// @fn void decrypt(string str)
/// @brief -- Determines the encryption cipher and decrypts the file
///           setting m_cipher to the value used for decryption.
//////////////////////////////////////////////////////////////////////

#ifndef FILE_H
#define FILE_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <deque>
using std::deque;

class File {

  public:

    File();
    File(string filename);
    ~File();

    void            open(string filename);
    void            reopen();
    void            close(bool save_changes = false);

    void            save_file();
    void            save_file(string filename);

    string &        get_line(unsigned int line);
    string &        operator[](unsigned int line);

    void            insert_line(unsigned int line, string str, bool break_lines = true);
    void            insert_lines(unsigned int line, vector<string> str, bool break_lines = true);
    void            insert_lines(unsigned int line, deque<string> str, bool break_lines = true);
    void            erase_line(unsigned int line);
    void            erase_lines(unsigned int line, unsigned int num);

    void            set_data(string file_data);
    void            set_data(vector<string> file_data);
    void            set_data(deque<string> file_data);
    deque<string>   get_data();
    vector<string>  get_data_vector();
    string          get_raw_data(unsigned int start = 0, unsigned int end = -1);

    void            set_cipher(string cipher);
    string          get_cipher();

    string          get_filename();

    unsigned int    num_lines();
    bool            empty();
    void            clear();

    bool            error();

  protected:

    void    load_file();

    string  encrypt();
    void    decrypt(string str);

  private:

    // The file as it would be after performing a
    // series of getline() functions on an fstream
    deque<string>  m_file;

    // The filename
    string          m_filename;

    // The cipher key for encrytion/decryption
    // Calling it a cipher for readability.
    string          m_cipher;

    // Was there an error reading/writing to the file?
    bool            m_error;

};

#endif
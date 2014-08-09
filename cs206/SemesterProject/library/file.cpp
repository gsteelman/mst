//////////////////////////////////////////////////////////////////////
/// @file file.cpp
/// @author Jeremy Davidson
/// @brief -- Simple file read/write interface
//////////////////////////////////////////////////////////////////////

#include "file.h"

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>

#include "exception.h"
#include "strmanip.h"

//////////////////////////////////////////////////////////////////////
/// CONSTANTS
//////////////////////////////////////////////////////////////////////
// Signifies the beginning of the cipher
const string CIPHER_START_FLAG  = char_to_str(2) + char_to_str(2) + char_to_str(4) +
                                  char_to_str(6) + char_to_str(10) + char_to_str(16) + 
                                  char_to_str(26) + char_to_str(42) + char_to_str(68) +
                                  char_to_str(110) + char_to_str(178);

// Signifies the end of the cipher
const string CIPHER_END_FLAG    = char_to_str(238) + char_to_str(147) + char_to_str(91) +
                                  char_to_str(56) + char_to_str(35) + char_to_str(21) + 
                                  char_to_str(14) + char_to_str(7) + char_to_str(7);

// Completely arbitrary shift to adjust the cipher.
const unsigned int CIPHER_SHIFT = 110;

//////////////////////////////////////////////////////////////////////
/// @fn File()
/// @brief -- Loads nothing
//////////////////////////////////////////////////////////////////////
File::File() {

  // Nothing!

}

//////////////////////////////////////////////////////////////////////
/// @fn File(string filename)
/// @brief -- Loads the file given by "filename"
//////////////////////////////////////////////////////////////////////
File::File(string filename) : m_filename(filename) {

  load_file();

}

//////////////////////////////////////////////////////////////////////
/// @fn ~File()
/// @brief -- Closes the file WITHOUT saving changes.
//////////////////////////////////////////////////////////////////////
File::~File() {

  close();

}

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
void File::open(string filename) {

  m_filename = filename;

  load_file();

}

//////////////////////////////////////////////////////////////////////
/// @fn void reopen()
/// @brief -- Reopens the file using m_filename
//////////////////////////////////////////////////////////////////////
void File::reopen() {

  load_file();

}

//////////////////////////////////////////////////////////////////////
/// @fn void close(bool save_changes = false)
/// @brief -- Closes the file, saving changes if save_changes is true
/// @param bool save_changes -- Saves changes to m_filename
//////////////////////////////////////////////////////////////////////
void File::close(bool save_changes) {

  if (save_changes) {

    save_file();

  }

  // Done with the file, empty the name.
  m_filename = "";

  // Clear all the data in the file.
  clear();

}

//////////////////////////////////////////////////////////////////////
/// @fn string & get_line(unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
//////////////////////////////////////////////////////////////////////
string & File::get_line(unsigned int line) {

  if (line < m_file.size()) {

    return m_file[line];

  } else {

    throw Exception(1090, "Invalid line index. (class File, get_line())");

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn string & operator[](unsigned int line)
/// @brief -- Returns a string, BY REFERENCE, containing the line
///           of data at "line"
///           Throws if line is invalid.
/// @param unsigned int line -- Line to retrieve
//////////////////////////////////////////////////////////////////////
string & File::operator[](unsigned int line) {

  return get_line(line);

}

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
void File::insert_line(unsigned int line, string str, bool break_lines) {

  //m_file.insert(m_file.begin() + line, str);
  // Convert to a deque and send to the insert_lines function.
  insert_lines(line, deque<string>(1, str), break_lines);

}

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
void File::insert_lines(unsigned int line, vector<string> str, bool break_lines) {

  //m_file.insert(m_file.begin() + line, str.begin(), str.end());
  // Convert to a deque and send to the insert_lines function.
  insert_lines(line, deque<string>(str.begin(), str.end()), break_lines);

}

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
void File::insert_lines(unsigned int line, deque<string> str, bool break_lines) {

  // If we need to break lines up from the input, do it here
  // and keep it completely contained from the rest of the routine.
  if (break_lines) {

    deque<string> fixed_input;
    vector<string> lines;

    // Loop through all the lines passed.
    for (int x = 0; x < str.size(); x++) {

      // Find the lines...
      lines = str_find_lines(str[x]);

      // And put them in a new deque.
      fixed_input.insert(fixed_input.end(), lines.begin(), lines.end());

    }

    // Store the new deque.
    str = fixed_input;

  }
  
  m_file.insert(m_file.begin() + line, str.begin(), str.end());

}

//////////////////////////////////////////////////////////////////////
/// @fn void erase_line(unsigned int line)
/// @brief -- Deletes line at "line"
/// @param unsigned int line -- Position to erase line.
//////////////////////////////////////////////////////////////////////
void File::erase_line(unsigned int line) {

  // Make sure we're in range.
  if (line >= m_file.size()) {

    throw Exception(405, "Invalid line to erase. (class File, erase_line())");

  }

  m_file.erase(m_file.begin() + line);

}

//////////////////////////////////////////////////////////////////////
/// @fn void erase_lines(unsigned int line, unsigned int num)
/// @brief -- Deletes "num" lines starting at "line"
/// @param unsigned int line -- Position to erase from.
/// @param unsigned int num -- Number of lines to erase.
//////////////////////////////////////////////////////////////////////
void File::erase_lines(unsigned int line, unsigned int num) {

  // Make sure we're in range.
  if (line >= m_file.size()) {

    throw Exception(405, "Invalid line to erase. (class File, erase_lines())");

  }

  // Truncate number of lines to end of file if overflowed.
  if (line + num >= m_file.size()) {

    num = m_file.size() - line;

  }

  m_file.erase(m_file.begin() + line, m_file.begin() + line + num);

}

//////////////////////////////////////////////////////////////////////
/// @fn void set_data(string file_data)
/// @brief -- Set the data to the raw string "file_data"
/// @param string file_data -- The data to set
//////////////////////////////////////////////////////////////////////
void File::set_data(string file_data) {

  // Set data from the vector returned by str_find_lines
  set_data(str_find_lines(file_data));

}

//////////////////////////////////////////////////////////////////////
/// @fn void set_data(deque<string> file_data)
/// @brief -- Set the data to the vector of lines "file_data"
/// @param deque<string> file_data -- The data to set
//////////////////////////////////////////////////////////////////////
void File::set_data(deque<string> file_data) {

  m_file = file_data;

}

//////////////////////////////////////////////////////////////////////
/// @fn void set_data(vector<string> file_data)
/// @brief -- Set the data to the vector of lines "file_data"
/// @param vector<string> file_data -- The data to set
//////////////////////////////////////////////////////////////////////
void File::set_data(vector<string> file_data) {

  m_file.clear();
  
  // Vector to deque conversion.
  for (int x = 0; x < file_data.size(); x++) {

    m_file.push_back(file_data[x]);

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn string get_raw_data()
/// @brief -- Returns a string containing the raw data in the file
///           '\n' characters will be maintained.
//////////////////////////////////////////////////////////////////////
string File::get_raw_data(unsigned int start, unsigned int end) {

  // Stupidity check.
  if (start > end) {

    unsigned int temp = start;
    start = end;
    end = temp;

  }

  // File existence check
  if (m_file.empty()) {

    return "";

  }

  // Range checking.
  if (start >= m_file.size()) {

    start = m_file.size() - 1;

  }

  if (end >= m_file.size()) {

    end = m_file.size() - 1;

  }

  string raw_data;

  // Loop through the file vector.
  for (int x = start; x <= end; x++) {

    // Add each line to the string.
    raw_data += m_file[x];

    // If this is NOT the last line...
    if (x != m_file.size() - 1) {

      // Insert a newline character, which are the
      // ONLY characters parsed out by the line-finder.
      raw_data += char_to_str('\n');

    }

  }

  return raw_data;

}

//////////////////////////////////////////////////////////////////////
/// @fn deque<string> get_data()
/// @brief -- Returns a deque containing the string-parsed data
///           in the file. '\n' characters will NOT be maintained.
//////////////////////////////////////////////////////////////////////
deque<string> File::get_data() {

  return m_file;

}

//////////////////////////////////////////////////////////////////////
/// @fn vector<string> get_data_vector()
/// @brief -- Returns a vector containing the string-parsed data
///           in the file. '\n' characters will NOT be maintained.
//////////////////////////////////////////////////////////////////////
vector<string> File::get_data_vector() {

  vector<string> to_return;
  
  // Deque to vector conversion.
  for (int x = 0; x < m_file.size(); x++) {

    to_return.push_back(m_file[x]);

  }

  return to_return;

}

//////////////////////////////////////////////////////////////////////
/// @fn void set_cipher(string cipher)
/// @brief -- Set the encryption cipher to "cipher"
/// @param string cipher -- The string to set for the cipher
//////////////////////////////////////////////////////////////////////
void File::set_cipher(string cipher) {

  m_cipher = cipher;

}

//////////////////////////////////////////////////////////////////////
/// @fn string get_cipher()
/// @brief -- Retrieves the encryption cipher
//////////////////////////////////////////////////////////////////////
string File::get_cipher() {

  return m_cipher;

}

//////////////////////////////////////////////////////////////////////
/// @fn string get_filename()
/// @brief -- Retrieves the filename
//////////////////////////////////////////////////////////////////////
string File::get_filename() {

  return m_filename;

}

//////////////////////////////////////////////////////////////////////
/// @fn unsigned int num_lines()
/// @brief -- Retrieve the number of lines in the file
//////////////////////////////////////////////////////////////////////
unsigned int File::num_lines() {

  return m_file.size();

}

//////////////////////////////////////////////////////////////////////
/// @fn bool empty()
/// @brief -- Is the file empty?
//////////////////////////////////////////////////////////////////////
bool File::empty() {

  return m_file.empty();

}

//////////////////////////////////////////////////////////////////////
/// @fn void clear()
/// @brief -- Make the file empty.
//////////////////////////////////////////////////////////////////////
void File::clear() {

  m_file.clear();

}

//////////////////////////////////////////////////////////////////////
/// @fn bool error()
/// @brief -- Was there an error on read/write?
//////////////////////////////////////////////////////////////////////
bool File::error() {

  return m_error;

}

//////////////////////////////////////////////////////////////////////
/// @fn void load_file()
/// @brief -- Opens the file at "m_filename"
//////////////////////////////////////////////////////////////////////
void File::load_file() {

  // Clear our current data deque
  m_file.clear();

  // Stream for file input
  ifstream in_file(m_filename.c_str(), ifstream::binary);

  // Set the error flag.
  m_error = in_file.fail();

  // If we failed somehow...
  if (m_error) {

    // Escape.
    return;

  }

  // Storage for our raw data.
  string file_data;

  // Line data.
  string line;

  while (!in_file.eof()) {

    // Using getline because there isn't a suitable
    // get() equivalent for straight strings.
    getline(in_file, line);

    file_data += line;

    if (!in_file.eof()) {

      // If we didn't pass the eof by getting
      // that line, it means we devoured an '\n'
      // in the process and we need to restore it.
      file_data += char_to_str('\n');

    }

  };

  // Decrypt the data, if a cipher exists.
  decrypt(file_data);

}

//////////////////////////////////////////////////////////////////////
/// @fn void save_file()
/// @brief -- Saves the file to "m_filename"
//////////////////////////////////////////////////////////////////////
void File::save_file() {

  // Save!
  ofstream out_file(m_filename.c_str(), ofstream::binary);

  // Set the error flag.
  m_error = out_file.fail();

  // If we failed somehow...
  if (m_error) {

    // Escape.
    return;

  }

  // Run encrypt, which will encrypt the data in m_file if
  // a cipher is present, or will leave it alone if not.
  // Either way, we get a single string with all the data.
  string to_output = encrypt();

  // Write the data in the string to the file.
  out_file.write(to_output.data(), to_output.length());

  out_file.close();

}

//////////////////////////////////////////////////////////////////////
/// @fn void save_file(string filename)
/// @brief -- Saves the file to "filename" and adjusts m_filename
//////////////////////////////////////////////////////////////////////
void File::save_file(string filename) {

  // Change the filename...
  m_filename = filename;

  // Then save. :)
  save_file();

}

//////////////////////////////////////////////////////////////////////
/// @fn string encrypt()
/// @brief -- Encrypts the file data using m_cipher
//////////////////////////////////////////////////////////////////////
string File::encrypt() {

  // Grab the straight data and store it in a single string.
  string file_data = get_raw_data();
  
  // If we have an encryption cipher...
  if (m_cipher != "") {

    // Encrypt the data.
    file_data = str_vigenere(file_data, m_cipher);

    // Append the cipher flag to the end of the file.
    file_data += CIPHER_START_FLAG;

    // Caesar-shift the cipher for a very slight layer of
    // extra protection.
    file_data += str_caesar(m_cipher, CIPHER_SHIFT);

    // Append the end flag.
    file_data += CIPHER_END_FLAG;

  }

  return file_data;

}

//////////////////////////////////////////////////////////////////////
/// @fn void decrypt(string str)
/// @brief -- Determines the encryption cipher and decrypts the file
///           setting m_cipher to the value used for decryption.
//////////////////////////////////////////////////////////////////////
void File::decrypt(string str) {

  // Search for start/end flags.
  // Set ignore_following to zero because we don't want to
  // ignore ANY occurrences of the flag strings.
  string cipher = str_find_range(str, CIPHER_START_FLAG, CIPHER_END_FLAG, false, true, false, 0);

  // If we found a cipher...
  if (cipher != "") {

    // Remove it from the string.
    str.erase(str.find(cipher), cipher.length());

    // Remove the cipher flags from the cipher.
    cipher = str_left (cipher, cipher.length() - CIPHER_END_FLAG.length());
    cipher = str_right(cipher, cipher.length() - CIPHER_START_FLAG.length());

    // Cipher is Caesar-shifted by CIPHER_SHIFT after encrypting,
    // so we de-shift (third param is encrypt/decrypt: true/false).
    cipher = str_caesar(cipher, CIPHER_SHIFT, false);

    // Actual data is Vigenère-ciphered by the cipher key,
    // so we decipher it.
    str = str_vigenere(str, cipher, false);

  }

  // Split into lines and store in the vector.
  set_data(str_find_lines(str));

  // Store the cipher for later encryption, if applicable.
  m_cipher = cipher;

}

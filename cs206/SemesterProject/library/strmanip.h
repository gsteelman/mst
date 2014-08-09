//////////////////////////////////////////////////////////////////////
/// @file strmanip.h
/// @author Jeremy Davidson
/// @brief -- A set of string manipulation functions
///           Many of these functions are reproductions of functions
///           available through Visual Basic which make string
///           manipulation MUCH easier.
//////////////////////////////////////////////////////////////////////
/// @fn string str_tolower(string str)
/// @brief -- Converts str to lowercase
/// @param string str -- The string to convert to lowercase
//////////////////////////////////////////////////////////////////////
/// @fn string str_toupper(string str)
/// @brief -- Converts str to uppercase
/// @param string str -- The string to convert to uppercase
//////////////////////////////////////////////////////////////////////
/// @fn string str_left(string str, int length)
/// @brief -- Returns the left portion of the string of size length
///           Returns the whole string if length > str.length()
/// @param string str -- The string to examine
/// @param int length -- The length of the string to return
//////////////////////////////////////////////////////////////////////
/// @fn string str_right(string str, int length)
/// @brief -- Returns the right portion of the string of size length
///           Returns the whole string if length > str.length()
/// @param string str -- The string to examine
/// @param int length -- The length of the string to return
//////////////////////////////////////////////////////////////////////
/// @fn string str_mid(string str, int start, int length)
/// @brief -- Returns the middle portion of the string starting at
///           start and reaching to length.
///           Returns the whole string from "start" to the end if
///           length exceeds that which is available.
/// @param string str -- The string to examine
/// @param int length -- The length of the string to return
//////////////////////////////////////////////////////////////////////
/// @fn string str_strip(string str, string to_strip, bool leading, bool inner, bool trailing)
/// @brief -- Returns the string with all instances of to_strip
///           removed, according to the parameters.
/// @param string str -- The string to examine
/// @param string to_strip -- The string to find and remove
/// @param bool leading -- Whether to remove instances of to_strip found
///                        at the beginning of the string, before other
///                        characters.
/// @param bool inner -- Whether to remove instances of to_strip found
///                      between other characters.
/// @param bool trailing -- Whether to remove instances of to_strip found
///                         at the end of the string.
//////////////////////////////////////////////////////////////////////
/// @fn string str_replace_all(string str, string to_replace, string replace_with, char ignore_following = '\\')
/// @brief -- Returns the string with all instances of to_replace replaced
///           by replace_with, except immediately following ignore_following
/// @param string str -- The string to examine
/// @param string to_replace -- The string to find and replace
/// @param string replace_with -- The string to replace to_replace with
/// @param bool inner -- Whether to remove instances of to_strip found
///                      between other characters.
/// @param char ignore_following -- If to_replace is found after this character,
///                                 it will be ignored in the replacing.
//////////////////////////////////////////////////////////////////////
/// @fn int str_to_int(string str)
/// @brief -- Wraps around the built-in ASCII-to-int atoi() function
///           and takes strings directly.
/// @param string str -- The string to convert
//////////////////////////////////////////////////////////////////////
/// @fn double str_to_doub(string str)
/// @brief -- Wraps around the built-in ASCII-to-int strtod() function
///           and takes strings directly.
/// @param string str -- The string to convert
//////////////////////////////////////////////////////////////////////
/// @fn string int_to_str(int num, unsigned int precision = 1)
/// @brief -- Converts an integer to a string.
/// @param int num -- The number to convert
/// @param unsigned int precision -- The minimum number of digits.
/// @note -- Zeroes will be added BEFORE the integer, if needed
///          to satisfy "precision".
//////////////////////////////////////////////////////////////////////
/// @fn string doub_to_str(double num, unsigned int precision = 1)
/// @brief -- Converts a double to a string.
/// @param int num -- The number to convert
/// @param unsigned int precision -- The minimum number of digits.
/// @note -- Zeroes will be added AFTER the decimal point, if needed
///          to satisfy "precision".
//////////////////////////////////////////////////////////////////////
/// @fn double hex_to_dec(string hex)
/// @brief -- Converts a string with hexadecimal numbers into its
///           equivalent decimal value.
/// @param string hex -- The number to convert
//////////////////////////////////////////////////////////////////////
/// @fn string char_to_str(char chr)
/// @brief -- Returns a string containing chr.
/// @param char chr -- The char to convert
//////////////////////////////////////////////////////////////////////
/// @fn string str_find_range(string str, string start, string end, bool nested, bool inclusive)
/// @brief -- Returns the string contained between "start" and "end"
/// @param string str -- The string to examine
/// @param string start -- The string defining the start of the range
/// @param string end -- The string defining the end of the range
/// @param bool nested -- Take into account layers of start/end ranges
///                       For example, nested parentheses "(hello (he said))"
///                       would return "(hello (he said)" when nested = false
///                       and "(hello (he said))" when nested = true
/// @param bool inclusive -- If true, return the string including the
///                          start/end values. For example, "(hello)"
///                          would return "hello" when inclusive = false
///                          and "(hello)" when inclusive = true
/// @param bool ignore_quotes -- If true, this will ignore start/end values
///                              found between sets of quotes. For example,
///                              with parentheses again, " ("Hey, :)") " would
///                              return " ("Hey, :) " with ignore = false and
///                              " ("Hey, :)") " with ignore = true.
/// @param char ignore_following -- If *either* start, *or* end are found
///                                 directly after this character, they will
///                                 be ignored in the search.
/// @return -- Returns the string if found, or a blank string if
///            the string wasn't found.
//////////////////////////////////////////////////////////////////////
/// @fn vector<string> str_find_lines(string str, string delimiters)
/// @brief -- Returns a vector of strings from str by breaking
///           lines at any of delimiters
/// @param string str -- The string to search
/// @param string delimiters -- A string of delimiting characters.
//////////////////////////////////////////////////////////////////////
/// @fn vector<int> str_find_all(string str, string to_find)
/// @brief -- Returns the positions of all instances (non-overlapping)
///           of to_find within str
/// @param string str -- The string to search
/// @param string to_find -- The string to look for
//////////////////////////////////////////////////////////////////////
/// @fn string str_caesar(string str, int shift, bool encrypt = true)
/// @brief -- Encrypts or decrypts a string using a Caesar cipher 
/// @param string str -- The string to en/decrypt
/// @param int shift -- The shift value for the Caesar cipher
/// @param bool encrypt -- True to ENcrypt; false to DEcrypt
//////////////////////////////////////////////////////////////////////
/// @fn string str_vigenere(string str, string key, bool encrypt = true)
/// @brief -- Encrypts or decrypts a string using a Vigenère cipher 
/// @param string str -- The string to en/decrypt
/// @param string key -- The key for the Vigenère cipher
/// @param bool encrypt -- True to ENcrypt; false to DEcrypt
//////////////////////////////////////////////////////////////////////

#ifndef STRMANIP_H
#define STRMANIP_H

#include <string>
using std::string;

#include <vector>
using std::vector;

string str_tolower(string str);
string str_toupper(string str);

string str_left(string str, unsigned int length);
string str_right(string str, unsigned int length);
string str_mid(string str, unsigned int start, unsigned int length);

string str_strip(string str, string to_strip, bool leading, bool inner, bool trailing);
// Overloaded to accept a character
string str_strip(string str, char to_strip, bool leading, bool inner, bool trailing);

string str_replace_all(string str, string to_replace, string replace_with, char ignore_following = '\\');
// A bunch of overloads. :)
string str_replace_all(string str, char to_replace, string replace_with, char ignore_following = '\\');
string str_replace_all(string str, string to_replace, char replace_with, char ignore_following = '\\');
string str_replace_all(string str, char to_replace, char replace_with, char ignore_following = '\\');

int    str_to_int(string str);
double str_to_doub(string str);
string int_to_str(int num, unsigned int precision = 1);
string doub_to_str(double num, unsigned int precision = 1);

long int hex_to_dec(string hex);

string char_to_str(char chr);

string str_find_range(string str,
                      string start,
                      string end,
                      bool nested = false,
                      bool inclusive = true,
                      bool ignore_quotes = false,
                      char ignore_following = '\\');
// Overloads allowing the function to accept characters.
string str_find_range(string str, char start, string end, bool nested = false,
                      bool inclusive = true, bool ignore_quotes = false, char ignore_following = '\\');
string str_find_range(string str, string start, char end, bool nested = false,
                      bool inclusive = true, bool ignore_quotes = false, char ignore_following = '\\');
string str_find_range(string str, char start, char end, bool nested = false,
                      bool inclusive = true, bool ignore_quotes = false, char ignore_following = '\\');

vector<string> str_find_lines(string str, string delimiters = char_to_str('\n'), bool keep_delim = false);

vector<int> str_find_all(string str, string to_find);

string str_caesar(string str, int shift, bool encrypt = true);
string str_vigenere(string str, string key, bool encrypt = true);

#endif
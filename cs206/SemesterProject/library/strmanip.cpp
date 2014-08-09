//////////////////////////////////////////////////////////////////////
/// @file strmanip.cpp
/// @author Jeremy Davidson
/// @brief -- A set of string manipulation functions
///           Many of these functions are reproductions of functions
///           available through Visual Basic which make string
///           manipulation MUCH easier.
//////////////////////////////////////////////////////////////////////

#include "strmanip.h"

#include "../library/library.h"

#include <vector>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <algorithm>
using namespace std;

//////////////////////////////////////////////////////////////////////
/// @fn string str_tolower(string str)
/// @brief -- Converts str to lowercase
/// @param string str -- The string to convert to lowercase
//////////////////////////////////////////////////////////////////////
string str_tolower(string str) {

  // Transform the passed-in string using the tolower function
  transform(str.begin(), str.end(), str.begin(), tolower);

  // We return the string so the user doesn't have to deal with
  // us screwing up the original string.
  return str;

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_toupper(string str)
/// @brief -- Converts str to uppercase
/// @param string str -- The string to convert to uppercase
//////////////////////////////////////////////////////////////////////
string str_toupper(string str) {

  // Transform the passed-in string using the tolower function
  transform(str.begin(), str.end(), str.begin(), toupper);

  // We return the string so the user doesn't have to deal with
  // us screwing up the original string.
  return str;

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_left(string str, int length)
/// @brief -- Returns the left portion of the string of size length
///           Returns the whole string if length > str.length()
/// @param string str -- The string to examine
/// @param int length -- The length of the string to return
//////////////////////////////////////////////////////////////////////
string str_left(string str, unsigned int length) {

  // This one's the easiest of all.
  return str.substr(0, length);

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_right(string str, int length)
/// @brief -- Returns the right portion of the string of size length
///           Returns the whole string if length > str.length()
/// @param string str -- The string to examine
/// @param int length -- The length of the string to return
//////////////////////////////////////////////////////////////////////
string str_right(string str, unsigned int length) {

  // Now things get complicated. Have to make sure
  // we stay within range of the string.
  // Substr doesn't account for a negative start.
  if (length >= str.length()) {

    return str;

  }

  // And now we can return the right side of the string.
  return str.substr(str.length() - length, length);

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_mid(string str, int start, int length)
/// @brief -- Returns the middle portion of the string starting at
///           start and reaching to length.
///           Returns the whole string from "start" to the end if
///           length exceeds that which is available.
/// @param string str -- The string to examine
/// @param int length -- The length of the string to return
//////////////////////////////////////////////////////////////////////
string str_mid(string str, unsigned int start, unsigned int length) {

  // If we're trying to start AFTER the string ends,
  // just return nothing. Substr will take care of
  // everything else.
  if (start >= str.length()) {

    return "";

  }

  return str.substr(start, length);

}

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
string str_strip(string str, string to_strip, bool leading, bool inner, bool trailing) {

  // For sanity's sake...
  if (str.find(to_strip) == string::npos ||
      (!leading && !inner && !trailing)) {

    // Don't bother if it's not there. :)
    return str;

  }

  // Now... Check leading/trailing
  if (leading) {

    // While the first characters in the string match
    // what we're stripping...
    while (str_left(str, to_strip.length()) == to_strip) {

      // Throw them away.
      str = str_right(str, str.length() - to_strip.length());

    };

  } /* if (leading) */

  if (trailing) {

    // While the last characters in the string match
    // what we're stripping...
    while (str_right(str, to_strip.length()) == to_strip) {

      // Throw them away.
      str = str_left(str, str.length() - to_strip.length());

    };

  } /* if (trailing) */

  // Work from the inside.
  if (inner) {

    // Get the edges.
    unsigned int left = 0;
    unsigned int right = str.length();

    // Loop through the string and find the first bit that
    // doesn't match what we're stripping.
    while (str_mid(str, left, to_strip.length()) == to_strip) {

      left += to_strip.length();

    };

    // Loop through and find the last that doesn't match.
    while (str_mid(str, right - to_strip.length(), to_strip.length()) == to_strip) {

      right -= to_strip.length();

    };

    bool done = false;

    while (!done) {

      unsigned int pos = str.find(to_strip, left);

      if (pos == string::npos || pos > right) {

        done = true;

      } else {

        str.erase(pos, to_strip.length());

        // Since we just removed a chunk of the string,
        // we have to adjust the right bound.
        right -= to_strip.length();

      } /* if (pos == string::npos) */

    }; /* while (!done) */

  } /* if (inner) */

  return str;

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_strip()
/// @brief -- Overload of the all-string version
//////////////////////////////////////////////////////////////////////
string str_strip(string str, char to_strip, bool leading, bool inner, bool trailing) {

  return str_strip(str, char_to_str(to_strip), leading, inner, trailing);

}

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
string str_replace_all(string str, string to_replace, string replace_with, char ignore_following) {

  // Stores the position of to_replace within the string.
  int pos = 0;

  // Replace all to_replace with replace_with
  while (pos != string::npos) {

    // Find the em dash candidates within the string
    pos = str.find(to_replace, pos);

    // If we have a match... and it doesn't have
    // ignore_following immediately before it...
    if (pos != string::npos &&
       (pos > 0 && str[pos - 1] != ignore_following)) {

      // Replace it!
      str.replace(pos, to_replace.length(), replace_with);

      // Increment the current position by how many extra
      // characters were added in the replace, plus one so
      // we don't get any one-char infinite loops.
      pos += replace_with.length() - to_replace.length() + 1;

    }

  };

  return str;

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_replace_all()
/// @brief -- Overload of the all-string version
//////////////////////////////////////////////////////////////////////
string str_replace_all(string str, char to_replace, string replace_with, char ignore_following) {

  return str_replace_all(str, char_to_str(to_replace), replace_with, ignore_following);

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_replace_all()
/// @brief -- Overload of the all-string version
//////////////////////////////////////////////////////////////////////
string str_replace_all(string str, string to_replace, char replace_with, char ignore_following) {

  return str_replace_all(str, to_replace, char_to_str(replace_with), ignore_following);

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_replace_all()
/// @brief -- Overload of the all-string version
//////////////////////////////////////////////////////////////////////
string str_replace_all(string str, char to_replace, char replace_with, char ignore_following) {

  return str_replace_all(str, char_to_str(to_replace), char_to_str(replace_with), ignore_following);

}

//////////////////////////////////////////////////////////////////////
/// @fn int str_to_int(string str)
/// @brief -- Wraps around the built-in ASCII-to-int atoi() function
///           and takes strings directly.
/// @param string str -- The string to convert
//////////////////////////////////////////////////////////////////////
int str_to_int(string str) {

  return atoi(str.c_str());

}

//////////////////////////////////////////////////////////////////////
/// @fn double str_to_doub(string str)
/// @brief -- Wraps around the built-in ASCII-to-int strtod() function
///           and takes strings directly.
/// @param string str -- The string to convert
//////////////////////////////////////////////////////////////////////
double str_to_doub(string str) {

  return strtod(str.c_str(), NULL);

}

//////////////////////////////////////////////////////////////////////
/// @fn string int_to_str(int num, unsigned int precision = 1)
/// @brief -- Converts an integer to a string.
/// @param int num -- The number to convert
/// @param unsigned int precision -- The minimum number of digits.
/// @note -- Zeroes will be added BEFORE the integer, if needed
///          to satisfy "precision".
//////////////////////////////////////////////////////////////////////
string int_to_str(int num, unsigned int precision) {

  // Integers are never 255 digits... =P
  char * conversion = new char[255];

  sprintf(conversion, "%.*d", precision, num);

  string str(conversion);

  delete [] conversion;

  return str;

}

//////////////////////////////////////////////////////////////////////
/// @fn string doub_to_str(double num, unsigned int precision = 1)
/// @brief -- Converts a double to a string.
/// @param int num -- The number to convert
/// @param unsigned int precision -- The minimum number of digits.
/// @note -- Zeroes will be added AFTER the decimal point, if needed
///          to satisfy "precision".
//////////////////////////////////////////////////////////////////////
string doub_to_str(double num, unsigned int precision) {

  // Numbers are never 255 digits... =P
  char * conversion = new char[255];

  sprintf(conversion, "%.*f", precision, num);

  string str(conversion);

  delete [] conversion;

  return str;

}

//////////////////////////////////////////////////////////////////////
/// @fn double hex_to_dec(string hex)
/// @brief -- Converts a string with hexadecimal numbers into its
///           equivalent decimal value.
/// @param string hex -- The number to convert
//////////////////////////////////////////////////////////////////////
long int hex_to_dec(string hex) {

  // Yay for built-in functions. :)
  return strtol(hex.c_str(), NULL, 16);

}

//////////////////////////////////////////////////////////////////////
/// @fn string char_to_str(char chr)
/// @brief -- Returns a string containing chr.
/// @param char chr -- The char to convert
//////////////////////////////////////////////////////////////////////
string char_to_str(char chr) {

  // Yes, it's silly. =P But it saves me a lot of annoying
  // re-declaration hassle with my overloads.
  string str(1, chr);

  return str;

}

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
///                               * If ignore_following == 0, no ignoring will
///                                 be performed at all.
/// @return -- Returns the string if found, or a blank string if
///            the string wasn't found.
//////////////////////////////////////////////////////////////////////
string str_find_range(string str, string start, string end, bool nested,
                  bool inclusive, bool ignore_quotes, char ignore_following) {
  
  // For the purposes of this routine, we will assume
  // inclusive = true and take that into account
  // at the end when we return the string.

  unsigned int start_pos = 0;
  unsigned int end_pos = 1;

  vector<string>  removed_quotes;
  vector<int>     removed_pos;
  bool quotes_removed = false;

  // Make something almost impossible for someone to be searching
  // for, therefore unlikely to interfere in the search process.
  char ignore_ch[10] = {21, 22, 24, 26, 17, 18, 19, 20, 21, 22};
  string ignore(ignore_ch);

  if (ignore_quotes) {

    // While there are still quote-ranges within the string
    while (!quotes_removed) {

      // Find them, not-nested, but inclusive. Obviously, we don't
      // need to infinitely loop this, so we set ignore_quotes
      // to false in this instance.
      string temp_quote = str_find_range(str, "\"", "\"", false, true, false);

      // If it returns "", we didn't find any more quotes, so
      // we're done.
      if (temp_quote == "") {

        quotes_removed = true;

      } else {

        unsigned int pos = str.find(temp_quote);

        // Make sure we didn't break anything...
        if (pos != string::npos) {

          // Otherwise, add the quote to the removed_quotes vector.
          removed_quotes.push_back(temp_quote);

          // And store WHERE we put the removal.
          removed_pos.push_back(pos);

          str.replace(pos, temp_quote.length(), ignore);

        } else {

          throw Exception(15, "We somehow broke our own function... Apparently, searching doesn't work. (strmanip.cpp, str_find_range())");

        } /* if (pos != string::npos) */

      } /* if (temp_quote == "") */

    }; /* while (!quotes_removed) */

  } /* if (ignore_quotes) */

  // Store the original (quote-removed, but not stripped)
  // string for use later. :)
  string original = str;

  bool ignore_char_found = true;

  while (ignore_char_found) {

    // Find the first instance of start
    start_pos = str.find(start, start_pos);

    if (end_pos <= start_pos) {

      end_pos = start_pos + 1;

    }

    // It has to be after the start pos, you know.
    end_pos = str.find(end, end_pos);

    // See that there IS a previous char and test to see if it
    // matches the ignore char.
    if (start_pos == string::npos || end_pos == string::npos) {

      ignore_char_found = false;

    } else if (ignore_following != 0 && // If ignore_following is zero, don't ignore at all.
               start_pos > 0 && str[start_pos - 1] == ignore_following) {

      start_pos++;

    } else if (ignore_following != 0 &&
               end_pos > 0 && str[end_pos - 1] == ignore_following) {

      end_pos++;

    } else if (start_pos > end_pos) {
      
      unsigned int temp = start_pos;
      start_pos = end_pos;
      end_pos = temp;

    } else {

      ignore_char_found = false;

    }

  };

  // Make sure we actually HAVE an instance of each start and end.
  if (start_pos == string::npos || end_pos == string::npos || start_pos == end_pos) {

    return "";

  }

  if (nested) {

    // Nested is more complicated.
    // We have to keep track of how many starts
    // and ends we come across.

    // We initialize start_count to one, because we
    // have to count them as we come across them in the string.
    // If we find another start before an end, we have to then
    // find TWO ends in order to really be done.
    unsigned int start_count = 1;
    unsigned int end_count = 0;

    // While we're checking, we check for both starts and ends
    // and if we run out of starts or ends, 
    unsigned int check_pos = start_pos + 1;

    // While we have more starts than ends...
    // and we haven't run past the end of the string.
    while (start_count > end_count && check_pos < str.length()) {

      unsigned int temp_start = str.find(start, check_pos);;
      unsigned int temp_end = str.find(end, check_pos);;

      // If we're all out of both starts AND ends...
      if (temp_start == string::npos && temp_end == string::npos) {

        // Since we're all the way here, and we didn't break out
        // for start_count == end_count...
        check_pos = str.length();

        // AND we store the break condition, because it's broken.
        end_pos = string::npos;

      } else if (temp_start < temp_end) {

        // Only increment if the character previous isn't our
        // ignore condition.
        if (temp_start > 0 && str[temp_start - 1] != ignore_following) {

          // If the start came first... increment it.
          start_count++;

        }

        // And set the next check to just after
        // the place we just found.
        check_pos = temp_start + 1;

      /* else if (temp_start < temp_end) */
      } else {

        // Same as above.
        if (temp_end > 0 && str[temp_end - 1] != ignore_following) {

          // Otherwise, if the end came first, increment its count.
          end_count++;

        }

        // Set the next check pos to where IT was.
        check_pos = temp_end + 1;

        // And, since we're interested in the ending position...
        // store that.
        end_pos = temp_end;

      } /* temp_start vs temp_end */

    }; /* while (start_count > end_count && check_pos < str.length()) */

  } /* if (nested) */

  // Make sure we actually HAVE an instance of each start and end.
  if (start_pos == string::npos || end_pos == string::npos) {

    return "";

  } else {

    // If we HAVE something to work with, strip the
    // outsides of the string.
    str = str_mid(str, start_pos, end_pos - start_pos + end.length());

  }

  // If we chose to ignore quotes, AND we
  // have some to replace...
  if (ignore_quotes && !removed_quotes.empty()) {

    bool quotes_replaced = false;

    while (!quotes_replaced) {

      // Find the first instance of an "ignore" in the stripped string.
      int stripped_pos = str.find(ignore);

      // If there was one...
      if (stripped_pos != string::npos) {

        // Find its match in the original, unstripped string
        // by finding everything from the beginning of the stripped string
        // to the end of the first ignore. We include the ignore string
        // to guarantee what we're searching for is actually something
        // that we ignored. 
        string left = str_left(str, stripped_pos + ignore.length());

        int original_pos = original.find(left);

        if (original_pos == string::npos) {

          throw Exception(10, "We somehow broke our own function... Apparently, searching identical strings doesn't work. (strmanip.cpp, str_find_range())");

        }

        // In order to get the position of the IGNORE character, we have to
        // shift forward by the length of the string we compared with,
        // minus the length of the ignore string.
        original_pos = original_pos + left.length() - ignore.length();

        // Find the index in the positions vector that matches
        // the position we just found.
        // NOTE: We can't just take the first ignore string, because
        // it's possible that in the stripping, we got rid of some of
        // the ignored data, and we want to make sure we put everything
        // back in the right place.
        unsigned int quote_index = search(removed_pos, original_pos);

        if (quote_index == UINT_MAX) {

          throw Exception(stripped_pos, "We somehow broke our own function... Apparently, searching identical strings doesn't work. (strmanip.cpp, str_find_range())");

        }

        // Replace the ignore string with the removed string.
        str.replace(stripped_pos, ignore.length(), removed_quotes[quote_index]);

      } else {

        quotes_replaced = true;

      } /* if (stripped_pos != string::npos) */

    }; /* while (!quotes_replaced) */

  } /* if (ignore_quotes && !removed_quotes.empty()) */

  if (!inclusive) {

    // If we're not including the start/end, then we
    // use the mid function and get everything between the
    // start/end caps.
    str = str_mid(str, start.length(), str.length() - start.length() - end.length());

  }

  // If we make it this far...
  return str;

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_find_range()
/// @brief -- Overload of the all-string variant.
//////////////////////////////////////////////////////////////////////
string str_find_range(string str, char start, string end, bool nested,
                  bool inclusive, bool ignore_quotes, char ignore_following) {
  
  return str_find_range(str, char_to_str(start), end, nested,
                    inclusive, ignore_quotes, ignore_following);

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_find_range()
/// @brief -- Overload of the all-string variant.
//////////////////////////////////////////////////////////////////////
string str_find_range(string str, string start, char end, bool nested,
                  bool inclusive, bool ignore_quotes, char ignore_following) {
  
  return str_find_range(str, start, char_to_str(end), nested,
                    inclusive, ignore_quotes, ignore_following);

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_find_range()
/// @brief -- Overload of the all-string variant.
//////////////////////////////////////////////////////////////////////
string str_find_range(string str, char start, char end, bool nested,
                  bool inclusive, bool ignore_quotes, char ignore_following) {
  
  return str_find_range(str, char_to_str(start), char_to_str(end), nested,
                    inclusive, ignore_quotes, ignore_following);

}

//////////////////////////////////////////////////////////////////////
/// @fn vector<string> str_find_lines(string str, string delimiters)
/// @brief -- Returns a vector of strings from str by breaking
///           lines at any of delimiters, 
/// @param string str -- The string to search
/// @param string delimiters -- A string of delimiting characters.
/// @param bool keep_delim -- Maintains the delimiters in the lines
///                           if true, or discards if false.
//////////////////////////////////////////////////////////////////////
vector<string> str_find_lines(string str, string delimiters, bool keep_delim) {

  vector<string> lines;

  while (str != "") {

    unsigned int delimiter_pos = str.find_first_of(delimiters);

    // If we DID find a delimiter...
    if (delimiter_pos != string::npos) {

      // Shift the position forward by either one or zero,
      // depending on keep_delim.
      // This prevents delimiter_pos from becoming zero if
      // we don't find a delimiter (npos = -1) and keep_delim
      // is true, thus calling str_left with a length of zero.
      delimiter_pos += keep_delim;

      // By keeping the length to delimiter_pos, we can exclude the
      // delimiters unless keep_delim is true, in which case it
      // will include the delimiters
      lines.push_back(str_left(str, delimiter_pos));

      // Remove the part of the string we just captured.
      // Adjust by keep_delim here instead of in str_left
      // so we avoid the situation described above.
      str = str_right(str, str.length() - delimiter_pos + keep_delim - 1);

    } else {

      // If we didn't find a delimiter...
      // Push EVERYTHING onto the vector.
      lines.push_back(str);

      // And empty the string.
      str = "";

    }

  };

  return lines;

}

//////////////////////////////////////////////////////////////////////
/// @fn vector<int> str_find_all(string str, string to_find)
/// @brief -- Returns the positions of all instances (non-overlapping)
///           of to_find within str
/// @param string str -- The string to search
/// @param string to_find -- The string to look for
//////////////////////////////////////////////////////////////////////
vector<int> str_find_all(string str, string to_find) {

  vector<int> positions;
  unsigned int pos = 0;
  unsigned int last_found = 0;

  while (pos != string::npos) {

     pos = str.find(to_find, last_found);

     // Because we're looking for non-overlapping instances
     // of to_find, we have "last_found" be just after
     // the position we just found.
     last_found = pos + to_find.length();

     if (pos != string::npos) {

       positions.push_back(pos);

     }

  };

  return positions;

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_caesar(string str, int shift, bool encrypt = true)
/// @brief -- Encrypts or decrypts a string using a Caesar cipher 
/// @param string str -- The string to en/decrypt
/// @param int shift -- The shift value for the Caesar cipher
/// @param bool encrypt -- True to ENcrypt; false to DEcrypt
//////////////////////////////////////////////////////////////////////
string str_caesar(string str, int shift, bool encrypt) {

  // If we're decrypting...
  if (!encrypt) {

    // Invert the shift
    shift *= -1;

  }

  for (int x = 0; x < str.length(); x++) {

    str[x] += shift;

  }

  return str;

}

//////////////////////////////////////////////////////////////////////
/// @fn string str_vigenere(string str, string key, bool encrypt = true)
/// @brief -- Encrypts or decrypts a string using a Vigenère cipher 
/// @param string str -- The string to en/decrypt
/// @param string key -- The key for the Vigenère cipher
/// @param bool encrypt -- True to ENcrypt; false to DEcrypt
//////////////////////////////////////////////////////////////////////
string str_vigenere(string str, string key, bool encrypt) {

  // If we're decrypting...
  if (!encrypt) {

    // Invert the key
    for (int x = 0; x < key.length(); x++) {

      key[x] *= -1;

    }

  }

  int key_pos = 0;

  // Encrypt/decrypt the string
  for (int x = 0; x < str.length(); x++) {

    // Shift the string forward by the key
    str[x] += key[key_pos];

    // Next position in the key
    key_pos++;

    // If we're at the end of the key
    if (key_pos >= key.length()) {

      // Reset to zero.
      key_pos = 0;

    }

  }

  return str;

}
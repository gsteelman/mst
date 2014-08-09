//////////////////////////////////////////////////////////////////////
/// @file database.cpp
/// @author Jeremy Davidson
/// @brief -- Vacation system database
//////////////////////////////////////////////////////////////////////

#include "database.h"

#include "../library/exception.h"
#include "../library/library.h"
#include "../library/strmanip.h"

///////////////////////////////////////////
/// CONSTANTS
///////////////////////////////////////////
const string GLOBAL_SCOPE   = "--GLOBAL--";
const string DEFAULT_ENTRY  = "--DEFAULT--";

// For readability when encryption is disabled.
const string SCOPE_START    = "<";
const string SCOPE_END      = ">";
const string FIELD_START    = "  [";
const string FIELD_END      = "]";
const string ENTRY_START    = "    {";
const string ENTRY_END      = "}";

//const string DB_CIPHER      = "MAELSTROM";
const string DB_CIPHER = "";

//////////////////////////////////////////////////////////////////////
/// @fn Database()
/// @brief -- Loads nothing
//////////////////////////////////////////////////////////////////////
Database::Database() {

  // The global scope is created by the simple act of accessing it.
  m_database[GLOBAL_SCOPE];

}

//////////////////////////////////////////////////////////////////////
/// @fn Database(string filename)
/// @brief -- Loads the file given by "filename"
//////////////////////////////////////////////////////////////////////
Database::Database(string filename) {

  open(filename);

}

//////////////////////////////////////////////////////////////////////
/// @fn ~Database()
/// @brief -- Closes the file WITHOUT saving changes.
//////////////////////////////////////////////////////////////////////
Database::~Database() {

  // DESTROY!
  close();

}

//////////////////////////////////////////////////////////////////////
/// @fn void open(string filename)
/// @brief -- Opens the file given by "filename"
/// @param string filename -- Name of file to open
//////////////////////////////////////////////////////////////////////
void Database::open(string filename) {

  m_file.open(filename);

  parse_data();

}

//////////////////////////////////////////////////////////////////////
/// @fn void close(bool save_changes = false)
/// @brief -- Closes the database, saving changes if save_changes is true
/// @param bool save_changes -- Saves changes to m_filename
//////////////////////////////////////////////////////////////////////
void Database::close(bool save_changes) {

  if (save_changes) {

    // Don't bother updating the file if we're not saving.
    export_data();

  }

  m_file.close(save_changes);

  // We're all done, so empty the database.
  clear();

}

//////////////////////////////////////////////////////////////////////
/// @fn void save_file()
/// @brief -- Saves the file to "m_filename"
/// @throws -- If save fails for any reason.
//////////////////////////////////////////////////////////////////////
void Database::save_file() {

  export_data();

  m_file.save_file();

  if (m_file.error()) {

    throw Exception(1, "Save failed. (class Database, save_file())");

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void save_file(string filename)
/// @brief -- Saves the file to "filename" and adjusts m_filename
/// @throws -- If save fails for any reason.
//////////////////////////////////////////////////////////////////////
void Database::save_file(string filename) {

  export_data();
  
  m_file.save_file(filename);

  if (m_file.error()) {

    throw Exception(2, "Save failed. (class Database, save_file())");

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void clear()
/// @brief -- Empties the entire database.
/// @note -- The GLOBAL_SCOPE scope will persist, but all data in
///          it will be cleared.
//////////////////////////////////////////////////////////////////////
void Database::clear() {

  vector<string> scopes = get_scopes();

  // Iterate through all existing scopes...
  for (unsigned int x = 0; x < scopes.size(); x++) {

    // And DESTROY THEM!
    delete_scope(scopes[x]);

  }

  // If the global scope has been created...
  if (m_database.find(GLOBAL_SCOPE) != m_database.end()) {

    clear_scope(GLOBAL_SCOPE);

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn vector<string> get_scopes()
/// @brief -- Returns a vector of all the scopes defined in this
///           database. 
//////////////////////////////////////////////////////////////////////
vector<string> Database::get_scopes() {

  // Skeleton
  vector<string> scopes;

  // Get an iterator to the database multimap.
  ScopeIteratorC iterator = m_database.begin();

  for (iterator = m_database.begin(); iterator != m_database.end(); iterator++) {

    // Don't keep the global scope, because it should be invisible.
    if (iterator->first != GLOBAL_SCOPE) {

      // Get the keys (first value stored in the pair)
      scopes.push_back(iterator->first);

    }

  }

  return scopes;

}

//////////////////////////////////////////////////////////////////////
/// @fn void add_scope(string scope)
/// @brief -- Adds a scope to the database.
/// @param string scope -- Name of the scope to add.
/// @note -- Does nothing if scope already exists.
/// @note -- A new scope automatically inherits all fields defined in
///          the GLOBAL_SCOPE scope.
//////////////////////////////////////////////////////////////////////
void Database::add_scope(string scope) {

  // If the scope doesn't exist...
  if (m_database.find(scope) == m_database.end()) {

    // The scope is created automatically by accessing it.
    m_database[scope];

    // Copy the global scope's fields into the new scope.
    FieldIteratorC field_iterator;
    
    for (field_iterator = m_database[GLOBAL_SCOPE].begin();
         field_iterator != m_database[GLOBAL_SCOPE].end();
         field_iterator++) {

      add_field(scope, field_iterator->first);

    }

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void clear_scope(string scope)
/// @brief -- Clears all fields from "scope"
/// @param string scope -- Name of the scope to clear.
/// @note -- Fields in GLOBAL_SCOPE shared by "scope" will be cleared
///          of all their entries, but the fields will persist.
/// @throws -- If "scope" does not exist in the database.
//////////////////////////////////////////////////////////////////////
void Database::clear_scope(string scope) {

  // Make sure the scope exists. :)
  if (m_database.find(scope) == m_database.end()) {

    throw Exception(3, "Scope \"" + scope + "\" does not exist. (class Database, clear_scope())");

  }

  // Get the fields we need to maintain.
  vector<string> fields = get_fields(GLOBAL_SCOPE);

  FieldMap field_map;

  for (unsigned int x = 0; x < fields.size(); x++) {

    // Insert the scopes with a default entry, so they
    // exist, but are ignored.
    FieldPair new_field(fields[x], DEFAULT_ENTRY);

    field_map.insert(new_field);

  }

  // Replace the existing field map.
  m_database[scope] = field_map;

}

//////////////////////////////////////////////////////////////////////
/// @fn void delete_scope(string scope)
/// @brief -- Deletes "scope" from the database and all entries
///           related to it.
/// @param string scope -- Name of the scope to remove.
/// @note -- If GLOBAL_SCOPE is deleted, all its fields are removed,
///          but the scope persists.
///          Fields removed from GLOBAL_SCOPE this way will also
///          be removed from all other scopes in the database.
/// @throws -- If "scope" does not exist in the database.
//////////////////////////////////////////////////////////////////////
void Database::delete_scope(string scope) {

  // Make sure the scope exists. :)
  if (m_database.find(scope) == m_database.end()) {

    throw Exception(4, "Scope \"" + scope + "\" does not exist. (class Database, delete_scope())");

  }

  m_database.erase(scope);

  // If we erased the global scope...
  if (scope == GLOBAL_SCOPE) {

    // ...recreate it. :)
    m_database[GLOBAL_SCOPE];

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn vector<string> get_fields(string scope = GLOBAL_SCOPE)
/// @brief -- Returns a vector of all the names of fields within
///           the scope provided.
/// @throws -- If "scope" does not exist in the database.
//////////////////////////////////////////////////////////////////////
vector<string> Database::get_fields(string scope) {

  // Make sure the scope exists. :)
  if (m_database.find(scope) == m_database.end()) {

    throw Exception(5, "Scope \"" + scope + "\" does not exist. (class Database, get_fields())");

  }

  vector<string> fields;

  FieldIteratorC field_iterator;

  // Get the iterator to the beginning of the field map
  // matching the scope requested.
  for (field_iterator = m_database[scope].begin();
       field_iterator != m_database[scope].end();
       field_iterator++) {

    // If the field doesn't already exist in the vector...
    if (search(fields, field_iterator->first) == UINT_MAX) {

      // Stash it.
      fields.push_back(field_iterator->first);

    }

  }

  return fields;

}

//////////////////////////////////////////////////////////////////////
/// @fn add_field(string field)
/// @brief -- Adds a field to the GLOBAL_SCOPE
/// @param string field -- Name of the field to add.
/// @note -- Fields added to GLOBAL_SCOPE are automatically passed to
///          other scopes.
//////////////////////////////////////////////////////////////////////
void Database::add_field(string field) {

  // If the field is not already a member of the global scope...
  if (m_database[GLOBAL_SCOPE].find(field) == m_database[GLOBAL_SCOPE].end()) {

    // Create a field pair with a default entry.
    FieldPair new_field(field, DEFAULT_ENTRY);

    // And insert it into the global scope.
    m_database[GLOBAL_SCOPE].insert(new_field);

    vector<string> other_scopes = get_scopes();

    for (unsigned int x = 0; x < other_scopes.size(); x++) {

      // Add the field to the other scopes.
      add_field(other_scopes[x], field);

    }

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn add_field(string scope, string field)
/// @brief -- Adds a "field" field to the "scope" scope.
/// @param string scope -- Scope to add the field to.
/// @param string field -- Name of the field to add.
/// @note -- If "scope" does not exist, it will be created.
//////////////////////////////////////////////////////////////////////
void Database::add_field(string scope, string field) {

  // If we're adding to the global scope,
  // send it to the specialized function, so it
  // does all the extras it needs to.
  if (scope == GLOBAL_SCOPE) {

    add_field(field);

    return;

  }

  // If the scope doesn't exist...
  if (m_database.find(scope) == m_database.end()) {

    // Create it.
    add_scope(scope);

  }

  // If the field doesn't exist...
  if (m_database[scope].find(field) == m_database[scope].end()) {

    // Create a field pair with a default entry.
    FieldPair new_field(field, DEFAULT_ENTRY);

    // And insert it into the scope.
    m_database[scope].insert(new_field);

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void clear_field(string scope, string field)
/// @brief -- Deletes all entries associated with "field" in "scope".
/// @param string scope -- Scope of the field.
/// @param string field -- Field to clear.
/// @throws -- If "field" does not exist in "scope".
/// @throws -- If "scope" does not exist.
//////////////////////////////////////////////////////////////////////
void Database::clear_field(string scope, string field) {

  // Make sure the scope exists. :)
  if (m_database.find(scope) == m_database.end()) {

    throw Exception(6, "Scope \"" + scope + "\" does not exist. (class Database, clear_field())");

  }

  // Make sure the field exists. :)
  if (m_database[scope].find(field) == m_database[scope].end()) {

    throw Exception(7, "Field \"" + field + "\" does not exist in scope \"" + scope + "\". (class Database, clear_field())");

  }

  // It does the job. :P
  delete_field(scope, field);
  add_field(scope, field);

}

//////////////////////////////////////////////////////////////////////
/// @fn delete_field(string field)
/// @brief -- Removes "field" from the GLOBAL_SCOPE
/// @param string field -- Field to delete.
/// @note -- Fields deleted from the GLOBAL_SCOPE using THIS METHOD
///          are automatically removed from other scopes.
///          Deleting fields from the GLOBAL_SCOPE using the BELOW
///          method WILL NOT remove them from other scopes.
/// @throws -- If "field" does not exist in the GLOBAL_SCOPE.
//////////////////////////////////////////////////////////////////////
void Database::delete_field(string field) {

  // Make sure the field exists. :)
  if (m_database[GLOBAL_SCOPE].find(field) == m_database[GLOBAL_SCOPE].end()) {

    throw Exception(8, "Field \"" + field + "\" does not exist in scope \"" + GLOBAL_SCOPE + "\". (class Database, delete_field())");

  }

  // Find the range of entries with "field" as their field.
  FieldIteratorC lower_bound = m_database[GLOBAL_SCOPE].lower_bound(field);
  FieldIteratorC upper_bound = m_database[GLOBAL_SCOPE].upper_bound(field);

  // Erase the entire range.
  m_database[GLOBAL_SCOPE].erase(lower_bound, upper_bound);

  vector<string> other_scopes = get_scopes();

  for (unsigned int x = 0; x < other_scopes.size(); x++) {

    // Remove the field from the other scopes.
    delete_field(other_scopes[x], field);

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn delete_field(string scope, string field)
/// @brief -- Removes "field" from "scope"
/// @param string scope -- Scope to remove the field from.
/// @param string field -- Name of the field to remove.
/// @note -- Fields deleted from the GLOBAL_SCOPE using this method
///          WILL NOT remove them from other scopes in the database.
/// @throws -- If "field" does not exist in "scope".
/// @throws -- If "scope" does not exist.
//////////////////////////////////////////////////////////////////////
void Database::delete_field(string scope, string field) {

  // Make sure the scope exists. :)
  if (m_database.find(scope) == m_database.end()) {

    throw Exception(9, "Scope \"" + scope + "\" does not exist. (class Database, delete_field())");

  }

  // Make sure the field exists. :)
  if (m_database[scope].find(field) == m_database[scope].end()) {

    throw Exception(10, "Field \"" + field + "\" does not exist in scope \"" + scope + "\". (class Database, delete_field())");

  }

  // Note: Fields deleted from the GLOBAL_SCOPE using this method
  //       WILL NOT remove them from other scopes in the database.
  // Logic: The global scope is, in essence, a guaranteed subset
  //        of every single other scope in the database. If
  //        a new field is ADDED to the global scope, then it
  //        is expected to appear in all the other scopes,
  //        but if a field is removed from the global scope,
  //        it still satisfies the property of being a subset
  //        of all the other fields without any further
  //        modification.
  //        If you WANT to remove fields globally, use the
  //        other version of this method.
  //        :)

  // Find the range of entries with "field" as their field.
  FieldIteratorC lower_bound = m_database[scope].lower_bound(field);
  FieldIteratorC upper_bound = m_database[scope].upper_bound(field);

  // Erase the entire range.
  m_database[scope].erase(lower_bound, upper_bound);

  // If the field exists in the global scope, it
  // MUST remain a member of this scope, even though
  // all its data is now gone.
  if (m_database[GLOBAL_SCOPE].find(field) != m_database[GLOBAL_SCOPE].end()) {

    add_field(scope, field);

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn string get_entry(string scope, string field, unsigned int index)
/// @brief -- Returns the entry stored in "scope"'s field "field"
/// @param string scope -- Scope to retrieve the entry from.
/// @param string field -- Field to retrieve the entry from.
/// @param unsigned int index -- The index of the entry. 
/// @note -- If "field" has more than one entry, this will return
///          the one at "index" in the database.
/// @throws -- If "field" does not exist in "scope".
/// @throws -- If "scope" does not exist.
/// @throws -- If "index" is out of range.
//////////////////////////////////////////////////////////////////////
string Database::get_entry(string scope, string field, unsigned int index) {

  // Make sure the scope exists. :)
  if (m_database.find(scope) == m_database.end()) {

    throw Exception(11, "Scope \"" + scope + "\" does not exist. (class Database, get_entry())");

  }

  // Make sure the field exists. :)
  if (m_database[scope].find(field) == m_database[scope].end()) {

    throw Exception(12, "Field \"" + field + "\" does not exist in scope \"" + scope + "\". (class Database, get_entry())");

  }

  if (m_database[scope].count(field) <= index) {

    throw Exception(17, "Entry at index " + int_to_str(index) + " does not exist in field \"" + field + "\" in scope \"" + scope + "\". (class Database, get_entry())");

  }

  // Get the first entry.
  FieldIteratorC entry_it = m_database[scope].lower_bound(field);

  // Shift it forward to the desired index.
  for (int x = 0; x < index; x++) {

    entry_it++;

  }

  // Return the entry stored in the field found.
  string entry = entry_it->second;

  return entry;

}

//////////////////////////////////////////////////////////////////////
/// @fn vector<string> get_entries(string scope, string field)
/// @brief -- Returns all entries associated to "field" in "scope".
/// @param string scope -- Scope to retrieve the entry from.
/// @param string field -- Field to retrieve the entry from.
/// @note -- Use this method if a field could have more than one
///          entry.
/// @throws -- If "field" does not exist in "scope".
/// @throws -- If "scope" does not exist.
//////////////////////////////////////////////////////////////////////
vector<string> Database::get_entries(string scope, string field) {

  // Make sure the scope exists. :)
  if (m_database.find(scope) == m_database.end()) {

    throw Exception(13, "Scope \"" + scope + "\" does not exist. (class Database, get_entries())");

  }

  // Make sure the field exists. :)
  if (m_database[scope].find(field) == m_database[scope].end()) {

    throw Exception(14, "Field \"" + field + "\" does not exist in scope \"" + scope + "\". (class Database, get_entries())");

  }

  vector<string> entries;

  FieldIteratorC lower_bound = m_database[scope].lower_bound(field);
  FieldIteratorC upper_bound = m_database[scope].upper_bound(field);

  // Loop through the entries that match "field"
  for (FieldIteratorC it = lower_bound; it != upper_bound; it++) {

    // And store them in the vector.
    entries.push_back(it->second);

  }

  return entries;

}

//////////////////////////////////////////////////////////////////////
/// @fn void add_entry(string scope, string field, string value)
/// @brief -- Adds "value" as an entry in "field" in "scope".
/// @param string scope -- Scope to add the entry to.
/// @param string field -- Field to add the entry to.
/// @param string value -- Entry to add.
/// @note -- If "field" already has an entry in the database,
///          ANOTHER entry will be added to the database with
///          the same "field" association.
/// @note -- If either "scope" or "field" do not exist, they will
///          be created to accommodate the entry.
//////////////////////////////////////////////////////////////////////
void Database::add_entry(string scope, string field, string value) {

  // If the requested scope does not exist, add it.
  if (m_database.find(scope) == m_database.end()) {

    add_scope(scope);

  }

  // If the requested field does not exist, add it.
  if (m_database[scope].find(field) == m_database[scope].end()) {

    add_field(scope, field);

  }

  FieldIterator lower_bound = m_database[scope].lower_bound(field);
  FieldIterator upper_bound = m_database[scope].upper_bound(field);

  // Loop through the entries that match "field"
  for (FieldIterator it = lower_bound; it != upper_bound; it++) {

    // If we run into a default entry...
    if (it->second == DEFAULT_ENTRY) {

      // Replace it, because we don't want one.
      it->second = value;

      // And leave.
      return;

    }

  }

  // If we don't run into a default entry in our check...
  // Create a new entry.
  FieldPair new_entry(field, value);

  // And add it.
  m_database[scope].insert(new_entry);

}

//////////////////////////////////////////////////////////////////////
/// @fn void edit_entry(string scope, string field, string value, unsigned int index)
/// @brief -- Edits the entry at "index" in "field" within "scope".
/// @param string scope -- Scope to edit the entry.
/// @param string field -- Field to edit the entry.
/// @param string value -- Entry to store.
/// @param unsigned int index -- The index of the entry. 
/// @note -- If "field" already has an entry in the database,
///          it will be OVERWRITTEN by this entry.
///          If MULTIPLE entries exist, the one at index "index"
///          be overwritten by this entry.
/// @note -- If "scope" or "field" do not exist, they will
///          be created to accommodate the edit.
/// @throws -- If "index" is out of range.
//////////////////////////////////////////////////////////////////////
void Database::edit_entry(string scope, string field, string value, unsigned int index) {

  // If the requested scope does not exist, add it.
  if (m_database.find(scope) == m_database.end()) {

    add_scope(scope);

  }

  // If the requested field does not exist, add it.
  if (m_database[scope].find(field) == m_database[scope].end()) {

    add_field(scope, field);

  }

  if (m_database[scope].count(field) <= index) {

    throw Exception(18, "Entry at index " + int_to_str(index) + " does not exist in field \"" + field + "\" in scope \"" + scope + "\". (class Database, edit_entry())");

  }

  // Get the first entry.
  FieldIterator entry_it = m_database[scope].lower_bound(field);

  // Shift it forward to the desired index.
  for (int x = 0; x < index; x++) {

    entry_it++;

  }

  // Replace the first entry with "value"
  entry_it->second = value;

}

//////////////////////////////////////////////////////////////////////
/// @fn void delete_entry(string scope, string field, unsigned int index)
/// @brief -- Removes the entry stored in the "field" in "scope"
/// @param string scope -- Scope to remove the entry from.
/// @param string field -- Field to remove the entry from.
/// @param unsigned int index -- The index of the entry. 
/// @note -- If MULTIPLE entries exist, only the one at "index" is removed.
///          To remove ALL entries in a field, use clear_field().
/// @throws -- If "field" does not exist in "scope".
/// @throws -- If "scope" does not exist.
/// @throws -- If "index" is out of range.
//////////////////////////////////////////////////////////////////////
void Database::delete_entry(string scope, string field, unsigned int index) {

  // Make sure the scope exists. :)
  if (m_database.find(scope) == m_database.end()) {

    throw Exception(15, "Scope \"" + scope + "\" does not exist. (class Database, delete_entry())");

  }

  // Make sure the field exists. :)
  if (m_database[scope].find(field) == m_database[scope].end()) {

    throw Exception(16, "Field \"" + field + "\" does not exist in scope \"" + scope + "\". (class Database, delete_entry())");

  }

  int count = m_database[scope].count(field);

  if (count <= index) {

    throw Exception(19, "Entry at index " + int_to_str(index) + " does not exist in field \"" + field + "\" in scope \"" + scope + "\". (class Database, delete_entry())");

  }

  // Get the first entry.
  FieldIterator entry_it = m_database[scope].lower_bound(field);

  // Shift it forward to the desired index.
  for (int x = 0; x < index; x++) {

    entry_it++;

  }

  if (count != 1) {

    // And kill it.
    m_database[scope].erase(entry_it);

  } else {

    clear_field(scope, field);

  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void parse_data()
/// @brief -- Parses the data in m_file and converts it to the
///           internal database format.
//////////////////////////////////////////////////////////////////////
void Database::parse_data() {

  // Start the database fresh.
  clear();

  // Keep track of where we are in the file.
  string scope, field, entry;

  for (unsigned int x = 0; x < m_file.num_lines(); x++) {

    // Loop at the str_find_range documentation for an explanation
    // of the parameters.
    string line = str_find_range(m_file[x], SCOPE_START, SCOPE_END);

    // If we didn't get nothing back...
    if (line != "") {

      // That means we found a scope.
      // Strip the START/END tags from the line and store as scope.
      scope = str_mid(line,
                      SCOPE_START.length(),
                      line.length() - SCOPE_START.length() - SCOPE_END.length());

    // The scope check was a failure.
    } else {

      // So we look for a field.
      line = str_find_range(m_file[x], FIELD_START, FIELD_END);
          
      // If we didn't get nothing back...
      if (line != "") {

        // That means we found a field.
        // Strip the START/END tags from the line and store as field.
        field = str_mid(line,
                        FIELD_START.length(),
                        line.length() - FIELD_START.length() - FIELD_END.length());

      // The field check was a failure.
      } else {

        // So we look for an entry.
        line = str_find_range(m_file[x], ENTRY_START, ENTRY_END);

        // If we found something...
        if (line != "") {

          // That means we found an entry.
          // Strip the START/END tags from the line and store as entry.
          entry = str_mid(line,
                          ENTRY_START.length(),
                          line.length() - ENTRY_START.length() - ENTRY_END.length());

          // Add the entry to the database.
          add_entry(scope, field, entry);

        } /* if (line != "") -- For entry */

      } /* if (line != "") -- For field */

    } /* if (line != "") -- For scope */

  } /* for (unsigned int x = 0; x < m_file.num_lines(); x++) */

}

//////////////////////////////////////////////////////////////////////
/// @fn void export_data()
/// @brief -- Converts the internal database to a text format and
///           stores it in the m_file file.
//////////////////////////////////////////////////////////////////////
void Database::export_data() {

  m_file.clear();

  // Get our scopes.
  vector<string> scopes = get_scopes();

  // get_scopes ignores the global scope, but we want it
  // for exporting.
  scopes.push_back(GLOBAL_SCOPE);

  // Storage for later.
  vector<string> fields;
  vector<string> entries;

  // Loop through all the scopes.
  for (unsigned int x = 0; x < scopes.size(); x++) {

    // Create a tag for the current scope.
    string line = SCOPE_START + scopes[x] + SCOPE_END;

    // Insert it at the end of the file.
    m_file.insert_line(m_file.num_lines(), line);

    // Find the fields that go with this scope.
    fields = get_fields(scopes[x]);

    // Loop through them.
    for (unsigned int y = 0; y < fields.size(); y++) {

      // Create a tag for the current field.
      line = FIELD_START + fields[y] + FIELD_END;

      // Insert it at the end of the file.
      m_file.insert_line(m_file.num_lines(), line);

      // Find the entries that go with this field.
      entries = get_entries(scopes[x], fields[y]);

      // And loop through them, too
      for (unsigned int z = 0; z < entries.size(); z++) {

        // Create a tag for the current entry.
        line = ENTRY_START + entries[z] + ENTRY_END;

        // Insert it at the end of the file.
        m_file.insert_line(m_file.num_lines(), line);

      }

    }

  }

  // Set encryption, because it's fun!
  m_file.set_cipher(DB_CIPHER);

  // Save the export.
  m_file.save_file();

}

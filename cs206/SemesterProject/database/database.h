//////////////////////////////////////////////////////////////////////
/// @file database.h
/// @author Jeremy Davidson
/// @brief -- Vacation system database
//////////////////////////////////////////////////////////////////////
/// @fn Database()
/// @brief -- Loads nothing
//////////////////////////////////////////////////////////////////////
/// @fn Database(string filename)
/// @brief -- Loads the file given by "filename"
//////////////////////////////////////////////////////////////////////
/// @fn ~Database()
/// @brief -- Closes the file WITHOUT saving changes.
//////////////////////////////////////////////////////////////////////
/// @fn void open(string filename)
/// @brief -- Opens the file given by "filename"
/// @param string filename -- Name of file to open
//////////////////////////////////////////////////////////////////////
/// @fn void close(bool save_changes = false)
/// @brief -- Closes the database, saving changes if save_changes is true
/// @param bool save_changes -- Saves changes to m_filename
//////////////////////////////////////////////////////////////////////
/// @fn void save_file()
/// @brief -- Saves the file to "m_filename"
/// @throws -- If no filename has been specified.
//////////////////////////////////////////////////////////////////////
/// @fn void save_file(string filename)
/// @brief -- Saves the file to "filename" and adjusts m_filename
//////////////////////////////////////////////////////////////////////
/// @fn void clear()
/// @brief -- Empties the entire database.
/// @note -- The GLOBAL_SCOPE scope will persist, but all data in
///          it will be cleared.
//////////////////////////////////////////////////////////////////////
/// @fn vector<string> get_scopes()
/// @brief -- Returns a vector of all the scopes defined in this
///           database. 
//////////////////////////////////////////////////////////////////////
/// @fn void add_scope(string scope)
/// @brief -- Adds a scope to the database.
/// @param string scope -- Name of the scope to add.
/// @note -- Does nothing if scope already exists.
/// @note -- A new scope automatically inherits all fields defined in
///          the GLOBAL_SCOPE scope.
//////////////////////////////////////////////////////////////////////
/// @fn void clear_scope(string scope)
/// @brief -- Clears all fields from "scope"
/// @param string scope -- Name of the scope to clear.
/// @note -- Fields in GLOBAL_SCOPE shared by "scope" will be cleared
///          of all their entries, but the fields will persist.
/// @throws -- If "scope" does not exist in the database.
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
/// @fn vector<string> get_fields(string scope = GLOBAL_SCOPE)
/// @brief -- Returns a vector of all the names of fields within
///           the scope provided.
/// @throws -- If "scope" does not exist in the database.
//////////////////////////////////////////////////////////////////////
/// @fn add_field(string field)
/// @brief -- Adds a field to the GLOBAL_SCOPE
/// @param string field -- Name of the field to add.
/// @note -- Fields added to GLOBAL_SCOPE are automatically passed to
///          other scopes.
//////////////////////////////////////////////////////////////////////
/// @fn add_field(string scope, string field)
/// @brief -- Adds a "field" field to the "scope" scope.
/// @param string scope -- Scope to add the field to.
/// @param string field -- Name of the field to add.
/// @note -- If "scope" does not exist, it will be created.
//////////////////////////////////////////////////////////////////////
/// @fn void clear_field(string scope, string field)
/// @brief -- Deletes all entries associated with "field" in "scope".
/// @param string scope -- Scope of the field.
/// @param string field -- Field to clear.
/// @throws -- If "field" does not exist in "scope".
/// @throws -- If "scope" does not exist.
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
/// @fn delete_field(string scope, string field)
/// @brief -- Removes "field" from "scope"
/// @param string scope -- Scope to remove the field from.
/// @param string field -- Name of the field to remove.
/// @note -- Fields deleted from the GLOBAL_SCOPE using this method
///          WILL NOT remove them from other scopes in the database.
/// @throws -- If "field" does not exist in "scope".
/// @throws -- If "scope" does not exist.
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
/// @fn vector<string> get_entries(string scope, string field)
/// @brief -- Returns all entries associated to "field" in "scope".
/// @param string scope -- Scope to retrieve the entry from.
/// @param string field -- Field to retrieve the entry from.
/// @note -- Use this method if a field could have more than one
///          entry.
/// @throws -- If "field" does not exist in "scope".
/// @throws -- If "scope" does not exist.
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
/// @fn void parse_data()
/// @brief -- Parses the data in m_file and converts it to the
///           internal database format.
//////////////////////////////////////////////////////////////////////
/// @fn void export_data()
/// @brief -- Converts the internal database to a text format and
///           stores it in the m_file file.
//////////////////////////////////////////////////////////////////////

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;
using std::multimap;
using std::pair;

#include "../library/file.h"

///////////////////////////////////////////
/// GLOBALS
///////////////////////////////////////////
extern const string GLOBAL_SCOPE;
extern const string DEFAULT_ENTRY;

///////////////////////////////////////////
/// TYPEDEFS
///////////////////////////////////////////
typedef multimap<string, string>  FieldMap;
typedef pair    <string, string>  FieldPair;
typedef FieldMap::iterator        FieldIterator;
typedef FieldMap::const_iterator  FieldIteratorC;
typedef map<string, FieldMap>     ScopeMap;
typedef pair<string, FieldMap>    ScopePair;
typedef ScopeMap::iterator        ScopeIterator;
typedef ScopeMap::const_iterator  ScopeIteratorC;
// Sorry about all these typedefs, but I really don't
// think you wanna try to sort through all the
// multimap<string, multimap<string, string> >::iterator
// I'd be using if there were no typedefs. :)

class Database {

  public:

    Database();
    Database(string filename);
    ~Database();

    void            open(string filename);
    void            close(bool save_changes = false);

    void            save_file();
    void            save_file(string filename);

    void            clear();

    vector<string>  get_scopes();
    void            add_scope(string scope);
    void            clear_scope(string scope);
    void            delete_scope(string scope);

    vector<string>  get_fields(string scope = GLOBAL_SCOPE);
    void            add_field(string field);
    void            add_field(string scope, string field);
    void            clear_field(string scope, string field);
    void            delete_field(string field);
    void            delete_field(string scope, string field);

    string          get_entry(string scope, string field, unsigned int index = 0);
    vector<string>  get_entries(string scope, string field);
    void            add_entry(string scope, string field, string value);
    void            edit_entry(string scope, string field, string value, unsigned int index = 0);
    void            delete_entry(string scope, string field, unsigned int index = 0);

  protected:

    void parse_data();
    void export_data();

  private:

    File      m_file;

    // Type defined above. For readability above else.
    ScopeMap  m_database;

};

#endif
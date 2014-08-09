<?php

/**
 * file: functions.php
 * brief: contains functions necessary for the project
 */
 
include "config.php";
include "display_results.php";

/**
 * fn: my_untrusted_mysql_query
 * brief: perform a mysql query and check to make sure the query executed
 *    properly.
 * param: $sql_query -- string that is the query to perform
 * param: $connection -- string that is the connection to the database
 */
function my_untrusted_mysql_query( $sql_query, $connection = 0 )
{
  //If a specific connection wasn't passed in, set it to the global connection
  if ($connection == 0)
  {
    global $con;
    $connection = $con;
  }
  
  //Perform a version of the query that's been cleaned of unsanitary characters
  //and doesn't allow SQL injection attacks
  $result = mysql_query( mysql_real_escape_string($sql_query), $connection );
  if (!$result)
  {
    die('MySQL query failure: ' . mysql_error() . "<br />");
  }
  
  if ( is_resource($result) )
  {
    //Store the results of the query. We do this because a PHP array is more
    //portable and easier to work with since we don't have to use sql specific
    //functions for it.
    $return_array = array();
  
    while ( $row = mysql_fetch_assoc($result) )
    {
      array_push($return_array, $row);
    }
  
    //Free the memory used by the result of the query
    mysql_free_result($result);
    
    return $return_array;
  }
}

/**
 * fn: my_trusted_mysql_query
 * brief: perform a mysql query and check to make sure the query executed
 *    properly.
 * param: $sql_query -- string that is the query to perform
 * param: $connection -- string that is the connection to the database
 */
function my_trusted_mysql_query( $sql_query, $connection = 0 )
{
  //If a specific connection wasn't passed in, set it to the global connection
  if ($connection == 0)
  {
    global $con;
    $connection = $con;
  }
  
  //Perform a version of the query that's been cleaned of unsanitary characters
  //and doesn't allow SQL injection attacks
  $result = mysql_query( $sql_query, $connection );
  if (!$result)
  {
    die('MySQL query failure: ' . mysql_error() . "<br />");
  }

  if ( is_resource($result) )
  {
    //Store the results of the query. We do this because a PHP array is more
    //portable and easier to work with since we don't have to use sql specific
    //functions for it.
    $return_array = array();
  
    while ( $row = mysql_fetch_assoc($result) )
    {
      array_push($return_array, $row);
    }
  
    //Free the memory used by the result of the query
    mysql_free_result($result);
    
    return $return_array;
  }
}

/**
 * fn: my_mysql_connect
 * brief: perform a mysql connect and check to make sure the connect executed
 *    properly.
 */
function my_mysql_connect()
{
  //Use the global connection
  global $con;
  global $server_loc;
  global $server_username;
  global $server_pass;
  
  //Connect to the server
  $con = mysql_connect( $server_loc, $server_username, $server_pass );
  if (!$con)
  {
    die('Could not connect to server: ' . mysql_error() . "<br />");
  }
  
  global $db_name;
  
  //Select the database
  $result = mysql_select_db( $db_name, $con );
  if (!$result)
  {
    die('Could not connect to database: ' . $db_name . '; ' . mysql_error() . "<br />");
  }
}

/**
 * fn: my_mysql_connect
 * brief: perform a mysql connect and check to make sure the connect executed
 *    properly.
 */
function my_mysql_close()
{
  global $con;

  $result = mysql_close($con);
  if (!$result)
  {
    die('Could not close connection: ' . mysql_error() . "<br />");
  }
}

/**
 * fn: display_results
 * brief: takes in an array of results from an sql query and then displays them
 * param: $query_results -- array of results from my_trusted_mysql_query()
 */
 
function display_results( $query_results )
{
  if ( count($query_results) != 0 )
  {
    echo "<table align='center' border='1'>";
    echo "<tr>";
    
    //Print out the table headers
    foreach ( $query_results[0] as $key => $value )
    {
      echo "<th>$key</th>";
    }
    
    echo "</tr>";
    
    //Print out each row
    foreach ($query_results as $row) 
    {
      echo "<tr>";
      
      foreach( $row as $key => $value )
      {
        echo "<td>$value</td>";
      }
      echo "</tr>";
    }
     
    echo "</table>"; 
  }
}

/**
 * fn: safe_inputs
 * brief: takes in an array and returns an array containing the 
 *    mysql_real_escape_string() version of each element.
 * param: $inputs -- array of inputs from $_POST probably
 */
function safe_inputs( $inputs )
{
  $q = array();
  
  my_mysql_connect();

  foreach($inputs as $key => $value)
  {
    if ( is_array( $value ) )
    {
      $q[mysql_real_escape_string($key)] = $value;
    }
    
    //Cleanse the key (because it's generated from an HTML form, the
    //user could put whatever they wanted here) and its value
    else
    {
      $q[mysql_real_escape_string($key)] = mysql_real_escape_string($value);
    }
  }
  
  my_mysql_close();
  
  return $q;
}

?> 
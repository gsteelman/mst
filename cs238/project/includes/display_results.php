<?php 

/**
 * file: display_results.php
 * brief: takes in an array of results from an sql query and then displays them
 * purpose: this page exists so we can just pass results to it from wherever and
 *    then the results will display the same from all pages in our site
 */
 
/**
 * fn: output_res
 * brief: takes in an array of results from an sql query and then displays them
 * param: $query_results -- array of results from my_trusted_mysql_query()
 */

function output_res( $query_results )
{
  /*echo "<html><title>Display Results</title><body>";
  echo "<table border='1'>";
  echo "<tr>";*/
  
  echo "<table border='1'>";
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
  //echo "</table></body></html>";

}
 
?> 
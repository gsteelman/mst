This is a simple TWiki perl module that retrieves data from the Yahoo! Stock Quote 
server and displays it in TWiki format.

Sample usage:
perl stock_quote.pl -p "./" -d -h -e 12/13_2008 -b 1-1/2005

Please list the stock symbols for the quotes to retrieve. Must be separated by a single space a - or a _
Like this: GOOG-SPY_IGRSX VBIIX
SPY_VBIIX IGRSX
Retrieving quote data from the server. If this takes more than a few seconds kill the script and try again, the server h
as stalled in answering.
Stock data retrieval successful.


FOR THE SECOND PHASE OF THE PROJECT (TESTING)
The results of the test cases are all in the .docx or .pdf (they contain the same data).
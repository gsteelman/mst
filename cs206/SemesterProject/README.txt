To compile our project, please include all of the .h and .cpp files in the directories
  \database
  \library
  \requestTime
  \rulesSystem
    NOTE: Do NOT include TEST_rulesSystem.cpp
  \system
  \validate
  \
    NOTE: This means to include main.cpp, common.h, and common.cpp
    
NOTE: The ruleset to use needs to be located at "\rulesSystem\test.ruleset"

Operation of the program via the command line interface is explained below:

Run the project executable file with the following parameters to perform the respective functions:

Vacation System Help:
-Command <parameter1> <parameter2> ... <parameterN>
--help
  Shows this documentation.
  Aliases: -h
--login <username> <password>
  Sends login information to the SSO system.
  Aliases: -l
--request <start> <end> <\"sick\" OR \"vacation\">
  Puts a request into the database. Dates should be formatted as MM/DD
  Aliases: --r
--viewrequest <SSO>
  Lists all pending requests from <SSO>.
  Input \"all\" for <SSO> to view all requests pending approval.
  Only users of \"Manager\" class or higher may use this function.
  Aliases: --view --vr
--approverequest <SSO> <yes/no>
  Approve request from <SSO>.
  Only users of \"Manager\" class or higher may use this function.
  Aliases: --approve --ar
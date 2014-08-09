#!/bin/sh
#welcome the user
echo "Welcome to the script menu system."

option=0

#Will loop until the user chooses option 4
while [ "$option" -ne 4 ]
do
  #present the options to the user
  echo ""
  
  #present the menu to the user
  echo "Select your operation:"
  echo "1 - Print ancestry tree of current process."
  echo "2 - List users currently online."
  echo "3 - List processes of a given online user."
  echo "4 - Exit."

  read option #read in the option the user wants to do

  #switch on the option chosen by the user
  case "$option" in

    '1')
    #show the current process' ancestry tree
    currProc=$$
    echo "The current process' ancestry tree is: "
    echo "$currProc"
    
    #now we run through each process and then rotate to its parent
    while [ "$currProc" -ne "1" ] 
    do
      currProc=$(ps h -o ppid -p $currProc)
      echo "  |  "
      echo "$currProc"
    done
    echo ""
    ;;

    '2') 
    #Shows the users currently online
    echo ""
    echo "Users currently online:"
    users
    ;;

    '3')
    #Grabs the online users and puts their names into a temporary file userlist
    who | while read onlineuser
    do
      echo $onlineuser | cut -f1 -d' ' >> userlist
    done
    
    #Prepares the list of users online, then indexes them for the user to see
    #prepends each username with a number   
    index=1
    cat userlist | while read onlineuser
    do
      echo "$index-$onlineuser" >> indexeduserlist
      let index=$index+1
    done

    #done with the userlist now that we have an indexed one, remove it
    rm userlist

    #Present the user with the indexed list of usernames to choose from
    echo ""
    echo "Please select a user from the following list:"
    cat indexeduserlist
    read userchoice #get user choice

    #gets the username string
    desireduser=$(cat indexeduserlist | grep "$userchoice-" | cut -f2 -d'-')
    echo ""
    echo "Processes for $desireduser:"
    ps -ef > tempps
    grep $desireduser tempps #outputs to the screen the process list for user

    #A bit of cleanup
    rm indexeduserlist
    rm tempps
    ;;

    '4')
    echo ""
    echo "Exiting program."
    echo ""
    exit #exits the script
    ;;

    *)
    echo "Your input was not a valid choice. Try again."
      option=0
    ;;

    esac #gets out of the case statement
done #gets out of the while loop

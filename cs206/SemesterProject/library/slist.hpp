//////////////////////////////////////////////////////////////////////
/// @file slist.hpp
/// @author Jeremy Davidson
/// @brief Templated slist storage class. 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn Slist()
/// @brief -- Initializes the Slist
/// @pre -- Create a slist, preferably with a data type selected
/// @post -- Your slist is initialized. What's more to say?
//////////////////////////////////////////////////////////////////////
template <class Generic>
Slist<Generic>::Slist() {

  m_size = 0;
  
  m_front = NULL;
  
}

//////////////////////////////////////////////////////////////////////
/// @fn ~Slist()
/// @brief -- Destructor... frees the memory the pointer is pointing at
/// @pre -- Automatic
/// @post -- Automatic
//////////////////////////////////////////////////////////////////////
template <class Generic>
Slist<Generic>::~Slist() {

  clear();
  
}

//////////////////////////////////////////////////////////////////////
/// @fn void push_front(Generic x)
/// @brief -- Adds x to the first spot in the slist, shifts the pointers
///           so the chain-style list is maintained
/// @post -- m_size incremented, and x stored in the slist
/// @param Generic x -- The item to be placed in the slist
/// @return -- Nothing
//////////////////////////////////////////////////////////////////////
template <class Generic>
void Slist<Generic>::push_front(Generic x) {
 
  // Creates a temporary variable with the data we want
  Snode<Generic> * temp = new Snode<Generic>;
  
  // Puts the data in temp
  temp->data = x;
  
  // Assigns the forward to what m_front is pointing at
  temp->forward = m_front;
  
  // Makes m_front point to temp
  m_front = temp;
  
  // Increment size
  m_size++;

}

//////////////////////////////////////////////////////////////////////
/// @fn void pop_front()
/// @brief -- Grabs the item at the front of the slist and deletes it
/// @pre -- m_size > 0
/// @post -- m_size decrements by one
//////////////////////////////////////////////////////////////////////
template <class Generic>
void Slist<Generic>::pop_front() {

  if (!empty()) {
  
    // Reduce the effective size of the array,
    m_size--;
    
    // Creates a temp to point at the first entry
    Snode<Generic> * temp = m_front;
    
    // Points m_front at the next item
    m_front = m_front->forward;
    
    // And deletes temp
    delete temp;
    
  } else {
  
    throw Exception(1, "Trying to pop from an empty list. (class Slist, pop_front())");
    
  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void remove(Generic x)
/// @brief -- Searches for the first item in the list that matches x
///           and deletes it
/// @pre -- The list isn't empty, and x exists within the list
/// @post -- The item x is removed
/// @param Generic x -- The item to be removed from the list
//////////////////////////////////////////////////////////////////////
template <class Generic>
void Slist<Generic>::remove(Generic x) {

  if (!empty()) {
  
    // SPECIAL CASE: Requested data is at the front of the list
    if (m_front->data == x) {
    
      pop_front();
      return;
      
    }
    
    Snode<Generic> * temp = m_front;
        
    // Loop until end of list or temp is pointing at the node just before
    // the one that has the data x
    while (temp->forward != NULL && temp->forward->data != x) {
      
      temp = temp->forward;
    
    }
    
    if (temp->forward == NULL) {
    
      throw Exception(4, "Trying to remove nonexistent data. (class Slist, remove())");
      
    } else if (temp->forward->data == x) {
    
      // Reduce the size of the list
      m_size--;
      
      // Create another temporary pointer to look directly at the node
      // with the data we want
      Snode<Generic> * to_delete = temp->forward;
      
      // Point temp's forward at the node beyond the one
      // we're going to delete
      temp->forward = to_delete->forward;
      
      // Bye bye
      delete to_delete;
    
    } else {
    
      throw Exception(5, "Unknown error. Run for the hills. (class Slist, remove())");
      
    }
    
  } else {
  
    throw Exception(2, "Trying to remove from an empty list. (class Slist, remove())");
    
  }

}

//////////////////////////////////////////////////////////////////////
/// @fn Generic & front()
/// @brief -- Returns the item at the front of the list
/// @pre -- The list isn't empty
/// @return -- Returns the item at the front of the list
//////////////////////////////////////////////////////////////////////
template <class Generic>
Generic & Slist<Generic>::front() {

  if (!empty()) {
  
    return m_front->data;
    
  } else {
  
    throw Exception(3, "Trying to access the front of an empty list. (class Slist, front())");
    
  }

}

//////////////////////////////////////////////////////////////////////
/// @fn void clear()
/// @brief -- Empties all the data in the array and resets it to size 1
/// @pre -- None
/// @post -- All the data is gone
//////////////////////////////////////////////////////////////////////
template <class Generic>
void Slist<Generic>::clear() {

  while (!empty()) {
  
    pop_front();
  
  }

}

//////////////////////////////////////////////////////////////////////
/// @fn unsigned int size()
/// @brief -- Returns the number of elements in the slist
/// @pre -- Nothing
/// @post -- Nothing
/// @return -- Returns the number of elements in the slist
//////////////////////////////////////////////////////////////////////
template <class Generic>
unsigned int Slist<Generic>::size() {

  return m_size;

}

//////////////////////////////////////////////////////////////////////
/// @fn bool empty()
/// @brief -- Returns whether the list is empty or not
/// @return -- True/false for if the list is empty
//////////////////////////////////////////////////////////////////////
template <class Generic>
bool Slist<Generic>::empty() {

  return (m_front == NULL);

}

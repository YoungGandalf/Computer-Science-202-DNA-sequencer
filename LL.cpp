/************************************
File: LL.cpp
Project: CMSC 202 Project 3, Fall 2018
Author: Adam Hereth
Date: 11/1/2018

This .cpp file is responsible for creating the Link List needed to insert and display the 
dna strands from the text file
*************************************/


#include "LL.h"

// Name: LL() - Default Constructor
// Desc: Used to build a new linked list
// Preconditions: None
// Postconditions: Creates a new linked list where m_head and m_tail point to NULL
LL::LL()
{
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
}
// Name: ~LL() - Destructor
// Desc: Used to destruct a new linked list
// Preconditions: There is an existing linked list with at least one node
// Postconditions: A linked list is deallocated (including all dynamically allocated nodes)
// to have no memory leaks!
LL::~LL()
{
  Clear();
}

// Name: InsertEnd
// Preconditions: Takes in a char. Creates new node.
// Requires a linked list
// Postconditions: Adds a new node to the end of the linked list.
void LL::InsertEnd(char data)
{
  Node * head = m_head;
  Node * temp = new Node;
  temp->m_data = data;
  temp->m_next = NULL;
  if(m_head == NULL)
    {
      m_head = temp;
    }
  else
    {
      //goes through the loop and inserts the data into the last  Node
      while(head->m_next != NULL)
	{
	  head = head->m_next;
	}
      head->m_next = temp;
    }
}

// Name: Display
// Preconditions: Outputs the linked list.
// Postconditions: Returns number of nodes displayed.
int LL::Display()
{
  int count = 0;
  if (m_head == NULL)
    {
      cout << "The Linked List is empty" << endl;
    }
  else
    {
      //creates a new temp node that loops through the LL and outputs the data
      Node *temp = m_head;
      while(temp != NULL)
	{
	  cout << temp->m_data << "->";
	  temp = temp->m_next;
	  count++;
	}
       cout << "END" << endl;
    }
  return count;
}

// Name: IsEmpty
// Preconditions: Requires a linked list
// Postconditions: Returns if the linked list is empty.
bool LL::IsEmpty()
{
  if (m_head == NULL)
    {
      cout << "Linked list is empty" << endl;
      return true;
    }
  else
    {
      return false;
    }
}

// Name: SizeOf
// Preconditions: Requires a linked list
// Postconditions: Populates m_size with the total number of nodes and returns m_size
int LL::SizeOf()
{
  Node *temp = m_head;
  int count = 0;
  while(temp != NULL)
    {
      count++;
      temp = temp->m_next;
    }
  //had to create a count and have that equal to m_size because if I did m_size++
  //the code would increase m_size too much and would cause a seg fault.
  m_size = count;
  return m_size;
}

// Name: Clear
// Preconditions: Requires a linked list
// Postconditions: Removes all nodes in a linked list
void LL::Clear()
{
  Node *temp = m_head;
  //iterates through the LL and sets the temp equal to whatever Node m_head is pointing at and
  //sets temp to the next Node and then deletes m_head and then sets head to the temp
  while (m_head != NULL)
    {
      temp = m_head->m_next;
      delete m_head;
      m_head = temp;
    }
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
}

// Name: ReplaceData (works like find and replace)
// Desc: Iterates over the linked list and replaces every *quantity* charFrom with charTo
// For ReplaceData ('A','C', 3) then every third 'A' would be replaced with a 'C'
// Preconditions: Requires a linked list
// Postconditions: Updates a linked list by mutating data based on a frequency
int LL::ReplaceData(char charFrom, char charTo, int frequency)
{
  //checks to see if the LL is empty 
  if (IsEmpty())
    {
      cout << "Empty" << endl;
      return 0;
    }
  Node *temp = m_head;
  int count = 0;
  int total = 0;
  while (temp != NULL)
    {
      if ((temp->m_data) == (charFrom))
	{
	  count++;
	  if (count == frequency)
	    {
	      temp->m_data = charTo;
	      count = 0;
	      total++;
	    }
	}
      temp = temp->m_next;
    }
  return total;
}

// Name: GetData
// Preconditions: Requires a linked list
// Postconditions: Returns the data at a specific node
char LL::GetData(int nodeNum)
{
  Node * temp = m_head;
  int count = 0;
  //iterates through m_dna objects and returns the individual data from each strand
  while(count < nodeNum)
    {
      temp = temp->m_next;
      count++;
    }
  return temp->m_data;
}

// Name: operator<< (Overloaded << operator)
// Preconditions: Requires a linked list
// Postconditions: Returns an ostream with the data from every node separated by ->
ostream &operator<< (ostream &output, LL &myLL)
{
  //outputs the display function 
  output << myLL.Display();
  return output;
}

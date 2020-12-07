/***********************************
File: Sequencer.cpp
Project: CMSC 202 Project 3, Fall 2018
Author: Adam Hereth
Date: 11/1/2018

This code implements the files from the Sequencer.h file. The .cpp file displays the strands,
reads in the file, outputs a menu, calculates the consensus, and mutates the strands
 ***********************************/


#include "Sequencer.h"
// Name: Sequencer (default constructor)
// Preconditions: A linked list (DNA) is available
// Postconditions: A linked list (DNA) where m_head and m_tail points to NULL
// m_size is also populated with SizeOf
Sequencer::Sequencer(string fileName)
{
  m_fileName = fileName;
  readFile();
  mainMenu();
}

// Name:  Sequencer (destructor)
// Preconditions: There is an existing linked list (DNA)
// Postconditions: A linked list (DNA) is deallocated (including nucleotides) to have no memory leaks!
Sequencer::~Sequencer()
{
  //iterates through m_dna vector and creates a LL thats equal to the m_dna index and then
  //deletes that LL
  for(unsigned int i=0;i<m_dna.size();i++)
    {
      LL *remove = m_dna.at(i);
      delete remove;
    }
}

// Name:  DisplayStrands
// Preconditions: At least one linked list is in m_dna
// Postconditions: Displays each linked list (DNA strand) in m_dna
void Sequencer::DisplayStrands()
{
  //outputs the deferenced vector object at each index
  for(int i=0;i<(int)m_dna.size();i++)
    {
      cout << *m_dna.at(i) << endl;
    }
}

// Name:  readFile
// Preconditions: Valid file name of characters (Either A, T, G, or C)
// Postconditions: Populates the LinkedList (DNA)
void Sequencer::readFile()
{
  //create a new LL pointer
  LL *newDNA = new LL;
  ifstream infile;
  int strandNum = 1;
  int count = 0;
  infile.open(m_fileName.c_str());
  char data;
  while(infile >> data)
    {
      //has the new DNA LL call the InsertEnd function and input the char data from the textfile
      //into the newDNA LL.
      newDNA->InsertEnd(data);
      if (infile.peek() == '\n')
	{
	  cout << "Strand " << strandNum << " with " << newDNA->SizeOf() << " nucleotides"<< endl;
	  //had the count = this because Display returned an integer
	  count = newDNA->Display();
	  //pushes the newDNA LL into the m_dna vector
	  m_dna.push_back(newDNA);
	  strandNum++;
	  //create a new LL to keep creating a filling a LL for each strand
	  newDNA = new LL;
	}
    }
  infile.close();
  cout << "File loaded, number of strands is: "  << strandNum-1 << endl;
  delete newDNA;
}

// Name:  mainMenu
// Preconditions: Populated LinkedList (DNA)
// Postconditions: None
void Sequencer::mainMenu()
{
  int menu;
  do
    {
      cout << "What would you like to do?" << endl;
      cout << "1. Display Strands" << endl;
      cout << "2. Use Consensus Tool" << endl;
      cout << "3. Mutate Strands" << endl;
      cout << "4. Exit" << endl;
      cin >> menu;
      switch(menu)
	{
	case 1:
	  {
	    DisplayStrands();
	  }
	  break;
	case 2:
	  {
	    CalculateConsensus();
	  }
	  break;
	case 3:
	  {
	    MutateStrand();
	  }
	  break;
	case 4:
	  {
	    cout << "Thank you" << endl;
	  }
	  break;
	}
    }while(menu != 4);
}

// Name:  CalculateConsensus
// Preconditions: Populated m_dna vector populated with 3 or  more strands
// Postconditions: Creates a  new strand that represents the  most common nuceloti
// at each position
void Sequencer::CalculateConsensus()
{
  //initialize A,G,T,C
  int A=0;
  int G=0;
  int T=0;
  int C=0;
  if(m_dna.size() == 0)
    cout << "no strands loaded" << endl;
  m_consensus = new LL;
  for(int i=0; i<m_dna.at(0)->SizeOf(); i++)
    {
      //want to have the A,G,T,C be re initialized to 0.
      A=0;
      G=0;
      T=0;
      C=0;
      for (int j=0; j<int(m_dna.size());j++)
	{
	  //compares the m_dna vector at the j index of the LL inside m_dna and uses GetData
	  //to find the specific char and compare it to A,T,G,C
	  if(m_dna.at(j)->GetData(i) == 'A')
	    A++;
	  if(m_dna.at(j)->GetData(i) == 'T')
	    T++;
	  if(m_dna.at(j)->GetData(i) == 'G')
	    G++;
	  if(m_dna.at(j)->GetData(i) == 'C')
	    C++;
	}
      //since the char are integers they can be compared and if the char meets the if statements
      //parameters the m_consensus vector inserts that char into it.
      if(A>G and A>T and A>C)
	m_consensus->InsertEnd('A');
      if(T>G and T>A and T>C)
	m_consensus->InsertEnd('T');
      if(G>A and G>T and G>C)
	m_consensus->InsertEnd('G');
      if(C>A and C>T and C>G)
	m_consensus->InsertEnd('C');
    }
  cout << *m_consensus << endl;
  delete m_consensus;
}

// Name:  MutateStrand
// Preconditions: Populated LinkedList (DNA)
// Postconditions: DNA strand is mutated from a specific nucleotide (G,C,A,T) to another
//valid nucleotide (G,C,A,T) at a given interval.
void Sequencer::MutateStrand()
{
  char charFrom;
  char charTo;
  int frequency;
  cout << "What would you like to replace? (A,T,G,C)" << endl;
  cin >> charFrom;
  while(charFrom != 'A' and charFrom != 'T' and charFrom != 'G' and charFrom != 'C')
    {
      cout << "Invalid; please try again (A,T,G,C)" << endl;
      cin >> charFrom;
    }
  cout << "What would you like to change to? (A,T,G,C)" << endl;
  cin >> charTo;
  while(charFrom != 'A' and charFrom != 'T' and charFrom != 'G' and charFrom != 'C')
    {
      cout << "Invalid; please try again (A,T,G,C)" << endl;
      cin >> charTo;
    }
  cout << "What would you like the frequency to be? (1-5)" << endl;
  cin >> frequency;
  while(frequency > 5 || frequency < 1)
    {
      cout << "Invalid; please try again (1-5)" << endl;
      cin >> frequency;
    }
  //loops through m_dna vector at the specific index and replaces charFrom to charTo and uses
  //the user input for frequency to determine the amount between the switch
  for(unsigned int i = 0; i < m_dna.size(); i++)
    {
      m_dna.at(i)->ReplaceData(charFrom,charTo,frequency);
    }
}

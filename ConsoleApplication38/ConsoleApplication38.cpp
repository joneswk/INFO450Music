#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 100;


//Music class
class music
{
	string songName;
	music* next;

public:
	music() {}
	music(string song) 
	{
		songName = song;
		next = NULL;
	}
	friend class linkedList;
};

//Class linked list
class linkedList
{
	music* head;
	music* tail;
public:
	linkedList();
	void addNodetoHead(music *ptr);
	void addNodeToEnd(music *ptr);
	int insertAfter(music *newnode, string i);
	int RemoveNode(string i);
	void showList(); //Transverse a list
	int readList(string filename);
	int saveList(string filename);	
};

//Linked List constructor 
linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}
void linkedList::addNodetoHead(music *ptr) 
//For your program node=music
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		ptr->next = head;
		head = ptr;
	}
}

void linkedList::addNodeToEnd(music* ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

int linkedList::insertAfter(music *newnode, string i) 
//Extra Credit
{

	music *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->songName == i) // we found the node to insert after
		{
			newnode->next = ptr->next;
			ptr->next = newnode;
			if (tail == ptr) // repoint tail if we added to end
				tail = newnode;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

int linkedList::RemoveNode(string i) 
{
	music *ptr = head;
	if (ptr == NULL)  // empty list
		return -1;

	// if node is at the head
	if (head-> songName == i)
	{
		//if only 1 node in the list
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (ptr->next)->songName == i)
		{
			if (tail == ptr->next)
				tail = ptr;
			music *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;

}

//Traverse, Skip, Delete, Node from list
void linkedList::showList()
{
	music* ptr = head;
	music* prev = NULL;
	string choice;
	int amount;

	cout << "**** My Music List **** " << endl;
	if (head == NULL) //Empty List
	{
		cout << "List is empty!" << endl;
		return;
	}

	//If only 1 node in the list
	if (head == tail)
	{
		head = NULL;
		tail = NULL;
	}
	else
		head = head->next;

	while (ptr != NULL)
	{
		cout << "Welcome To Razor Blade Music!!!!!!!!" << endl;
		cout << "The song is " << ptr->songName << " by " << " [P]lay, [S]kip,[D]elete, or [Q]uit? ";
		getline(cin, choice);

		if (choice == "p" || choice == "P")
		{
			cout << "---------\n";
			cout << "Playing: ";
			ptr->songName;
			cout << "---------\n";
			if (ptr == tail)
			{
				ptr = head;
			}
			else
			{
				ptr = ptr->next;
			}
		}
		//Skip song on list
		if (choice == "s" || choice == "S")
		{
			cout << "How many songs you would you like to skip?" << endl;
			cin >> amount;
			cin.clear();
			cin.ignore();
			cout << "---------\n";
			for (int i = 1; ptr && i <= amount; i++)
			{
				cout << "Skipping: ";
				ptr->songName;

				prev = ptr;
				if (ptr == tail)
				{
					ptr = head;
				}
				else
				{
					ptr = ptr->next;
				}
			}
			cout << "---------\n";
		}

		//Delete song from list
		if (choice == "D" || choice == "d")
		{
			if (ptr->next && (ptr->next)->songName == ptr->songName)
			{
				if (tail == ptr->next)
					tail = ptr;

				music* tbd = ptr->next;
				ptr->next = (ptr->next)->next;
				delete tbd;
			}
			cout << "---------\n";
			cout << "Deleting: ";
			ptr->songName;
			cout << "---------\n";

			if (ptr == tail)
			{
				ptr = head;
			}
			else
			{
				ptr = ptr->next;
			}
		}

		//Quit List
		if (choice == "Q" || choice == "q")
		{
			cout << "That's all folks,Thanks for listening on Razor Blade Music Ciao!!! " << endl;
			break;
		}
	}
}

int linkedList::readList(string filename)
{
	int count = 0;
	string sName;
	ifstream infile(filename, ios::in);
	if (!infile)
	{
		cout << "File could not be opened for reading" << endl;
		return READERROR;
	}

	while (!infile.eof())
	{
		getline(infile, sName);
		if (!sName.empty())
		{
			if (count == 0)
			{
				music *newnode = new music(sName);
				count++;
			}
			addNodeToEnd(new music(sName));
			count++;
		}
	}

	infile.close();
	return 0;
}

int linkedList::saveList(string filename) 
//Enter function to save list to the .txt file
{
	ofstream output(filename, ios::trunc);
	if (!output)
	{
		cout << "Could not write to file!" << endl;
		return WRITEERROR;
	}
	if (output)
	{
		music *ptr;
		ptr = head;
		while (ptr != NULL)
		{
			output << ptr->songName << endl;
			ptr = ptr->next;
		}
	}
	output.close();
	return 0;
}

int main()
{
	string filename;
	linkedList *mylist = new linkedList();
	cout << "What's Going On Guys, Before using the Razor Blade MP3 Music Platform, What is the full file pathname for your music library? (Please Enter Below)" << endl;
	getline(cin, filename);
	mylist->readList(filename);
	mylist->showList();
	mylist->saveList(filename);
	return 0;
}
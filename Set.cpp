#include "Set.h"


Set::Set()   //Constructor Definition
{
	m_size = 0; //Initialize size to 0
	head = new Node;  //New node
	head->next = head;  //Next and prev point to each other
	head->prev = head;
}

Set::Set(const Set & s)  //Copy Constructor definition
{
		this->m_size = s.size();  //Assign new size
		this->head = new Node;  //Dynamically allocate new node
		this->head->next = head;  //Assign the head so it points to itselt
		this->head->prev = head;
		for (Node * p = s.head->next; p != s.head; p = p->next) //Feed through one we're copying
		{
			Node * newNode = new Node;  //Create new node
			newNode->m_data = p->m_data;   //Copy data
			(head->prev)->next = newNode;  //Insert it in and adjust 4 pointers
			newNode->prev = head->prev;
			newNode->next = head;
			head->prev = newNode;
		}
	}

Set::~Set()   //Destructor definition
{
	
	for (int i = 0; i < m_size + 1; i++)
	{
		Node * n = head;
		head = head->prev;
		head->next = nullptr;
		n->prev = nullptr;
		delete n;
	}
} 

Set& Set::operator=(const Set & s) //Assignment operator Definition
{
	if (this != &s)  //If they are not already equal
	{
		delete this->head;   //Delete old head
		this->m_size = s.size();  //Assign new size
		this->head = new Node;  // Dynamically allocated
		this->head->next = head; //Set it so it points to itself (like in constructor)
		this->head->prev = head;
		for (Node * p = s.head->next; p != s.head; p = p->next)  //Loop through s
		{
			Node * newNode = new Node;  //Create new node
			newNode->m_data = p->m_data;  //Give it the data in s
			(head->prev)->next = newNode;  //Add to to the end of the list
			newNode->prev = head->prev;  //Adjust the 3 other pointers
			newNode->next = head;
			head->prev = newNode;
		}
	}
	return *this;  //Return a dereference to calling obj
}  

bool Set::empty() const   //Empty Definition
{
	bool answer = false;
	if (m_size == 0)   //If size is 0, it's obviously empty
		answer = true;
	return answer;
}

int Set::size() const   //Size definition
{
	return m_size;   //Since size is a private member, we can just return it
}

bool Set::insert(const ItemType& value)
{
	bool answer = false;
	int count = 0;
	for (Node* p = head->next; p != head; p = p->next)  //Go through set
	{
		if (p->m_data != value)  //If it's not equal, make a counter
			count++;
	}

	if (count == m_size)
	{
		answer = true;     //Changes answer to true
		Node * newFam = new Node;  //Create new node, dynamically allocated
		newFam->m_data = value;  //Set the new node's value equal to the insert
		(head->prev)->next = newFam; //Assign the last one in the list's next to the new one
		newFam->prev = head->prev; //Assign new node's prev to head's prev
		newFam->next = head;  //Assign new node's next to head
		head->prev = newFam; //Assign previous to head
		m_size++;  //increase the size of the set
	}
	return answer;   //Returns the correct bool
}

bool Set::erase(const ItemType& value)  //Erase definition
{
	bool answer = false;
	for (Node* p = head->next; p != head; p = p->next)  //Go through set
	{
		if (p->m_data == value) //If it's equal, erase it
		{
			answer = true;  //Answer returns true
			(p->prev)->next = p->next; //Previous' next points to p's next
			(p->next)->prev = p->prev;  //p's Next points to p's previous
			m_size--; //Decrease size
			delete p;  //Delete node
			break; //Break out of loop
		}
	}
	return answer;
}

bool Set::contains(const ItemType& value) const  //Contains definition
{
	bool answer = false;
	for (Node* p = head->next; p != head; p = p->next)  //Go through set
	{
		if (p->m_data == value) //If it's equal, break
		{
			answer = true;
			break;
		}
	}
	return answer;

}

bool Set::get(int pos, ItemType& value) const
{
	bool answer = false;

	if (0 <= pos && pos < m_size)  //If greater than 0 and less than size
	{
		for (Node* p = head->next; p != head; p = p->next)  //Nested for loop
		{
			int count = 0;
			for (Node * n = head->next; n != head; n = n->next)
				if (p->m_data > n->m_data) //If greater than something, add to count
					count++;
			if (count == pos)   //If count is equal to the position, then add
			{
				value = p->m_data;
				answer = true;
				break;
			}
		}
	}
	return answer;   //Return answer
}

void Set::swap(Set& other)   //Swap definition  
{
	Node * temp;  //Create temp pointer
	temp = other.head;  //Head points to other's dummy
	other.head = this->head;
	this->head = temp;
	int tsize = this->m_size;   //Change sizes of the lists
	this->m_size = other.m_size;
	other.m_size = tsize;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
	Set temp;
	for (int i = 0; i < s1.size(); i++)  //Feed through first set
	{
		ItemType x;  //Create variable to carry from get() to inset()
		s1.get(i, x); //Get dat biotch
		temp.insert(x);  //Insert dat biotch
	}

	for (int i = 0; i < s2.size(); i++)  //Feed through second set
	{
		ItemType x;  //Create variable to carry from get() to inset()
		s2.get(i, x); //Get dat biotch
		temp.insert(x);  //Insert dat biotch
	}
	result = temp;
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
	Set temp = s1;  //Create temp set
	for (int i = 0; i < s2.size(); i++)  //Feed through set 2
	{
		ItemType x;  //Create x
		s2.get(i, x);  //Retrieve values
		temp.erase(x); //Stick it in temp
	}
	result = temp;  //Result is now temp
}

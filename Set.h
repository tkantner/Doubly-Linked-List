#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>
using namespace std;

typedef string ItemType;

class Set
{
public:
	Set();   
	Set(const Set & s); //Copy Constructor
	~Set();   //Destructor
	Set& operator=(const Set & s);   //Assignment operator
	bool empty() const; 
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int pos, ItemType& value) const;
	void swap(Set& other);
private:
	int m_size;   //The size of the linked list
	struct Node    //Nodes in the list
	{
		ItemType m_data;   //Data of the node
		Node * prev;       //Pointer to previous node
		Node * next;       //Pointer to next node
	};
	Node * head;  //Pointer to start
};
void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);
#endif // !SET_DEFINED

#include<iostream>
#include<stdexcept>

class List;

class ListNode {
	friend List;
public:
	ListNode() :_data(0), _next(NULL) {}
	void del();
private:
	int _data;
	ListNode* _prev;
	ListNode* _next;
};

void ListNode::del() {
	ListNode* q=this->_prev;
	q->_next=this->_next;
	if(this->_next){
		this->_next->_prev=q;
	}
	delete this;
}

class List {
public:
	List();
	~List();
	void Creat();
	bool Search(int data);
	void PushBack(int data);
	
	ListNode* GetFirst() { return _first; }
	List* Compare(List* li);
	void Print();
private:
	ListNode* _first;
	ListNode* _last;
};

List::List()
{
	_first = new ListNode;
	_first->_data = 0;
	_first->_prev = NULL;
	_first->_next = NULL;
	_last = _first;
}

List::~List()
{
	ListNode* p = _first;
	while (p != NULL)
	{
		ListNode* q = p;
		p = p->_next;
		delete q;
	}
	return;
}

void List::Creat()
{
	int data;
	std::cin >> data;
	ListNode* p = _first;
	while (std::cin.good() && data != -1)
	{
		ListNode* q = new ListNode;
		q->_data = data;
		p->_next = q;
		q->_prev = p;
		p = q;
		std::cin >> data;
	}
	if(!std::cin.good())
		throw std::invalid_argument("Wrong Input!");
	p->_next = NULL;
	_last = p;
	return;
}

void List::PushBack(int data)
{
	ListNode* p = new ListNode;
	p->_data = data;
	p->_next = NULL;
	_last->_next = p;
	_last = p;
	return;
}

bool List::Search(int data)
{
	ListNode* p = _first->_next;
	while (p->_data != data)
	{
		if (p->_next != NULL)
			p = p->_next;
		else return false;
	}
	if (p != NULL)
	{
		if (p->_data == data){
			p->del();
			return true;
		}
	}
	return false;
}

List* List::Compare(List* li)
{
	List* newList = new List;
	ListNode* p = _first->_next;
	while (p != NULL)
	{
		if (li->Search(p->_data))
			newList->PushBack(p->_data);
		p = p->_next;
	}
	return newList;
}

void List::Print()
{
	ListNode* p = _first->_next;
	if (p == NULL)
	{
		std::cout << "NULL";
		return;
	}
	while (p != NULL)
	{
		std::cout << p->_data << " ";
		p = p->_next;
	}
	return;

}

int main(void)
{
	List li1;
	List li2;
	std::cout<<"Please enter the first list(end with -1):";
	li1.Creat();
	std::cout<<"Please enter the second list(end with -1):";
	li2.Creat();
	List* p = li1.Compare(&li2);
	std::cout<<"The intersection of two linked lists is:";
	p->Print();
	system("pause");
	return 0;
}
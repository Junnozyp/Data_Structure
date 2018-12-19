#include<iostream>
#include<cmath>
#include<cassert>

using namespace std;

template <class T>
struct Node
{
	T _data;
	Node<T> *next;
	Node<T> *prev;
};

template <class T>
class Linklist
{
private:
	Node<T> * head;
public:
	Linklist();
	void pushback(T x);
	void pushfront(T x);
	void popback();
	void popfront();
	Node<T> * find(T x);
	void insert(Node<T> * pos, T x);
	void erase(Node<T> * pos);
	int use_count();
	void display();
	Node<T> * Re_position(int i) {
		Node<T> * p = head;
		int n = 0;
		while (n++< i-1)p = p->next;
		return p;
	}
	~Linklist();


};
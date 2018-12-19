#include"Linklist.h"
#include<string>

template <class T>
Linklist <T> ::Linklist()
{
	head = NULL;
}

template <class T>
Linklist <T> ::~Linklist()
{
	Node<T> * cur = head;
	Node<T> * Next = cur->next;
	while (cur != NULL)
	{
		
		delete cur;
		cur = Next;
		if (cur != NULL)Next = Next->next; //逐个删除
		else
			break;
	}
}
template <class T>
void Linklist <T> ::pushback(T x)   //将元素置于链尾
{
	Node <T>  * p = new Node<T>[sizeof(Node<T>)];
	p->_data = x;
	p->next = NULL;
	if (head == NULL)
	{
		head = p;
		p->prev = NULL;
	}
	else
	{
		Node<T> * cur = head;
		while (cur->next)
		{
			cur = cur->next;//为空的前一个
		}
		cur->next = p;
		p->prev = cur;
	}
}

template <class T>
void Linklist <T> ::display()
{
	
	Node<T> * cur = head;
	while (cur != NULL)
	{
		cout <<cur->_data <<"  ";
		cur = cur->next;
		
	}
}

template <class T>
void Linklist <T> ::pushfront(T x)   //将元素置于链头
{
	Node<T> * tmp = new Node<T>[sizeof(Node<T>)];

	if (head == NULL)
	{
		tmp->_data = x;
		head = tmp;
		head->next = head->prev = NULL;
	}
	else
	{
		tmp->_data = head->_data;
		tmp->next = head->next;
		tmp->prev = head;
		head->next = tmp;
		tmp->next->prev = tmp;
		head->_data = x;
	}
}

template <class T>
void Linklist <T> ::popback()   //删除链尾
{
	if (head != NULL)
	{
		Node<T> * cur =head;
		Node <T> * pre = NULL;

		while (cur->next)
		{
			pre = cur;
			cur = cur->next;
		}      //找到链尾

		delete[] cur;
		cur = NULL;
		pre->next = NULL;
	}
}


template <class T>
void Linklist<T> ::popfront()   //删除链头
{
	if (head != NULL)
	{
		if (head->next == NULL)
		{
			delete[] head;
			head = NULL;
		}
		else
		{
			Node<T> * del = head;
			head = head->next;
			delete[] del;
			del = NULL;
		}
		
	}

}

template <class T>
int  Linklist<T> ::use_count()
{
	int count = 0;
	Node<T>* cur = head;
	while (cur)
	{
		cur = cur->next;
		count++;
	}
	return  count;
}

template <class T>
Node<T>* Linklist<T> ::find(T x)
{
	if (head == NULL)
		return NULL;
	else
	{
		Node<T>* cur = head;
		while (cur)
		{
			if (x == cur->_data)return cur;
			cur = cur->next;

		}
		cerr << "Not Found!" << endl;
		return NULL;
	}
}

template <class T>
void Linklist<T> ::insert(Node<T> * pos, T x)
{
	assert(pos);
	if (head == NULL)return;
	else
	{
		Node<T>* cur = head;
		if (head == pos)
			pushfront(x);
		else
		{
			while (cur)
			{
				if (cur == pos)
				{
					Node<T>* temp = new Node<T>[sizeof(Node<T>)];
					temp->_data = cur->_data;
					temp->next = cur->next;
					temp->prev = cur;
					cur->_data = x;
					cur->next = temp;
					temp->next->prev = temp;
					return;
				}
				cur = cur->next;
			}
			cout << "No found!" << endl;
		}
	}
}


int main(void)
{

	Linklist<int> ls;
	ls.pushback(1);
	ls.pushback(2);
	ls.pushback(3);
	cout << "1:";
	ls.display();
	cout << endl;

	ls.pushfront(0);
	ls.pushfront(100);
	
	cout << "2:";
	ls.display();
	cout << endl;

	cout << "3:";
	ls.insert(ls.Re_position(2), 10);
	ls.display();
	cout << endl;

	Node<int> * ret = ls.find(0);
	if (ret != NULL)
		cout << ret->_data << endl;
	cout << ls.use_count() << endl;
	/*ls.popback();
	cout << "3:";
	ls.display();
	cout << endl;

	ls.popfront();
	cout << "4:";
	ls.display();
	cout << endl;

	cout << ls.use_count() << endl;
	ls.pushback(1);
	ls.pushback(2);
	ls.pushback(3);
	ls.pushback(4);
	cout << "5:";
	ls.display();
	cout << endl;

*/

	return 0;
}


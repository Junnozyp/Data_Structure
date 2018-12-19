#ifndef STACK_H_
#define STACK_H_
#include<string>
#include<iostream>
using namespace std;

//template<typename T>
//struct Node {
//	
//	Node<T> *next;
//	T data;
//	
//};


template<class T>
class Stack {
	enum { Max = 100 };
	int stacksize;
	T * items;
	int top;
public:
	explicit Stack(int ss = Max);
	Stack(const Stack & st);
	~Stack() { delete[] items; }

	bool isempty()const { return top == 0; }
	bool isfull()const { return top == stacksize; }
	bool push(const T & item);
	bool pop(T & item);
	T pop();
	T Gettop(T & item) { return items[top]; }
	T Gettop() { return items[top]; }
	Stack & operator =(const Stack & st);
	void Show()const;
	void Clear(int n);  //清除并更新
	template<class T>
	friend ostream & operator << (ostream & os, const Stack<T> & s);
};

template <class T>
Stack<T>::Stack(int ss) :stacksize(ss), top(0) {
	items = new T[stacksize];        //数组指针用法
}

template <class T>
Stack<T>::Stack(const Stack & st)
{
	stacksize = st.stacksize;
	top = st.top;
	items = new T[stacksize];
	for (int i = 0; i < stacksize; i++)
		items[i] = st.items[i];
}

template <class T>
bool Stack<T>::push(const T & item)
{
	if (top < stacksize)
	{
		items[top++] = item;
		return true;
	}
	else
		return false;
}

template <class T>
bool Stack<T>::pop(T & item)
{
	if (top > 0)
	{
		item = items[--top];
		return true;
	}
	else
		return false;
}

template<class T>
inline T Stack<T>::pop()
{
	T value=0;
	if (top > 0)
	{
		value = items[--top];
		return value;
	}
	else
	{
		exit(1);
	}
}

template <class T>
Stack<T> & Stack<T>::operator=(const Stack<T> & st)
{
	if (this == &st)return;
	delete[]items;
	stacksize = st.stacksize;
	top = st.top;
	items = new T[stacksize];
	for (int i = 0; i < stacksize; i++)
		items[i] = st.items[i];
	return *this;
}
template <class T>
void Stack<T>::Show()const
{
	for (int i = 0; i < top; i++)
		cout << items[i] << " ";
	cout << endl;
}
template <class T>
ostream & operator <<(ostream & os, const Stack<T> & st)
{
	if (st.isempty())
	{
		cout << "The stack is empty\n";
		return os;
	}
	for (int i = 0; i < st.top; i++)
		os << st.items[i] << " ";
	os << endl;
	return os;
}

template <class T>
void Stack<T>::Clear(int n)
{
	Stack<T>::~Stack();
	stacksize = n;

	items = new T[stacksize];
	top = 0;
}
//给运算符评定权值
int Assess(const char c)
{
	int value=0;
	switch (c)
	{
		case '+':
		case'-':
		{
			value = 1;
			break;
		}
		case'*':
		case'/':
		{
			value = 2;
			break;
		}
		case'(':
		{
			value = 0;
			break;
		}
		case')':
		{
			value = 4;
			break;
		}
	}
	return value;
}

//将中缀表达式转换成后缀表达式
void Inorder_to_Postorder(const char  * st,int size)
{
	cout << "Postorder expression : \n";
	Stack<char> save(100);
	int value = 0,value_save=0;
	for (int i = 0; i < size; i++)
	{
		if (st[i] >= '0'&&st[i] <= '9')
		{
			cout << st[i] << ' ';
			cout << ' ';
		}
		else
		{
			
			value = Assess(st[i]);
			if (value != 4 && (value == 0 || value > value_save))  //是‘（’ 或者高级运算符的话进栈
			{
				save.push(st[i]);
				value_save = value;
			}
			else if (value <= value_save) //低级运算符，先出栈，再进栈
			{
				char temp;
				save.pop(temp);
				cout << temp << ' ';
				save.push(st[i]);
				value_save = value;
			}
			if (value == 4)
			{
				for (char temp;;)
				{
					save.pop(temp);
					if (temp != '(')
						cout << temp << ' ';
					else
					{
						
						char cc;
						save.Gettop(cc);
						value_save=Assess(cc);
						break;
					}
				}
			}
		}
		
	}
	save.Show();
}
//单步计算
int single_cal(int fir, int rear, const char operator_)
{
	switch (operator_)
	{
	case'*':
		return fir * rear;
	case'/':
		return fir / rear;
	case'+':
		return fir + rear;
	case'-':
		return fir - rear;
	}

}
//后缀表达式求值
void Calculate_for_Post(const char  * st, int size)
{
	Stack<int> calcul(100);
	for (int i = 0; i < size; i++)
	{
		if (st[i] >= '0'&&st[i] <= '9')
			calcul.push(st[i]-'0');
		else
		{
			
			int sec = calcul.pop();
			int fir = calcul.pop();
			calcul.push(single_cal(fir, sec, st[i]));//单步计算

		}
	}
	cout << "The Result: " << calcul.pop() << endl;
}
//中缀表达式求值
void Calculate_for_Inorder(const char  * st, int size)
{
	Stack<int> calcul_(100);
	Stack<char>operator_(100);

	int value=0, value_save=0;   //当前运算符的权值，栈顶元素的权值
	for (int i = 0; i < size; i++)
	{
		if (st[i] >= '0'&&st[i] <= '9')
		{
			calcul_.push(st[i]-'0'); //存入对应整数
		}
		else
		{
			value = Assess(st[i]);
			if (value != 4 && (value == 0 || value > value_save))
			{
				operator_.push(st[i]);
				cout << st[i];
			}
			else if (value == 4)  //')'
			{
				int sec = calcul_.pop();
				int fir = calcul_.pop();
				calcul_.push(single_cal(fir, sec, operator_.pop()));
				cout << fir << ' ' << sec << calcul_.Gettop() << endl;
				for (char temp = operator_.pop(); temp != '(';)//两个运算符在一对括号里
				{
					int sec = calcul_.pop();
					int fir = calcul_.pop();
					calcul_.push(single_cal(fir, sec, operator_.pop()));
					cout << fir << ' ' << sec << calcul_.Gettop()<<endl;
					temp= operator_.pop();
					
				}
			}
			else
			{
				
				int sec = calcul_.pop();
				int fir = calcul_.pop();
				calcul_.push(single_cal(fir, sec, operator_.pop()));
			
			}
		}
	}
	if (!operator_.isempty())
	{
		int sec = calcul_.pop();
		int fir = calcul_.pop();
		calcul_.push(single_cal(fir, sec, operator_.pop()));

	}
	//((5-1)*3)+8
	//((5 - 1)*(4 - 1 * 3)) + 5
	cout << "The Result: " << calcul_.pop() << endl;
}
#endif // !STACK_H_


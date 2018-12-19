#ifndef QUEUE_LINKED_H_
#define QUEUE_LINKED_H_

#include"Pre.h"
// 索引异常机制——超出数组边界等
class Out_Of_Bounds :public exception
{

public:
	string  Type_ex = "none";
	const char * what() { return "out of the range of present part!\n"; }
	Out_Of_Bounds(const char  * type);
	~Out_Of_Bounds()
	{

	}
};

Out_Of_Bounds::Out_Of_Bounds(const char * type)
{
	Type_ex = type;
}
template <typename T>
struct Node
{
	T data;
	Node *next;
};
template<class T>
class QueueLinked
{
private:
	Node<T> * front;
	Node <T> * rear;
	int size;
	int Maxsize = 10000;
public:
	QueueLinked() { rear = front = 0; }   // 不能复制NULL，因为是空指针但是可以是0；
	~QueueLinked();
	bool isEmpty()const
	{
		return ((front) ? false : true);
	}
	bool isFull()const { return size == Maxsize; }
	T First()const;
	T Last()const;
	QueueLinked<T> & Add(const T & item);   //队尾添加新元素
	QueueLinked<T> & Delete(T & item);    //队头删除元素
										  //模板类中的友元函数声明
	template<typename T>
	friend ostream & operator<<(ostream & os, const QueueLinked<T>&  Q);
	bool Unique();
	int QueueSize()const { return size; }
};


template<class T>
QueueLinked<T> &QueueLinked<T>::Add(const T & item)
{
	if (isFull())throw Out_Of_Bounds("The queue is ful!\n");
	Node <T> * temp = new Node<T>;
	temp->data = item;
	temp->next = NULL;

	if (front)rear->next = temp;
	else
		front = temp;

	rear = temp;
	size++;
	return *this;
}
template<class T>
inline QueueLinked<T>& QueueLinked<T>::Delete(T & item)
{
	// TODO: 在此处插入 return 语句
	if (isEmpty())throw Out_Of_Bounds("The queue is empty!\n");
	item = front->data;
	Node <T>*temp = front;
	front = front->next;
	delete temp;
	size--;
	return *this;
}
template<class T>
inline bool QueueLinked<T>::Unique()
{
	if (isEmpty())throw Out_Of_Bounds_("The queue is empty!\n");
	unsigned char unique[1000] = { 0 }; // 8*1000位
	int block = 0, position = 0;
	Node <T> * front_ = front;  //伪指针
	Node<T> * rear_ = front_;//伪指针
	for (; rear_; rear_ = rear_->next)
	{
		block = rear_->data / 8;//确定在哪个位块里
		position = rear_->data % 8; //确定在块里的第几位
		if ((unique[block] & (unsigned char)pow(2, position)) << (8 - position - 1) >> position)
		{
			front_->next = rear_->next;  //delete the element;
			size--;
			continue;  //当发现重复时进行物理上删除后不再对front进行操作
		}
		else
		{

			unique[block] = unique[block] | (unsigned char)pow(2, position);
		}
		front_ = rear_;
		// cout << block<<"  :"<<bitset<sizeof(unsigned char) * 8>(unique[block]) << endl;

	}
	return true;
}
template<class T>
inline QueueLinked<T>::~QueueLinked()
{
	Node<T> * temp;
	while (front)
	{
		temp = front->next;
		delete front;
		front = temp;
	}

}

template<class T>
inline T QueueLinked<T>::First() const
{
	if (isEmpty())throw Out_Of_Bounds("The queue is empty!\n");
	return front->next;
}

template<class T>
inline T QueueLinked<T>::Last() const
{
	if (isEmpty())throw Out_Of_Bounds("The queue is empty!\n");
	return rear->data;
}

template<typename T>
inline ostream & operator<<(ostream & os, const QueueLinked<T>& Q)
{
	// TODO: 在此处插入 return 语句
	Node <T>*temp = Q.front;
	while (temp)
	{
		os << temp->data << " ";
		temp = temp->next;
	}
	return os;

}
#endif // !QUEUE_LINKED_H_



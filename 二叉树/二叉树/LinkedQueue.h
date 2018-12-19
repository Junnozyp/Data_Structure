#ifndef QUEUE_LINKED_H_
#define QUEUE_LINKED_H_

#include"Pre.h"
// �����쳣���ơ�����������߽��
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
	QueueLinked() { rear = front = 0; }   // ���ܸ���NULL����Ϊ�ǿ�ָ�뵫�ǿ�����0��
	~QueueLinked();
	bool isEmpty()const
	{
		return ((front) ? false : true);
	}
	bool isFull()const { return size == Maxsize; }
	T First()const;
	T Last()const;
	QueueLinked<T> & Add(const T & item);   //��β�����Ԫ��
	QueueLinked<T> & Delete(T & item);    //��ͷɾ��Ԫ��
										  //ģ�����е���Ԫ��������
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
	// TODO: �ڴ˴����� return ���
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
	unsigned char unique[1000] = { 0 }; // 8*1000λ
	int block = 0, position = 0;
	Node <T> * front_ = front;  //αָ��
	Node<T> * rear_ = front_;//αָ��
	for (; rear_; rear_ = rear_->next)
	{
		block = rear_->data / 8;//ȷ�����ĸ�λ����
		position = rear_->data % 8; //ȷ���ڿ���ĵڼ�λ
		if ((unique[block] & (unsigned char)pow(2, position)) << (8 - position - 1) >> position)
		{
			front_->next = rear_->next;  //delete the element;
			size--;
			continue;  //�������ظ�ʱ����������ɾ�����ٶ�front���в���
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
	// TODO: �ڴ˴����� return ���
	Node <T>*temp = Q.front;
	while (temp)
	{
		os << temp->data << " ";
		temp = temp->next;
	}
	return os;

}
#endif // !QUEUE_LINKED_H_



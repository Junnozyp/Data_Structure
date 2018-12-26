#pragma once

#include"Prec.h"
#include"Exception_my.h"
template<class T>
class MaxHeap
{
private:
	int CurrentSize, Maxsize;
	T * heap;
	
public:
	MaxHeap(int MaxHeapSize = 100);
	~MaxHeap()
	{
		Deactivate();  //ֱ��ɾ��heap�ᵼ���ڴ���ʴ��� ��ʼ���н�һ���������heap
	}
	int Size()const { return CurrentSize; }
	T Max()
	{
		if (CurrentSize == 0)Out_Of_Bounds("There is no number in the heap!\n");
		return heap[1];//�������±�Ϊ1��Ԫ��Ϊ���ڵ�
	}
	bool isEmpty()const { return CurrentSize == 0; }
	bool isFull()const { return CurrentSize == Maxsize; }
	MaxHeap<T> & Insert(const T x); //���ѵĲ���
	MaxHeap<T> & DeleteMax(const T x);
	void Initialize(T a[], int size, int Arraysize);
	void Show()const {
		for (int i = 1; i <= CurrentSize; i++)
			cout << heap[i] << " ";
		cout << endl;
	}
	void Deactivate() { heap = 0; }
	MaxHeap<T> & ChangeMax(const T x);
};

template<class T>
inline MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
	Maxsize = MaxHeapSize;
	heap = new T[Maxsize+1];
	CurrentSize = 0;
}

template<class T>
inline MaxHeap<T>& MaxHeap<T>::Insert(const T  x)
{
	// TODO: �ڴ˴����� return ���	
	//��x�嵽�����У�������ĩ�˲��룬Ȼ��ͨ���Ƚϲ����ϸ�
	//ʱ�临�Ӷ�Ϊlogn
	if (isFull())Out_Of_Bounds("The Heap is already full!\n");

	int i = ++CurrentSize;
	while (i != 1 && x > heap[i / 2])
	{
		//���ܰ�x����heap��i��
		heap[i] = heap[i / 2];
		i /= 2;
	}
	//�ҵ�Ӧ�ò����λ��
	heap[i] = x;
	return *this;

}

template<class T>
inline MaxHeap<T>& MaxHeap<T>::DeleteMax(const T x)
{
	// TODO: �ڴ˴����� return ���
	//�����Ԫ�ط���x�����Ӷ���ɾ�����Ԫ��
	//�ٶ�����Ԫ�ط�����ڵ㣬�����³����ҵ���÷ŵ�λ��
	if(isEmpty())Out_Of_Bounds("There is no number in the heap!\n");

	x = heap[1];
	//�ع���
	T target = heap[CurrentSize--];
	//�Ӹ���ʼ��Ѱ�Һ��ʵ�λ��
	int i = 1;  //�ѵĵ�ǰ�ڵ�
	int next_i = 2;//i�ĺ���
	while (next_i <= CurrentSize) {
		if (next_i < CurrentSize&&heap[next_i] < heap[next_i + 1])next_i++;  //Ѱ�Ҹýڵ����ĺ���

		//���ڵ���亢�Ӵ�����Է���ֱ���˳�
		if (target >= heap[next_i])break;

		//С���亢��
		heap[i] = heap[next_i];//����������
		i = next_i;//����һ��
		next_i *= 2;
	}
	heap[i] = target;

	return *this;

}

//�ı����ѵĶ����������������������µ���

template<class T>
inline MaxHeap<T>& MaxHeap<T>::ChangeMax(const T x)
{
	if (isEmpty())Out_Of_Bounds("There is no number in the heap!\n");

	
	//�ع���
	T target =x;
	heap[1] = x;
	//�Ӹ���ʼ��Ѱ�Һ��ʵ�λ��
	int i = 1;  //�ѵĵ�ǰ�ڵ�
	int next_i = 2;//i�ĺ���
	while (next_i <= CurrentSize) {
		if (next_i < CurrentSize&&heap[next_i] < heap[next_i + 1])next_i++;  //Ѱ�Ҹýڵ����ĺ���

																			 //���ڵ���亢�Ӵ�����Է���ֱ���˳�
		if (target >= heap[next_i])break;

		//С���亢��
		heap[i] = heap[next_i];//����������
		i = next_i;//����һ��
		next_i *= 2;
	}
	
	heap[i] = target;

	return *this;
}
template<class T>
inline void MaxHeap<T>::Initialize(T a[], int size, int ArraySize) //size�����������Ԫ�ظ�����ArraySize�������������ɸ���
{
	//�����ѳ�ʼ��Ϊ����a
	delete[]heap;
	heap = a;
	CurrentSize = size;
	Maxsize = ArraySize;

	//����һ������
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i];//�����ĸ������һ���������Ľڵ�

		//Ѱ�ҷ���y��λ��
		int c = 2 * i;//c�ĸ��ڵ�ΪĿ��λ��
		while (c <= CurrentSize)
		{
			if (c < CurrentSize&&heap[c] < heap[c + 1])c++;

			//�ܰ�y����heap��c/2����
			if (y >= heap[c])break;
			//����
			heap[c / 2] = heap[c];//����������
			c *= 2;//  ��һһ�㣬�����Ƚ�


		}
		heap[c / 2] = y;
	}
}

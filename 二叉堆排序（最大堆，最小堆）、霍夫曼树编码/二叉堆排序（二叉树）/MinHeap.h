#pragma once

#include"Prec.h"
#include"Exception_my.h"
template<class T>
class MinHeap
{
private:
	int CurrentSize, Maxsize;
	T * heap;

public:
	MinHeap(int MinHeapSize = 100);
	~MinHeap()
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
	MinHeap<T> & Insert(const T x); //��С�ѵĲ���
	MinHeap<T> & DeleteMin( T &x);
	void Initialize(T a[], int size, int Arraysize);
	void Show()const {
		for (int i = 1; i <= CurrentSize; i++)
			cout << heap[i] << " ";
		cout << endl;
	}
	void Deactivate() { heap = 0; }
	MinHeap<T> & ChangeMin(const T x);
};

template<class T>
inline MinHeap<T>::MinHeap(int MinHeapSize)
{
	Maxsize = MinHeapSize;
	heap = new T[Maxsize + 1];
	CurrentSize = 0;
}

template<class T>
inline MinHeap<T>& MinHeap<T>::Insert(const T  x)
{
	// TODO: �ڴ˴����� return ���	
	//��x�嵽��С���У�������ĩ�˲��룬Ȼ��ͨ���Ƚϲ����ϸ�
	//ʱ�临�Ӷ�Ϊlogn
	if (isFull())Out_Of_Bounds("The Heap is already full!\n");

	int i = ++CurrentSize;
	while (i != 1 && x < heap[i / 2])
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
inline MinHeap<T>& MinHeap<T>::DeleteMin( T &x)
{
	// TODO: �ڴ˴����� return ���
	//����СԪ�ط���x�����Ӷ���ɾ����СԪ��
	//�ٶ�����Ԫ�ط�����ڵ㣬�����³����ҵ���÷ŵ�λ��
	if (isEmpty())Out_Of_Bounds("There is no number in the heap!\n");

	x = heap[1];
	
	//�ع���
	T target = heap[CurrentSize--];
	//�Ӹ���ʼ��Ѱ�Һ��ʵ�λ��
	int i = 1;  //�ѵĵ�ǰ�ڵ�
	int next_i = 2;//i�ĺ���
	while (next_i <= CurrentSize) {
		if (next_i < CurrentSize&&heap[next_i] > heap[next_i + 1])next_i++;  //Ѱ�Ҹýڵ���С�ĺ���

																			 //���ڵ���亢�Ӵ�����Է���ֱ���˳�
		if (target <= heap[next_i])break;

		//С���亢��
		heap[i] = heap[next_i];//����������
		i = next_i;//����һ��
		next_i *= 2;
	}
	heap[i] = target;

	return *this;

}

//�ı���С�ѵĶ����������������������µ���

template<class T>
inline MinHeap<T>& MinHeap<T>::ChangeMin(const T x)
{
	if (isEmpty())Out_Of_Bounds("There is no number in the heap!\n");


	//�ع���
	T target = x;
	heap[1] = x;
	//�Ӹ���ʼ��Ѱ�Һ��ʵ�λ��
	int i = 1;  //�ѵĵ�ǰ�ڵ�
	int next_i = 2;//i�ĺ���
	while (next_i <= CurrentSize) {
		if (next_i < CurrentSize&&heap[next_i] > heap[next_i + 1])next_i++;  //Ѱ�Ҹýڵ���С�ĺ���

																			 //���ڵ���亢�Ӵ�����Է���ֱ���˳�
		if (target <= heap[next_i])break;

		//С���亢��
		heap[i] = heap[next_i];//����������
		i = next_i;//����һ��
		next_i *= 2;
	}

	heap[i] = target;

	return *this;
}
template<class T>
inline void MinHeap<T>::Initialize(T a[], int size, int ArraySize) //size�����������Ԫ�ظ�����ArraySize��������С�����ɸ���
{
	//����С�ѳ�ʼ��Ϊ����a
	delete[]heap;
	heap = a;
	//for (int i = 1; i <= 10; i++)
	//	cout << heap[i] << ' ';
	CurrentSize = size;
	Maxsize = ArraySize;

	//����һ����С��
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i];//�����ĸ������һ���������Ľڵ�
		/*cout << heap[i];*/
					  //Ѱ�ҷ���y��λ��
		int c = 2 * i;//c�ĸ��ڵ�ΪĿ��λ��
		while (c <= CurrentSize)
		{
			if (c < CurrentSize&&heap[c] > heap[c + 1])c++;

			//�ܰ�y����heap��c/2����
			if (y <= heap[c])break;
			//����
			heap[c / 2] = heap[c];//����������
			c *= 2;//  ��һһ�㣬�����Ƚ�


		}
		heap[c / 2] = y;
	}
}
#pragma once

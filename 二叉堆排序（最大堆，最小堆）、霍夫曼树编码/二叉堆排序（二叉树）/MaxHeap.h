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
		Deactivate();  //直接删除heap会导致内存访问错误， 初始化中将一个数组给了heap
	}
	int Size()const { return CurrentSize; }
	T Max()
	{
		if (CurrentSize == 0)Out_Of_Bounds("There is no number in the heap!\n");
		return heap[1];//以数组下标为1的元素为根节点
	}
	bool isEmpty()const { return CurrentSize == 0; }
	bool isFull()const { return CurrentSize == Maxsize; }
	MaxHeap<T> & Insert(const T x); //最大堆的插入
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
	// TODO: 在此处插入 return 语句	
	//将x插到最大堆中，先在最末端插入，然后通过比较不断上浮
	//时间复杂度为logn
	if (isFull())Out_Of_Bounds("The Heap is already full!\n");

	int i = ++CurrentSize;
	while (i != 1 && x > heap[i / 2])
	{
		//不能把x放入heap【i】
		heap[i] = heap[i / 2];
		i /= 2;
	}
	//找到应该插入的位置
	heap[i] = x;
	return *this;

}

template<class T>
inline MaxHeap<T>& MaxHeap<T>::DeleteMax(const T x)
{
	// TODO: 在此处插入 return 语句
	//将最大元素放入x，并从堆中删除最大元素
	//假定最后的元素放入根节点，不断下沉，找到其该放的位置
	if(isEmpty())Out_Of_Bounds("There is no number in the heap!\n");

	x = heap[1];
	//重构堆
	T target = heap[CurrentSize--];
	//从根开始，寻找合适的位置
	int i = 1;  //堆的当前节点
	int next_i = 2;//i的孩子
	while (next_i <= CurrentSize) {
		if (next_i < CurrentSize&&heap[next_i] < heap[next_i + 1])next_i++;  //寻找该节点最大的孩子

		//根节点比其孩子大则可以放入直接退出
		if (target >= heap[next_i])break;

		//小于其孩子
		heap[i] = heap[next_i];//将孩子上移
		i = next_i;//下移一层
		next_i *= 2;
	}
	heap[i] = target;

	return *this;

}

//改变最大堆的顶部，如果不满足规则则向下调整

template<class T>
inline MaxHeap<T>& MaxHeap<T>::ChangeMax(const T x)
{
	if (isEmpty())Out_Of_Bounds("There is no number in the heap!\n");

	
	//重构堆
	T target =x;
	heap[1] = x;
	//从根开始，寻找合适的位置
	int i = 1;  //堆的当前节点
	int next_i = 2;//i的孩子
	while (next_i <= CurrentSize) {
		if (next_i < CurrentSize&&heap[next_i] < heap[next_i + 1])next_i++;  //寻找该节点最大的孩子

																			 //根节点比其孩子大则可以放入直接退出
		if (target >= heap[next_i])break;

		//小于其孩子
		heap[i] = heap[next_i];//将孩子上移
		i = next_i;//下移一层
		next_i *= 2;
	}
	
	heap[i] = target;

	return *this;
}
template<class T>
inline void MaxHeap<T>::Initialize(T a[], int size, int ArraySize) //size是数组的现有元素个数，ArraySize是数组最大的容纳个数
{
	//把最大堆初始化为数组a
	delete[]heap;
	heap = a;
	CurrentSize = size;
	Maxsize = ArraySize;

	//产生一个最大堆
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i];//子树的根，最后一个有子树的节点

		//寻找放置y的位置
		int c = 2 * i;//c的父节点为目标位置
		while (c <= CurrentSize)
		{
			if (c < CurrentSize&&heap[c] < heap[c + 1])c++;

			//能把y放入heap【c/2】？
			if (y >= heap[c])break;
			//不能
			heap[c / 2] = heap[c];//将孩子上移
			c *= 2;//  下一一层，继续比较


		}
		heap[c / 2] = y;
	}
}

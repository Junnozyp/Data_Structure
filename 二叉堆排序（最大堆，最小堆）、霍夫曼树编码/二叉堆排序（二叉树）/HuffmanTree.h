#pragma once
#include"Prec.h"
#include"BinaryTree.h"
#include"MinHeap.h"


template<class T>
void HuffmanTree(T a[], int n,BinaryTree<T> & target,char b[])  //注意加引用符号
{
	//	根据权重啊a[1:n]构造霍夫曼树
	//创建单节点树的数组

	auto  * w = new Huffman<T>[n + 1];


	BinaryTree<int> z, zero;
	for (int i = 1; i <= n; i++)
	{
		z.MakeTree(b[i-1],i, zero, zero);
		w[i].weight = a[i];
		w[i].tree = z;

	}

	//把数组变成最小堆
	MinHeap<Huffman<T> >H(1);
	H.Initialize(w, n, n);


	//将堆中的树不断合并
	Huffman<T> x, y;
	for (int i = 1; i < n; i++)
	{
		H.DeleteMin(x);
		H.DeleteMin(y);
	
		
		z.MakeTree(0, x.tree, y.tree);
		x.weight += y.weight;
		x.tree = z;
		H.Insert(x);
	}

	H.DeleteMin(x);//最后的树
	H.Deactivate();
	delete[]w;
	
	
	target = x.tree;
	
}

template<class T>
class Huffman
{
	template<class T>
	friend void HuffmanTree(T a[], int n, BinaryTree<T> & target,char b[]);
	


private:
	BinaryTree<int>tree;
	T weight;//	权值
	
public:
	Huffman() {

	}
	~Huffman()
	{

	}
	//转换函数
	operator T ()const { return weight; }
	/*BinaryTree<int>* HuffmanTree(T[], int n);
	void setHuffmanCode(BinaryTreeNode<T> *t);
	void OutputHuffmanCode(BinaryTreeNode<T> *t);
	void HUffmanCode(BinaryTree<T> * h);*/
	//复制构造函数
	Huffman<T>& operator =(const Huffman<T> & hu);
};

template<class T>
inline Huffman<T>& Huffman<T>::operator=(const Huffman<T>& hu)
{
	// TODO: 在此处插入 return 语句
	if (this == &hu)return *this;
	tree = hu.tree;
	weight = hu.weight;
	return *this;

}




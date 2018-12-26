#pragma once
#include"Prec.h"
#include"BinaryTree.h"
#include"MinHeap.h"


template<class T>
void HuffmanTree(T a[], int n,BinaryTree<T> & target,char b[])  //ע������÷���
{
	//	����Ȩ�ذ�a[1:n]�����������
	//�������ڵ���������

	auto  * w = new Huffman<T>[n + 1];


	BinaryTree<int> z, zero;
	for (int i = 1; i <= n; i++)
	{
		z.MakeTree(b[i-1],i, zero, zero);
		w[i].weight = a[i];
		w[i].tree = z;

	}

	//����������С��
	MinHeap<Huffman<T> >H(1);
	H.Initialize(w, n, n);


	//�����е������Ϻϲ�
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

	H.DeleteMin(x);//������
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
	T weight;//	Ȩֵ
	
public:
	Huffman() {

	}
	~Huffman()
	{

	}
	//ת������
	operator T ()const { return weight; }
	/*BinaryTree<int>* HuffmanTree(T[], int n);
	void setHuffmanCode(BinaryTreeNode<T> *t);
	void OutputHuffmanCode(BinaryTreeNode<T> *t);
	void HUffmanCode(BinaryTree<T> * h);*/
	//���ƹ��캯��
	Huffman<T>& operator =(const Huffman<T> & hu);
};

template<class T>
inline Huffman<T>& Huffman<T>::operator=(const Huffman<T>& hu)
{
	// TODO: �ڴ˴����� return ���
	if (this == &hu)return *this;
	tree = hu.tree;
	weight = hu.weight;
	return *this;

}




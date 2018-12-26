#pragma once
#include"Prec.h"
#include"LinkedQueue.h"


//�ڵ�����������
int _count;

template<class T>
struct BinaryTreeNode
{
	T data;
	char sign;
	string code;   //����������
	BinaryTreeNode<T> * LeftChild;  //������
	BinaryTreeNode<T> * RightChild; //������
};
//���������ݺ���
template<class T>
static void Output(BinaryTreeNode<T> *t)
{
	cout << t->data << " ";
}
//ɾ��������ݺ���
template<class T>
static void Free(BinaryTreeNode<T> *t)
{
	delete t;
}
//ͳ�ƽڵ���
template<class T>
static void Add1(BinaryTreeNode<T> *t)
{
	_count++;
}


//�������ඨ��
template<class T>
class BinaryTree
{

private:
	BinaryTreeNode<T> * root;//���ڵ�ָ��
	void PreOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> * t);
	void InOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> * t);
	void PostOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> * t);
	void LevelOrder(void(*Visit)(BinaryTreeNode<T> *u));
	int Height(BinaryTreeNode<T>*t)const; //�������ĸ߶�
public:
	BinaryTree() { root = new BinaryTreeNode<T>; root = 0; }
	~BinaryTree()
	{

	}
	void Send(BinaryTreeNode<T>* u) { u = root; }
	bool isEmpty()const { return ((root) ? false : true); }
	bool Root(T x)const;
	void MakeTree(const T element, BinaryTree<T>& left, BinaryTree<T> & right);
	void MakeTree(const char element, const T element1, BinaryTree<T>& left, BinaryTree<T> & right);
	void BreakTree(T element, BinaryTree<T>& left, BinaryTree<T> & right);
	void PreOrder(void(*Visit)(BinaryTreeNode<T> *u))
	{
		PreOrder(Visit, root); cout << endl;
	}
	void InOrder(void(*Visit)(BinaryTreeNode<T> *u))
	{
		InOrder(Visit, root); cout << endl;
	}
	void PostOrder(void(*Visit)(BinaryTreeNode<T> *u))
	{
		PostOrder(Visit, root); cout << endl;
	}
	void LevelOrder()
	{
		LevelOrder(Output); cout << endl;
	}
	void Delete()
	{
		PostOrder(Free, root); root = 0;
	}
	int Height()const { return Height(root); }
	int Size()
	{
		_count = 0;
		PreOrder(Add1, root);
		return _count;

	}
	BinaryTree<T> & operator =(const BinaryTree<T> & n);
	void Copy(BinaryTreeNode<T>*u) {
		root = u;
	}
	BinaryTreeNode<T>* Re_root()const {
		BinaryTreeNode<T>*u = root;
		return u;
	}
};

template<class T>
inline void BinaryTree<T>::PreOrder(void(*Visit)(BinaryTreeNode<T>*u), BinaryTreeNode<T>* t)
{
	//ǰ�����
	if (t)
	{
		Visit(t);

		PreOrder(Visit, t->LeftChild);

		PreOrder(Visit, t->RightChild);


	}

}

template<class T>
inline void BinaryTree<T>::InOrder(void(*Visit)(BinaryTreeNode<T>*u), BinaryTreeNode<T>* t)
{
	if (t)
	{

		InOrder(Visit, t->LeftChild);
		Visit(t);
		InOrder(Visit, t->RightChild);
	}
}

template<class T>
inline void BinaryTree<T>::PostOrder(void(*Visit)(BinaryTreeNode<T>*u), BinaryTreeNode<T>* t)
{
	if (t)
	{
		PostOrder(Visit, t->LeftChild);

		PostOrder(Visit, t->RightChild);
		Visit(t);
	}
}

template<class T>
bool BinaryTree<T>::Root(T x)const
{
	//ȡ���ڵ��data�򣬷���x
	//���û�и��ڵ㣬����false
	if (root)
	{
		x = root->data;
		return true;
	}
	else
		return false;
}

template<class T>
inline void BinaryTree<T>::MakeTree(const T element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	/*��left��right ��element�ϲ���һ����
	left ,right, this�����ǲ�ͬ����
	��������*/
	if (&left == &right)
	{
		root = new BinaryTreeNode<T>;
		BinaryTree<T>  new_one;
		new_one.Copy(CopyTree(left.Re_root()));  //ʹ�ø��ƺ���
		root->data = element;
		root->LeftChild = new_one.root;
		root->RightChild = right.root;
	}
	else
	{
		root = new BinaryTreeNode<T>;
		root->data = element;
		root->LeftChild = left.root;
		root->RightChild = right.root;
	}


	//��ֹ����ԭ����left��right
	left.root = right.root = 0;
}

template<class T>
inline void BinaryTree<T>::MakeTree(const char element, const T element1, BinaryTree<T>& left, BinaryTree<T>& right)
{
	if (&left == &right)
	{
		root = new BinaryTreeNode<T>;
		BinaryTree<T>  new_one;
		new_one.Copy(CopyTree(left.Re_root()));  //ʹ�ø��ƺ���
		root->sign = element;
		root->data = element1;
		root->LeftChild = new_one.root;
		root->RightChild = right.root;
	}
	else
	{
		root = new BinaryTreeNode<T>;
		root->sign = element;
		root->data = element1;
		root->LeftChild = left.root;
		root->RightChild = right.root;
	}


	//��ֹ����ԭ����left��right
	left.root = right.root = 0;
}

template<class T>
inline void BinaryTree<T>::BreakTree(T element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	//left ,right, this�����ǲ�ͬ����
	//������Ƿ�Ϊ��
	if (!root)throw Out_Of_Bounds("The tree can't be empty");

	//�ֽ���
	element = root->data;
	left.root = root->LeftChild;
	right.root = root->RightChild;
	delete root;
	root = 0;
}

template<class T>
inline BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& n)
{
	// TODO: �ڴ˴����� return ���
	if (this == &n)
		return *this;
	root = n.root;
	return *this;
}



template<class T>
inline void BinaryTree<T>::LevelOrder(void(*Visit)(BinaryTreeNode<T>*u))
{
	//��t���������������������нṹ
	QueueLinked<BinaryTreeNode<T> *> Q;
	BinaryTreeNode<T>* t;
	t = root;
	while (t)
	{
		Visit(t);

		//�����ӷ������
		if (t->LeftChild)Q.Add(t->LeftChild);
		if (t->RightChild)Q.Add(t->RightChild);

		//������һ���ڵ�
		try {
			Q.Delete(t);  //ɾ������һ�����ʵĽڵ��t
		}
		catch (Out_Of_Bounds &os) { cout << os.Type_ex; return; }

	}

}

template<class T>
inline int BinaryTree<T>::Height(BinaryTreeNode<T>* t) const
{
	if (!t)return 0;
	int hL = Height(t->LeftChild);//�������ĸ߶�
	int hR = Height(t->RightChild);//�������ĸ߶�
	if (hL > hR)return ++hL;
	else
		return ++hR;
}


//�ݹ������
template<class T>
BinaryTreeNode<T> * CopyTree(BinaryTreeNode<T>* tree)
{
	BinaryTreeNode<T> *ltree = NULL, *rtree = NULL, *root = NULL;
	if (tree == NULL)
		return NULL;
	ltree = CopyTree(tree->LeftChild);        //���������� 
	rtree = CopyTree(tree->RightChild);        //���������� 
	root = (BinaryTreeNode<T> *)malloc(sizeof(BinaryTreeNode<T>)); //���Ƹ���� 
	root->data = tree->data;
	root->LeftChild = ltree;
	root->RightChild = rtree;
	return root;

}

template<class T>
static void setHuffmanCode(BinaryTreeNode<T>* t)
{
	if (t->LeftChild != NULL)
	{
		t->LeftChild->code = t->code;//�̳и��ڵ�ı���
		t->LeftChild->code.append("0");
	}

	if (t->RightChild != NULL)
	{
		t->RightChild->code = t->code;
		t->RightChild->code.append("1");
	}
}

template<class T>
static  void OutputHuffmanCode(BinaryTreeNode<T>* t)
{
	if (t->LeftChild == NULL && t->RightChild == NULL)
		cout << "The char  " << t->sign << "  's HuffmanCode is " << t->code << endl;
}

template<class T>
static void HuffmanCode(BinaryTree<T>& h)
{
	h.PreOrder(setHuffmanCode);
	h.PreOrder(OutputHuffmanCode);
}





















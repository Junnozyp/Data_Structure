#pragma once
#include"Prec.h"
#include"LinkedQueue.h"


//节点数计数变量
int _count;

template<class T>
struct BinaryTreeNode
{
	T data;
	char sign;
	string code;   //霍夫曼编码
	BinaryTreeNode<T> * LeftChild;  //左子树
	BinaryTreeNode<T> * RightChild; //右子树
};
//输出结点数据函数
template<class T>
static void Output(BinaryTreeNode<T> *t)
{
	cout << t->data << " ";
}
//删除结点数据函数
template<class T>
static void Free(BinaryTreeNode<T> *t)
{
	delete t;
}
//统计节点数
template<class T>
static void Add1(BinaryTreeNode<T> *t)
{
	_count++;
}


//二叉树类定义
template<class T>
class BinaryTree
{

private:
	BinaryTreeNode<T> * root;//根节点指针
	void PreOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> * t);
	void InOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> * t);
	void PostOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> * t);
	void LevelOrder(void(*Visit)(BinaryTreeNode<T> *u));
	int Height(BinaryTreeNode<T>*t)const; //返回树的高度
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
	//前序遍历
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
	//取根节点的data域，放入x
	//如果没有根节点，返回false
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
	/*将left和right 和element合并成一棵树
	left ,right, this必须是不同的树
	创建新树*/
	if (&left == &right)
	{
		root = new BinaryTreeNode<T>;
		BinaryTree<T>  new_one;
		new_one.Copy(CopyTree(left.Re_root()));  //使用复制函数
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


	//阻止访问原来的left和right
	left.root = right.root = 0;
}

template<class T>
inline void BinaryTree<T>::MakeTree(const char element, const T element1, BinaryTree<T>& left, BinaryTree<T>& right)
{
	if (&left == &right)
	{
		root = new BinaryTreeNode<T>;
		BinaryTree<T>  new_one;
		new_one.Copy(CopyTree(left.Re_root()));  //使用复制函数
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


	//阻止访问原来的left和right
	left.root = right.root = 0;
}

template<class T>
inline void BinaryTree<T>::BreakTree(T element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	//left ,right, this必须是不同的树
	//检查树是否为空
	if (!root)throw Out_Of_Bounds("The tree can't be empty");

	//分解树
	element = root->data;
	left.root = root->LeftChild;
	right.root = root->RightChild;
	delete root;
	root = 0;
}

template<class T>
inline BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& n)
{
	// TODO: 在此处插入 return 语句
	if (this == &n)
		return *this;
	root = n.root;
	return *this;
}



template<class T>
inline void BinaryTree<T>::LevelOrder(void(*Visit)(BinaryTreeNode<T>*u))
{
	//对t进行逐层遍历，采用链队列结构
	QueueLinked<BinaryTreeNode<T> *> Q;
	BinaryTreeNode<T>* t;
	t = root;
	while (t)
	{
		Visit(t);

		//将孩子放入对列
		if (t->LeftChild)Q.Add(t->LeftChild);
		if (t->RightChild)Q.Add(t->RightChild);

		//访问下一个节点
		try {
			Q.Delete(t);  //删除的下一欲访问的节点给t
		}
		catch (Out_Of_Bounds &os) { cout << os.Type_ex; return; }

	}

}

template<class T>
inline int BinaryTree<T>::Height(BinaryTreeNode<T>* t) const
{
	if (!t)return 0;
	int hL = Height(t->LeftChild);//左子树的高度
	int hR = Height(t->RightChild);//右子树的高度
	if (hL > hR)return ++hL;
	else
		return ++hR;
}


//递归后序复制
template<class T>
BinaryTreeNode<T> * CopyTree(BinaryTreeNode<T>* tree)
{
	BinaryTreeNode<T> *ltree = NULL, *rtree = NULL, *root = NULL;
	if (tree == NULL)
		return NULL;
	ltree = CopyTree(tree->LeftChild);        //复制左子树 
	rtree = CopyTree(tree->RightChild);        //复制右子树 
	root = (BinaryTreeNode<T> *)malloc(sizeof(BinaryTreeNode<T>)); //复制根结点 
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
		t->LeftChild->code = t->code;//继承父节点的编码
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





















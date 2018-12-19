#pragma once
#include"my_exception.h"
#define  Node  BSTreeNode<K, V>
template<class K,class V>//key and value
struct BSTreeNode
{
	K data; //值
	V inform;//附带信息
	//int freq;//频率
	Node * left;
	Node * right;

	Node(const K & da=0, const V & inf="none")//初始化
		:data(da)
		, inform(inf)
		,left(NULL)
		,right(NULL)
	{ }

};

template<class K, class V>
class BSTree
{
private:
	Node *root;
	void InOrder(Node * root)const;
	void PreOrder(Node * root)const;
	int Height(Node *t)const; //返回树的高度
	
public:
	BSTree():root(NULL)
	{ }
	~BSTree()
	{

	}

	bool Insert(const K & da, const V & inf="none");
	Node * Find(const K & da);//按给定的关键字查找
	bool Delete(const K& da); //按给定的关键字删除.
	//遍历
	void _InOrder()const
	{
		InOrder(root);
		cout << endl;
	}
	void _PreOrder()const
	{
		PreOrder(root);
		cout << endl;
	}

	int Height()const { return Height(root); }
	
	
};

template<class K, class V>
inline bool BSTree<K, V>::Insert(const K & da, const V & inf)
{
	if (root == NULL)//根节点为空
	{
		root = new Node(da, inf);
		return true;
	}

	Node * c_parent = NULL;
	Node * cur = root;

	while (cur)
	{
		if (da > cur->data)  //data大于节点的值，则继续在节点的右节点搜索位置
		{
			c_parent = cur;
			cur = cur->right;
		}
		else if (da < cur->data)
		{
			c_parent = cur;
			cur = cur->left;
		}
		else
		{
			throw Out_Of_Bounds("Badinsert_item!\n");
		}
	}
	//在parent节点后插入data
	if (da > c_parent->data)c_parent->right = new Node(da, inf);
	else
		c_parent->left = new Node(da, inf);
	return true;
}

template<class K, class V>
inline Node * BSTree<K, V>::Find(const K & da)
{
	Node * cur = root;
	while (cur)
	{
		if (da > cur->data)
			cur = cur->right;
		else if (da < cur->data)
			cur = cur->left;
		else
			return cur;
	}
	return NULL;
}

template<class K, class V>
inline bool BSTree<K, V>::Delete(const K & da)
{
	Node * c_parent = root;
	Node * cur = root;
	//找到data对应的节点
	while (cur)
	{
		if (cur->data = da)
			break;
		c_parent = cur;
		if (cur->data > da)
			cur = cur->left;
		else
			cur = cur->right;
	}

	if (cur == NULL)
		throw Out_Of_Bounds("Can't find the item you wanno delete!\n");

	//处理data元素的父节点和data节点
	if (cur->left == NULL || cur->right == NULL)//  一个子结点为空或者两个子结点都为空
	{
		Node *ptemp = NULL;
		if (cur->left != NULL)
			ptemp = cur->left;
		else if (cur->right != NULL)
			ptemp = cur->right;

		if (c_parent->left == cur)
			c_parent->left = ptemp;
		else
			c_parent->right = ptemp;

		delete cur;
		cur = NULL;
	}
	else
		//找到前驱节点，即左子树中的最大值,且须满足最大值不会在只有左子树的节点上
	{
		Node * ptemp = cur->left;
		Node * p_parent = cur;
		while (ptemp->right != NULL)
		{
			p_parent = ptemp;
			ptemp = ptemp->right;
		}

		cur->data = ptemp->data;
		cur->inform = ptemp->inform;
		p_parent->right = NULL;
		delete ptemp;
		ptemp = NULL;
	}
}

template<class K, class V>
inline void BSTree<K, V>::InOrder(Node * root) const
{
	
	if (root == NULL)
		return;

	InOrder(root->left);
	cout << "( " << root->data << " ," << root->inform << " )" << "  ";
	InOrder(root->right);
}

template<class K, class V>
inline void BSTree<K, V>::PreOrder(Node * root) const
{
	if (root == NULL)
		return;

	cout << "( " << root->data << " ," << root->inform << " )" << "  ";
	InOrder(root->left);
	
	InOrder(root->right);
}

template<class K, class V>
inline int BSTree<K, V>::Height(Node * t) const
{
	if (!t)return 0;
	int hL = Height(t->left);//左子树的高度
	int hR = Height(t->right);//右子树的高度
	if (hL > hR)return ++hL;
	else
		return ++hR;
}



#pragma once
#include"my_exception.h"
#define  Node  BSTreeNode<K, V>
template<class K,class V>//key and value
struct BSTreeNode
{
	K data; //ֵ
	V inform;//������Ϣ
	//int freq;//Ƶ��
	Node * left;
	Node * right;

	Node(const K & da=0, const V & inf="none")//��ʼ��
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
	int Height(Node *t)const; //�������ĸ߶�
	
public:
	BSTree():root(NULL)
	{ }
	~BSTree()
	{

	}

	bool Insert(const K & da, const V & inf="none");
	Node * Find(const K & da);//�������Ĺؼ��ֲ���
	bool Delete(const K& da); //�������Ĺؼ���ɾ��.
	//����
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
	if (root == NULL)//���ڵ�Ϊ��
	{
		root = new Node(da, inf);
		return true;
	}

	Node * c_parent = NULL;
	Node * cur = root;

	while (cur)
	{
		if (da > cur->data)  //data���ڽڵ��ֵ��������ڽڵ���ҽڵ�����λ��
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
	//��parent�ڵ�����data
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
	//�ҵ�data��Ӧ�Ľڵ�
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

	//����dataԪ�صĸ��ڵ��data�ڵ�
	if (cur->left == NULL || cur->right == NULL)//  һ���ӽ��Ϊ�ջ��������ӽ�㶼Ϊ��
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
		//�ҵ�ǰ���ڵ㣬���������е����ֵ,�����������ֵ������ֻ���������Ľڵ���
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
	int hL = Height(t->left);//�������ĸ߶�
	int hR = Height(t->right);//�������ĸ߶�
	if (hL > hR)return ++hL;
	else
		return ++hR;
}



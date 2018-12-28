#pragma once
#include<iostream>
#include<iomanip>
using namespace std;
#define Node AVLTreeNode<T>

template<class T>
struct AVLTreeNode
{
	T key; //��ֵ
	int height;//�߶�
	AVLTreeNode * left;
	AVLTreeNode * right;

	AVLTreeNode(T value,AVLTreeNode * l,AVLTreeNode * r):
		key(value),left(l),right(r){ }
};


//AVL���ඨ��
template<class T>
class AVLTree
{
private:
	Node * mRoot;//���ڵ�

public:
	AVLTree() {  }
	~AVLTree()
	{
		Destroy(mRoot);
	}

	int Height();  //��ȡ���ĸ���
	int Max(int a, int b);//�Ƚ����ĸ߶�

	void PreOrder() { PreOrder(mRoot); }
	void InOrder() { InOrder(mRoot); }
	void PostOrder() { PostOrder(mRoot); }

	//���Ҽ�ֵΪK�Ľڵ�
	Node * Find(T key)const { Find(mRoot, key); }
	//������С�Ľڵ㲢���ؼ�ֵ
	T Minimum()const;
	//�������Ľڵ�
	T Maximum()const;

	//����㣨keyΪ��ֵ������AVL����
	void Insert(T key);

	//ɾ����㣨keyΪ��ֵ���Ľڵ�
	void Delete(T key);

	//����
	void Destroy() { Destroy(mRoot); }

	//��ӡ	
	void Print() {
		if (mRoot != NULL)
			Print(mRoot, mRoot->key, 0);
	}

	void Node_height()
	{
		Node_height(mRoot);
	}
private:
	int Height(Node * tree);
	void Node_height(Node * tree);
	void PreOrder(Node * tree)const ;
	void InOrder(Node * tree)const;
	void PostOrder(Node * tree)const;

	Node * Find(Node * x, T key)const;
	Node * Minimum(Node * tree);
	Node * Maximum(Node * tree);

	//LL: �����Ӧ�����������ת��
	Node * LLRotation(Node * k2);
	//RR: ���Ҷ�Ӧ��������ҵ���ת��
	Node * RRROtation(Node * k1);
	//LR�����Ҷ�Ӧ���������˫��ת��
	Node * LRRotation(Node * k3);
	//RL�������Ӧ���������˫��ת��
	Node * RLRotation(Node * k1);


	Node * Insert(Node * &tree, T key);  //ע��ʹ������
	Node * Delete(Node * &tree,Node *z);//&?

	void Destroy(Node * tree);
	void Print(Node * tree, T key, int direction);
};

template<class T>
inline int AVLTree<T>::Height()
{
	return Height(mRoot);
}

template<class T>
inline int AVLTree<T>::Max(int a, int b)
{
	return a > b ? a : b;
}

template<class T>
inline T AVLTree<T>::Minimum() const
{
	Node *p = Minimum(mRoot);
	if (p != NULL)
		return p->key;
	return (T)NULL;
}

template<class T>
inline T AVLTree<T>::Maximum() const
{
	Node *p = Maximum(mRoot);
	if (p != NULL)
		return p->key;
	return (T)NULL;
}

template<class T>
inline void AVLTree<T>::Insert(T key)
{
	Insert(mRoot, key);
}

template<class T>
inline void AVLTree<T>::Delete(T key)
{
	Node * z;
	if ((z = Find(mRoot, key)) != NULL)
		mRoot = Delete(mRoot, z);
}

template<class T>
inline int AVLTree<T>::Height(Node * tree)
{
	if (!tree)return 0;
	int hL = Height(tree->left);//�������ĸ߶�
	int hR = Height(tree->right);//�������ĸ߶�
	if (hL > hR)return ++hL;
	else
		return ++hR;
}
template<class T>
inline void AVLTree<T>::Node_height(Node * tree)
{
	if (tree)
	{
		cout << tree->key << " 's height " << tree->height << endl;
		Node_height(tree->left);
		Node_height(tree->right);
	}
}
template<class T>
inline void AVLTree<T>::PreOrder(Node * tree) const
{
	if (tree)
	{
		cout << tree->key << " ";
		PreOrder(tree->left);
		PreOrder(tree->right);
	}
}
template<class T>
inline void AVLTree<T>::InOrder(Node * tree) const
{
	if (tree)
	{
		PreOrder(tree->left);
		cout << tree->key << " ";
		PreOrder(tree->right);
	}
	
}
template<class T>
inline void AVLTree<T>::PostOrder(Node * tree) const
{
	if (tree)
	{
		PreOrder(tree->left);
		PreOrder(tree->right);
		cout << tree->key << " ";
	}
	
}
template<class T>
inline Node * AVLTree<T>::Find(Node * x, T key) const
{
	if (x == NULL || x->key == key)
		return x;
	if (key < x->key)
		return Find(x->left, key);
	else
		return Find(x->right, key);
}
template<class T>
inline Node * AVLTree<T>::Minimum(Node * tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}
template<class T>
inline Node * AVLTree<T>::Maximum(Node * tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}
/*
 * LL�������Ӧ�����(����ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template<class T>
inline Node * AVLTree<T>::LLRotation(Node * k2)
{
	Node * k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	//���¸߶�ֵ
	k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = Max(Height(k1->left), k2->height) + 1;

	return k1;
}
/*
 * RR�����Ҷ�Ӧ�����(�ҵ���ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template<class T>
inline Node * AVLTree<T>::RRROtation(Node * k1)
{
	Node * k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = Max(Height(k1->left), Height(k1->right)) + 1;
	k2->height = Max(Height(k2->right), k1->height) + 1;

	return k2;
}
/*
 * LR�����Ҷ�Ӧ�����(��˫��ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template<class T>
inline Node * AVLTree<T>::LRRotation(Node * k3)
{
	k3->left = RRROtation(k3->left);
	return LLRotation(k3);
}
/*
 * RL�������Ӧ�����(��˫��ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template<class T>
inline Node * AVLTree<T>::RLRotation(Node * k1)
{
	k1->right = LLRotation(k1->right);

	return RRROtation(k1);
}
/*
 * �������뵽AVL���У������ظ��ڵ�
 *
 * ����˵����
 *     tree AVL���ĸ����
 *     key ����Ľ��ļ�ֵ
 * ����ֵ��
 *     ���ڵ�
 */
template<class T>
inline Node * AVLTree<T>::Insert(Node * &tree, T key)
{
	if (tree == NULL)
	{
		//�½��ڵ�
		tree = new Node(key, NULL, NULL);
		if (tree == NULL)
		{
			cout << "ERROR: created AVL tree failed!\n";
			return NULL;
		}
	}

	else if (key < tree->key)
	{
		//�ݹ�
		tree->left = Insert(tree->left, key);
		// ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ���
		if (Height(tree->left) - Height(tree->right) == 2)
		{
			if (key < tree->left->key)//LL
				tree = LLRotation(tree);
			else
				tree = LRRotation(tree);
		}
	}
	else if (key > tree->key)
	{
		tree->right = Insert(tree->right, key);

		if (Height(tree->right) - Height(tree->left) == 2)
		{
			if (key > tree->right->key)
				tree = RRROtation(tree);
			else
				tree = RLRotation(tree);
		}
	}
	else  //key=tree->key	
	{
		cout << "Can't add the item which is already existed!\n";

	}

	//tree->height = Max(Height(tree->left), Height(tree->right))+1;

	return tree;

}
/*
 * ɾ�����(z)�����ظ��ڵ�
 *
 * ����˵����
 *     tree AVL���ĸ����
 *     z ��ɾ���Ľ��
 * ����ֵ��
 *     ���ڵ�
 */
template<class T>
inline Node * AVLTree<T>::Delete(Node * &tree, Node *z)
{
	//��Ϊ�ջ���û��Ҫɾ���Ľڵ㣬ֱ�ӷ���NULL
	if (tree == NULL || z == NULL)
		return NULL;
	if (z->key < tree->key)//��ɾ���Ľڵ���tree����������
	{
		
		tree->left = Delete(tree->left, z);
		
		//��ɾ���ڵ��AVL��ʧȥƽ�⣬����е���
		if (Height(tree->right) - Height(tree->left) == 2)
		{
			Node * r = tree->right;
			if (Height(r->left) > Height(r->right))
				tree = RLRotation(tree);  //���ɾ����һ�������ұ߿�������ƽ��
			else
				tree = RRROtation(tree);
		}
	}
	else if (z->key>tree->key)// ��ɾ���Ľڵ���"tree��������"��
	{
		tree->right = Delete(tree->right, z);

		
		if (Height(tree->left) - Height(tree->right) == 2)
		{
			Node * l = tree->left;
			if (Height(l->right) > Height(l->left))
				tree = LRRotation(tree);
			else
				tree = LLRotation(tree);
		}
	}
	else
	{
		//tree���Ƕ���Ҫɾ���Ľڵ�

		//tree�����Һ��Ӷ��ǿ�
		if ((tree->left != NULL) && (tree->right != NULL))
		{
			if (Height(tree->left) > Height(tree->right))
			{// ���tree�����������������ߣ�
				// ��(01)�ҳ�tree���������е����ڵ�
				//   (02)�������ڵ��ֵ��ֵ��tree��
				//   (03)ɾ�������ڵ㡣
				// ����������"tree�������������ڵ�"��"tree"������
				// �������ַ�ʽ�ĺô��ǣ�ɾ��"tree�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				Node * max_ = Maximum(tree->left);
				tree->key = max_->key;
				tree->left = Delete(tree->left, max_);
			}
			else
			{
				// ���tree��������������������(��������ȣ�������������������1)
				// ��(01)�ҳ�tree���������е���С�ڵ�
				//   (02)������С�ڵ��ֵ��ֵ��tree��
				//   (03)ɾ������С�ڵ㡣
				// ����������"tree������������С�ڵ�"��"tree"������
				// �������ַ�ʽ�ĺô��ǣ�ɾ��"tree������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				Node * min_ = Minimum(tree->right);
				tree->key = min_->key;
				tree->right = Delete(tree->right, min_);
			}
		}

		else
		{
			Node * temp = tree;
			tree = (tree->left != NULL) ? tree->left : tree->right;
			delete temp;
			temp = NULL;
		}
	}
	return tree;
}

template<class T>
inline void AVLTree<T>::Destroy(Node * tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		return Destroy(tree->left);
	if (tree->right != NULL)
		return Destroy(tree->right);
	delete tree;
	tree = NULL;
}

template<class T>
inline void AVLTree<T>::Print(Node * tree, T key, int direction)
{
	if (tree != NULL)
	{
		//setw(int n)��������������
		if (direction == 0)    // tree�Ǹ��ڵ�
			cout << setw(2) << tree->key << " is root" << endl;
		else                // tree�Ƿ�֧�ڵ�
			cout << setw(2) << tree->key << " is " << setw(2) << key << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		Print(tree->left, tree->key, -1);
		Print(tree->right, tree->key, 1);
	}
}


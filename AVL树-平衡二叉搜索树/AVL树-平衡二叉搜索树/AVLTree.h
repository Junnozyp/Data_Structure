#pragma once
#include<iostream>
#include<iomanip>
using namespace std;
#define Node AVLTreeNode<T>

template<class T>
struct AVLTreeNode
{
	T key; //键值
	int height;//高度
	AVLTreeNode * left;
	AVLTreeNode * right;

	AVLTreeNode(T value,AVLTreeNode * l,AVLTreeNode * r):
		key(value),left(l),right(r){ }
};


//AVL树类定义
template<class T>
class AVLTree
{
private:
	Node * mRoot;//根节点

public:
	AVLTree() {  }
	~AVLTree()
	{
		Destroy(mRoot);
	}

	int Height();  //获取树的告诉
	int Max(int a, int b);//比较树的高度

	void PreOrder() { PreOrder(mRoot); }
	void InOrder() { InOrder(mRoot); }
	void PostOrder() { PostOrder(mRoot); }

	//查找键值为K的节点
	Node * Find(T key)const { Find(mRoot, key); }
	//查找最小的节点并返回键值
	T Minimum()const;
	//查找最大的节点
	T Maximum()const;

	//将结点（key为键值）插入AVL树中
	void Insert(T key);

	//删除结点（key为键值）的节点
	void Delete(T key);

	//销毁
	void Destroy() { Destroy(mRoot); }

	//打印	
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

	//LL: 左左对应的情况（左单旋转）
	Node * LLRotation(Node * k2);
	//RR: 右右对应的情况（右单旋转）
	Node * RRROtation(Node * k1);
	//LR：左右对应的情况（左双旋转）
	Node * LRRotation(Node * k3);
	//RL：右左对应的情况（右双旋转）
	Node * RLRotation(Node * k1);


	Node * Insert(Node * &tree, T key);  //注意使用引用
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
	int hL = Height(tree->left);//左子树的高度
	int hR = Height(tree->right);//右子树的高度
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
 * LL：左左对应的情况(左单旋转)。
 *
 * 返回值：旋转后的根节点
 */
template<class T>
inline Node * AVLTree<T>::LLRotation(Node * k2)
{
	Node * k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	//更新高度值
	k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = Max(Height(k1->left), k2->height) + 1;

	return k1;
}
/*
 * RR：右右对应的情况(右单旋转)。
 *
 * 返回值：旋转后的根节点
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
 * LR：左右对应的情况(左双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template<class T>
inline Node * AVLTree<T>::LRRotation(Node * k3)
{
	k3->left = RRROtation(k3->left);
	return LLRotation(k3);
}
/*
 * RL：右左对应的情况(右双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template<class T>
inline Node * AVLTree<T>::RLRotation(Node * k1)
{
	k1->right = LLRotation(k1->right);

	return RRROtation(k1);
}
/*
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
template<class T>
inline Node * AVLTree<T>::Insert(Node * &tree, T key)
{
	if (tree == NULL)
	{
		//新建节点
		tree = new Node(key, NULL, NULL);
		if (tree == NULL)
		{
			cout << "ERROR: created AVL tree failed!\n";
			return NULL;
		}
	}

	else if (key < tree->key)
	{
		//递归
		tree->left = Insert(tree->left, key);
		// 插入节点后，若AVL树失去平衡，则进行相应的调节
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
 * 删除结点(z)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     z 待删除的结点
 * 返回值：
 *     根节点
 */
template<class T>
inline Node * AVLTree<T>::Delete(Node * &tree, Node *z)
{
	//根为空或者没有要删除的节点，直接返回NULL
	if (tree == NULL || z == NULL)
		return NULL;
	if (z->key < tree->key)//待删除的节点在tree的左子树中
	{
		
		tree->left = Delete(tree->left, z);
		
		//若删除节点后AVL树失去平衡，则进行调节
		if (Height(tree->right) - Height(tree->left) == 2)
		{
			Node * r = tree->right;
			if (Height(r->left) > Height(r->right))
				tree = RLRotation(tree);  //左边删除了一个，则右边可能引起不平衡
			else
				tree = RRROtation(tree);
		}
	}
	else if (z->key>tree->key)// 待删除的节点在"tree的右子树"中
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
		//tree就是对于要删除的节点

		//tree的左右孩子都非空
		if ((tree->left != NULL) && (tree->right != NULL))
		{
			if (Height(tree->left) > Height(tree->right))
			{// 如果tree的左子树比右子树高；
				// 则(01)找出tree的左子树中的最大节点
				//   (02)将该最大节点的值赋值给tree。
				//   (03)删除该最大节点。
				// 这类似于用"tree的左子树中最大节点"做"tree"的替身；
				// 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
				Node * max_ = Maximum(tree->left);
				tree->key = max_->key;
				tree->left = Delete(tree->left, max_);
			}
			else
			{
				// 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
				// 则(01)找出tree的右子树中的最小节点
				//   (02)将该最小节点的值赋值给tree。
				//   (03)删除该最小节点。
				// 这类似于用"tree的右子树中最小节点"做"tree"的替身；
				// 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
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
		//setw(int n)用来控制输出间隔
		if (direction == 0)    // tree是根节点
			cout << setw(2) << tree->key << " is root" << endl;
		else                // tree是分支节点
			cout << setw(2) << tree->key << " is " << setw(2) << key << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		Print(tree->left, tree->key, -1);
		Print(tree->right, tree->key, 1);
	}
}


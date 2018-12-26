#include"Pre.h"


//�ڵ�����������
int _count;
int L_count;

template<class T>
struct BinaryTreeNode
{
	T data;
	BinaryTreeNode<T> * LeftChild;  //������
	BinaryTreeNode<T> * RightChild; //������
};

//ͨ��
template<class T>
void General_Use(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> * t)
{
	if(t)
	{
		
		General_Use(Visit,t->LeftChild);
		General_Use(Visit,t->RightChild);
		Visit(t);
	}
}
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
template<class T>
static void L_Count(BinaryTreeNode<T> * t)
{
		L_count++;
}
//�������ҽڵ�
template<class T>
static void Exchange(BinaryTreeNode<T> * t)
{
	BinaryTreeNode<T> *temp = new BinaryTreeNode<T>;
	temp=t->LeftChild;
	t->LeftChild=t->RightChild;
	t->RightChild=temp;
} 

template<class T>
static void Find_node(BinaryTreeNode<T> * t,T & item)
{
	
	if(t->data==item)
	{
		cout<<t->data<<endl;
		General_Use(Free,t);
	}
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
	void CreateBiTree(BinaryTreeNode<T> * & t);
	void Count_Leaves(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> * t);
	void Exchange_LR(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> * t);
	void Release_node(BinaryTreeNode<T> * t,T & item)
	{
		cout<<"hahah\n";
		if(t)
		{
			if(t->data==item)
			{
				cout<<"Found it!\n";
				//���ڵ�ΪҪɾ���Ľڵ�
				delete t->LeftChild;
				t->LeftChild=NULL;
				delete t->RightChild;
				t->RightChild=NULL;
				delete t; 
			}
			else if(t->LeftChild!=NULL&&t->LeftChild->data==item)
			{
				cout<<"Found it!\n";
				delete t->LeftChild->LeftChild;
				delete t->LeftChild->RightChild;
				delete t->LeftChild;
				t->LeftChild=NULL;
			}
			else if(t->RightChild!=NULL&&t->RightChild->data==item)
			{
				cout<<"Found it!\n";
				delete t->RightChild->LeftChild;
				delete t->RightChild->RightChild;
				delete t->RightChild;
				t->RightChild=NULL;
			}
			else
			{
				if(t->LeftChild)
				Release_node(t->LeftChild,item);
					if(t->RightChild)
				Release_node(t->RightChild,item);
			}
		}
		else
		return ;
	}
public:
	BinaryTree() { //root = new BinaryTreeNode<T>; 
		root = 0; }
	~BinaryTree()
	{
		Delete();
	}
	

	 
	void Send(BinaryTreeNode<T>* u) { u = root; }
	bool isEmpty()const { return ((root) ? false : true); }
	bool Root(T x)const;
	void CreateBiTree()
	{
		CreateBiTree(root);
	}
	void MakeTree(const T element, BinaryTree<T>& left, BinaryTree<T> & right);
	void BreakTree( T element, BinaryTree<T>& left, BinaryTree<T> & right);
	void PreOrder()
	{
		PreOrder(Output, root); cout << endl;
	}
	void InOrder()
	{
		InOrder(Output, root); cout << endl;
	}
	void PostOrder()
	{
		PostOrder(Output, root); cout << endl;
	}
	void LevelOrder()
	{
		LevelOrder(Output); cout << endl;
	}
	void Delete()
	{
		PostOrder(Free, root); root = 0;
	}
	
		//��ͨ�ڵ�ɾ��
	void Delete(BinaryTreeNode<T>*u)
	{
		PostOrder(Free, u); root = 0;
	}
	int Height()const { return Height(root); }
	int Size()
	{
		_count = 0;
		PreOrder(Add1, root);
		return _count;
	
	}
	void Copy(BinaryTreeNode<T>*u) {
		root = u;
	}
	BinaryTreeNode<T>* Re_root()const{
		BinaryTreeNode<T>*u = root;
		return u;
	}
	//����Ҷ�ڵ����Ŀ
	int Count_Leaves()
	{
		 Count_Leaves(L_Count,root);
		 return L_count;
	}
	
	//�������ҽڵ�
	bool exchange_LR()
	{
		Exchange_LR(Exchange,root);
		return true;
	} 
	 
	bool release_node(T & item)
	{
		Release_node(root,item);
	}

};

template<class T>
inline void BinaryTree<T>::PreOrder(void(*Visit)(BinaryTreeNode<T>*u), BinaryTreeNode<T>* t)
{
	//ǰ�����
	if (t)
	{
		Visit(t);		
		PreOrder(Visit,t->LeftChild);		
		PreOrder(Visit,t->RightChild);	
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
inline void BinaryTree<T>::Exchange_LR(void(*Visit)(BinaryTreeNode<T>*u), BinaryTreeNode<T>* t)
{
	if (t)
	{
		Visit(t);		
		PreOrder(Visit,t->LeftChild);		
		PreOrder(Visit,t->RightChild);
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
inline void BinaryTree<T>::CreateBiTree(BinaryTreeNode<T>*& t)
{
	static int flag = 1;	
	if (flag == 1)
	{
		T ch=getchar();
		if (ch == '\n') {
			flag = 0;
			return;
		}
		if (ch == ' ')t = NULL;
		else
		{
			t = new BinaryTreeNode<T>;
			t->LeftChild = t->RightChild = NULL;
			t->data = ch;
			CreateBiTree(t->LeftChild);
			CreateBiTree(t->RightChild);
		}
	}
	else
		return;
	
}

template<class T>
inline void BinaryTree<T>::Count_Leaves(void(*Visit)(BinaryTreeNode<T>*u), BinaryTreeNode<T>* t)
{
	if (t==NULL)
	{
		Visit(t);
	}
	else
	{
		Count_Leaves(Visit,t->LeftChild);
		Count_Leaves(Visit,t->RightChild);
	}
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

//template<class T>
//inline void BinaryTree<T>::BreakTree(T element, BinaryTree<T>& left, BinaryTree<T>& right)
//{
//	//left ,right, this�����ǲ�ͬ����
//	//������Ƿ�Ϊ��
//	if (!root)throw Out_Of_Bounds("The tree can't be empty");
//	//�ֽ���
//	element = root->data;
//	left.root = root->LeftChild;
//	right.root = root->RightChild;
//	delete root;
//	root = 0;
//}
//template<class T>
//inline void BinaryTree<T>::LevelOrder(void(*Visit)(BinaryTreeNode<T>*u))
//{
//	//��t���������������������нṹ
//	QueueLinked<BinaryTreeNode<T> *> Q;
//	BinaryTreeNode<T>* t;
//	t = root;
//	while (t)
//	{
//		Visit(t);
//		//�����ӷ������
//		if (t->LeftChild)Q.Add(t->LeftChild);
//		if (t->RightChild)Q.Add(t->RightChild);
//		//������һ���ڵ�
//		try {
//			Q.Delete(t);  //ɾ������һ�����ʵĽڵ��t
//		}
//		catch (Out_Of_Bounds &os) { //cout << os.Type_ex;
//		return; }
//	}
//}
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

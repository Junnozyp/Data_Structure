#include"Pre.h"
#include"BinaryTree.h"


BinaryTree<int> a, x, y, z,n;



int main(void)
{
	
	//y.MakeTree(1, a, a);
	//z.MakeTree(2, a, a);
	//x.MakeTree(3, y, z);
	//y.MakeTree(4, x, a);
	//n.MakeTree(5, y, y);
	//n.InOrder();
	//cout << endl;

	//cout <<"Height: "<< n.Height() << endl;
	//cout << "Size: " << n.Size() << endl;

	///*n.Delete();
	//cout << "Size: " << n.Size() << endl;*/

	//BinaryTree<int> copy;
	//copy.Copy(CopyTree(n.Re_root())); //copytree 返回一个新树的根节点指针
	////BinaryTreeNode<int>* c=NULL, *o=NULL;
	////copy.Send(c);
	////n.Send(o);
	////CopyBiTree(o, c);
	////copy.PreOrder();
	//cout << "Size: " << copy.Size() << endl;



	BinaryTree<char>  BiTree;
	cout << "Enter elements for BinaryTree by preorder sequence:\n";
	BiTree.CreateBiTree();
	cout << "BinaryTree shows by Inorder:\n";
	BiTree.InOrder();
	cout << "BinaryTree shows by Postorder:\n";
	BiTree.PostOrder();
	cout << "BinaryTree shows by Levelorder:\n";
	BiTree.LevelOrder();
	cout << "The length of this BinaryTree:  " << BiTree.Height() << endl;
	cout << "The number of leaves node of this BinaryTree:  " << BiTree.Count_Leaves() << endl;

	//Testing Exchanging Function
	cout << "Exchange the leftroot and rightroot :\n";
	BiTree.exchange_LR();
	cout << "The new BinaryTree shows by Preorder:\n";
	BiTree.PreOrder();

	//Testing Delete_node Function
	char target;
	cout << "Input the data of the node you want to delete:  	";
	cin >> target;
	BiTree.release_node(target);
	cout << "The new BinaryTree shows by Preorder:\n";
	BiTree.PreOrder();

	return 0;
	
}
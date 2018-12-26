#include"Pre.h"
#include"BinaryTree.h"

int main(void)
{
	




	BinaryTree<char>  BiTree;
	cout << "Enter elements for BinaryTree by preorder sequence:\n";
	BiTree.CreateBiTree();
	cout << "BinaryTree shows by Inorder:\n";
	BiTree.InOrder();
	cout << "BinaryTree shows by Postorder:\n";
	BiTree.PostOrder();
	//cout << "BinaryTree shows by Levelorder:\n";
	//BiTree.LevelOrder();
	cout << "The length of this BinaryTree:  " << BiTree.Height() << endl;
	cout << "The number of leaves node of this BinaryTree:  " << BiTree.Count_Leaves() << endl;
	
	cout<<"Exchange the leftroot and rightroot :\n";
	BiTree.exchange_LR();
	cout << "The new BinaryTree shows by Preorder:\n";
	BiTree.PreOrder();
	
	char target;
	cout<<"Input the data of the node you want to delete:  	";
	cin>>target;
	BiTree.release_node(target);
	cout << "The new BinaryTree shows by Preorder:\n";
	BiTree.PreOrder();
	
	
	return 0;
	
}

#include"Pre.h"


#include"BinaryTree.h"


BinaryTree<int> a, x, y, z,n;



int main(void)
{
	
	y.MakeTree(1, a, a);
	z.MakeTree(2, a, a);
	x.MakeTree(3, y, z);
	y.MakeTree(4, x, a);
	n.MakeTree(5, y, y);
	n.InOrder();
	cout << endl;

	cout <<"Height: "<< n.Height() << endl;
	cout << "Size: " << n.Size() << endl;

	/*n.Delete();
	cout << "Size: " << n.Size() << endl;*/

	BinaryTree<int> copy;
	copy.Copy(CopyTree(n.Re_root())); //copytree 返回一个新树的根节点指针
	//BinaryTreeNode<int>* c=NULL, *o=NULL;
	//copy.Send(c);
	//n.Send(o);
	//CopyBiTree(o, c);
	//copy.PreOrder();
	cout << "Size: " << copy.Size() << endl;


	return 0;
	
}
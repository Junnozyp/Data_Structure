#include"AVLTree.h"

static int arr[] = { 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main(void)
{
	int i, ilen;
	AVLTree<int> root;
	ilen = TBL_SIZE(arr);
	for (i = 0; i < ilen; i++)
	{
		cout << arr[i] << ' ';
		root.Insert(arr[i]);

	}
	cout << endl<<root.Height();
	cout << "\nÇ°Ðò±éÀú:\n";
	root.PreOrder();

	cout << "AVL Tree's detailed informaiton:\n";
	root.Print();

	root.Delete(14);
	root.Delete(16);
	root.Delete(15);
	root.Node_height();

	root.Print();
	return 0;
}
#include"Prec.h"
#include"MaxHeap.h"
#include"MinHeap.h"
#include"BinaryTree.h"
#include"HuffmanTree.h"


int main(void)
{
	/*MaxHeap<int > test;
	MinHeap<int > test1;
	int target[40] = { 0 };
	for (int i = 1; i < 21; i++)
		target[i] = i;

	test.Initialize(target, 20, 40);

	test.Show();

	for (int i = 1; i < 21; i++)
	{
		cout << target[i] << " ";
	}
	cout << endl;

	test1.Initialize(target, 20, 40);
	test1.ChangeMin(-1);
	test1.Show();

	return 0;*/
	char b[7] = { 'A','B','C','D','E','F','G' };
	int a[8] = { 0,500,24,7,17,34,5,13 };
	int n = 7;
	//for (int i = 0; i <= n; i++)
	//	a[i] = 2 * i;
	
	BinaryTree<int>  x;
	HuffmanTree(a, n, x,b);

	x.PreOrder(Output);

	x.PreOrder(setHuffmanCode);
	x.PreOrder(OutputHuffmanCode);

	
	return 0;

}
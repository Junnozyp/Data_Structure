#include"BinarySearchTree.h"
#include<string>
#include<time.h>
int main(void)
{
	/*int a[20];
	srand((unsigned)time(0));
	for (int i = 0; i < 20; i++)
		a[i] = rand()%100;*/
	int a[10] = {30,5,35,2,32,80,31,33,60,85 };
	int b[6] = { 5,10,4,2,12,3 };
	BSTree<int, string>  test;
	try {
			
			for (int i = 0; i <10; i++)
				test.Insert(a[i]);
	}
	catch (Out_Of_Bounds &os)
	{
		cout << os.Type_ex << endl;
	}

	test._InOrder();
	test._PreOrder();

	return 0;
}
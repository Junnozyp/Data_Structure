#include"标头.h"

#include<algorithm>
int main(void)
{

	string test;
	getline(cin, test);
	test.erase(remove(test.begin(), test.end(), ' '), test.end());//删除特定的字符
	cout << test << endl;
	//Inorder_to_Postorder(test.c_str(), test.size());
	

	Calculate_for_Inorder(test.c_str(), test.size());


	//cout << test[2];

	//str.erase(std::remove(str.begin(), str.end(), 'a'), str.end());
	return 0;

}
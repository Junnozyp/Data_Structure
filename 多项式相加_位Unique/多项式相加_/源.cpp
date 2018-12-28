#include"Polynomial.h"

int main(void)
{
	int num = 3;
	Polynomial test1(num);

	cout << "Enter " << num << " parts of the Polynomial 1: ( coef + expn )\n";
	float coef_ = 0;
	int expn_ = 0;

	for (int i = 0; i < num; i++)
	{
		if(cin>>coef_>>expn_)
		test1.insert(coef_,expn_);
		else
		{
			i--;
			continue;
		}
	}

	test1.ShowPoly();

	cout << "Copy:\n";
	num++;
	Polynomial test2(num);
	cout << "Enter " << num << " parts of the Polynomial 2: ( coef + expn )\n";


	for (int i = 0; i < num; i++)
	{
		if (cin >> coef_ >> expn_)
			test2.insert(coef_, expn_);
		else
		{
			i--;
			continue;
		}
	}
	test2.ShowPoly();
	cout << "Testing addition:\n";
	Polynomial test3 = test1.operator+(test2);

	test3.ShowPoly();

	cout << "Testing substraction:\n";
	Polynomial test4 = test3 - test1;
	test4.ShowPoly();
	


	return 0;



}
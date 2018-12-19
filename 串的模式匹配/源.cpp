#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

void get_next(string & st, int next[])
{
	//��ģʽ����next��������������
	int i = 1, j = 0;
	next[1] = 0;
	while (i < st.size())
	{
		if (j == 0 || st[i-1] == st[j-1]) //string�Ǵ�0��ʼ��
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
	
}


void get_next_p(string & st, int next[])
{
	//��ģʽ����next��������������
	int i = 1, j = 0;
	next[1] = 0;
	while (i < st.size())
	{
		if (j == 0 || st[i - 1] == st[j - 1]) //string�Ǵ�0��ʼ��
		{
			++i;
			++j;
			if (st[i-1] != st[j-1])
				next[i] = j;
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}
}

//����ģʽ��T��next������ģʽ���������ĵ�pos���ַ�֮���λ��
int Index_KMP(string & s, string t, int pos,int next[])
{
	int i = pos, j = 1;
	while (i <= s.size() && j <= t.size())
	{
		if (j == 0 || s[i - 1] == t[j - 1]) { ++i; ++j; }
		else
			j = next[j];
	}
	if (j > t.size())return i - t.size();
	else return 0;
}


int main(void)
{
	

	string test = "abaabcac";
	string compare = "acabaabaabcacaabc";
	int *next = new int[test.size()];
	

	//get_next_p(test, next);
	////get_next(test, next);
	//for (int i = 1; i <=test.size(); i++)
	//	cout << next[i] << ' ';

	//cout << endl<< Index_KMP(compare, test, 1, next);

	//string�Ĳ����ַ�������,�ں�������ֵ�ĵ�n���ַ�֮��
	cout<<compare.find(test, 0);
	cout << endl;

	string substring = compare.substr(0, 7);
	cout << substring;
	//copy
	substring.assign(compare, 0, 8);
	cout << endl << substring;
	//����
	substring.insert(0 ,test);
	cout << endl << substring;
	//ɾ��
	substring.erase(0, 5);
	cout << endl << substring;
	//ȫ�����
	substring.clear();
	cout << endl << substring;
	return 0;
}
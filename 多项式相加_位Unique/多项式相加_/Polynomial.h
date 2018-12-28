#ifndef Polynomial_H_
#define Polynomial_H_


#include<iostream>
#include<cstdlib>
using namespace std;
// compare function
template<typename T>
int compare(T & a, T & b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
	
}

//����Ƿ�Ϊ0
template <typename T>
int substract(T &a, T &b)
{
	int i=0;
	(a - b) == 0 ? i = 0 : i = 1;
	return i;
}

//����Ƿ�Ϊ0
template <typename T>
int add_if(T &a, T &b)
{
	int i = 0;
	(a + b) == 0 ? i = 1 : i = 0;
	return i;
}

class Polynomial
{
private:
	struct Node {
		float  coef;   // ϵ��	
		int expn;		// ָ��
		Node * next;
	};
	enum { Q_size = 32 };
	// save each expns;
	int same[Q_size] = { 0 };
	int same_count=0;

	//ʹ��λ����ȷ��������,��˳��洢�ṹ�¿���ʹ��
	/*int save_ex = 0x0000;*/


	Node * front=nullptr;  // ͷָ��
	Node * f_p = nullptr;  //βָ��
	int Polysize=0;   // number of members
	int Polylength=0;  // number of limitation
	
	
	
public:

	Polynomial();
	Polynomial(int Polylength = Q_size);   //��ʼ��
	Polynomial(const Polynomial & q);    // ���ƹ��캯��
	Polynomial & operator=(const Polynomial & q);
	void ShowPoly();  // print Polynomial
	
	
	~Polynomial();

	//void AddPloy(Polynomial & pa, Polynomial & pb);
	void MultiPoly(Polynomial & pa, Polynomial & pb);
	//void SubtractPloy(Polynomial & pa, Polynomial & pb);

	// ִ����������ʽ�ļӼ���
	Polynomial operator + (Polynomial & pa);
	Polynomial operator - (Polynomial & pa);
	// �жϿջ�����
	bool isfull()const { return Polysize == Polylength; }
	bool isempty()const { return Polysize == 0; }
	//�޸��޶�
	void Changelength(int leng) { Polylength = leng; }
	int PolyLength()const { return Polylength; }//���������޶�
	int PolySize()const { return Polysize; }//��������

	bool insert(float co, int ex);// ������
	//ѡ������
	bool Order_Poly();
};


inline Polynomial::Polynomial()
{
	front = new Node;
	front->expn = -1;
	front->coef = 0;
	front->next = NULL;
	Polylength = Q_size;
	cout << "object created\n";
}




Polynomial::Polynomial(int polyL) // polysize Ϊ����   ����Ϊ���������޶�
{
	if (polyL == 0)
	{
		front = new Node;
		front->expn = -1;
		front->coef = 0;
		front->next = NULL;
		Polylength = Q_size;
		return;
	}
	
	front = new Node;
	front->expn = -1;
	front->coef = 0;
	front->next = NULL;
	
	f_p = front; // set tail pointer to head pointer

	Polylength = polyL;  // update the limitation
	cout << "Object created\n";

}

bool Polynomial::insert(float co, int ex)
{
	if (isfull())
	{
		cout << "The polynomial part is full already!\n";
		return false;
	}
	//save each expn;
	//����ָͬ����ʱ
	
	for (int i = 0; i < same_count; i++)
	{
		if (same[i] == ex)
		{
			Node * po = front->next;// fake pointer to use
			//�ҵ�ָ����ͬ����
			while (i--)
				po = po->next;
			po->coef += co;
			return true;
		}	
	}
	same[same_count++] = ex;  // ����δ�������ָ��ֵ������

	//˳��ṹ��ʹ��
	/*int compare_ex = pow(2, ex);
	if (((compare_ex&save_ex) << (32 - ex - 1)) >> (ex))
	{ 
		Node * po = front->next;
		while (ex--)
				po = po->next;
			po->coef += co;
			return true;
	}*/
		

	Node * insert_obj = new Node;
	insert_obj->coef = co;
	insert_obj->expn = ex;
	insert_obj->next = NULL;
	Polysize++;
	if (front->next== NULL)front->next = insert_obj; //��һ�����룬����ͷ������һ��ָ���һ�����
	else
	f_p->next = insert_obj;   // ����λ��
	f_p = insert_obj; // ���½��
	return true;
}

inline bool Polynomial::Order_Poly()
{
	if (isempty()) return false;

	int ex_temp = 0;
	float co_temp=0;
	auto _last = front->next;
	auto _next = _last->next;
	//�ο�����---����-�������
	for(int i=0;i<Polysize-1;i++, _last = front->next, _next = _last->next)
		for (int j = 0; j < Polysize - 1 - i; j++)
		{
			if (_last->expn > _next->expn)
			{
				//��ָ������������
				//����ϵ��
				co_temp = _last->coef;
				_last->coef = _next->coef;
				_next->coef = co_temp;

				//����ָ��
				ex_temp = _last->expn;
				_last->expn = _next->expn;
				_next->expn = ex_temp;
			}
			//���½��
			_last = _next;
			_next = _next->next;
		}
	return true;
}

Polynomial::~Polynomial()
{

	
	while (front) // if the first Node isn't empty
	{
		f_p = front->next;//�ȱ�����һ���ĵ�ַ,ɾ�����ٸ�ֵ
		delete front;
		front = f_p;
		
	}
	cout << "Object delete successed! \n";
	
}

//���ƹ��캯��
Polynomial::Polynomial(const Polynomial & q)
{
	if (front != f_p)// if the first Node isn't empty, clear it!
		while (front) 
		{
			f_p = front->next;
			delete front;
			front = f_p;
		}
	// recall the memory for the head pointer
	front = new Node;
	front->expn = -1;
	front->coef = 0;
	front->next = NULL;
	f_p = front;
	Polylength = q.Polylength;
	

	Node * copy = q.front->next;// fake pointer to use
	for (; copy !=NULL;)
	{
		if (insert(copy->coef, copy->expn))   // �������Ѿ���insert�и���,ͨ�����ò��뺯����ɸ��Ʋ���
		{
			copy = copy->next;
			
		}
		//������ʧ��
		else
		{
			cout << "Copy failed!\n";
			exit(1);
		}
		
	}

	
}

//��ֵ���������
Polynomial & Polynomial::operator =(const Polynomial & q)
{
	//�ǿ�������
	if(front->next) // if the first Node isn't empty , clear  it
		while (front)
		{
			f_p = front->next;
			delete front;
			front = f_p;

		}
	// recall the memory for the head pointer
	front = new Node;
	front->expn = -1;
	front->coef = 0;
	front->next = NULL;
	f_p = front;
	Polylength = q.Polylength;


	Node * copy = q.front->next;// fake pointer to use
	for (; copy != NULL;)
	{
		if (insert(copy->coef, copy->expn))   // �������Ѿ���insert�и���
		{
			copy = copy->next;

		}
		else
		{
			cout << "Copy failed!\n";
			exit(1);
		}

	}

	
}

void Polynomial::ShowPoly()
{
	if (isempty())
	{
		cout << "The Polynomial is empty!\n";
		return;
	}
	//�������
	Order_Poly();
	cout << endl << "The polynomial follows below: \n";
	Node * output = front->next; // fake pointer to use
	cout << "M (x)=";
	while (output)
	{
		cout << output->coef << "x*(" << output->expn << ")";
		output = output->next;
		if (output)
			cout << " + ";
	}

	cout << endl;
}
Polynomial  Polynomial::operator + (Polynomial & pa)  //��������Ϊ���ö����ұ�����Ϊ�������ݵ�
{
	Polynomial Add_poly(Polysize+pa.Polysize);   // ������������������ʽȫ�������Ķ���ʽ��
	/*Node * creat = new Node;*/
	/*creat = Add_poly.front->next;*/

	// fake pointer to use
	Node * copy_a = front->next;
	Node * copy_b = pa.front->next;

	float sum = 0;
	while (copy_a&&copy_b)
	{
		Node *temp = new Node;  //�м����
		temp->next = NULL;
		switch (compare(copy_a->expn, copy_b->expn))   // ѡ��ָ��С����
		{

		case -1:
		
			Add_poly.insert(copy_a->coef, copy_a->expn);
			copy_a = copy_a->next;   //С��һ������
			break;
		case 1:
		
			Add_poly.insert(copy_b->coef, copy_b->expn);
			copy_b = copy_b->next;  //С��һ������
			break;
		case 0:
			//ָ������ͬ����ϵ�����Ƿ����
			sum = copy_a->coef + copy_b->coef;
			if (sum == 0)   // �պ��������
			{
				delete temp;
			}
			else
			{
	
				Add_poly.insert(sum, copy_b->expn);
			}
			copy_a = copy_a->next; copy_b = copy_b->next;  // both  update
			
			break;
		}
	}
	 // link the remaining of copy_a or copy_b
	if (copy_a == NULL) {
		while (copy_b)
		{
			Add_poly.insert(copy_b->coef, copy_b->expn);
			copy_b = copy_b->next;
		}
	}
	
	if (copy_b==NULL) {
		while (copy_a)
		{
			Add_poly.insert(copy_a->coef, copy_a->expn);
			copy_a = copy_a->next;
		}
	}


	
	return Add_poly;
}

Polynomial  Polynomial::operator -(Polynomial & pa)  //��������Ϊ���ö����ұ�����Ϊ�������ݵ�
{
	Polynomial Add_poly(Polysize + pa.Polysize);   // ������
												   /*Node * creat = new Node;*/
												   /*creat = Add_poly.front->next;*/

	Node * copy_a = front->next;
	Node * copy_b = pa.front->next;

	float sum = 0;
	while (copy_a&&copy_b)
	{
		Node *temp = new Node;  //�м����
		temp->next = NULL;
		switch (compare(copy_a->expn, copy_b->expn))   // ѡ��ָ��С����
		{
		//�ٶ�����ʽ�Ѱ�ָ����С�������и���
		case -1:
			Add_poly.insert(copy_a->coef, copy_a->expn);  
			copy_a = copy_a->next;
			break;
		case 1:
			Add_poly.insert(-copy_b->coef, copy_b->expn);   // ������Ǹ�ֵ
			copy_b = copy_b->next;
			break;
		case 0:
			sum = copy_a->coef - copy_b->coef;    //ϵ���������պõ���
			if (sum == 0)
			{
				delete temp;

			}
			else
			{

				Add_poly.insert(sum, copy_b->expn);
			}
			copy_a = copy_a->next; copy_b = copy_b->next; //both update

			break;
		}
	}

	if (copy_a == NULL) {
		while (copy_b)
		{
			Add_poly.insert(copy_b->coef, copy_b->expn);
			copy_b = copy_b->next;
		}
	}

	if (copy_b == NULL) {
		while (copy_a)
		{
			Add_poly.insert(copy_a->coef, copy_a->expn);
			copy_a = copy_a->next;
		}
	}



	return Add_poly;
}
#endif


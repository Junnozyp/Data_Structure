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

//相减是否为0
template <typename T>
int substract(T &a, T &b)
{
	int i=0;
	(a - b) == 0 ? i = 0 : i = 1;
	return i;
}

//相加是否为0
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
		float  coef;   // 系数	
		int expn;		// 指数
		Node * next;
	};
	enum { Q_size = 32 };
	// save each expns;
	int same[Q_size] = { 0 };
	int same_count=0;

	//使用位运算确定已有项,在顺序存储结构下可以使用
	/*int save_ex = 0x0000;*/


	Node * front=nullptr;  // 头指针
	Node * f_p = nullptr;  //尾指针
	int Polysize=0;   // number of members
	int Polylength=0;  // number of limitation
	
	
	
public:

	Polynomial();
	Polynomial(int Polylength = Q_size);   //初始化
	Polynomial(const Polynomial & q);    // 复制构造函数
	Polynomial & operator=(const Polynomial & q);
	void ShowPoly();  // print Polynomial
	
	
	~Polynomial();

	//void AddPloy(Polynomial & pa, Polynomial & pb);
	void MultiPoly(Polynomial & pa, Polynomial & pb);
	//void SubtractPloy(Polynomial & pa, Polynomial & pb);

	// 执行两个多项式的加减法
	Polynomial operator + (Polynomial & pa);
	Polynomial operator - (Polynomial & pa);
	// 判断空或者满
	bool isfull()const { return Polysize == Polylength; }
	bool isempty()const { return Polysize == 0; }
	//修改限度
	void Changelength(int leng) { Polylength = leng; }
	int PolyLength()const { return Polylength; }//返回项数限度
	int PolySize()const { return Polysize; }//返回项数

	bool insert(float co, int ex);// 插入结点
	//选择排序法
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




Polynomial::Polynomial(int polyL) // polysize 为项数   参数为给定项数限度
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
	//有相同指数项时
	
	for (int i = 0; i < same_count; i++)
	{
		if (same[i] == ex)
		{
			Node * po = front->next;// fake pointer to use
			//找到指数相同的项
			while (i--)
				po = po->next;
			po->coef += co;
			return true;
		}	
	}
	same[same_count++] = ex;  // 若并未保存过该指数值项，则存入

	//顺序结构下使用
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
	if (front->next== NULL)front->next = insert_obj; //第一个插入，则让头结点的下一个指向第一个结点
	else
	f_p->next = insert_obj;   // 连接位置
	f_p = insert_obj; // 更新结点
	return true;
}

inline bool Polynomial::Order_Poly()
{
	if (isempty()) return false;

	int ex_temp = 0;
	float co_temp=0;
	auto _last = front->next;
	auto _next = _last->next;
	//参考例子---链表-宿舍管理
	for(int i=0;i<Polysize-1;i++, _last = front->next, _next = _last->next)
		for (int j = 0; j < Polysize - 1 - i; j++)
		{
			if (_last->expn > _next->expn)
			{
				//把指数项大的往后移
				//交换系数
				co_temp = _last->coef;
				_last->coef = _next->coef;
				_next->coef = co_temp;

				//交换指数
				ex_temp = _last->expn;
				_last->expn = _next->expn;
				_next->expn = ex_temp;
			}
			//更新结点
			_last = _next;
			_next = _next->next;
		}
	return true;
}

Polynomial::~Polynomial()
{

	
	while (front) // if the first Node isn't empty
	{
		f_p = front->next;//先保存下一个的地址,删除后再赋值
		delete front;
		front = f_p;
		
	}
	cout << "Object delete successed! \n";
	
}

//复制构造函数
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
		if (insert(copy->coef, copy->expn))   // 计数项已经在insert中更新,通过调用插入函数完成复制操作
		{
			copy = copy->next;
			
		}
		//若插入失败
		else
		{
			cout << "Copy failed!\n";
			exit(1);
		}
		
	}

	
}

//赋值运算符重载
Polynomial & Polynomial::operator =(const Polynomial & q)
{
	//非空则清零
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
		if (insert(copy->coef, copy->expn))   // 计数项已经在insert中更新
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
	//输出排序
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
Polynomial  Polynomial::operator + (Polynomial & pa)  //运算符左侧为调用对象，右边是作为参数传递的
{
	Polynomial Add_poly(Polysize+pa.Polysize);   // 创建能容纳两个多项式全部项数的多项式类
	/*Node * creat = new Node;*/
	/*creat = Add_poly.front->next;*/

	// fake pointer to use
	Node * copy_a = front->next;
	Node * copy_b = pa.front->next;

	float sum = 0;
	while (copy_a&&copy_b)
	{
		Node *temp = new Node;  //中间变量
		temp->next = NULL;
		switch (compare(copy_a->expn, copy_b->expn))   // 选出指数小的项
		{

		case -1:
		
			Add_poly.insert(copy_a->coef, copy_a->expn);
			copy_a = copy_a->next;   //小的一方更新
			break;
		case 1:
		
			Add_poly.insert(copy_b->coef, copy_b->expn);
			copy_b = copy_b->next;  //小的一方更新
			break;
		case 0:
			//指数项相同，看系数项是否抵消
			sum = copy_a->coef + copy_b->coef;
			if (sum == 0)   // 刚好两项抵消
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

Polynomial  Polynomial::operator -(Polynomial & pa)  //运算符左侧为调用对象，右边是作为参数传递的
{
	Polynomial Add_poly(Polysize + pa.Polysize);   // 最多个数
												   /*Node * creat = new Node;*/
												   /*creat = Add_poly.front->next;*/

	Node * copy_a = front->next;
	Node * copy_b = pa.front->next;

	float sum = 0;
	while (copy_a&&copy_b)
	{
		Node *temp = new Node;  //中间变量
		temp->next = NULL;
		switch (compare(copy_a->expn, copy_b->expn))   // 选出指数小的项
		{
		//假定多项式已按指数从小到大排列各项
		case -1:
			Add_poly.insert(copy_a->coef, copy_a->expn);  
			copy_a = copy_a->next;
			break;
		case 1:
			Add_poly.insert(-copy_b->coef, copy_b->expn);   // 插入的是负值
			copy_b = copy_b->next;
			break;
		case 0:
			sum = copy_a->coef - copy_b->coef;    //系数项相减后刚好抵消
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


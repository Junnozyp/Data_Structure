#ifndef DORMITORY_H_
#define DORMITORY_H_
#include<iostream>
#include<string>
#include<exception>
using namespace std;
//假设某校有20间宿舍，宿舍编号101，102，..., 120。每间只住一名学生。初始部分宿舍已用。
//用两个链表（已用宿舍链表和可用宿舍链表）维护宿舍的管理，实现宿舍分配、宿舍交回。
//
//约定已用宿舍链表按宿舍号升序链接。初始可用宿舍链表也按宿舍号升序链接。
//
//宿舍分配从可用宿舍链表中摘取第一间宿舍分配给学生。学生交回的宿舍挂在可用宿舍链表最后。
//
//备注：使用list容器或静态链表。不用考虑宿舍分配和交回不成功的情况。

const int Dorm_size = 20;

// 索引异常机制——超出数组边界
class Out_Of_Bounds :public exception
{

public:
	string  Type_ex = "none";
	const char * what() { return "out of the range of present part!\n"; }
	Out_Of_Bounds(const char  * type);
	~Out_Of_Bounds()
	{

	}
};

Out_Of_Bounds::Out_Of_Bounds(const char * type)
{
	Type_ex = type;
}

class Dorm_free;  //前向声明
struct Dorm_data
{
	int num;
	string name;
	Dorm_data * next;
};
// 已用宿舍类
class Dorm_use
{
private:
	Dorm_data * Dormuse_list;  //已经使用的宿舍链表
	int use_size;       // 已经使用的数量
	Dorm_data * front;   //头指针
	Dorm_data * rear;  //尾指针
public:
	friend class Dorm_free;   //声明友元类
	Dorm_use();
	~Dorm_use();
	bool Dorm_use_insert(const char * name, int num, Dorm_free & present_left);  //初始分配函数-z指定宿舍
	bool Dorm_use_push( const char * name,Dorm_free & present_left);  //分配现有的空宿舍
	void display_use()const;
	bool Sort();
	bool isfull()const { return use_size == Dorm_size; }
	bool isempty()const { return use_size == 0; }
};
//剩余宿舍类
class Dorm_free
{
private:
	Dorm_data * Dormfree_list;  // 剩余宿舍的链表
	int free_size;    //剩余的空宿舍数量
	Dorm_data * front;   //头指针
	Dorm_data * rear;   //尾指针
public:
	friend class Dorm_use;   //声明友元类
	Dorm_free();
	~Dorm_free();
	bool Dorm_free_pop(int num,Dorm_use & present_use);  //归还宿舍
	void display_free()const;
	bool isempty()const { return free_size == 0; }
};

// 剩余宿舍的构造函数
Dorm_free::Dorm_free():free_size(Dorm_size)
{
	front = new Dorm_data;
	front->num = -1;
	front->next = NULL;
	rear = front;
	for (int i = 0; i < Dorm_size; i++)  //申请20个内存保存20个宿舍
	{
		Dorm_data * Dorm = new Dorm_data;
		Dorm->name = "none";
		Dorm->num = 101 + i;
		Dorm->next = NULL;
		
		if (front == NULL)
			front = Dorm;
		else
			rear->next = Dorm;
		rear = Dorm;
	}
}

// 剩余宿舍的析构函数
Dorm_free::~Dorm_free()
{
	Dorm_data * temp = new Dorm_data;
	while (front != nullptr)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}
// 归还指定房号的宿舍，插入可用链表的最后
bool Dorm_free::Dorm_free_pop(int num, Dorm_use & present_use)
{
	if (num > 120 || num < 101) throw Out_Of_Bounds("Returning Dormitory fail!");
	if (present_use.isempty())
	{
		cout << "There is no Dormitory under use!\n";
		return false;
	}
	Dorm_data * temp=NULL;  //指示find的前一个结点，用来更新
	Dorm_data * find = present_use.front;  // 寻找指定号码的宿舍结点
	for (; find->num != num;) {
		temp = find;
		find = find->next; //寻找指定号码的宿舍

	}
	temp->next = find->next;  //更新已用宿舍链表里的结点

	find->name = "none";//清空内容
	rear->next = find; //挂在可用链表尾部
	find->next = NULL;

	rear = find;  //更新尾指针
	//更新计数值
	present_use.use_size--;
	free_size++;

	return true;
}
// 输出剩余的宿舍的链表
void Dorm_free:: display_free()const
{
	Dorm_data * temp = front->next;
	while (temp)
	{
		cout << temp->num  ;
		temp = temp->next;
		if (temp)cout << "-";

	}
	cout << endl;
}

// 已用链表的构造函数
Dorm_use::Dorm_use():use_size(0)
{
	front= new Dorm_data;
	rear = front;
	front->name = "none";
	front->num = -1;
	front->next = NULL;
}


// 已用链表的析构函数
Dorm_use::~Dorm_use()
{
	Dorm_data * temp = new Dorm_data;
	while (front != nullptr)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

// 初始的插入操作
bool Dorm_use::Dorm_use_insert(const char * name, int num, Dorm_free & present_left)
{
	if (present_left.isempty()) {
		cout << "There is no Dorm left!\n";
		return false;
	}
	if (num > 120 || num < 101) throw Out_Of_Bounds("insert fail!");

	Dorm_data * temp=NULL;  //指示find的前一个结点，用来更新
	Dorm_data * find=present_left.front;

	for (; find->num != num;) {
		temp = find;
		find = find->next; //寻找指定号码的宿舍
	}


		temp->next = find->next; // 让目标节点的前驱指向目标节点的后继
	
	present_left.free_size--;  //更新剩余链表的数量

	find->name = name;
	find->num = num;
	find->next = NULL;

	if (isempty())   //insert操作是从前往后插入
		front->next = find;
	else
		rear->next = find;
	rear = find;

	//更新已用链表的数量
	use_size++;
	return true;
	

}

//为学生分配宿舍，从可用宿舍链表头摘取一间宿舍，

//按宿舍号升序挂在已用宿舍链表中

bool Dorm_use::Dorm_use_push(const char * name, Dorm_free & present_left)
{
	if (present_left.isempty()) {
		cout << "There is no Dorm left!\n";
		return false;
	}

	Dorm_data * temp= present_left.front->next;
	
	//更新剩余宿舍链表的头结点指向及数量
	present_left.front->next = temp->next;    // 从原链表中剥离目标节点

	present_left.free_size--;//更新剩余宿舍链表的数量



	temp->name = name;

	if (isempty())  // 若已用链表为空，则插入在第一个位置
	{
		front->next = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = front->next; // 使temp连接第二个结点 
		front->next = temp;//插入第一个位置
	}

	//更新已用链表的数量
	use_size++;
	return true;
}

// 输出已用了宿舍的链表
void Dorm_use::display_use()const
{
	Dorm_data * temp = front->next;
	while (temp)
	{
		cout << temp->name << "(" << temp->num << ")" ;
		temp = temp->next;
		if (temp)cout << "-";

	}
	cout << endl;
}
// 输出前对已用链表进行排序，从小到大
inline bool Dorm_use::Sort()
{
	// 伪指针
	Dorm_data * _last, *_next;
	_last = front->next;  
	_next = _last->next;
	//中间变量
	string temp_name="none";
	int temp_num=0;
	//选择排序法
	for (int i = 0; i < use_size - 1; i++, _last = front->next, _next = _last->next) //每比完一轮使指针重新指向前两个结点
		for (int j = 0; j < use_size - 1 - i; j++)
		{
			if (_last->num > _next->num)
			{
				//更换name
				temp_name = _last->name;
				_last->name = _next->name;
				_next->name = temp_name;
				//更换num
				temp_num = _last->num;
				_last->num = _next->num;
				_next->num = temp_num;

				
			}
			_last = _next;
			_next = _next->next; // 把结点更新放在外部
		}

	return true;
}
#endif // !DORMITORY_H_


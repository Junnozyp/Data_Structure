#ifndef DORMITORY_H_
#define DORMITORY_H_
#include<iostream>
#include<string>
#include<exception>
using namespace std;
//����ĳУ��20�����ᣬ������101��102��..., 120��ÿ��ֻסһ��ѧ������ʼ�����������á�
//����������������������Ϳ�����������ά������Ĺ���ʵ��������䡢���ύ�ء�
//
//Լ��������������������������ӡ���ʼ������������Ҳ��������������ӡ�
//
//�������ӿ�������������ժȡ��һ����������ѧ����ѧ�����ص�������ڿ��������������
//
//��ע��ʹ��list������̬�������ÿ����������ͽ��ز��ɹ��������

const int Dorm_size = 20;

// �����쳣���ơ�����������߽�
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

class Dorm_free;  //ǰ������
struct Dorm_data
{
	int num;
	string name;
	Dorm_data * next;
};
// ����������
class Dorm_use
{
private:
	Dorm_data * Dormuse_list;  //�Ѿ�ʹ�õ���������
	int use_size;       // �Ѿ�ʹ�õ�����
	Dorm_data * front;   //ͷָ��
	Dorm_data * rear;  //βָ��
public:
	friend class Dorm_free;   //������Ԫ��
	Dorm_use();
	~Dorm_use();
	bool Dorm_use_insert(const char * name, int num, Dorm_free & present_left);  //��ʼ���亯��-zָ������
	bool Dorm_use_push( const char * name,Dorm_free & present_left);  //�������еĿ�����
	void display_use()const;
	bool Sort();
	bool isfull()const { return use_size == Dorm_size; }
	bool isempty()const { return use_size == 0; }
};
//ʣ��������
class Dorm_free
{
private:
	Dorm_data * Dormfree_list;  // ʣ�����������
	int free_size;    //ʣ��Ŀ���������
	Dorm_data * front;   //ͷָ��
	Dorm_data * rear;   //βָ��
public:
	friend class Dorm_use;   //������Ԫ��
	Dorm_free();
	~Dorm_free();
	bool Dorm_free_pop(int num,Dorm_use & present_use);  //�黹����
	void display_free()const;
	bool isempty()const { return free_size == 0; }
};

// ʣ������Ĺ��캯��
Dorm_free::Dorm_free():free_size(Dorm_size)
{
	front = new Dorm_data;
	front->num = -1;
	front->next = NULL;
	rear = front;
	for (int i = 0; i < Dorm_size; i++)  //����20���ڴ汣��20������
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

// ʣ���������������
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
// �黹ָ�����ŵ����ᣬ���������������
bool Dorm_free::Dorm_free_pop(int num, Dorm_use & present_use)
{
	if (num > 120 || num < 101) throw Out_Of_Bounds("Returning Dormitory fail!");
	if (present_use.isempty())
	{
		cout << "There is no Dormitory under use!\n";
		return false;
	}
	Dorm_data * temp=NULL;  //ָʾfind��ǰһ����㣬��������
	Dorm_data * find = present_use.front;  // Ѱ��ָ�������������
	for (; find->num != num;) {
		temp = find;
		find = find->next; //Ѱ��ָ�����������

	}
	temp->next = find->next;  //������������������Ľ��

	find->name = "none";//�������
	rear->next = find; //���ڿ�������β��
	find->next = NULL;

	rear = find;  //����βָ��
	//���¼���ֵ
	present_use.use_size--;
	free_size++;

	return true;
}
// ���ʣ������������
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

// ��������Ĺ��캯��
Dorm_use::Dorm_use():use_size(0)
{
	front= new Dorm_data;
	rear = front;
	front->name = "none";
	front->num = -1;
	front->next = NULL;
}


// �����������������
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

// ��ʼ�Ĳ������
bool Dorm_use::Dorm_use_insert(const char * name, int num, Dorm_free & present_left)
{
	if (present_left.isempty()) {
		cout << "There is no Dorm left!\n";
		return false;
	}
	if (num > 120 || num < 101) throw Out_Of_Bounds("insert fail!");

	Dorm_data * temp=NULL;  //ָʾfind��ǰһ����㣬��������
	Dorm_data * find=present_left.front;

	for (; find->num != num;) {
		temp = find;
		find = find->next; //Ѱ��ָ�����������
	}


		temp->next = find->next; // ��Ŀ��ڵ��ǰ��ָ��Ŀ��ڵ�ĺ��
	
	present_left.free_size--;  //����ʣ�����������

	find->name = name;
	find->num = num;
	find->next = NULL;

	if (isempty())   //insert�����Ǵ�ǰ�������
		front->next = find;
	else
		rear->next = find;
	rear = find;

	//�����������������
	use_size++;
	return true;
	

}

//Ϊѧ���������ᣬ�ӿ�����������ͷժȡһ�����ᣬ

//����������������������������

bool Dorm_use::Dorm_use_push(const char * name, Dorm_free & present_left)
{
	if (present_left.isempty()) {
		cout << "There is no Dorm left!\n";
		return false;
	}

	Dorm_data * temp= present_left.front->next;
	
	//����ʣ�����������ͷ���ָ������
	present_left.front->next = temp->next;    // ��ԭ�����а���Ŀ��ڵ�

	present_left.free_size--;//����ʣ���������������



	temp->name = name;

	if (isempty())  // ����������Ϊ�գ�������ڵ�һ��λ��
	{
		front->next = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = front->next; // ʹtemp���ӵڶ������ 
		front->next = temp;//�����һ��λ��
	}

	//�����������������
	use_size++;
	return true;
}

// ������������������
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
// ���ǰ����������������򣬴�С����
inline bool Dorm_use::Sort()
{
	// αָ��
	Dorm_data * _last, *_next;
	_last = front->next;  
	_next = _last->next;
	//�м����
	string temp_name="none";
	int temp_num=0;
	//ѡ������
	for (int i = 0; i < use_size - 1; i++, _last = front->next, _next = _last->next) //ÿ����һ��ʹָ������ָ��ǰ�������
		for (int j = 0; j < use_size - 1 - i; j++)
		{
			if (_last->num > _next->num)
			{
				//����name
				temp_name = _last->name;
				_last->name = _next->name;
				_next->name = temp_name;
				//����num
				temp_num = _last->num;
				_last->num = _next->num;
				_next->num = temp_num;

				
			}
			_last = _next;
			_next = _next->next; // �ѽ����·����ⲿ
		}

	return true;
}
#endif // !DORMITORY_H_


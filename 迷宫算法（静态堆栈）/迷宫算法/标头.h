

#include<iostream>

using namespace std;


//�Թ��㷨������ṹ
struct Position
{
	int row;
	int col;
	
};

//��̬��ջ�ඨ��
template <class T>
class Stack
{
private:
	int top;
	int Maxtop; //����ջ��ֵ
	T * stack;
	int size;
public:
	Stack(int MaxStackSize = 20);
	~Stack()
	{
		delete[]stack;
	}
	bool isEmpty()const {return  size == 0; }
	bool isFull()const { return size == Maxtop; }
	T Top()const;
	int Length()const { return size; }
	Stack<T> & Add(const T & item);
	Stack<T> & Delete(T & item);
	void Show()const;
};

template<class T>
inline void  Stack<T>::Show()const
{
	for(int i=0;i<size;i++)
	cout << "( "<<stack[i].row<<", "<<stack[i].col<<")" << "--> ";
}
template<class T>
inline Stack<T>::Stack(int MaxStackSize)
{
	Maxtop = MaxStackSize - 1;
	stack = new T[MaxStackSize];
	top = 0;
	size = 0;
}

template<class T>
inline T Stack<T>::Top() const
{
	//if(isEmpty())throw 
	return stack[top];
}

template<class T>
inline Stack<T>& Stack<T>::Add(const T & item)
{
	// TODO: �ڴ˴����� return ���
	//if(isFull())

	stack[top++] = item;
	size++;
	return *this;
	
}

template<class T>
inline Stack<T>& Stack<T>::Delete(T & item)
{
	// TODO: �ڴ˴����� return ���
	//if(isEmpty())
	item = stack[top--];
	return *this;
	
}

int m;
//�Թ��㷨

Stack<Position> * path; //���浱ǰ��·��

bool FindPath(int (*maze)[12])
{
	path = new Stack<Position>(m*m - 1);
	Position offset[4];
	offset[0].row = 0; offset[0].col = 1;//right
	offset[1].row = 1; offset[1].col = 0;//down
	offset[2].row = 0; offset[2].col = -1;//left
	offset[3].row = -1, offset[3].col = 0;//up
	for (int i = 0; i <= m + 1; i++)  //ͨ���������Ա߼�һȦ�����������߽紦��
	{
		maze[0][i] = maze[m + 1][i] = 1; //�ڵײ��Ͷ�������ϰ�
		maze[i][0] = maze[i][m + 1] = 1;//�����������ϰ�
	}

	Position here;
	here.row = 1;
	here.col = 1;
	maze[1][1] = 1;//��ֹ��� ��������趨Ϊ��1,1��
	int option = 0;//������
	int Lastoption = 3;
	//Ѱ��һ��·��
	while (here.row != m || here.col != m)
	{
		int r, c;
		while (option <= Lastoption)
		{
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)break;
			option++;//��һ��ѡ��
		}
		if (option <= Lastoption)//�ҵ�
		{
			path->Add(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 1;//�����ϰ���ֹ��һ�η���
			option = 0;
			
		}
		else
		{
			if (path->isEmpty())return false;
			Position next;
			path->Delete(next);
			if (next.row == here.row)//��ʣ�� �º����ѡ��
				option = 2 + next.col - here.col;
			else//��ʣ�����ѡ��
				option = 3 + next.row - here.row;
			here = next;
		}
	}
	if (!path->isEmpty())
	{
		path->Show();
		cout << endl;
	}
	return true;//�����Թ����
}





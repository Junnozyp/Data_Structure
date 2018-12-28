

#include<iostream>

using namespace std;


//迷宫算法的所需结构
struct Position
{
	int row;
	int col;
	
};

//静态堆栈类定义
template <class T>
class Stack
{
private:
	int top;
	int Maxtop; //最大的栈顶值
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
	// TODO: 在此处插入 return 语句
	//if(isFull())

	stack[top++] = item;
	size++;
	return *this;
	
}

template<class T>
inline Stack<T>& Stack<T>::Delete(T & item)
{
	// TODO: 在此处插入 return 语句
	//if(isEmpty())
	item = stack[top--];
	return *this;
	
}

int m;
//迷宫算法

Stack<Position> * path; //保存当前的路径

bool FindPath(int (*maze)[12])
{
	path = new Stack<Position>(m*m - 1);
	Position offset[4];
	offset[0].row = 0; offset[0].col = 1;//right
	offset[1].row = 1; offset[1].col = 0;//down
	offset[2].row = 0; offset[2].col = -1;//left
	offset[3].row = -1, offset[3].col = 0;//up
	for (int i = 0; i <= m + 1; i++)  //通过在数组旁边加一圈屏障来做到边界处理
	{
		maze[0][i] = maze[m + 1][i] = 1; //在底部和顶部添加障碍
		maze[i][0] = maze[i][m + 1] = 1;//在左和右添加障碍
	}

	Position here;
	here.row = 1;
	here.col = 1;
	maze[1][1] = 1;//阻止入口 这里入口设定为（1,1）
	int option = 0;//方法数
	int Lastoption = 3;
	//寻找一条路径
	while (here.row != m || here.col != m)
	{
		int r, c;
		while (option <= Lastoption)
		{
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)break;
			option++;//下一个选择
		}
		if (option <= Lastoption)//找到
		{
			path->Add(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 1;//设置障碍防止再一次访问
			option = 0;
			
		}
		else
		{
			if (path->isEmpty())return false;
			Position next;
			path->Delete(next);
			if (next.row == here.row)//还剩下 下和左的选择
				option = 2 + next.col - here.col;
			else//还剩下左的选择，
				option = 3 + next.row - here.row;
			here = next;
		}
	}
	if (!path->isEmpty())
	{
		path->Show();
		cout << endl;
	}
	return true;//到达迷宫入口
}





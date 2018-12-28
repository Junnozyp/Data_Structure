#define _CRT_SECURE_NO_WARNINGS
#include"Dormitory.h"

int main(void)
{
	Dorm_use use_part;
	Dorm_free free_part;
	char name[10],command[10];
	int num;
	int count = 0;
	cin >> count;
	try {
			for (int i = 0; i < count; i++)
			{
				/*cout << "Enter the " << i << " th" << " 's information:\n";*/
				if(cin>>name>>num)
					use_part.Dorm_use_insert(name, num, free_part);
			}
			/*cout << "Enter the command:\n";*/
	}

	catch (Out_Of_Bounds & ou)  // 捕捉异常
	{
		cout << ou.Type_ex << endl << ou.what() << endl;
		exit(1);
	}

	(cin >> count).get();
	char test[20] = { '\0' };
	try
	{
		for (int i = 0; i < count; i++)
	  {
		cin.getline(test, 20);
		// 输出已用宿舍链表的指令
		if (strcmp(test, "display_use") == 0)
		{
			use_part.Sort();
			use_part.display_use();
			continue;
			
		}
		if (strcmp(test, "display_free") == 0)
		{
			free_part.display_free();
			continue;
		}

		//插入或归还指令
		sscanf(test, "%6s %s", command, name);
		for (int i = 0; i<(sizeof(command) / sizeof(command[0])); i++)
		{
			command[i] = tolower(command[i]);
		}
			if (strcmp(command, "assign") == 0)
			{
				use_part.Dorm_use_push(name, free_part);
				//use_part.display_use();
			}
				
			else if (strcmp(command, "return") == 0)
			{
				char * pt = name;
				int count = 2;
				num = 0;
				while (*pt>= '0'&&*pt <='9')
				{
					num +=( *pt-'0') * pow(10, count--);   // 注意减去字符‘0’对应的ASCII码值，才是真正的数
					pt++;
				}
			
				free_part.Dorm_free_pop(num, use_part);
			//	free_part.display_free();
			}

			else
			{
				cout << "Can't tell the command you input!\n";   
				i--;
				continue;
			}
		
			
	  }
	}
	//捕获异常
	catch (Out_Of_Bounds & ou)
	{
		cout << ou.Type_ex << endl << ou.what() << endl;
		exit(1);
	}

	 use_part.Sort(); 

	use_part.display_use();



	//测试分离字符串的函数
	

	//if (strcmp(test, "display_use")==0)
	//{
	//	cout << "display_use\n";
	//}
	//if (strcmp(test, "display_free")==0)
	//{
	//	cout << "display_free\n";
	//}
	//char name[10] = { '\0' };
	//char command[10] =  { '\0' };
	//char num[3] =  { '\0' };


	//sscanf(test, "%6s %s",command,name);
	//cout << command << "  " << name;

	//for (int i = 0; i<(sizeof(command)/sizeof(command[0])); i++)
	//{
	//	command[i]=tolower(command[i]);
	//}

	//if (strcmp(command, "assign")==0)
	//	cout << endl << "assign command tell\n";
	return 0;
}
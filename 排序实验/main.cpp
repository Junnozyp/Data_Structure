#include"MP.h"
#include<time.h>
#include<stdlib.h>

int main()
{
//	cout<<"The original data shows below:\n"; 
//    for(int i=0;i<10;i++)
//    {
//            cout<<test_data[i].name<<" :   "<<test_data[i].grade<<endl;
//    } 
//    cout<<"After Sorting: \n";
//   // MP_Sequence(data_p,10); //0.01476s
//    XZ_Sequence(data_p,10);  //0.02295s 
//    //QuickSort(data_p,10);  //0.01332s
//    for(int i=0;i<10;i++)
//    {
//            cout<<test_data[i].name<<" :   "<<test_data[i].grade<<endl;
//    } 

	srand(time(NULL));
	for(int i=0;i<100000;i++)
	{
    
		int Randnum=rand()%10000;	
	    data_p1[i].grade=Randnum;
	    data_p1[i].name="aa";
	  // cout<<data_p1[i].name<<" :   "<<data_p1[i].grade<<endl;
	}
	    cout<<"After Sorting: \n";
    //MP_Sequence(data_p1,10000); //5.375s
    XZ_Sequence(data_p1,100000);  //4.965s
    //QuickSort(data_p1,100000);  //3.1721s
    for(int i=0;i<100000;i++)
    {
            cout<<i<<"  "<<data_p1[i].name<<" :   "<<data_p1[i].grade<<endl;
    }
	return 0;
}

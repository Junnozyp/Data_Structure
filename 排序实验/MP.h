
#include"base.h"
using namespace std;

//ц╟ещеепР 
bool MP_Sequence(Data * data, int num)
{
     for(int i=0;i<num-1;i++)
     for(int j=0;j<num-1-i;j++)
     if(data[j].grade>data[j+1].grade)
     {
         Data temp;
         temp=data[j];
         data[j]=data[j+1];
         data[j+1]=temp;
     }                      
     return true;
}


bool XZ_Sequence(Data * data, int num)
{
     for(int i=0;i<num-1;i++)
     {
           int mindex=i;
           for(int j=i+1;j<num-1;j++)    
           
                if(data[j].grade<data[mindex].grade)
                {
                   Data temp;
                   temp=data[j];
                   data[j]=data[mindex];
                   data[mindex]=temp;  
                }
     } 
     return true;  
}

int Partition(Data * data,int low, int high)
{
    Data  temp=data[low];
    int pivotkey=data[low].grade;
    while(low<high)
    {
        while(low<high&&data[high].grade>=pivotkey)--high;
        data[low]=data[high];
        while(low<high&&data[low].grade<=pivotkey)++low;
        data[high]=data[low];
    }
    data[low]=temp;
    return low;
}
    

void Qsort(Data * data, int low, int high)
{
     if(low<high)
     {
        int pivotloc=Partition(data, low, high);
        Qsort(data,low, pivotloc-1);
        Qsort(data,pivotloc+1,high);
     }
}


void QuickSort(Data * data,int num)
{
     Qsort(data,0,num-1);
}

#include<iostream>
#include<string>
using namespace std;

typedef  int T; 
struct Data{
       string name;
       T grade; 
};


//结构体数组 
Data test_data[10]=
{
       {"aa",75},
       {"bb",87},
       {"cc",68},
       {"dd",45},
       {"ee",80},
       {"ff",85},
       {"gg",90},
       {"hh",96},
       {"JJ",88},
       {"KK",93}
};

Data test_data1[100000];


//结构体指针 
Data * data_p=test_data;
Data * data_p1=test_data1;

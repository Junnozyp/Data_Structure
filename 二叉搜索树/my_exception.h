
#pragma once
#include<iostream>
#include<exception>	
using namespace std;

//Òì³£»úÖÆ
class Out_Of_Bounds :public exception
{
public:
	string Type_ex = "none";
	const char * what() { return "out of the range of present part!\n"; }
	Out_Of_Bounds(const char * type);
	~Out_Of_Bounds()
	{

	}
};
Out_Of_Bounds::Out_Of_Bounds(const char * type) {
	Type_ex = type;
}


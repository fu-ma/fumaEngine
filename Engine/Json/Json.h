#pragma once
#include<string>
#include<fstream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
using namespace std;

class Json
{
private:
	static const int MAXSTRING_NUM = 100;
public: // Ã“Iƒƒ“ƒo•Ï”
	static Json *GetInstance();
public:
	void AddString(string Name, string Number);
	void Write();
	float ReadFile(const char *filename, const char *Name);
private:
	ofstream file;
	string fileName = "data.json";
	vector<string> Names{ "Name" };
	vector<string> Numbers{ "Data" };
	FILE *fp;
	char str[MAXSTRING_NUM];
	char name[MAXSTRING_NUM];
	float num;
	errno_t error;
	float number = 0;
};


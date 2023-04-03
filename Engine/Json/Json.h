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
	static const int MAXMAPSIZE_X = 100;
	static const int MAXMAPSIZE_Y = 10;
public: // ê√ìIÉÅÉìÉoïœêî
	static Json *GetInstance();
public:
	void AddString(string Name, string Number);
	void Write();
	float ReadFile(const char *filename, const char *Name);
	int GetMapData(const int y, const int x) { return mapData[y][x]; }
private:
	ofstream file;
	string fileName = "data.json";
	vector<string> Names{ "Name" };
	vector<string> Numbers{ "Data" };
	FILE *fp;
	char str[MAXSTRING_NUM];
	char name[MAXSTRING_NUM];
	char num[MAXSTRING_NUM];
	char arrayNum[MAXSTRING_NUM];
	int OneCharacter;
	errno_t error;
	float number = 0;
	int mapData[MAXMAPSIZE_Y][MAXMAPSIZE_X];
	int x, y;
};


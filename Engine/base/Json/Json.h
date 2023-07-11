#pragma once
#include<string>
#include<fstream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include<DirectXMath.h>
using namespace std;

class Json
{
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
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
	const XMFLOAT2 &GetXmfloat2() { return xmfloat2; }
	const XMFLOAT3 &GetXmfloat3() { return xmfloat3; }
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
	XMFLOAT2 xmfloat2;
	XMFLOAT3 xmfloat3;
	int letterCount;
};


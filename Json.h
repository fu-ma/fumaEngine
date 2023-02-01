#pragma once
#include<string>
#include<fstream>
#include<vector>

using namespace std;

class Json
{
public: // 静的メンバ変数
	static Json *GetInstance();
public:
	void AddString(string Name, string Number);
	void Write();
private:
	ofstream file;
	string fileName = "data.json";
	vector<string> Names{ "Name" };
	vector<string> Numbers{ "Data" };
};


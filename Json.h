#pragma once
#include<string>
#include<fstream>
#include<vector>

using namespace std;

class Json
{
public: // Ã“Iƒƒ“ƒo•Ï”
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


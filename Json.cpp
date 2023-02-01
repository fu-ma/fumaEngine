#include "Json.h"

Json *Json::GetInstance()
{
	static Json json;
	return &json;
}

void Json::AddString(string Name, string Number)
{
	Names.push_back(Name);
	Numbers.push_back(Number);
}

void Json::Write()
{
	file.open(fileName, ios::out);
	file << "{" << endl;
	for (int i = 0; i != Names.size(); ++i)
	{
		file << "\t" << Names[i] << " : " << Numbers[i] << endl;
	}
	file << "}" << endl;
	file.close();
}

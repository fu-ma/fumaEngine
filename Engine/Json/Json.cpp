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

float Json::ReadFile(const char *filename, const char *Name)
{
	error = fopen_s(&fp,filename, "r");
	if (error != 0)
	{
		exit(0);
	}
	else
	{
		//ˆês–Ú‚Í”ò‚Î‚·
		fgets(str, 100, fp);
		//“ñs–Ú‚©‚ç’l‚ð’²‚×‚é
		while (fscanf_s(fp, "%s : %f", name, MAXSTRING_NUM, &num) != EOF)
		{
			if (strcmp(name,Name) == 0)
			{
				number = num;
			}
		}
		fclose(fp);
		return number;
	}

	return 0;
}

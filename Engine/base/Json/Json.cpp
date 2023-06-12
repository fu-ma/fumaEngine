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

float Json::ReadFile(const char *filename, const char* Name)
{
	x = 0;
	y = 0;
	error = fopen_s(&fp,filename, "r");
	if (error != 0)
	{
		exit(0);
	}
	else
	{
		//一行目は飛ばす
		fgets(str, 100, fp);
		//二行目から値を調べる
		while (fscanf_s(fp, "%s : %s", name, MAXSTRING_NUM, num, MAXSTRING_NUM) != EOF)
		{
			//検索をかけた文字列と一致したら
			if (strcmp(name, Name) == 0)
			{
				//[が見つかったら
				if (strcmp(num, "[") == 0)
				{
					//]が見つかるまで続ける
					while (strcmp(arrayNum, "]") != 0)
					{
						fscanf_s(fp, "%s,", arrayNum, MAXSTRING_NUM);
						mapData[y][x] = (int)atof(arrayNum);
						x++;
						if (x > MAXMAPSIZE_X - 1)
						{
							x = 0;
							y++;
						}
						if (y > MAXMAPSIZE_Y - 1)
						{
							break;
						}
					}
				}
				else
				{
					//配列ではない場合数値を読み込む
					number = (float)atof(num);
				}
			}
		}
		fclose(fp);
		return number;
	}

	return 0;
}

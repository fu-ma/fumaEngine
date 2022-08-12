#pragma once
#include<stdio.h>

class csvOpen
{

	FILE *fp;
	int *num[100][100];
public:
	bool csvLoad(const char *filename);
	void mapInit();

	int *GetNum() { return num; }
};


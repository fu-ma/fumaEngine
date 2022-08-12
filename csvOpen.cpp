#include "csvOpen.h"

bool csvOpen::csvLoad(const char *filename)
{
    fp = fopen(filename, "r");

    if (fp == nullptr)
    {
        return false;
    }

    return true;
}

void csvOpen::mapInit()
{
    for (int j = 0; j < 100; j++)
    {
        for (int i = 0; i < 100; i++)
        {
            if (fscanf(fp, "%d,", &num[i][j] != '\0'))
            {
            }
        }
    }
}

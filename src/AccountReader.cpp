#include "pch.h"
#include "AccountReader.h"
#include <string>
#include <fstream>
#include "PlayerBT.h"

ThreadInfo::~ThreadInfo()
{
	delete templateBT;
}

AccountReader::AccountReader()
{
}

AccountReader::~AccountReader()
{
}

bool AccountReader::ReadAccountFile(const char* directory, const char* file, int userNum, ThreadInfo* info)
{
	char filename[64] = { "" };
	strcat_s(filename, sizeof(filename), directory);
	strcat_s(filename, sizeof(filename), "/");
	strcat_s(filename, sizeof(filename), file);
	FILE* fp = nullptr;
	fopen_s(&fp, filename, "r");
	if (fp == nullptr)
	{
		printf("Can't open the account file");
		return false;
	}

	for (int i = 0; i < userNum; ++i)
	{
		fscanf_s(fp, "%llu", &info->info[i].accountNo);
		fscanf_s(fp, "%ls", info->info[i].id, 20);
		fscanf_s(fp, "%ls", info->info[i].nickname, 20);
		fscanf_s(fp, "%s", info->info[i].sessionKey, 65);
	}

	fclose(fp);
	return true;
}

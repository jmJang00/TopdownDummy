#pragma once
#include <vector>

class PlayerBT;

struct DummyAccountInfo
{
	unsigned long long accountNo = 0; 
	wchar_t id[20] = { 0 };
	wchar_t nickname[20] = { 0 };
	char sessionKey[65] = { 0 };
};

struct ThreadInfo
{
	DummyAccountInfo info[5000] = {};
	PlayerBT* templateBT = nullptr;
	int userNum = 0;

	~ThreadInfo();
};

class AccountReader
{
public:

	AccountReader();

	~AccountReader();

	void Init();

	bool ReadAccountFile(const char* directory, const char* file, int userNum, ThreadInfo* info);
};

#include "pch.h"
#include "CAppBuilder.h"
#include <stdio.h>
#include <process.h>
#include <conio.h>
#include <JNet/CMonitorThread.h>

CAppBuilder::CAppBuilder()
	: printLogLevel(0)
	, printMonitor(false)
	, config()
	, monitor(nullptr)
	, systemSection(nullptr)
	, serverSection(nullptr)
	, redisSection(nullptr)
	, dummySection(nullptr)
	, dbSection(nullptr)
	, projectName(nullptr)
{
}

bool CAppBuilder::ReadFile()
{
	if (!config.Read("Config", "config.cnf"))
	{
		return false;
	}

	return true;
}

void CAppBuilder::DeleteSection()
{
	delete systemSection;
	delete serverSection;
	delete redisSection;
	delete dbSection;
	delete dummySection;
}

void CAppBuilder::DefineSystemSection()
{
	if (systemSection != nullptr)
		return;

	systemSection = config.DefineSection<FSystemConfig>("system")
		->FieldInt("print_log_level", &FSystemConfig::printLogLevel, 0)
		->FieldInt("file_log_level", &FSystemConfig::fileLogLevel, 0);
}

void CAppBuilder::DefineServerSection()
{
	if (serverSection != nullptr)
		return;

	serverSection = config.DefineSection<FServerConfig>("config")
		->FieldString("server_ip", &FServerConfig::serverIp, "0.0.0.0")
		->FieldString("server_port", &FServerConfig::serverPort, "0")
		->FieldInt("worker_thread_num", &FServerConfig::workerThreadNum, 0)
		->FieldInt("concurrent_thread_num", &FServerConfig::concurrentThreadNum, 0)
		->FieldInt("max_sessions", &FServerConfig::maxSessions, 0)
		->FieldInt("sendbuf_zero", &FServerConfig::sendBufZero, 0)
		->FieldInt("encoding", &FServerConfig::encoding, 0)
		->FieldInt("nagle", &FServerConfig::nagle, 0);
}

void CAppBuilder::DefineRedisSection()
{
	if (redisSection != nullptr)
		return;

	redisSection = config.DefineSection<FRedisConfig>("redis")
		->FieldString("server_ip", &FRedisConfig::host, "0.0.0.0")
		->FieldInt("server_port", &FRedisConfig::port, 0)
		->FieldInt("timeout", &FRedisConfig::timeout, 0);
}

void CAppBuilder::DefineDBSection()
{
	if (dbSection != nullptr)
		return;

	dbSection = config.DefineSection<FDBConfig>("db")
		->FieldString("host", &FDBConfig::host, "")
		->FieldInt("port", &FDBConfig::port, 0)
		->FieldString("user", &FDBConfig::user, "")
		->FieldString("pw", &FDBConfig::pw, "")
		->FieldString("db", &FDBConfig::db, "");
}

void CAppBuilder::DefineDummySection()
{
	if (dummySection != nullptr)
		return;

	dummySection = config.DefineSection<FDummyConfig>("dummy")
		->FieldString("server_ip", &FDummyConfig::serverIp, "0.0.0.0")
		->FieldString("server_port", &FDummyConfig::serverPort, "0")
		->FieldString("bind_ip", &FDummyConfig::bindIp, "0.0.0.0")
		->FieldInt("worker_thread_num", &FDummyConfig::workerThreadNum, 0)
		->FieldInt("concurrent_thread_num", &FDummyConfig::concurrentThreadNum, 0)
		->FieldInt("max_sessions", &FDummyConfig::maxSessions, 0)
		->FieldInt("sendbuf_zero", &FDummyConfig::sendBufZero, 0)
		->FieldInt("encoding", &FDummyConfig::encoding, 0)
		->FieldInt("nagle", &FDummyConfig::nagle, 0);
}

bool CAppBuilder::LoadSystemConfig(FSystemConfig* systemConfig, const char* name)
{
	if (name != nullptr)
	{
		dbSection->ChangeSectionName(name);
	}

	return config.LoadOne(*systemSection, *systemConfig);
}

bool CAppBuilder::LoadServerConfig(FServerConfig* serverConfig, const char* name)
{
	if (name != nullptr)
	{
		dbSection->ChangeSectionName(name);
	}

	return config.LoadOne(*serverSection, *serverConfig);
}

bool CAppBuilder::LoadRedisConfig(FRedisConfig* redisConfig, const char* name)
{
	if (name != nullptr)
	{
		dbSection->ChangeSectionName(name);
	}

	return config.LoadOne(*redisSection, *redisConfig);
}

bool CAppBuilder::LoadDBConfig(FDBConfig* dbConfig, const char* name)
{
	if (name != nullptr)
	{
		dbSection->ChangeSectionName(name);
	}

	return config.LoadOne(*dbSection, *dbConfig);
}

bool CAppBuilder::LoadDummyConfig(FDummyConfig* dummyConfig, const char* name)
{
	if (name != nullptr)
	{
		dummySection->ChangeSectionName(name);
	}

	return config.LoadOne(*dummySection, *dummyConfig);
}

void CAppBuilder::PrintHelpStr()
{
	static const char* helpStr =
		"=== %S Control Keys ===\n"
		"\n"
		"[q] Quit %S\n"
		"    - Stop %S and exit\n"
		"\n"
		"[s] Save profiler data\n"
		"    - Output to Profile.txt\n"
		"\n"
		"[r] Reset profiler\n"
		"\n"
		"[c] Force crash (test)\n"
		"\n"
		"[d] Debug Toggle (test)\n"
		"\n"
		"[m] Monitor Toggle (test)\n"
		"\n"
		"[p][1-3] Set console log level 1:ERROR 2:SYSTEM 3:DEBUG\n"
		"\n"
		"[f][0-3] Set file log level 1:ERROR 2:SYSTEM 3:DEBUG\n"
		"\n"
		"[Any other key] Show monitoring status\n"
		"    - Display current %S statistics\n"
		"    - Press any key to return to control input\n"
		"\n"
		"===========================\n";

	printf(helpStr, projectName, projectName, projectName, projectName);
}

void CAppBuilder::Pause(const char* msg)
{
	if (msg != nullptr)
	{
		printf(msg);
	}
	DISABLE_WARNINGS_BEGIN(WARNING_6031);
	_getch();
	DISABLE_WARNINGS_END();
}

bool CAppBuilder::Control()
{
	int ch = _getch();

	bool noInput = false;

	printf("%c \n", ch);

	if (ch == 'q')
	{
		return false;
	}
	else if (ch == 's')
	{
		ProfileDataOutText(L"Profiler", L"Profile.txt");
	}
	else if (ch == 'r')
	{
		ProfileReset();
	}
	else if (ch == 'c')
	{
		CRASH(true);
	}
	else if (ch == 'p')
	{
		printf("Current print log level: %d\n", CLogger::GetPrintLogLevel());
		printf("Select print log level:");
		printf("\n> ");
		ch = _getch();
		// 0은 모니터링 정보 표시 여부를 나타내기 위해 사용
		if (ch == '1')
		{
			printf("Set to 1\n");
			printLogLevel = 1;
		}
		else if (ch == '2')
		{
			printf("Set to 2\n");
			printLogLevel = 2;
		}
		else if (ch == '3')
		{
			printf("Set to 3\n");
			printLogLevel = 3;
		}
	}
	else if (ch == 'f')
	{
		printf("Current file log level: %d", CLogger::GetFileLogLevel());
		printf("Select file log level:");
		printf("\n> ");
		ch = _getch();
		printf("\n");
		if (ch == '0')
		{
			printf("Set to 0\n");
			CLogger::SetFileLogLevel(0);
		}
		else if (ch == '1')
		{
			printf("Set to 1\n");
			CLogger::SetFileLogLevel(1);
		}
		else if (ch == '2')
		{
			printf("Set to 2\n");
			CLogger::SetFileLogLevel(2);
		}
		else if (ch == '3')
		{
			printf("Set to 3\n");
			CLogger::SetFileLogLevel(3);
		}
	}
	else if (ch == 'm')
	{
		printMonitor ^= 1;
	}
	else if (ch == 'h')
	{
		PrintHelpStr();
	}
	else
	{
		if (!ControlExtension(ch))
		{
			noInput = true;
		}
	}

	if (noInput)
	{
		printf("not registered command\n");
		printf("Switch to normal mode... \n\n");
		CLogger::SetPrintLogLevel(printLogLevel);
		monitor->Turn(printMonitor);
		Pause();
		CMonitorThread::Turn(false);
		CLogger::SetPrintLogLevel(0);
		printf("Switch to command mode... \n");
		printf("> ");
	}
	else
	{
		printf("> ");
	}

	return true;
}

bool CAppBuilder::Start(const wchar_t* name)
{
	projectName = name;

	OnLibInit();

	do
	{
		printf("Switch to normal mode...\n\n");
		PrintHelpStr();

		INetworkEntity* net = nullptr;
		net = OnStart();
		if (!net)
		{
			OnLibRelease();
			return false;
		}

		monitor = new CMonitorThread(name, net);
		monitor->Start();

		bool first = true;

		while (1)
		{
			if (!first)
			{
				if (!Control())
				{
					CLogger::SetPrintLogLevel(printLogLevel);
					monitor->Turn(false);
					monitor->Stop();
					delete monitor;
					OnExit();
					OnLibRelease();
					return true;
				}
			}
			else
			{
				CMonitorThread::Turn(false);
				CLogger::SetPrintLogLevel(0);
				printf("Switch to command mode... \n");
				printf("> ");
				first = false;
			}
		}

	} while (0);
}

bool CAppBuilder::BuildAndStart(const wchar_t* name)
{
	if (!ReadFile())
	{
		Pause("ReadFile() failed. Press any key to exit...\n");
		return false;
	}

	DefineSection();

	if (!LoadSection())
	{
		DeleteSection();
		Pause("LoadSection() failed. Press any key to exit...\n");
		return false;
	}

	DeleteSection();

	printMonitor = false;

	if (!Configure())
	{
		Pause("Configure() failed. Press any key to exit...\n");
		return false;
	}

	printLogLevel = CLogger::GetPrintLogLevel();

	Pause("Press any key to start...\n");
	Start(name);
	Pause("Press any key to exit...\n");

	return true;
}

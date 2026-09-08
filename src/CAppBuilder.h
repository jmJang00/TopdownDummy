#pragma once
#include <JCore/MyConfigs.h>
#include <JParse/Config.h>

template <typename T>
class SectionMeta;

class INetworkEntity;
class CMonitorThread;
struct FSystemConfig;
struct FServerConfig;
struct FRedisConfig;
struct FDBConfig;

class CAppBuilder
{
public:
	CAppBuilder();

	virtual void DefineSection() = 0;
	virtual bool LoadSection() = 0;
	virtual bool Configure() = 0;
	virtual INetworkEntity* OnStart() = 0;
	virtual void OnExit() = 0;
	virtual void OnLibInit() = 0;
	virtual void OnLibRelease() = 0;
	virtual bool ControlExtension(char ch) { return false; }

	void DefineSystemSection();
	void DefineServerSection();
	void DefineRedisSection();
	void DefineDBSection();
	void DefineDummySection();
	bool LoadSystemConfig(FSystemConfig* config, const char* name = nullptr);
	bool LoadServerConfig(FServerConfig* config, const char* name = nullptr);
	bool LoadRedisConfig(FRedisConfig* config, const char* name = nullptr);
	bool LoadDBConfig(FDBConfig* config, const char* name = nullptr);
	bool LoadDummyConfig(FDummyConfig* config, const char* name = nullptr);

	void PrintHelpStr();
	void Pause(const char* msg = nullptr);
	bool Control();
	bool Start(const wchar_t* name);
	bool BuildAndStart(const wchar_t* name);

private:
	bool ReadFile();
	void DeleteSection();

protected:
	const wchar_t* projectName;
	int printLogLevel;
	bool printMonitor;
	Config config;
	SectionMeta<FDBConfig>* dbSection;
	SectionMeta<FSystemConfig>* systemSection;
	SectionMeta<FServerConfig>* serverSection;
	SectionMeta<FRedisConfig>* redisSection;
	SectionMeta<FDummyConfig>* dummySection;
	CMonitorThread* monitor;
};

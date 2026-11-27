#include "pch.h"
#include <JCore/Initialize.h>
#include <JNet/Initialize.h>
#include "BTParser.h"
#include "DummyClient.h"
#include "CAppBuilder.h"

class CDummyBuilder : public CAppBuilder
{
public:
	CDummyBuilder()
		: dummyThreadSection(nullptr)
	{

	}

	void DefineSection()
	{
		DefineDummySection();

		dummyThreadSection = config.DefineSection<FDummyThreadConfig>("thread")
			->FieldString("user_bt_file", &FDummyThreadConfig::userBTFile, "0.0.0.0")
			->FieldString("user_info_file", &FDummyThreadConfig::userInfoFile, "0")
			->FieldInt("user_num", &FDummyThreadConfig::userNum, 0);
	}

	bool LoadSection()
	{
		if (!LoadDummyConfig(&dummyConfig))
		{
			return false;
		}

		dummyThreadConfigs = config.Load(*dummyThreadSection);
		if (dummyThreadConfigs.size() == 0)
		{
			return false;
		}

		return true;
	}

	bool Configure() override
	{
		CLogger::SetFileLogLevel(2);
		CLogger::SetPrintLogLevel(2);
		return true;
	}

	INetworkEntity* OnStart()
	{
		dummy = new DummyClient();
		if (!dummy->Start(dummyConfig, dummyThreadConfigs))
		{
			printf("dummy client can't start\n");
			return nullptr;
		}
		return dummy;
	}

	void OnExit()
	{
		dummy->Stop();
		delete dummy;
	}

	void OnLibInit()
	{
		JCoreInit::Initialize();
		JNetInit::Initialize();
	}

	void OnLibRelease()
	{
		JNetInit::Release();
		JCoreInit::Release();
	}

private:
	SectionMeta<FDummyThreadConfig>* dummyThreadSection;
	std::vector<FDummyThreadConfig> dummyThreadConfigs;
	FDummyConfig dummyConfig;
	DummyClient* dummy = nullptr;
};

int main(int argc, char* argv[])
{
	CDummyBuilder builder;
	builder.BuildAndStart(L"TopdownDummy");
	return 0;
}


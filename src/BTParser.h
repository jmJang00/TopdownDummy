#pragma once
#include <JParse/BaseCompiler.h>
#include <map>
#include <string>

class PlayerBT;

typedef std::map<std::string, PlayerBT*> bt_map;

class BTParser : public BaseCompiler
{
public:
	BTParser();

	~BTParser();

	void Init();

	bool Evaluate(LCRSTree* tree) override;

public:
	bt_map btMap;
};

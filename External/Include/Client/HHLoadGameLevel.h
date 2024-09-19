#pragma once
#include <Engine/singleton.h>

#include <Engine/HHLevel.h>

class HHLoadGameLevel
	: public HHSingleton<HHLoadGameLevel>
{
	SINGLE(HHLoadGameLevel);

public:
	void Initialize();

	void ChangeLevelByName(const wstring& levelName, LEVEL_STATE state);
	
private:
	HHLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
	unordered_map<wstring, LEVEL_TYPE> levelMap;

};


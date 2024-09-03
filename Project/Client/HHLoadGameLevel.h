#pragma once
#include <Engine/singleton.h>

#include <Engine/HHLevel.h>

class HHLoadGameLevel
	: public HHSingleton<HHLoadGameLevel>
{
	SINGLE(HHLoadGameLevel);

public:
	void Initialize();
	
private:
	HHLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];

};


#pragma once

class HHLevel;
class HHGameObject;

class HHLevelMgr
	: public HHSingleton<HHLevelMgr>
{
	SINGLE(HHLevelMgr);

public:
	void Initialize();
	void Progress();

	friend class HHTaskMgr;

	HHLevel* GetCurrentLevel() { return m_CurLevel; }

	void LevelChanged();
	bool IsLevelChanged() { return m_LevelChanged; }

	HHGameObject* FindObjectByName(const wstring& _Name);

private:
	HHLevel*	m_CurLevel;
	HHLevel*	m_arrLevel[(UINT)LEVEL_TYPE::END];
	bool		m_LevelChanged;

	bool		ChangeLevel(HHLevel* _NextLevel);

};

#pragma once

class HHTaskMgr
	: public HHSingleton<HHTaskMgr>
{
	SINGLE(HHTaskMgr)
public:
	void Tick();
	void AddTask(const tTask& _Task);

private:
	vector<tTask>			m_vecTask;
	vector<HHGameObject*>	m_GC;		// Garbage Collector;

	void ClearGarbageCollector();
	void ExecuteTask();

};

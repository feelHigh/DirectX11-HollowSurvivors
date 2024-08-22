#pragma once

class HHTimeMgr
	: public HHSingleton<HHTimeMgr>
{
	SINGLE(HHTimeMgr);

public:
	void Initialize();
	void Tick();
	void Render();

	float GetDeltaTime() { return m_DeltaTime; }
	float GetTime() { return m_Time; }

	float GetEngineDeltaTime() { return m_E_DeltaTime; }
	float GetEngineTime() { return m_E_Time; }

	UINT GetFPS() { return m_FPS; }

private:
	// LARGE_INTEGER - 8 ����Ʈ ���� ���
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	UINT			m_FPS;

	float			m_DeltaTime;	// ������ ���� �ð�( 1 ������ �����ϴµ� �ɸ��� �ð� )
	float			m_Time;			// ���α׷��� ���� ���ķ� ����� �ð�

	float			m_E_DeltaTime;	// ������ ���� �ð�(Engine)
	float			m_E_Time;		// ���α׷��� ���� ���ķ� ����� �ð�(Engine)

	wchar_t			m_TimeInfo[255];

};

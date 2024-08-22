#pragma once

typedef void(*OBJECT_SAVE)(FILE*, class HHGameObject*);
typedef HHGameObject* (*OBJECT_LOAD)(FILE*);

class HHEngine
	: public HHSingleton<HHEngine>
{	
	SINGLE(HHEngine);
public:
	int Initialize(HWND _wnd, POINT _ptResolution, OBJECT_SAVE _SaveFunc, OBJECT_LOAD _Func);
	void Progress();
	void ChangeWindowScale(UINT _Width, UINT _Height);

	FMOD::System* GetFMODSystem() { return m_FMODSystem; }

	HWND GetMainWnd() { return m_hWnd; }

private:
	HWND			m_hWnd;
	POINT			m_ptResolution;
	FMOD::System*	m_FMODSystem;  // FMOD ������ Ŭ����

};

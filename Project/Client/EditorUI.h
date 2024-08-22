#pragma once

#include "ImGui/imgui.h"

class EditorUI
{
public:
	EditorUI();
	virtual ~EditorUI();

	virtual void Initialize() {};
	virtual void Tick();
	virtual void Update() = 0;

	void SetActive(bool _Active);
	bool IsActive() { return m_Active; }

	void UseMenuBar(bool _Use) { m_UseMenuBar = _Use; }
	void SetMove(bool _Move) { m_Move = _Move; }

	void SetModal(bool _Modal) { m_Modal = _Modal; }
	bool IsModal() { return m_Modal; }

	void SetFocus();

	UINT GetID() { return m_ID; }

	void SetName(const string& _Name);
	const string& GetName() { return m_Name; }
	const string& GetFullName() { return m_FullName; }

	void AddChildUI(EditorUI* _UI);
	const vector<EditorUI*>& GetChildUI() { return m_vecChildUI; }

	EditorUI* GetParentUI() { return m_ParentUI; }

	void SetChildBorder(bool _Set) { m_ChildBorder = _Set; }
	void SetChildSize(ImVec2 _Size) { m_ChildSize = _Size; }

private:
	static UINT			m_GlobalID;

	string				m_Name;
	string				m_FullName;
	const UINT			m_ID;
	bool				m_Active;

	EditorUI*			m_ParentUI;
	vector<EditorUI*>	m_vecChildUI;

	ImVec2				m_ChildSize;

	bool				m_Modal;
	bool				m_ChildBorder;
	bool				m_UseMenuBar;
	bool				m_Move;

	virtual void Activate() {}
	virtual void Deactivate() {}

};

typedef void(EditorUI::* DELEGATE_0)(void);
typedef void(EditorUI::* DELEGATE_1)(DWORD_PTR);
typedef void(EditorUI::* DELEGATE_2)(DWORD_PTR, DWORD_PTR);
typedef void(EditorUI::* DELEGATE_3)(DWORD_PTR, DWORD_PTR, DWORD_PTR);

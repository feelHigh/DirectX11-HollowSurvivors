#include "pch.h"
#include "Outliner.h"

#include "TreeUI.h"
#include "Inspector.h"
#include "HHEditorMgr.h"

#include <Engine/HHLevelMgr.h>
#include <Engine/HHLevel.h>
#include <Engine/HHLayer.h>
#include <Engine/HHGameObject.h>

Outliner::Outliner()
{
	m_Tree = new TreeUI;
	m_Tree->SetName("OutlinerTree");
	AddChildUI(m_Tree);

	// 루트 보이지 않기
	m_Tree->ShowRoot(false);

	// Drag, Drop On
	m_Tree->UseDrag(true);
	m_Tree->UseDrop(true);

	// Clicked Delegate 등록
	m_Tree->AddClickedDelegate(this, (DELEGATE_1)&Outliner::GameObjectClicked);

	// Self DragDrop Delegate 등록
	m_Tree->AddDragDropDelegate(this, (DELEGATE_2)&Outliner::GameObjectAddChild);

	// 외부 드랍 Delegate 등록
	m_Tree->AddDropDelegate(this, (DELEGATE_2)&Outliner::DroppedFromOuter);
	m_Tree->SetDropPayLoadName("ContentTree");

	// Asset 상태를 Content 의 TreeUI 에 반영
	RenewLevel();
}

Outliner::~Outliner()
{
}

void Outliner::Update()
{
	if (HHLevelMgr::GetInstance()->IsLevelChanged())
		RenewLevel();
}

void Outliner::RenewLevel()
{
	// 모든 내용 삭제
	m_Tree->Clear();

	// 루트노드 생성
	TreeNode* pRootNode = m_Tree->AddNode(nullptr, "Root", 0);

	HHLevel* pLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
	if (nullptr == pLevel)
		return;

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		HHLayer* pLayer = pLevel->GetLayer(i);
		const vector<HHGameObject*>& vecObjects = pLayer->GetParentObjects();

		for (size_t i = 0; i < vecObjects.size(); ++i)
		{
			AddGameObject(pRootNode, vecObjects[i]);
		}
	}
}

void Outliner::AddGameObject(TreeNode* pNode, HHGameObject* _Object)
{
	string ObjectName = string(_Object->GetName().begin(), _Object->GetName().end());

	TreeNode* pObjectNode = m_Tree->AddNode(pNode, ObjectName.c_str(), (DWORD_PTR)_Object);

	const vector<HHGameObject*>& vecChild = _Object->GetChildObjects();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddGameObject(pObjectNode, vecChild[i]);
	}
}

void Outliner::GameObjectAddChild(DWORD_PTR _Param1, DWORD_PTR _Param2)
{
	TreeNode* pDragNode = (TreeNode*)_Param1;
	TreeNode* pDropNode = (TreeNode*)_Param2;

	HHGameObject* pDragObject = (HHGameObject*)pDragNode->GetData();
	HHGameObject* pDropObject = nullptr;

	// Drag 오브젝트를 Drop 오브젝트의 자식으로 넣어준다.
	if (pDropNode)
	{
		pDropObject = (HHGameObject*)pDropNode->GetData();

		// 자식으로 들어갈 오브젝트가 부모(조상) 중 하나였다면 무시한다.
		if (pDropObject->IsAncestor(pDragObject))
			return;

		pDropObject->AddChild(pDragObject);
	}

	// Drop 목적지가 없기 때문에, Drag 오브젝트를 최상위 부모로 만들어준다.
	else
	{
		if (!pDragObject->GetParentObject())
			return;

		// 부모오브젝트랑 연결을 끊고
		pDragObject->DeregisterChild();

		// 본인 소속 레이어에 최상위 부모로서 재등록 한다.
		HHLevelMgr::GetInstance()->GetCurrentLevel()->RegisterAsParent(pDragObject->GetLayerIndex(), pDragObject);
	}
}

void Outliner::DroppedFromOuter(DWORD_PTR _OuterData, DWORD_PTR _DropNode)
{
	TreeNode* ContentNode = *((TreeNode**)_OuterData);
	TreeNode* DropNode = (TreeNode*)_DropNode;
}

void Outliner::GameObjectClicked(DWORD_PTR _Param)
{
	TreeNode* pNode = (TreeNode*)_Param;

	HHGameObject* pObject = (HHGameObject*)pNode->GetData();

	Inspector* pInspector = (Inspector*)HHEditorMgr::GetInstance()->FindEditorUI("Inspector");
	pInspector->SetTargetObject(pObject);
	//ImGui::SetWindowFocus(nullptr);
}

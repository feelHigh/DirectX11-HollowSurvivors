#include "pch.h"
#include "Inspector.h"

#include <Engine/HHLevelMgr.h>
#include <Engine/HHLevel.h>
#include <Engine/HHLayer.h>
#include <Engine/HHGameObject.h>
#include <Engine/components.h>

#include "TransformUI.h"
#include "Collider2DUI.h"
#include "Light2DUI.h"
#include "CameraUI.h"
#include "MeshRenderUI.h"
#include "FlipbookRenUI.h"
#include "TileMapUI.h"
#include "ParticleSystemUI.h"

#include "MeshUI.h"
#include "MeshDataUI.h"
#include "TextureUI.h"
#include "PrefabUI.h"
#include "TextureUI.h"
#include "MaterialUI.h"
#include "SpriteUI.h"
#include "FlipBookUI.h"
#include "SoundUI.h"
#include "GraphicShaderUI.h"
#include "ComputeShaderUI.h"
#include "ScriptUI.h"
#include "TextUI.h"
#include "FSMUI.h"

void Inspector::Initialize()
{
	CreateComponentUI();

	CreateAssetUI();


	if (nullptr == m_TargetObject)
	{
		SetTargetObject(HHLevelMgr::GetInstance()->FindObjectByName(L"Player"));
		//SetTargetObject(CLevelMgr::GetInst()->FindObjectByName(L"MainCamera"));
		//SetTargetObject(CLevelMgr::GetInst()->FindObjectByName(L"PointLight 1"));
		return;
	}
}

void Inspector::CreateComponentUI()
{
	m_arrComponentUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	m_arrComponentUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetName("TransformUI");
	m_arrComponentUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetChildSize(ImVec2(0.f, 130.f));
	AddChildUI(m_arrComponentUI[(UINT)COMPONENT_TYPE::TRANSFORM]);

	m_arrComponentUI[(UINT)COMPONENT_TYPE::COLLIDER2D] = new Collider2DUI;
	m_arrComponentUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetName("Collider2DUI");
	m_arrComponentUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetChildSize(ImVec2(0.f, 100.f));
	AddChildUI(m_arrComponentUI[(UINT)COMPONENT_TYPE::COLLIDER2D]);

	m_arrComponentUI[(UINT)COMPONENT_TYPE::LIGHT2D] = new Light2DUI;
	m_arrComponentUI[(UINT)COMPONENT_TYPE::LIGHT2D]->SetName("Light2DUI");
	m_arrComponentUI[(UINT)COMPONENT_TYPE::LIGHT2D]->SetChildSize(ImVec2(0.f, 200.f));
	AddChildUI(m_arrComponentUI[(UINT)COMPONENT_TYPE::LIGHT2D]);

	m_arrComponentUI[(UINT)COMPONENT_TYPE::CAMERA] = new CameraUI;
	m_arrComponentUI[(UINT)COMPONENT_TYPE::CAMERA]->SetName("CameraUI");
	m_arrComponentUI[(UINT)COMPONENT_TYPE::CAMERA]->SetChildSize(ImVec2(0.f, 200.f));
	AddChildUI(m_arrComponentUI[(UINT)COMPONENT_TYPE::CAMERA]);

	m_arrComponentUI[(UINT)COMPONENT_TYPE::FLIPBOOK_RENDERER] = new FlipbookRenUI;
	m_arrComponentUI[(UINT)COMPONENT_TYPE::FLIPBOOK_RENDERER]->SetName("FlipBookComUI");
	m_arrComponentUI[(UINT)COMPONENT_TYPE::FLIPBOOK_RENDERER]->SetChildSize(ImVec2(0.f, 100.f));
	AddChildUI(m_arrComponentUI[(UINT)COMPONENT_TYPE::FLIPBOOK_RENDERER]);

	m_arrComponentUI[(UINT)COMPONENT_TYPE::MESHRENDER] = new MeshRenderUI;
	m_arrComponentUI[(UINT)COMPONENT_TYPE::MESHRENDER]->SetName("MeshRenderUI");
	m_arrComponentUI[(UINT)COMPONENT_TYPE::MESHRENDER]->SetChildSize(ImVec2(0.f, 100.f));
	AddChildUI(m_arrComponentUI[(UINT)COMPONENT_TYPE::MESHRENDER]);

	m_arrComponentUI[(UINT)COMPONENT_TYPE::TILEMAP] = new TilemapUI;
	m_arrComponentUI[(UINT)COMPONENT_TYPE::TILEMAP]->SetName("TileMapUI");
	m_arrComponentUI[(UINT)COMPONENT_TYPE::TILEMAP]->SetChildSize(ImVec2(0.f, 100.f));
	AddChildUI(m_arrComponentUI[(UINT)COMPONENT_TYPE::TILEMAP]);

	m_arrComponentUI[(UINT)COMPONENT_TYPE::PARTICLESYSTEM] = new ParticleSystemUI;
	m_arrComponentUI[(UINT)COMPONENT_TYPE::PARTICLESYSTEM]->SetName("ParticleSystemUI");
	m_arrComponentUI[(UINT)COMPONENT_TYPE::PARTICLESYSTEM]->SetChildSize(ImVec2(0.f, 100.f));
	AddChildUI(m_arrComponentUI[(UINT)COMPONENT_TYPE::PARTICLESYSTEM]);

	m_arrComponentUI[(UINT)COMPONENT_TYPE::GAME_TEXT] = new TextUI;
	m_arrComponentUI[(UINT)COMPONENT_TYPE::GAME_TEXT]->SetName("TextUI");
	m_arrComponentUI[(UINT)COMPONENT_TYPE::GAME_TEXT]->SetChildSize(ImVec2(0.f, 100.f));
	AddChildUI(m_arrComponentUI[(UINT)COMPONENT_TYPE::GAME_TEXT]);
}

void Inspector::CreateScriptUI(UINT _Count)
{
	for (UINT i = 0; i < _Count; ++i)
	{
		ScriptUI* pScriptUI = new ScriptUI;

		char szScriptUIName[255] = {};
		sprintf_s(szScriptUIName, 255, "ScriptUI##%d", (int)m_vecScriptUI.size());
		pScriptUI->SetName(szScriptUIName);

		AddChildUI(pScriptUI);
		m_vecScriptUI.push_back(pScriptUI);
	}
}

void Inspector::CreateAssetUI()
{
	AssetUI* UI = nullptr;

	UI = new MeshUI;
	UI->SetName("MeshUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::MESH] = UI;

	UI = new MeshDataUI;
	UI->SetName("MeshDataUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::MESH_DATA] = UI;

	UI = new MaterialUI;
	UI->SetName("MaterialUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::MATERIAL] = UI;

	UI = new PrefabUI;
	UI->SetName("PrefabUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::PREFAB] = UI;

	UI = new TextureUI;
	UI->SetName("TextureUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::TEXTURE] = UI;

	UI = new SpriteUI;
	UI->SetName("SpriteUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::SPRITE] = UI;

	UI = new FlipbookUI;
	UI->SetName("FlipbookUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::FLIPBOOK] = UI;

	UI = new SoundUI;
	UI->SetName("SoundUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::SOUND] = UI;

	UI = new GraphicShaderUI;
	UI->SetName("GraphicShaderUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::GRAPHIC_SHADER] = UI;

	UI = new ComputeShaderUI;
	UI->SetName("ComputeShaderUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::COMPUTE_SHADER] = UI;

	UI = new FSMUI;
	UI->SetName("FSMUI");
	AddChildUI(UI);
	m_arrAssetUI[(UINT)ASSET_TYPE::FSM] = UI;
}
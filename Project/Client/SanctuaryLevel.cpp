#include "pch.h"
#include "SanctuaryLevel.h"

#include <Engine/HHAssetMgr.h>
#include <Engine/assets.h>

#include <Engine/HHLevelMgr.h>
#include <Engine/HHLevel.h>
#include <Engine/HHLayer.h>
#include <Engine/HHGameObject.h>
#include <Engine/components.h>

#include <Engine/HHCollisionMgr.h>

#include <Engine/HHSetColorCS.h>
#include <Engine/HHStructuredBuffer.h>

#include <Scripts/HHPlayerScript.h>
#include <Scripts/HHCameraMoveScript.h>

#include "HHLevelSaveLoad.h"

HHLevel* SanctuaryLevel::CreateSanctuaryLevel()
{
	// Level Load
	//wstring StrLevelLoadPath = HHPathMgr::GetInstance()->GetContentPath();
	//StrLevelLoadPath += L"level\\TitleLevel.lv";
	//HHLevel* pLoadedLevel = HHLevelSaveLoad::LoadLevel(StrLevelLoadPath);

	//ChangeLevel(pLoadedLevel, LEVEL_STATE::PLAY);

	//return;

	// Material
	Ptr<HHMaterial> BackgroundMtrl = HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"BackgroundMtrl");


	// Level 생성
	HHLevel* pLevel = new HHLevel;

	pLevel->GetLayer(0)->SetName(L"Default");
	pLevel->GetLayer(1)->SetName(L"Background");
	pLevel->GetLayer(2)->SetName(L"Foreground");
	pLevel->GetLayer(3)->SetName(L"Menu");

	// 카메라 오브젝트
	HHGameObject* MainCamera = new HHGameObject;
	MainCamera->SetName(L"MainCamera");
	MainCamera->AddComponent(new HHTransform);
	MainCamera->AddComponent(new HHCamera);
	MainCamera->AddComponent(new HHCameraMoveScript);

	// 우선순위를 0 : MainCamera 로 설정
	MainCamera->Camera()->SetPriority(0);

	// 카메라 레이어 설정
	MainCamera->Camera()->SetLayerAll();
	MainCamera->Camera()->SetFar(100000.f);
	MainCamera->Camera()->SetProjectionType(ORTHOGRAPHIC);

	pLevel->AddObject(0, MainCamera);

	// 광원 오브젝트 추가
	HHGameObject* Global_Illumination = nullptr;
	Global_Illumination = new HHGameObject;
	Global_Illumination->SetName(L"World Light");
	Global_Illumination->AddComponent(new HHTransform);
	Global_Illumination->AddComponent(new HHLight2D);

	Global_Illumination->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 100.f));
	Global_Illumination->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	Global_Illumination->Light2D()->SetLightAmbient(Vec3(1.f, 1.f, 1.f));

	pLevel->AddObject(0, Global_Illumination);

	// Background 배치
	HHGameObject* BGObject = nullptr;
	BGObject = new HHGameObject;
	BGObject->SetName(L"Level Background");
	BGObject->AddComponent(new HHTransform);
	BGObject->AddComponent(new HHMeshRender);

	BGObject->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 1000.f));
	BGObject->Transform()->SetRelativeScale(Vec3(2560.f, 1440.f, 1.f));
	BGObject->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	BGObject->MeshRender()->SetMaterial(BackgroundMtrl);

	Ptr<HHTexture> BGTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Title\\HollowSurvivorsArtwork3-alpha.png"
		, L"Texture2D\\Title\\HollowSurvivorsArtwork3-alpha.png");
	BGObject->GetRenderComponent()->GetMaterial()->SetTextureParam(TEX_0, BGTexture);
	BGObject->GetRenderComponent()->GetMaterial()->SetScalarParam(INT_0, 0);

	pLevel->AddObject(1, BGObject);

	return pLevel;

	//ChangeLevel(TitleLvl, LEVEL_STATE::PLAY);

	// 레벨 지정 Save
	//wstring strLevelPath = HHPathMgr::GetInstance()->GetContentPath();
	//strLevelPath += L"Level\\TitleLevel.lv";
	//HHLevelSaveLoad::SaveLevel(strLevelPath, TitleLvl);
}

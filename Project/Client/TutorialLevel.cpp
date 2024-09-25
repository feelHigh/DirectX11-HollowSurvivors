#include "pch.h"
#include "TutorialLevel.h"

#include "HHLoadGameLevel.h"

#include <Engine/HHAssetMgr.h>
#include <Engine/assets.h>

#include <Engine/HHLevelMgr.h>
#include <Engine/HHLevel.h>
#include <Engine/HHLayer.h>
#include <Engine/HHGameObject.h>
#include <Engine/components.h>

#include <Engine/HHCollisionMgr.h>

#include <Engine/HHText.h>

#include <Engine/HHSetColorCS.h>
#include <Engine/HHStructuredBuffer.h>

#include <Scripts/HHPlayerScript.h>
#include <Scripts/HHCameraMoveScript.h>
#include <Scripts/HHMouseCursorScript.h>
#include <Scripts/HHButtonScript.h>

#include <Scripts/HHTutorialBackgroundScript.h>
#include <Scripts/HHTutorialMapScript.h>

#include "HHLevelSaveLoad.h"

HHLevel* TutorialLevel::Initialize()
{
	//ShowCursor(false);

#pragma region Material Assets
	Ptr<HHMaterial> PlayerMtrl = HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"Std2DMtrl");
	Ptr<HHMaterial> BackgroundMtrl = HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"BackgroundMtrl");
#pragma endregion

	// Level 생성
	HHLevel* TutorialLvl = new HHLevel;

	TutorialLvl->GetLayer(0)->SetName(L"Default");
	TutorialLvl->GetLayer(1)->SetName(L"User");
	TutorialLvl->GetLayer(2)->SetName(L"UI");
	TutorialLvl->GetLayer(3)->SetName(L"Background");
	TutorialLvl->GetLayer(4)->SetName(L"Tilemap");
	TutorialLvl->GetLayer(5)->SetName(L"Player");

	// 카메라 오브젝트
	HHGameObject* MainCamera = new HHGameObject;
	MainCamera->SetName(L"Main Camera");
	MainCamera->AddComponent(new HHTransform);
	MainCamera->AddComponent(new HHCamera);
	MainCamera->AddComponent(new HHCameraMoveScript);

	MainCamera->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 500.f));

	MainCamera->Camera()->SetPriority(0);
	MainCamera->Camera()->SetLayerAll();
	MainCamera->Camera()->SetFar(100000.f);
	MainCamera->Camera()->SetProjectionType(PERSPECTIVE);

	TutorialLvl->AddObject(0, MainCamera);

	// 광원 오브젝트 추가
	HHGameObject* Global_Illumination = nullptr;
	Global_Illumination = new HHGameObject;
	Global_Illumination->SetName(L"World Light");
	Global_Illumination->AddComponent(new HHTransform);
	Global_Illumination->AddComponent(new HHLight2D);

	Global_Illumination->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 100.f));
	Global_Illumination->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	Global_Illumination->Light2D()->SetLightAmbient(Vec3(1.f, 1.f, 1.f));

	TutorialLvl->AddObject(0, Global_Illumination);

#pragma region User Layer
	HHGameObject* MouseCursor = new HHGameObject;
	MouseCursor->SetName(L"Mouse Cursor");
	MouseCursor->AddComponent(new HHTransform);
	MouseCursor->AddComponent(new HHCollider2D);
	MouseCursor->AddComponent(new HHMeshRender);
	MouseCursor->AddComponent(new HHMouseCursorScript);

	MouseCursor->Transform()->SetRelativeScale(Vec3(32.f, 32.f, 1.f));

	MouseCursor->Collider2D()->SetIndependentScale(false);
	MouseCursor->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	MouseCursor->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	MouseCursor->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	MouseCursor->MeshRender()->SetMaterial(BackgroundMtrl);

	TutorialLvl->AddObject(1, MouseCursor);
#pragma endregion

#pragma region UI Layer

#pragma endregion

#pragma region Background Layer
	HHGameObject* LevelBackground = nullptr;
	LevelBackground = new HHGameObject;
	LevelBackground->SetName(L"Level Background");
	LevelBackground->AddComponent(new HHTransform);
	LevelBackground->AddComponent(new HHMeshRender);
	LevelBackground->AddComponent(new HHTutorialBackgroundScript);

	LevelBackground->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 1000.f));
	LevelBackground->Transform()->SetRelativeScale(Vec3(760.f * 2.5f, 621.f * 2.5f, 1.f));

	LevelBackground->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	LevelBackground->MeshRender()->SetMaterial(BackgroundMtrl);

	TutorialLvl->AddObject(1, LevelBackground);
#pragma endregion

#pragma region Tilemap Layer
	HHGameObject* LevelMap = nullptr;
	LevelMap = new HHGameObject;
	LevelMap->SetName(L"Level Map");
	LevelMap->AddComponent(new HHTransform);
	LevelMap->AddComponent(new HHMeshRender);
	LevelMap->AddComponent(new HHTutorialMapScript);

	LevelMap->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 900.f));
	LevelMap->Transform()->SetRelativeScale(Vec3(738.f * 2.5f, 368.f * 2.5f, 1.f));

	LevelMap->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	LevelMap->MeshRender()->SetMaterial(BackgroundMtrl);

	TutorialLvl->AddObject(2, LevelMap);
#pragma endregion

#pragma region Player Layer
	HHGameObject* pPlayer = new HHGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new HHTransform);
	pPlayer->AddComponent(new HHMeshRender);
	pPlayer->AddComponent(new HHCollider2D);
	pPlayer->AddComponent(new HHFlipbookRenderer);
	pPlayer->AddComponent(new HHPlayerScript);
	pPlayer->Transform()->SetRelativePosition(0.f, 0.f, 800.f);
	pPlayer->Transform()->SetRelativeScale(128.f, 128.f, 1.f);

	pPlayer->Collider2D()->SetIndependentScale(false);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pPlayer->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(PlayerMtrl);

	Ptr<HHFlipbook> pFlipBook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Idle_Down.flip");
	pPlayer->FlipbookRenderer()->AddFlipbook(0, pFlipBook);
	pPlayer->FlipbookRenderer()->Play(0, 8, true);

	TutorialLvl->AddObject(5, pPlayer);
#pragma endregion

	// 레벨 지정 Save
	wstring strLevelPath = HHPathMgr::GetInstance()->GetContentPath();
	strLevelPath += L"Level\\TutorialLevel.lv";
	HHLevelSaveLoad::SaveLevel(strLevelPath, TutorialLvl);

	return TutorialLvl;
}


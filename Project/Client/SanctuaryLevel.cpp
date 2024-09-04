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

#include <Scripts/HHLevelBackgroundScript.h>
#include <Scripts/HHPlayerScript.h>
#include <Scripts/HHSmallGirlScript.h>
#include <Scripts/HHCameraMoveScript.h>
#include <Scripts/HHMouseCursorScript.h>
#include <Scripts/HHTilemapScript.h>

#include "HHLevelSaveLoad.h"

HHLevel* SanctuaryLevel::CreateSanctuaryLevel()
{
	//ShowCursor(false);

	// Material
	Ptr<HHMaterial> BackgroundMtrl = HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"BackgroundMtrl");

	// Level 생성
	HHLevel* SanctuaryLvl = new HHLevel;

	SanctuaryLvl->GetLayer(0)->SetName(L"Default");
	SanctuaryLvl->GetLayer(1)->SetName(L"Background");
	SanctuaryLvl->GetLayer(3)->SetName(L"Player");

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

	SanctuaryLvl->AddObject(0, MainCamera);

	// 마우스 커서 테스트
	HHGameObject* MouseCursor = new HHGameObject;
	MouseCursor->SetName(L"Mouse Cursor");
	MouseCursor->AddComponent(new HHTransform);
	MouseCursor->AddComponent(new HHMeshRender);
	MouseCursor->AddComponent(new HHMouseCursorScript);

	MouseCursor->Transform()->SetRelativeScale(Vec3(32.f, 32.f, 1.f));

	MouseCursor->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	MouseCursor->MeshRender()->SetMaterial(BackgroundMtrl);

	SanctuaryLvl->AddObject(10, MouseCursor);

	// 광원 오브젝트 추가
	HHGameObject* Global_Illumination = nullptr;
	Global_Illumination = new HHGameObject;
	Global_Illumination->SetName(L"World Light");
	Global_Illumination->AddComponent(new HHTransform);
	Global_Illumination->AddComponent(new HHLight2D);

	Global_Illumination->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 100.f));
	Global_Illumination->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	Global_Illumination->Light2D()->SetLightAmbient(Vec3(1.f, 1.f, 1.f));

	SanctuaryLvl->AddObject(0, Global_Illumination);

	// Background 배치
	HHGameObject* BGObject = nullptr;
	BGObject = new HHGameObject;
	BGObject->SetName(L"Sanctuary Background Texture");
	BGObject->AddComponent(new HHTransform);
	BGObject->AddComponent(new HHMeshRender);
	BGObject->AddComponent(new HHLevelBackgroundScript);

	BGObject->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 1000.f));
	BGObject->Transform()->SetRelativeScale(Vec3(2560.f, 1440.f, 1.f));
	BGObject->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	BGObject->MeshRender()->SetMaterial(BackgroundMtrl);

	SanctuaryLvl->AddObject(1, BGObject);

	// Tilemap 배치 보류
	/*HHGameObject* pTilemap = nullptr;
	pTilemap = new HHGameObject;
	pTilemap->SetName(L"Tilemap");
	pTilemap->AddComponent(new HHTransform);
	pTilemap->AddComponent(new HHTilemap);
	pTilemap->AddComponent(new HHTilemapScript);

	pTilemap->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 900.f));

	pTilemap->Tilemap()->SetRowCol(30, 30);
	pTilemap->Tilemap()->SetTileSize(Vec2(16.f, 16.f));

	Ptr<HHTexture> pTexture = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"Texture2D\\Sanctuary\\floor_tileset.png");

	pTilemap->Tilemap()->SetAtlasTexture(pTexture);
	pTilemap->Tilemap()->SetAtlasTileSize(Vec2(16.f, 16.f));

	SanctuaryLvl->AddObject(2, pTilemap);*/

	// 레벨 지정 Save
	wstring strLevelPath = HHPathMgr::GetInstance()->GetContentPath();
	strLevelPath += L"Level\\SanctuaryLevel.lv";
	HHLevelSaveLoad::SaveLevel(strLevelPath, SanctuaryLvl);

	return SanctuaryLvl;
}

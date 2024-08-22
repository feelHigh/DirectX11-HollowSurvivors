#include "pch.h"
#include "HHTestLevel.h"

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
#include <Scripts/HHMissileScript.h>
#include <Scripts/HHCameraMoveScript.h>

#include "HHLevelSaveLoad.h"

void HHTestLevel::CreateTestLevel()
{
	// Material
	Ptr<HHMaterial> pMtrl = HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"Std2DMtrl");
	Ptr<HHMaterial> pAlphaBlendMtrl = HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<HHMaterial> pDebugShapeMtrl = HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"DebugShapeMtrl");

	Ptr<HHTexture> pTexture = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"texture//Character.png");
	pAlphaBlendMtrl->SetTextureParam(TEX_0, pTexture);

	CreatePrefab();

	// Sound 재생
	Ptr<HHSound> pSound = HHAssetMgr::GetInstance()->FindAsset<HHSound>(L"sound\\DM.wav");
	pSound->Play(0, 1.f, false);

	/*
	// Level Load
	wstring StrLevelLoadPath = HHPathMgr::GetInstance()->GetContentPath();
	StrLevelLoadPath += L"level\\Temp.lv";
	HHLevel* pLoadedLevel = HHLevelSaveLoad::LoadLevel(StrLevelLoadPath);

	ChangeLevel(pLoadedLevel, LEVEL_STATE::PLAY);

	return;
	*/

	// Level 생성
	HHLevel* pLevel = new HHLevel;

	pLevel->GetLayer(0)->SetName(L"Default");
	pLevel->GetLayer(1)->SetName(L"Background");
	pLevel->GetLayer(2)->SetName(L"Tile");
	pLevel->GetLayer(3)->SetName(L"Player");
	pLevel->GetLayer(4)->SetName(L"Monster");
	pLevel->GetLayer(5)->SetName(L"PlayerProjectile");
	pLevel->GetLayer(6)->SetName(L"MonsterProjectile");

	// 카메라 오브젝트
	HHGameObject* CamObj = new HHGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new HHTransform);
	CamObj->AddComponent(new HHCamera);
	CamObj->AddComponent(new HHCameraMoveScript);

	// 우선순위를 0 : MainCamera 로 설정
	CamObj->Camera()->SetPriority(0);

	// 카메라 레이어 설정 (31번 레이어 제외 모든 레이어를 촬영)
	CamObj->Camera()->SetLayerAll();
	CamObj->Camera()->SetLayer(31, false);
	CamObj->Camera()->SetFar(100000.f);
	CamObj->Camera()->SetProjectionType(ORTHOGRAPHIC);

	pLevel->AddObject(0, CamObj);

	HHGameObject* pObject = nullptr;

	// 광원 오브젝트 추가
	pObject = new HHGameObject;
	pObject->SetName(L"World Light");
	pObject->AddComponent(new HHTransform);
	pObject->AddComponent(new HHLight2D);

	pObject->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pObject->Light2D()->SetLightAmbient(Vec3(0.8f, 0.8f, 0.8f));
	pObject->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 100.f));

	pLevel->AddObject(0, pObject);

	// 플레이어 오브젝트
	/*HHGameObject* pPlayer = new HHGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new HHTransform);
	pPlayer->AddComponent(new HHMeshRender);
	pPlayer->AddComponent(new HHCollider2D);
	pPlayer->AddComponent(new HHFlipbookRenderer);
	pPlayer->AddComponent(new HHPlayerScript);
	pPlayer->Transform()->SetRelativePosition(0.f, 0.f, 100.f);
	pPlayer->Transform()->SetRelativeScale(200.f, 200.f, 1.f);

	pPlayer->Collider2D()->SetIndependentScale(false);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pPlayer->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(pMtrl);

	Ptr<HHFlipbook> pFlipBook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Link_MoveDown.flip");
	pPlayer->FlipbookRenderer()->AddFlipbook(5, pFlipBook);
	pPlayer->FlipbookRenderer()->Play(5, 10, true);

	pLevel->AddObject(3, pPlayer);*/

	// Monster Object
	/*HHGameObject* pMonster = new HHGameObject;
	pMonster->SetName(L"Monster");

	pMonster->AddComponent(new HHTransform);
	pMonster->AddComponent(new HHMeshRender);
	pMonster->AddComponent(new HHCollider2D);

	pMonster->Transform()->SetRelativePosition(-400.f, 0.f, 100.f);
	pMonster->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

	pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pMonster->Collider2D()->SetScale(Vec3(1.2f, 1.2f, 1.f));

	pMonster->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	pMonster->MeshRender()->SetMaterial(pMtrl);

	pLevel->AddObject(4, pMonster);*/

	// TileMap Object
	/*HHGameObject* pTileMapObj = new HHGameObject;
	pTileMapObj->SetName(L"TileMap");

	pTileMapObj->AddComponent(new HHTransform);
	pTileMapObj->AddComponent(new HHTilemap);

	pTileMapObj->Transform()->SetRelativePosition(Vec3(-800.f, 450.f, 500.f));

	pTileMapObj->Tilemap()->SetRowCol(100, 100);
	pTileMapObj->Tilemap()->SetTileSize(Vec2(64.f, 64.f));

	Ptr<HHTexture> pTileAtlas = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"texture\\TILE.bmp");
	pTileMapObj->Tilemap()->SetAtlasTexture(pTileAtlas);
	pTileMapObj->Tilemap()->SetAtlasTileSize(Vec2(64.f, 64.f));

	pLevel->AddObject(2, pTileMapObj);*/

	// Particle Object
	HHGameObject* pParticleObj = new HHGameObject;
	pParticleObj->SetName(L"Particle");

	pParticleObj->AddComponent(new HHTransform);
	pParticleObj->AddComponent(new HHParticleSystem);

	pParticleObj->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 500.f));

	pLevel->AddObject(0, pParticleObj);

	// PostProcess Object
	/*HHGameObject* pGrayFilterObj = new HHGameObject;
	pGrayFilterObj->SetName(L"GrayFilter");
	pGrayFilterObj->AddComponent(new HHTransform);
	pGrayFilterObj->AddComponent(new HHMeshRender);

	pGrayFilterObj->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

	pGrayFilterObj->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	pGrayFilterObj->MeshRender()->SetMaterial(HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"DistortionMtrl"));

	pLevel->AddObject(0, pGrayFilterObj);*/

	// 레벨 지정 Save
	
	wstring strLevelPath = HHPathMgr::GetInstance()->GetContentPath();
	strLevelPath += L"level\\Temp.lv";
	HHLevelSaveLoad::SaveLevel(strLevelPath, pLevel);

	ChangeLevel(pLevel, LEVEL_STATE::PLAY);
	
	// 충돌 지정
	HHCollisionMgr::GetInstance()->CollisionCheck(3, 4); // Player vs Monster
	HHCollisionMgr::GetInstance()->CollisionCheck(5, 4); // Player Projectile vs Monster
}

void HHTestLevel::CreatePrefab()
{
	HHGameObject* pProto = new HHGameObject;
	pProto->SetName(L"Missile");
	pProto->AddComponent(new HHTransform);
	pProto->AddComponent(new HHMeshRender);
	pProto->AddComponent(new HHMissileScript);

	pProto->Transform()->SetRelativeScale(100.f, 100.f, 1.f);

	pProto->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	pProto->MeshRender()->SetMaterial(HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"Std2DMtrl"));

	Ptr<HHPrefab> pPrefab = new HHPrefab;
	pPrefab->SetProtoObject(pProto);

	HHAssetMgr::GetInstance()->AddAsset<HHPrefab>(L"MissilePref", pPrefab);

	wstring FilePath = HHPathMgr::GetInstance()->GetContentPath();
	FilePath += L"prefab\\Missile.pref";
	pPrefab->Save(FilePath);
}

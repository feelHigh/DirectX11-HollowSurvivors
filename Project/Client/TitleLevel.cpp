#include "pch.h"
#include "TitleLevel.h"

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

#include <Scripts/HHLevelBackgroundScript.h>
#include <Scripts/HHPlayerScript.h>
#include <Scripts/HHSmallGirlScript.h>
#include <Scripts/HHCameraMoveScript.h>
#include <Scripts/HHMouseCursorScript.h>
#include <Scripts/HHTitleLogoScript.h>
#include <Scripts/HHButtonScript.h>

#include "HHLevelSaveLoad.h"

HHLevel* TitleLevel::CreateTitleLevel()
{
	//ShowCursor(false);

	// Material
	Ptr<HHMaterial> BackgroundMtrl = HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"BackgroundMtrl");

	// Level 생성
	HHLevel* TitleLvl = new HHLevel;

	TitleLvl->GetLayer(0)->SetName(L"Default");
	TitleLvl->GetLayer(1)->SetName(L"Background");
	TitleLvl->GetLayer(2)->SetName(L"Foreground");
	TitleLvl->GetLayer(3)->SetName(L"Menu");
	TitleLvl->GetLayer(10)->SetName(L"UI");

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

	TitleLvl->AddObject(0, MainCamera);

	// 마우스 커서 테스트
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

	TitleLvl->AddObject(10, MouseCursor);

	// 광원 오브젝트 추가
	HHGameObject* Global_Illumination = nullptr;
	Global_Illumination = new HHGameObject;
	Global_Illumination->SetName(L"World Light");
	Global_Illumination->AddComponent(new HHTransform);
	Global_Illumination->AddComponent(new HHLight2D);

	Global_Illumination->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 100.f));
	Global_Illumination->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	Global_Illumination->Light2D()->SetLightAmbient(Vec3(1.f, 1.f, 1.f));

	TitleLvl->AddObject(0, Global_Illumination);

#pragma region Background
	HHGameObject* BGObject = nullptr;
	BGObject = new HHGameObject;
	BGObject->SetName(L"Title Background Texture");
	BGObject->AddComponent(new HHTransform);
	BGObject->AddComponent(new HHMeshRender);
	BGObject->AddComponent(new HHLevelBackgroundScript);

	BGObject->Transform()->SetRelativePosition(Vec3(0.f, 0.f, 1000.f));
	BGObject->Transform()->SetRelativeScale(Vec3(2560.f, 1440.f, 1.f));
	BGObject->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	BGObject->MeshRender()->SetMaterial(BackgroundMtrl);

	TitleLvl->AddObject(1, BGObject);
#pragma endregion

#pragma region Foreground Layer
	// Foreground 배치
	HHGameObject* FGObject = nullptr;
	FGObject = new HHGameObject;
	FGObject->SetName(L"Title Logo");
	FGObject->AddComponent(new HHTransform);
	FGObject->AddComponent(new HHMeshRender);
	FGObject->AddComponent(new HHCollider2D);
	FGObject->AddComponent(new HHTitleLogoScript);

	FGObject->Transform()->SetRelativePosition(Vec3(6.f, 176.f, 900.f));
	FGObject->Transform()->SetRelativeScale(Vec3(543.f, 294.f, 1.f));
	FGObject->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	FGObject->MeshRender()->SetMaterial(BackgroundMtrl);

	FGObject->Collider2D()->SetIndependentScale(false);
	FGObject->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	FGObject->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	TitleLvl->AddObject(2, FGObject);
#pragma endregion

#pragma region Menu Layer
	HHGameObject* MenuObject = nullptr;
	MenuObject = new HHGameObject;
	MenuObject->SetName(L"Play Menu");
	MenuObject->AddComponent(new HHTransform);
	MenuObject->AddComponent(new HHCollider2D);
	MenuObject->AddComponent(new HHText);
	MenuObject->AddComponent(new HHTextRenderer);
	MenuObject->AddComponent(new HHButton);
	MenuObject->AddComponent(new HHButtonScript);

	MenuObject->Transform()->SetRelativePosition(Vec3(0.f, -100.f, 900.f));
	MenuObject->Transform()->SetRelativeScale(Vec3(180.f, 40.f, 1.f));

	MenuObject->Collider2D()->SetIndependentScale(false);
	MenuObject->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	MenuObject->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	MenuObject->Button()->SetButtonType(BUTTON_TYPE::TITLE_PLAY);

	MenuObject->Text()->SetText(L"PLAY");
	MenuObject->Text()->SetFontSize(56.f);

	TitleLvl->AddObject(3, MenuObject);

	MenuObject = new HHGameObject;
	MenuObject->SetName(L"Option Menu");
	MenuObject->AddComponent(new HHTransform);
	MenuObject->AddComponent(new HHCollider2D);
	MenuObject->AddComponent(new HHText);
	MenuObject->AddComponent(new HHTextRenderer);
	MenuObject->AddComponent(new HHButton);
	MenuObject->AddComponent(new HHButtonScript);

	MenuObject->Transform()->SetRelativePosition(Vec3(0.f, -150.f, 900.f));
	MenuObject->Transform()->SetRelativeScale(Vec3(180.f, 40.f, 1.f));

	MenuObject->Collider2D()->SetIndependentScale(false);
	MenuObject->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	MenuObject->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	MenuObject->Text()->SetText(L"OPTIONS");
	MenuObject->Text()->SetFontSize(56.f);

	MenuObject->Button()->SetButtonType(BUTTON_TYPE::TITLE_OPTION);

	TitleLvl->AddObject(3, MenuObject);

	MenuObject = new HHGameObject;
	MenuObject->SetName(L"Credits Menu");
	MenuObject->AddComponent(new HHTransform);
	MenuObject->AddComponent(new HHCollider2D);
	MenuObject->AddComponent(new HHText);
	MenuObject->AddComponent(new HHTextRenderer);
	MenuObject->AddComponent(new HHButton);
	MenuObject->AddComponent(new HHButtonScript);

	MenuObject->Transform()->SetRelativePosition(Vec3(0.f, -200.f, 900.f));
	MenuObject->Transform()->SetRelativeScale(Vec3(180.f, 40.f, 1.f));

	MenuObject->Collider2D()->SetIndependentScale(false);
	MenuObject->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	MenuObject->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	MenuObject->Text()->SetText(L"CREDITS");
	MenuObject->Text()->SetFontSize(56.f);

	MenuObject->Button()->SetButtonType(BUTTON_TYPE::TITLE_CREDITS);

	TitleLvl->AddObject(3, MenuObject);

	MenuObject = new HHGameObject;
	MenuObject->SetName(L"Quit Menu");
	MenuObject->AddComponent(new HHTransform);
	MenuObject->AddComponent(new HHCollider2D);
	MenuObject->AddComponent(new HHText);
	MenuObject->AddComponent(new HHTextRenderer);
	MenuObject->AddComponent(new HHButton);
	MenuObject->AddComponent(new HHButtonScript);

	MenuObject->Transform()->SetRelativePosition(Vec3(-9.f, -250.f, 900.f));
	MenuObject->Transform()->SetRelativeScale(Vec3(180.f, 40.f, 1.f));

	MenuObject->Collider2D()->SetIndependentScale(false);
	MenuObject->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	MenuObject->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	MenuObject->Text()->SetText(L"QUIT");
	MenuObject->Text()->SetFontSize(56.f);

	MenuObject->Button()->SetButtonType(BUTTON_TYPE::TITLE_QUIT);

	TitleLvl->AddObject(3, MenuObject);
#pragma endregion

#pragma region Collision Manager
	// 충돌 지정
	HHCollisionMgr::GetInstance()->CollisionCheck(3, 10); // Menu & User
#pragma endregion

	// 레벨 지정 Save
	wstring strLevelPath = HHPathMgr::GetInstance()->GetContentPath();
	strLevelPath += L"Level\\TitleLevel.lv";
	HHLevelSaveLoad::SaveLevel(strLevelPath, TitleLvl);

	return TitleLvl;
}

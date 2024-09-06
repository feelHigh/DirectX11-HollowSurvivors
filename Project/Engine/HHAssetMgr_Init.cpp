#include "pch.h"
#include "HHAssetMgr.h"
#include "HHDevice.h"

void HHAssetMgr::Initialize()
{
	CreateEngineMesh();
	CreateEngineTexture();
	CreateEngineSprite();
	CreateEngineGraphicShader();
	CreateEngineComputeShader();
	CreateEngineMaterial();
}

void HHAssetMgr::CreateEngineMesh()
{
	Ptr<HHMesh> pMesh = nullptr;
	Vtx v;
	// PointMesh
	pMesh = new HHMesh;
	v.vPosition = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);

	UINT i = 0;
	pMesh->Create(&v, 1, &i, 1);
	AddAsset(L"PointMesh", pMesh);
	//---------------------------------------------------------------------------------------------
	// RectMesh 생성	
	// 0 -- 1
	// | \  |
	// 3 -- 2
	Vtx arrVtx[4] = {};

	arrVtx[0].vPosition = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);

	arrVtx[1].vPosition = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[1].vUV = Vec2(1.f, 0.f);

	arrVtx[2].vPosition = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);

	arrVtx[3].vPosition = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);

	// Index 버퍼 생성
	UINT arrIdx[6] = {};
	arrIdx[0] = 0;	arrIdx[1] = 1;	arrIdx[2] = 2;
	arrIdx[3] = 0; 	arrIdx[4] = 2;	arrIdx[5] = 3;

	pMesh = new HHMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	pMesh->SetEngineAsset();
	AddAsset(L"RectMesh", pMesh);
	//---------------------------------------------------------------------------------------------
	// RectMesh_Debug
	arrIdx[0] = 0;	arrIdx[1] = 1;	arrIdx[2] = 2; arrIdx[3] = 3; arrIdx[4] = 0;

	pMesh = new HHMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 5);
	pMesh->SetEngineAsset();
	AddAsset(L"RectMesh_Debug", pMesh);
	//---------------------------------------------------------------------------------------------
	// CircleMesh
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;

	int Slice = 40;
	float fTheta = XM_2PI / Slice;
	float Radius = 0.5f;

	// 중심점
	v.vPosition = Vec3(0.f, 0.f, 0.f);
	v.vUV = Vec2(0.5f, 0.5f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	// 테두리
	float Angle = 0.f;
	for (int i = 0; i < Slice + 1; ++i)
	{
		v.vPosition = Vec3(Radius * cosf(Angle), Radius * sinf(Angle), 0.f);
		v.vUV = Vec2(v.vPosition.x + 0.5f, -(v.vPosition.y - 0.5f));
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vecVtx.push_back(v);

		Angle += fTheta;
	}

	// 인덱스
	for (int i = 0; i < Slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	pMesh = new HHMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	pMesh->SetEngineAsset();
	AddAsset(L"CircleMesh", pMesh);
	//---------------------------------------------------------------------------------------------
	// CircleMesh_Debug
	vecIdx.clear();
	for (size_t i = 1; i < vecVtx.size(); ++i)
	{
		vecIdx.push_back((UINT)i);
	}

	pMesh = new HHMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	pMesh->SetEngineAsset();
	AddAsset(L"CircleMesh_Debug", pMesh);
	//---------------------------------------------------------------------------------------------
}

void HHAssetMgr::CreateEngineTexture()
{
	// PostProcess 용도 텍스쳐 생성
	Vec2 Resolution = HHDevice::GetInstance()->GetResolution();
	Ptr<HHTexture> pPostProcessTex = CreateTexture(L"PostProcessTex"
													, (UINT)Resolution.x
													, (UINT)Resolution.y
													, DXGI_FORMAT_R8G8B8A8_UNORM
													, D3D11_BIND_SHADER_RESOURCE);

	// Noise Texture
	//Load<HHTexture>(L"texture\\noise\\noise_01.png", L"texture\\noise\\noise_01.png");
	//Load<HHTexture>(L"texture\\noise\\noise_02.png", L"texture\\noise\\noise_02.png");
	//Load<HHTexture>(L"texture\\noise\\noise_03.jpg", L"texture\\noise\\noise_03.jpg");
}

void HHAssetMgr::CreateEngineSprite()
{
	//Ptr<HHTexture> pAtlasTex = Load<HHTexture>(L"Texture2D\\Player\\Player_Test.png", L"Texture2D\\Player\\Player_Test.png");

	//Ptr<HHSprite> pSprite = nullptr;

	//for (int i = 0; i < nSprite; ++i)
	//{
	//	wchar_t szKey[50] = {};
	//	swprintf_s(szKey, 50, L"Player_Idle_Down_%d", i);

	//	pSprite = new HHSprite;
	//	pSprite->Create(pAtlasTex, Vec2((float)i * 64.f, 0.f), Vec2(64.f, 64.f));
	//	pSprite->SetBackground(Vec2(64.f, 64.f));

	//	/*if (i == 2)
	//		pSprite->SetOffset(Vec2(30.f, 0.f));*/

	//	AddAsset(szKey, pSprite);
	//}

	//Ptr<HHFlipbook> pFlipBook = nullptr;

	//pFlipBook = new HHFlipbook;

	//for (int i = 0; i < nSprite; ++i)
	//{
	//	wchar_t szKey[50] = {};
	//	swprintf_s(szKey, 50, L"Player_Idle_Down_%d", i);
	//	pFlipBook->AddSprite(FindAsset<HHSprite>(szKey));
	//}

	//AddAsset(L"Player_Idle_Down", pFlipBook);
	// 여기까는 AddAsset만하고 Save/Load 안됌
	// 여기부터 사용
	/*int nSprite = 9;
	int nRow = 27;

	wstring strContentPath = HHPathMgr::GetInstance()->GetContentPath();
	
	for (int i = 0; i < nSprite; ++i)
	{
		wchar_t Buffer[50] = {};
		swprintf_s(Buffer, 50, L"Player_Attack_Sword_Combo3_Right_%d", i);

		pSprite = new HHSprite;
		pSprite->Create(pAtlasTex, Vec2((float)i * 64.f, nRow * 64.f), Vec2(64.f, 64.f));
		pSprite->SetBackground(Vec2(64.f, 64.f));	

		pSprite->SetRelativePath(wstring(L"Animation\\") + Buffer + L".sprite");
		pSprite->Save(strContentPath + L"Animation\\" + Buffer + L".sprite");


		pSprite = Load<HHSprite>(Buffer, wstring(L"Animation\\") + Buffer + L".sprite");
	}

	Ptr<HHFlipbook> pFilpBook = new HHFlipbook;

	for (int i = 0; i < nSprite; ++i)
	{
		wchar_t Buffer[50] = {};
		swprintf_s(Buffer, 50, L"Player_Attack_Sword_Combo3_Right_%d", i);
		pFilpBook->AddSprite(FindAsset<HHSprite>(Buffer));		
	}

	AddAsset(L"Player_Attack_Sword_Combo3_Right", pFilpBook);
	pFilpBook->Save(strContentPath + L"Animation\\" + L"Player_Attack_Sword_Combo3_Right" + L".flip");*/
	// 여기 사용 안함
	//Load<HHFlipbook>(L"Player_Idle_Down", L"Animation\\Player_Idle_Down.flip");
}

void HHAssetMgr::CreateEngineGraphicShader()
{
	Ptr<HHGraphicShader> pShader = nullptr;

#pragma region Default Shader
	// Std2D Shader
	pShader = new HHGraphicShader;

	pShader->CreateVertexShader(L"Shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"Shader\\std2d.fx", "PS_Std2D");

	pShader->SetRasterizerType(RASTERIZER_STATE_TYPE::CULL_NONE);
	pShader->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::LESS);
	pShader->SetBlendType(BLEND_STATE_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	pShader->AddTextureParam(TEX_0, "OutputTexture");

	AddAsset(L"Std2DShader", pShader);
	//---------------------------------------------------------------
	// Std2D Alpha Blend
	pShader = new HHGraphicShader;
	pShader->CreateVertexShader(L"Shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"Shader\\std2d.fx", "PS_Std2D_AlphaBlend");

	pShader->SetRasterizerType(RASTERIZER_STATE_TYPE::CULL_NONE);
	pShader->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBlendType(BLEND_STATE_TYPE::ALPHABLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddAsset(L"Std2DAlphaBlendShader", pShader);
	//---------------------------------------------------------------
	// DebugShapeShader
	pShader = new HHGraphicShader;
	pShader->CreateVertexShader(L"Shader\\debug.fx", "VS_DebugShape");
	pShader->CreatePixelShader(L"Shader\\debug.fx", "PS_DebugShape");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	pShader->SetRasterizerType(RASTERIZER_STATE_TYPE::CULL_NONE);
	pShader->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::LESS);
	pShader->SetBlendType(BLEND_STATE_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DEBUG);

	AddAsset(L"DebugShapeShader", pShader);
	//---------------------------------------------------------------
	// TilemapShader
	pShader = new HHGraphicShader;

	pShader->CreateVertexShader(L"Shader\\tilemap.fx", "VS_Tilemap");
	pShader->CreatePixelShader(L"Shader\\tilemap.fx", "PS_Tilemap");

	pShader->SetRasterizerType(RASTERIZER_STATE_TYPE::CULL_NONE);
	pShader->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::LESS);
	pShader->SetBlendType(BLEND_STATE_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	AddAsset(L"TilemapShader", pShader);
	//---------------------------------------------------------------
	// ParticleShader
	pShader = new HHGraphicShader;

	pShader->CreateVertexShader(L"Shader\\particle.fx", "VS_Particle");
	pShader->CreateGeometryShader(L"Shader\\particle.fx", "GS_Particle");
	pShader->CreatePixelShader(L"Shader\\particle.fx", "PS_Particle");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	pShader->SetRasterizerType(RASTERIZER_STATE_TYPE::CULL_NONE);
	pShader->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::NO_WRITE);
	pShader->SetBlendType(BLEND_STATE_TYPE::ALPHABLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_PARTICLE);

	AddAsset(L"ParticleRenderShader", pShader);
#pragma endregion

#pragma region Game Shader
	// Standard Shader
	pShader = new HHGraphicShader;

	pShader->CreateVertexShader(L"Shader\\Standard.fx", "VS_Standard");
	pShader->CreatePixelShader(L"Shader\\Standard.fx", "PS_Standard");

	pShader->SetRasterizerType(RASTERIZER_STATE_TYPE::CULL_NONE);
	pShader->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::LESS);
	pShader->SetBlendType(BLEND_STATE_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	AddAsset(L"StandardShader", pShader);
	//---------------------------------------------------------------

#pragma endregion
}

#include "HHParticleTickCS.h"

void HHAssetMgr::CreateEngineComputeShader()
{
	// ParticleTick
	Ptr<HHComputeShader> pCS = nullptr;

	pCS = new HHParticleTickCS;
	AddAsset<HHComputeShader>(L"ParticleTickCS", pCS);
}

void HHAssetMgr::CreateEngineMaterial()
{
	Ptr<HHMaterial>	pMtrl = nullptr;

#pragma region Default Matrerial
	// Std2DMtrl
	pMtrl = new HHMaterial(true);
	pMtrl->SetShader(FindAsset<HHGraphicShader>(L"Std2DShader"));
	AddAsset(L"Std2DMtrl", pMtrl);
	//-----------------------------------------------------------------------
	// Std2DAlphaBlendMtrl
	pMtrl = new HHMaterial(true);
	pMtrl->SetShader(FindAsset<HHGraphicShader>(L"Std2DAlphaBlendShader"));
	AddAsset(L"Std2DAlphaBlendMtrl", pMtrl);
	//-----------------------------------------------------------------------
	// DebugShapeMtrl
	pMtrl = new HHMaterial(true);
	pMtrl->SetShader(FindAsset<HHGraphicShader>(L"DebugShapeShader"));
	AddAsset(L"DebugShapeMtrl", pMtrl);
	//-----------------------------------------------------------------------
	// TileMapMtrl
	pMtrl = new HHMaterial(true);
	pMtrl->SetShader(FindAsset<HHGraphicShader>(L"TilemapShader"));
	AddAsset(L"TilemapMtrl", pMtrl);
	// ParticleRenderMtrl
	pMtrl = new HHMaterial(true);
	pMtrl->SetShader(FindAsset<HHGraphicShader>(L"ParticleRenderShader"));
	AddAsset(L"ParticleRenderMtrl", pMtrl);
#pragma endregion

#pragma region Game Material
	// BackgroundMtrl
	pMtrl = new HHMaterial(true);
	pMtrl->SetShader(FindAsset<HHGraphicShader>(L"StandardShader"));
	AddAsset(L"BackgroundMtrl", pMtrl);
	//-----------------------------------------------------------------------

#pragma endregion
}
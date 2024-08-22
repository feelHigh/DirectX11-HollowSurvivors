#include "pch.h"
#include "HHMeshRender.h"

#include "HHTransform.h"
#include "HHFlipbookRenderer.h"
#include "HHSprite.h"

HHMeshRender::HHMeshRender()
	: HHRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

HHMeshRender::~HHMeshRender()
{
}

void HHMeshRender::FinalTick()
{
}

void HHMeshRender::Render()
{
	if (!GetMesh() || !GetMaterial() || !GetMaterial()->GetShader())
		return;

	// FlipBookComponent 가 있으면 현재 재생중인 Sprite 정보를 Binding 하게 한다.
	if (FlipbookRenderer())
		FlipbookRenderer()->Binding();
	else
		HHFlipbookRenderer::Clear();

	// 위치, 크기, 회전 상태정보 바인딩
	Transform()->Binding();

	// 재질 바인딩(재질 상수, 쉐이더 등등)
	GetMaterial()->Binding();

	// 버텍스버퍼, 인덱스버퍼 바인딩 및 렌더링 호출
	GetMesh()->Render();
}

void HHMeshRender::SaveToFile(FILE* _File)
{
	SaveDataToFile(_File);
}

void HHMeshRender::LoadFromFile(FILE* _File)
{
	LoadDataFromFile(_File);
}

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

	// FlipBookComponent �� ������ ���� ������� Sprite ������ Binding �ϰ� �Ѵ�.
	if (FlipbookRenderer())
		FlipbookRenderer()->Binding();
	else
		HHFlipbookRenderer::Clear();

	// ��ġ, ũ��, ȸ�� �������� ���ε�
	Transform()->Binding();

	// ���� ���ε�(���� ���, ���̴� ���)
	GetMaterial()->Binding();

	// ���ؽ�����, �ε������� ���ε� �� ������ ȣ��
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

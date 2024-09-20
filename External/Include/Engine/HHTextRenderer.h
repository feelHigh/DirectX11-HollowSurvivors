#pragma once
#include "HHRenderComponent.h"

class HHTextRenderer
	: public HHRenderComponent
{
public:
	CLONE(HHTextRenderer);
	HHTextRenderer();
	~HHTextRenderer();

	virtual void FinalTick() override;
	virtual void Render() override;

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

private:
	HHText* pText;

};

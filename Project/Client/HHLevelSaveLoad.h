#pragma once

class HHLevelSaveLoad
{
public:
	static void SaveLevel(const wstring& _FilePath, HHLevel* _Level);
	static void SaveGameObject(FILE* _File, HHGameObject* _Object);


	static class HHLevel* LoadLevel(const wstring& _FilePath);
	static class HHGameObject* LoadGameObject(FILE* _File);
	static class HHComponent* GetComponent(COMPONENT_TYPE _Type);

};

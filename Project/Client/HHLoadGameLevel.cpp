#include "pch.h"
#include "HHLoadGameLevel.h"

#include <Engine/HHPathMgr.h>

#include "HHLevelSaveLoad.h"

HHLoadGameLevel::HHLoadGameLevel()
    : m_arrLevel{}
{
}

HHLoadGameLevel::~HHLoadGameLevel()
{
}

void HHLoadGameLevel::Initialize()
{
    // Get the content path and set the level directory path
    wstring StrLevelLoadPath = HHPathMgr::GetInstance()->GetContentPath();
    StrLevelLoadPath += L"Level\\";

    // Create a map to associate file names with enum values
    unordered_map<wstring, LEVEL_TYPE> levelMap =
    {
        { L"TitleLevel.lv", LEVEL_TYPE::TITLE },
        { L"SanctuaryLevel.lv", LEVEL_TYPE::SANCTUARY }
    };

    for (const auto& entry : directory_iterator(StrLevelLoadPath))
    {
        // Get the file path as a wstring
        std::wstring filePath = entry.path().wstring();

        // Get the file name only
        std::wstring fileName = entry.path().filename().wstring();

        // Check if the file name is in our map
        if (levelMap.find(fileName) != levelMap.end()) 
        {
            // Get the corresponding LEVEL_TYPE
            LEVEL_TYPE levelType = levelMap[fileName];

            // Load the level file
            HHLevel* pLoadedLevel = HHLevelSaveLoad::LoadLevel(filePath);

            // Store the loaded level in the appropriate array index
            m_arrLevel[(UINT)levelType] = pLoadedLevel;
        }
    }

    HHLevel* pStartLevel = m_arrLevel[(UINT)LEVEL_TYPE::TITLE];
    ChangeLevel(pStartLevel, LEVEL_STATE::PLAY);
}

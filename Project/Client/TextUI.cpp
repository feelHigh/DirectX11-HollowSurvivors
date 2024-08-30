#include "pch.h"
#include "TextUI.h"

#include "Engine/HHGameObject.h"
#include "Engine/HHText.h"

TextUI::TextUI()
	: ComponentUI(COMPONENT_TYPE::GAME_TEXT)
{
}

TextUI::~TextUI()
{
}

void TextUI::Update()
{
	Title();

	HHText* pText = GetTargetObject()->Text();

	std::string strText = ConvertWcharToString(pText->GetText().c_str()); // Use c_str() to get the const wchar_t* from wstring
	ImGui::Text("Output Text");
	ImGui::InputText("##OutputText", (char*)strText.c_str(), strText.length(), ImGuiInputTextFlags_ReadOnly);

	/*string strText = string(pText->GetText().begin(), pText->GetText().end());
	ImGui::Text("Output Text");
	ImGui::InputText("##OutputText", (char*)strText.c_str(), strText.length(), ImGuiInputTextFlags_ReadOnly);*/
}

string TextUI::ConvertWcharToString(const wchar_t* wstr)
{
	if (wstr == nullptr) {
		return string();
	}

	// Get the required size for the buffer
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);

	// Allocate a buffer for the converted string
	string strTo(size_needed, 0);

	// Convert the wide-character string to a multi-byte string
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &strTo[0], size_needed, nullptr, nullptr);

	return strTo;
}

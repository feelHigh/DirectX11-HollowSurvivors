#include "pch.h"

tTransform	g_Trans = {};
tGlobalData g_GlobalData = {};

const char* ASSET_TYPE_STRING[] =
{
	"MESH",
	"MESH_DATA",
	"MATERIAL",
	"PREFAB",
	"TEXTURE",
	"SOUND",
	"GRAPHIC_SHADER",
	"COMPUTE_SHADER",
	"SPRITE",
	"FLIPBOOK",
	"FSM",
};

const char* ToString(ASSET_TYPE _Type) { return ASSET_TYPE_STRING[(UINT)_Type]; }

const char* COMPONENT_TYPE_STRING[] =
{
	"TRANSFORM",
	"COLLIDER2D",
	"COLLIDER3D",
	"LIGHT2D",
	"LIGHT3D",
	"FLIPBOOKCOMPONENT",
	"ANIMATOR3D",
	"STATE_MACHINE",
	"RIGIDBODY",
	"CAMERA",
	"MESHRENDER",
	"TILEMAP",
	"PARTICLE_SYSTEM",
	"DECAl",
	"SKYBOX",
	"LANDSCAPE",
	"GAME_TEXT",		// 텍스트 출력
	"GAME_BUTTON",		// UI 버턴
};

const char* ToString(COMPONENT_TYPE _Type) { return COMPONENT_TYPE_STRING[(UINT)_Type]; }

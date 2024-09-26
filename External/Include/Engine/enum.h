	#pragma once

enum class CONSTANT_BUFFER_TYPE
{
	TRANSFORM,
	MATERIAL,
	SPRITE,
	GLOBAL,
	END,
};

enum class ASSET_TYPE
{
	MESH,
	MESH_DATA,
	MATERIAL,
	PREFAB,
	TEXTURE,
	SOUND,
	GRAPHIC_SHADER,
	COMPUTE_SHADER,
	SPRITE,
	FLIPBOOK,
	FSM,
	END,
};

extern const char* ASSET_TYPE_STRING[(UINT)ASSET_TYPE::END];
const char* ToString(ASSET_TYPE _Type);

enum class COMPONENT_TYPE
{
	TRANSFORM,
	COLLIDER2D,
	COLLIDER3D,
	LIGHT2D,
	LIGHT3D,
	FLIPBOOK_RENDERER,
	ANIMATOR3D,
	RIGIDBODY,
	CAMERA,
	STATE_MACHINE,

	MESHRENDER,
	TILEMAP,
	PARTICLESYSTEM,
	DECAl,
	SKYBOX,
	LANDSCAPE,

	TEXTRENDERER,

	GAME_TEXT,
	GAME_BUTTON,

	END,

	// Script는 해당 게임 오브젝트의 고유 기능 담당하기 때문에 END 뒤에 배치
	SCRIPT,
};

extern const char* COMPONENT_TYPE_STRING[(UINT)COMPONENT_TYPE::END];
const char* ToString(COMPONENT_TYPE _Type);

enum DIRECTION_TYPE
{
	RIGHT,
	UP,
	FRONT,
};

enum class RASTERIZER_STATE_TYPE
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,
	END,
};

enum class DEPTH_STENCIL_STATE_TYPE
{
	LESS,
	LESS_EQUAL,

	GREATER,

	NO_TEST,
	NO_WRITE,
	NO_TEST_NO_WRITE,

	END,
};

enum class BLEND_STATE_TYPE
{
	DEFAULT,
	ALPHABLEND_COVERAGE,
	ALPHABLEND,
	ONE_ONE,
	END,
};

enum SCALAR_PARAM
{
	INT_0, INT_1, INT_2, INT_3,
	FLOAT_0, FLOAT_1, FLOAT_2, FLOAT_3,
	VEC2_0, VEC2_1, VEC2_2, VEC2_3,
	VEC4_0, VEC4_1, VEC4_2, VEC4_3,
	MAT_0, MAT_1, MAT_2, MAT_3,
};

enum TEXTURE_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEXCUBE_0,
	TEXCUBE_1,

	TEXARR_0,
	TEXARR_1,

	END,
};

enum SHADER_DOMAIN
{
	DOMAIN_OPAQUE,		// 불투명
	DOMAIN_MASKED,		// 투명
	DOMAIN_TRANSPARENT,	// 반투명
	DOMAIN_PARTICLE,	// 파티클
	DOMAIN_POSTPROCESS, // 후처리
	DOMAIN_UI,			// UI
	DOMAIN_DEBUG,		// 디버그
	DOMAIN_NONE,		// 미설정
};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,
	CUBE,
	SPHERE,
};

enum TASK_TYPE
{
	// Param_0 : Layer, Param_1 : Object Address
	CREATE_OBJECT,

	// Param 0 : Next Level State
	CHANGE_LEVEL_STATE,

	// Param_0 : Delete Object Adress
	DELETE_OBJECT,

	// Param_0 : Level Adress, Param_1 : Level State
	CHANGE_LEVEL,

	// Param_0 : Asset Address
	DELETE_ASSET,

	LEVEL_CHANGED,
	ASSET_CHANGED,

	ADD_CHILD,
	COMPONENT_ACTIVATE,
	COMPONENT_DEACTIVATE,
};

enum class LEVEL_TYPE
{
	TITLE,
	TUTORIAL,
	SANCTUARY,

	END,
};

enum LEVEL_STATE
{
	PLAY,
	PAUSE,
	STOP,
};

enum class LIGHT_TYPE
{
	DIRECTIONAL,
	POINT,
	SPOT,
};

enum class PARTICLE_MODULE
{
	SPAWN,
	SPAWN_BURST,
	ADD_VELOCITY,
	SCALE,
	DRAG,
	NOISE_FORCE,
	RENDER,

	END,
};

enum BUTTON_TYPE
{
	TITLE_PLAY,
	TITLE_OPTION,
	TITLE_CREDITS,
	TITLE_QUIT,
};

enum class DIR
{
	DOWN,
	UP,
	LEFT,
	RIGHT,
	NONE,
};

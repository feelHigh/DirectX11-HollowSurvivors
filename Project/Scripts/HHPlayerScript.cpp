#include "pch.h"
#include "HHPlayerScript.h"

HHPlayerScript::HHPlayerScript()
	: HHScript(UINT(SCRIPT_TYPE::PLAYERSCRIPT))
	, m_eDir(DIR::DOWN)
	, m_eState(PLAYER_STATE::IDLE)
	, m_uHP(10)
	, m_uMP(2)
	, m_uProgress(0)
	, m_fSpeed(340.f)
	, m_pFlipbook(nullptr)
	, m_iFPS(8)
	, m_iCombo(0)
	//, m_pFlipbookRenderer(nullptr)
{
	//AddScriptParam(SCRIPT_PARAM::FLOAT, "PlayerSpeed", &m_Speed);
	//AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
}

HHPlayerScript::~HHPlayerScript()
{
}

void HHPlayerScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();

#pragma region Load Animation Asset
	Ptr<HHFlipbook> m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Idle_Down.flip");
	FlipbookRenderer()->AddFlipbook(0, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Idle_Up.flip");
	FlipbookRenderer()->AddFlipbook(1, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Idle_Left.flip");
	FlipbookRenderer()->AddFlipbook(2, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Idle_Right.flip");
	FlipbookRenderer()->AddFlipbook(3, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Walk_Down.flip");
	FlipbookRenderer()->AddFlipbook(4, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Walk_Up.flip");
	FlipbookRenderer()->AddFlipbook(5, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Walk_Left.flip");
	FlipbookRenderer()->AddFlipbook(6, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Walk_Right.flip");
	FlipbookRenderer()->AddFlipbook(7, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Dash_Down.flip");
	FlipbookRenderer()->AddFlipbook(8, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Dash_Up.flip");
	FlipbookRenderer()->AddFlipbook(9, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Dash_Left.flip");
	FlipbookRenderer()->AddFlipbook(10, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Dash_Right.flip");
	FlipbookRenderer()->AddFlipbook(11, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Spell_Down.flip");
	FlipbookRenderer()->AddFlipbook(12, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Spell_Up.flip");
	FlipbookRenderer()->AddFlipbook(13, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Spell_Left.flip");
	FlipbookRenderer()->AddFlipbook(14, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Spell_Right.flip");
	FlipbookRenderer()->AddFlipbook(15, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo1_Down.flip");
	FlipbookRenderer()->AddFlipbook(16, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo1_Up.flip");
	FlipbookRenderer()->AddFlipbook(17, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo1_Left.flip");
	FlipbookRenderer()->AddFlipbook(18, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo1_Right.flip");
	FlipbookRenderer()->AddFlipbook(19, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo2_Down.flip");
	FlipbookRenderer()->AddFlipbook(20, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo2_Up.flip");
	FlipbookRenderer()->AddFlipbook(21, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo2_Left.flip");
	FlipbookRenderer()->AddFlipbook(22, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo2_Right.flip");
	FlipbookRenderer()->AddFlipbook(23, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo3_Down.flip");
	FlipbookRenderer()->AddFlipbook(24, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo3_Up.flip");
	FlipbookRenderer()->AddFlipbook(25, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo3_Left.flip");
	FlipbookRenderer()->AddFlipbook(26, m_pFlipbook);

	m_pFlipbook = HHAssetMgr::GetInstance()->FindAsset<HHFlipbook>(L"Animation\\Player_Attack_Sword_Combo3_Right.flip");
	FlipbookRenderer()->AddFlipbook(27, m_pFlipbook);

	FlipbookRenderer()->Play(0, 8, true);
#pragma endregion
	
}

void HHPlayerScript::Tick()
{
	switch (m_eState)
	{
	case PLAYER_STATE::IDLE:
		Idle();
		break;
	case PLAYER_STATE::MOVE:
		Move();
		break;
	case PLAYER_STATE::DASH:
		Dash();
		break;
	case PLAYER_STATE::ATTACK_MELEE:
		Attack_Melee();
		break;
	case PLAYER_STATE::ATTACK_SPELL:
		Attack_Spell();
		break;
	case PLAYER_STATE::DEAD:
		Dead();
		break;
	case PLAYER_STATE::NONE:
		break;
	default:
		break;
	}

}

void HHPlayerScript::Idle()
{
	// Move
	if (KEY_TAP(KEY::S) || KEY_TAP(KEY::W) || KEY_TAP(KEY::A) || KEY_TAP(KEY::D)
		|| KEY_PRESSED(KEY::S) || KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D))
	{
		m_eState = PLAYER_STATE::MOVE;
		Move_Animation();
	}

	// Dash
	if (KEY_TAP(KEY::SPACE))
	{
		m_eState = PLAYER_STATE::DASH;
		Dash_Animation();
	}

	// Attack
	if (KEY_TAP(KEY::LBTN) || KEY_TAP(KEY::RBTN))
	{
		if(KEY_TAP(KEY::LBTN))
		{
			m_eState = PLAYER_STATE::ATTACK_MELEE;
			Attack_Melee_Animation();
		}
		if(KEY_TAP(KEY::RBTN))
		{
			m_eState = PLAYER_STATE::ATTACK_SPELL;
			Attack_Spell_Animation();
		}
	}
}

void HHPlayerScript::Move()
{
	Vec3 vPos = Transform()->GetRelativePosition();

	// Direction
	if (KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::S))
	{
		if (KEY_RELEASED(KEY::W))
		{
			m_eDir = DIR::UP;
			Move_Animation();
		}
		if (KEY_RELEASED(KEY::S))
		{
			m_eDir = DIR::DOWN;
			Move_Animation();
		}
	}
	if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D))
	{
		if (KEY_RELEASED(KEY::A))
		{
			m_eDir = DIR::LEFT;
			Move_Animation();
		}
		if (KEY_RELEASED(KEY::D))
		{
			m_eDir = DIR::RIGHT;
			Move_Animation();
		}
	}
	if (KEY_TAP(KEY::W) || KEY_TAP(KEY::S) || KEY_RELEASED(KEY::W) || KEY_RELEASED(KEY::S))
	{
		if (KEY_TAP(KEY::W))
		{
			Move_Animation();
		}

		if (KEY_RELEASED(KEY::S))
		{
			Move_Animation();
		}

		if (KEY_RELEASED(KEY::W))
		{
			if (KEY_PRESSED(KEY::A))
			{
				m_eDir = DIR::LEFT;
			}
			else if (KEY_PRESSED(KEY::D))
			{
				m_eDir = DIR::RIGHT;
			}

			Move_Animation();
		}

		if (KEY_RELEASED(KEY::S))
		{
			if (KEY_PRESSED(KEY::A))
			{
				m_eDir = DIR::LEFT;
			}
			else if (KEY_PRESSED(KEY::D))
			{
				m_eDir = DIR::RIGHT;
			}

			Move_Animation();
		}
	}

	if (KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D) || KEY_PRESSED(KEY::W) || KEY_PRESSED(KEY::S))
	{
		if (KEY_PRESSED(KEY::W))
		{
			vPos.y += m_fSpeed * DT;
		}

		if (KEY_PRESSED(KEY::S))
		{
			vPos.y -= m_fSpeed * DT;
		}

		if (KEY_PRESSED(KEY::A))
		{
			vPos.x -= m_fSpeed * DT;
		}

		if (KEY_PRESSED(KEY::D))
		{
			vPos.x += m_fSpeed * DT;
		}
	}
	else
	{
		m_eState = PLAYER_STATE::IDLE;
		Idle_Animation();
	}

	Transform()->SetRelativePosition(vPos);

	// Handle dash
	if (KEY_TAP(KEY::SPACE))
	{
		m_eState = PLAYER_STATE::DASH;
		Dash_Animation();
	}
}

void HHPlayerScript::Dash()
{
	Vec3 vPos = Transform()->GetRelativePosition();

	switch (m_eDir)
	{
	case DIR::DOWN:
		vPos.y -= m_fSpeed * 256.0f * DT;
		FlipbookRenderer()->Play(8, m_iFPS, false);
		break;
	case DIR::UP:
		vPos.y += m_fSpeed * 256.0f * DT;
		FlipbookRenderer()->Play(9, m_iFPS, false);
		break;
	case DIR::LEFT:
		vPos.x -= m_fSpeed * 256.0f * DT;
		FlipbookRenderer()->Play(10, m_iFPS, false);
		break;
	case DIR::RIGHT:
		vPos.x += m_fSpeed * 256.0f * DT;
		FlipbookRenderer()->Play(11, m_iFPS, false);
		break;
	default:
		break;
	}

	Transform()->SetRelativePosition(vPos);

	// After dashing, return to idle or move state
	m_eState = PLAYER_STATE::IDLE;
}

void HHPlayerScript::Attack_Melee()
{
}

void HHPlayerScript::Attack_Spell()
{
}

void HHPlayerScript::Dead()
{
}

void HHPlayerScript::Idle_Animation()
{
	switch (m_eDir)
	{
	case DIR::DOWN:
		FlipbookRenderer()->Play(0, m_iFPS, true);
		break;
	case DIR::UP:
		FlipbookRenderer()->Play(1, m_iFPS, true);
		break;
	case DIR::LEFT:
		FlipbookRenderer()->Play(2, m_iFPS, true);
		break;
	case DIR::RIGHT:
		FlipbookRenderer()->Play(3, m_iFPS, true);
		break;
	case DIR::NONE:
		break;
	default:
		break;
	}
}

void HHPlayerScript::Move_Animation()
{
	if (KEY_TAP(KEY::S) || KEY_PRESSED(KEY::S))
	{
		m_eDir = DIR::DOWN;
		FlipbookRenderer()->Play(4, m_iFPS, true);
	}

	if (KEY_TAP(KEY::W) || KEY_PRESSED(KEY::W))
	{
		m_eDir = DIR::UP;
		FlipbookRenderer()->Play(5, m_iFPS, true);
	}

	if (KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A))
	{
		m_eDir = DIR::LEFT;
		FlipbookRenderer()->Play(6, m_iFPS, true);
	}

	if (KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D))
	{
		m_eDir = DIR::RIGHT;
		FlipbookRenderer()->Play(7, m_iFPS, true);
	}
}

void HHPlayerScript::Dash_Animation()
{
	switch (m_eDir)
	{
	case DIR::DOWN:
		FlipbookRenderer()->Play(8, m_iFPS, false);
		break;
	case DIR::UP:
		FlipbookRenderer()->Play(9, m_iFPS, false);
		break;
	case DIR::LEFT:
		FlipbookRenderer()->Play(10, m_iFPS, false);
		break;
	case DIR::RIGHT:
		FlipbookRenderer()->Play(11, m_iFPS, false);
		break;
	case DIR::NONE:
		break;
	default:
		break;
	}
}

void HHPlayerScript::Attack_Melee_Animation()
{
	Vec3 vPos = Transform()->GetRelativePosition();

	switch (m_eDir)
	{
	case DIR::DOWN:
		vPos.y -= m_fSpeed * 32.0f * DT;
		FlipbookRenderer()->Play(16, m_iFPS, false);
		break;
	case DIR::UP:
		vPos.y += m_fSpeed * 32.0f * DT;
		FlipbookRenderer()->Play(19, m_iFPS, false);
		break;
	case DIR::LEFT:
		vPos.x -= m_fSpeed * 32.0f * DT;
		FlipbookRenderer()->Play(21, m_iFPS, false);
		break;
	case DIR::RIGHT:
		vPos.x += m_fSpeed * 32.0f * DT;
		FlipbookRenderer()->Play(24, m_iFPS, false);
		break;
	case DIR::NONE:
		break;
	default:
		break;
	}

	Transform()->SetRelativePosition(vPos);
}

void HHPlayerScript::Attack_Spell_Animation()
{
	Vec3 vPos = Transform()->GetRelativePosition();

	switch (m_eDir)
	{
	case DIR::DOWN:
		vPos.y -= m_fSpeed * 32.0f * DT;
		FlipbookRenderer()->Play(12, m_iFPS, false);
		break;
	case DIR::UP:
		vPos.y += m_fSpeed * 32.0f * DT;
		FlipbookRenderer()->Play(13, m_iFPS, false);
		break;
	case DIR::LEFT:
		vPos.x -= m_fSpeed * 32.0f * DT;
		FlipbookRenderer()->Play(14, m_iFPS, false);
		break;
	case DIR::RIGHT:
		vPos.x += m_fSpeed * 32.0f * DT;
		FlipbookRenderer()->Play(15, m_iFPS, false);
		break;
	case DIR::NONE:
		break;
	default:
		break;
	}

	Transform()->SetRelativePosition(vPos);
}

void HHPlayerScript::Dead_Animation()
{
}


void HHPlayerScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
}

void HHPlayerScript::Overlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
}

void HHPlayerScript::EndOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
}

void HHPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
	//SaveAssetReference(m_Texture, _File);
}

void HHPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
	//LoadAssetReference(m_Texture, _File);
}
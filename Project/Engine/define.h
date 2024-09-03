#pragma once

#define SINGLE(Type) private:\
						Type();\
						~Type();\
						friend class HHSingleton<Type>;

#define DEVICE 	HHDevice::GetInstance()->GetDevice()
#define CONTEXT HHDevice::GetInstance()->GetContext()
#define MAX_LAYER 32

#define DT HHTimeMgr::GetInstance()->GetDeltaTime()
#define ENGINE_DT HHTimeMgr::GetInstance()->GetEngineDeltaTime()

#define KEY_CHECK(KEY, STATE) HHKeyMgr::GetInstance()->GetKeyState(KEY) == STATE
#define KEY_TAP(KEY) HHKeyMgr::GetInstance()->GetKeyState(KEY) == KEY_STATE::TAP
#define KEY_PRESSED(KEY) HHKeyMgr::GetInstance()->GetKeyState(KEY) == KEY_STATE::PRESSED
#define KEY_RELEASED(KEY) HHKeyMgr::GetInstance()->GetKeyState(KEY) == KEY_STATE::RELEASED

#define CLONE(Type) virtual Type* Clone() {return new Type(*this); }
#define CLONE_DISABLE(Type) virtual Type* Clone() { return nullptr; }

#define DELETE(p) if(nullptr != p) delete p; p = nullptr;

#define FIND_OBJECT(ObjectName) HHLevelMgr::GetInstance()->GetCurrentLevel()->FindObjectByName(ObjectName)

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

#pragma once

// Engine
#ifdef _DEBUG
#pragma comment(lib, "Engine\\Engine_d")
#else
#pragma comment(lib, "Engine\\Engine")
#endif

#include <Engine/global.h>
#include <Engine/HHEngine.h>

// Scripts
#ifdef _DEBUG
#pragma comment(lib, "Scripts\\Scripts_d")
#else
#pragma comment(lib, "Scripts\\Scripts")
#endif


#include <set>
using std::set;
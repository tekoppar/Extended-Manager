#pragma once

#ifndef _MANAGER_H
#define _MANAGER_H

#include "Adresses.h"
#include "detours.h"
#include "StringUtils.h"
#include "MessageClass.h"
#include "HelperClasses.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Transform.h"

#include "AkLogger.h"
#include "Object.h"
#include "Component.h"
#include "GameObject.h"
#include "GetClasses.h"

typedef void (*tCreateCheckpoint)(void* GameController);
tCreateCheckpoint oCreateCheckpoint;

typedef float(*tGetGameCompletion)(void* GameController);
tGetGameCompletion oGetGameCompletion;

typedef Moon::Object(*tInstantiate)(Moon::Object object);
tInstantiate oInstantiate;

typedef void(__thiscall* CClassFunction_t)(void* __this);
CClassFunction_t Real_CClassFunction;

typedef app::String* (__thiscall* tIl2CppString)(const char* str);
tIl2CppString RealIl2cpp_string_new_wrapper;

typedef void(__thiscall* tGameControllerUpdate)(void* __this);
tGameControllerUpdate Real_GameControllerUpdate;

typedef void(__thiscall* tOnPointerClick)(void* __this);
tOnPointerClick Real_OnPointerClick;

#endif
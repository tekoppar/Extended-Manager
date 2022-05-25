#pragma once

#ifndef _MANAGER_H
#define _MANAGER_H

#include "Adresses.h"
#include "detours.h"
#include "StringUtils.h"
#include "MessageClass.h"

typedef void (*tCreateCheckpoint)(void* GameController);
tCreateCheckpoint oCreateCheckpoint;

typedef float(*tGetGameCompletion)(void* GameController);
tGetGameCompletion oGetGameCompletion;

typedef void(__thiscall* CClassFunction_t)(void* __this);
CClassFunction_t Real_CClassFunction;

typedef app::String* (__thiscall* tIl2CppString)(const char* str);
tIl2CppString RealIl2cpp_string_new_wrapper;

typedef void(__thiscall* tGameControllerUpdate)(void* __this);
tGameControllerUpdate Real_GameControllerUpdate;

typedef void(__thiscall* tMoonDriverUpdate)(void* __this);
tMoonDriverUpdate Real_MoonDriverUpdate;

typedef void(__thiscall* tMoonDriverFixedUpdate)(void* __this);
tMoonDriverFixedUpdate Real_MoonDriverFixedUpdate;

typedef void(__thiscall* tMoonDriverLateUpdate)(void* __this);
tMoonDriverLateUpdate Real_MoonDriverLateUpdate;

typedef void(__thiscall* tMoonDriverTimelineUpdate)(void* __this, float deltaTime);
tMoonDriverTimelineUpdate Real_MoonDriverTimelineUpdate;

typedef void(__thiscall* tMoonDriverSystemOnUpdate)(void* __this, float deltaTime);
tMoonDriverSystemOnUpdate Real_MoonDriverSystemOnUpdate;

typedef void(__thiscall* tUpdateManagerUpdate)(void* __this, float deltaTime);
tUpdateManagerUpdate Real_UpdateManagerUpdate;

typedef void(__thiscall* tUnityPlayerLoop)(void* __this);
tUnityPlayerLoop Real_UnityPlayerLoop;

typedef void(__thiscall* tPlayerInputFixedUpdate)(void* __this);
tPlayerInputFixedUpdate Real_tPlayerInputFixedUpdate;

typedef void(__thiscall* tSeinOnKill)(void* __this);
tSeinOnKill Real_SeinOnKill;

#endif
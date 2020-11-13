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

typedef void(__thiscall* tOnPointerClick)(void* __this);
tOnPointerClick Real_OnPointerClick;

typedef void(__thiscall* tSeinOnKill)(void* __this);
tSeinOnKill Real_SeinOnKill;

#endif
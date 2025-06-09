#pragma once
#include "offset.h"
#include "XorStr.h"
#include "Struct.h"

class Cheat
{
public:

	Cheat(UINT64 MainModule,uint64_t baseAddress);
	void Cache();
	void GetGNames(uint64_t baseAddress);
	uint64_t UWorld, CurrentLevel, GameInstance, LocalPlayers, PlayerController, AcknowledgedPawn, PlayerCameraManager, GNames;

	CameraCacheEntry CameraEntry; // ScriptStruct Engine.CameraCacheEntry

private:

	UINT64 m_MainModule;   // ´æ´¢ MainModule
	uint64_t m_baseAddress; // ´æ´¢ baseAddress

};

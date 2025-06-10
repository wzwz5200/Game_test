#pragma once
#include "offset.h"
#include "XorStr.h"
#include "Struct.h"
#include <vector>
#include "ActorEntity.h"

class Cheat
{
public:

	Cheat(UINT64 MainModule,uint64_t baseAddress);
	void Cache();
	void GetGNames(uint64_t baseAddress);
	void UpdatePlayers();

	std::vector<std::shared_ptr<ActorEntity>> GetActors();

	CameraCacheEntry GetCameraCache();

	void RefreshViewMatrix();
	uint64_t GetActorSize();

	std::string GetNames(DWORD ID);
	std::string GetNamesFromList(DWORD ID);

	

private:
	uint64_t UWorld, CurrentLevel, GameInstance, LocalPlayers, PlayerController, AcknowledgedPawn, PlayerCameraManager, GNames;
	std::vector<std::shared_ptr<ActorEntity>> Actors;
	CameraCacheEntry CameraEntry; // ScriptStruct Engine.CameraCacheEntry
	uint64_t OwningActor;
	int MaxPacket;
	int localTempId;
	UINT64 m_MainModule;   // ´æ´¢ MainModule
	uint64_t m_baseAddress; // ´æ´¢ baseAddress

};

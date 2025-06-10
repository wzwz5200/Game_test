#pragma once
#include <intrin.h> // Include this header for intrinsic functions
#include <cstdint>
#include <map>
#include <string>

#include <map>

struct _Local
{
	int Teamid;
	int SpectatedCount;
	bool reset;
	std::map<int, std::string> KV;
}inline Local;

namespace SDK {
	//Version 35.2.2.3
  //The offset has not been tested, if there is an error please let me know.
	constexpr uint64_t XenuineDecrypt = 0x0E71EB28;
	constexpr uint64_t GWorld = 0x10026FE8;
	constexpr uint64_t Names = 0x102A7468;
	constexpr uint64_t NamesOffset = 0x0010;
	constexpr uint64_t ElementsPerChunk = 0x3E60;

	constexpr uint64_t Ror = 0x0000;
	constexpr uint64_t rval = 0x0004;
	constexpr uint64_t sval = 0x0010;
	constexpr uint64_t offset = 0x0014;
	constexpr uint64_t xor_key_1 = 0x1AB534C4;
	constexpr uint64_t xor_key_2 = 0x2E7134C4;

	constexpr uint64_t GameInstance = 0x0348;
	constexpr uint64_t LocalPlayers = 0x00B8;
	constexpr uint64_t Actors = 0x0188;
	constexpr uint64_t ActorsForGC = 0x00E0;
	constexpr uint64_t ComponentToWorld = 0x0260;
	constexpr uint64_t ComponentLocation = 0x0270;
	constexpr uint64_t CurrentWeaponIndex = 0x0301;
	constexpr uint64_t CurrentLevel = 0x03E0;
	constexpr uint64_t TimeSeconds = 0x03CC;
	constexpr uint64_t WorldOrigin = 0x0838;
	constexpr uint64_t PlayerController = 0x0030;
	constexpr uint64_t AcknowledgedPawn = 0x04B0;
	constexpr uint64_t ViewTarget = 0x0420;
	constexpr uint64_t PlayerCameraManager = 0x04D8;
	constexpr uint64_t CameraFov = 0x0A20;
	constexpr uint64_t CameraPos = 0x0FC8;
	constexpr uint64_t CameraRot = 0x0A40;
	constexpr uint64_t RootComponent = 0x0340;
	constexpr uint64_t ReplicatedMovement = 0x0088;
	constexpr uint64_t PlayerState = 0x0428;
	constexpr uint64_t Mesh = 0x07B0;
	constexpr uint64_t StaticMesh = 0x0AD8;
	constexpr uint64_t Health = 0x0A30;
	constexpr uint64_t GroggyHealth = 0x1840;
	constexpr uint64_t CharacterName = 0x0E30;
	constexpr uint64_t LastTeamNum = 0x1870;
	constexpr uint64_t SpectatedCount = 0x26C0;
	constexpr uint64_t VehicleRiderComponent = 0x2000;
	constexpr uint64_t WeaponProcessor = 0x0968;
	constexpr uint64_t ComponentVelocity = 0x0330;
	constexpr uint64_t LastSubmitTime = 0x0738;
	constexpr uint64_t LastRenderTimeOnScreen = 0x073C;
	constexpr uint64_t AnimScriptInstance = 0x0E10;
	constexpr uint64_t Packge = 0x05A0;
	constexpr uint64_t ItemID = 0x026C;
	constexpr uint64_t ItemTable = 0x00A8;
	constexpr uint64_t DroppedItem_Item = 0x0468;
	constexpr uint64_t DroppedItemGroup = 0x0100;
	constexpr uint64_t DroppedItemGroup_Count = 0x0108;
	constexpr uint64_t DroppedItemInteractionComponent_Item = 0x0860;
	constexpr uint64_t SeatIndex = 0x0220;
	constexpr uint64_t LastVehiclePawn = 0x0260;
	constexpr uint64_t EquippedWeapons = 0x01F8;
	constexpr uint64_t WeaponTrajectoryData = 0x1168;
	constexpr uint64_t ControlRotation_CP = 0x0710;
	constexpr uint64_t RecoilADSRotation_CP = 0x08E4;
	constexpr uint64_t LeanLeftAlpha_CP = 0x0758;
	constexpr uint64_t LeanRightAlpha_CP = 0x075C;
	constexpr uint64_t TrajectoryConfig = 0x0100;
	constexpr uint64_t PlayerStatistics = 0x04E0;
	constexpr uint64_t AimOffsets = 0x1BF8;
	constexpr uint64_t DamageDealtOnEnemy = 0x0830;
	constexpr uint64_t PartnerLevel = 0x04F6;
	constexpr uint64_t SurvivalLevel = 0x0BA4;
	constexpr uint64_t PubgIdData = 0x0BA0;
	constexpr uint64_t CharacterMovement = 0x0480;
	constexpr uint64_t LastUpdateVelocity = 0x03D0;
	constexpr uint64_t GameState = 0x0890;
	constexpr uint64_t FeatureRep = 0x0D98;
	constexpr uint64_t LerpSafetyZoneRadius = 0x00AC;
	constexpr uint64_t LerpSafetyZonePosition = 0x00A0;
	constexpr uint64_t PoisonGasWarningRadius = 0x00C8;
	constexpr uint64_t PoisonGasWarningPosition = 0x00BC;

	constexpr uint64_t BlockInputWidgetList = 0x05D0;
	constexpr uint64_t TrainingSpotToolTipWidget = 0x06F8;
	constexpr uint64_t MyHUD = 0x04D0;
	constexpr uint64_t WidgetStateMap = 0x0558;
	constexpr uint64_t TrainingMapGrid = 0x05E0;
	constexpr uint64_t MapGrid = 0x04A8;
	constexpr uint64_t SelectMinimapSizeIndex = 0x05B8;
	constexpr uint64_t Slot = 0x0030;
	constexpr uint64_t LayoutData = 0x0038;
	constexpr uint64_t Alignment = 0x0020;
	constexpr uint64_t Visibility = 0x00A1;

	constexpr uint64_t Health0 = 0x0280;
	constexpr uint64_t Health1 = 0x0958;
	constexpr uint64_t Health2 = 0x0980;
	constexpr uint64_t Health3 = 0x0A44;
	constexpr uint64_t Health4 = 0x0A30;
	constexpr uint64_t Health5 = 0x0A45;
	constexpr uint64_t Health6 = 0x0A40;

	constexpr uint64_t HealthXorKeys0 = 0xCEC7A59C;
	constexpr uint64_t HealthXorKeys1 = 0x9B63B286;
	constexpr uint64_t HealthXorKeys2 = 0xCA6BE2BD;
	constexpr uint64_t HealthXorKeys3 = 0x863848F3;
	constexpr uint64_t HealthXorKeys4 = 0x74911D0A;
	constexpr uint64_t HealthXorKeys5 = 0x23DDAEA4;
	constexpr uint64_t HealthXorKeys6 = 0x945F3C8;
	constexpr uint64_t HealthXorKeys7 = 0xBD39B521;
	constexpr uint64_t HealthXorKeys8 = 0xBAE7A58;
	constexpr uint64_t HealthXorKeys9 = 0xA8EF8687;
	constexpr uint64_t HealthXorKeys10 = 0xE27593B5;
	constexpr uint64_t HealthXorKeys11 = 0x9F8ADB68;
	constexpr uint64_t HealthXorKeys12 = 0xBD7443D5;
	constexpr uint64_t HealthXorKeys13 = 0x8693F307;
	constexpr uint64_t HealthXorKeys14 = 0xF3099E38;
	constexpr uint64_t HealthXorKeys15 = 0xE1D42A5C;

}
// Define a macro for __ROL4__ if it's not already defined
#ifndef __ROL4__
#define __ROL4__(value, shift) _rotl(value, shift)
#endif
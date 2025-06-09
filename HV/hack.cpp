#include "hack.h"

Cheat::Cheat(UINT64 MainModule, uint64_t baseAddress)
    : m_MainModule(MainModule), m_baseAddress(baseAddress)

{

    //获取基础地址
    InitDecrypt(MainModule, SDK::XenuineDecrypt);
   // uint64_t baseAddress = GetModule(targetProcessId, L"TslGame.exe"); // 获取模块基址
    uint64_t encryptedUWorld = HV::Read<uint64_t>(baseAddress + SDK::GWorld);

    UWorld = Decrypt(encryptedUWorld);

    std::cout << "Uworld : " << UWorld << std::endl;

    GameInstance = Decrypt(HV::Read<uint64_t>(UWorld + SDK::GameInstance));

    LocalPlayers = Decrypt(HV::Read<uint64_t>(HV::Read<uint64_t>(GameInstance + SDK::LocalPlayers)));

    PlayerController = Decrypt(HV::Read<uint64_t>(LocalPlayers + SDK::PlayerController));

    PlayerCameraManager = HV::Read<uint64_t>(PlayerController + SDK::PlayerCameraManager);
    float FOV = HV::Read<float>(PlayerCameraManager + SDK::CameraFov);


   


        CameraEntry.POV.FOV = HV::Read<float>(PlayerCameraManager + SDK::CameraFov);
        CameraEntry.POV.Location = HV::Read<UEVector>(PlayerCameraManager + SDK::CameraPos);
        CameraEntry.POV.Rotation = HV::Read<UERotator>(PlayerCameraManager + SDK::CameraRot);

        std::cout << "FOV : " << CameraEntry.POV.Rotation.Pitch << std::endl;



  
        //获取Gname地址
    GetGNames(baseAddress);

    std::cout << GNames << std::endl;
}

void Cheat::Cache()
{



}



void Cheat::GetGNames(uint64_t baseAddress)
{
    GNames = Decrypt(HV::Read<uint64_t>(baseAddress + SDK::Names));
    GNames = Decrypt(HV::Read<uint64_t>(GNames + SDK::NamesOffset));
   
}
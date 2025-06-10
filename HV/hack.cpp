#include "hack.h"
#include <list>


Cheat::Cheat(UINT64 MainModule, uint64_t baseAddress)
    : m_MainModule(MainModule), m_baseAddress(baseAddress)

{

    //获取基础地址
    InitDecrypt(MainModule, SDK::XenuineDecrypt);
   // uint64_t baseAddress = GetModule(targetProcessId, L"TslGame.exe"); // 获取模块基址
    uint64_t encryptedUWorld = HV::Read<uint64_t>(baseAddress + SDK::GWorld);

    UWorld = Decrypt(encryptedUWorld);

    std::cout << "Uworld : " << UWorld << std::endl;
    CurrentLevel = Decrypt(HV::Read<uint64_t>(UWorld + SDK::CurrentLevel));


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
    OwningActor = Decrypt(HV::Read<uint64_t>(CurrentLevel + SDK::Actors));
    AcknowledgedPawn = Decrypt(HV::Read<uint64_t>(PlayerController + SDK::AcknowledgedPawn));

    Local.Teamid = HV::Read<uint64_t>(AcknowledgedPawn + SDK::LastTeamNum);
    Local.SpectatedCount = HV::Read<uint64_t>(AcknowledgedPawn + SDK::SpectatedCount);
    MaxPacket = HV::Read<int>(OwningActor + 8);
    std::cout << "MAX: " << std::hex << OwningActor << std::endl;

    if (MaxPacket == 0) {
        return;
    }

    OwningActor = HV::Read<uint64_t>(OwningActor);
    std::vector<uint64_t> entitylist;
    entitylist.resize(MaxPacket);
    std::unique_ptr<uint64_t[]> object_raw_ptr = std::make_unique<uint64_t[]>(MaxPacket);
    HV::ReadMemory(OwningActor, reinterpret_cast<ULONG64>(object_raw_ptr.get()), MaxPacket * sizeof(uint64_t));

    for (size_t i = 0; i < MaxPacket; i++)
    {
        entitylist[i] = object_raw_ptr[i];
    }

    std::list<std::shared_ptr<ActorEntity>> actors;

    for (uint64_t address : entitylist)
    {
        uintptr_t actor = address;
        if (actor == AcknowledgedPawn)
            continue;
        if (!actor)
            continue;
        std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor);
        actors.push_back(entity);

    }

    for (std::shared_ptr<ActorEntity> entity : actors)
    {
        if (entity->RootComponent) {
            entity->isCheck = true;
        }
        entity->SetUp1();
    }
    std::vector<std::shared_ptr<ActorEntity>> playerlist;
    for (std::shared_ptr<ActorEntity> entity : actors)
    {
        entity->SetUp2();

    }

    for (std::shared_ptr<ActorEntity> entity : actors)
    {
        int id = Decrypt(entity->id);
        std::string name = GetNamesFromList(id);
        if (name == "") {
            name = GetNames(id);
            Local.KV[id] = name;
            printf("insertName: %s\n", name);
        }


        entity->SetUp3();
        if (entity->Head3D.X == 0 && entity->Head3D.Y == 0 && entity->Head3D.Z)
            continue;
        playerlist.push_back(entity);
    }
    Actors = playerlist;


}



void Cheat::GetGNames(uint64_t baseAddress)
{
    GNames = Decrypt(HV::Read<uint64_t>(baseAddress + SDK::Names));
    GNames = Decrypt(HV::Read<uint64_t>(GNames + SDK::NamesOffset));
   
}

void Cheat::UpdatePlayers()
{
    for (std::shared_ptr<ActorEntity> entity : Actors)
    {

        entity->UpdateBone();
    }
  
    for (std::shared_ptr<ActorEntity> entity : Actors)
    {

        entity->SetUp3();
    }
}

std::vector<std::shared_ptr<ActorEntity>> Cheat::GetActors()
{
    return Actors;
}

CameraCacheEntry Cheat::GetCameraCache()
{
    return  CameraEntry;
}

void Cheat::RefreshViewMatrix()
{
    HV::ReadMemory(PlayerCameraManager + SDK::CameraFov, reinterpret_cast<ULONG64>(&CameraEntry.POV.FOV), sizeof(float));
    HV::ReadMemory(PlayerCameraManager + SDK::CameraPos, reinterpret_cast<ULONG64>(&CameraEntry.POV.Location), sizeof(UEVector));
    HV::ReadMemory(PlayerCameraManager + SDK::CameraRot, reinterpret_cast<ULONG64>(&CameraEntry.POV.Rotation), sizeof(UERotator));

}

uint64_t Cheat::GetActorSize()
{
    return MaxPacket;
}

typedef struct StringA
{
    char buffer[1024];
};
std::string Cheat::GetNames(DWORD ID)
{
    std::string emp = "Unknown";
    if (ID <= 0) return emp;
    uint32_t IdDiv = ID / SDK::ElementsPerChunk;
    uint32_t Idtemp = ID % SDK::ElementsPerChunk;
    uint64_t Serial = HV::Read<uint64_t>(GNames + IdDiv * 0x8);
    if (!Serial || Serial < 0x100000)
        return emp;
    uint64_t pName = HV::Read<uint64_t>(Serial + 0x8 * Idtemp);
    if (!pName || pName < 0x100000)
        return emp;

    StringA names = HV::Read<StringA>(pName + 0x10);
    char te[256];
    memset(&te, 0, 256);
    if (memcmp(names.buffer, te, 256) == 0)
        return emp;

    std::string str(names.buffer);
    return str;
 
}

std::string Cheat::GetNamesFromList(DWORD ID)
{
    return Local.KV[ID];

}

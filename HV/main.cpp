#include "HV.h"

#include <iostream>
#include "Tools.h"
#include "XorStr.h"
#include "offset.h"
UINT64 MainModule;

int main()
{
    printf("[>] Checking presence...\n");
    bool status = HV::CheckPresence();
    if (!status)
    {
        printf("[!] Hypervisor not running\n");
        getchar();
        return EXIT_FAILURE;
    }

    printf("[>] Instructing hypervisor to protect itself...\n");
    status = HV::Protect();
    if (!status)
    {
        printf("[!] Hypervisor self-protection failed\n");
        getchar();
        return EXIT_FAILURE;
    }

    printf("[>] Searching for target process...\n");

    UINT32 targetProcessId = LookupProcessId(L"TslGame.exe");
    UINT32 targetChildProcessId = LookupChildProcessId(L"TslGame.exe");
    if (!targetProcessId)
    {
        printf("[!] Process not found\n");
        getchar();
        return EXIT_FAILURE;
    }

    printf("[+] Process has PID of %u\n", targetProcessId);
    printf("[+] Process targetChildProcessId has PID of %u\n", targetChildProcessId);

    printf("[>] Attaching to process...\n");
    status = HV::AttachToProcess(targetChildProcessId);
    if (!status)
    {
        printf("[!] Failed to attach\n");
        getchar();
        return EXIT_FAILURE;
    }

    printf("[+] Current process: EPROCESS -> 0x%llx CR3 -> 0x%llx\n", HV::Data::CurrentEPROCESS, HV::Data::CurrentDirectoryBase);
    printf("[+] Target process: EPROCESS -> 0x%llx CR3 -> 0x%llx\n", HV::Data::TargetEPROCESS, HV::Data::TargetDirectoryBase);

    printf("[>] Getting module base address...\n");
    MainModule = GetModule(targetProcessId, L"TslGame.exe");
    if (!MainModule)
    {
        printf("[!] Failed to get module base address\n");
        getchar();
        return EXIT_FAILURE;
    }

    printf("[+] Module is at 0x%llx\n", MainModule);

    printf("[>] Reading module header...\n");
    UINT64 header = HV::Read<UINT64>(MainModule);
    if (!header)
    {
        printf("[!] Failed to read header\n");
        getchar();
        return EXIT_FAILURE;
    }

    printf("[+] Header data: 0x%p\n", reinterpret_cast<void*>(header));


    InitDecrypt(MainModule, SDK::XenuineDecrypt);
    uint64_t baseAddress = GetModule(targetProcessId, L"TslGame.exe"); // 获取模块基址
    uint64_t encryptedUWorld = HV::Read<uint64_t>(baseAddress + SDK::GWorld);

    uint64_t UWorld = Decrypt(encryptedUWorld);

    std::cout << "Uworld : " << UWorld << std::endl;



}
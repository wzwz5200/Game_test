#include "XorStr.h"


// 在源文件中定义全局变量
XenuineDecrypts XenuineDecryptFN = nullptr;
uint64_t DecryptKey = 0;

void InitDecrypt(uint64_t base, uint64_t offset)
{ // offset is Decrypt offset
    uint64_t DecryptPtr = HV::Read<uint64_t>(base + offset);
    int Tmp1Add = HV::Read<int>(DecryptPtr + 3);
    DecryptKey = Tmp1Add + DecryptPtr + 7;

    uint8_t CodeBuff[1024] = { 0 };
    CodeBuff[0] = 0x90;
    CodeBuff[1] = 0x90;

    // ��ȡ Decrypt �����ֽ��뵽 CodeBuff[2]
    HV::ReadMemory(DecryptPtr, reinterpret_cast<uint64_t>(CodeBuff + 2), 1024 - 2);

    CodeBuff[2] = 0x48;
    CodeBuff[3] = 0x8B;
    CodeBuff[4] = 0xC1;
    CodeBuff[5] = 0x90;
    CodeBuff[6] = 0x90;
    CodeBuff[7] = 0x90;
    CodeBuff[8] = 0x90;

    XenuineDecryptFN = reinterpret_cast<XenuineDecrypts>(
        VirtualAlloc(NULL, sizeof(CodeBuff), MEM_COMMIT, PAGE_EXECUTE_READWRITE));

    memcpy((LPVOID)XenuineDecryptFN, (LPVOID)CodeBuff, sizeof(CodeBuff));
}


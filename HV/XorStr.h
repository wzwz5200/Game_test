#pragma once

#include <Windows.h>
#include "HV.h"

typedef uint64_t(__fastcall* XenuineDecrypts)(uint64_t, uint64_t);
#define Decrypt(a) XenuineDecryptFN(DecryptKey, a)

extern XenuineDecrypts XenuineDecryptFN;  // ���extern�ؼ���
extern uint64_t DecryptKey;               // ���extern�ؼ���

void InitDecrypt(uint64_t base, uint64_t offset);
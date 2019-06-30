#include <stdint.h>
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <psapi.h>
#include <tchar.h>

#define SOLARIAN_OFFSET 0x7AD170
#define ANTARI_OFFSET 0x7AD178
#define SHINARI_OFFSET 0x7AD180
#define IBERON_OFFSET 0x7AD188
#define KRAHEN_OFFSET 0x7AD190
#define GODAN_OFFSET 0x7AD198
#define CHEBLON_OFFSET 0x7AD1A0
#define TOLUEN_OFFSET 0x7AD1A8

/* 32-bit and 64-bit check to keep MEM size same as LPVOID. */
#ifdef _WIN64
    // 64-bit Windows
    #define MEM uint64_t
#else
    // 32-bit Windows
    #define MEM uint32_t
#endif

int main() {
    LPVOID address;
    double money = 10000000;
    double value = 0;
    MEM myrace = SOLARIAN_OFFSET;
    int stat = 1;

    HWND hWnd = FindWindowA(0, "Imperium Galactica II");
    if (hWnd == 0) {
        printf("Could not find window.\n");
    } else {
    	TCHAR szProcessName[MAX_PATH];
        DWORD PID;
        GetWindowThreadProcessId(hWnd, &PID);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, PID);

        HMODULE hMod;
        DWORD cbNeeded;

        // Since the game runs in 32-bit mode even on 64-bit Windows, there is no need to check in 64-bit modules
        // if (EnumProcessModulesEx(hProc, &hMod, sizeof(hMod), &cbNeeded, LIST_MODULES_32BIT | LIST_MODULES_64BIT)) {
        if (EnumProcessModulesEx(hProc, &hMod, sizeof(hMod), &cbNeeded, LIST_MODULES_32BIT)) {
            	GetModuleBaseName(hProc, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
                MEM baseaddress = (MEM)hMod;
                printf("BASE: %p\n", baseaddress);
                MEM result = baseaddress + myrace;
                address = (LPVOID)result;
                printf("RESULT: %p\n", address);
        }

        if(!hProc) {
            printf("Cannot open process.\n");
        } else {
            while (1) {
                int stat = WriteProcessMemory(hProc, (LPVOID)address, &money, (DWORD)sizeof(money), NULL);
                // ReadProcessMemory(hProc, (void*)address, &value, sizeof(value), 0);

                if(stat > 0){
                    printf("Memory written to process.\n");
                } else {
                    printf("Memory couldn't be written to process.\n");
                }

                sleep(0.1);
            }

            CloseHandle(hProc);
        }
    }
    return 0;
}

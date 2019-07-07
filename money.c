#include <stdint.h>
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <psapi.h>
#include <tchar.h>
#include "offsets.h"


static HANDLE hProc;
static MEM BASE_ADDRESS;


int freeze_money(int race, double value) {
    LPVOID address = (LPVOID)(BASE_ADDRESS + MONEY_OFFSETS[race]);
    while (1) {
        int stat = WriteProcessMemory(hProc, (LPVOID)address, &value, (DWORD)sizeof(value), NULL);

        if(stat > 0){
            printf("Memory written to process.\n");
        } else {
            printf("Memory couldn't be written to process.\n");
        }

        sleep(0.1);
    }
}


int get_current_race() {
    int race;
    LPVOID address = (LPVOID)(BASE_ADDRESS + CURRENT_RACE_OFFSET);
    ReadProcessMemory(hProc, (void*)address, &race, sizeof(race), 0);
    return race;
}


int change_current_race(int race) {
    LPVOID address = (LPVOID)(BASE_ADDRESS + CURRENT_RACE_OFFSET);
    int stat = WriteProcessMemory(hProc, (LPVOID)address, &race, (DWORD)sizeof(race), NULL);
    return stat;
}


int main() {
    LPVOID address;

    TCHAR szProcessName[MAX_PATH];
    DWORD PID;
    HMODULE hMod;
    DWORD cbNeeded;

    HWND hWnd = FindWindowA(0, "Imperium Galactica II");
    if (!hWnd) {
        printf("Could not find Imperium Galactica II window.\n");
        return 1;
    }

    GetWindowThreadProcessId(hWnd, &PID);
    hProc = OpenProcess(PROCESS_ALL_ACCESS, 1, PID);
    // Since the game runs in 32-bit mode even on 64-bit Windows,
    // there is no need to check in 64-bit modules
    if (EnumProcessModulesEx(hProc, &hMod, sizeof(hMod), &cbNeeded, LIST_MODULES_32BIT)) {
        GetModuleBaseName(hProc, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
        BASE_ADDRESS = (MEM)hMod;
    }

    if (!hProc) {
        printf("Cannot open process.\n");
        return 1;
    }

    printf("BASE_ADDRESS: %p\n", BASE_ADDRESS);

    int race = get_current_race();
    printf("%d\n", race);

    change_current_race(1);

    // freeze_money(GAIA, 100);

    CloseHandle(hProc);
    return 0;
}

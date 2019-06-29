#include <stdint.h>
#include <stdio.h>
#include <windows.h>
#include <unistd.h>

/* 32-bit and 64-bit check to keep MEM size same as LPVOID. */
#ifdef _WIN64
    // 64-bit Windows
    #define MEM uint64_t
#else
    // 32-bit Windows
    #define MEM uint32_t
#endif


int main() {
    MEM baseaddress = 0x11D0000;
    MEM solarian_offset = 0x7AD170;
    MEM result = baseaddress + solarian_offset;
    LPVOID address = (LPVOID)result;
    printf("%p\n", address);

    double nVal = 0;
    double value = 0;
    int stat = 1;

    HWND hWnd = FindWindowA(0, "Imperium Galactica II");
    if(hWnd == 0){
        printf("Could not find window.\n");
    } else {
        DWORD PID;
        GetWindowThreadProcessId(hWnd, &PID);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, PID);

        if(!hProc) {
            printf("Cannot open process.\n");
        } else {
            while (1) {
                int stat = WriteProcessMemory(hProc, (LPVOID)address, &nVal, (DWORD)sizeof(nVal), NULL);
                // ReadProcessMemory(hProc, (void*)0x01B0D170, &value, sizeof(value), 0);

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

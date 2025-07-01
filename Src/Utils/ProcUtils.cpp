//
// Created by alteik on 01.07.2025.
//

#include "ProcUtils.hpp"
#include <tlhelp32.h>

int ProcUtils::getMinecraftPID()
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    process.dwSize = sizeof(process);

    if (Process32First(snapshot, &process))
    {
        do
        {
            if (strcmp(process.szExeFile, "Minecraft.Windows.exe") == 0)
            {
                CloseHandle(snapshot);
                return process.th32ProcessID;
            }
        }
        while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);
    return 0;
}

int ProcUtils::getModulesCount(DWORD pID)
{
    HANDLE moduleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
    if (moduleSnap == INVALID_HANDLE_VALUE) return 0;

    MODULEENTRY32 me32;
    me32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(moduleSnap, &me32))
    {
        CloseHandle(moduleSnap);
        return 0;
    }

    int count = 1;
    while (Module32Next(moduleSnap, &me32)) count++;

    CloseHandle(moduleSnap);
    return count;
}
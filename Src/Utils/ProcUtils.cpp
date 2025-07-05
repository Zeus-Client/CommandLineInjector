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
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);

    MODULEENTRY32 module;
    module.dwSize = sizeof(module);

    int count = 0;
    if (Module32First(snapshot, &module))
    {
        do { ++count; }
        while (Module32Next(snapshot, &module));
    }

    CloseHandle(snapshot);
    return count;
}
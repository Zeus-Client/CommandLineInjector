//
// Created by alteik on 01.07.2025.
//

#pragma once

#include <windows.h>

class ProcUtils
{
public:
    static int getMinecraftPID();
    static int getModulesCount(DWORD pID);
};
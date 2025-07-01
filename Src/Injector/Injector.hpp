//
// Created by alteik on 01.07.2025.
//

#pragma once

#include <iostream>
#include <Windows.h>

class Injector
{
public:
    static void applyAppPackages(const std::string& dllPath);
    static void inject(const std::string& dllPath, DWORD pID);
};
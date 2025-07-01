//
// Created by alteik on 01.07.2025.
//

#include "Injector.hpp"

#include <TlHelp32.h>
#include <filesystem>
#include <print>

void Injector::applyAppPackages(const std::string& dllPath)
{
    if (GetFileAttributesA(dllPath.c_str()) != FILE_ATTRIBUTE_NORMAL) SetFileAttributesA(dllPath.c_str(), FILE_ATTRIBUTE_NORMAL);
}

void Injector::inject(const std::string& dllPath, const DWORD pID)
{
    applyAppPackages(dllPath);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pID);

    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    auto pLoadLibraryA = static_cast<LPVOID>(GetProcAddress(hKernel32, "LoadLibraryA"));

    LPVOID pDllPath = VirtualAllocEx(
        hProcess,
        nullptr,
        dllPath.length() + 1,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
    );

    SIZE_T bytesWritten;
    WriteProcessMemory(
        hProcess,
        pDllPath,
        dllPath.c_str(),
        dllPath.length() + 1,
        &bytesWritten
    );

    HANDLE hThread = CreateRemoteThread(
        hProcess,
        nullptr,
        0,
        static_cast<LPTHREAD_START_ROUTINE>(pLoadLibraryA),
        pDllPath,
        0,
        nullptr
    );

    WaitForSingleObject(hThread, INFINITE);

    DWORD exitCode = 0;
    GetExitCodeThread(hThread, &exitCode);
    std::println("DLL injected. Handle: 0x{:X}", static_cast<uintptr_t>(exitCode));
}
//
// Created by alteik on 01.07.2025.
//

#include <filesystem>
#include <print>

#include <Src/Utils/ProcUtils.hpp>
#include <Src/Injector/Injector.hpp>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::println("Please pass dll path as program start argument!");
        return -1;
    }

    std::string dllPath = argv[1];

    if (!std::filesystem::exists(dllPath) || std::filesystem::is_directory(dllPath))
    {
        std::println("Invalid file path!");
        return -2;
    }

    int pID = ProcUtils::getMinecraftPID();
    if (pID == NULL)
    {
        std::println("No Minecraft found! Starting Minecraft...");
        system("start minecraft:");

        Sleep(500);

        pID = ProcUtils::getMinecraftPID();
        if (pID == NULL)
        {
            std::println("Something has gone horribly wrong, aborting.");
            return -3;
        }
    }

    std::println("Found Minecraft! pID: {}", pID);
    std::println("Waiting for Minecraft to load...");

    while (ProcUtils::getModulesCount(pID) <= 140) { Sleep(10); }

    std::println("Minecraft loaded! Injecting DLL...");

    Injector::inject(dllPath, pID);

    return 0;
}
// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <TlHelp32.h>
#include <Windows.h>
#include "mem.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}


class weaponClass
{
public:
    union {
        //               Type     Name   Offset
        DEFINE_MEMBER_N(int, currentWeaponPointer, 0x0004);
        DEFINE_MEMBER_N(int*, currentAmmoPointer, 0x0014);
    };
};

class Entity
{
public:
    union
    {
        //               Type     Name   Offset
        //DEFINE_MEMBER_N(Vector3, posHead, 0x4);
        //DEFINE_MEMBER_N(Vector3, posPlayer, 0x0034);
        //DEFINE_MEMBER_N(Vector3, viewAngle, 0x0040);
        DEFINE_MEMBER_N(int, playerHealth, 0x00F8);
        DEFINE_MEMBER_N(int, playerArmor, 0x00FC);
        DEFINE_MEMBER_N(int, playerSpeed, 0x0080);
        DEFINE_MEMBER_N(int, playerGrenades, 0x0158);
        DEFINE_MEMBER_N(weaponClass*, weaponPointer, 0x0374);
    };
};

DWORD WINAPI HackThread(HMODULE hModule)
{
    // Create a console window
    AllocConsole();
    
    // Open a new file stream inside of the target process
    FILE* tempFile{ 0 };
    freopen_s(&tempFile, "CONOUT$", "w", stdout);
    std::cout << "The console has been successfully attached.\n";

    // Get the module base address
    uintptr_t moduleBaseAddress{ (uintptr_t)(GetModuleHandle(L"ac_client.exe")) };
    std::cout << "The module base address was located at: " << moduleBaseAddress << "\n";

    // Define variables for toggles, false because they are set to off by default
    bool bHealth{ false };
    bool bAmmo{ false };
    bool bNoRecoil{ false };
    bool bSpeed{ false };
    
    // Main program loop, will run intil END is pressed or until the user closes the program
    while (true)
    {
        // Takes in key input from the user
        if (GetAsyncKeyState(VK_END) & 1)
        {
            std::cout << "DLL has been ejected.\n";
            break;
        }

        // Max Health & Armor + Invincibility toggle
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bHealth = !bHealth;

            if (bHealth)
            {
                std::cout << "MAX STATS + INVINCIBILITY has been toggled ON.\n";
            }
            else
            {
                std::cout << "MAX STATS + INVINCIBILITY has been toggled OFF.\n";
            }
        }

        // Infinite Ammo toggle
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bAmmo = !bAmmo;

            if (bAmmo)
            {
                std::cout << "INFINITE AMMO has been toggled ON.\n";
            }
            else
            {
                std::cout << "INFINITE AMMO has been toggled OFF.\n";
            }
        }

        // Infinite Ammo toggle
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bNoRecoil = !bNoRecoil;

            if (bNoRecoil)
            {
                // Goes to the address of the recoil function and patches the bytes with 0x90 NOP instructions
                Nop((BYTE*)(moduleBaseAddress + 0x63786), 10);
                std::cout << "NO RECOIL has been toggled ON.\n";
            }
            else
            {
                // Writes back the original recoil function when toggled off
                Patch((BYTE*)(moduleBaseAddress + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
                std::cout << "NO RECOIL has been toggled OFF.\n";
            }
        }

        // Player speed x 2 toggle
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            bSpeed = !bSpeed;

            if (bSpeed)
            {
                std::cout << "DOUBLE SPEED has been toggled ON.\n";
            }
            else
            {
                std::cout << "DOUBLE SPEED has been toggled OFF.\n";
            }
        }

        // Stores a pointer to the local player object
        Entity* localPlayer{ *(Entity**)(moduleBaseAddress + 0x10F4F4) };
        uintptr_t* localPlayerPtr{ (uintptr_t*)(moduleBaseAddress + 0x10F4F4) };

        // If the player object point exists...
        if (localPlayer)
        {
            // If toggled on, continously write player object health and armor
            if (bHealth)
            {
                localPlayer->playerHealth = 100;
                localPlayer->playerArmor = 100;
            }

            // If toggled on, continously write current weapon ammo and grenades
            if (bAmmo)
            {
                localPlayer->playerGrenades = 5;

                // Value for grenades within currentWeaponPointer
                uintptr_t grenade{ 0x8 };

                // If the player is not holding a grenade...
                if (localPlayer->weaponPointer->currentWeaponPointer != grenade)
                {
                    *localPlayer->weaponPointer->currentAmmoPointer = 20;
                }
                else // If the player is holding a grenade...
                {
                    *localPlayer->weaponPointer->currentAmmoPointer = 5;
                }
            }

            // If toggled on, player speed is doubled
            // BUGGED: Sometimes forward movement "sticks" and will need an addition keystroke to stop the player
            // BUGGED: Seems to happen only with the following combo: Hold W, Hold D, Release W, Release D
            // BUGGED: While infinite ammo is toggled on, ammo will decrease while player is strafing
            if (bSpeed)
            {
                while (GetKeyState('W') & 0x8000)
                {
                    localPlayer->playerSpeed = (0x0000'0002);
                    while (GetKeyState('W') == 0)
                    {
                        localPlayer->playerSpeed = 0;
                        break;
                    }

                   while (GetKeyState('A') & 0x8000)
                    {
                        localPlayer->playerSpeed = (0x0000'0002 + 0x0000'0200);
                        if ((GetKeyState('W') == 0) || (GetKeyState('A') == 0))
                        {
                            localPlayer->playerSpeed = 0;
                            break;
                        }
                    }

                   while (GetKeyState('D') & 0x8000)
                   {
                       localPlayer->playerSpeed = (0x0000'0002 + 0x0000'FE00);
                       if ((GetKeyState('W') == 0) || (GetKeyState('D') == 0))
                       {
                           localPlayer->playerSpeed = 0;
                           break;
                       }
                   }
                    break;
                }


                while (GetKeyState('A') & 0x8000)
                {
                    localPlayer->playerSpeed = (0x0000'0200);
                    if (GetKeyState('A') == 0)
                    {
                        localPlayer->playerSpeed = 0;
                        break;
                    }
                }

                while (GetKeyState('D') & 0x8000)
                {
                    localPlayer->playerSpeed = (0x0000'FE00);
                    if (GetKeyState('D') == 0)
                    {
                        localPlayer->playerSpeed = 0;
                        break;
                    }
                }

                while (GetKeyState('S') & 0x8000)
                {
                    localPlayer->playerSpeed = (0x0000'00FE);
                    if (GetKeyState('S') == 0)
                    {
                        localPlayer->playerSpeed = 0;
                        break;
                    }
                }
            }
        }
        // Sleep for 5ms for performance purposes
        Sleep(5);
    }
    // Clean-up and Eject DLL
    fclose(tempFile);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        // Create a thread when the .DLL gets loaded
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr);

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        CloseHandle(hModule);
        break;
    }
    return TRUE;
}


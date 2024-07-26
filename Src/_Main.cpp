#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "gd.h" 
using namespace cocos2d;
using namespace cocos2d::extension;

#include <glob/glob.h>

int ModsLoaded = 0;
std::string ModsLoadedList = "";
bool afterLoad = false;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;

    if (GetKeyState(VK_CONTROL) & 0x8000) ModUtils::OpenConsole();

    ModUtils::log("Crawling...", 1);

    for (auto& entry : glob::glob({ "*.dll", "**/*.dll" })) {

        std::string loadit = "true";

        if (strstr(entry.string().c_str(), "geode")) loadit = "path contins geode/unzipped";
        if (strstr(entry.string().c_str(), "minhook")) loadit = "path contins minhook";
        if (strstr(entry.string().c_str(), "MinHook")) loadit = "path contins MinHook";
        if (strstr(entry.string().c_str(), "websockets.dll")) loadit = "path contins websockets.dll";
        if (strstr(entry.string().c_str(), "msvcp")) loadit = "path contins msvcp";
        if (strstr(entry.string().c_str(), "msvcr")) loadit = "path contins msvcr";
        if (GetModuleHandleA(entry.filename().string().c_str())) loadit = "already loaded";

        if (loadit == "true") {
            HMODULE hModule = LoadLibrary(entry.string().c_str());
            if (!hModule) ModUtils::log("Failed to load library \"" + entry.string() + "\" .", 1);
            else {
                ModUtils::log(" Loaded library \"" + entry.string() + "\"!", 1);
                ++ModsLoaded;
                ModsLoadedList = ModsLoadedList + ((ModsLoadedList == "" ? "" : ", ") + entry.filename().string());
            }
        }
        else    ModUtils::log("Skipped library \"" + entry.string() + "\": " + loadit, 1);
    }

    ModUtils::log("Loading libs reached end!", 1);

    return TRUE;
}

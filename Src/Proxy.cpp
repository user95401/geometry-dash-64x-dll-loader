#pragma comment(linker, "/EXPORT:XInputGetState=XInputGetState,@2")

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

    HINSTANCE s_instance = NULL;
    struct XINPUT_STATE {};
    struct XINPUT_CAPABILITIES {};

    typedef DWORD(WINAPI* f_XInputGetState)(DWORD, XINPUT_STATE*);
    f_XInputGetState s_XInputGetState = NULL;

    typedef DWORD(WINAPI* f_XInputGetCapabilities)(DWORD, DWORD, XINPUT_CAPABILITIES*);
    f_XInputGetCapabilities s_XInputGetCapabilities = NULL;

    void load()
    {
        WCHAR path[MAX_PATH];
        GetSystemDirectoryW(path, MAX_PATH);
        wcscat_s(path, L"\\XInput1_4.dll");
        s_instance = LoadLibraryW(path);

        if (!s_instance)
            return;

        s_XInputGetState = (f_XInputGetState)(GetProcAddress(s_instance, "XInputGetState"));
        s_XInputGetCapabilities = (f_XInputGetCapabilities)(GetProcAddress(s_instance, "XInputGetCapabilities"));
    }

    __declspec(dllexport)
        DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
    {
        if (!s_XInputGetState)
            load();

        return s_XInputGetState(dwUserIndex, pState);
    }

    __declspec(dllexport)
        DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
    {
        if (!s_XInputGetCapabilities)
            load();

        return s_XInputGetCapabilities(dwUserIndex, dwFlags, pCapabilities);
    }

#ifdef __cplusplus
}
#endif

#ifndef __COMMON_H__
#define __COMMON_H__

#define WINVER 0x0600       /* Windows Vista */
#define _WIN32_WINNT 0x0600 /* Windows Vista */
#include <windows.h>

static ULONGLONG time_now_milliseconds()
{
    return GetTickCount64();
}

static int lctrl_pressed()
{
    return 0x8000 & GetKeyState(VK_LCONTROL);
}

static int rctrl_pressed()
{
    return 0x8000 & GetKeyState(VK_RCONTROL);
}

static int ctrl_pressed()
{
    return lctrl_pressed() || rctrl_pressed();
}

static int lshift_pressed()
{
    return 0x8000 & GetKeyState(VK_LSHIFT);
}

static int rshift_pressed()
{
    return 0x8000 & GetKeyState(VK_RSHIFT);
}

static int shift_pressed()
{
    return lshift_pressed() || rshift_pressed();
}

static int lalt_pressed()
{
    return 0x8000 & GetKeyState(VK_LMENU);
}

static int ralt_pressed()
{
    return 0x8000 & GetKeyState(VK_RMENU);
}

static int alt_pressed()
{
    return lalt_pressed() || ralt_pressed();
}

static DWORD scancode_flags(WORD vkCode)
{
    double dwFlags;
    {
        if (vkCode == VK_LWIN
            || vkCode == VK_RWIN
            || vkCode == VK_APPS
            || vkCode == VK_RCONTROL
            || vkCode == VK_RMENU
            || vkCode == VK_LEFT
            || vkCode == VK_DOWN
            || vkCode == VK_UP
            || vkCode == VK_RIGHT
            || vkCode == VK_NEXT
            || vkCode == VK_PRIOR)
            dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_EXTENDEDKEY;
        else
            dwFlags = KEYEVENTF_SCANCODE;
    }
    return dwFlags;
}

ULONG_PTR naive_hash(char* s)
{
    ULONG_PTR x = 0x4230943225432809;
    {
        while (*s)
            x = 3 * x + *(s++);
    }
    return x;
}

static void press(WORD vkCode, ULONG_PTR dwExtraInfo)
{
    INPUT input;
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = 0;
        input.ki.wScan = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
        input.ki.dwFlags = scancode_flags(vkCode);
        input.ki.time = 0;
        input.ki.dwExtraInfo = dwExtraInfo;
    }
    SendInput(1, &input, sizeof(INPUT));
}

static void release(WORD vkCode, ULONG_PTR dwExtraInfo)
{
    INPUT input;
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = 0;
        input.ki.wScan = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
        input.ki.dwFlags = scancode_flags(vkCode) | KEYEVENTF_KEYUP;
        input.ki.time = 0;
        input.ki.dwExtraInfo = dwExtraInfo;
    }
    SendInput(1, &input, sizeof(INPUT));
}

#endif

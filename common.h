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

static int lwin_pressed()
{
    return 0x8000 & GetKeyState(VK_LWIN);
}

static int rwin_pressed()
{
    return 0x8000 & GetKeyState(VK_RWIN);
}

static int win_pressed()
{
    return lwin_pressed() || rwin_pressed();
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

static const int KEY_TYPE[256] = {
    0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0,
    1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    1, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 1, 2, 2, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 0, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
    0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1
};

static void press(WORD vkCode, ULONG_PTR dwExtraInfo)
{
    DWORD dwFlags;

    if (KEY_TYPE[vkCode] == 1)
        dwFlags = KEYEVENTF_SCANCODE;
    else if (KEY_TYPE[vkCode] == 2)
        dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_EXTENDEDKEY;
    else
        return;

    INPUT input;
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = 0;
        input.ki.wScan = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
        input.ki.dwFlags = dwFlags;
        input.ki.time = 0;
        input.ki.dwExtraInfo = dwExtraInfo;
    }
    SendInput(1, &input, sizeof(INPUT));
}

static void release(WORD vkCode, ULONG_PTR dwExtraInfo)
{
    DWORD dwFlags;

    if (KEY_TYPE[vkCode] == 1)
        dwFlags = KEYEVENTF_SCANCODE;
    else if (KEY_TYPE[vkCode] == 2)
        dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_EXTENDEDKEY;
    else
        return;

    INPUT input;
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = 0;
        input.ki.wScan = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
        input.ki.dwFlags = dwFlags | KEYEVENTF_KEYUP;
        input.ki.time = 0;
        input.ki.dwExtraInfo = dwExtraInfo;
    }
    SendInput(1, &input, sizeof(INPUT));
}

#endif

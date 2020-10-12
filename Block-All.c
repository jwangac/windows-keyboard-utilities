#include "common.h"

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    return 1;
}

int main(void)
{
    CreateMutexA(NULL, FALSE, "WKU_" __FILE__ "_INSTANCE");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
        return 1;

    SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);

    MSG msg;
    GetMessage(&msg, NULL, 0, 0);
}

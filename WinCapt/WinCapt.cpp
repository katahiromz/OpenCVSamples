#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

int g_width;
int g_height;
double g_fps;
cv::VideoCapture g_cap(0);
cv::Mat g_frame;
BITMAPINFO g_bi =
{
    {
        sizeof(BITMAPINFOHEADER), 0, 0, 1
    }
};
CRITICAL_SECTION g_lock;

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    assert(g_cap.isOpened());

    g_cap >> g_frame;
    g_width = g_frame.cols;
    g_height = g_frame.rows;
    g_fps = 5;

    g_bi.bmiHeader.biWidth = g_width;
    g_bi.bmiHeader.biHeight = -g_height;
    g_bi.bmiHeader.biBitCount = 24;
    g_bi.bmiHeader.biCompression = BI_RGB;

    InitializeCriticalSection(&g_lock);

    SetTimer(hwnd, 999, DWORD(1000 / g_fps), NULL);

    return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
    case IDCANCEL:
        KillTimer(hwnd, 999);
        DeleteCriticalSection(&g_lock);

        EndDialog(hwnd, id);
        break;
    }
}

void OnTimer(HWND hwnd, UINT id)
{
    EnterCriticalSection(&g_lock);
    g_cap >> g_frame;
    LeaveCriticalSection(&g_lock);

    InvalidateRect(hwnd, NULL, TRUE);
}

void OnPaint(HWND hwnd)
{
    RECT rc;
    GetClientRect(hwnd, &rc);

    PAINTSTRUCT ps;
    if (HDC hdc = BeginPaint(hwnd, &ps))
    {
        SetStretchBltMode(hdc, COLORONCOLOR);

        EnterCriticalSection(&g_lock);
        StretchDIBits(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                      0, 0, g_width, g_height,
                      g_frame.data, &g_bi, DIB_RGB_COLORS, SRCCOPY);
        LeaveCriticalSection(&g_lock);

        EndPaint(hwnd, &ps);
    }
}

BOOL OnEraseBkgnd(HWND hwnd, HDC hdc)
{
    return TRUE;
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hwnd, WM_TIMER, OnTimer);
        HANDLE_MSG(hwnd, WM_ERASEBKGND, OnEraseBkgnd);
        HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    InitCommonControls();
    DialogBox(hInstance, MAKEINTRESOURCE(100), NULL, DialogProc);
    return 0;
}

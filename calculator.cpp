#include <windows.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <tchar.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4
#define ADD 5
#define MINUS 6
#define MULTIPLY 7
#define DIVIND 8

using namespace std;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void addMenus(HWND);
void addControls(HWND);
void calculateResult(HWND, wchar_t*, wchar_t*, int);
void showResult(HWND, wchar_t);

HMENU hMenu;
HWND hNum1;
HWND hNum2;




int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+25);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;



    CreateWindowW(L"myWindowClass", L"MY Calculator",
                  WS_VISIBLE | WS_SYSMENU,
                  100, 100, 250, 200,
                  NULL, NULL, NULL, NULL);




    MSG msg = {0};

    while(GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {

    case WM_COMMAND:

        switch(wp)
        {
        case FILE_MENU_EXIT:
            DestroyWindow(hWnd);

            break;

        case FILE_MENU_NEW:

            MessageBeep(MB_ICONINFORMATION);

            break;
        case CHANGE_TITLE:
            wchar_t text[100];
            GetWindowTextW(hNum1, text, 100);
            SetWindowTextW(hWnd, text);

            break;

        case ADD:
            wchar_t ADDnum1[100];
            wchar_t ADDnum2[100];
            GetWindowTextW(hNum1, ADDnum1, 100);
            GetWindowTextW(hNum2, ADDnum2, 100);

            calculateResult(hWnd, ADDnum1, ADDnum2, ADD);
            break;

        case MINUS:
            wchar_t MINUSnum1[100];
            wchar_t MINUSnum2[100];
            GetWindowTextW(hNum1, MINUSnum1, 100);
            GetWindowTextW(hNum2, MINUSnum2, 100);

            calculateResult(hWnd, MINUSnum1, MINUSnum2, MINUS);
            break;

        case MULTIPLY:
            wchar_t MULTIPLYnum1[100];
            wchar_t MULTIPLYnum2[100];
            GetWindowTextW(hNum1, MULTIPLYnum1, 100);
            GetWindowTextW(hNum2, MULTIPLYnum2, 100);

            calculateResult(hWnd, MULTIPLYnum1, MULTIPLYnum2, MULTIPLY);
            break;

        case DIVIND:
            wchar_t DIVINDnum1[100];
            wchar_t DIVINDnum2[100];
            GetWindowTextW(hNum1, DIVINDnum1, 100);
            GetWindowTextW(hNum2, DIVINDnum2, 100);

            calculateResult(hWnd, DIVINDnum1, DIVINDnum2, DIVIND);
            break;
        }
        break;

    case WM_CREATE:
        addMenus(hWnd);
        addControls(hWnd);


        break;



    case WM_DESTROY:

        PostQuitMessage(0);

        break;

    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void addMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, CHANGE_TITLE, "SubMenu Item");


    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR) hSubMenu, "Open SubMenu");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");


    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFileMenu, "File");

    AppendMenu(hMenu, MF_STRING, ADD, "Help");

    SetMenu(hWnd, hMenu);
}

void addControls(HWND hWnd)
{
    CreateWindowW(L"static", L"Enter First Number :",
                    WS_VISIBLE | WS_CHILD,
                    10, 10, 140, 20,
                    hWnd, NULL, NULL, NULL);

    hNum1 = CreateWindowW(L"edit", L"",
                    WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL,
                    10, 30, 200, 20,
                    hWnd, NULL, NULL, NULL);

    CreateWindowW(L"static", L"Enter Second Number :",
                    WS_VISIBLE | WS_CHILD,
                    10, 50, 160, 20,
                    hWnd, NULL, NULL, NULL);

    hNum2 = CreateWindowW(L"edit", L"",
                    WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL,
                    10, 70, 200, 20,
                    hWnd, NULL, NULL, NULL);

    CreateWindowW(L"button", L"+",
                    WS_VISIBLE | WS_CHILD,
                    12.5, 100, 20, 20,
                    hWnd, (HMENU)ADD, NULL, NULL);

    CreateWindowW(L"button", L"-",
                    WS_VISIBLE | WS_CHILD,
                    75, 100, 20, 20,
                    hWnd, (HMENU)MINUS, NULL, NULL);

    CreateWindowW(L"button", L"*",
                    WS_VISIBLE | WS_CHILD,
                    137.5, 100, 20, 20,
                    hWnd, (HMENU)MULTIPLY, NULL, NULL);

    CreateWindowW(L"button", L"/",
                    WS_VISIBLE | WS_CHILD,
                    200, 100, 20, 20,
                    hWnd, (HMENU)DIVIND, NULL, NULL);
}

void showResult(HWND hWnd,wchar_t *wResult)
{
    MessageBoxW(hWnd, wResult, L"Result", MB_OK);

}

void calculateResult(HWND hWnd, wchar_t *num1, wchar_t *num2, int Operator) {
    double fN1, fN2, sum = 0;
    cout << endl << swscanf(num1, L"%lf", &fN1);
    cout << endl << swscanf(num2, L"%lf", &fN2);
    cout << fN1 << " " << fN2 << "\n";

    switch (Operator) {
        case ADD:
            sum = fN1 + fN2;
            break;
        case MINUS:
            sum = fN1 - fN2;
            break;
        case MULTIPLY:
            sum = fN1 * fN2;
            break;
        case DIVIND:
            if (fN2 != 0)
                sum = fN1 / fN2;
            else {
                MessageBoxW(hWnd, L"Cannot divide by zero!", L"Error", MB_OK);
                return;
            }
            break;
    }


    wchar_t wResult[100];
    swprintf(wResult, L"Result = %.2f", sum);

    showResult(hWnd, wResult);
}






#include <iostream>
#include <Windows.h>

/*
    This program will reposition the targeted window to [x=0, y=0]. This is useful if the window
    is "stuck" off-screen (e.g. if you've unplugged an external monitor and the desktop didn't adjust
    for some reason). Sometimes it is annoying if you are forced to close & re-open the application.
    
    LT, 2023
*/
int main()
{
    HWND HWin;
    RECT lpRect;
    LONG x = 0;
    LONG y = 0;
    LONG r = 0;
    LONG b = 0;

    HWND my_console_win;
    my_console_win = GetConsoleWindow();
    HWin = NULL;
    bool finished = false;

    std::cout << "Focus the target window that you want to reposition now (e.g. select it from the task bar)...";

    while (!finished)
    {
        HWND temp_win;
        
        temp_win = GetForegroundWindow();
        
        if (temp_win != my_console_win && HWin != temp_win && temp_win !=NULL)
        {
            HWin = temp_win;
            LPSTR title = new char[1000]; // Old school & vulnerable to buffer overruns, but who in this case who cares?
            BOOL got_wnd_info = GetWindowTextA(HWin, title, 1000);
            std::cout << "Captured \"" << title << "\".\n";

            lpRect = {};
            GetWindowRect(HWin, &lpRect);

            x = lpRect.left;
            y = lpRect.top;
            r = lpRect.right;
            b = lpRect.bottom;

            std::cout << "Coordinates of the captured window: (" << x << "," << y << "," << r << "," << b << ").\n";
            std::cout << "Now come back here and re-focus the console.\n";
        }
        else if(temp_win == my_console_win && HWin != NULL)
        {
            std::cout << "Repositioning the target window now!\n";
            EnableWindow(HWin, true);

            LONG new_x = 0;
            LONG new_y = 0;
            LONG new_r = r - x;
            LONG new_b = b - y;

            BOOL result = SetWindowPos(HWin, NULL, new_x, new_y, new_r, new_b, SWP_SHOWWINDOW);

            ShowWindow(HWin, 5);
            if (result)
            {
                std::cout << "Repositioned the target window successfully to (" << new_x << "," << new_y << "," << new_r << "," << new_b << ").\n";
            }
            else
            {
                std::cout << "Failed to reposition the target window!\n";
            }
            finished = true;
        }
        Sleep(100);
    }
    
    std::cin.ignore();
}
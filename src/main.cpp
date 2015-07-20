#include "Game.h"
#include "GameStateSplash.h"

#include <windows.h>

int main() {
    av::Game game;

#if _DEBUG
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOW);
#else
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
#endif
    game.pushState(new av::GameStateSplash(game));
    game.run();

#if _DEBUG
    system("PAUSE");
#endif

    return 0;
}
#include "win_fonksiyon.h"
#include <iostream>
#include <windows.h>
using namespace std;




void gotoxy(int x, int y) // cursör pozisyonu deðistirmek
{
    COORD kordinat;
    kordinat.X = x;
    kordinat.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kordinat);
}

void kursor_gizle() //
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO  cursor_info;

    GetConsoleCursorInfo(out, &cursor_info);
    cursor_info.bVisible = false;
    SetConsoleCursorInfo(out, &cursor_info);
}


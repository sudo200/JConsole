#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "at_sudo200_JConsole_JConsole.h"

#define CONSOLE_MODE_ON   1
#define CONSOLE_MODE_OFF  0

#define XMAX                          80
#define YMAX                          25

void textcolor(int);

static int __BACKGROUND = 0;
static int __FOREGROUND = 0x7;
static int cmode;

JNIEXPORT void JNICALL Java_at_sudo200_JConsole_JConsole_initConsole(JNIEnv *env, jclass c)
{
        system("mode CON: COLS=80 LINES=25");
        textcolor(at_sudo200_JConsole_JConsole_WHITE);
        cmode = CONSOLE_MODE_ON;

}

void gotoxy(int xpos, int ypos)
{
    COORD Screenpos;

            if ( 0 <= xpos && xpos < XMAX &&
                 0 <= ypos && ypos < YMAX     )
            {
               Screenpos.X = xpos;
               Screenpos.Y = ypos;
               SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Screenpos);
            }
}

JNIEXPORT void JNICALL Java_at_sudo200_JConsole_JConsole_gotoxy(JNIEnv *env, jclass c, jint xpos, jint ypos)
{
    gotoxy(xpos, ypos);
}

JNIEXPORT void JNICALL Java_at_sudo200_JConsole_JConsole_delay(JNIEnv *env, jclass c, jint msec)
{
    long start = clock();
    long dauer = msec * (CLOCKS_PER_SEC / 1000);
    long ende = start + dauer;
    while( clock() < ende );
}

void clrscr()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    char color =  __FOREGROUND + (__BACKGROUND << 4);
    int anzahl = XMAX * YMAX;
    COORD Startpos = {0,0};
    DWORD ergebnis;

    FillConsoleOutputAttribute( h, color, anzahl, Startpos, &ergebnis);
    FillConsoleOutputCharacter( h,  ' ' , anzahl, Startpos, &ergebnis);
}

JNIEXPORT void JNICALL Java_at_sudo200_JConsole_JConsole_clrscr(JNIEnv *env, jclass c)
{
    clrscr();
}

void textcolor (int c)
{
int color = 0;

    switch(c)
    {
        case at_sudo200_JConsole_JConsole_BLACK    : color =  0; break;
        case at_sudo200_JConsole_JConsole_RED      : color = 12; break;
        case at_sudo200_JConsole_JConsole_GREEN    : color = 10; break;
        case at_sudo200_JConsole_JConsole_YELLOW   : color = 14; break;
        case at_sudo200_JConsole_JConsole_BLUE     : color =  9; break;
        case at_sudo200_JConsole_JConsole_MAGENTA  : color = 13; break;
        case at_sudo200_JConsole_JConsole_CYAN     : color = 11; break;
        case at_sudo200_JConsole_JConsole_WHITE    : color = 15; break;
        case at_sudo200_JConsole_JConsole_GRAY     : color =  8; break;
        case at_sudo200_JConsole_JConsole_H_RED    : color =  4; break;
        case at_sudo200_JConsole_JConsole_H_GREEN  : color =  2; break;
        case at_sudo200_JConsole_JConsole_H_YELLOW : color =  6; break;
        case at_sudo200_JConsole_JConsole_H_BLUE   : color =  1; break;
        case at_sudo200_JConsole_JConsole_H_MAGENTA: color =  5; break;
        case at_sudo200_JConsole_JConsole_H_CYAN   : color =  3; break;
        case at_sudo200_JConsole_JConsole_H_WHITE  : color =  7; break;
        default                                    : color =  0;
    }

    __FOREGROUND = color;
    color = __FOREGROUND + (__BACKGROUND << 4);
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color);
}

JNIEXPORT void JNICALL Java_at_sudo200_JConsole_JConsole_textcolor(JNIEnv *env, jclass c, jint color)
{
    textcolor(color);
}

void textbackground (int c)
{
int color = 0;

    switch(c)
    {
        case at_sudo200_JConsole_JConsole_BLACK    : color =  0; break;
        case at_sudo200_JConsole_JConsole_RED      : color =  4; break;
        case at_sudo200_JConsole_JConsole_GREEN    : color =  2; break;
        case at_sudo200_JConsole_JConsole_YELLOW   : color =  6; break;
        case at_sudo200_JConsole_JConsole_BLUE     : color =  1; break;
        case at_sudo200_JConsole_JConsole_MAGENTA  : color =  5; break;
        case at_sudo200_JConsole_JConsole_CYAN     : color =  3; break;
        case at_sudo200_JConsole_JConsole_WHITE    : color =  7; break;
        default                                    : color =  0;
    }

    __BACKGROUND = color;
    color = __FOREGROUND + (__BACKGROUND << 4);
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color);
}

JNIEXPORT void JNICALL Java_at_sudo200_JConsole_JConsole_textbackground(JNIEnv *env, jclass c, jint color)
{
    textbackground(color);
}

JNIEXPORT void JNICALL Java_at_sudo200_JConsole_JConsole_setCursorType (JNIEnv *env, jclass c, jint type)
{
    CONSOLE_CURSOR_INFO Info;

        GetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &Info);
        if (type == 0)
            Info.bVisible = FALSE;
        else
        {
            Info.dwSize = type;
            Info.bVisible = TRUE;
        }

        SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &Info);
}

JNIEXPORT void JNICALL Java_at_sudo200_JConsole_JConsole_closeConsole(JNIEnv *env, jclass c)
{
    textcolor(at_sudo200_JConsole_JConsole_WHITE);
    textbackground(at_sudo200_JConsole_JConsole_BLACK);
    gotoxy(0, 0);
    cmode = CONSOLE_MODE_OFF;
}

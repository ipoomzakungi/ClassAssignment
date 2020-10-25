#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>


void gotoxy(short, short);
void drawship(short, short);
void setcursor(bool);
void setcolor(int, int);
void bulletMove();
void bulletSetting();
void setupStar();
void checkStar(int);
void hitCheck(int);

char ch = ' ';
int x = 38, y = 20, c = 0;
int point = 0;
int bullet[5][2];
int numBullet = 0; //Bullet on screen
int star[20][2];

int main() {
    srand(time(NULL));
    setupStar();

    setcursor(0);

    gotoxy(70, 0);
    printf("Point : %d", point);
    drawship(x, y);
    ch = _getch();

    for (int i = 0; i < 5; i++)   //setting all position bullet
    {
        bullet[i][0] = 40;
        bullet[i][1] = 23;
    }
    while (ch != 'x') {
        setcolor(3, 0);
        gotoxy(92, 8);
        printf("Key : %c", ch);

        if (ch == 'w' || ch == 'W')
        {

            while (ch == 'w' || ch == 'W' || ch == ' ') {
                if (ch == ' ')
                {
                    bulletSetting();
                    ch = 'w';
                }
                while (!(_kbhit()))
                {
                    bulletMove();

                    Sleep(100);
                }
                ch = _getch();
            }
        }
        else if (ch == 'q' || ch == 'Q')
        {
            while (ch == 'q' || ch == 'Q' || ch == ' ') {
                while (!(_kbhit()))
                {
                    if (ch == ' ')
                    {
                        bulletSetting();
                        ch = 'q';
                    }
                    if (x > 0) {
                        gotoxy(x, y);
                        setcolor(2, 0);
                        printf("      ");
                        drawship(--x, y);
                    }
                    bulletMove();

                    Sleep(100);
                }
                ch = _getch();
            }
        }
        else if (ch == 'e' || ch == 'E')
        {
            while (ch == 'e' || ch == 'E' || ch == ' ') {
                while (!(_kbhit()))
                {
                    if (ch == ' ')
                    {
                        bulletSetting();
                        ch = 'e';
                    }
                    if (x < 60) {
                        gotoxy(x, y);
                        setcolor(2, 0);
                        printf("      ");
                        drawship(++x, y);
                    }
                    bulletMove();

                    Sleep(100);
                }
                ch = _getch();
            }

        }

        else {
            bulletMove();
            ch = _getch();
        }









    }
    gotoxy(0, 1);
    printf("DONE");
    return 0;
}


void gotoxy(short x, short y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawship(short x, short y)
{
    setcolor(2, 4);
    gotoxy(x, y);
    printf("<-0->");
}

void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void bulletMove()
{
    for (int i = 0; i < 5; i++)
    {
        setcolor(7, 0);
        gotoxy(bullet[i][0], bullet[i][1]);
        printf(" ");

        if (bullet[i][1] != 0 && bullet[i][1] != 23)
        {

            gotoxy(bullet[i][0], --bullet[i][1]);
            printf("•");

        }
        else if (bullet[i][1] == 0) {
            bullet[i][1] = 23;
            numBullet--;
        }
        hitCheck(i);
        gotoxy(92, 10);
        printf("Bullet Remain : %d", 5 - numBullet);


    }
}
void bulletSetting()
{
    if (numBullet < 5) {
        numBullet++;
        for (int i = 0; i < numBullet; i++)
        {
            if (bullet[i][1] == 23) {
                bullet[i][0] = x + 2;
                bullet[i][1] = 19;
            }
            else {

                //bullet[i][1]++;

            }

        }
    }


}

void setupStar()
{
    for (int i = 0; i < 20; i++)
    {
        star[i][0] = rand() % 58 + 2;
        star[i][1] = rand() % 4 + 1;
        checkStar(i);
        gotoxy(star[i][0], star[i][1]);
        printf("*");
    }
}

void checkStar(int i)
{
    for (int k = 0; k < i; k++)
    {
        if (star[i][0] == star[k][0] && star[i][1] == star[k][1])
        {
            star[i][0] = rand() % 60 + 10;
            star[i][1] = rand() % 4 + 1;
            checkStar(i);
        }
    }
}

void hitCheck(int i)
{
    for (int k = 0; k < 20; k++)
    {
        if (bullet[i][0] == star[k][0] && bullet[i][1] == star[k][1])
        {
            star[k][0] = 72;
            Beep(700, 100);
            point++;
            gotoxy(70, 0);
            printf("Point : %d", point);
        }

    }

}
#include "TXLib.h"

struct Personage
{
  int x;
  int y;
  int v;
  bool visible;
  HDC pic;
};

//Рисование бабочки
void DrawBut(Personage but)
{
    if (but.visible)
        txTransparentBlt (txDC(), but.x, but.y, 100, 100, but.pic, 0, 0, TX_WHITE);
}

struct Object
{
    int x;
    int w;
    int v;
    int y;
    bool visible;
};

void drawRoad(Object road)
{
    txSetFillColor(TX_WHITE);
    txRectangle(road.x, 545, road.x+road.w, 555);
}

int main()
{
    txCreateWindow (1200, 600);

    txDisableAutoPause();
    txTextCursor (false);

    HDC Fon = txLoadImage ("Картинки/Fon.bmp");


    HDC butUpRight = txLoadImage ("Картинки/Бабочка/UpRight.bmp");
    HDC butUpLeft = txLoadImage ("Картинки/Бабочка/UpLeft.bmp");

    Personage but[5];
    but[0] = {400, 300, 0, true, butUpRight};
    but[1] = {500, 300, 0, true, butUpLeft};
    but[2] = {400, 100, 0, true, butUpRight};
    but[3] = {800, 300, 0, true, butUpLeft};
    but[4] = {900, 200, 0, true, butUpRight};


    HDC marioRight = txLoadImage ("Картинки/Mario/right.bmp");
    HDC marioLeft = txLoadImage ("Картинки/Mario/left.bmp");

    Personage mario = {100, 400, 0, true, marioRight};

    Personage enemy = {1000, 400, 0, true, txLoadImage ("Картинки/Enemy/left.bmp")};

    int kol = 10;
    Personage bullet[100];

    int kolroad = 100;
    Object road[100];
    road[0].x=10;
    road[0].v=15;


    char str[100];



    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txClear();
        txSetColor(TX_WHITE,3);

        txBitBlt (txDC(), 0, 0, 1200, 600, Fon);

        txSetFillColor(TX_GRAY);
        txRectangle(0, 500, 1200, 600);

        for(int i=0; i<kolroad; i++)
        {
            road[i] = {road[0].x+(120*i), 100, road[0].v};
            drawRoad (road[i]);
        }


        road[0].x = road[0].x - road[0].v;
        enemy.x = enemy.x - road[0].v;



        txTransparentBlt (txDC(), mario.x, mario.y, 100, 125, mario.pic, 0, 0, TX_WHITE);

        if(enemy.visible)
        Win32::TransparentBlt (txDC(), enemy.x, enemy.y, 100, 125, enemy.pic, 0, 0, 100, 125, TX_WHITE);

        if(GetAsyncKeyState('D'))
        {
            mario.pic = marioRight;
            mario.x=mario.x+10;
        }

        if(GetAsyncKeyState('A'))
        {
            mario.pic = marioLeft;
            mario.x=mario.x-10;
        }

        if(GetAsyncKeyState(VK_SPACE))
        {
            mario.v=-20;
        }

        mario.y=mario.y+mario.v;
        mario.v=mario.v+3;

        if(mario.y>400)
            mario.y=400;

        if(GetAsyncKeyState(VK_CONTROL))
        {
            bullet[0] = {mario.x+50, mario.y+50, 25, true};
        }

        if(bullet[0].visible)
        {
            txSetColor(TX_WHITE,3);
            txCircle(bullet[0].x, bullet[0].y, 5);

            if(mario.pic == marioRight)
            bullet[0].x=bullet[0].x+bullet[0].v;

            else if (mario.pic == marioLeft)
            bullet[0].x=bullet[0].x-bullet[0].v;
        }

 //x3<x2 && x1<x4

        if (bullet[0].x>enemy.x && bullet[0].x<enemy.x+50)
        {
            enemy.visible = false;
            bullet[0].visible = false;
        }


//Вызов функции рисования бабочки
        for(int i=0; i<5; i++)
        {
            DrawBut(but[i]);
        }

        for(int i=0; i<5; i++)
        {
            if(GetAsyncKeyState(VK_DOWN))
            {
                but[i].pic = butUpRight;
                but[i].y=but[i].y+10;
            }

            if(GetAsyncKeyState(VK_UP))
            {
                but[i].pic = butUpLeft;
                but[i].y=but[i].y-10;
            }

            if(GetAsyncKeyState(VK_LEFT))
            {
                but[i].pic = butUpLeft;
                but[i].x=but[i].x-10;
            }

            if(GetAsyncKeyState(VK_RIGHT))
            {
                but[i].pic = butUpRight;
                but[i].x=but[i].x+10;
            }
        }

        if (but[0].x>=txGetExtentX())
        {
            but[0].x=txGetExtentX()-15;
        }

        if (but[0].x<=0)
        {
            but[0].x=15;
        }

        if (but[0].y<=0)
        {
            but[0].y=15;
        }

        if (but[0].y>=txGetExtentY())
        {
            but[0].y=txGetExtentY()-15;
        }

        txSetColor(TX_BLACK,3);
        txSelectFont("Time", 20);
        //Вывод значения переменной на экран
        sprintf(str, "X Марио = %d", mario.x);
        txTextOut(0,0, str);
        sprintf(str, "Y Марио = %d", mario.y);
        txTextOut(0,25, str);
        sprintf(str, "x road = %d", road[0].x);
        txTextOut(0,50, str);



        txSleep(50);
    }

    txDeleteDC (butUpRight);
    txDeleteDC (butUpLeft);

    for(int i=0; i<5; i++)
    {
        txDeleteDC (but[i].pic);
    }
    txDeleteDC (Fon);

    txDeleteDC (marioRight);
    txDeleteDC (marioLeft);


return 0;
}


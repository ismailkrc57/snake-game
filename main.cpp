#include <iostream>
#include <windows.h>
#include "win_fonksiyon.h"
#include <time.h>
#include <stdlib.h>
using namespace std;

enum YON
{
    sag = 1,
    sol = 2,
    asagi = 3,
    yukari = 4,
};

struct YILAN
{
    int x;
    int y;
    YON yon;
    char karakter = 'O';
};

struct YEM
{
    int x;
    int y;
    char sekil= 'x';
};

char tuslar[256];
const int max_yilan_uzunlugu = 500;
YILAN yilan[max_yilan_uzunlugu];
YEM yem;
int yilan_kuyruk_uzunlugu = 0;
const int saha_genisligi = 80;
const int saha_yuksekligi = 20;
char saha[saha_genisligi][saha_yuksekligi];
char yem_alani[saha_genisligi-4][saha_yuksekligi-4];
int rand_x, rand_y;
int score=0;

void klavye_oku(char tuslar[])
{
    for (int i=0; i<256; i++)
    {
        tuslar[i] = (char)(GetAsyncKeyState(i) >> 8);
    }
}

void saha_olustur()
{
    for(int y=0; y<saha_yuksekligi; y++)
    {
        for(int x=0; x<saha_genisligi; x++)
        {
            cout<<saha[x][y];
        }
        cout<<endl;
    }
}

void sinirlari_olustur()
{
    for(int x=0; x<saha_genisligi; x++)
    {
        saha[x][0] = 178;
        saha[x][saha_yuksekligi-1] = 178;
    }
    for(int y=0; y<saha_yuksekligi; y++)
    {
        saha[0][y] = 178;
        saha[saha_genisligi-1][y] = 178;
    }



}

void sahneyi_temzile()
{
    for(int y=0; y<saha_yuksekligi; y++)
    {
        for(int x=0; x<saha_genisligi; x++)
        {
            saha[x][y] = ' ';
        }
        cout<<endl;
    }
}

void kuyruk_ekle()
{
   if(yilan_kuyruk_uzunlugu == max_yilan_uzunlugu)
    return;
   int x = yilan[yilan_kuyruk_uzunlugu-1].x;
   int y = yilan[yilan_kuyruk_uzunlugu-1].y;
   YON yon = yilan[yilan_kuyruk_uzunlugu-1].yon;
   char karakter = yilan[yilan_kuyruk_uzunlugu-1].karakter;

   switch(yilan[yilan_kuyruk_uzunlugu-1].yon)
        {
            case sag:
                x--;
                break;
            case sol:
                x++;
                break;
            case asagi:
                y--;
                break;
            case yukari:
                y++;
                break;
        }

        yilan[yilan_kuyruk_uzunlugu].x = x;
        yilan[yilan_kuyruk_uzunlugu].y = y;
        yilan[yilan_kuyruk_uzunlugu].yon = yon;
        yilan[yilan_kuyruk_uzunlugu].karakter = karakter;
        yilan_kuyruk_uzunlugu++;
}

void yilan_olustur()
{

    yilan_kuyruk_uzunlugu =1;
    yilan[0].x = 20;
    yilan[0].y = 10;
    yilan[0].yon = sag;
    kuyruk_ekle();
    kuyruk_ekle();


}

void yilan_meydana_gel()
{
    for(int i=0; i<yilan_kuyruk_uzunlugu; ++i)
    {
        int x = yilan[i].x;
        int y = yilan[i].y;
        saha[x][y] = yilan[i].karakter;
    }
}

void yilan_kos()
{
    for(int i=0; i<yilan_kuyruk_uzunlugu; i++)
    {
        switch(yilan[i].yon)
        {
            case sag:
                yilan[i].x++;
                break;
            case sol:
                yilan[i].x--;
                break;
            case asagi:
                 yilan[i].y++;
                break;
            case yukari:
                yilan[i].y--;
                break;

        }
    }

     for(int i=yilan_kuyruk_uzunlugu-1; i>0; i--)
        {
            yilan[i].yon = yilan[i-1].yon;
        }
}

void klavye_kontrol()
{
    klavye_oku(tuslar);

    if(tuslar['A'] != 0)
    {
        yilan[0].yon = sol;
    }

    if(tuslar['D'] != 0)
    {
        yilan[0].yon = sag;
    }

    if(tuslar['W'] != 0)
    {
        yilan[0].yon = yukari;
    }
    if(tuslar['S'] != 0)
    {
        yilan[0].yon = asagi;
    }

}

int yem_konum_ver()
{
    srand(time(NULL));
    rand_x = 10 + rand()%70;
    rand_y = 2+ rand()%12;
}

void yenildin()
{
   /* for(int i=1; i<yilan_kuyruk_uzunlugu-1; i++)
    {
        if(yilan[0].x == yilan[i].x && yilan[0].x == yilan[i].y)
        {
            gotoxy(90,18);
            cout<<"KAYBETTINIZ";
            Sleep(8000);
            exit(1);
        }
    }
    */
    if(yilan[0].x ==0 || yilan[0].x == 79 || yilan[0].y == 0 || yilan[0].y == 19)
    {
        gotoxy(35,30);
            cout<<"KAYBETTIN";
            Sleep(8000);
            exit(1);
    }

}

int main ()
{

    kursor_gizle();
    yilan_olustur();
    yem_konum_ver();
    saha[rand_x][rand_y] = yem.sekil;
    saha_olustur();
    gotoxy(85,0);cout<<"score: "<<score;
    while(1)
    {
        sahneyi_temzile();
        sinirlari_olustur();
        klavye_kontrol();
        yenildin();
        if(yilan[0].x == rand_x && yilan[0].y == rand_y)
        {
            yem_konum_ver();
            kuyruk_ekle();
            score++;
            gotoxy(85,0);cout<<"score: "<<score;

        }
        saha[rand_x][rand_y] = yem.sekil;
        yilan_kos();
        yilan_meydana_gel();
        gotoxy(0,0);
        saha_olustur();
        Sleep(30);
    }

    cin.get();
}

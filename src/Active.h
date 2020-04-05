#if!defined ACTIVE_H_INCLUDE
#define ACTIVE_H_INCLUDE

#include <windows.h>
#include <vector>

using namespace std;

const int nBoxWidth = 10;

const int nWindowWidth = 600;

const int nWindowHeight  = 600;

const COLORREF colFirst = RGB(255, 0, 0);
const COLORREF colOther = RGB(0, 255, 0);
const COLORREF colApple = RGB(0, 0, 255);

typedef struct tagPerSnake
{
	int nXNow;
	int nYNow;
}PerSnake;

enum MODE
{
	Ready,
	Start,
	End
};



extern HBITMAP hbitmap;//±³¾°BITMAP
extern HDC     hmemdc;//±³¾°DC
extern BITMAP  bm;


extern vector<PerSnake> vec;

extern int nAppleX;
extern int nAppleY;

extern int nXmove;
extern int nYmove;

extern MODE CureentMode;



void Show(HWND hwnd);


void KeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam);

void RandomApple(void);

void Time(HWND);


bool Check(void);

int WinOrLost();

#endif
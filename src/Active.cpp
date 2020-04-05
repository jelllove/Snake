#include "Active.h"

HBITMAP hbitmap;
HDC     hmemdc;
BITMAP  bm;

MODE CureentMode;


int nAppleX;
int nAppleY;

int nXmove;
int nYmove;

vector<PerSnake> vec;

void Show(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);

 	PatBlt(hmemdc, 0, 0, bm.bmWidth, bm.bmHeight, WHITENESS);

	switch(CureentMode)
	{
	case Ready:
		{
			char text[] = "按下空格键开始";

			TextOut(hmemdc, 0, 0, text, strlen(text));

			break;
		}


	case Start:
		{

			HBRUSH brush;
			
			brush= CreateSolidBrush(colApple);

			SelectObject(hmemdc, brush);
			
			Rectangle(hmemdc, nAppleX, nAppleY , nAppleX  + nBoxWidth, nAppleY  + nBoxWidth);
			
			DeleteObject(brush);



			vector<PerSnake>::iterator it;

			it = vec.begin();
			
			brush= CreateSolidBrush(colFirst);
			
		    SelectObject(hmemdc, brush);
			
			Rectangle(hmemdc, (*it).nXNow , (*it).nYNow , (*it).nXNow  + nBoxWidth, (*it).nYNow  + nBoxWidth);
			
			DeleteObject(brush);


			brush= CreateSolidBrush(colOther);
			
			SelectObject(hmemdc, brush);
			
			for (it++; it < vec.end(); it++)
			{
				Rectangle(hmemdc, (*it).nXNow , (*it).nYNow, (*it).nXNow + nBoxWidth, (*it).nYNow + nBoxWidth);
			}

			DeleteObject(brush);

			break;
		}
	}



	BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hmemdc, 0, 0, SRCCOPY);

	ReleaseDC(hwnd, hdc);
}

void KeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch(CureentMode)
	{
	case Ready:
		{
			if (wParam == VK_SPACE)
			{
				
				SetTimer(hwnd, 1, 100, NULL);

				CureentMode = Start;
				PerSnake snake;

				snake.nXNow = 0;
				snake.nYNow = 0;
				nXmove = nBoxWidth;
				nYmove = 0;

				vec.clear();
				vec.push_back(snake);

				RandomApple();

				Show(hwnd);
			}
			break;
		}
	case Start:
		{
			switch(wParam) 
			{
			case VK_LEFT:
				{
					if (nYmove != 0)
					{
						nXmove = -nBoxWidth;
						nYmove = 0;
					}
					break;
				}

			case VK_UP:
				{
					if (nXmove != 0)
					{
						nXmove = 0;
						nYmove = -nBoxWidth;
					}
					break;
				}
			case VK_DOWN:
				{
					if (nXmove != 0)
					{
						nXmove = 0;
						nYmove = nBoxWidth;
					}
					break;
				}
			case VK_RIGHT:
				{
					if (nYmove != 0)
					{
						nXmove = nBoxWidth;
						nYmove = 0;
					}
					break;
				}
			}
			break;
		}
	}
}


void RandomApple(void)
{
	if (vec.empty())
	{
		return;
	}

	int n = 0;

	int nn;

	while (n !=1)
	{
		nn = rand()%(nWindowWidth / nBoxWidth);

		nAppleX = nn * nBoxWidth;

		n = 1;

		for (int i = 0; i < vec.size(); i++)
		{
			if ( (vec.at(i)).nXNow == nAppleX)
			{
				n = 0;

				break;
			}
		}
	}


	while (n !=2)
	{
		nn = rand()%(nWindowHeight / nBoxWidth);

		nAppleY = nn * nBoxWidth;

		n = 2;

		for (int i = 0; i < vec.size(); i++)
		{
			if ( (vec.at(i)).nYNow == nAppleY)
			{
				n = 0;

				break;
			}
		}
	}
}



void Time(HWND hwnd)
{
	if (CureentMode == Start)
	{
		vector<PerSnake>::iterator it;

		if (Check())
		{
			PerSnake snake;

			snake.nXNow = 0;
			snake.nYNow = 0;
			vec.push_back(snake);

			RandomApple();
		}

		int n = vec.size();

		for (int i = (n - 1); i > 0; i--)
		{
			(vec.at(i)).nXNow = (vec.at(i - 1)).nXNow;
			(vec.at(i)).nYNow = (vec.at(i - 1)).nYNow;
		}

		it = vec.begin();
		
		(*it).nXNow = (*it).nXNow + nXmove;
		(*it).nYNow = (*it).nYNow + nYmove;

		int nFlag = WinOrLost();

		if (nFlag == -1 || nFlag == 1)
		{
			KillTimer(hwnd, 1);
			
			if (nFlag == -1)
			{
				MessageBox(hwnd, "you lost", "GameOver", MB_OK);
			}
			else
			{
				MessageBox(hwnd, "You Win", "GoodGame", MB_OK);
			}
			

			CureentMode = Ready;
			PerSnake snake;
			
			snake.nXNow = 0;
			snake.nYNow = 0;
			nXmove = nBoxWidth;
			nYmove = 0;
			
			vec.clear();
			vec.push_back(snake);
			
			RandomApple();
		}


		Show(hwnd);
	}
}



bool Check(void)
{
	vector<PerSnake>::iterator it;

	it = vec.begin();

	if ((*it).nXNow == nAppleX && (*it).nYNow == nAppleY)
	{
		return true;
	}

	return false;
	
}


int WinOrLost()
{
	vector<PerSnake>::iterator it;

	it = vec.begin();

	int nNewX = (*it).nXNow;
	int nNewY = (*it).nYNow;

	if (nNewX < 0 || nNewX > nWindowWidth || nNewY < 0 || nNewY > nWindowHeight)
	{
		return -1;
	}

	int n = vec.size();

	for (int i = 1; i < n; i++)
	{
		if (vec.at(0).nXNow == vec.at(i).nXNow &&  vec.at(0).nYNow == vec.at(i).nYNow)
		{
			return -1;
		}
	}

	if (vec.size() >= (nWindowHeight / nBoxWidth) * (nWindowWidth / nBoxWidth) * 0.666)
	{
		return 1;
	}

	return 0;
	
}
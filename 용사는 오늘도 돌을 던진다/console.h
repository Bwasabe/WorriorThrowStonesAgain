#pragma once
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<cmath>
#include<string>
#include <random>
#include <vector>
#include <numeric>
//아스키아트
#include<io.h>
#include<fcntl.h>
#include<mmsystem.h>
#include<Digitalv.h>

#pragma comment(lib, "winmm.lib")

#define PI 3.141592
#define Rad2Deg (180/PI)
#define Deg2Rad (PI/180)
#define ERROR_NUM -1

#define SAFE_DELETE(P) if(P){delete(P); P = nullptr;}


enum Color
{
	Black,
	Blue,
	Gree,
	Aqua,
	Red,
	Purple,
	Yellow,
	White,
	LightBlue,
	LightGreen,
	LightAqua,
	LightRed,
	LightPurple,
	LightYellow,
	LightWhite,
	Length,
};

typedef struct tagOBJECTSIZE{
	LONG width;
	LONG height;
} OBJECTSIZE;

template<typename T>
T Input() {
	using namespace std;
	T input;
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');

		return ERROR_NUM;
	}

	return input;
}


void GotoXY(int x, int y);

void SetColor(int color, int bColor);
void FullScreen();

void NoScrollBarFullScreen();

RECT GetWindowRect();
void HideCursor();
void AwesomeTitle(std::wstring* titles, int titleLength);

int Random(int x, int y = 0);



bool operator==(const POINT& leftValue, const POINT& rightValue);

POINT operator+(const POINT &leftValue, const POINT& rightValue);

POINT operator-(const POINT& leftValue, const POINT& rightValue);

POINT operator+=(POINT& leftValue, const POINT& rightValue);


template<class T>
inline T operator~ (T a) { return (T)~(int)a; }
template<class T>
inline T operator| (T a, T b) { return (T)((int)a | (int)b); }
template<class T>
inline T operator& (T a, T b) { return (T)((int)a & (int)b); }
template<class T>
inline T operator^ (T a, T b) { return (T)((int)a ^ (int)b); }
template<class T>
inline T operator|= (T a, T b) { return (T)((int)a |= (int)b); }
template<class T>
inline T operator&= (T a, T b) { return (T)((int)a &= (int)b); }
template<class T>
inline T operator^= (T a, T b) { return (T)((int)a ^= (int)b); }



COORD WhereCursor(void);


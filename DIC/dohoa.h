#pragma once
#include<Windows.h>
#include<conio.h>
#include<string>
using namespace std;
#define x_thongbao 24
#define y_thongbao 40
#define Min_frame_x 20
#define Max_frame_x 121
#define Medium_frame_x 60
#define Min_frame_y 5
#define Max_frame_y 36

/*==============key===========*/
#define KEY_UP -72
#define KEY_DOWN -80
#define LEFT -75
#define RIGHT -77
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define HOME -71
#define DEL -83
#define TAB 9
#define INS -82
/*===================EDIT THEMES===============*/
void setcolor(short x) { //Ham thay doi textcolor va backgroundcolor
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, x);
}

void cls()//xoa toan bo man hinh va set mau toan man hinh ve mau lien truoc no
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer - tinh so phan tu trong bo nho dem*/
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces - lap day bang khoang trang*/
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes - thay doi bang tat ca thuoc tinh hien tai*/
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home - tra con tro ve dau*/
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void Nocursortype(bool Change)
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = Change;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void RemoveScroll() {
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(hstdout, csbi.dwSize);

	HWND x = GetConsoleWindow();
	ShowScrollBar(x, SB_BOTH, FALSE);
}
int  GetKey() {
	char key; key = _getch();
	if (key == -32 || key == 0)
		return -(_getch());
	else return key;
}
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void thongbao(string text, int x, int y)
{
	setcolor(4);
	gotoxy(x, y);
	cout << text;
	while (!_kbhit()){}
	gotoxy(x, y);
	for (int i = 0; i < text.size(); i++)
		cout << " ";
	setcolor(7);
}
void khung()
{
	for (int i = 1; i < Max_frame_x; i++)
	{
		gotoxy(Min_frame_x + i, Min_frame_y);
		cout << char(205);
		gotoxy(Min_frame_x + i, Max_frame_y);
		cout << char(205);
		if (i < Medium_frame_x)
		{
			gotoxy(Min_frame_x + i, 8); cout << char(205);
		}
	}
	gotoxy(Min_frame_x, Min_frame_y);
	cout << char(201);
	gotoxy(Min_frame_x+Max_frame_x, Min_frame_y);
	cout << char(187);
	gotoxy(Min_frame_x, Max_frame_y);
	cout << char(200);
	gotoxy(Min_frame_x + Max_frame_x, Max_frame_y);
	cout << char(188);
	gotoxy(Min_frame_x+Medium_frame_x, Min_frame_y); cout << char(203);
	gotoxy(Min_frame_x + Medium_frame_x, Max_frame_y); cout << char(202);
	for (int j = 0; j < 30; j++)
	{
		gotoxy(Min_frame_x + Medium_frame_x, j + 6);
		cout << char(186);
		gotoxy(Min_frame_x, j + 6);
		cout << char(186);
		gotoxy(Max_frame_x+Min_frame_x, j + 6);
		cout << char(186);
	}
	gotoxy(Min_frame_x+2, 7);
	cout << "TIM KIEM: ";	
}
void khung_thongbao()
{
	for (int i = 1; i < Max_frame_x; i++)
	{
		gotoxy(Min_frame_x + i, Max_frame_y + 2);
		cout << char(205);
		gotoxy(Min_frame_x + i, Max_frame_y + 6);
		cout << char(205);
	}
	for (int j = 1; j < 4; j++)
	{
		gotoxy(Min_frame_x, Max_frame_y + 2 + j);
		cout << char(186);
		gotoxy(Max_frame_x+20, Max_frame_y + 2 + j);
		cout << char(186);
	}
	gotoxy(Min_frame_x, Max_frame_y + 2); cout << char(201);
	gotoxy(Max_frame_x + 20, Max_frame_y + 2); cout << char(187);
	gotoxy(Min_frame_x, Max_frame_y + 6); cout << char(200);
	gotoxy(Max_frame_x + 20, Max_frame_y + 6); cout << char(188);
	setcolor(7);
	gotoxy(Min_frame_x + 56, Max_frame_y + 3); cout << "THONG BAO";
}
void cls1(int min_y,int max_y,int min_x)
{
	for (int i = min_y; i < max_y; i++)
	{
		gotoxy(min_x, i);
		cout << "                                                           ";
	}
}
void khung_insert()
{
	for (int i = 23; i < 83; i++)
	{
		gotoxy(Max_frame_x + i, Max_frame_y/2 + 12);
		cout << char(205);
		gotoxy(Max_frame_x + i, Max_frame_y+6);
		cout << char(205);
		gotoxy(Max_frame_x + i, Max_frame_y / 2 + 15);
		cout << char(205);
	}
	for (int j = 1; j < 12; j++)
	{
		if(j<3){ gotoxy(Max_frame_x + 53, Max_frame_y / 2 + 12 + j); cout << char(186);
		}
		gotoxy(Max_frame_x+23, Max_frame_y / 2 + 12+ j);
		cout << char(186);
		gotoxy(Max_frame_x + 82, Max_frame_y / 2 + 12 + j);
		cout << char(186);
	}
	gotoxy(Max_frame_x+23, Max_frame_y / 2 + 12); cout << char(201);
	gotoxy(Max_frame_x + 82, Max_frame_y / 2+12); cout << char(187);
	gotoxy(Max_frame_x+23, Max_frame_y+ 6); cout << char(200);
	gotoxy(Max_frame_x + 82, Max_frame_y + 6); cout << char(188);
	gotoxy(153, 31); cout << "THEM NGHIA";
	gotoxy(182, 31); cout << "THEM VI DU";
}
void delete_frame()
{
	for (int j = 0; j < 13; j++)
	{
		gotoxy(Max_frame_x + 23, Max_frame_y / 2 + 12 + j);
		for (int i = 23; i < 83; i++)cout << " ";
	}
}
void khung_huongdan()
{
	for (int i = 23; i < 83; i++)
	{
		gotoxy(Max_frame_x + i, Min_frame_y );
		cout << char(205);
		gotoxy(Max_frame_x + i, Min_frame_y + 3); cout << char(205);
		gotoxy(Max_frame_x + i, Max_frame_y / 2 + 10);
		cout << char(205);
	}
	for (int j = 1; j < 24; j++)
	{
		gotoxy(Max_frame_x + 23, Min_frame_y  + j);
		cout << char(186);
		gotoxy(Max_frame_x + 82, Min_frame_y + j);
		cout << char(186);
	}
	gotoxy(Max_frame_x + 23, Min_frame_y ); cout << char(201);
	gotoxy(Max_frame_x + 82, Min_frame_y); cout << char(187);
	gotoxy(Max_frame_x + 23, Max_frame_y/2 + 10); cout << char(200);
	gotoxy(Max_frame_x + 82, Max_frame_y/2 + 10); cout << char(188);
	gotoxy(169, 6); cout << "HUONG DAN";
}
void delete_frame_2()
{
	for (int i = 0; i < 19; i++)
	{
		gotoxy(Max_frame_x + 24, Min_frame_y + 4+i);
		setcolor(15);
		cout << "                                                          ";
	}
}
void huong_dan_chinh()
{
	
	delete_frame_2();
	setcolor(10);
	int i = Min_frame_y + 4;
	gotoxy(Max_frame_x + 28, i+=2);
	cout << "^ hoac v : Thay doi lua chon";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "INS : Them Tu";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "DEL: Xoa Tu";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "ENTER: Xem Tu";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "Y: Dong Y(YES)";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "N: Khong Dong Y(NO)";
	gotoxy(Max_frame_x + 28, i += 4);
	cout << "Lien Tuc Xem Thong Bao De Biet Chi Tiet Loi(Neu co)";
	setcolor(15);
}
void huong_dan_them()
{
	delete_frame_2();
	setcolor(10);
	int i = Min_frame_y+4 ;
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "1,2,3,4,5: Thay Doi Loai Tu Tuong Ung";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "1-DANH TU|2-DONG TU|3-TINH TU|4-TRANG TU|5-GIOI TU";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "^ hoac v : Chinh sua tu hoac nghia";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "ESC: Thoat Them Tu";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "ENTER: Them Tu Vao Tu Dien";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "Y: Dong Y(YES)";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "N: Khong Dong Y(NO)";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "Lien Tuc Xem Thong Bao De Biet Chi Tiet Loi(Neu co)";
	setcolor(15);
}
void huong_dan_them_2()
{
	delete_frame_2();
	setcolor(10);
	int i = Min_frame_y + 4;
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "ESC: Thoat Them Tu";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "ENTER: Them Tu Vao Tu Dien";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "Y: Dong Y(YES)";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "N: Khong Dong Y(NO)";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "< hoac >: De Chuyen QUa Them Ngia Hoac Them Tu";
	gotoxy(Max_frame_x + 28, i += 4);
	cout << "Lien Tuc Xem Thong Bao De Biet Chi Tiet Loi(Neu co)";
	
	setcolor(15);
}
void huong_dan_xoa()
{
	delete_frame_2();
	setcolor(10);
	int i = Min_frame_y + 4;
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "Y: Dong Y(YES)";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "N: Khong Dong Y(NO)";
	setcolor(15);
}
void huong_dan_tab()
{
	delete_frame_2();
	setcolor(10);
	int i = Min_frame_y + 4;
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "^ hoac v : Thay doi lua chon";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "TAB: Chuyen Lai Phan Tim Kiem";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "DEL: Xoa Nghia(chi xoa khi con it nhat 1 nghia)";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "Y: Dong Y(YES)";
	gotoxy(Max_frame_x + 28, i += 2);
	cout << "N: Khong Dong Y(NO)";
	setcolor(15);
}
void highlight(WordNodes *&data,int x,int y,int color)
{
	string s = data->word.English;
	setcolor(color);
	gotoxy(21, y);
	cout << "                                           ";
	gotoxy(x, y);	
	cout << s;
	setcolor(15);
}
void thongtinchung()
{
	string s = "\"DO AN TU DIEN\" VO VU DUC - N18DCCN048 - D18CQCN03-N";
	setcolor(11);
	gotoxy(60, 1);
	cout << s;
	setcolor(15);
}
void highlight_words(string &str, int x, int y, int color,string &s)
{
	setcolor(color);
	gotoxy(x, y);
	if (str.size() < 40) {
		for (int i = 0; i < str.size(); i++)
			cout << " ";
	}
	else {
		for (int i = 0; i < 40; i++)
			cout << " ";
	}
	
	gotoxy(x, y);
	cout << str;
	setcolor(15);
	if (s.size() > 40)
		gotoxy(72, 7);
	else
		gotoxy(33 + s.size(), 7);
}
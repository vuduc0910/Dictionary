#include<iostream>
#include<string>
#include<Windows.h>
#include<conio.h>
#include<fstream>
using namespace std;
#define MAX_SIZE_EXEMPLE 5
/*==============key===========*/
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define HOME 71
#define DEL 83
#define TAB 9
#define INS 82
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
/*=====================kHAI BÁO CẤU TRÚC===================*/
struct Mean {
	string mean = "";
	Mean *pNext = NULL;
};
struct l_mean {//danh sách nghĩa 
	Mean *mean_Head = NULL;
	Mean *mean_Tail = NULL;
	/*-----------------xử lý liên kết đơn--------*/
	void Insert_Last_Mean(string data)
	{
		Mean *p = new Mean;
		p->mean = data;
		if (mean_Head == NULL)
			mean_Head = mean_Tail = p;
		else
		{
			mean_Tail->pNext = p;
			mean_Tail = p;
		}
	}
	void Delete_Mean(int index)//vi tri xoa
	{
		if (mean_Head == NULL)
		{
			//xay ra loi khong thuc hien xoa
		}
		else
		{
			Mean *p = mean_Head;
			Mean *prev = NULL;
			int i;
			for (i = 1; i < index; i++)
			{
				prev = p;
				p = p->pNext;
			}
			if (i == 1)
			{
				mean_Head = mean_Head->pNext;
			}
			else {
				prev->pNext = p->pNext;
			}
			delete p;
		}
	}
};
struct Exemple {// mảng con trỏ
	int n = 0;
	string *Node[MAX_SIZE_EXEMPLE] = { NULL };
	void Insert_Exemple(string data)
	{
		if (n == MAX_SIZE_EXEMPLE)
		{
			// báo lỗi
		}
		else {
			Node[n++] = new string(data);
		}
	}
	int Search(string data)
	{
		for (int i = 0; i < n; i++)
		{
			if (data.compare(*Node[i]) == 0)
			{
				return i;
			}
		}
		return -1;
	}
	void Delete_Exemple(string data)
	{
		if (n == 0)
		{
			/* baos lỗi */
		}
		else {
			if (Search(data) != 0)
			{
				int i = Search(data);
				delete Node[i];// xoá bộ nhớ ở node bị xoá
				while (i < n - 1)
				{

					Node[i] = Node[i + 1];
					i++;
				}
				n--;
			}
		}
	}
};
enum wordtype {
	Nouns = 1, Verb = 2, Adjective = 3, Adverb = 4, Prepositions = 5
};
struct Word {// định nghĩa dữ liệu của nodes
	string English = "";
	l_mean list_mean;
	Exemple exemple;
	wordtype style = Nouns;
};
struct WordNodes {
	Word word;
	WordNodes *Next = NULL;
	WordNodes *Pre = NULL;
};
struct Hash_Dic {// kiểu dữ liệu này còn để định nghĩa mảng
	WordNodes *pHead = NULL;
	WordNodes *pTail = NULL;
	void Insert_Hash(WordNodes *&word)
	{
		if (pHead == NULL)
		{
			pHead = pTail = word;
		}
		else {
			pTail->Next = word;
			word->Pre = pTail;
			pTail = word;
		}
	}
};
string fixtext(string &s)// xoa dau cach thua 
{
	if (s != "")
	{
		const string& temp = " \t\n\v\f\r ";
		s.erase(0, s.find_first_not_of(temp));// xoá các kí tự thừa ở đầu chuỗi
		s.erase(s.find_last_not_of(temp) + 1);//  xoá kí tự thùa cuối chuỗi
		//xoá kí tự thừa ở giữa chuỗi
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == ' '&&s[i + 1] == ' ')
			{
				s.erase(i, 1);
				i--;
			}
		}
		//chuyển chữ hoa thành chữ thường
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] > 64 && s[i] < 91)
				s[i] += 32;
		}
	}
	return s;
}
int HashFirst(WordNodes *&WORD)//tách kí tự đầu tiên của từ
{
	string s = WORD->word.English;
	if (s != "") {
		return s[0] - 97;
	}
	return -1;
}
void output_file(ofstream &fileout, Hash_Dic *dictionary)
{
	//for (int i = 0; i < 26; i++)
	{
		for (WordNodes *p = dictionary[0].pHead; p != NULL; p = p->Next)
		{
			fileout << p->word.English << "|";
			fileout << p->word.style << "|";
			for (Mean *j = p->word.list_mean.mean_Head; j != p->word.list_mean.mean_Tail; j = j->pNext)
				fileout << j->mean << ",";
			fileout << p->word.list_mean.mean_Tail->mean;
			fileout << "|";
			for (int k = 0; k < p->word.exemple.n; k++)
			{
				fileout << *p->word.exemple.Node[k] << ",";
			}
		}
	}
}
void Readline(string line, WordNodes *&data)
{
	string s = "";
	int i = 0;
	while (line[i] != '|')
	{
		s += line[i];
		i++;

	}
	data->word.English = s;
	s = "";
	i++;//loai bo vi tri dau |
	int typeint = line[i] - '0';//chuyển sang kiểu int

	wordtype type = (wordtype)Verb;
	switch (typeint)
	{
	case 1: {
		type = (wordtype)Nouns;
		break; }
	case 2: {
		type = (wordtype)Verb;
		break; }
	case 3: {
		type = (wordtype)Adjective;
		break; }
	case 4: {
		type = (wordtype)Adverb;
		break; }
	case 5: {
		type = (wordtype)Prepositions;
		break; }
	}
	data->word.style = type;

	i += 2;
	while (line[i] != '|')
	{
		if (line[i] != ',')
		{
			s += line[i];
		}
		else {
			if (s != "")
			{

				data->word.list_mean.Insert_Last_Mean(s);
				s = ""; //bỏ dấu ","
			}
		}

		i++;
	}
	data->word.list_mean.Insert_Last_Mean(s);
	s = "";
	i++;
	for (int j = 0; j < MAX_SIZE_EXEMPLE; j++)
	{
		while (line[i] != ',')
		{
			s += line[i];
			i++;
		}
		i++;
		data->word.exemple.Insert_Exemple(s);
		s = "";
	}
}

void input_file(ifstream &filein, Hash_Dic *&dic)
{
	string line;
	if (filein.is_open())
	{
		while (getline(filein, line))
		{

			WordNodes *data = new WordNodes;
			getline(filein, line);
			Readline(line, data);
			dic->Insert_Hash(data);
		}
	}
}
void input(Hash_Dic &dic)
{
	WordNodes *p = new WordNodes;
	rewind(stdin);
	cout << "\nTu";
	getline(cin, p->word.English);
	string data;
	cout << "\nNgia:";
	getline(cin, data);
	p->word.list_mean.Insert_Last_Mean(data);
	cout << "\nvidu";
	for (int i = 0; i <= 4; i++)
	{
		rewind(stdin);
		string data1;
		getline(cin, data1);
		p->word.exemple.Insert_Exemple(data1);
	}
	p->word.style = Nouns;
	p->Next = p->Pre = NULL;
	dic.pHead = dic.pTail = p;
}
void output(Hash_Dic *&dic)
{
	for (WordNodes *i = dic[0].pHead; i != NULL; i = i->Next)
	{
		cout << i->word.English << endl;
		cout << i->word.style << endl;
		for (Mean *j = i->word.list_mean.mean_Head; j != NULL; j = j->pNext)
		{
			cout << j->mean << endl;
		}
		for (int k = 0; k < i->word.exemple.n; k++)
		{
			cout << *i->word.exemple.Node[k] << endl;
		}
	}
}
int main()
{
	Hash_Dic *dic;
	dic = new Hash_Dic;
	string line = "05";
	ifstream filein;
	filein.open("dic.txt", ios::in);
	input_file(filein, dic);
	filein.close();
	output(dic);
	ofstream of;
	of.open("of.txt", ios::out);
	output_file(of, dic);
	of.close();
	while (1) {};
	return 0;
}


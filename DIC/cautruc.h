#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
#include<conio.h>
#include<fstream>
using namespace std;
#define MAX_SIZE_EXEMPLE 5
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
		if (mean_Head == NULL&&mean_Head==mean_Tail)
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
			if (p == mean_Tail)
				mean_Tail = prev;
			delete p;
		}
	}
	int solienket()
	{
		int dem = 0;
		for (Mean *i = mean_Head; i != NULL; i = i->pNext)
		{
			++dem;
		}
		return dem;
	}
};
struct Exemple {// mảng con trỏ
	int n = 0;
	string *Node[MAX_SIZE_EXEMPLE] = { NULL };
	void Insert_Exemple(string data)
	{
		if (n == MAX_SIZE_EXEMPLE)
		{
			//không xử lí
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
			if (Search(data) != -1)
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
enum wordtype {//kiểu liệt kê
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
};

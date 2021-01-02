#include"cautruc.h"
#include"dohoa.h"
int HashFirst(WordNodes *&WORD)//tách kí tự đầu tiên của từ . hashf(string s)
{
	string s = WORD->word.English;
	if (s != "") {
		return (int)s[0] - 97;// mã ascii a=97
	}
	return -1;
}
bool lookup_str(string &fi, string &s)// timf theo tung chu
{
	if (fi.size() > s.size())
		return false;
	for (int i = 0; i < fi.size(); i++)
	{
		if (fi[i] != s[i])
			return false;
	}
	return true;
}
//tim kiem tutrong dic
bool seach_str(string &fi, string &s)// tim toan bo tu
{
	if (fi.size() != s.size())
		return false;
	for (int i = 0; i < fi.size(); i++)
	{
		if (fi[i] != s[i])
			return false;
	}
	return true;
}
//===============xử lí liên kết kép====================
void Insert_dictionary(Hash_Dic *&dic, WordNodes *&data)// theem vao mang bamw
{
	int index = HashFirst(data);
	if (dic[index].pHead == NULL)
	{
		dic[index].pHead = dic[index].pTail = data;
	}
	else
	{
		WordNodes *i;
		for (i = dic[index].pHead; i != NULL && i->word.English.compare(data->word.English) == -1; i = i->Next);
		if (i == NULL)
		{
			dic[index].pTail->Next = data;
			data->Pre = dic[index].pTail;
			dic[index].pTail = data;
		}
		else if (i == dic[index].pHead)
		{
			data->Next = dic[index].pHead;
			dic[index].pHead->Pre = data;
			dic[index].pHead = data;
		}
		else {
			WordNodes *p = i->Pre;
			data->Next = i;
			data->Pre = p;
			p->Next = data;
			i->Pre = data;
		}

	}
}
int Test_Hashdish_Next(int index, Hash_Dic *&dic)//giá trị i đầu tiên của hash dic
{
	for (int i = index + 1; i < 26; i++)
	{
		if (dic[i].pHead != NULL)
			return i;
	}
	return -1;//không có mảng nào ở sau có giá trị
}
int Test_Hashdish_Pre(int index, Hash_Dic *&dic)// kiểm tra vi tri từ phía trước gần nhất
{
	for (int j = index - 1; j > -1; j--)
	{
		if (dic[j].pHead != NULL)
			return j;
	}
	return -1;
}
void Delete_word(Hash_Dic *&dic, WordNodes *&data)//xoa trong 1 mang bam
{
	int index = HashFirst(data);
	if (dic[index].pHead == NULL)
	{
		return;
	}
	for (WordNodes *i = dic[index].pHead; i != NULL; i = i->Next)
	{
		if (seach_str(i->word.English, data->word.English) == true)
		{
			if (i == dic[index].pHead&&i == dic[index].pTail) {
				delete dic[index].pHead;
				dic[index].pHead = dic[index].pTail = NULL;
			}
			else if (i == dic[index].pHead&&i != dic[index].pTail)
			{
				i = i->Next;
				i->Pre = NULL;
				delete dic[index].pHead;
				dic[index].pHead = i;
			}
			else if (i == dic[index].pTail&&i != dic[index].pHead)
			{
				i = i->Pre;
				i->Next = NULL;
				delete dic[index].pTail;
				dic[index].pTail = i;
			}
			else {
				i->Pre->Next = i->Next;
				i->Next->Pre = i->Pre;
				delete i;
			}
			break;
		}
	}
}
/*===================Xử lí string================*/
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

WordNodes *Nextword(WordNodes *&word, Hash_Dic *&dic)
{
	int index = HashFirst(word);
	if (word->Next == NULL)
	{
		if (Test_Hashdish_Next(index, dic) != -1)
		{
			return dic[Test_Hashdish_Next(index, dic)].pHead;
		}
		else {
			return NULL;
		}
	}
	/*for (WordNodes *i = dic[index].pHead; i != NULL; i = i->Next)
	{
		if (seach_str(word->word.English, i->word.English) == true)
			return i->Next;
	}*/
	return word->Next;
}
WordNodes *Preword(WordNodes *&word, Hash_Dic *&dic)
{
	int index = HashFirst(word);
	if (word->Pre == NULL)
	{
		if (Test_Hashdish_Pre(index, dic) != -1)
			return dic[Test_Hashdish_Pre(index, dic)].pTail;
		else
			return NULL;
	}
	/*for (WordNodes *i = dic[index].pHead; i != NULL; i = i->Next)
	{
		if (seach_str(word->word.English, i->Next->word.English) == true)
			return i;
	}*/
	return word->Pre;
}
//tim kiem
//input vao keyhit
string insert_string_find(string &s, int x, int y, char &key)
{
	switch (key)
	{
	
	case BACKSPACE:
	{
		if (s != ""&&s.size() < 41)
		{
			s[s.size() - 1] = ' ';
			gotoxy(x, y); cout << s;
			s.pop_back();
			gotoxy(x, y); cout << s;

		}
		else if (s.size() > 40)
		{
			gotoxy(x, y);
			for (int i = 0; i < 40; i++)
			{
				cout << s[s.size() - 40 + i];
			}
			s.pop_back();
		}
		//cls1(9, 36, 21);
		return s;
	}
	default:
	{
		if ((key < 65 || (key > 90 && key < 97) || key>122) && key != 32)
		{
			cls1(6, 36, 81);
			gotoxy(100, 20); setcolor(4); cout << ".....WARNING.....";
			gotoxy(98, 21); setcolor(4); cout << "***CHU Y THONG BAO***";
			thongbao("Ki tu khong hop le, vui long nhap lai ki tu chu tu a->z hoac ki tu ben bang huong dan va tiep tuc.", x_thongbao, y_thongbao);

		}
		else if (key == 32 && s == "") {}
		else
		{
			if (key == 32 && s[s.size() - 1] == ' ') {}
			else {
				if (key > 64 && key < 91)
					key += 32;//CHUYEN VỀ CHỮ THƯỜNG
				s.push_back(key);
				if (s.size() > 40)
				{
					gotoxy(x, y);
					for (int i = 0; i < 40; i++)
					{
						cout << s[s.size() - 40 + i];
					}
				}
				else {
					gotoxy(x, y);
					cout << s;
				}
			}
		}
		return s;
	}
	}
}

// tim tu

//thao tac sap xep 
void sort_dic(Hash_Dic *&dic)
{
	for (int i = 0; i < 26; i++)
	{
		for (WordNodes *k = dic[i].pHead; k != NULL; k = k->Next)
		{
			for (WordNodes *j = dic[i].pHead; j != NULL; j = j->Next)
			{
				if (k->word.English.compare(j->word.English) == -1)
				{
					Word temp = k->word;
					k->word = j->word;
					j->word = temp;
				}
			}
		}
	}
}
void display_str(string &s, int x, int &y)
{
	if (s.size() > 40)
	{
		int i = 0, j = 0, k = 0;
		while (i < s.size())
		{
			if (j > 53)
			{
				j = 0;
				k++;
			}
			gotoxy(x + j, 6 + y + k);
			cout << s[i];
			j++;
			i++;
		}
		y = y + k;
	}
	else
	{
		gotoxy(x, 6 + y);
		cout << s;
	}
}
void display_Hashdic(Hash_Dic *&dic, int so_dau, int so_cuoi, string s)
{
	/*if (s == "")
	{*/
		int dem = 0;
		WordNodes *p = dic[Test_Hashdish_Next(-1, dic)].pHead;
		for (int i = 0; i <= so_dau; i++) p = Nextword(p, dic);
		while (p != NULL && dem < so_cuoi)
		{
			gotoxy(33, 10 + dem++);
			cout << p->word.English;
			p = Nextword(p, dic);
		}
	//}
	/*else
	{
		int dem = 0;
		WordNodes *p = NULL;
		int index = s[0] - 97;
		for (WordNodes *j = dic[index].pHead; j != NULL; j = j->Next)
		{
			if (lookup_str(s, j->word.English) == true)
			{
				p = j;
				break;
			}
		}
		if (p == NULL) {}
		else {
			for (int i = 0; i <= so_dau; i++) p = Nextword(p, dic);
			while (p != NULL && dem < so_cuoi&&lookup_str(s, p->word.English) == true)
			{
				gotoxy(33, 10 + dem++);
				cout << p->word.English;
				p = Nextword(p, dic);
			}
		}
	}*/
}
void tach_words(WordNodes *&data, string *&ds,int &temp) {
	string s1, s2, s3, s4;
	s1 = "Tu: ";
	s2 = "Loai tu : ";
	s3 = "Nghia: ";
	s4 = "Vidu: ";

	ds[0] = s1 + data->word.English;
	switch (data->word.style)
	{
	case 1: ds[1] = s2 + "DANH TU";
		break;
	case 2: ds[1] = s2 + "DONG TU";
		break;
	case 3:ds[1] = s2 + "TINH TU";
		break;
	case 4:ds[1] = s2 + "TRANG TU";
		break;
	case 5:ds[1] = s2 + "GIOI TU";
		break;
	}
	ds[2] = s3;
	int dem = 3;
	for (Mean *i = data->word.list_mean.mean_Head; i != NULL; i = i->pNext)
	{
		ds[dem++] = i->mean;
	}
	temp = dem;//để chuyển dòng
	ds[dem++] = s4;
	for (int j = 0; j < data->word.exemple.n; j++)
	{
		if (*data->word.exemple.Node[j] != "")
			ds[dem++] = *data->word.exemple.Node[j];
	}
}
void display_words(WordNodes *&data,int vitri_dau)
{
	int ts=4+data->word.list_mean.solienket();
	for (int j = 0; j < data->word.exemple.n; j++)
	{
		if (*data->word.exemple.Node[j] != "")
			ts += 1;
	}
	string *ds = new string[ts];
	cls1(6, 36, 81);//xoa khung ben phai
	int dem = vitri_dau;
	int digital = 0;
	int temp;//kiem tra tu s4
	tach_words(data, ds, temp);
	while (digital < 27 && dem < ts)
	{
		if (dem == 0 || dem == 1 || dem == 2 || dem == temp) {
			gotoxy(81, 6 + ++digital); cout << ds[dem++];
			
		}
		else if (dem > temp)
		{
			digital += 1;
			display_str(ds[dem], 85, digital);
			dem += 1;
		}
		else {
			gotoxy(85, 6 + ++digital); cout << ds[dem++];
		}
		////gotoxy(0, 9); cout << dem;
	}
	delete[] ds;
}
/*========================MODEM THEM TU====================*/
WordNodes *Insert_word()//THEEM TU
{
	//=TAOJ GIAO DIEN BAN DAU
	WordNodes *p = new WordNodes;
	cls1(6, 36, 81);
	bool kttt = true;//kiem tra trang thai da them nghia hoac vi du moi chua
	int item = 1;
	int digital = 0;
	gotoxy(105, 6); cout << "NEW WORD";
	gotoxy(81, 6 + ++digital); cout << "Tu: ";
	gotoxy(81, 6 + ++digital); cout << "Loai Tu: DANH TU";
	gotoxy(81, 6 + ++digital); cout << "Nghia:"; gotoxy(85, 7);
	//DUA VAO VONG LAP BAT KEY
	while (1) {
		char key_in = GetKey();
		/*Thoát việc thêm từ và không lưu từ*/
		if (key_in == ESC) {
			while (1) {
				thongbao("BAN CO MUON THOAT VIEC THEM TU HAY KHONG? (Y/N)", x_thongbao, y_thongbao);
				char key_esc = GetKey();
				if (key_esc == 89 || key_esc == 121)
				{
					delete p;
					cls1(6, 36, 81);
					return NULL;
				}
				else if (key_esc == 78 || key_esc == 110)//đưa trỏ chuột về vị trí cũ
				{
					string s;
					if (item == 1)
					{
						s = p->word.English;
						gotoxy(85 + s.size(), 7);
					}
					else
					{
						s = p->word.list_mean.mean_Head->mean;
						gotoxy(88 + s.size(), 9);
					}
					break;
				}
			}

		}
		/*Kết thúc viết thoát thêm từ*/
		/* NHẤN PHÍM ĐỂ THÊM NGHĨA VÀ VÍ DỤ*/
		else if (key_in == INS)
		{
			huong_dan_them_2();
			string mean = "";
			string exemple = "";
			khung_insert();
			int item1 = 1;
			setcolor(4);
			gotoxy(153, 31); cout << "THEM NGHIA";
			setcolor(15);
			gotoxy(Max_frame_x + 24, 35); cout << "NGHIA: " << mean;
			setcolor(15);
			while (1)
			{
				char key_ins = GetKey();
				if (key_ins == ENTER)//nhap vao nghĩa hoac vi du
				{
					bool kt = false;//tao dong thai de thoat vong lap
					while (1)
					{
						
						thongbao("BAN CO MUON LUU NGHIA VA VI DU NAY HAY KHONG?(Y/N)", x_thongbao, y_thongbao);
						char key1 = GetKey();
						if (key1 == 89 || key1 == 121) {
							if (mean != "")
							{
								p->word.list_mean.Insert_Last_Mean(mean);
							}
							if (exemple != "") {
								p->word.exemple.Insert_Exemple(exemple);
							}
							delete_frame();
							// đưa con trỏ chuột về vi trí tu
							display_words(p, 0);
							item = 1;
							string str = p->word.English;
							gotoxy(85 + str.size(), 7);
							kttt = false;//có còn cho phép tuỳ chỉnh nghĩa không
							kt = true;// kiểm tra thoát vòng lặp
							
							break;
						}
						else if (key1 == 78 || key1 == 110)
						{
							
							break;
						}						
					}
					if (kt == true)
						break;
				}
				else if (key_ins == ESC)//thoat them vi du
				{
					bool kt = false;// biến thoát vòng lặp lớn
					while (1) {
						thongbao("BAN CO MUON THOAT VIEC THEM NGHIA VA VI DU HAY KHONG ? (Y/N) ", x_thongbao, y_thongbao);
						char key1 = GetKey();
						if (key1 == 89 || key1 == 121) {
							delete_frame();
							kt = true;
							break;
						}
						else if (key1 == 78 || key1 == 110)
						{
							break;
						}
					}
					if (kt == true) {
						item = 1;
						string s = p->word.English;
						gotoxy(85 + s.size(), 7);
						break;
					}
				}
				else if (key_ins == LEFT || key_ins == RIGHT)//chuyen doi qua lai giua them tu va them vi du
				{
					if (p->word.exemple.n < MAX_SIZE_EXEMPLE) {
						if (item1 == 1)
						{
							for (int k = 0; k < mean.size() + 7; k++)//xoa cai hien thi nghia
							{
								gotoxy(Max_frame_x + 24 + k, 35); cout << " ";
							}
							gotoxy(153, 31); cout << "THEM NGHIA";
							setcolor(4);
							gotoxy(182, 31); cout << "THEM VI DU";
							setcolor(15);
							gotoxy(Max_frame_x + 24, 35); cout << "VI DU: " << exemple;
							item1 = 2;
							gotoxy(Max_frame_x + 31 + exemple.size(), 35);
						}
						else
						{
							for (int k = 0; k < exemple.size() + 7; k++)//xoa cai hien thi nghia
							{
								gotoxy(Max_frame_x + 24 + k, 35); cout << " ";
							}
							gotoxy(182, 31); cout << "THEM VI DU";
							setcolor(4);
							gotoxy(153, 31); cout << "THEM NGHIA";
							setcolor(15);
							gotoxy(Max_frame_x + 24, 35); cout << "NGHIA: " << mean;
							item1 = 1;
							gotoxy(Max_frame_x + 31 + mean.size(), 35);
						}
					}
					else {
						thongbao("SO LUONG VI DU DA DU KHONG THE THEM TIEP", x_thongbao, y_thongbao);
						gotoxy(Max_frame_x + 24, 35); cout << "NGHIA: " << mean;
					}
				}
				
				else
				{
					if ((key_ins < 65 || (key_ins > 90 && key_ins < 97) || key_ins>122) && key_ins != 32 && key_ins != BACKSPACE)
					{

					}
					else
					{
						if (item1 == 1)
						{
							mean = insert_string_find(mean, Max_frame_x + 31, 35, key_ins);
							gotoxy(Max_frame_x + 31+ mean.size(), 35);// dduwa tro chuot ve vi tri do;
						}
						else
						{
							exemple = insert_string_find(exemple, Max_frame_x + 31, 35, key_ins);
							gotoxy(Max_frame_x + 31 + exemple.size(), 35);
						}
					}

				}
			}
		}
		/* KẾT THÚC THÊM NGHĨA VÀ VÍ DỤ*/
		else if (key_in >= 49 && key_in <= 53) {
			gotoxy(90, 8);
			cout << "                 ";
			wordtype type = (wordtype)Verb;
			switch (key_in)
			{

			case 49:
			{
				type = (wordtype)Nouns;
				gotoxy(90, 8); cout << "DANH TU";
				break;
			}
			case 50:
			{
				type = (wordtype)Verb;
				gotoxy(90, 8); cout << "DONG TU";
				break;
			}
			case 51:
			{
				type = (wordtype)Adjective;
				gotoxy(90, 8); cout << "TINH TU";
				break;
			}
			case 52:
			{
				type = (wordtype)Adverb;
				gotoxy(90, 8); cout << "TRANG TU";
				break;
			}
			case 53:
			{
				type = (wordtype)Prepositions;
				gotoxy(90, 8); cout << "GIOI TU";
				break;
			}
			}
			p->word.style = type;
			string s = p->word.English;
			gotoxy(85 + s.size(), 7);
		}
		else if (key_in == KEY_DOWN || key_in == KEY_UP) {
			if (kttt == true) {
				if (item == 1)
				{
					
						string s = "";
						if (p->word.list_mean.mean_Head != NULL)
						{
							s = p->word.list_mean.mean_Head->mean;
						}
						gotoxy(88 + s.size(), 9);
						item = 2;
					
					
				}
				else {
					string s = p->word.English;
					gotoxy(85 + s.size(), 7);
					item = 1;
				}
			}
		}
		else if (key_in == ENTER)
		{
			if (p->word.English != ""&&p->word.list_mean.mean_Head!=NULL) {
				string tb = "BAN CO MUON THEM TU \"";
				tb += p->word.English;
				tb += "\" HAY KHONG? (Y/N)";
				while (1)
				{
					thongbao(tb, x_thongbao, y_thongbao);
					char key_enter = GetKey();
					if (key_enter == 89 || key_enter == 121)
					{
						int m = p->word.exemple.n;
						for (int i = 0; i < 5 - m; i++)//cho tat ca nhung khoang vi du khong co de luu file
						{
							p->word.exemple.Insert_Exemple("");
						}
						cls1(6, 36, 81);
						return p;
					}
					else if (key_enter == 78 || key_enter == 110)//đưa trỏ chuột về vị trí cũ
					{
						string s;
						if (item == 1)
						{
							s = p->word.English;
							gotoxy(85 + s.size(), 7);
						}
						else
						{
							s = p->word.list_mean.mean_Head->mean;
							gotoxy(88 + s.size(), 9);
						}
						break;
					}
				}
			}
			
		}
		else if ((key_in < 65 || (key_in > 90 && key_in < 97) || key_in>122) && key_in != 32 && key_in != BACKSPACE) {}
		else
		{
		/*tiep tuc nhap nghia*/
			if (item == 1)
			{
				string s = p->word.English;
				insert_string_find(s, 85, 7, key_in);
				p->word.English = s;
			}
			/*tiep tuc nhap vu du*/
			else if (item == 2)
			{
				string str;
				if (p->word.list_mean.mean_Head == NULL)//tao mot vi du khoi dau;
				{
					string s = "";
					p->word.list_mean.Insert_Last_Mean(s);
				}
				str = p->word.list_mean.mean_Head->mean;
				insert_string_find(str, 88, 9, key_in);
				if (str != "")
					p->word.list_mean.mean_Head->mean = str;
				else
					p->word.list_mean.Delete_Mean(0);

			}
		}
	}
}
/*===========================MODEM QUAN TRONG NHAT BAI=================*/
void find_str(Hash_Dic *&dic)//modem chinh 
{
	WordNodes *currentword = NULL;
	string s = "";
	int vitri = 0;
	int vitri_hienthidau = -1;
	int vitri_hienthicuoi = 24;//mặc định hiển thị tối đa 24 từ
	display_Hashdic(dic, vitri_hienthidau, vitri_hienthicuoi, s);
	khung_huongdan();
	huong_dan_chinh();
	khung_thongbao();
	khung();
	if (Test_Hashdish_Next(-1, dic) != -1) {
		currentword = dic[Test_Hashdish_Next(-1, dic)].pHead;
		/*//gotoxy(0, 0); cout << vitri_hienthidau;*/
		highlight(currentword, 33, 10 + vitri++, 240);
		display_words(currentword,0);
		gotoxy(33 + s.size(), 7);
	}
	while (true)
	{
		while(!_kbhit())
		{
			
		}
		char key = GetKey();
		if (key == ESC)
		{
			while (1) {
				thongbao("BAN CO MUON THOAT CHUONG TRINH HAY KHONG? (Y/N)", x_thongbao, y_thongbao);
				char key_esc = GetKey();

				if (key_esc == 89 || key_esc == 121)
					return;
				else if (key_esc == 78 || key_esc == 110)
				{
					break;
				}
			}
		}
		/*========================XEM TU=========================*/
		else if (key == ENTER)
		{
			huong_dan_tab();
			if (currentword != NULL) {
				string str = currentword->word.list_mean.mean_Head->mean;
				int vt = 0;
				int vitridau = 0;
				int dem = 0;
				int danhdau = 0;
				highlight_words(str, 85, 10, 112,s);//lam sang nghia dau tien
				int ts = currentword->word.list_mean.solienket();
				for (int j = 0; j < currentword->word.exemple.n; j++)
				{
					if (*currentword->word.exemple.Node[j] != "")
						ts += 1;
				}
				/*ĐƯA VÀO MẢNG STRING ĐỂ DỄ KIỂM SOÁT*/	
				string *ds = new string[ts];
				for (Mean *i = currentword->word.list_mean.mean_Head; i != NULL; i = i->pNext)
				{
					ds[dem++] = i->mean;
				}
				danhdau = dem;
				for (int j = 0; j < currentword->word.exemple.n; j++)
				{
					if (*currentword->word.exemple.Node[j] != "")
						ds[dem++] = *currentword->word.exemple.Node[j];
				}
				////gotoxy(0, 0); cout << ds[ts - 1];
				dem = 0;
				while (1)
				{
					char key_tab = GetKey();
					if (key_tab == TAB)
					{
						display_words(currentword, 0);
						highlight_words(ds[dem], 85,10 + vt, 15,s);
						delete[] ds;
						break;
					}					
					else if (key_tab == KEY_DOWN)
					{
						//gotoxy(0, 3); cout << ts;
						if (vt > 22)
						{
							//gotoxy(0, 1); cout << dem << " " << vt;
							if (dem < ts-1)
							{
								if (dem == danhdau - 1)
									vitridau += 1;
								vitridau += 1;
								display_words(currentword, vitridau);
							}
							////gotoxy(0, 4);cout<< vitridau;
							if (dem < ts - 1) {
								
								//highlight_words(ds[dem], 85, 10 + vt, 15, s);
								dem += 1;
								
								highlight_words(ds[dem], 85, 10 + vt, 112, s);
								//gotoxy(0, 4); cout << ds[dem];
								
							}
						}
						else {
							if (dem < ts-1) {
								highlight_words(ds[dem], 85, 10 + vt, 15, s);
								if (dem == danhdau-1)
									vt += 2;
								else
									vt += 1;								
								highlight_words(ds[++dem], 85, 10 + vt, 112, s);
								//gotoxy(0, 1); cout << dem << " " << vt;
							}
							
						}	
						
					}
					else if (key_tab == KEY_UP)
					{
						if (vt == 0 )
						{
							if (vitridau == 0)
							{
								//khong xu li
							}
							else if(vitridau!=0){
								highlight_words(ds[dem], 85, 10 + vt, 15, s);
								vitridau = 0;
								vt = --dem;
								display_words(currentword, vitridau);
								highlight_words(ds[dem], 85, 10 + vt, 112, s);
							}
						}
						/*else if (vitridau >1&&vt==-3)
						{
							vitridau-=1;		
							display_words(currentword, vitridau);
							highlight_words(ds[dem], 85, 10 + vt, 15, s);
							dem--;
							highlight_words(ds[dem], 85, 10 + vt, 112, s);							
						}
						else if (vitridau == 1 && vt == -3)
						{
							vt = 22;
							vitridau = 0;
							highlight_words(ds[dem], 85, 10 + vt, 15, s);
							dem--;
							highlight_words(ds[dem], 85, 10 + vt, 112, s);
						}*/
						else
						{
							highlight_words(ds[dem], 85, 10 + vt, 15, s);//xoa highlight cu
							if (dem == danhdau )
								vt -= 2;
							else
							vt--;
							dem--;
							highlight_words(ds[dem], 85, 10 + vt, 112, s);
						}
						//gotoxy(0, 0); cout << vitridau << " " << vt << " " << dem;
					}
					else if (key_tab == DEL)
					{
						if (dem < currentword->word.list_mean.solienket()&& currentword->word.list_mean.solienket()>1)
						{
							string tb = "BAN CO MUON XOA NGHIA \"";
							tb += ds[dem];
							tb += "\" HAY KHONG ? (Y/N)";
							//bool thoat = false;
							while (1) {
								thongbao(tb, x_thongbao, y_thongbao);
								char key_tab_del = GetKey();
								if (key_tab_del == 89 || key_tab_del == 121)
								{

									int kt = 0;//kieem tra tu do ow dau
									for (Mean *i = currentword->word.list_mean.mean_Head; i != NULL; i = i->pNext)
									{
										if (seach_str(i->mean, ds[dem]) == true) {
											kt++;
											break;
										}
										kt++;
									}
									currentword->word.list_mean.Delete_Mean(kt);
									for (int i = dem; i < ts - 1; i++)
									{
										ds[i] = ds[i + 1];
									}
									if (dem == ts - 1)
									{
										dem--;
									}
									danhdau--;
									//gotoxy(0, 0);
									//cout << danhdau;
									if (dem == danhdau)
									{
										vt += 1;
									}
									ts--;
									display_words(currentword, 0);
									highlight_words(ds[dem], 85, 10 + vt, 112, s);

									break;
								}
								else if (key_tab_del == 78 || key_tab_del == 110) {// trả chuột về thanh tìm kiếm
									if (s.size() > 40)
										gotoxy(72, 7);
									else
										gotoxy(33 + s.size(), 7);
									break;
								}
							}
						}
					}
				}
			}
			huong_dan_chinh();
		}
		/*======================THEM 1 TU====================*/
		else if (key == INS)
		{
			huong_dan_them();
			WordNodes *p = Insert_word();
			if (p != NULL)
			{
				cls1(9, 36, 21);
				Insert_dictionary(dic, p);
				//highlight(currentword, 33, 9 + vitri, 7);
				currentword = dic[Test_Hashdish_Next(-1, dic)].pHead;
				vitri_hienthidau = -1;
				vitri = 0;
				display_Hashdic(dic, vitri_hienthidau, vitri_hienthicuoi, s);
				highlight(currentword, 33, 10 + vitri++, 240);
				display_words(currentword,0);
			}
			huong_dan_chinh();
		}
		/*========================XOA 1 TU==============================*/
		else if (key == DEL)
		{
			huong_dan_xoa();
			if (currentword != NULL)
			{
				WordNodes *temp;
				temp = currentword->Next;
				if (temp == NULL && Test_Hashdish_Next(HashFirst(currentword), dic) == -1 && Test_Hashdish_Pre(HashFirst(currentword), dic) == -1 && (dic[HashFirst(currentword)].pHead == dic[HashFirst(currentword)].pTail))
				{//trường hợp từ điển chỉ có 1 từ
					string tb = "BAN CO CHAC CHAN MUON XOA TU \"";
					tb += currentword->word.English;
					tb += "\" HAY KHONG? (Y/N) ";
					while (1) {
						thongbao(tb, x_thongbao, y_thongbao);
						char key_del = GetKey();
						if (key_del == 89 || key_del == 121)
						{
							tb = "";
							tb = "BAN DA XOA TU \"";
							tb += currentword->word.English;
							tb += "\" ";
							cls1(9, 36, 21);//xoa khung ben phai
							cls1(6, 36, 81);
							dic[HashFirst(currentword)].pHead = dic[HashFirst(currentword)].pTail = NULL;//xoas phan tu duy nhat
							delete currentword;//xoa vung nho
							currentword = NULL;//tra ve NULL
							thongbao(tb, x_thongbao, y_thongbao);
							break;
						}
						else if (key_del == 78 || key_del == 110)
						{
							break;
						}
					}
				}
				else {
					if (temp != NULL)
					{
						if (lookup_str(s, temp->word.English) == false)
						{
							if (lookup_str(s, currentword->Pre->word.English) == true)
							{
								temp = currentword->Pre;
								if (vitri_hienthidau != -1) {
									vitri_hienthidau -= 1;

								}
								else {
									vitri--;
								}
							}
							else
								temp = NULL;
						}

					}
					else if (temp == NULL)
					{
						if (s == "")
						{
							if (Test_Hashdish_Next(HashFirst(currentword), dic) != -1)
							{
								temp = dic[Test_Hashdish_Next(HashFirst(currentword), dic)].pHead;
							}
							else
							{
								if (dic[HashFirst(currentword)].pHead != dic[HashFirst(currentword)].pTail) {
									temp = currentword->Pre;
									if (vitri_hienthidau != -1) {
										vitri_hienthidau -= 1;
										////gotoxy(0, 3); cout << vitri_hienthidau;
									}
									else {
										vitri--;
									}
								}
								else {
									if (vitri_hienthidau != -1) {
										vitri_hienthidau -= 1;
										////gotoxy(0, 3); cout << vitri_hienthidau;
									}
									temp = dic[Test_Hashdish_Pre(HashFirst(currentword), dic)].pTail;
								}
							}
						}
						else
						{
							if (currentword->Pre != NULL) {
								if (lookup_str(s, currentword->Pre->word.English) == true)
								{
									temp = currentword->Pre;
								}
								else
									temp = NULL;
							}
							else
								temp = NULL;
						}
					}

					while (1) {
						string tb = "BAN CO CHAC CHAN MUON XOA TU \"";
						tb += currentword->word.English;
						tb += "\" HAY KHONG? (Y/N) ";
						thongbao(tb, x_thongbao, y_thongbao);
						char key_del = GetKey();
						if (key_del == 89 || key_del == 121)
						{
							tb = "";
							tb = "BAN DA XOA THANH CONG TU\"";
							tb += currentword->word.English;
							tb += "\" ";
							Delete_word(dic, currentword);
							if (temp != NULL) {
								currentword = temp;
								cls1(9, 36, 21);
								display_Hashdic(dic, vitri_hienthidau, vitri_hienthicuoi, s);
								int dem = 0;//xu li vi tri
								WordNodes *k;
								for (k = dic[Test_Hashdish_Next(-1, dic)].pHead; k != NULL; k = Nextword(k, dic))
								{
									if (lookup_str(s, k->word.English) != false)
										break;
								}
								for (k; k != NULL && lookup_str(s, k->word.English) != false; k = Nextword(k, dic)) dem = dem + 1;
								if (vitri >= dem) vitri = dem;
								////gotoxy(0, 1); cout << vitri << " " << dem;

								highlight(currentword, 33, 9 + vitri, 240);
								display_words(currentword,0);
							}
							else {
								cls1(9, 36, 21);
								cls1(6, 36, 81);
								currentword = NULL;
							}
							thongbao(tb, x_thongbao, y_thongbao);
							break;
						}
						else if (key_del == 78 || key_del == 110)
						{
							break;
						}
					}
				}
			}
			huong_dan_chinh();
		}
		else if (key == KEY_DOWN)
		{
			if (currentword != NULL)
			{
				highlight(currentword, 33, 9 + vitri++, 7);	//xoas vi tri cu							
				if (Nextword(currentword, dic) == NULL )//|| lookup_str(s, Nextword(currentword, dic)->word.English) == false)
				{
					vitri--;
				}
				else
					currentword = Nextword(currentword, dic);
				if (vitri > 24)
				{
					vitri = 24;
					vitri_hienthidau += 1;
					vitri_hienthicuoi;
					cls1(9, 36, 21);
					display_Hashdic(dic, vitri_hienthidau, vitri_hienthicuoi, s);
					gotoxy(0, 1); cout << vitri_hienthidau;
				}
				/*if (lookup_str(s, currentword->word.English) == false) {
					currentword = Preword(currentword, dic);
					vitri--;
				}*/
				
				highlight(currentword, 33, 9 + vitri, 240);
				display_words(currentword,0);
			}
		}
		else if (key == KEY_UP) {
			if (currentword != NULL) {
				highlight(currentword, 33, 9 + vitri--, 7);//xoa highlight dòng cũ				
				if (Preword(currentword, dic) == NULL )//|| lookup_str(s, Preword(currentword, dic)->word.English) == false)//quan trọng, hết từ hoặc không tim được từ
					vitri += 1;//trả về giá trị 2 để sử dụng cho highlight phía dưới
				else
					currentword = Preword(currentword, dic);
				int dem1 = 0;
				
				if (vitri < 1)
				{
					if (vitri_hienthidau == -1) {
						for (WordNodes *p = dic[Test_Hashdish_Next(-1, dic)].pHead; p != NULL; p = Nextword(p, dic))
						{
							dem1++;
							if (lookup_str(s, p->word.English) == true)
							{
								vitri_hienthidau += dem1 - 1;
								break;
							}
						}
					}
					vitri = 1;
					vitri_hienthidau -= 1;
					gotoxy(0, 0); cout << vitri_hienthidau;
					cls1(9, 36, 21);
					display_Hashdic(dic, vitri_hienthidau, vitri_hienthicuoi, s);

				}
				
				/*if (lookup_str(s, currentword->word.English) == false)
				{
					currentword = Nextword(currentword, dic);
					vitri += 1;
				}*/
				highlight(currentword, 33, 9 + vitri, 240);
				display_words(currentword,0);
			}

		}

		else {
			cls1(9, 36, 21);//xoa khung ben trai
			int digital = 0;
			gotoxy(33, 7);
			vitri = 1;
			s = insert_string_find(s, 33, 7, key);
			if (Test_Hashdish_Next(-1, dic) != -1) {// tinhs towis truowngf howp hoong co tu nao tron
				if (s == "")
				{
					currentword = dic[Test_Hashdish_Next(-1, dic)].pHead;
					vitri_hienthidau = -1;
					vitri = 0;
					display_Hashdic(dic, vitri_hienthidau, vitri_hienthicuoi, s);
					highlight(currentword, 33, 10 + vitri++, 240);
					display_words(currentword,0);
				}
				else {
					vitri_hienthidau = -1;//chua chawc
					int index = s[0] - 97;
					int temp = 0;
					//for (WordNodes *j = dic[index].pHead; j != NULL; j = j->Next) {//lay tu dau tien tim duoc

					//	if (lookup_str(s, j->word.English) == true) {
					//		currentword = j;
					//		break;
					//	}
					//}
					int dem1 = 0;
					for (WordNodes *j = dic[Test_Hashdish_Next(-1, dic)].pHead; j != NULL; j = Nextword(j, dic))
					{
						dem1++;
						if (lookup_str(s, j->word.English) == true)
						{
							currentword = j;
							break;
						}
						
					}
					display_Hashdic(dic, dem1-2, vitri_hienthicuoi, s);
					for (WordNodes *i = dic[index].pHead; i != NULL; i = i->Next)//xuat danh sach tu tim duoc
					{
						//if (lookup_str(s, i->word.english) == true) {
							//gotoxy(33, 9 + ++digital);
							//cout << i->word.english;
						//}
						
					}
					if (dem1 == 0)//kt co tim duoc tu khong
					{
						gotoxy(33, 10);
						cout << "khong tim thay tu";
						currentword = NULL;
						cls1(6, 36, 81);
					}
					else
					{
						highlight(currentword, 33, 10, 240);
						display_words(currentword,0);
					}

				}
			}
			else {
				gotoxy(33, 10);
				cout << "DACH SACH DANG CAP NHAT";
				currentword = NULL;
				cls1(6, 36, 81);
			}
		}
		if (s.size() > 40)
			gotoxy(72, 7);
		else
			gotoxy(33 + s.size(), 7);
	}
}
//========================thao tac voi file=================
void Readline(string line, WordNodes *&data)
{
	string s = "";
	int i = 0;
	while (line[i] != '|')
	{
		s += line[i];
		i++;

	}
	s = fixtext(s);// phong truong hop khi nguoi dung sua file
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
				s = fixtext(s);
				data->word.list_mean.Insert_Last_Mean(s);
				s = ""; //bỏ dấu ","
			}
		}

		i++;
	}
	s = fixtext(s);
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
		s = fixtext(s);
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
			Readline(line, data);
			Insert_dictionary(dic, data);
		}
	}
}
void output_file(ofstream &fileout, Hash_Dic *dictionary)
{
	for (int i = 0; i < 26; i++)
	{
		for (WordNodes *p = dictionary[i].pHead; p != NULL; p = p->Next)
		{
			fileout << p->word.English << "|";
			fileout << p->word.style << "|";
			for (Mean *j = p->word.list_mean.mean_Head; j != p->word.list_mean.mean_Tail&&j!=NULL; j = j->pNext)
				fileout << j->mean << ",";
			fileout << p->word.list_mean.mean_Tail->mean;
			fileout << "|";
			for (int k = 0; k < p->word.exemple.n; k++)
			{
				fileout << *p->word.exemple.Node[k] << ",";
			}
			fileout << endl;
		}
	}
}
//void output(Hash_Dic *&dic)
//{
//	for (int l = 0; l < 26; l++)
//	{
//		for (WordNodes *i = dic[l].pHead; i != NULL; i = i->Next)
//		{
//			display_words(i,0);
//		}
//	}
//}
void giaiphongbonho(Hash_Dic *&dic)
{
	for (int i = 0; i < 23; i++)
	{
		WordNodes *j = dic[i].pHead;
		while (j != NULL)
		{
			j = j->Next;
			delete dic[i].pHead;
			dic[i].pHead = j;
		}
	}
}
int main()
{
	thongtinchung();
	Hash_Dic *dic;
	dic = new Hash_Dic[26];
	ifstream filein;
	filein.open("dic1.txt", ios::in);
	input_file(filein, dic);	
	filein.close();
	find_str(dic);
	ofstream of;
	of.open("dic1.txt", ios::out);
	output_file(of, dic);
	of.close();
	giaiphongbonho(dic);
	delete[] dic;
	return 0;
}

#ifndef Lib_H
#define Lib_H

#include <iostream>
#include <conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include "mylib.h"
#include <sstream>
#include <cmath>

using namespace std;

#define key_up 1072
#define key_dw 1080
#define key_left 1075
#define key_right 1077
#define key_alt 27
#define key_esc 27
#define key_enter 13
#define key_delete 8
#define key_tab 9
#define key_space 32
#define rong 0

#define so0 48





#define Black			0
#define DarkBlue		1
#define DarkGreen		2
#define DarkCyan		3
#define DarkRed			4
#define DarkPink		5
#define DarkYellow		6
#define DarkWhite		7
#define Grey			8
#define Blue			9
#define Green			10
#define Cyan			11
#define Red				12
#define Pink			13
#define Yellow			14
#define White			15



#define SODONGCHT 3





void TextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}

void gotoXY(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void PutCharXY(int x, int y,const char* KyTu, int color)
{
    gotoXY(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf(KyTu);
}

void vekhung(int x,int y,int h,int w)
{
    cout.fill(196);
    gotoXY(x,y);
    cout<<char(218)<<setw(w)<<char(196)<<char(191);
    cout.fill(' ');
    for(int i=1; i<=h; ++i)
    {
        gotoXY(x,y+i);
        cout<<char(179)<<setw(w)<<' '<<char(179);
    }
    gotoXY(x,y+h+1);
    cout.fill(196);
    cout<<char(192)<<setw(w)<<char(196)<<char(217);
}

//ham bat mot phim
int getKey()
{
    int key = _getch();
    if(key==224)
        key=_getch()+1000;
    return key;
}

int menu(int x,int y,char a[][70],int soluongmenu)
{
    ShowCur(false);
    int key = 0; // luu gia tri phim duoc nhan
    int menuduocchon = 0;// luu menu dang duoc chon
    do
    {
        //in ra menu
        TextColor(DarkWhite);
        for	(int i =0; i<soluongmenu; ++i)
        {
            vekhung(x-1,y+3*i-1,1,60);
            gotoXY(x,y+3*i);
            cout<<a[i]<<endl;
        }
        //chon mau va to nen cho menu duoc chon
        TextColor(Blue);
        gotoXY(x,y+3*menuduocchon);
        cout<<a[menuduocchon]; // in lai menu duoc chon

        key = getKey(); // bat phim

        switch(key)
        {
        case key_up:
        {
            if(menuduocchon>0)
                menuduocchon--; // truong hop menu dang tren dau
            break;
        }
        case key_dw:
        {
            if(menuduocchon < soluongmenu-1)
                menuduocchon++;//truong hop menu duoi cuoi dung
            break;
        }
        case key_enter:
        {
            return menuduocchon; // tra ra gia tri menu dang duoc chon
            break;
        }
        }
    }
    while(key!=key_esc);

    return -1;
}
int menu_function(int x,int y,char a[3][70],int soluongmenu)
{
    ShowCur(false);
    int key = 0; // luu gia tri phim duoc nhan
    int menuduocchon = 0;// luu menu dang duoc chon
    do
    {
        //in ra menu
        TextColor(DarkWhite);
        for	(int i =0; i<soluongmenu; ++i)
        {
            vekhung(x-1,y+3*i-1,1,35);
            gotoXY(x,y+3*i);
            cout<<a[i]<<endl;
        }
        //chon mau va to nen cho menu duoc chon
        TextColor(Blue);
        gotoXY(x,y+3*menuduocchon);
        cout<<a[menuduocchon]; // in lai menu duoc chon

        key = getKey(); // bat phim

        switch(key)
        {
        case key_up:
        {
            if(menuduocchon>0)
                menuduocchon--; // truong hop menu dang tren dau
            break;
        }
        case key_dw:
        {
            if(menuduocchon < soluongmenu-1)
                menuduocchon++;//truong hop menu duoi cuoi dung
            break;
        }
        case key_enter:
        {
            return menuduocchon; // tra ra gia tri menu dang duoc chon
            break;
        }
        }
    }
    while(key!=key_esc);
    return -1;
}
int menu_xoa(int x,int y,char a[4][30],int soluongmenu)
{
    ShowCur(false);
    int key = 0; // luu gia tri phim duoc nhan
    int menuduocchon = 0;// luu menu dang duoc chon
    do
    {
        //in ra menu
        TextColor(White);
        for	(int i =0; i<soluongmenu; ++i)
        {
            gotoXY(x,y+1*i);
            cout<<a[i]<<endl;
        }
        //chon mau va to nen cho menu duoc chon
        TextColor(Red);
        gotoXY(x,y+1*menuduocchon);
        cout<<a[menuduocchon]; // in lai menu duoc chon

        key = getKey(); // bat phim

        switch(key)
        {
        case key_up:
        {
            if(menuduocchon>0)
                menuduocchon--; // truong hop menu dang tren dau
            break;
        }
        case key_dw:
        {
            if(menuduocchon < soluongmenu-1)
                menuduocchon++;//truong hop menu duoi cuoi dung
            break;
        }
        case key_enter:
        {
            return menuduocchon; // tra ra gia tri menu dang duoc chon
            break;
        }
        }
    }
    while(key!=key_esc);
    return -1;
}

void BaoLoi (char *s,int x, int y)
{
    TextColor(Red);
    gotoXY (x,y);
    cout <<s;
    Sleep(2000);
    gotoXY(x,y);
    for(int i =0; i<strlen(s); i++)
        cout<<" ";
    TextColor(White);
}

void ThanhCong (char *s,int x, int y)
{
    TextColor(Green);
    gotoXY (x,y);
    cout <<s;
    Sleep(2000);
    gotoXY(x,y);
    for(int i =0; i<strlen(s); i++)
        cout<<" ";
    TextColor(White);
}


void strdelete(char *s,int vt,int sl)
{
    int n=strlen(s),i;
    for (i=vt; i<=n-sl; ++i)
        s[i]=s[i+sl];
}

char* ChuanHoa(char a[])
{
    int i;
    while(a[strlen(a)-1]==' ')// xoa het cac ki tu trong o cuoi chuoi
        a[strlen(a)-1]=0;
    while(a[0]==' ')          //xoa het cac ki tu trong o dau chuoi
        strdelete(a,0,1);

    i=0;
    while(i<strlen(a))                //xoa hai ki tu trong lien tiep
        if((a[i]==' ')&&(a[i+1]==' '))
            strdelete(a,i,1);
        else ++i;

    return a;
}

char* string_to_charptr(string s)
{
    char cstr[s.size() + 1];

    copy(s.begin(), s.end(), cstr);
    cstr[s.size()] = '\0';
    char* str =ChuanHoa(cstr);

    return str;
}

string ChuanHoaString(string s)
{
    char cstr[s.size() + 1];

    copy(s.begin(), s.end(), cstr);
    cstr[s.size()] = '\0';
    char* str =ChuanHoa(cstr);

    return string(str);
}


bool KiemTraChuoiRong(string s)
{
    s= ChuanHoaString(s);
    if(s.length()==0)
        return true;
    return false;
}

string DateFormat(string s)
{
    string dd,mm,yy;
    dd= s.substr(0,2);
    mm= s.substr(2,2);
    yy=s.substr(4,7);
    return s=dd+"/"+mm+"/"+yy;
}

string replaceAll(string subject, const string& search, const string& replace)
{
    size_t pos = 0;
    // Hàm find sẽ trả về string::npos nếu không tìm thấy chuỗi con.
    while ((pos = subject.find(search, pos)) != string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

string DoiGioiTinh(string s)
{
    if(s=="NAM")
        return "0";
    if(s=="NU")
        return "1";
}

bool emptyFile(ifstream& pFile)
{
    // return pFile.peek() == ifstream::traits_type::eof();
}


char* encrpyt (char *str)
{
    for(int i = 0; (i < 100 && str[i] != '\0'); i++)
        str[i] = str[i] + 2; //the key for encryption is 3 that is added to ASCII value
    return str;

}

char* decrpyt (char *str)
{
    for(int i = 0; (i < 100 && str[i] != '\0'); i++)
        str[i] = str[i] - 2; //the key for encryption is 3 that is subtracted to ASCII value
    return str;

}
void gotoxy(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void clearErr(int x, int y)
{
    gotoxy(x,y);
    cout<<"                                                                                                                                                                  ";
}
void clearErrDateKhoiHanh(int x, int y)
{
    gotoxy(x,y);
    cout<<"           ";
}
void clearErrTTHK(int x, int y)
{
    gotoxy(x,y);
    cout<<"                        ";
}

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void clreol( )
{
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;
    FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
                                info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
    gotoxy (info.dwCursorPosition.X, info.dwCursorPosition.Y );
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void clrscr()
{
    system("cls");
}
/*void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}*/
void VeHCN(int x, int y, int width, int height)
{
    gotoxy(x,y);
    cout<<char(218);
    gotoxy(x+width, y);
    cout<<char(191);
    gotoxy(x, y+height);
    cout<<char(192);
    gotoxy(x+width, y+height);
    cout<<char(217);

    gotoxy(x,y);
    for(int i = x+1; i<=(x+width-1); i++)
    {
        gotoxy(i,y);
        cout<<char(196);
    }
    gotoxy(x,y+height);
    for(int i = x+1; i<=(x+width-1); i++)
    {
        gotoxy(i,y+height);
        cout<<char(196);
    }
    gotoxy(x,y);
    for(int i = y+1; i<=(y+height-1); i++)
    {
        gotoxy(x,i);
        cout<<char(179);
    }
    gotoxy(x+width,y);
    for(int i = y+1; i<=(y+height-1); i++)
    {
        gotoxy(x+width,i);
        cout<<char(179);
    }
}
void AlertErr(int x, int y, char *s)
{
    gotoxy(x,y);
    SetColor(12);
    SetBGColor(0);
    cout<<s;
    SetColor(15);
}
void DelSpace(char *s)
{
    int i,n,j;
    n=strlen(s); // tinh do dai chuoi
    for(i=0; i<n; i++)
    {

        if((s[0]==' ') || ((s[i]==' ')&&(s[i+1]==' ') ))
        {
            for(j=i; j<n-1; j++)
            s[j]=s[j+1];
            n--;
            i--;
        }
    }
    s[i]=0;
}
void vekhungMayBay()
{
    ShowCur(false);
    TextColor(0x0004);
    system("cls");
 //   show_tittle();
    TextColor(Green);
    SetColor(15);
    TextColor(White);

    vekhung(20,0,2,10);
    gotoXY(22,2);
    cout<<"F3: EDIT";

    vekhung(58,0,2,12);
    gotoXY(60,2);
    cout<<"F4: DELETE";

    vekhung(96,0,2,12);
    gotoXY(98,2);
    cout<<"ESC: EXIT";



    vekhung(3,4,2,10);
    vekhung(13,4,2,30);
    vekhung(43,4,2,30);
    vekhung(73,4,2,12);
    vekhung(86,4,2,12);
    vekhung(3,6,20,10);
    vekhung(13,6,20,30);
    vekhung(43,6,20,30);
    vekhung(73,6,20,12);
    vekhung(86,6,20,12);


    TextColor(Green);
    gotoXY(4,5);
    cout<<"STT ";
    gotoXY(15,5);
    cout<<"SO HIEU MAY BAY ";
    gotoXY(45,5);
    cout<<"LOAI MAY BAY";
    gotoXY(75,5);
    cout<<"SO DAY";
    gotoXY(87,5);
    cout<<"SO DONG";
   // vekhung(3,28,1,96);
   // PutCharXY(4,29,"<-: TRANG TRUOC | \t\t \t\t \t| TRANG SAU :->",Green);
  //  TextColor(White);
  //  gotoXY(45,29);
  //  cout<<"TRANG: ";

}
 void HighLight () {
	SetColor(Cyan);
	SetBGColor(Grey);
}
 void Normal () {
	SetColor(White);
	SetBGColor(Black);
}

//===================== VALIDATION===========
void NhapChuoi ( char *S,int x,int y) {
    fflush(stdin);
    do
    {
        gotoxy(x,y);
       gets(S);

    }
    while (strcmp(S,"")==0) ;
}
void nhapInt(int k,int x,int y)
{
    int len = 0;
    do{
    gotoxy(x,y);
    cin>>k;
    len = log10(k) + 1;
    }
    while(len == NULL);
}
int inputNum(char *num,int n){
	int i=0;
	char  getnum;
	while(1)
	{
		//(getnum=getch())!=13 && getnum!=27
		getnum=getch();
		if(getnum==key_delete && i>0){
			i--;
			printf("\b \b");
		}
		else if(getnum>='0'&&getnum<='9'&&i<n)
		{
			num[i]=getnum;
			putchar(getnum);
			i++;
		}
		if(getnum == key_enter && i==n) break;
		if(getnum== key_alt ) return -1;
	}
	num[i]=0;
	return 1;
}

int inputNum_noN(char *num){
	int i=0;
	char  getnum;
	while(1)
	{
		//(getnum=getch())!=13 && getnum!=27
		getnum=getch();
		if(getnum==8 && i>0){
			i--;
			printf("\b \b");
		}
		else if(getnum>='0'&&getnum<='9')
		{
			num[i]=getnum;
			putchar(getnum);
			i++;
		}
		if(getnum == key_enter && i>0) break;
		if(getnum== key_alt) return -1;
	}
	num[i]=0;
	return 1;
}
void CursorStatus(unsigned size, WINBOOL stt) {
    CONSOLE_CURSOR_INFO crs_inf = {size, stt};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &crs_inf);
}
void Color(int x) {
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, x);
}
void Get_Date() {
    time_t rawtime;
    struct tm * timeinfo;

    rawtime = time(NULL);
    timeinfo = localtime(&rawtime);
    cout << timeinfo->tm_mday << "/" << timeinfo->tm_mon+1 << "/" << timeinfo->tm_year - 100 + 2000;

}
void Get_Hour() {
    time_t rawtime;
    struct tm * timeinfo;

    rawtime = time(NULL);
    timeinfo = localtime(&rawtime);
    cout << timeinfo->tm_hour << ":" << timeinfo->tm_min;

}
void delLine(int x, int y, int leng) {
    gotoxy(x, y);
    for (int i = 1; i <= leng; i++) {


        cout << " ";
    }
    gotoxy(x, y);

}
// check nhap cb
int check_Chuoi_Char(char ma[])
{
	for(int i = 0; i < strlen(ma); i++){
		if (!isdigit(ma[i]))
			return -1;
	}
	return 1;
}

int inputNum(char *&num,int n){
	int i=0;
	char  getnum;
	while(1)
	{
		//(getnum=getch())!=13 && getnum!=27
		getnum=getch();
		if(getnum==key_space && i>0){
			i--;
			printf("\b \b");
		}
		else if(getnum>='0'&&getnum<='9'&&i<n)
		{
			num[i]=getnum;
			putchar(getnum);
			i++;
		}
		if(getnum == key_enter && i==n) break;
		if(getnum==key_esc) return -1;
	}
	num[i]=rong;
	return 1;
}



#endif

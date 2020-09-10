#include<conio.h>
#include<stdio.h>
#include<iostream>
#include <ctime>
#include <cstring>
#include<stdlib.h>
#include<math.h>
#include"mylib.h"
#include<Windows.h>

using namespace std;


const int dong =5;
const int cot = 10 ;
const int Up = 72;
const int Down = 80;
const int item_menu=8;
const int ESC = 27;
const int Enter = 13;
const int Left = 75;
const int Right = 77;
const int MAXMB = 300;
const int backspace  = 8;
const int checkDay = 5;
const int checkDong = 20;
const int F2 = 60;
const int F3 = 61;
const int F4 = 62;
const int F5 = 63;
const int numPageCB = 10;
const int numPageMB = 10;
const int numPageCBHK = 10;
const int setupTimeCB = 2880;
//const int setupTimeDatCB = 2880; // 2 ngay
const int setupTimeDatSHMB = 7200; // 5 ngay
char *FileDSMB = "DSMB.txt";
char *FileDSCB = "DSCB.txt";
char *FileDSKH = "DSKH.txt";
//================KHAI BÁI STRUCT================
struct MayBay
{
    char SoHieuMB[15];
    char LoaiMB[40];
    int soDay;
    int soDong;
};

struct listMB
{
    int n;
    MayBay *nodes[MAXMB];
};
typedef struct listMB LISTMB;

struct Date
{
    int min;
    int hour;
    int day;
    int month;
    int year;

};
struct Ve
{
    char ViTriNgoi[5];
    char CMND[11];
};

struct ChuyenBay
{
    char MaCB[15];
    Date NgayKhoiHanh;
    char SanBayDen[50];
    int TrangThai;
    char SoHieuMB[15];
    int SoVeDaDat;
    int MaxVe;
    Ve *dsVe;
};

struct ListCB
{
    ChuyenBay CB;
    ListCB *next;
};
typedef struct ListCB *NODECB;// định nghĩa khai báo về sau khỏi cần phải *
struct ThongTinKH
{
    char CMND[11];
    char Ho[30];
    char Ten[30];
    char Phai[5];
};
struct KhachHang
{
    ThongTinKH data;
    KhachHang* left;
    KhachHang* right;
} ;
typedef struct KhachHang *BSTKH;
//=============================================


//============================================QUAN LI MAY BAY=====================================
int empty(LISTMB &LMB)
{
    return LMB.n==0;
}
int Full_MB(LISTMB &LMB)
{
    if(LMB.n == MAXMB)
    {
        return 0;
    }
    else
        return 1;
}
int NhapMa(char *Ma)
{
    int i=0;
    char ch;
    while(1)
    {
        ch=getch();
        if(ch==backspace && i>0) //8:SPACE
        {
            i--;
            printf("\b \b");
        }
        if((ch>='A' && ch<='Z' && i<14) || (ch-48>=0 && ch-48<=9 && i<14))// i = ma toi da 14 ki tu, 48=0, chi nhan ki tu hoa va so
        {
            Ma[i]=ch;
            putchar(ch);// xuat ki tu
            i++;
        }
        else if(ch==Enter && i >0)// chuyen dong
            break;
        else if(ch==ESC)
            return -1;
    }
    Ma[i]=0; // 0 = NULL
    return 1;
}
void NhapTenKh(char *Ma)
{
    int i=0;
    char ch;
    while(1)
    {
        ch=getch();
        if(ch==backspace && i>0) //8:SPACE
        {
            i--;
            printf("\b \b");
        }
        if((ch>='A' && ch<='Z' && i<14))// i = ma toi da 14 ki tu, 48=0, chi nhan ki tu hoa va so
        {
            Ma[i]=ch;
            putchar(ch);// xuat ki tu
            i++;
        }
        else if(ch==Enter && i >0)// chuyen dong
            break;

    }
    Ma[i]=0; // 0 = NULL

}
MayBay *TimMayBayTheoMa(LISTMB LMB,char Ma[])
{
    for(int i=0; i<LMB.n; i++)
    {
        if(strcmp(Ma,LMB.nodes[i]->SoHieuMB) == 0)
        {
            return LMB.nodes[i];
        }
    }
    return NULL;
}

int kiemtra_trungma(LISTMB LMB,string s)
{
    for(int i =0; i<LMB.n; i++)
    {
        if(s == LMB.nodes[i]->SoHieuMB)
        {
            return i;
        }
    }
    return -1;
}
string tao_ma_maybay(LISTMB LMB)
{
    string a = "MB0000";
    do
    {
        for(int i = 2; i<a.length(); i++)
        {
            a[i] = rand()% (57-48+1) +48; // 57 = 9, 48 =0
        }

    }
    while(kiemtra_trungma(LMB,a)>=0);
    return a;
}

int SearchMB(LISTMB &LMB,char *sh)
{
    for(int i=0; i<LMB.n; i++)
    {
        if(strcmp(sh,LMB.nodes[i]->SoHieuMB)==0)
            return i;
    }
    return -1;
}
void GhiFileDSMB(char *fileName, LISTMB LMB)
{
    FILE * f;
    f = fopen(fileName,"w");
    if(f)
    {
        fprintf(f,"%-5d\n\n", LMB.n);
        for(int i=0; i<LMB.n; i++)
        {
            fprintf(f,"%s\n%s\n%d\n%d\n\n",LMB.nodes[i]->SoHieuMB, LMB.nodes[i]->LoaiMB, LMB.nodes[i]->soDay, LMB.nodes[i]->soDong);
        }
        fclose(f);
    }
    else
    {
        AlertErr(8,1,"Khong mo duoc file \"DSMB.txt\" de ghi!");
    }
}
void LoaiBoKiTuXuongDong(char *str)
{
    int l = strlen(str);// tinh do dai chuoi
    if(str[l-1]=='\n')
        str[l-1]='\0';
}
void DocFileDSMB(char *fileName, LISTMB &LMB)
{
    MayBay MB;

    FILE * f;

    f = fopen(fileName,"r");
    if(f)
    {
        fseek(f, 0, SEEK_END);// di chuyen vi tri con tro den vi tri cuoi
        if(ftell(f)==0) // trả ve so ki tu trong file
        {
            fclose(f);
            return;
        }
        fseek(f, 0, SEEK_SET);

        if(!feof(f))
        {
            fscanf(f,"%5d",&LMB.n);	//	cout<<LMB.n<<endl;
            for(int i=0; i<LMB.n; i++)
            {
                fscanf(f,"%s",&MB.SoHieuMB);
                fgets(MB.LoaiMB,40,f); // doc mot dong
                fgets(MB.LoaiMB,40,f);
                LoaiBoKiTuXuongDong(MB.LoaiMB);
                fscanf(f,"%d",&MB.soDay);
                fscanf(f,"%d",&MB.soDong);
                LMB.nodes[i] = new MayBay;
                *LMB.nodes[i] = MB;
            }
        }
        fclose(f);
    }
    else
    {
        AlertErr(8,1,"Khong mo duoc file \"DSMB.txt\"!");
    }
}
void NhapDSMB(LISTMB &LMB)
{

    MayBay MB;
    int key;
    SetColor(14);
    VeHCN(15,0,15,2);
    gotoxy(17,1);
    cout<<"ESC: QUAY LAI";
    gotoxy(15,5);
    cout<<"STT       |    So Hieu May Bay      |       Loai May Bay        |    So Day     |   So Dong"<<endl;
    gotoxy(15,6);
    cout<<"-------------------------------------------------------------------------------------------"<<endl;
    int current = 7;
    int stt =1;
    do
    {
        int check_full = Full_MB(LMB);
        if(check_full == 0)
        {
            AlertErr(8,4,"DANH SACH DA FULL || AN PHIM BAT KI DE THOAT!");
            Sleep(2000);
            clearErr(8,4);
        }
        else
        {
            clearErr(1,2);
            gotoxy(15,current);
            printf("%-10d", stt);
            stt++;
            cout<<"|                         |                           |               |              "<<endl;
            gotoxy(31,current);
SHMB:
            ;
            SetColor(14);
            clearErr(8,4);
            gotoxy(8,4);
            cout<<"NHAP SO HIEU MAY BAY:";

            gotoxy(31,current);
            if(NhapMa(MB.SoHieuMB)==-1)
                return;
            for(int i=0; i<LMB.n; i++)
            {

                if(SearchMB(LMB, MB.SoHieuMB)!=-1)
                {
                    AlertErr(8,4,"SO HIEU MAY BAY BI TRUNG!");
                    Sleep(2000);
                    clearErr(8,4);
                    gotoxy(31,current);
                    cout<<"                 ";
                    goto SHMB;
                }
            }
            clearErr(8,4);
            gotoxy(8,4);
            cout<<"NHAP LOAI MAY BAY :";
            gotoxy(57,current);
            fflush(stdin);
            NhapChuoi(MB.LoaiMB,57,current);
            DelSpace(MB.LoaiMB);


SODAY:
            ;
            clearErr(8,4);
            SetColor(14);
            gotoxy(8,4);
            cout<<"NHAP SO DAY:";
            gotoxy(86,current);

            char soDay[2];
            if(inputNum(soDay,1) == -1)
                return;
            MB.soDay = atoi(soDay);
            if(MB.soDay > checkDay)
            {
                AlertErr(8,4,"SO DAY KHONG DUOC HON 5!");
                Sleep(2000);
                clearErr(8,4);
                gotoxy(31,current);
                clearErr(8,4);
                gotoxy(86,current);
                cout<<"   ";
                goto SODAY;
            }

SODONG:
            ;
            clearErr(8,4);
            gotoxy(8,4);
            SetColor(14);
            cout<<"NHAP SO DONG:";
            gotoxy(100,current);

            char soDong[3];
            if(inputNum_noN(soDong) == -1)
                return;
            MB.soDong = atoi(soDong);
            if(MB.soDong > checkDong)
            {
                AlertErr(8,4,"SO DONG KHONG DUOC HON 20!");
                Sleep(2000);
                clearErr(8,4);
                gotoxy(31,current);
                clearErr(8,4);
                gotoxy(100,current);
                cout<<"     ";
                goto SODONG;
            }


            LMB.nodes[LMB.n] = new MayBay;
            *LMB.nodes[LMB.n++] = MB;
            current++;

            GhiFileDSMB(FileDSMB,LMB);
            clearErr(8,4);
            gotoxy(8,4);
            SetColor(14);
            cout<<"THEM MAY BAY THANH CONG, ENTER -> TIEP TUC THEM MAY BAY, NHAN PHIM BAT KI DE THOAT!";
        }
        key=getch();
    }
    while(key==Enter);


}
int Delete_Item_MB(LISTMB & LMB,int i)
{
    if(i < 0 || i >= LMB.n || LMB.n == 0)
        return 0;
    delete LMB.nodes[i];
    for (int j=i+1; j <LMB.n; j++)
        LMB.nodes[j-1]=LMB.nodes[j];
    LMB.n--;
    GhiFileDSMB(FileDSMB,LMB);
    return 1;
}

void DeleteMB(LISTMB &LMB, int i, NODECB LCB)
{
    NODECB p ;
    p =LCB;
    while(p!=NULL)
    {
        if(strcmp(LMB.nodes[i]->SoHieuMB, p->CB.SoHieuMB)==0)
        {
            AlertErr(15,4, "DA CO CHUYEN BAY DUOC TAO TREN MAY BAY NAY!");
            Sleep(2000);
            clearErr(15,4);
            return ;
        }
        p=p->next;
    }


    char confirm[10];
    gotoxy(15,4);
    TextColor(Green);
    cout<<"Nhan \"yes\" de xac nhan xoa may bay nay: ";
    cin>>confirm;

    if(strcmp(confirm,"yes")==0)
    {
        int kq = Delete_Item_MB(LMB,i);
        if(kq == 0)
        {
            clearErr(15,4);
            AlertErr(15,4, "Xoa May Bay that bai ");
            Sleep(3000);
            clearErr(15,4);
        }
        else
        {
            clearErr(15,4);
            gotoxy(15,4);
            cout<<"Xoa May Bay thanh cong!";
            Sleep(3000);
            clearErr(15,4);
        }

    }
    else
    {
        gotoxy(15,5);
        cout<<"Da huy yeu cau xoa may bay nay!";
        Sleep(1000);
    }
    system("cls");
}
void EditMB(LISTMB &LMB, int i, NODECB LCB)
{
    //cout<<LMB.nodes[i]->SoHieuMB;

    NODECB p ;
    p =LCB;
    while(p!=NULL)
    {
        if(strcmp(LMB.nodes[i]->SoHieuMB, p->CB.SoHieuMB)==0)
        {
            AlertErr(15,4, "DA CO CHUYEN BAY DUOC TAO TREN MAY BAY NAY!");
            Sleep(1000);
            clearErr(15,4);
            return ;
        }
        p=p->next;
    }


    TextColor(Blue);
    gotoxy(120,8);
    cout<<"CHINH SUA SO HIEU MAY BAY : "<<LMB.nodes[i]->SoHieuMB;
    gotoxy(120,10);
    cout<<"LOAI MAY BAY MOI : ";
    fflush(stdin);
    NhapChuoi(LMB.nodes[i]->LoaiMB,140,10);
    DelSpace(LMB.nodes[i]->LoaiMB);
SODAYNEW:
    ;
    SetColor(Blue);
    gotoxy(120,12);
    cout<<"SO DAY MOI : ";
    gotoxy(140,12);
    char soDaynew[2];
    if(inputNum(soDaynew,1)== -1)
        return;
    if(atoi(soDaynew) > checkDay)
    {
        AlertErr(120,4,"SO DAY KHONG DUOC HON 5!");
        Sleep(2000);
        clearErr(120,4);
        gotoxy(140,12);
        cout<<"    ";
        goto SODAYNEW;
    }
    LMB.nodes[i]->soDay = atoi(soDaynew);
SODONGNEW:
    ;
    SetColor(Blue);
    gotoxy(120,14);
    cout<<"SO DONG MOI : ";
    gotoxy(140,14);
    char soDongnew[3];
    if(inputNum_noN(soDongnew)== -1)
        return;
    if(atoi(soDongnew) > checkDong)
    {
        AlertErr(120,4,"SO DONG KHONG DUOC HON 20!");
        Sleep(2000);
        clearErr(120,4);
        gotoxy(140,14);
        cout<<"    ";
        goto SODONGNEW;
    }
    LMB.nodes[i]->soDong = atoi(soDongnew);
    GhiFileDSMB(FileDSMB,LMB);
    system("cls");
}
int InDSMB(LISTMB &LMB, NODECB LCB)
{
    int crtPage = 1;

BEGIN:
    ;

    SetColor(14);
    VeHCN(15,0,15,2);
    gotoxy(17,1);
    cout<<"F3: EDIT";
    VeHCN(55,0,15,2);
    gotoxy(57,1);
    cout<<"F4: DELETE";
    VeHCN(95,0,15,2);
    gotoxy(97,1);
    cout<<"ESC: EXIT";


    gotoxy(55,7);
    cout<<"DANH SACH MAY BAY";
    gotoxy(15,9);
    cout<<"STT       |    SO HIEU MAY BAY      |   LOAI MAY BAY           |   SO DAY      |   SO DONG"<<endl;
    gotoxy(15,10);
    cout<<"-------------------------------------------------------------------------------------------"<<endl;

LR:
    ;
    SetColor(14);
    VeHCN(55,25,10,2);
    gotoxy(57,26);
    cout<<"Page "<<crtPage;
    SetColor(15);
    int current = 0;
    int pages = LMB.n/ numPageMB;
    if(LMB.n%numPageMB>0)
        pages++;

    int y =11;
    if(!empty(LMB))
    {
        for(int i =(crtPage-1)*numPageMB; i<crtPage*numPageMB;)
        {
            gotoxy(15,y++);
            printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d\n",i+1,LMB.nodes[i]->SoHieuMB, LMB.nodes[i]->LoaiMB, LMB.nodes[i]->soDay,LMB.nodes[i]->soDong);
            if(++i == LMB.n) //
                break;
        }
        gotoxy(15,11);
        HighLight();
        int f = (crtPage-1)*numPageMB;
        printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",f+1,LMB.nodes[f]->SoHieuMB, LMB.nodes[f]->LoaiMB, LMB.nodes[f]->soDay,LMB.nodes[f]->soDong);

        int kytu;
        do
        {
            kytu = getch();
            switch (kytu)
            {
            case Up :
                if (current > 0)
                {
                    Normal();
                    gotoxy(15,11+current);// toa do vi tri dang dung
                    printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",current+f+1,LMB.nodes[current+f]->SoHieuMB, LMB.nodes[current+f]->LoaiMB, LMB.nodes[current+f]->soDay,LMB.nodes[current+(crtPage-1)*2]->soDong);
                    current --;
                    HighLight();
                    gotoxy(15,11+current);
                    printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",current+f+1,LMB.nodes[current+f]->SoHieuMB, LMB.nodes[current+f]->LoaiMB, LMB.nodes[current+f]->soDay,LMB.nodes[current+(crtPage-1)*2]->soDong);

                }
                break;
            case Down :
                if ((crtPage==pages && current+1 <numPageMB-(pages*numPageMB-LMB.n)) || (crtPage<pages && current+1 <numPageMB))
                {
                    Normal();
                    gotoxy(15,11+current);
                    printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",current+f+1,LMB.nodes[current+f]->SoHieuMB, LMB.nodes[current+f]->LoaiMB, LMB.nodes[current+f]->soDay,LMB.nodes[current+(crtPage-1)*2]->soDong);
                    current ++;
                    HighLight();
                    gotoxy(15,11+current);
                    printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",current+f+1,LMB.nodes[current+f]->SoHieuMB, LMB.nodes[current+f]->LoaiMB, LMB.nodes[current+f]->soDay,LMB.nodes[current+(crtPage-1)*2]->soDong);
                }
                break;
            case Right:
                if(crtPage<pages)
                {
                    crtPage++;
                    Normal();
                    for(int i =0; i< numPageMB; i++)
                        clearErr(1,11+i);

                    goto LR;
                }
                break;
            case Left:
                if(crtPage>1)
                {
                    crtPage--;
                    Normal();
                    for(int i =0; i< numPageMB; i++)
                        clearErr(1,11+i);
                    goto LR;
                }
                break;
            case F3:
            {
                EditMB(LMB, current+f, LCB); // node[i] = current +f
                goto BEGIN;
                break;
            }
            case F4:
            {
                DeleteMB(LMB, current+f, LCB);
                gotoxy(57,30);
                cout<<"TEST MAY BAY"<<LMB.n;
                if(LMB.n%numPageMB==0 && pages >1)
                {
                    crtPage--;

                }

                goto BEGIN;
                break;
            }

            case ESC:
                return ESC;
            }
        }
        while (1);
    }
    else
    {
        gotoxy(15,y++);
        cout<<"DANH SACH RONG, VUI LONG NHAP DANH SACH TRUOC KHI HIEU CHINH MAY BAY";

    }
    getch();

}



void UpdateMB(LISTMB &LMB, NODECB LCB)
{

    int soluongMeNu = 2;
    char menuMB_update [2][70] =
    {
        "1. THEM MAY BAY",
        "2. UPDATE MAY BAY"
    };
    int m;
    do
    {
        ShowCur(false);
        TextColor(0x0004);
        system("cls");

        TextColor(Green);
        vekhung(68,35,1,34);
        PutCharXY(70,36,"ESC: QUAY LAI | ENTER: XAC NHAN",Green);
        m = menu(55,10,menuMB_update,soluongMeNu);
        switch(m)
        {
        case 0:
        {
            system("cls");
            NhapDSMB(LMB);
        }
        break;
        case 1:
        {
            system("cls");
            InDSMB(LMB, LCB);
        }
        break;
        case ESC:
            return ;
        }
    }
    while(m!=-1);
}

//=========================================QUAN LÍ CHUYEN BAY======================

void Init(NODECB &LCB)
{
    LCB = NULL;
}
NODECB createCB(ChuyenBay CB)
{
    NODECB p;
    p = new ListCB;
    p->next = NULL;
    p->CB = CB;
    return p;
}
tm *currentTime()
{
    time_t currentTime = time(0); // lay date/time hien tai he thong, he thong k có time tra ve -1
    tm *crt = localtime(&currentTime); // trả về con trỏ tới cấu trúc tm biểu diễn local time
    return crt;
}
void xuatTimeCurrent()
{
    tm *crt = currentTime();

    int yearHT = crt->tm_year + 1900; // tm_year cchi tra ve 120
    int monthHT = crt->tm_mon + 1;
    int dayHT = crt->tm_mday;
    int hourHT =  crt->tm_hour;
    int minHT = crt->tm_min;
    TextColor(Green);
    gotoxy(30,1);
    cout<<"TIME HIEN TAI :"<<dayHT<<"/"<<monthHT<<"/"<<yearHT<<"\t"<<hourHT<<":"<<minHT;
}


bool checkYear(int year)
{
    // nam nhuan la nam chia het cho 400, chia het cho 4 & khong chia het cho 100
    return (((year % 4 == 0) && (year % 100 != 0)) ||
            (year % 400 == 0));
}
int Time(Date date)
{

    int y = date.year;
    int mth =date.month;
    int d=date.day;
    int h =date.hour;
    int m =date.min;

    tm *crt = currentTime();
    int year = crt->tm_year + 1900; // tm_year cchi tra ve 120
    int month = crt->tm_mon + 1;
    int day = crt->tm_mday;
    int hour =  crt->tm_hour;
    int min = crt->tm_min;
    //cout<< year <<endl <<month<<endl<<day<<endl;
    int sumDay = 0;
    int sumPhut = 0;
    bool flag = false;
    while(y>= year)
    {
        flag = true;
        if(y==year && mth == month)
        {
            sumDay += d-day;
            break;
        }
        else
        {
            if(month==1 || month==3 || month==5 || month== 7|| month==8 || month== 10|| month==12)
            {
                sumDay+= 31-day;
            }
            if(month==4 || month==6 || month==9 || month== 11)
            {
                sumDay+= 30-day;
            }
            if(month==2)
            {
                if(checkYear(year)== true)
                    sumDay +=29-day;
                else
                    sumDay +=28 - day;

            }
        }
        month++;
        day=0;
        if(month == 13)
        {
            year++;
            month =1;
        }
    }
    if(flag==true)
        sumPhut = sumDay*24*60 + (h-hour)*60 + m - min;
    return sumPhut;
}
int emptyLCB(NODECB LCB)
{
    return(LCB == NULL ? true : false);
}
int countCB(NODECB LCB)
{
    int count =0;
    NODECB p=LCB;
    while(p!=NULL)
    {
        p=p->next;
        count++;
    }
    return count;
}

void insertFirst(NODECB &LCB, ChuyenBay CB)
{
    NODECB p = createCB(CB);
    p->next = LCB;
    LCB = p;
}

void insertAfter(NODECB q, ChuyenBay CB)
{
    NODECB p;
    p=createCB(CB);
    p->next = q->next;
    q->next = p;
}
void insertOrder(NODECB &LCB, ChuyenBay CB)
{
    NODECB p,t,s; //p nut trc,q nut sau

    p = new ListCB;
    p->CB = CB;

    for(s = LCB ; s != NULL && strcmp(s->CB.MaCB,CB.MaCB) == -1; t=s,s=s->next);
    if(s == LCB)
    {
        p->next = LCB;
        LCB = p;
    }
    else
    {
        p->next = s;
        t->next = p;
    }


}
void insertOrder_TIME(NODECB &LCB, ChuyenBay CB)
{
    NODECB p,t,s; //p nut trc,q nut sau
    /*  q = NULL;

      for(p = LCB; p!=NULL && (strcmp(p->CB.MaCB, CB.MaCB)==-1); p=p->next)
          q=p;

      if(q==NULL)
          insertFirst(LCB, CB);
      else
          insertAfter(q, CB);
    */
    p = new ListCB;
    p->CB = CB;
    int getTime = Time(CB.NgayKhoiHanh);
    for(s = LCB ; s != NULL && Time(s->CB.NgayKhoiHanh) < getTime ; t=s,s=s->next);
    //for(s = LCB ;s != NULL && strcmp(s->CB.MaCB,CB.MaCB) == -1;t=s,s=s->next);
    if(s == LCB)
    {
        p->next = LCB;
        LCB = p;
    }
    else
    {
        p->next = s;
        t->next = p;
    }


}
void insert_Last(NODECB & First, ChuyenBay CB)
{
    NODECB p = new ListCB;
    p->CB = CB;
    p ->next = NULL;
    if(First == NULL)
    {
        First = p;
    }
    else
    {
        NODECB Last = First;
        for(; Last->next != NULL ; Last = Last ->next);
        Last ->next = p;
    }

}
void deleteFirst(NODECB &LCB)
{
    if(emptyLCB(LCB))
    {
        AlertErr(8,1,"Danh sach chuyen bay rong!");
    }
    else
    {
        NODECB p;
        p=LCB;
        LCB = LCB->next; //tro den dia chi phan tu sau
        delete(p);
    }

}
void deleteAfter(NODECB q)
{
    if(q==NULL || q->next==NULL)
    {
        AlertErr(8,4,"Khong co phan tu nao sau phan tu nay!");
    }
    else
    {
        NODECB p;

        p= q->next;
        //  q->next = q-> next->next;
        q->next = p->next;
        delete p;
    }
}
void deleteAll(NODECB &LCB)
{
    NODECB p;
    p=LCB;
    while(LCB!=NULL)
    {
        p=LCB;
        LCB=LCB->next;
        delete p;
    }
}

NODECB searchCB(NODECB LCB, char *MaCB)
{
    NODECB p;
    for(p=LCB; p!=NULL ; p=p->next)
    {
        if(strcmp(p->CB.MaCB,MaCB)==0)
            return p;
    }
    return NULL;
}
void GhiFileDSCB(char *fileName, NODECB LCB)
{
    FILE * f;
    f = fopen(fileName,"w");
    if(f)
    {
        NODECB p;
        for(p=LCB; p!=NULL; p=p->next)
        {
            fprintf(f,"%s\n%d  %d  %d  %d  %d\n%s\n%d\n%s\n%d\n%d\n",p->CB.MaCB,p->CB.NgayKhoiHanh.hour,p->CB.NgayKhoiHanh.min,p->CB.NgayKhoiHanh.day,p->CB.NgayKhoiHanh.month,p->CB.NgayKhoiHanh.year,
                    p->CB.SanBayDen,p->CB.TrangThai,p->CB.SoHieuMB,p->CB.SoVeDaDat,p->CB.MaxVe);
            if(p->CB.SoVeDaDat>0)
            {
                for(int i =0; i<p->CB.SoVeDaDat; i++)
                    fprintf(f,"%s  %s          ",p->CB.dsVe[i].ViTriNgoi,p->CB.dsVe[i].CMND);
            }
            fprintf(f,"\n\n");
        }
        fclose(f);
    }
    else
    {
        AlertErr(8,1,"Khong mo duoc file \"DSCB.txt\" de ghi!");
    }
}
void DocFileDSCB(char *fileName, NODECB &LCB)
{
    ChuyenBay CB;
    FILE * f;

    f = fopen(fileName,"r");
    if(f)
    {
        fseek(f, 0, SEEK_END);
        if(ftell(f)==0) //gia tri con tro hien tai trong file
        {
            fclose(f);
            return;
        }

        fseek(f, 0, SEEK_SET);
        while(!feof(f))
        {
            fscanf(f,"%s",&CB.MaCB);
            fscanf(f,"%d%d%d%d%d",&CB.NgayKhoiHanh.hour, &CB.NgayKhoiHanh.min, &CB.NgayKhoiHanh.day, &CB.NgayKhoiHanh.month, &CB.NgayKhoiHanh.year);
            fgets(CB.SanBayDen,50,f);
            fgets(CB.SanBayDen,50,f);
            LoaiBoKiTuXuongDong(CB.SanBayDen);
            fscanf(f,"%d",&CB.TrangThai);
            fscanf(f,"%s", &CB.SoHieuMB);
            fscanf(f,"%d", &CB.SoVeDaDat);
            fscanf(f,"%d", &CB.MaxVe);
            CB.dsVe = new Ve[CB.MaxVe];
            if(CB.SoVeDaDat>0)
            {
                for(int i=0; i<CB.SoVeDaDat; i++)
                {
                    fscanf(f,"%s",&CB.dsVe[i].ViTriNgoi);
                    fscanf(f,"%s",&CB.dsVe[i].CMND);
                }
            }
            if(Time(CB.NgayKhoiHanh)<=0 && CB.SoVeDaDat==0) // quá time k đặt mua
                CB.TrangThai=0;
            else if(Time(CB.NgayKhoiHanh)<=0 && CB.TrangThai != 0)
                CB.TrangThai = 3;
            if(!feof(f))
            {
                insertOrder(LCB, CB);
            }

        }
        fclose(f);

    }
    else
    {
        AlertErr(8,1,"Khong mo duoc file \"DSCB.txt\"!");
    }
   GhiFileDSCB(FileDSCB, LCB);
}

void NhapDate(Date &date, int current, int x)
{
    SetColor(14);
    int ngaymax;
    cout<<"   :   -    /    /     ";

HOUR:
    ;
    SetColor(14);
    clearErr(8,4);
    gotoxy(8,4);
    cout<<"NHAP GIO :";
    gotoxy(x+46,current);
    char gio[3];
    if(inputNum(gio,2) == -1)
        return ;
    date.hour = atoi(gio);
    if(date.hour > 23 || date.hour <0)
    {
        AlertErr(8,4,"GIO PHAI TU 00 -> 24H");
        Sleep(1000);
        clearErr(8,4);
        gotoxy(x+46,current);
        cout<<"  ";
        goto HOUR;
    }

MIN:
    ;
    SetColor(14);
    clearErr(8,4);
    gotoxy(8,4);
    cout<<"NHAP PHUT :";
    gotoxy(x+49,current);
    char phut[3];
    if(inputNum(phut,2) == -1)
        return;
    date.min = atoi(phut);
    if(date.min > 60 || date.min <0)
    {
        AlertErr(8,4,"SO PHUT PHAI TU 00 -> 60");
        Sleep(1000);
        clearErr(8,4);
        gotoxy(x+49,current);
        cout<<"  ";
        goto MIN;
    }
DATE:
    ;
    SetColor(14);
    clearErr(8,4);
    gotoxy(8,4);
    cout<<"NHAP NGAY :";
    gotoxy(x+54,current);
    char ngay[3];
    char thang[3];

    if(inputNum(ngay,2) == -1)
        return;
    date.day = atoi(ngay);


    clearErr(8,4);
    gotoxy(8,4);
    cout<<"NHAP THANG :";
    gotoxy(x+59,current);
    if(inputNum(thang,2) == -1)
        return;
    date.month = atoi(thang);
    if (date.month<0 || date.month> 12 || date.day<0 || date.day> 31)
    {
        AlertErr(8,4,"NGAY THANG KHONG HOP LE. VUI LONG NHAP LAI");
        Sleep(2000);
        clearErr(8,4);
        gotoxy(x+54,current);
        cout<<"   /    /     ";
        goto DATE;
    }
    clearErr(8,4);
    gotoxy(8,4);
    cout<<"NHAP NAM :";
    gotoxy(x+64,current);

    char nam[5];
    if(inputNum(nam,4) == -1)
        return;
    date.year = atoi(nam);

    tm *crt = currentTime();
    int yearCurrent = crt->tm_year + 1900;
    int monthCurrent = crt->tm_mon+1;  // tm_year cchi tra ve 120
    int dayCurrent = crt->tm_mday;
    if(date.year < yearCurrent || date.year == yearCurrent && date.month < monthCurrent || date.year == yearCurrent && date.month == monthCurrent && date.day < dayCurrent )
    {
        AlertErr(8,4,"DD/MM/YYYY PHAI LON HON THOI GIAN HIEN TAI");
        Sleep(2000);
        clearErr(8,4);
        gotoxy(x+54,current);
        cout<<"   /    /     ";
        goto DATE;
    }
    else
    {

        switch (date.month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            ngaymax=31;
            break;
        case 2:
            if (checkYear(date.year))
                ngaymax=29;
            else
                ngaymax=28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            ngaymax=30;
            break;
        }
        if (date.day>ngaymax)
        {
            AlertErr(8,4,"KIEM TRA LAI SO NGAY TRONG THANG CHO HOP LI!");
            Sleep(3000);
            clearErr(8,4);
            gotoxy(x+54,current);
            cout<<"   /    /     ";
            goto DATE;
        }
    }

}

void NhapCB(NODECB &LCB, LISTMB LMB)
{

    TextColor(Green);
    gotoxy(7,1);
    cout<<"ESC: QUAY LAI";
    xuatTimeCurrent();
    ChuyenBay CB;
    int key;
    int i;
    gotoxy(8,7);
    SetColor(14);
    cout<<"STT       |    Ma chuyen bay      |      Ngay khoi hanh         |   San bay den     |   So hieu may bay |"<<endl;
    gotoxy(8,8);
    cout<<"--------------------------------------------------------------------------------------------------------|"<<endl;
    int current = 9;
    int stt =1;

    do
    {
        SetColor(14);
        clearErr(1,2);
        gotoxy(8,current);
        printf("%-10d", stt++);
        cout<<"|                       |                             |                   |                   |"<<endl;
MACB:
        ;
        SetColor(14);
        clearErr(8,4);
        gotoxy(8,4);
        cout<<"NHAP MA CHUYEN BAY";
        gotoxy(25, current);
        //cin>>CB.MaCB;

        if(NhapMa(CB.MaCB)==-1)
            return;
        clearErr(8,2);
        clearErr(8,4);
        if(searchCB(LCB, CB.MaCB) != NULL)
        {
            AlertErr(8,4,"Ma chuyen bay bi trung!");
            Sleep(2000);
            clearErr(8,4);
            gotoxy(22,current);
            cout<<"                 ";
            goto MACB;
        }
DATE:
        ;
        gotoxy(45, current);
        cout<<"                          ";
        gotoxy(45, current);
        NhapDate(CB.NgayKhoiHanh, current,0);
        clearErr(8,4);
        int t = Time(CB.NgayKhoiHanh);
        if(t<=setupTimeCB)
        {
            AlertErr(8,4,"GIO KHOI HANH CUA CHUYEN BAY PHAI CACH IT NHAT 1 NGAY !");
            Sleep(2000);
            clearErr(8,4);
            gotoxy(45,current);
            cout<<"                          ";
            goto DATE;
        }
SANBAYDEN:
        ;
        clearErr(8,4);
        SetColor(Yellow);
        gotoxy(8,4);
        cout<<"NHAP SAN BAY DEN :";
        gotoxy(76, current);
        cout<<"               ";
        gotoxy(76, current);
        NhapChuoi(CB.SanBayDen,76,current);
        DelSpace(CB.SanBayDen);

        SetColor(14);
        gotoxy(120,7);
        cout<<"DANH SACH SO HIEU MAY BAY"<<endl;
        gotoxy(120,8);
        cout<<"-------------------------"<<endl;
        int  k = 9;
        for(int i = 0; i<LMB.n; i++)
        {
            gotoxy(130,k++);
            cout<<LMB.nodes[i]->SoHieuMB<<endl;
        }

SHMB:
        ;


        clearErr(8,4);
        SetColor(Yellow);
        gotoxy(8,4);
        cout<<"NHAP SO HIEU MAY BAY :";
        gotoxy(98, current);
        if(NhapMa(CB.SoHieuMB)== -1)
            return;

        clearErr(8,4);
        i =SearchMB(LMB, CB.SoHieuMB);
        if(i==-1)
        {
            AlertErr(8,4,"SO HIEU MAY BAY KHONG TON TAI!");
            Sleep(2000);
            clearErr(8,4);
            gotoxy(98, current);
            cout<<"       ";
            goto SHMB;
        }
        NODECB q,tmpCheckCB;
        Init(tmpCheckCB);
        q=LCB;
        for(q; q !=NULL; q=q->next)
        {
            if(strcmp(q->CB.SoHieuMB,CB.SoHieuMB) == 0 && q->CB.TrangThai == 1 )
            {
                insertOrder_TIME(tmpCheckCB,q->CB);
            }
        }
        int a = countCB(tmpCheckCB);
        if(a!=0)
        {
            NODECB h;
            for(h=tmpCheckCB; h!=NULL ;)
            {
                if(abs(Time(h->CB.NgayKhoiHanh)- t) < setupTimeDatSHMB) // trg hợp thoi gian dat nho hon time trong ds time tang dan
                {
                    AlertErr(8,4,"HAI CHUYEN BAY CUNG SO HIEU PHAI CACH IT NHAT 5 NGAY ");
                    Sleep(3000);
                    clearErr(8,4);
                    gotoxy(98, current);
                    deleteAll(tmpCheckCB);
                    cout<<"       ";
                    goto DATE;

                }
               /* else
                {
                    if(strcmp(h->CB.SanBayDen,CB.SanBayDen ) == 0)
                    {
                        SetColor(Red);
                        gotoxy(8,4);
                        cout<<"CHUYEN BAY DANG TAO DANG NAM O SAN BAY HIEN TAI : ";
                        SetColor(Blue);
                        cout<<h->CB.SanBayDen;
                        SetColor(Red);
                        cout<<"CHON SAN BAY DEN KHAC";
                        Sleep(3000);
                        clearErr(8,4);
                        gotoxy(98, current);
                        cout<<"       ";
                        goto SANBAYDEN;
                    }
                }*/
                h=h->next;

            }
        }
        CB.MaxVe = LMB.nodes[i]->soDay * LMB.nodes[i]->soDong;
        CB.SoVeDaDat = 0;
        CB.dsVe = new Ve[CB.MaxVe];
        CB.TrangThai=1;
        current++;
        //   insertOrder(LCB, CB);
        insert_Last(LCB,CB);
        GhiFileDSCB(FileDSCB,LCB);
        gotoxy(8,2);
        SetColor(14);
        cout<<"Them chuyen bay thanh cong, Enter de tiep tuc them chuyen bay, nhan phim bat ki de thoat!";
        SetColor(15);
        delete [] CB.dsVe;
        key= getch();
    }
    while(key == Enter);


}
void EditCB(NODECB &LCB, int current, LISTMB LMB)
{

    NODECB p;
    p=LCB;
    int flag=0;
    while(flag<current)	  // tim CB  can sua
    {
        p= p->next;
        flag++;
    }
    gotoxy(15,3);
    if(p->CB.SoVeDaDat>0 || p->CB.TrangThai==0)
    {
        AlertErr(8,4,"KHONG THE SUA - CHUYEN BAY DA CO HANH KHACH HOAC DA HUY CHUYEN!");
        Sleep(3000);
        clearErr(8,4);
        return;
    }
    Normal();
    SetColor(Green);
    gotoxy(53,28);
    cout<<"THONG TIN CHINH SUA CHUYEN BAY";
    gotoxy(15,30);
    cout<<"        Ngay Khoi Hanh        |                 San Bay Den                 |        So Hieu May Bay  "<<endl;
    gotoxy(15,31);
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
    gotoxy(15,32);
    cout<<"                              |                                             |                               "<<endl;


    //cout<<"+ Ngay khoi hanh: ";
DATE:
    ;
    gotoxy(18,32);
    cout<<"                          ";
     gotoxy(18,32);
    SetColor(14);
    gotoxy(18,32);
    NhapDate(p->CB.NgayKhoiHanh,32,-27);
    clearErr(8,4);
    int t = Time(p->CB.NgayKhoiHanh);
    if(t<=setupTimeCB)
    {
        AlertErr(8,4,"Gio khoi hanh cua chuyen bay phai cach it nhat 1 tuan ke tu thoi diem hien tai!");
        gotoxy(18,32);
        cout<<"                          ";
        goto DATE;
    }

    clearErr(8,4);
    gotoxy(8,4);
    cout<<"NHAP SAN BAY DEN :";

    gotoxy(55,32);
     gotoxy(55,32);
    cout<<"                   ";
    NhapChuoi(p->CB.SanBayDen,55,32);
    DelSpace(p->CB.SanBayDen);

    //hien thi thong tin so hieu may bay

    SetColor(Green);
    gotoxy(130,28);
    cout<<"DANH SACH SO HIEU MAY BAY"<<endl;
    gotoxy(130,31);
    cout<<"-------------------------"<<endl;
    int  k = 32;
    for(int i = 0; i<LMB.n; i++)
    {
        gotoxy(135,k++);
        cout<<LMB.nodes[i]->SoHieuMB<<endl;
    }

SHMB:
    ;
    clearErr(8,4);
    SetColor(14);
    gotoxy(8,4);
    cout<<"NHAP SO HIEU MAY BAY :";
    gotoxy(100,32);
    if(NhapMa(p->CB.SoHieuMB)==-1)
        return;
    clearErr(8,4);
    int i =SearchMB(LMB, p->CB.SoHieuMB);
    if(i==-1)
    {
        AlertErr(8,4,"SO HIEU MAY BAY KHONG TON TAI!");
        Sleep(3000);
        gotoxy(100,32);
        cout<<"            ";
        goto SHMB;
    }

     NODECB q,tmpCheckCB;
        Init(tmpCheckCB);
        q=LCB;
        for(q; q !=NULL; q=q->next)
        {
            if(strcmp(q->CB.SoHieuMB,p->CB.SoHieuMB) == 0 && q->CB.TrangThai == 1 && strcmp(q->CB.MaCB,p->CB.MaCB) != 0)
            {
                insertOrder_TIME(tmpCheckCB,q->CB);
            }
        }
        int a = countCB(tmpCheckCB);
        if(a!=0)
        {
            NODECB h;
            for(h=tmpCheckCB; h!=NULL ;)
            {
                if(abs(Time(h->CB.NgayKhoiHanh)- t) < setupTimeDatSHMB) // trg hợp thoi gian dat nho hon time trong ds time tang dan
                {
                    AlertErr(8,4,"HAI CHUYEN BAY CUNG SO HIEU PHAI CACH IT NHAT 5 NGAY ");
                    Sleep(3000);
                    clearErr(8,4);
                    gotoxy(100, 32);
                    deleteAll(tmpCheckCB);
                    cout<<"         ";
                    goto DATE;
                }
                h=h->next;
            }
        }
    p->CB.MaxVe = LMB.nodes[i]->soDay * LMB.nodes[i]->soDong;
    GhiFileDSCB(FileDSCB, LCB);
    system("cls");
    //InDSCB(LCB, LMB);


}
void DeleteCB(NODECB &LCB, int current, LISTMB LMB )
{
    NODECB q;
    q=LCB;
    if(current>0)
    {
        int flag=0;
        while(flag<current-1)// định vi phan tu trc node xan xoa
        {
            q= q->next;
            flag++;
        }
        if(q->next->CB.SoVeDaDat>0 )
        {

            AlertErr(8,5,"Chuyen bay nay khong the xoa vi da co ve duoc mua!");
            Sleep(2000);
            clearErr(8,4);
            clearErr(8,5);
            return;
        }
    }
    else if(q->CB.SoVeDaDat>0)
    {
        AlertErr(8,5,"Chuyen bay nay khong the xoa vi da co ve duoc mua!");
        Sleep(1500);
        clearErr(8,4);
        clearErr(8,5);
        return;
    }
    //cout<<q->CB.MaCB;
    char confirm[10];
    gotoxy(8,4);
    Normal();
    SetColor(14);
    cout<<"Nhan \"yes\" de xac nhan xoa chuyen bay: ";
    SetColor(Green);
    cout<<q->next->CB.MaCB<<" : ";
    SetColor(14);
    cin>>confirm;

    if(strcmp(confirm,"yes")==0)
    {

        if(current>0)
            deleteAfter(q);
        else
            deleteFirst(LCB);
        GhiFileDSCB(FileDSCB,LCB);
        system("cls");
        //InDSCB(LCB, LMB);
    }
    else
    {
        gotoxy(8,5);
        cout<<"Da huy yeu cau xoa chuyen bay!";
        Sleep(1500);
        clearErr(8,4);
        clearErr(8,5);
    }
}
void CancelCB(NODECB &LCB, int current, LISTMB LMB )
{



    NODECB p;
    p=LCB;
    int flag=0;
    while(flag<current)
    {
        p= p->next;
        flag++;
    }
    cout<<p->CB.MaCB;
    if(p->CB.TrangThai==0)
    {
        AlertErr(8,5,"Chuyen bay nay truoc do da bi huy!");
        Sleep(3000);
        clearErr(8,4);
        clearErr(8,5);
        return;
    }
  /*  if(p->CB.SoVeDaDat>0)
    {
        AlertErr(8,5,"CHUYEN BAY DA CO HANH KHACH - KHONG THE HUY CHUYEN BAY!");
        Sleep(3000);
        clearErr(8,4);
        clearErr(8,5);
        return;
    }*/
    char confirm[10];
    gotoxy(8,4);
    Normal();
    cout<<"Nhan \"yes\" de xac nhan huy chuyen bay: ";
    cin>>confirm;

    if(strcmp(confirm,"yes")==0)
    {
        p->CB.TrangThai= 0;
        GhiFileDSCB(FileDSCB, LCB);
        gotoxy(8,5);
        SetColor(14);
        cout<<"HUY CHUYEN BAY THANH CONG!";
        Sleep(3000);
        system("cls");
        //InDSCB(LCB,LMB);
        return;
    }
    else
    {
        gotoxy(8,5);
        cout<<"DA HUY YEU CAU CHUYEN BAY!";
        Sleep(3000);
        clearErr(8,4);
        clearErr(8,5);
    }

}
void InMotCB(NODECB LCB, int current)
{

    NODECB p;
    int count = 0;
    p=LCB;
    while(count < current)
    {
        p=p->next;
        count++;
    }
    printf("%-8d|     %-15s| %02d:%02d\ - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d",count+1,p->CB.MaCB,p->CB.NgayKhoiHanh.hour,p->CB.NgayKhoiHanh.min,p->CB.NgayKhoiHanh.day,p->CB.NgayKhoiHanh.month,p->CB.NgayKhoiHanh.year,
           p->CB.SanBayDen,p->CB.TrangThai,p->CB.SoHieuMB,p->CB.SoVeDaDat,p->CB.MaxVe);
}
void InDSCB(NODECB &LCB, LISTMB LMB)
{
    int crtPage = 1;

BEGIN:
    ;

    SetColor(14);
    VeHCN(5,0,15,2);
    gotoxy(7,1);
    cout<<"F2: CANCEL";
    VeHCN(25,0,15,2);
    gotoxy(27,1);
    cout<<"F3: EDIT";
    VeHCN(45,0,15,2);
    gotoxy(47,1);
    cout<<"F4: DELETE";
    VeHCN(65,0,15,2);
    gotoxy(67,1);
    cout<<"ESC: EXIT";

    VeHCN(85,0,70,2);
    gotoxy(87,1);
    cout<<"Trang Thai: 0 - Huy Chuyen,  1 - Con Ve, 2 - Het Ve,  3 - Hoan Tat";
    gotoxy(55,7);
    cout<<"DANH SACH CHUYEN BAY";
    //Normal();
    int n =countCB(LCB);
    gotoxy(5,9);
    cout<<"STT     |    Ma Chuyen Bay   |     Ngay Khoi Hanh     |      San Bay Den      | Trang Thai | So Hieu May Bay | So Ve Da Dat | So Luong Ve "<<endl;
    gotoxy(5,10);
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

LR:
    ;
    SetColor(14);
    VeHCN(60,39,10,2);
    gotoxy(62,40);
    cout<<"Page "<<crtPage;
    SetColor(15);
    int current = 0;
    int pages = n/numPageCB;
    if(n%numPageCB>0)
        pages++; // pages = 1

    if(!emptyLCB(LCB))
    {

        NODECB p,q;
        p=LCB;
        q=p; // giu lai lat xuat in hilight
        int i=(crtPage-1)*numPageCB;
        int c=0;
        while(c<i)
        {
            p=p->next;
            q=p;
            c++;
        }
        int y=11;
        for(; p!=NULL && i<crtPage* numPageCB; p=p->next)
        {
            gotoxy(5,y++);
            printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d",i+1,p->CB.MaCB,p->CB.NgayKhoiHanh.hour,p->CB.NgayKhoiHanh.min,p->CB.NgayKhoiHanh.day,p->CB.NgayKhoiHanh.month,p->CB.NgayKhoiHanh.year,
                   p->CB.SanBayDen,p->CB.TrangThai,p->CB.SoHieuMB,p->CB.SoVeDaDat,p->CB.MaxVe);
            i++;
        }

        gotoxy(5,11);
        HighLight();
        printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d",(crtPage-1)* numPageCB +1,q->CB.MaCB,q->CB.NgayKhoiHanh.hour,q->CB.NgayKhoiHanh.min,q->CB.NgayKhoiHanh.day,q->CB.NgayKhoiHanh.month,q->CB.NgayKhoiHanh.year,
               q->CB.SanBayDen,q->CB.TrangThai,q->CB.SoHieuMB,q->CB.SoVeDaDat,q->CB.MaxVe);

        int f = (crtPage-1)*numPageCB; // chay tu 0 trong ds
        int kytu;
        do
        {
            kytu = getch();
            if(kytu <=0)
                kytu = getch();
            switch(kytu)
            {
            case Up:
                if(current > 0)
                {
                    Normal();
                    gotoxy(5,current+11);
                    InMotCB(LCB,current+f);
                    current--;
                    HighLight();
                    gotoxy(5,current+11);
                    InMotCB(LCB,current+f);
                };
                break;
            case Down:
                if((crtPage==pages && current+1 <numPageCB-(pages* numPageCB -n)) || (crtPage<pages && current+1 <numPageCB)) // pageHt = sumPage && indexDong <
                {
                    Normal();
                    gotoxy(5,current+11);
                    InMotCB(LCB,current+f);
                    current++;
                    HighLight();
                    gotoxy(5,current+11);
                    InMotCB(LCB,current+f);
                }
                break;

            case Right:
                if(crtPage<pages)
                {
                    crtPage++;
                    Normal();
                    for(int i =0; i< numPageCB; i++)
                        clearErr(1,11+i);
                    goto LR;
                }
                break;
            case Left:
                if(crtPage>1)
                {
                    crtPage--;
                    Normal();
                    for(int i =0; i< numPageCB; i++)
                        clearErr(1,11+i);
                    goto LR;
                }
                break;
            case F2:
            {
                CancelCB(LCB, current+f, LMB);
                goto BEGIN;
                break;
            }
            case F3:
            {
                EditCB(LCB, current+f, LMB);
                goto BEGIN;
                break;
            }
            case F4:
            {
                DeleteCB(LCB, current+f, LMB);
                if(countCB(LCB)% numPageCB ==0)
                    crtPage--;
                goto BEGIN;
                break;
            }
            case ESC:
                return;
            }
        }
        while(1);
    }
    else
    {
        clearErr(5,12);
        gotoxy(5,12);
        SetColor(Green);
        cout<<"DANH SACH RONG, VUI LONG THEM CHUYEN BAY";

    }

    getch();
}
void UpdateCB(NODECB &LCB, LISTMB LMB)
{
    int soluongMeNu = 2;
    char menuMB_update [2][70] =
    {
        "THEM CHUYEN BAY",
        "CAP NHAT CHUYEN BAY"
    };
    int m;
    do
    {
        ShowCur(false);
        TextColor(0x0004);
        system("cls");
        TextColor(Green);
        vekhung(68,35,1,34);
        PutCharXY(70,36,"ESC: QUAY LAI | ENTER: XAC NHAN",Green);
        m = menu(55,10,menuMB_update,soluongMeNu);

        //	Normal();
        switch(m)
        {
        case 0:
        {
            system("cls");
            NhapCB(LCB, LMB);
        }
        break;
        case 1:
        {
            system("cls");
            InDSCB(LCB, LMB);
        }
        break;
        case ESC:
            return ;
        }
    }
    while(m!=-1);
}
//============================================================================================================================================
//===========================================================KHACH HANG=======================================================================

void InitBST(BSTKH &LKH)
{
    LKH=NULL;
}


int Compare(ThongTinKH KH1, ThongTinKH KH2)
{
    return strcmp(KH1.CMND,KH2.CMND);
}
void InsertKH(BSTKH &LKH, ThongTinKH TTKH)
{
    if(LKH==NULL)
    {
        LKH = new KhachHang;
        LKH->data = TTKH;
        LKH->left  = NULL;
        LKH->right = NULL;

    }
    else
    {
        if(Compare(LKH->data, TTKH)==1)
            InsertKH(LKH->left, TTKH);
        else if(Compare(LKH->data, TTKH)==-1)
            InsertKH(LKH->right, TTKH);
    }
}
void GhiFileDSKH(char *fileName, BSTKH LKH)//NLR
{
    FILE * f;
    f = fopen(fileName,"w");
    if(f)
    {
        const int STACKSIZE = 300;
        BSTKH Stack[STACKSIZE];

        int sp =-1;
        BSTKH p = LKH;
        while(p!=NULL)
        {
            fprintf(f,"%s\n%s\n%s\n%s\n\n",p->data.CMND,p->data.Ho,p->data.Ten,p->data.Phai);
            if(p->right!=NULL)
                Stack[++sp]= p->right;
            if(p->left!=NULL)
                p=p->left;
            else if(sp==-1)
                break;
            else
                p=Stack[sp--];
        }
        fclose(f);
    }
    else
    {
        AlertErr(8,4,"Khong mo duoc file \"DSKH.txt\" de ghi!");
    }
}
void DocFileDSKH(char *fileName, BSTKH &LKH)//
{
    ThongTinKH KH;

    FILE * f;

    f = fopen(fileName,"r");
    if(f)
    {
        fseek(f, 0, SEEK_END);
        if(ftell(f)==0) //gia tri con tro hien tai trong file
        {
            fclose(f);
            return;
        }

        fseek(f, 0, SEEK_SET);
        while(!feof(f))
        {
            fscanf(f,"%s",&KH.CMND);
            fgets(KH.Ho,250,f);
            fgets(KH.Ho,250,f);
            LoaiBoKiTuXuongDong(KH.Ho);
            fscanf(f,"%s",&KH.Ten);
            fscanf(f,"%s",&KH.Phai);

            if(!feof(f))
            {
                InsertKH(LKH, KH);
            }
        }

        fclose(f);

    }

    else
    {

        AlertErr(8,4,"Khong mo duoc file \"DSKH.txt\"!");
    }
}


void Preorder(BSTKH LKH)
{
    if(LKH!=NULL)
    {
        cout<<LKH->data.CMND<<endl;
        //fprintf(f,"%s  ",LKH->data.CMND);
        Preorder(LKH->left);
        Preorder(LKH->right);
    }

}

BSTKH SearchKH(BSTKH LKH, char CMND[11])
{
    BSTKH p;
    p=LKH;
    while(p!=NULL && (strcmp(p->data.CMND,CMND)!=0))
    {
        if(strcmp(p->data.CMND,CMND)==1)
            p=p->left;
        else
            p=p->right;
    }

    return p;
}

void NhapKH(BSTKH &LKH, char CMND[11], int soDay)
{
    ThongTinKH KH;
    strcpy(KH.CMND, CMND);
    int y = 9+soDay*2;
    gotoxy(37,y +10);
    SetColor(Yellow);
    cout<<"THEM THONG TIN HANH KHACH";
    gotoxy(11,y +12);
    printf("        CMND        |           Ho           |        Ten        |     Phai");
    gotoxy(11,y +13);
    cout<<"------------------------------------------------------------------------------\n";
    SetColor(15);
    gotoxy(11,y +14 );
    cout<<"                    |                        |                   |             "<<endl;
    gotoxy(17,y +14 );
    cout<<CMND;
    SetColor(Yellow);
    gotoxy(60,y +8);
    cout<<"VUI LONG NHAP HO";
    gotoxy(34,y +14 );
    fflush(stdin);
    SetColor(White);
    NhapChuoi(KH.Ho,34,y +14);
    LoaiBoKiTuXuongDong(KH.Ho);
    SetColor(Yellow);
    gotoxy(60,y +8);
    cout<<"VUI LONG NHAP TEN";
    SetColor(15);
    gotoxy(62,y +14 );
    NhapTenKh(KH.Ten);
    //  NhapChuoi(KH.Ten,62,y+14);
//     LoaiBoKiTuXuongDong(KH.Ten);
    SetColor(14);
    gotoxy(60,y +8);
    cout<<"VUI LONG NHAP PHAI";
    SetColor(15);
    gotoxy(82,y +14 );
    NhapTenKh(KH.Phai);
    clearErrTTHK(58,y +8);
    InsertKH(LKH, KH);
    GhiFileDSKH(FileDSKH, LKH);

}

//=================================================================     VE    ====================================================================
void VeDSVDM(NODECB p)
{
    for(int i= 0; i< p->CB.SoVeDaDat; i++)
    {
        char *vitringoi = p->CB.dsVe[i].ViTriNgoi;
        gotoxy(15,28+i);
        int d = vitringoi[0]-64;//vi tri day

        int c = 0;	//vi tri so ghe cua day
        int len = strlen(vitringoi); // do dai chuoi cua day
        // tim toa do in mau

        for(int j = 1; j< strlen(vitringoi); j++)
        {
            c+= (vitringoi[j]-so0) * pow(10,len-2);//
            len--;
        }
        SetColor(Blue);
        gotoxy(8+c*6-3,9+ d*2);
        cout<<p->CB.dsVe[i].ViTriNgoi;

    }
}
void Inorder(BSTKH KH)
{
    int y = 5;
    if(KH != NULL)
  {
      gotoxy(100,y);
       Inorder(KH->left);
      printf("%d ", KH->data.CMND);
      y++;
      Inorder(KH->right);
   }


}
void Intrav(BSTKH root)
{
   const int STACKSIZE = 500;
   BSTKH Stack[STACKSIZE];
   BSTKH p=root;
   int sp=-1;	 // Khoi tao Stack rong
   int y =5;
   do
   { while (p != NULL)
      {	 Stack[++sp]= p;
	   p= p->left;
      }
      if (sp != -1)
      {	 p=Stack[sp--];
      gotoxy(100,y++);
	 cout << p->data.CMND << "  ;  ";
	 p=p->right;
      }
      else break;
   } while (1);

}

int searchVe(NODECB p, char vtn[5])
{
    for(int i=0; i < p->CB.SoVeDaDat; i++)
    {
        if(strcmp(vtn,p->CB.dsVe[i].ViTriNgoi)==0)
        {
            return i;
        }
    }
    return -1;
}

void NhapVe(NODECB &LCB, NODECB &p,NODECB tmp,  int x, int y,int soDong, int soDAY, BSTKH LKH) 	//p: chuyen bay can dat trong LCB
{

    for(int i=0; i< 13; i++)
    clearErr(8,10+soDAY*2 + 4 + i);
  //  BSTKH t= LKH;
   // Inorder(Y);
    //Intrav(t);
    char vitringoi[5] ;
   // sprintf(vitringoi,"%c%d",char(y+64), x);
    sprintf(vitringoi,"%c%d",char(y+64), x);
    gotoxy(8,4);
    cout<<"VE DANG CHON MUA : ";
    SetColor(Blue);
    cout<<vitringoi;
    gotoxy(8,7);
//	itoa(x,ch1,10);
    /*  int i=0;
      for( i; i<strlen(ch1); i++)
      {
          vitringoi[i+1] = ch1[i];
      }
      //vitringoi[i+1]='\0';
      vitringoi[i+1]=0;
      //cout<<	vitringoi;
    */

    if(searchVe(p, vitringoi)!=-1)
    {
        AlertErr(8,5,"VE NAY DA DUOC MUA!");
        Sleep(2000);
        clearErr(8,5);
        return;
    }
    SetColor(White);
    VeHCN(8,9+soDAY*2 +4,30,4);

CMND:
    ;
    SetColor(Yellow);
    gotoxy(11,9+soDAY*2 +6);
    cout<<"NHAP VAO CMND: ";
    if(inputNum(p->CB.dsVe[p->CB.SoVeDaDat].CMND,9)==-1)
    {
        for(int i=0; i< 13; i++)
            clearErr(8,9+soDAY*2 + 4 + i);
        return;
    }
    clearErr(8,4);


    for(int i =0; i< p->CB.SoVeDaDat; i++)
    {
        if(strcmp(p->CB.dsVe[i].CMND,p->CB.dsVe[p->CB.SoVeDaDat].CMND)==0)
        {
            AlertErr(8,4,"KHACH HANG DA CO VE TREN CHUYEN BAY NAY!");
            Sleep(2000);
            clearErr(8,4);
            gotoxy(11,9+soDAY*2 +6);
            cout<<"                         ";
            goto CMND;
            break;
        }
    }
    NODECB q ;
    int checkTimeCBNOW = Time(p->CB.NgayKhoiHanh);

    for(q=tmp; q!=NULL; q=q->next)
    {
        if(strcmp(q->CB.MaCB,p->CB.MaCB) == 0 || strcmp(q->CB.SoHieuMB,p->CB.SoHieuMB)==0)
            q=q->next;
        int checkTimeDSCB = Time(q->CB.NgayKhoiHanh);
        for(int j = 0; j <q->CB.SoVeDaDat; j++)
        {
            if(strcmp(q->CB.dsVe[j].CMND,p->CB.dsVe[p->CB.SoVeDaDat].CMND)==0 && abs(checkTimeCBNOW-checkTimeDSCB) <setupTimeCB )
            {
                AlertErr(8,4,"KH DANG CO CHUYEN BAY CUNG THOI DIEM :");
                SetColor(Blue);
                cout<<q->CB.MaCB;
                SetColor(Red);
                cout<<" CB PHAI CACH IT NHAT 2 NGAY ";
                Sleep(3000);
                clearErr(8,4);
                gotoxy(11,9+soDAY*2 +6);
                cout<<"                         ";
                goto CMND;
                break;
            }

        }
    }


    BSTKH KH = SearchKH(LKH, p->CB.dsVe[p->CB.SoVeDaDat].CMND); // tra ve dia chi ttkh neu true

    if(KH != NULL)
    {
        int toadoX = soDong*7+20;
        gotoxy(toadoX,7);
        SetColor(Yellow);
        cout<<"THONG TIN HANH KHACH ";
        SetColor(White);
        VeHCN(toadoX,9,20,8); // VE KHUNG HK
        gotoxy(toadoX+2,10);
        cout<<"CMND : "<<KH->data.CMND;
        gotoxy(toadoX+2,12);
        cout<<"HO : "<<KH->data.Ho;
        gotoxy(toadoX+2,14);
        cout<<"TEN : "<<KH->data.Ten;
        gotoxy(toadoX+2,16);
        cout<<"PHAI : "<<KH->data.Phai;

    }
    else
    {
        NhapKH(LKH,p->CB.dsVe[p->CB.SoVeDaDat].CMND, soDAY);
    }

    char confirm[10];
    gotoxy(8,4);
    Normal();
    cout<<"Nhan \"yes\" de xac nhan dat ve chuyen bay: ";
    cin>>confirm;
    int k = 8+soDAY*2+4;
    if(strcmp(confirm,"yes")==0)
    {
        for(int y = 7; y< 20 ; y++)
        {
            clearErrTTHK(soDong*7 +20,y);
            clearErr(8,k);
            k++;
        }

        strcpy(p->CB.dsVe[p->CB.SoVeDaDat].ViTriNgoi,vitringoi);
        p->CB.SoVeDaDat++;
        if(p->CB.SoVeDaDat==p->CB.MaxVe)
        {
            p->CB.TrangThai=2;
            clearErr(8,4);
            SetColor(Green);
            gotoxy(8,4);
            cout<<"DA FULL VE!";
            Sleep(5000);
            clearErr(8,4);
        }
        VeDSVDM(p);
        GhiFileDSCB(FileDSCB, LCB);
        clearErr(8,4);
        gotoxy(8,4);
        cout<<"DAT THANH CONG!";
        Sleep(1500);
        clearErr(8,4);
    }
    else
    {
        gotoxy(8,5);
        cout<<"Da huy yeu cau dat ve chuyen bay!";
        Sleep(1500);
        clearErr(8,4);
        clearErr(8,5);
        int k = 8+soDAY*2+4;
        for(int y = 7; y< 20 ; y++)
        {
            clearErrTTHK(soDong*7+20,y);
            clearErr(8,k);
            k++;
        }
    }

}
//============================================ DAT VE ======================================================
void DSVeOfCB(NODECB LCB, NODECB tmp, int current, LISTMB LMB, BSTKH LKH)
{
RESTART :
    ;
    Normal();
    system("cls");
    SetColor(Yellow);
    VeHCN(35,0,27,2);
    gotoxy(37,1);
    cout<<"ENTER: TIEN HANH DAT VE";

    int x=11;
    int y= 11;

    NODECB q;
    q=tmp;
    int flag = 0;
    while(flag < current)
    {
        q=q->next;
        flag++;
    }

    NODECB p;
    p=LCB;
    while(p!=NULL && strcmp(q->CB.MaCB,p->CB.MaCB)!=0)
        p=p->next;


    int i = SearchMB(LMB, q->CB.SoHieuMB);
    //cout<<LMB.nodes[i]->soDay << endl<<LMB.nodes[i]->soDong;
    gotoxy(10,7);
    SetColor(Green);
    cout<<"DANH SACH VE CUA CHUYEN BAY "<<q->CB.MaCB<<endl;
    SetColor(15);
    int soDong = LMB.nodes[i]->soDong;
    int soDay = LMB.nodes[i]->soDay;

    SetColor(14);
    VeHCN(8,0,20,2);
    gotoxy(10,1);
    SetColor(Yellow);
    cout<<"VE CON TRONG :";
    SetColor(Blue);
    cout<<soDong*soDay - p->CB.SoVeDaDat;
    SetColor(White);
    VeHCN(8,9,soDong*6 +4,soDay*2+2);
    gotoxy(11,11);
    for(int day = 1; day<= soDay; day++)
    {
    //    int a = 0;
     //   int k = 1;
        for(int dong =1; dong <= soDong; dong++)
        {
           // if(k == 10)
          //  {
           //   a++;
          //    k = 0;
          //  }
            printf("%c%-5d",char(day+64),dong);
          //  k++;

        }
        y=y+2;
        gotoxy(11,y);
    }

    gotoxy(68,7);
    SetColor(White);
   VeDSVDM(p);
    y=11;
    int currentX = 1;
    int currentY = 1;
    SetColor(Yellow);
    gotoxy(x,y);
    printf("%c%-2d",char(currentX+64),currentY);
    int kytu;
    do
    {

        kytu = getch();

        if(kytu <=0)
            kytu = getch();

        switch(kytu)
        {
        case Up:
            if(currentY > 1)
            {
                SetColor(White);
                gotoxy(currentX+x-1,currentY+y-1);
                printf("%c%-2d",char(currentY+64),currentX);
                currentY--;
                y-=1;
                VeDSVDM(p);
                SetColor(Yellow);
                gotoxy(currentX+x-1,currentY+y-1);
                printf("%c%-2d",char(currentY+64),currentX);
            };
            break;
        case Down:
            if(currentY  < LMB.nodes[i]->soDay)
            {

                SetColor(White);
                gotoxy(currentX+x-1,currentY+y-1);
                printf("%c%-2d",char(currentY+64),currentX);
                currentY++;
                y+=1;

                SetColor(Yellow);
                gotoxy(currentX+x-1,currentY+y-1);
                printf("%c%-2d",char(currentY+64),currentX);
            }
            break;
        case Left:
            if(currentX  >1)
            {

                SetColor(White);
                gotoxy(currentX + x-1,currentY+y-1);
                printf("%c%-2d",char(currentY+64),currentX);
                currentX--;
                x-=5;
                VeDSVDM(p);
                SetColor(Yellow);
                gotoxy(currentX + x-1,currentY+y-1);
                printf("%c%-2d",char(currentY+64),currentX);
            }
            break;
        case Right:
            if(currentX  < LMB.nodes[i]->soDong)
            {

                SetColor(White);
                gotoxy(currentX + x-1,currentY+y-1);
                printf("%c%-2d",char(currentY+64),currentX);
                currentX++;
                x+=5;
                VeDSVDM(p);
                SetColor(Yellow);
                gotoxy(currentX + x-1,currentY+y-1);
                printf("%c%-2d",char(currentY+64),currentX);
            }
            break;
        case Enter:
            NhapVe(LCB, p,tmp, currentX, currentY,soDong, soDay, LKH);
            goto RESTART;
        case ESC:
            return;
        }
    }
    while(1);
}

void DatVe(NODECB LCB, LISTMB LMB, BSTKH LKH)
{
BEGIN:
    Normal();
    system("cls");
    NODECB tmp,q;
    Init(tmp);
    q=LCB;
    for(q; q!=NULL; q=q->next)
    {
        if(q->CB.TrangThai== 1)
        {
            insertOrder(tmp,q->CB);
        }
    }
    gotoxy(55,7);
    SetColor(14);
    cout<<"DANH SACH CHUYEN BAY CO THE DAT VE";
     int current = 0;
    int n =countCB(tmp);
    gotoxy(5,9);
    cout<<"STT     |    Ma Chuyen Bay   |     Ngay Khoi Hanh     |      San Bay Den      | Trang Thai | So Hieu May Bay | So Ve Da Dat | So Luong Ve "<<endl;
    gotoxy(5,10);
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    Normal();

    if(tmp!=NULL)
    {
        NODECB p;
        int i=0;
        for(p=tmp; p!=NULL; p=p->next)
        {
            gotoxy(5,i+11);
            printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d",i+1,p->CB.MaCB,p->CB.NgayKhoiHanh.hour,p->CB.NgayKhoiHanh.min,p->CB.NgayKhoiHanh.day,p->CB.NgayKhoiHanh.month,p->CB.NgayKhoiHanh.year,
                   p->CB.SanBayDen,p->CB.TrangThai,p->CB.SoHieuMB,p->CB.SoVeDaDat,p->CB.MaxVe);
            i++;
        }
        p=tmp;
        gotoxy(5,11);
        HighLight();
        printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d",1,p->CB.MaCB,p->CB.NgayKhoiHanh.hour,p->CB.NgayKhoiHanh.min,p->CB.NgayKhoiHanh.day,p->CB.NgayKhoiHanh.month,p->CB.NgayKhoiHanh.year,
        p->CB.SanBayDen,p->CB.TrangThai,p->CB.SoHieuMB,p->CB.SoVeDaDat,p->CB.MaxVe);
        int kytu;
        do
        {
            kytu = getch();
            if(kytu <=0)
                kytu = getch();
            switch(kytu)
            {
            case Up:
                if(current > 0)
                {
                    Normal();
                    gotoxy(5,current+11);
                    InMotCB(tmp,current);
                    current--;
                    HighLight();
                    gotoxy(5,current+11);
                    InMotCB(tmp,current);
                };
                break;
            case Down:
                if(current +1 <n)
                {
                    Normal();
                    gotoxy(5,current+11);
                    InMotCB(tmp,current);
                    current++;
                    HighLight();
                    gotoxy(5,current+11);
                    InMotCB(tmp,current);
                }
                break;
            case Enter:
            {
                DSVeOfCB(LCB, tmp, current, LMB, LKH);
                goto BEGIN;
            }
            break;
            case ESC:
            {
                deleteAll(tmp);
                return;
            }
            }
        }
        while(1);
    }
    else
    {
        gotoxy(5,11);
        SetColor(Green);
        cout<<"HIEN CHUA CO CHUYEN BAY DE DAT, VUI LONG QUAY LAI TAO CHUYEN BAY";
    }
    getch();
}
//============================================================== HUY VE ===============================================
void DSVeDaDat(NODECB p)
{
    gotoxy(50,10);
    SetColor(Yellow);
    cout<<"DANH SACH VE DA DAT CUA CHUYEN BAY : " <<p->CB.MaCB <<endl;
    gotoxy(15,11);
    for(int i=0; i<p->CB.SoVeDaDat; i++ )
    {
        cout<<p->CB.dsVe[i].ViTriNgoi<<"     ";
    }
}

void HuyVe(NODECB & LCB)
{
    Normal();
    system("cls");
    char MaCB[15];
    char VeCanHuy[5];
    int key;
MACB:
    ;
    SetColor(Yellow);
    gotoxy(10,5);
    cout<<"NHAP VAO MA CHUYEN BAY CO VE CAN HUY: ";
    if(NhapMa(MaCB) == -1)
        return;

    NODECB p = searchCB(LCB,MaCB);
    if(p == NULL)
    {
        AlertErr(10,2,"MA CHUYEN BAY KHONG TON TAI!");
        Sleep(2000);
        clearErr(8,2);
        clearErr(10,5);
        goto MACB;

    }
    else if(p->CB.TrangThai == 0 || p->CB.TrangThai == 3)
    {
        AlertErr(10,2,"KHONG THE HUY VE - CHUYEN BAY DA BI HUY HOAC DA HOAN THANH!");
        Sleep(2000);
        clearErr(10,2);
        clearErr(10,5);
        goto MACB;
    }
    else
    {
        DSVeDaDat(p);
VE:
        ;
        gotoxy(10,6);
        SetColor(Yellow);
        cout<<"NHAP VE CAN HUY: ";
        NhapChuoi(VeCanHuy,30,6);
        int k = searchVe(p, VeCanHuy);
        if( k == -1)
        {
            AlertErr(10,2,"VE CAN HUY KHONG NAM TRONG DANH SACH CAC VE DA MUA CUA CHUYEN BAY NAY!");
            gotoxy(10,3);
            SetColor(Yellow);
            cout<<"VUI LONG CHON --> F4 : DE CHON LAI || F5 : CHON CHUYEN BAY MOI || ESC : THOAT";
            do
            {
                key = getch();
                if(key <=0)
                    key = getch();
                if (key==F4)
                {
                    clearErr(10,2);
                    clearErr(10,3);
                    clearErr(10,6);
                    goto VE;
                }
                else if(key==F5)
                {
                    system("cls");
                    SetColor(15);
                    goto MACB;
                }
                else if(key==ESC)
                    return;
            }
            while(1);
        }
        else
        {
            char confirm[10];
            gotoxy(10,2);
            Normal();
            cout<<"Nhan \"yes\" de xac nhan huy ve: ";
            cin>>confirm;
            if(strcmp(confirm,"yes")==0)
            {


                for(int j=k; j<p->CB.SoVeDaDat-1 ; j++)
                {

                       p->CB.dsVe[j]=p->CB.dsVe[j+1];

                }

                p->CB.SoVeDaDat--;
                p->CB.TrangThai=1;
                GhiFileDSCB(FileDSCB,LCB);
                system("cls");
                DSVeDaDat(p);
                gotoxy(10,3);
                SetColor(Yellow);
                cout<<"VUI LONG CHON --> F4 : DE TIEP TUC HUY VE || F5 : CHON CHUYEN BAY MOI || ESC : THOAT";
                do
                {
                    key = getch();
                    if(key <=0)
                        key = getch();
                    if (key==F4)
                    {
                        clearErr(10,2);
                        clearErr(10,3);
                        clearErr(10,6);
                        goto VE;
                    }
                    else if(key==F5)
                    {
                        system("cls");
                        SetColor(15);
                        goto MACB;
                    }
                    else if(key==ESC)
                        return;
                }
                while(1);
            }
            else
            {
                gotoxy(10,3);
                cout<<"DA HUY YEU CAU HUY VE!";
                Sleep(1000);
                clearErr(10,2);
                clearErr(10,3);
                gotoxy(10,3);
                SetColor(Yellow);
                cout<<"VUI LONG CHON --> F4 : DE TIEP TUC HUY VE || F5 : CHON CHUYEN BAY MOI || ESC : THOAT";
                do
                {
                    key = getch();
                    if(key <=0)
                        key = getch();
                    if (key==F4)
                    {
                        clearErr(10,2);
                        clearErr(10,3);
                        clearErr(10,6);
                        goto VE;
                    }
                    else if(key==F5)
                    {
                        system("cls");
                        SetColor(15);
                        goto MACB;
                    }
                    else if(key==ESC)
                        return;
                }
                while(1);
            }
        }
    }

}



// ===================================================IN DANH SACH HANH KHACH TREN MOT CHUYEN BAY==============================
void DSKHOfCB(NODECB LCB, BSTKH LKH, int current)
{
    fflush(stdin);
    Normal();
    system("cls");
    int count = 0;
    NODECB p;
    p=LCB;
    while(count < current)
    {
        p=p->next;
        count++;
    }
    //cout<<p->CB.MaCB;
    SetColor(Yellow);
    gotoxy(50,5);
    cout<<"DANH SACH HANH KHACH THUOC CHUYEN BAY: "<<p->CB.MaCB;
    gotoxy(35,7);
    printf("NGAY GIO KHOI HANH: %02d/%02d/%04d %02d:%02d           NOI DEN: %s", p->CB.NgayKhoiHanh.day, p->CB.NgayKhoiHanh.month, p->CB.NgayKhoiHanh.year, p->CB.NgayKhoiHanh.hour, p->CB.NgayKhoiHanh.min, p->CB.SanBayDen);
    gotoxy(25,9);
    cout<<"STT     |    So Ve    |        So CMND        |                 Ho Ten                 |      Phai      "<<endl;
    gotoxy(25,10);
    cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
    Normal();
    BSTKH KH;
    char HoTen[60];
    for(int i=0; i<p->CB.SoVeDaDat; i++)
    {
        gotoxy(25,11+i);
        KH =SearchKH(LKH, p->CB.dsVe[i].CMND);
        strcpy(HoTen,KH->data.Ho);
        strcat(HoTen, " ");
        strcat(HoTen, KH->data.Ten);
        printf("%-8d|     %-8s|       %-16s|       %-33s|      %-9s",i+1, p->CB.dsVe[i].ViTriNgoi, p->CB.dsVe[i].CMND, HoTen, KH->data.Phai);
    }
    int key;
    do
    {
        key =getch();
        if(key==ESC)
        {
            system("cls");
            return;
        }
    }
    while(1);
}
void InDSHK(NODECB LCB, BSTKH LKH)
{
    int crtPage = 1;
    Normal();
    system("cls");
DSKH:
    ;
    gotoxy(55,7);
    SetColor(Yellow);
    cout<<"DANH SACH CHUYEN BAY";
    gotoxy(5,9);
    cout<<"STT     |    Ma Chuyen Bay   |     Ngay Khoi Hanh     |      San Bay Den      | Trang Thai | So Hieu May Bay | So Ve Da Dat | So Luong Ve "<<endl;
    gotoxy(5,10);
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

    int n = countCB(LCB);
LR:
    ;
    SetColor(Yellow);
    VeHCN(60,39,10,2);
    gotoxy(62,40);
    cout<<"PAGE :"<<crtPage;
    SetColor(White);
    int current = 0;
    int pages = n/numPageCBHK;
    if(n%numPageCBHK>0)
        pages++;
    if(!emptyLCB(LCB))
    {
        NODECB p,q;
        p=LCB;
        q=p; // in CB HILIGHT
        int i=(crtPage-1)*numPageCBHK; // dinh vi bien de duyet
        int c=0;
        while(c<i)
        {
            p=p->next;
            q=p;
            c++;
        }
        int y=11;
        for(; p!=NULL && i<crtPage*numPageCBHK; p=p->next)
        {
            gotoxy(5,y++);
            printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d",i+1,p->CB.MaCB,p->CB.NgayKhoiHanh.hour,p->CB.NgayKhoiHanh.min,p->CB.NgayKhoiHanh.day,p->CB.NgayKhoiHanh.month,p->CB.NgayKhoiHanh.year,
                   p->CB.SanBayDen,p->CB.TrangThai,p->CB.SoHieuMB,p->CB.SoVeDaDat,p->CB.MaxVe);
            i++;
        }
        gotoxy(5,11);
        HighLight();
        printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d",(crtPage-1)*15+1,q->CB.MaCB,q->CB.NgayKhoiHanh.hour,q->CB.NgayKhoiHanh.min,q->CB.NgayKhoiHanh.day,q->CB.NgayKhoiHanh.month,q->CB.NgayKhoiHanh.year,
               q->CB.SanBayDen,q->CB.TrangThai,q->CB.SoHieuMB,q->CB.SoVeDaDat,q->CB.MaxVe);
        int f = (crtPage-1)*numPageCBHK;// định vị vi tri dau phan tu trang
        int kytu;
        do
        {
            kytu = getch();
            if(kytu <=0)
                kytu = getch();
            switch(kytu)
            {
            case Up:
                if(current > 0)
                {
                    Normal();
                    gotoxy(5,current+11);
                    InMotCB(LCB,current+f);
                    current--;
                    HighLight();
                    gotoxy(5,current+11);
                    InMotCB(LCB,current+f);
                };
                break;
            case Down:
                if((crtPage==pages && current+1 <numPageCBHK-(pages*numPageCBHK-n)) || (crtPage<pages && current+1 <numPageCBHK))
                {
                    Normal();
                    gotoxy(5,current+11);
                    InMotCB(LCB,current+f);
                    current++;
                    HighLight();
                    gotoxy(5,current+11);
                    InMotCB(LCB,current+f);
                }
                break;

            case Right:
                if(crtPage<pages)
                {
                    crtPage++;
                    Normal();
                    for(int i =0; i< numPageCBHK; i++)
                        clearErr(1,11+i);
                    goto LR;
                }
                break;
            case Left:
                if(crtPage>1)
                {
                    crtPage--;
                    Normal();
                    for(int i =0; i< numPageCBHK; i++)
                        clearErr(1,11+i);
                    goto LR;
                }
                break;
            case Enter:
                DSKHOfCB(LCB,LKH, current+f);
                goto DSKH;
                break;
            case ESC:
                return;
            }
        }
        while(1);
    }
    getch();
}
//==============================================IN DANH SACH CHUYEN BAY KHOI HANH TRONG NGAY ======================================
void ShowDSCB(NODECB LCB,Date date)
{

    SetColor(14);
    VeHCN(15,0,25,2);
    gotoxy(17,1);
    cout<<"ESC: EXIT";

    VeHCN(45,0,70,2);
    gotoxy(47,1);
    cout<<"Trang Thai: 0 - Huy Chuyen,  1 - Con Ve, 2 - Het Ve,  3 - Hoan Tat";

    gotoxy(45,7);
    cout<<"DANH SACH CHUYEN BAY KHOI HANH TRONG NGAY "<<date.day<<"/"<<date.month<<"/"<<date.year<<" DEN SAN BAY "<<LCB->CB.SanBayDen;

    int current = 0;
    int n =countCB(LCB);
    gotoxy(5,9);
    cout<<"STT     |    Ma Chuyen Bay   |     Ngay Khoi Hanh     |      San Bay Den      | Trang Thai | So Hieu May Bay | So Ve Da Dat | So Luong Ve | So ve con trong"<<endl;
    gotoxy(5,10);
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    Normal();
    if(!emptyLCB(LCB))
    {

        NODECB p;
        int i=0;
        for(p=LCB; p!=NULL; p=p->next)
        {
            gotoxy(5,i+11);
            int veTrong = p->CB.MaxVe-p->CB.SoVeDaDat;
            printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d|    %-9d",i+1,p->CB.MaCB,p->CB.NgayKhoiHanh.hour,p->CB.NgayKhoiHanh.min,p->CB.NgayKhoiHanh.day,p->CB.NgayKhoiHanh.month,p->CB.NgayKhoiHanh.year,
                   p->CB.SanBayDen,p->CB.TrangThai,p->CB.SoHieuMB,p->CB.SoVeDaDat,p->CB.MaxVe, veTrong);
            i++;
        }

        int kytu;
        do
        {
            kytu = getch();
            if(kytu==ESC)
                return;
        }
        while(1);
    }
}
void NhapDateKhoiHanh(Date & date,int current,int x)
{
    SetColor(14);
    int ngaymax;
    gotoxy (x+46, current-2);
    cout <<"NGAY KHOI HANH CUA CHUYEN BAY : DD/MM/YYYY ";
DATE :
    ;
    SetColor(14);
    gotoxy(x+46,current);
    cout<<"   /    /       ";
    gotoxy(8,current);
    cout<<"NHAP NGAY ";
    gotoxy(x+46,current);
    char ngay[3];
    if(inputNum(ngay,2) == -1)
        return;
    date.day = atoi(ngay);

    gotoxy(8,current);
    cout<<"NHAP THANG ";
    gotoxy(x+51,current);
    char thang[3];
    if(inputNum(thang,2) == -1)
        return;
    date.month = atoi(thang);
    if (date.month<0 || date.month> 12 || date.day<0 || date.day> 31)
    {
        AlertErr(8,4,"Ngay thang khong hop le. Dung dinh dang dd/MM/yyyy!");
        Sleep(2000);
        clearErr(8,4);
        goto DATE;
    }
    clearErrDateKhoiHanh(8,current);

    gotoxy(8,current);
    cout<<"NHAP NAM ";
    gotoxy(x+57,current);
    char name[5];
    if(inputNum(name,4) == -1)
        return;
    date.year = atoi(name);

    tm *crt = currentTime();
    int yearCurrent = crt->tm_year + 1900;
    int monthCurrent = crt->tm_mon+1;  // tm_year cchi tra ve 120
    int dayCurrent = crt->tm_mday;
    if(date.year < yearCurrent || date.year == yearCurrent && date.month < monthCurrent || date.year == yearCurrent && date.month == monthCurrent && date.day < dayCurrent )
    {
        AlertErr(8,4,"DD/MM/YYYY PHAI LON HON THOI GIAN HIEN TAI");
        Sleep(2000);
        clearErr(8,4);
        goto DATE;
    }
    else
    {
        switch (date.month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            ngaymax=31;
            break;
        case 2:
            if (checkYear(date.year))
                ngaymax=29;
            else
                ngaymax=28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            ngaymax=30;
            break;
        }
        if (date.day>ngaymax)
        {
            AlertErr(8,4,"Kiem tra lai ngay trong thang!");
            Sleep(2000);
            clearErr(8,4);
            goto DATE;
        }
    }


}
//============================================== DANH SACH VE TRONG ==============================================
void VeTrong(NODECB p)
{
    for(int i= 0; i< p->CB.SoVeDaDat; i++)
    {
        char *vitringoi = p->CB.dsVe[i].ViTriNgoi;
        gotoxy(15,28+i);
        int d = vitringoi[0]-64;//vi tri day

        int c = 0;	//vi tri cot
        int len = strlen(vitringoi);

        for(int j = 1; j< strlen(vitringoi); j++)
        {
            c+= (vitringoi[j]-48) * pow(10,len-2);
            len--;
        }
        //SetColor(9);
        gotoxy(8+c*6-3,11+ d*2);
        cout<<"   ";

    }
}

void DSVT(NODECB LCB, LISTMB LMB)
{
BEGIN:
    ;
    Normal();
    system("cls");
    char MaCB[15];
    int key;

MACB:
    ;
    int x=11;
    int y= 13;
    gotoxy(10,7);
    SetColor(15);
    cout<<"NHAP VAO MA CHUYEN BAY: ";

    if(NhapMa(MaCB)==-1)
        return;

    NODECB p = searchCB(LCB,MaCB);
    if(p==NULL)
    {
        AlertErr(10,4,"MA CHUYEN BAY KHONG TON TAI!");
        Sleep(2000);
        clearErr(8,4);
        clearErr(10,7);
        goto MACB;

    }
    else
    {
        SetColor(14);
        VeHCN(8,0,20,2);
        gotoxy(10,1);
        SetColor(14);
        cout<<"ESC: EXIT";
        VeHCN(35,0,35,2);
        gotoxy(37,1);
        cout<<"F5: XEM VE TREN CHUYEN BAY KHAC";

        int i = SearchMB(LMB,p->CB.SoHieuMB);
        gotoxy(25,9);
        SetColor(14);
        cout<<"DANH SACH VE CON TRONG CUA CHUYEN BAY : "<<p->CB.MaCB<<endl;
        SetColor(15);
        int soDong = LMB.nodes[i]->soDong;
        int soDay = LMB.nodes[i]->soDay;
        gotoxy(11,13);
        for(int day = 1; day<= soDay; day++)
        {
            for(int dong =1; dong <= soDong; dong++)
            {
                printf("%c%-5d",char(day+64),dong);
            }
            y=y+2;
            gotoxy(11,y);
        }
        VeTrong(p);
        do
        {
            key = getch();
            //if(key <=0) key = getch();
            switch(key)
            {
            case F5:
            {
                goto BEGIN;
                break;
            }
            case ESC:
                return;
            }
        }
        while(1);

    }




}

void DSCBKHTN(NODECB LCB, LISTMB LMB)
{
START :
    ;
    Date date;
    Normal();
    system("cls");
    gotoxy(55,7);
    SetColor(14);
    cout <<"DANH SACH CAC CHUYEN BAY KHOI HANH TRONG NGAY dd/mm/yyyy NOI DEN XXXX ";
    NhapDateKhoiHanh(date, 12, 1);


    char sanBayDen[50];
    gotoxy (1+46, 14);
    cout << "NHAP VAO SAN BAY DEN:";
    fflush(stdin);
    NhapChuoi(sanBayDen,70,14);
    DelSpace(sanBayDen);

    Normal();
    system("cls");
    NODECB newLCB;
    Init(newLCB);
    if(!emptyLCB(LCB))
    {
        NODECB p;
        for(p = LCB; p!=NULL; p = p->next)
        {
            if(p->CB.NgayKhoiHanh.day == date.day && p->CB.NgayKhoiHanh.month==date.month && p->CB.NgayKhoiHanh.year==date.year&&p->CB.TrangThai==1&&strcmp(p->CB.SanBayDen,sanBayDen)==0)
            {
             insert_Last(newLCB,p->CB);
            }
        }
    }
    else
    {
        gotoxy(55,7);
        SetColor(14);
        cout <<"KHONG CO CHUYEN BAY NAO TRONG DANH SACH CHUYEN BAY !!!";
        getch();
    }

    if(!emptyLCB(newLCB))
    {
        ShowDSCB(newLCB,date);
    }
    else
    {
        gotoxy(55,7);
        SetColor(14);
        cout <<"KHONG TIM THAY CHUYEN BAY NAO !!!";
        getch();
    }
}
int main()
{

    LISTMB LMB;
    LMB.n=0;

    DocFileDSMB(FileDSMB,LMB);

    NODECB LCB;
    Init(LCB);
    DocFileDSCB(FileDSCB, LCB);

    BSTKH LKH;
    InitBST(LKH);
    DocFileDSKH(FileDSKH, LKH);
    int soluongmenu = 8;// so luong menu

    char a [8][70] = 	{ "1. QUAN LI MAY BAY",
                          "2. QUAN LI CHUYEN BAY",
                          "3. DAT VE",
                          "4. HUY VE",
                          "5. IN DANH SACH HANH KHACH TREN MOT CHUYEN BAY",
                          "6. IN DANH SACH CAC CHUYEN BAY KHOI HANH TRONG NGAY",
                          "7. IN DANH SACH CAC VE CON TRONG CUA MOT CHUYEN BAY",
                          "8. THONG KE SO LUOT THUC HIEN CHUYEN BAY CUA TUNG MAY BAY"
                      };
    // goi ham menu trong menu.h
    int m;
    do
    {

        ShowCur(false);
        TextColor(0x0004);
        system("cls");
        TextColor(Green);
        vekhung(68,35,1,30);
        PutCharXY(70,36,"ESC: THOAT | ENTER: XAC NHAN",Green);
        m = menu(55,10,a,soluongmenu);
        switch (m)
        {
        case  0 :
        {
            UpdateMB(LMB,LCB);
            break;
        }
        case 1:
        {
            UpdateCB(LCB, LMB);
            break;
        }
        case 2:
        {
            DatVe(LCB,LMB, LKH);
            break;
        }
        case 3:
        {
            HuyVe(LCB);
            break;

        }
        case 4:
        {
            InDSHK(LCB, LKH);
            break;
        }
        case 5:
        {

            DSCBKHTN(LCB, LMB);
            break;
        }
        case 6:
        {
            DSVT(LCB, LMB);
            break;
        }


        }
    }
    while(m!=-1);
    delete[] LMB.nodes;
    deleteAll(LCB);
    PutCharXY(55,21,"CAM ON BAN DA SU DUNG PHAN MEM!!",Cyan);
    Sleep(3000);
    return 0;
}








struct Date {
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;

 };
struct Ve{
	char ViTriNgoi[5];
	char CMND[11];
	//char MaCB[15];
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
typedef struct ChuyenBay CHUYENBAY;

struct nodeCB
{
    CHUYENBAY CB;
    struct nodeCB *pnextCB;
};
typedef struct nodeCB NODECB;
struct listCB
{
    int n = 0;
    NODECB *pHeadCB;
    NODECB *pTailCB;
};
typedef struct listCB LISTCB;
//extern void Init(NODECB &LCB);

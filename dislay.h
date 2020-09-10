
#ifndef _DISPLAY_H
#define _DISPLAY_H


//main menu-----
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
void khoitaoChuyenBay(LISTCB &L)
{
    L.pHeadCB = L.pTailCB = NULL;
}
void themDauChuyenBay(LISTCB &l,CHUYENBAY data)
{
   NODECB* k = createCB(data);
 k->pnextCB =l.pHeadCB;


}
#endif

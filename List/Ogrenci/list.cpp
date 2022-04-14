#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

struct ders {
    char derskodu[10];
    char dersadi[50];      //ders structi tanımlandi.
    ders* sonraki;
};

struct ogrenci {
    char ogrno[15];
    char ad[30];          //ogrenci structi tanimlandi.
    char soyad[30];     
    ders* dersdugumu;
    ogrenci* sonraki;
};
ogrenci* bas, * son;

void menu_yazdir();
void ara_menu();
bool islem_yap(char);
bool ara_islem(char);
void listekur(string);
ogrenci* dugum_olustur(char*, char*, char*, char*, char*);    //Butun fonksiyonlari tanimladik.
void ekle(char*, char*, char*, char*, char*);
void listele();
void ara();
void soyadno_ara(char*);
void ogrenciSil(char*);
void DersSil(char*,char*);
void dosyaYaz();
void kesisimBul(char*);
int main()
{
    listekur("mat101.txt");
    listekur("fiz101.txt");
    listekur("eng101.txt");
    bool bitir = false;
    char secim;
    while (!bitir) {
        menu_yazdir();
        cin >> secim;              //switch-case yaziliyor.
        bitir = islem_yap(secim);
    }

}

void menu_yazdir()
{
    cout << ("                         ---ISLEM MENUSU---") << endl;
    cout << ("  Yapmak istediginiz islem icin asagidaki durumlardan birini giriniz...") << endl;
    cout << ("  Arama yapmak icin: A") << endl;
    cout << ("  Ders silmek icin: D") << endl;
    cout << ("  Kesisim bulmak icin: K") << endl;         //menu elemanlari tanimlaniyor.
    cout << ("  Listeye yazdirmak icin: L") << endl;
    cout << ("  Ogrenci silmek icin: O") << endl;
    cout << ("  Dosyaya yaz : Y") << endl;
    cout << ("  Cikis icin: C") << endl;
    cout << ("  Seciminiz:");
}
bool islem_yap(char secim)
{
    char* numara;
    numara = new char();
    char* dersadi;
    dersadi = new char();
    char* derskod;              //Asagidaki fonksiyonlarin parametrelerini tanimliyor.
    derskod = new char();
    bool sonlandir = false;
    switch (secim) {
    case 'A': case 'a':
        ara();                   //Arama yapma kismi.
        break;
    case 'D': case 'd':
        cout << ("Ogrenci numarasini giriniz:");   //ögrenci numarasini ve ders adini alarak ders siler/.
        cin >> numara;
        cout << ("Ders adini giriniz:");
        cin >> dersadi;
        DersSil(numara,dersadi);
        break;
    case 'K': case 'k':
        cout << ("Gormek istediginiz ders kodunu giriniz:");   //ders kodunu yazip alan kisileri gösterir.
        cin >> derskod;
        kesisimBul(derskod);
        break;
    case 'L': case 'l':
        listele();                  //ögrencileri listeler.
        break;
    case 'O': case 'o':
        cout << ("Ogrenci numarasini giriniz:");  //ögrenci numarasi ile ögrenci siler.
        cin >> numara;
        ogrenciSil(numara);
        break;
    case 'Y':case 'y':
        dosyaYaz();         //sirala() fonksiyonunda ki degerleri toplam ogrenci dosyasina yazdirir.
        break;

    case 'C': case 'c':
        cout << "Programi sonlandirmak istediğinize emin misiniz? (E/H):";  //sistemden cikar.
        cin >> secim;                                
        if (secim == 'E' || secim == 'e')
            sonlandir = true;
        break;
    default:
        cout << "Hata: Yanlis giris yaptiniz" << endl;             //hatali harf girilmisse uyari verir ve sisteme geri döndürür.
        cout << "Tekrar deneyiniz {A, D, K, L, O, Y, C} :";
        cin >> secim;
        sonlandir = islem_yap(secim);
        break;
    }
    return sonlandir;
}

void listekur(string dosyalarTXT)
{
    ogrenci ogr;
    ders drs;
    ifstream dosyamat(dosyalarTXT);  //parametreler ile dosyadan veriler cekilir.
    char satir[75];
    dosyamat.getline(satir, 75);

    char* ptr = strtok(satir, " ");

    int i = 0;
    ptr = strtok(satir, "\t");
    while (i<2)
    {
        if (i == 0) { strcpy(drs.derskodu, ptr); }
        if (i == 1) { strcpy(drs.dersadi, ptr); }
        ptr = strtok(NULL, " ");
        i++;
    }
    dosyamat.getline(satir, 75);
    while (dosyamat) {
        ptr = strtok(satir, "\t");
        int j = 0;
        while (ptr != NULL)
        {
            if (j == 0) { strcpy(ogr.ogrno, ptr); }          //dosya dan verileri alir.
            if (j == 1) { strcpy(ogr.ad, ptr); }
            if (j == 2) { strcpy(ogr.soyad, ptr); }
            if (j == 3) { strcat(ogr.ad, " ");strcat(ogr.ad, ogr.soyad);strcpy(ogr.soyad, ptr); }
            ptr = strtok(NULL, " ");
            j++;
        }
        ekle(ogr.ogrno, ogr.ad, ogr.soyad, drs.derskodu, drs.dersadi); //ekle fonkisyonu ile baglantili listeye eklenir.
        dosyamat.getline(satir, 75);

    }
    dosyamat.close();

}

ogrenci* dugum_olustur(char* ogrno, char* ad, char* soyad, char* derskodu, char* dersadi)
{
    ogrenci* yeniogr;
    ders* yeniders;
    yeniogr = new ogrenci;
    strcpy(yeniogr->ogrno, ogrno);
    strcpy(yeniogr->ad, ad);
    strcpy(yeniogr->soyad, soyad);      //ögrenci dugumunu olusturur.
    yeniders = new ders;
    yeniogr->dersdugumu = yeniders;
    strcpy(yeniders->dersadi, dersadi);
    strcpy(yeniders->derskodu, derskodu);
    yeniders->sonraki = NULL;
    yeniogr->sonraki = NULL;
    return yeniogr;
}

void ekle(char* ogrno, char* ad, char* soyad, char* derskodu, char* dersadi)
{

    ogrenci* tara, * arka, * yeniogr;
    ders* yeniders;
    tara = bas;
    arka = son;

    if (bas == NULL)
    {
        bas = dugum_olustur(ogrno, ad, soyad, derskodu, dersadi);         //ilk dugum ekleniyor.
        return;
    }

    if (strcmp(ogrno, bas->ogrno) < 0)
    {
        yeniogr = dugum_olustur(ogrno, ad, soyad, derskodu, dersadi);  //listenin basina ekleniyor.
        yeniogr->sonraki = bas;
        bas = yeniogr;
        return;
    }

    while (tara && (strcmp(ogrno, tara->ogrno)) > 0)
    {
        arka = tara;
        tara = tara->sonraki;
    }

    if (tara && strcmp(ogrno, tara->ogrno) == 0)
    {
        yeniders = new ders;                               //daha once isim bilgileri eklenmisse dugume
        yeniders->sonraki = tara->dersdugumu;              //sadece ders bilgilerini ekliyor.
        tara->dersdugumu = yeniders;    
        strcpy(yeniders->derskodu, derskodu);
        strcpy(yeniders->dersadi, dersadi);
    }

    else {
        yeniogr = dugum_olustur(ogrno, ad, soyad, derskodu, dersadi);
        if (tara)
        {
            yeniogr->sonraki = tara;  //Dugumun arasina yeni isim ekliyor.
            arka->sonraki = yeniogr;
        }
        else
            arka->sonraki = yeniogr;
    }

}

void listele()
{
    ogrenci* tara;
    ders *dr;
    tara = bas;
    while (tara != NULL)
    {
        cout << tara->ogrno << " " << tara->ad << " " << tara->soyad<<endl;
        dr = tara->dersdugumu;                                                //while dongusu ile ogrenci bilgilerini ekrana yazdirir.
        while (dr != NULL)
        {
            cout << "\t\t\t" << dr->derskodu << " " << dr->dersadi<<endl;    //while dongusu ile ders bilgilerini ekrana yazdirir.
            dr = dr->sonraki;
        }
        tara = tara->sonraki;
    }
}

void ara()
{
    bool bitir = false;
    char secim1;
    while (!bitir) {
        ara_menu();
        cin >> secim1;               //ara switch-case ini calistiriyor.
        bitir = ara_islem(secim1);
    }
}
void ara_menu()
{
    cout << (" Soyada gore aramak icin (1)") << endl;
    cout << (" Numaraya gore aramak icin (2)") << endl;  //ara switch-case menusu yazdiriliyor.
    cout << ("cikmak icin: C") << endl;

}

bool ara_islem(char secim1)
{
    char *soyad;
    char* numara;
    soyad = new char();
    numara = new char();        //kullanilicak parametreler tanimlaniyor.
    bool son = false;
    switch (secim1)
    {
    case '1':
        cout << ("Ogrencinin soyadini giriniz:");
        cin >> soyad;
        soyadno_ara(soyad);            //soyada göre isim ariyor.
        break;

    case '2':
        cout << ("Ogrencinin numarasini giriniz:");
        cin >> numara;
        soyadno_ara(numara);        //numaraya göre isim ariyor.
        break;
    case 'C': case 'c':
        son= true;                //cikis yapiliyor
        break;
    default:
        cout << "Hata: Yanlis giris yaptiniz:" << endl;
        cout << "Tekrar deneyiniz {1,2,C} :";
        cin >> secim1;
        son = ara_islem(secim1);
        break;
    }
    return son;
}

void soyadno_ara(char *kisi)
{
    ogrenci* tara;
    ders* dr;
    int sayac=0;
    tara = bas;
    while (tara)
    {
        sayac++;
         if (strncmp(kisi, tara->soyad, strlen(kisi)) == 0)    //soyadi bulunan kisi yaziliyor.
        {
            cout << sayac << "." <<"kayit"<<" "<< tara->ogrno << " " << tara->ad << " " << tara->soyad << endl;
            dr = tara->dersdugumu;
            while (dr)            //kisinin ersleri yaziliyor
            {
                cout << "\t\t\t" << dr->derskodu << " " << dr->dersadi << endl;
                dr = dr->sonraki;
            }
        }
        else if (strncmp(kisi, tara->ogrno, strlen(kisi)) == 0)    //ogrno bulunan kisi yaziliyor.
        {
            cout << sayac << "." <<"kayit"<<" "<< tara->ogrno << " " << tara->ad << " " << tara->soyad << endl;
            dr = tara->dersdugumu;
            while (dr)            //kisinin dersleri yaziliyor.
            {
                cout << "\t\t\t" << dr->derskodu << " " << dr->dersadi << endl;
                dr = dr->sonraki;
            }
        }
        tara = tara->sonraki;
    }
}
void ogrenciSil(char *numara)
{
    ogrenci* tara,* arka;
    ders* dr;
    int sayac = 1;
    int kayitno = 0; //ogrencinin hangi sirada oldugunu buluyor.
    tara = bas;
    arka = son;
    while (tara) {       //
        kayitno++;
        if (strncmp(numara, tara->ogrno, strlen(numara)) == 0) {
            tara = NULL;                                          //ogrenciyi buluyor.
            continue;
        }
        tara = tara->sonraki;
    }
    tara = bas;
    if (kayitno == 1)     //1.ogrenci ise bu if e giriyor.
    {
        bas = bas->sonraki;
        dr = tara->dersdugumu;
        while (dr)       //ogrenci dersleri ile beraber siliniyor.
        {
            tara->dersdugumu = dr->sonraki;
            delete dr;
            dr =tara->dersdugumu;
        }
        delete tara;
        cout << ("Ogrenci basariyla silinmistir.") << endl;
        return;
    }
    while ((tara != NULL) && (sayac < kayitno))
    {
        arka = tara;
        tara = tara->sonraki;
        sayac++;
    }
    if (sayac < kayitno)  //verilen kayitno buyukk.
    {
        cout << ("Silinecek kayit bulunamadi.") << endl;
    }
    else       //ortadaki ve sondaki ogrencilerin kaydini bulup siliyor
    { 
        arka->sonraki = tara->sonraki;
        dr = tara->dersdugumu;
        while (dr)
        {
            tara->dersdugumu = dr->sonraki;
            delete dr;
            dr = tara->dersdugumu;
        }
        delete tara;
        cout << ("Ogrenci basariyla silinmistir.") << endl;
    }
}

void DersSil(char*numara,char*dersadi) 
{
    ogrenci* tara, * arka;
    ders* dr, * derstara, * dersarka;
    dersarka = new ders();
    int drssirano = 0, sayac = 1, sayac1=1, sirano = 0;
    tara = bas;
    arka = son;
    while (tara) {
        sirano++;
        if (strncmp(numara, tara->ogrno, strlen(numara)) == 0) {  //ogrenci numarasi ayni olan ogrenciyi buluyor.
            tara = NULL;
            continue;
        }
        arka = tara;
        tara = tara->sonraki;
    }
    tara = arka->sonraki;
    if (tara) {                         //ogrenci hangi dersleri var.
        derstara = tara->dersdugumu;
        while (derstara) {
            drssirano++;
            if (strncmp(dersadi, derstara->derskodu, strlen(dersadi)) == 0) {
                derstara = NULL;
                tara = NULL;
                continue;
            }
            derstara = derstara->sonraki;
        }
    }
    tara = bas;
    if (sirano == 1) {
        derstara = tara->dersdugumu;     //1.ogrencinin secilen dersini siliyor.
        if (drssirano == 1) {
            derstara = derstara->sonraki;
            dr = tara->dersdugumu;
            if (dr) {
                tara->dersdugumu = derstara;
                delete dr;
                cout << ("Sectiginiz ders basarili bir sekilde silinmistir.") << endl;
            }
            return;
        }
        while ((derstara != NULL) && (sayac1 < drssirano)) {
            dersarka = derstara;
            derstara = derstara->sonraki;
            sayac1++;
        }
        if (sayac1 < drssirano) {
            cout << ("Silinecek kayit bulunamadi") << endl;
        }
        else {
            dersarka->sonraki = derstara->sonraki;  //aradaki ve sondaki ogrencilerin islemlerini yapiyor.
            dr = derstara;
            if (dr) {
                delete dr;
                dr = dersarka;cout << ("Sectiginiz ders basarili bir sekilde silinmistir.") << endl;
            }
            return;
        }
    }
    while ((tara != NULL) && (sayac < sirano)) {
        arka = tara;
        tara = tara->sonraki;
        sayac++;
    }
    if (sayac < sirano) { // Verilen sira no cok buyuk
        cout << ("Silinecek kayit bulunamadi.")<<endl;
    }
    else { // Kayit bulundu
        derstara = tara->dersdugumu;
        if (drssirano == 1) {
            derstara = derstara->sonraki;
            dr = tara->dersdugumu;
            if (dr) {
                tara->dersdugumu = derstara;
                delete dr;
                dr = dersarka;
                cout << ("Sectiginiz ders basarili bir sekilde silinmistir.") << endl;
            }
            return;
        }
        while ((derstara != NULL) && (sayac1 < drssirano)) {
            dersarka = derstara;
            derstara = derstara->sonraki;
            sayac1++;
        }
        if (sayac1 < drssirano) {
            cout << ("Silinecek kayit bulunamadi.")<<endl;
        }
        else {
            drssirano++;
            dersarka->sonraki = derstara->sonraki;
            dr = derstara;
            if (dr) {
                delete dr;
                dr = dersarka;
                cout << ("Sectiginiz ders basarili bir sekilde silinmistir.") << endl;
            }
        }
    }
}
void dosyaYaz()
{
    FILE *dosya;
    dosya=fopen("toplamogrenci.txt","w+");  //dosya aciliyor.

    ogrenci* tara;
    ders* dr;

    tara = bas;
    while (tara != NULL) //while ile dugumdeki bütün ogrenciler ve dersleri dosyaya aktariliyor.
    {
        fprintf(dosya,"%s %s %s \n",tara->ogrno ,tara->ad ,tara->soyad);
        dr = tara->dersdugumu;
        while (dr != NULL)
        {
       fprintf(dosya,"\t\t\t %s %s \n",dr->derskodu,dr->dersadi);
            dr = dr->sonraki;
        }
        tara = tara->sonraki;
    }
    fclose(dosya);
}
void kesisimBul(char *derskod)  //girilen dersi alan kisileri buluyor.
{
    ogrenci* tara;
    ders* dr;
    int sayac = 0;
    tara = bas;
    while (tara)
    {
        sayac++;
        dr = tara->dersdugumu;
        if (strncmp(derskod, dr->derskodu, strlen(derskod)) == 0)
        {
            cout << sayac << "." << "kayit" << " " << tara->ogrno << " " << tara->ad << " " << tara->soyad << endl;      
        }
        tara = tara->sonraki;
    }  
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Yazar
{
	int yazarID;
	char yazarAd[30];
	char yazarSoyad[30];
	struct Yazar* next;
}YAZAR;
typedef struct Ogrenci
{
	char ogrID[9]; 
	char ad[30]; 
	char soyad[30]; 
	int puan; 
	struct Ogrenci *next; 
	struct Ogrenci *prev;
}OGRENCI;
typedef struct KitapOrnek
{
	char EtiketNo[20]; 
	char Durum[8]; 
	struct KitapOrnek *next; 
}KITAP_ORNEK;
typedef struct Kitap 
{
	char kitapAdi[30];
	char ISBN[14]; 
	int adet; 
	struct Kitap *next; 
	struct KitapOrnek *head; 
}KITAP;
typedef struct KitapYazar
{
	char ISBN[13];
	int YazarID;
}KITAP_YAZAR;
typedef struct Tarih
{
	unsigned int gun:5;
	unsigned int ay:4;
	unsigned int yil:12;
}TARIH;
typedef struct KitapOdunc
{
	char EtiketNo[20];
	char ogrID[9];
	unsigned int islemTipi:1;
	struct Tarih islemTarihi;
}KITAP_ODUNC;

//FONKSIYON IMZALARI

int GecersizGiris();
int	EkleSilGuncelle();
void Menu();
void Kutuphane_Otomasyonu();
void initialStart();

void YazarMenusu();
void OgrenciMenusu();
void KitapMenusu();

void okuYazarlar(YAZAR**);
void okuOgrenciler(OGRENCI**);
void okuKitaplar(KITAP**);
void okuKitapYazar(KITAP_YAZAR***,int*);
void okuKitapOdunc(KITAP_ODUNC***,int*,KITAP*);

void fileYazarYaz(YAZAR*);
void fileOgrenciYaz(OGRENCI*);
void fileKitapYaz(KITAP*);
void fileKitapYazarYaz(KITAP_YAZAR**,int);
void fileKitapOduncYaz(KITAP_ODUNC**,int);

void printYazar(YAZAR*,char*,char*,KITAP_YAZAR**,int,KITAP*);
void printOgrenci(OGRENCI*,char*,char*,KITAP_ODUNC**,int);
void printOgrenciList(OGRENCI*,KITAP_ODUNC**,int,OGRENCI* (*Kosul)(OGRENCI*,KITAP_ODUNC**,int));
void printKitap(KITAP*,char*);
void printLogs(OGRENCI*,KITAP_ODUNC**,int);
void printKitapOdunc(KITAP_ODUNC**,int);
void printListKitap(KITAP*,KITAP_ODUNC**,int,KITAP_ORNEK* (*KosulK)(KITAP_ORNEK*,KITAP_ODUNC**,int)); 
void teslimedilmeyenler(KITAP*,KITAP_ODUNC**,int,TARIH);
void raftakiler(KITAP*,KITAP_ODUNC**,int);

void guncelleKitapYazarforYazar(KITAP_YAZAR**,int,YAZAR*);
void guncelleKitapYazarforKitap(KITAP_YAZAR**,int,KITAP*);
void guncelleKitapYazarforUpdate(KITAP*,char*,KITAP_YAZAR**,int);
void guncelleKitapOrnek(KITAP*,KITAP_ODUNC**,int);
void guncelleKitapOduncforOgrenciUpdate(OGRENCI*,char*,KITAP_ODUNC**,int);
void guncelleKitapOrnekforKitapUpdate(KITAP*,char*,KITAP_ODUNC**,int);
void guncelleKitapOduncforKitapUpdate(KITAP_ORNEK*,KITAP_ODUNC**,int,char*);
void guncelleKitapOrnekforOgrenciUpdate(OGRENCI*,char*,KITAP*);


YAZAR* bulYazar(YAZAR*,char*,char*);
YAZAR* addYazarfromFile(YAZAR*,int,char*,char*);
YAZAR* addYazar(YAZAR*,char*,char*);
YAZAR* deleteYazar(YAZAR*,char*,char*);
YAZAR* updateYazar(YAZAR*,char*,char*);


OGRENCI* bulOgrenci(OGRENCI*,char*,char*);
OGRENCI* addOgrencifromFile(OGRENCI*,char*,char*,char*,int);
OGRENCI* addOgrenci(OGRENCI*,char*,char*,KITAP_ODUNC**,int,KITAP*);
OGRENCI* deleteOgrenci(OGRENCI*,char*,char*,KITAP_ODUNC**,int,KITAP*);
OGRENCI* updateOgrenci(OGRENCI*,char*,char*,KITAP_ODUNC**,int,KITAP*);
OGRENCI* kosulYok(OGRENCI*,KITAP_ODUNC**,int);
OGRENCI* kosulKitapTeslimEtmeyen(OGRENCI*,KITAP_ODUNC**,int);
OGRENCI* kosulCezali(OGRENCI*,KITAP_ODUNC**,int);


KITAP* bulKitap(KITAP*,char*);
KITAP* addKitapfromFile(KITAP*,char*,char*,int);
KITAP* addKitap(KITAP*,char*,KITAP_YAZAR**,int,KITAP_ODUNC**,int);
KITAP* deleteKitap(KITAP*,char*,KITAP_YAZAR**,int,KITAP_ODUNC**,int);
KITAP* updateKitap(KITAP*,char*,KITAP_YAZAR**,int,KITAP_ODUNC**,int);


KITAP_ORNEK* bulKitapOrnekforAdd(KITAP*,char*);
KITAP_ORNEK* bulKitapOrnekforDelete(KITAP*,char*,OGRENCI*);

KITAP_YAZAR** addKitapYazar(KITAP_YAZAR**,int*,YAZAR*,char*,char*,KITAP*,char*);
KITAP_YAZAR** guncelleKitapYazar(KITAP_YAZAR**,int*,YAZAR*,char*,char*,KITAP*,char*);

KITAP_ODUNC** addKitapOdunc(KITAP_ODUNC**,int*,KITAP*,char*,OGRENCI*,char*,char*);

TARIH tarihAl(KITAP_ODUNC**,int);
int cmpTarih(TARIH,TARIH);

//FONKSIYONLAR

int EkleSilGuncelle()
{
	int secim;
	printf("\n");
	printf("		EKLE			'0'\n");
	printf("		SIL			'1'\n");
	printf("		GUNCELLE		'2'\n");
	printf("\n			    ");
	scanf("%d",&secim);
	while(secim>2 || secim<0)
		secim= GecersizGiris();
	return secim;
}
int GecersizGiris()
{
	int giris;
	printf("	YANLIS BIR GIRIS LUTFEN DOGRU BIR GIRIS YAPINIZ!\n    			    ");
	scanf("%d",&giris);
	return giris;
}
void initialStart(YAZAR** headYazar,OGRENCI** headOgrenci,KITAP** headKitap,KITAP_YAZAR*** arrKitapYazar,int* kitap_yazar,KITAP_ODUNC*** arrKitapOdunc,int* kitap_odunc)
{
	okuYazarlar(headYazar);
	okuOgrenciler(headOgrenci);
	okuKitaplar(headKitap);
	okuKitapYazar(arrKitapYazar,kitap_yazar);
	okuKitapOdunc(arrKitapOdunc,kitap_odunc,*headKitap);	
}
void Menu()
{
	int secim;
	KITAP* headKitap = NULL;
	OGRENCI* headOgrenci= NULL;
	YAZAR* headYazar = NULL;
	KITAP_ODUNC** arrKitapOdunc = (KITAP_ODUNC**)malloc(sizeof(KITAP_ODUNC*));
	int kitap_odunc = 0;
	KITAP_YAZAR** arrKitapYazar = (KITAP_YAZAR**)malloc(sizeof(KITAP_YAZAR*));
	int kitap_yazar = 0;
	
	initialStart(&headYazar,&headOgrenci,&headKitap,&arrKitapYazar,&kitap_yazar,&arrKitapOdunc,&kitap_odunc);
			
	printf("\n");
	printf("====================");
	printf("        MENU        ");
	printf("====================");
	printf("\n");
	
	printf("		YAZAR ISLEMLERI ICIN      '0'\n");
	printf("		OGRENCI ISLEMLERI ICIN    '1'\n");
	printf("		KITAP ISLEMLERI ICIN      '2'\n");
	printf("		CIKIS YAPMAK ICIN	  '9' ");
	printf("\n			    ");
	scanf("%d",&secim);
	while((secim>2 || secim<-1) && secim!= 9)
		secim = GecersizGiris();
	switch(secim)
	{
		case 0:
			YazarMenusu(&headYazar,&arrKitapYazar,kitap_yazar,headKitap);
			break;
		case 1:
			OgrenciMenusu(&headOgrenci,&arrKitapOdunc,&kitap_odunc,headKitap);
			break;
		case 2:
			KitapMenusu(&headKitap,&arrKitapYazar,&kitap_yazar,&headYazar,arrKitapOdunc,&kitap_odunc);
			break;
		case 9:
			exit(0);
			break;
	}
}
void Kutuphane_Otomasyonu()
{
	int exit = 1;

	printf("\n");
	printf("====================");
	printf("KUTUPHANE OTOMASYONU");
	printf("====================");
	printf("\n");
	
	while(exit)
		Menu();
}
int main()
{
	Kutuphane_Otomasyonu();
	return 0;
}



void YazarMenusu(YAZAR** head,KITAP_YAZAR*** arrKY,int ky,KITAP* khead)
{
	int exit=1,secim,index;
	char tmpad[20],tmpsoyad[20];
	YAZAR*(*Option[])(YAZAR*,char*,char*)={addYazar,deleteYazar,updateYazar};
	while(exit)
	{
		printf("\n");
		printf("====================");
		printf("  	YAZAR MENUSU	");
		printf("====================");
		printf("\n");
	
		printf("		YAZAR EKLE, SIL, GUNCELLE  '0'\n");
		printf("		YAZAR BILGISI GORUNTULEME  '1'\n");
		printf("		ANA MENUYE DONMEK  	   '9'\n");
		printf("\n			    ");
		scanf("%d",&secim);
		while((secim>1 || secim<0) && secim!= 9)
			secim = GecersizGiris();
		switch(secim)
		{
			case 0:
				index = EkleSilGuncelle();
				printf(" 	\"Yazaradi Yazarsoyadi\" formatinda giris yapiniz!\n			");
				scanf("%s %s",tmpad,tmpsoyad);
				*head = (*Option[index])(*head,tmpad,tmpsoyad);
				guncelleKitapYazarforYazar(*arrKY,ky,*head);	
				break;
			case 1:
				printf(" 	\"Yazaradi Yazarsoyadi\" formatinda giris yapiniz!\n			");
				scanf("%s %s",tmpad,tmpsoyad);
				printYazar(*head,tmpad,tmpsoyad,*arrKY,ky,khead);
				break;
			case 9:
				exit = 0;
				break;
		}
	}

}
void OgrenciMenusu(OGRENCI** head,KITAP_ODUNC*** arrKO,int* ko,KITAP* khead)
{
	int secim,exit=1,index;
	char tmpad[30],tmpsoyad[30],tmpid[9],kad[50];
	OGRENCI* (*Option[])(OGRENCI*,char*,char*,KITAP_ODUNC**,int,KITAP*)={addOgrenci,deleteOgrenci,updateOgrenci};
	OGRENCI* (*Kosul[])(OGRENCI*,KITAP_ODUNC**,int)={kosulYok,kosulKitapTeslimEtmeyen,kosulCezali};
	while(exit)
	{	
		printf("\n");
		printf("====================");
		printf("   OGRENCI MENUSU	");
		printf("====================");
		printf("\n");
	
		printf("	OGRENCI EKLE, SIL, GUNCELLE      	 '0'\n");
		printf("	OGRENCI BILGISI GORUNTULEME      	 '1'\n");
		printf(" 	KITAP TESLIM ETMEMIS OGRENCILERI LISLETE '2'\n");
		printf("	CEZALI OGRENCILERI LISTELE       	 '3'\n");
		printf("	TUM OGRENCILERI LISTELE    	 	 '4'\n");
		printf("	KITAP ODUNC AL/TESLIM ET	     	 '5'\n");
		printf("	ANA MENUYE DONMEK  	   		 '9'\n");
		printf("\n			    ");
		scanf("%d",&secim);
		while((secim>5 || secim<0) && secim!= 9)
			secim = GecersizGiris();
		switch(secim)
		{
			case 0:
				index = EkleSilGuncelle();
				printf(" 	\"Ogrenciadi Ogrencisoyadi\" formatinda giris yapiniz!\n			");
				scanf("%s %s",tmpad,tmpsoyad);
				*head = (*Option[index])(*head,tmpad,tmpsoyad,*arrKO,*ko,khead);
				break;
			case 1:
				printf(" 	\"Ogrenciadi Ogrencisoyadi\" formatinda giris yapiniz!\n			");
				scanf("%s %s",tmpad,tmpsoyad);
				printOgrenci(*head,tmpad,tmpsoyad,*arrKO,*ko);
				break;
			case 2:
				printOgrenciList(*head,*arrKO,*ko,Kosul[1]);
				break;
			case 3:
				printOgrenciList(*head,*arrKO,*ko,Kosul[2]);
				break;
			case 4:
				printOgrenciList(*head,*arrKO,*ko,Kosul[0]);
				break;
			case 5:
				printf(" 	\"Ogrenciadi Ogrencisoyadi\" formatinda giris yapiniz!\n			");
				scanf("%s %s",tmpad,tmpsoyad);
				printf("	   \"Kitapadi\" formatinda giris yapiniz!\n			");
				fflush(stdin);
				scanf("%[^\n]",kad);				
				*arrKO = addKitapOdunc(*arrKO,ko,khead,kad,*head,tmpad,tmpsoyad);
				break;
			case 9:
				exit = 0;
				break;
		}
	}
}
void KitapMenusu(KITAP** head,KITAP_YAZAR*** arrKY,int* ky,YAZAR** yhead,KITAP_ODUNC** arrKO,int* ko)
{
	int secim,exit = 1,tmpadet,index;
	char tmpad[50],tmpisbn[15],yAd[30],ySoyad[30];
	TARIH t;
	KITAP* (*Option[])(KITAP*,char*,KITAP_YAZAR**,int,KITAP_ODUNC**,int)={addKitap,deleteKitap,updateKitap};
	while(exit)
	{
		printf("\n");
		printf("====================");
		printf("  	KITAP MENUSU	");
		printf("====================");
		printf("\n");
	
		printf("	KITAP EKLE, SIL, GUNCELLE      	 	    '0'\n");
		printf("	KTIAP BILGISI GORUNTULEME      	 	    '1'\n");
		printf(" 	RAFTAKI KITAPLARI GORUNTULEME 		    '2'\n");
		printf("	ZAMANINDA TESLIM EDILMEYEN KITAPLARI LISTELE'3'\n");
		printf("	KITAP YAZAR ESLESTIR    	 	    '4'\n");
		printf("	KITABIN YAZARINI GUNCELLE	     	    '5'\n");
		printf("	ANA MENUYE DONMEK  	   		    '9'\n");
		printf("\n			    ");
		scanf("%d",&secim);
		while((secim>5 || secim<0) && secim!= 9)
			secim = GecersizGiris();
		switch(secim)
		{
			case 0:
				index = EkleSilGuncelle();
				printf("	   \"Kitapadi\" formatinda giris yapiniz!\n			");
				fflush(stdin);
				scanf("%[^\n]",tmpad);
				*head = (*Option[index])(*head,tmpad,*arrKY,*ky,arrKO,*ko);
				guncelleKitapYazarforKitap(*arrKY,*ky,*head);
				break;
			case 1:
				printf("	   \"Kitapadi\" formatinda giris yapiniz!\n			");
				fflush(stdin);
				scanf("%[^\n]",tmpad);
				printKitap(*head,tmpad);
				break;
			case 2:
				raftakiler(*head,arrKO,*ko);
				break;
			case 3:
				t = tarihAl(arrKO,*ko);
				teslimedilmeyenler(*head,arrKO,*ko,t);
				break;
			case 4:
				printf("	   \"Kitapadi\" formatinda giris yapiniz!\n			");
				fflush(stdin);
				scanf("%[^\n]",tmpad);
				printf(" 	\"Yazaradi Yazarsoyadi\" formatinda giris yapiniz!\n			");
				scanf("%s %s",yAd,ySoyad);				
				*arrKY = addKitapYazar(*arrKY,ky,*yhead,yAd,ySoyad,*head,tmpad);
				break;
			case 5:
				printf("	   \"Kitapadi\" formatinda giris yapiniz!\n			");
				fflush(stdin);
				scanf("%[^\n]",tmpad);
				printf(" 	\"Yazaradi Yazarsoyadi\" formatinda giris yapiniz!\n			");
				scanf("%s %s",yAd,ySoyad);				
				*arrKY = guncelleKitapYazar(*arrKY,ky,*yhead,yAd,ySoyad,*head,tmpad);				
				break;
			case 9:
				exit = 0;
				break;
		}
		
	}
}



void okuYazarlar(YAZAR** head)
{
	FILE* file;
	char tmpid[3],tmpad[30],tmpsoyad[30],tmp[500];	
	
	file = fopen("Yazarlar.csv","r");
	while (!feof(file))
    {
		fscanf(file,"%s\n",tmp);
		strcpy(tmpid,strtok(tmp,","));
		strcpy(tmpad,strtok(NULL,","));
		strcpy(tmpsoyad,strtok(NULL,","));
		*head = addYazarfromFile(*head,atoi(tmpid),tmpad,tmpsoyad);
	}
	fclose(file);
}
void okuOgrenciler(OGRENCI** head)
{
	FILE* file;
	char tmpid[9],tmpad[30],tmpsoyad[30],tmppuan[4],tmp[500];	
	
	file = fopen("Ogrenciler.csv","r");
	while (!feof(file))
    {
		fscanf(file,"%s\n",tmp);
		strcpy(tmpid,strtok(tmp,","));
		strcpy(tmpad,strtok(NULL,","));
		strcpy(tmpsoyad,strtok(NULL,","));
		strcpy(tmppuan,strtok(NULL,","));
		*head = addOgrencifromFile(*head,tmpid,tmpad,tmpsoyad,atoi(tmppuan));
	}
	fclose(file);
}
void okuKitaplar(KITAP** head)
{
	FILE* file;
	char tmpad[50],tmpisbn[20],tmpadet[3],tmp[500];
	
	file = fopen("Kitaplar.csv","r");
	while (!feof(file))
    {
		fscanf(file,"%[^\n]\n",tmp);
		strcpy(tmpad,strtok(tmp,","));
		strcpy(tmpisbn,strtok(NULL,","));
		strcpy(tmpadet,strtok(NULL,","));
		*head = addKitapfromFile(*head,tmpad,tmpisbn,atoi(tmpadet));
	}
	fclose(file);	
}
void okuKitapYazar(KITAP_YAZAR*** arrKitapYazar,int* kitapyazar)
{
	FILE* file;
	int i;
	char tmpisbn[20],tmpid[2],tmpstr[50];
	KITAP_YAZAR** tmp;
		
	file = fopen("KitapYazar.csv","r");
	while(!feof(file))
	{
		fscanf(file,"%[^\n]\n",tmpstr);
		(*kitapyazar)++;
	}
	fclose(file);
	tmp=(KITAP_YAZAR**)malloc(sizeof(KITAP_YAZAR*)*(*kitapyazar));
	for(i=0;i<*kitapyazar;i++)
		tmp[i] = (KITAP_YAZAR*)malloc(sizeof(KITAP_YAZAR)); 
	fopen("KitapYazar.csv","r");
	i = 0;
	while (!feof(file))
    {
		fscanf(file,"%[^\n]\n",tmpstr);
		strcpy(tmpisbn,strtok(tmpstr,","));
		strcpy(tmpid,strtok(NULL,","));
		strcpy(tmp[i]->ISBN,tmpisbn);
		(tmp[i])->YazarID = atoi(tmpid);
		*arrKitapYazar = tmp;	
		i++;
	}
	fclose(file);	
}
void okuKitapOdunc(KITAP_ODUNC*** arrKitapOdunc,int* kitapodunc,KITAP* head)
{
	FILE* file;
	int i;
	char tmpdata[20],tmpstr[100],tmptarih[5];
	KITAP_ODUNC** tmp;
	
	file = fopen("KitapOdunc.csv","r");
	while(!feof(file))
	{
		fscanf(file,"%[^\n]\n",tmpstr);
		(*kitapodunc)++;
	}
	fclose(file);
	tmp=(KITAP_ODUNC**)malloc(sizeof(KITAP_ODUNC*)*(*kitapodunc));
	for(i=0;i<*kitapodunc;i++)
		tmp[i] = (KITAP_ODUNC*)malloc(sizeof(KITAP_ODUNC)); 
	fopen("KitapOdunc.csv","r");
	i = 0;
	while (!feof(file))
    {
		fscanf(file,"%[^\n]\n",tmpstr);
		strcpy(tmpdata,strtok(tmpstr,","));
		strcpy(tmp[i]->EtiketNo,tmpdata);		
		strcpy(tmpdata,strtok(NULL,","));
		strcpy(tmp[i]->ogrID,tmpdata);
		strcpy(tmpdata,strtok(NULL,","));
		tmp[i]->islemTipi=atoi(tmpdata);
		strcpy(tmpdata,strtok(NULL,","));
		strcpy(tmptarih,strtok(tmpdata,"."));
		tmp[i]->islemTarihi.gun=atoi(tmptarih);
		strcpy(tmptarih,strtok(NULL,"."));
		tmp[i]->islemTarihi.ay=atoi(tmptarih);
		strcpy(tmptarih,strtok(NULL,","));
		tmp[i]->islemTarihi.yil=atoi(tmptarih);
		*arrKitapOdunc = tmp;
		i++;
	}
	fclose(file);
	guncelleKitapOrnek(head,*arrKitapOdunc,*kitapodunc);	
}



void fileYazarYaz(YAZAR* head)
{
	FILE* file;
	YAZAR* iter = head;
	 
	file = fopen("Yazarlar.csv","w+");
	while(iter)
	{
		fprintf(file,"%d,",iter->yazarID);
		fprintf(file,"%s,",iter->yazarAd);
		fprintf(file,"%s\n",iter->yazarSoyad);
		iter = iter->next;	
	}
	fclose(file);	
}
void fileOgrenciYaz(OGRENCI* head)
{
	FILE* file;
	OGRENCI* iter = head;
	 	
	file = fopen("Ogrenciler.csv","w+");
	while(iter)
	{
		fprintf(file,"%s,",iter->ogrID);
		fprintf(file,"%s,",iter->ad);
		fprintf(file,"%s,",iter->soyad);
		fprintf(file,"%d\n",iter->puan);
		iter = iter->next;	
	}
	fclose(file);	
}
void fileKitapYaz(KITAP* head)
{
	FILE* file;
	KITAP* iter = head;
		
	file = fopen("Kitaplar.csv","w+");
	while(iter)
	{
		fprintf(file,"%s,",iter->kitapAdi);
		fprintf(file,"%s,",iter->ISBN);
		fprintf(file,"%d\n",iter->adet);
		iter = iter->next;
	}
	fclose(file);	
}
void fileKitapYazarYaz(KITAP_YAZAR** arr,int kitapyazar)
{
	int i;
	FILE* file;
	
	file = fopen("KitapYazar.csv","w+");	
	for(i=0;i<kitapyazar;i++)
	{
		fprintf(file,"%s,",arr[i]->ISBN);
		fprintf(file,"%d\n",arr[i]->YazarID);
	}
	fclose(file);	

}
void fileKitapOduncYaz(KITAP_ODUNC** arr,int kitapodunc)
{
	int i;
	FILE* file;
	
	file = fopen("KitapOdunc.csv","w+");	
	for(i=0;i<kitapodunc;i++)
	{
		fprintf(file,"%s,",arr[i]->EtiketNo);
		fprintf(file,"%s,",arr[i]->ogrID);
		fprintf(file,"%d,",arr[i]->islemTipi);
		fprintf(file,"%d.%d.%d\n",arr[i]->islemTarihi.gun,arr[i]->islemTarihi.ay,arr[i]->islemTarihi.yil);
	}
	fclose(file);	

}



void printYazar(YAZAR* head,char* ad,char* soyad,KITAP_YAZAR** arr,int kitapyazar,KITAP* khead)
{
	YAZAR* prev = bulYazar(head,ad,soyad);
	YAZAR* iter;
	KITAP* iterk;
	int i;
		
	if(prev == NULL)
		printf("                         Bulunamadi!                         \n");
	else
	{
		if(prev== head)
		{
			if(strcmp(prev->yazarAd,ad)==0 && strcmp(prev->yazarSoyad,soyad)==0)
				iter = prev;
			else
				iter = prev->next;
		}
		else
			iter = prev->next;
		printf("=================================================\n");
		printf("ID: %d\nAd: %s\nSoyad: %s\n",iter->yazarID,iter->yazarAd,iter->yazarSoyad);
		printf("=================================================\n");
		for(i=0;i<kitapyazar;i++)
		{
			if(arr[i]->YazarID == iter->yazarID)
			{
				iterk = khead;
				while(iterk)
				{
					if(strcmp(iterk->ISBN,arr[i]->ISBN)==0)
					{
						printKitap(khead,iterk->kitapAdi);	
					}
					iterk = iterk->next;
				}
			}
		}
	}
}
void printOgrenci(OGRENCI* head,char* ad,char* soyad,KITAP_ODUNC** arr,int kitapodunc)
{
	OGRENCI* iter = bulOgrenci(head,ad,soyad);
	if(iter == NULL)
		printf("                         Bulunamadi!                         \n");
	else		
	{
		printf("=================================================\n");
		printf("ID:%s\nAd:%s\nSoyad:%s\nPuan:%d\n\n",iter->ogrID,iter->ad,iter->soyad,iter->puan);
		printLogs(iter,arr,kitapodunc);
		printf("=================================================\n");
	}
}
void printOgrenciList(OGRENCI* head,KITAP_ODUNC** arr,int kitapodunc,OGRENCI* (*Kosul)(OGRENCI* head,KITAP_ODUNC** arr,int kitapodunc))
{
	OGRENCI* iter = head;
	while(iter)
	{
		if(Kosul(iter,arr,kitapodunc))
			printOgrenci(head,iter->ad,iter->soyad,arr,kitapodunc);
		iter = iter->next;
	}
}
void printKitapOrnek(KITAP_ORNEK* ko)
{
	printf("Etiket: %s		Durum: %s\n",ko->EtiketNo,ko->Durum);
}
void printKitap(KITAP* head,char* ad)
{
	KITAP* prev = bulKitap(head,ad);
	KITAP* iter;
	KITAP_ORNEK* iterornek;
	if(prev == NULL)
		printf("                         Bulunamadi!                         \n");
	else
	{
		if(prev == head)
		{
			if(strcmp(prev->kitapAdi,ad)==0)
				iter = prev;
			else
				iter = prev->next;
		}
		else
			iter = prev->next;
		printf("================================================\n");
		printf("KitapAdi:%s\nKitapISBN:%s\n\n",iter->kitapAdi,iter->ISBN);
		iterornek = iter->head;
		while(iterornek)
		{
			printKitapOrnek(iterornek);
			iterornek = iterornek->next;
		}
		printf("================================================\n");
	}	
}
void printKitapOdunc(KITAP_ODUNC** arr,int i)
{	
	printf("Etiket: %s     OgrenciID: %s     IslemTipi: %d     Tarih: %d.%d.%d\n",arr[i]->EtiketNo,arr[i]->ogrID,arr[i]->islemTipi,arr[i]->islemTarihi.gun,arr[i]->islemTarihi.ay,arr[i]->islemTarihi.yil);
}
void printLogs(OGRENCI* o,KITAP_ODUNC** arr,int kitapodunc)
{
	int i;
	for(i=0;i<kitapodunc;i++)
	{
		if(strcmp(arr[i]->ogrID,o->ogrID)==0)
			printKitapOdunc(arr,i);
	}
}
void raftakiler(KITAP* head,KITAP_ODUNC** arr,int kitapodunc)
{
	KITAP* iter = head;
	KITAP_ORNEK* iterornek;
	while(iter)
	{
		printf("=================================================\n");
		printf("Kitap: %s\nISBN: %s\n\n",iter->kitapAdi,iter->ISBN);
		iterornek = iter->head;
		while(iterornek)
		{
			if(strcmp(iterornek->Durum,"RAFTA")==0)
				printKitapOrnek(iterornek);
			iterornek = iterornek->next;
		}
		printf("=================================================\n");
		iter = iter->next;
	}
}
void teslimedilmeyenler(KITAP* head,KITAP_ODUNC** arr,int kitapodunc,TARIH t)
{
	int i,flag = 0,j;
	KITAP* iter = head;
	KITAP_ORNEK* iterornek;
	TARIH t2;
	printf("=================================================\n");
	while(iter)
	{
		iterornek = iter->head;
		while(iterornek)
		{
			flag = 0;
			for(i=0;i<kitapodunc;i++)
			{
				if(strcmp(arr[i]->EtiketNo,iterornek->EtiketNo)==0 && arr[i]->islemTipi == 0)
				{
					t2 = arr[i]->islemTarihi;
					flag = 1;
					for(j=i+1;j<kitapodunc;j++)
					{
						if(strcmp(arr[j]->EtiketNo,iterornek->EtiketNo)==0 && arr[j]->islemTipi == 1)
							flag = 0;	
					}
				}
			}
			if(flag && cmpTarih(t,t2)>15)
				printKitapOrnek(iterornek);
			iterornek= iterornek->next;
		}
		iter = iter->next;
	}
	printf("=================================================\n");	
}



void guncelleKitapOrnek(KITAP* head,KITAP_ODUNC** arr,int kitapodunc)
{
	KITAP* iter = head;
	KITAP_ORNEK* iterornek;
	int i;
	while(iter)
	{
		iterornek = iter->head;
		while(iterornek)
		{
			for(i=0;i<kitapodunc;i++)
			{
				if(strcmp(arr[i]->EtiketNo,iterornek->EtiketNo)==0 && arr[i]->islemTipi == 0)
					strcpy(iterornek->Durum,arr[i]->ogrID);
				else if(strcmp(arr[i]->EtiketNo,iterornek->EtiketNo)==0 && arr[i]->islemTipi == 1)
					strcpy(iterornek->Durum,"RAFTA");
			}
			iterornek= iterornek->next;
		}
		iter = iter->next;
	}
	fileKitapOduncYaz(arr,kitapodunc);
	fileKitapYaz(head);
}
void guncelleKitapOrnekforOgrenciUpdate(OGRENCI* o,char* yeni,KITAP* head)
{
	KITAP* iter= head;
	KITAP_ORNEK* iterornek;
	while(iter)
	{
		iterornek = iter->head;
		while(iterornek)
		{
			if(strcmp(o->ogrID,iterornek->Durum)==0)
				strcpy(iterornek->Durum,yeni);
			iterornek= iterornek->next;
		}
		iter = iter->next;
	}
	fileKitapYaz(head);
}
void guncelleKitapOrnekforKitapUpdate(KITAP* iter,char* newisbn,KITAP_ODUNC** arrKO,int ko)
{
	KITAP_ORNEK* iterornek;
	char tmpstr[50],tmpno[3],tmpispn[15];
	iterornek = iter->head;
	while(iterornek)
	{
		strcpy(tmpstr,iterornek->EtiketNo);
		strcpy(tmpispn,strtok(tmpstr,"_"));
		strcpy(tmpno,strtok(NULL,","));
		strcpy(tmpispn,newisbn);
		strcat(strcat(tmpispn,"_"),tmpno);
		guncelleKitapOduncforKitapUpdate(iterornek,arrKO,ko,tmpispn);
		strcpy(iterornek->EtiketNo,tmpispn);
		iterornek= iterornek->next;
	}
	fileKitapOduncYaz(arrKO,ko);
}
void guncelleKitapOduncforKitapUpdate(KITAP_ORNEK* k,KITAP_ODUNC** arrKO,int ko,char* newetiket)
{
	int i;
	for(i=0;i<ko;i++)
	{
		if(strcmp(arrKO[i]->EtiketNo,k->EtiketNo)==0)
			strcpy(arrKO[i]->EtiketNo,newetiket);
	}
	fileKitapOduncYaz(arrKO,ko);
}
void guncelleKitapYazarforUpdate(KITAP* k,char* isbn,KITAP_YAZAR** arr,int kitapyazar)
{
	int i;
	for(i=0;i<kitapyazar;i++)
	{
		if(strcmp(arr[i]->ISBN,k->ISBN)==0)
			strcpy(arr[i]->ISBN,isbn);
	}
	fileKitapYazarYaz(arr,kitapyazar);
}
void guncelleKitapYazarforYazar(KITAP_YAZAR** arr,int kitapyazar,YAZAR* head)
{
	int i,j,flag;
	YAZAR* iter = head;
	for(i=0;i<kitapyazar;i++)
	{
		flag = 0;
		iter= head;
		while(iter)
		{
			if(iter->yazarID == arr[i]->YazarID)
				flag = 1;
			iter = iter->next;
		}
		if(flag == 0)
		{
			for(j=0;j<kitapyazar;j++)
			{
				if(arr[j]->YazarID == arr[i]->YazarID)
					arr[j]->YazarID = -1;
			}
		}
	}
	fileKitapYazarYaz(arr,kitapyazar);
}
void guncelleKitapYazarforKitap(KITAP_YAZAR** arr,int kitapyazar,KITAP* head)
{
	int i,j,flag;
	KITAP* iter = head;
	for(i=0;i<kitapyazar;i++)
	{
		flag = 0;
		iter= head;
		while(iter)
		{
			if(strcmp(iter->ISBN,arr[i]->ISBN)==0)
				flag = 1;
			iter = iter->next;
		}
		if(flag == 0)
		{
			for(j=0;j<kitapyazar;j++)
			{
				if(strcmp(arr[j]->ISBN,arr[i]->ISBN)==0)
					strcpy(arr[j]->ISBN,"KITAP SILINDI");
			}
		}
	}
	fileKitapYazarYaz(arr,kitapyazar);
}
void guncelleKitapOduncforOgrenciUpdate(OGRENCI* o,char* yeni,KITAP_ODUNC** arr,int kitapodunc)
{
	int i;
	for(i=0;i<kitapodunc;i++)
	{
		if(strcmp(arr[i]->ogrID,o->ogrID)==0)
			strcpy(arr[i]->ogrID,yeni);
	}
	fileKitapOduncYaz(arr,kitapodunc);
}



YAZAR* createYazar(int id,char* ad,char* soyad)
{
	YAZAR* tmp = (YAZAR*)malloc(sizeof(YAZAR));
	if(tmp==NULL)
		exit(0);
	tmp->yazarID = id;
	strcpy(tmp->yazarAd,ad);
	strcpy(tmp->yazarSoyad,soyad);
	tmp->next = NULL;
	return tmp;	
}
YAZAR* addYazarfromFile(YAZAR* head,int id,char* ad,char* soyad)
{
	YAZAR* tmp= createYazar(id,ad,soyad);
	YAZAR* iter = head;
	if(head==NULL)
		head = tmp;
	else
	{
		while(iter->next)
			iter=iter->next;
		iter->next = tmp;
	}
	return head;
}
YAZAR* addYazar(YAZAR* head,char* ad,char* soyad)
{
	int id = 0;
	YAZAR* iter = head;
	YAZAR* tmp;
	while(iter->next)
		iter= iter->next;
	if(head == NULL)
	{
		head = createYazar(1,ad,soyad);
		return head;
	}
	id = iter->yazarID + 1;
	tmp = createYazar(id,ad,soyad);
	iter->next = tmp;		
	fileYazarYaz(head);
	return head;
}
YAZAR* bulYazar(YAZAR* head,char* ad,char* soyad)
{
	YAZAR* iter = head;
	YAZAR* prev = head;
	int tmpid;
	int count = 0;	
	while(iter)
	{
		if(strcmp(iter->yazarAd,ad)==0 && strcmp(iter->yazarSoyad,soyad)==0)
			count++;
		iter=iter->next;
	}
	if(count == 0)
		return NULL;	
	else 
	{
		iter = head;
		if(count == 1)
		{
			while(iter && (strcmp(iter->yazarAd,ad)!=0 || strcmp(iter->yazarSoyad,soyad)!=0))
			{
				prev = iter;
				iter = iter->next;
			}	
		}
		else
		{
			printf("Birden fazla %s %s bulundu. ID girisi yapmaniz gerekmekte: ",ad,soyad);	
			scanf("%d",&tmpid);
			while(iter && (tmpid!=iter->yazarID || strcmp(iter->yazarAd,ad)!=0 || strcmp(iter->yazarSoyad,soyad)!=0))
			{
				prev = iter;
				iter = iter->next;
			}
			if(iter==NULL)
				return NULL;
		}
	}
	return prev;		
}
YAZAR* deleteYazar(YAZAR* head,char* ad,char* soyad)
{
	YAZAR* prev = bulYazar(head,ad,soyad);
	YAZAR* iter;
	if(prev==NULL)
	{
		printf("                         Bulunamadi!                         \n");
	}
	else
	{
		if(prev== head)
		{
			if(strcmp(prev->yazarAd,ad)==0 && strcmp(prev->yazarSoyad,soyad)==0)
				iter = prev;
			else
				iter = prev->next;
		}
		else
			iter = prev->next;
		if(head==iter)
		{
			YAZAR* tmp = head;
			head = head->next;
			free(tmp);
		}
		else if(iter->next==NULL)
		{
			YAZAR* tmp = iter;
			prev ->next =NULL;
			free(tmp);
		}
		else
		{
			YAZAR* tmp = iter;	
			prev->next = iter->next;
			free(tmp);
		}
		printf("		%s %s Bulundu ve Silindi\n",ad,soyad);			
	}
	fileYazarYaz(head);
	return head;	
}	
YAZAR* updateYazar(YAZAR* head,char* ad,char* soyad)
{
	char tmpad[30],tmpsoyad[30];
	YAZAR* prev = bulYazar(head,ad,soyad);
	YAZAR* iter;
	if(prev == NULL)
	{
		printf("                         Bulunamadi!                         \n");
	}
	else
	{
		if(prev== head)
		{
			if(strcmp(prev->yazarAd,ad)==0 && strcmp(prev->yazarSoyad,soyad)==0)
				iter = prev;
			else
				iter = prev->next;
		}
		else
			iter = prev->next;
		printf("   \"Yazaradi Yazarsoyadi\" formatinda yeni bilgileri giriniz!\n			");
		scanf("%s %s",tmpad,tmpsoyad);
		strcpy(iter->yazarAd,tmpad);
		strcpy(iter->yazarSoyad,tmpsoyad);
		printf("		     Bilgiler Degistirildi\n			");
	}
	fileYazarYaz(head);	
	return head;
}



OGRENCI* createOgrenci(OGRENCI* head,char* id,char* ad,char* soyad,int puan)
{
	OGRENCI* tmp = (OGRENCI*)malloc(sizeof(OGRENCI));
	if(tmp==NULL)
		exit(0);
	tmp->puan = puan;
	strcpy(tmp->ad,ad);
	strcpy(tmp->soyad,soyad);
	strcpy(tmp->ogrID,id);
	tmp->next = NULL;
	tmp->prev = NULL;
	return tmp;		
}
OGRENCI* addOgrencifromFile(OGRENCI* head,char* id,char* ad,char* soyad,int puan)
{
	OGRENCI* tmp = createOgrenci(head,id,ad,soyad,puan);
	OGRENCI* iter = head;
	if(head==NULL)
		head = tmp;
	else
	{
		while(iter->next)
			iter=iter->next;
		iter->next = tmp;
		tmp->prev = iter;
	}
	return head;
}
OGRENCI* addOgrenci(OGRENCI* head,char* ad,char* soyad,KITAP_ODUNC** arr,int kitapodunc,KITAP* khead)
{
	char tmpid[10];
	OGRENCI* iter = head;
	OGRENCI* tmp;
	int count,puan=100;
	do
	{
		count = 0;
		printf("	   Lutfen \"OgrenciID\" formatinda giris yapiniz.\n			    ");
		scanf("%s",tmpid);
		while(iter)
		{
			if(strcmp(iter->ogrID,tmpid)==0)
				count++;
			iter = iter->next;
		}
		if(count != 0)
			printf("		  OgrenciID daha once kullanilmis.\n\n");
		else if(strlen(tmpid)!= 8 )
			printf("		  8 Basamakli ID giriniz!\n");	
	}while(count!= 0 || strlen(tmpid)!= 8);
	iter = head;
	while(iter->next)
		iter= iter->next;
	tmp = createOgrenci(head,tmpid,ad,soyad,puan);
	if(head==NULL)
		head=tmp;
	else
	{
		iter->next = tmp;
		tmp->prev = iter;		
	}
	fileOgrenciYaz(head);
	return head;
}
OGRENCI* bulOgrenci(OGRENCI* head,char* ad,char* soyad)
{
	OGRENCI* iter = head;
	char tmpid[10];
	int count = 0;	
	while(iter)
	{
		if(strcmp(iter->ad,ad)==0 && strcmp(iter->soyad,soyad)==0)
			count++;
		iter=iter->next;
	}
	if(count == 0)
		return NULL;	
	else 
	{
		iter = head;
		if(count == 1)
		{
			while(iter && (strcmp(iter->ad,ad)!=0 || strcmp(iter->soyad,soyad)!=0))
				iter = iter->next;
		}
		else
		{
			printf("Birden fazla %s %s bulundu. ID girisi yapmaniz gerekmekte: ",ad,soyad);	
			scanf("%s",tmpid);
			while(iter && (strcmp(iter->ogrID,tmpid)!=0 || strcmp(iter->ad,ad)!=0 || strcmp(iter->soyad,soyad)!=0))
				iter = iter->next;
			if(iter==NULL)
				return NULL;
		}
	}
	return iter;	
}
OGRENCI* deleteOgrenci(OGRENCI* head,char* ad,char* soyad,KITAP_ODUNC** arr,int kitapodunc,KITAP* khead)
{
	OGRENCI* iter = bulOgrenci(head,ad,soyad);
	if(iter==NULL)
		printf("                         Bulunamadi!                         \n");
	else
	{
		if(head==iter)
		{
			OGRENCI* tmp = head;
			head = head->next;
			free(tmp);
		}
		else if(iter->next==NULL)
		{
			OGRENCI* tmp = iter;
			iter->prev->next =NULL;
			free(tmp);
		}
		else
		{
			OGRENCI* tmp = iter;
			iter->next->prev = iter->prev;
			iter->prev->next = iter->next;
			free(tmp);
		}
		printf("	     %s %s Bulundu ve Silindi\n",ad,soyad);
	}
	fileOgrenciYaz(head);
	return head;
}
OGRENCI* updateOgrenci(OGRENCI* head,char* ad,char* soyad,KITAP_ODUNC** arr,int kitapodunc,KITAP* khead)
{
	int secim,count;
	char tmpid[9],tmpad[30],tmpsoyad[30];
	OGRENCI* iter = bulOgrenci(head,ad,soyad);
	OGRENCI* tmp;
	if(iter == NULL)
		printf("                         Bulunamadi!                         \n");
	else
	{		
		printf(" \"Ogrenciadi Ogrencisoyadi\" formatinda yeni bilgileri giriniz!\n			");
		scanf("%s %s",tmpad,tmpsoyad);
		printf("	ID degistirmek istiyor musunuz ? '1' Evet, '0' Hayir\n			   ");
		scanf("%d",&secim);
		if(secim == 1)
		{
			tmp = iter;
			do
			{
				iter = head;
				count = 0;
				printf("	   Lutfen \"OgrenciID\" formatinda giris yapiniz.\n			    ");
				scanf("%s",tmpid);
				while(iter)
				{
					if(strcmp(iter->ogrID,tmpid)==0)
						count++;
					iter = iter->next;
				}
				iter = tmp;
				if(count != 0)
					printf("		  OgrenciID daha once kullanilmis.\n\n");
				else if(strlen(tmpid)!= 8 )
					printf("		  8 Basamakli ID giriniz!\n");	
			}while(count!= 0 || strlen(tmpid)!= 8);		
		}
		else
		{
			strcpy(tmpid,iter->ogrID);
		}
		guncelleKitapOrnekforOgrenciUpdate(iter,tmpid,khead);
		guncelleKitapOduncforOgrenciUpdate(iter,tmpid,arr,kitapodunc);		
		strcpy(iter->ad,tmpad);
		strcpy(iter->soyad,tmpsoyad);
		strcpy(iter->ogrID,tmpid);
		printf("		     Bilgiler Degistirildi\n			");
	}
	fileOgrenciYaz(head);
	return head;
}
OGRENCI* kosulCezali(OGRENCI* iter,KITAP_ODUNC** arr,int kitapodunc)
{
	if(iter->puan<0)
		return iter;
	return NULL;
}
OGRENCI* kosulYok(OGRENCI* iter,KITAP_ODUNC** arr,int kitapodunc)
{
	return iter;
}
OGRENCI* kosulKitapTeslimEtmeyen(OGRENCI* iter,KITAP_ODUNC** arr,int kitapodunc)
{
	int i,flag=0,j;
	for(i=0;i<kitapodunc;i++)
	{
		if(arr[i]->islemTipi== 0 && strcmp(arr[i]->ogrID,iter->ogrID)==0)
			flag=1;
		if(flag==1)
		{
			for(j=i+1;j<kitapodunc;j++)
			{
				if(arr[j]->islemTipi == 1 && strcmp(arr[j]->ogrID,iter->ogrID)==0)
					flag = 0;
			}
		}
	}
	if(flag == 1)
		return iter;
	return NULL;	
}



KITAP_ORNEK* bulKitapOrnekforAdd(KITAP* head,char* ad)
{
	KITAP* iter = head;
	KITAP_ORNEK* iterornek;
	while(iter && strcmp(iter->kitapAdi,ad)!=0)
		iter = iter->next;
	if(!iter)
		return NULL;
	iterornek = iter->head;
	while(iterornek && strcmp(iterornek->Durum,"RAFTA")!=0)
		iterornek = iterornek->next;
	if(!iterornek)
		return NULL;
	return iterornek;
}
KITAP_ORNEK* bulKitapOrnekforDelete(KITAP* head,char* ad,OGRENCI* o)
{
	KITAP* iter = head;
	KITAP_ORNEK* iterornek;
	while(iter && strcmp(iter->kitapAdi,ad)!=0)
		iter = iter->next;
	if(!iter)
		return NULL;
	iterornek = iter->head;
	while(iterornek && strcmp(iterornek->Durum,o->ogrID)!=0)
		iterornek = iterornek->next;
	if(!iterornek)
		return NULL;
	return iterornek;	
}
KITAP_ORNEK* deleteOrnek(KITAP_ORNEK* head,KITAP_ORNEK* iter)
{
	KITAP_ORNEK* iterornek = head;
	KITAP_ORNEK* prevornek = head;
	while(iterornek!=iter)
	{
		prevornek = iterornek;
		iterornek = iterornek->next;
	}
	if(head==iterornek)
	{
		KITAP_ORNEK* tmp = head;
		head = head->next;
		free(tmp);
	}
	else if(iterornek->next==NULL)
	{
		KITAP_ORNEK* tmp = iterornek;
		prevornek ->next =NULL;
		free(tmp);
	}
	else
	{
		KITAP_ORNEK* tmp = iterornek;
		prevornek->next = iterornek->next;
		free(tmp);
	}
	return head;
}
KITAP_ORNEK* addKitapOrnek(KITAP_ORNEK* head,char* isbn,int adet)
{
	KITAP_ORNEK* iter = head;	
	int i;
	char tmpstr[50],istr[3];
	for(i=1;i<=adet;i++)
	{
		KITAP_ORNEK* tmp = (KITAP_ORNEK*)malloc(sizeof(KITAP_ORNEK));
		strcpy(tmp->Durum,"RAFTA");
		tmp->next = NULL;
		itoa(i,istr,10);
		strcpy(tmpstr,isbn);
		strcat(tmpstr,"_");
		strcat(tmpstr,istr);
		strcpy(tmp->EtiketNo,tmpstr);
		if(head == NULL)
			head = tmp;
		else
		{
			iter = head;
			while(iter->next)
				iter = iter->next;
			iter->next = tmp;
		}
	}
	return head;
}
KITAP_ORNEK* guncelleKitapOrnekfordelete(KITAP_ORNEK* head,char* isbn,int adet,int* miktar)
{
	int i;
	KITAP_ORNEK* iter = head;
	int islem= adet;
	char tmpstr[50],istr[3];
	while(islem != adet-*miktar)
	{
		iter=head;
		while(iter->next)
			iter = iter->next;
		if(strcmp(iter->Durum,"RAFTA")==0)
		{
			head = deleteOrnek(head,iter);
			islem--;
		}
		else
		{
			*miktar = adet-islem;
			printf("%d tane sildiniz\n",*miktar);
			printf("Daha Fazla Silemezsiniz!");	
		}	
	}
	return head;
}
KITAP_ORNEK* guncelleKitapOrnekforAdd(KITAP_ORNEK* head,char* isbn,int adet,int miktar)
{
	int i;
	KITAP_ORNEK* iter = head;
	char tmpstr[50],istr[3];
	for(i = adet+1;i<=adet+miktar;i++)
	{
		KITAP_ORNEK* tmp = (KITAP_ORNEK*)malloc(sizeof(KITAP_ORNEK));
		strcpy(tmp->Durum,"RAFTA");
		tmp->next = NULL;
		itoa(i,istr,10);
		strcpy(tmpstr,isbn);
		strcat(tmpstr,"_");
		strcat(tmpstr,istr);
		strcpy(tmp->EtiketNo,tmpstr);
		while(iter->next)
			iter = iter->next;
		iter->next = tmp;	
	}
	return head;
}



KITAP* createKitap(KITAP* head,char* ad,char* isbn,int adet)
{
	KITAP* tmp=(KITAP*)malloc(sizeof(KITAP));
	if(tmp==NULL)
		exit(0);
	strcpy(tmp->kitapAdi,ad);
	strcpy(tmp->ISBN,isbn);
	tmp->adet = adet;
	tmp->next = NULL;
	tmp->head = NULL;
	tmp->head = addKitapOrnek(tmp->head,isbn,adet);
	return tmp;	
}
KITAP* addKitapfromFile(KITAP* head,char* ad,char* isbn,int adet)
{
	KITAP* tmp=createKitap(head,ad,isbn,adet);
	if(head==NULL)
		head = tmp;
	else if(strcmp(head->kitapAdi,tmp->kitapAdi)>0)
	{
		tmp->next = head;
		head = tmp;
	}
	else
	{
		KITAP* iter = head;
		while(iter->next && strcmp(iter->next->kitapAdi,tmp->kitapAdi)<0)
			iter=iter->next;
		if(iter->next)
		{
			while(strcmp(iter->kitapAdi,tmp->kitapAdi)==0 && strcmp(iter->next->ISBN,tmp->ISBN)<0)
				iter=iter->next;	
		}
		tmp->next = iter->next;
		iter->next = tmp;
	}
	return head;
}
KITAP* addKitap(KITAP* head,char* ad,KITAP_YAZAR** arr,int kitapyazar,KITAP_ODUNC** arrKO,int ko)
{
	int tmpadet;
	char tmpisbn[15];
	KITAP* iter = head;
	KITAP* tmp;
	printf("	\"Kitapisbn Kitapadet\" formatinda giris yapiniz!\n		      ");
	scanf("%s %d",tmpisbn,&tmpadet);	
	while(strlen(tmpisbn)!=13)
	{
		printf("	ISBN 13 haneli olmalidir. Lutfen Tekrar Giriniz\n			 ");
		scanf("%s",tmpisbn);
	}
	while(iter->next && strcmp(iter->ISBN,tmpisbn)!=0)
		iter= iter->next;
	if(iter->next || strcmp(iter->ISBN,tmpisbn)==0)
	{
		if(strcmp(iter->kitapAdi,ad)==0)
		{
			iter->head = guncelleKitapOrnekforAdd(iter->head,iter->ISBN,iter->adet,tmpadet);
			iter->adet += tmpadet;		
		}
		else
		{
			printf("Bu ISBN kullanilmakta!\n");
			return head;
		}
	}
	else
	{
		tmp=createKitap(head,ad,tmpisbn,tmpadet);
		if(head==NULL)
			head = tmp;
		else if(strcmp(head->kitapAdi,tmp->kitapAdi)>0)
		{
			tmp->next = head;
			head = tmp;
		}
		else
		{
			iter = head;
			while(iter->next && strcmp(iter->next->kitapAdi,tmp->kitapAdi)<0)
				iter=iter->next;
			if(iter->next)
			{	
				while(strcmp(iter->next->kitapAdi,tmp->kitapAdi)==0 && strcmp(iter->next->ISBN,tmp->ISBN)<0)
					iter=iter->next;	
			}
			tmp->next = iter->next;
			iter->next = tmp;
		}
	}
	fileKitapYaz(head);
	return head;
}
KITAP* bulKitap(KITAP* head,char* ad)
{
	KITAP* iter = head;
	KITAP* prev = head;
	int count=0;
	char tmpisbn[15];
	while(iter)
	{
		if(strcmp(iter->kitapAdi,ad)==0)
			count++;
		iter = iter->next;
	}
	if(count == 0)
		return NULL;
	else if(count == 1)
	{
		iter = head;
		while(iter && strcmp(iter->kitapAdi,ad)!=0)
		{
			prev = iter;
			iter = iter->next;
		}
	}
	else
	{
		printf("Birden Fazla Bulundu, ISBN Girisi Gereklidir: ");
		scanf("%s",tmpisbn);
		while(strlen(tmpisbn)!=13)
		{
			printf("13 Haneli Girmelisiniz\n");
			scanf("%s",tmpisbn);
		}
		iter = head;
		while(iter && (strcmp(iter->kitapAdi,ad)!= 0 || strcmp(iter->ISBN,tmpisbn)!= 0))
		{
			prev = iter;
			iter= iter->next;
		}
		if(!iter)
			return NULL;
	}
	return prev;
}
KITAP* deleteKitap(KITAP* head,char* ad,KITAP_YAZAR** arr,int kitapyazar,KITAP_ODUNC** arrKO,int ko)
{
	int secim,sil;
	KITAP_ORNEK* iterornek;
	KITAP* iter;
	KITAP* prev = bulKitap(head,ad);
	if(prev == NULL)
		printf("                         Bulunamadi!                         \n");
	else
	{
		if(prev == head)
		{
			if(strcmp(prev->kitapAdi,ad)==0)
				iter = prev;
			else
				iter = prev->next;
		}
		else
			iter = prev->next;
		printf("Kopya sayisi azaltmak icin '0'\n");
		printf("Kitabin varligini silmek icin '1'\n");
		scanf("%d",&secim);
		if(secim==1)
		{
			int silinebilir=1;
			iterornek = iter->head;
			while(iterornek)
			{
				if(strcmp(iterornek->Durum,"RAFTA")!=0)
				{
					silinebilir = 0;
					printf("%s bu kitaba sahip\n",iterornek->Durum);
				}
				iterornek = iterornek->next;
			}
			if(silinebilir == 0)
			{
				printf("Kitaplar teslim edilmeden silinemez.");
				return head;
			}
			else
			{
				if(head==iter)
				{
					KITAP* tmp = head;
					head = head->next;
					free(tmp);
				}
				else if(iter->next==NULL)
				{
					KITAP* tmp = iter;
					prev ->next =NULL;
					free(tmp);
				}	
				else
				{		
					KITAP* tmp = iter;
					prev->next = iter->next;
					free(tmp);
				}		
			}	
		}
		if(secim==0)
		{
			do
			{
				printf("Silmek istediginiz miktari giriniz: ");
				scanf("%d",&sil);
				if( sil <= iter->adet )
				{
					KITAP_ORNEK* iterornek = iter->head;
					iter->head = guncelleKitapOrnekfordelete(iter->head,iter->ISBN,iter->adet,&sil);
				}
				else
					printf("O kadar kitap mevcut degil!");
			}while(sil>iter->adet);
			iter->adet -= sil;	
		}			
	}
	fileKitapYaz(head);
	return head;		
}
KITAP* updateKitap(KITAP* head,char* ad,KITAP_YAZAR** arr,int kitapyazar,KITAP_ODUNC** arrKO,int ko)
{
	int tmpadet,secim;
	char tmpisbn[14],tmpad[30];
	KITAP* iter;
	KITAP* iter2;
	KITAP* prev = bulKitap(head,ad);
	if(prev == NULL)
		printf("                         Bulunamadi!                         \n");
	else
	{	
		printf("	 \"Kitapadi\" formatinda yeni bilgiyi giriniz!\n			");
		fflush(stdin);
		scanf("%[^\n]",tmpad);
		printf("	ISBN degistirmek ister misiniz? Evet '1', Hayir '0'\n			    ");
		scanf("%d",&secim);
		while(secim>1 || secim<0)
			secim = GecersizGiris();
		if(secim==1)
		{
			printf("	   \"Kitapisbn\" formatinda yeni bilgiyi yapiniz!\n		      ");
			scanf("%s",tmpisbn);	
			while(strlen(tmpisbn)!=13)
			{
				printf("	ISBN 13 haneli olmalidir. Lutfen Tekrar Giriniz\n			 ");
				scanf("%s",tmpisbn);
			}
			iter= head;
			while(iter->next && strcmp(iter->ISBN,tmpisbn)!=0)
				iter= iter->next;
			if(iter->next || strcmp(iter->ISBN,tmpisbn)==0)
			{
				if(strcmp(iter->kitapAdi,tmpad)==0)
				{
					printf("Lutfen Kitap Ekleme Secenegini Kullaniniz, Bu Kitap Zaten Mevcut\n");	
				}
				else
				{
					printf("Bu ISBN kullanilmakta!\n");
					printf("Guncelleme Basarisiz\n");
				}
			}
			else
			{
				if(prev== head)
				{	
					if(strcmp(prev->kitapAdi,ad)==0)
						iter = prev;
					else
						iter = prev->next;
				}
				else
					iter = prev->next;
				guncelleKitapYazarforUpdate(iter,tmpisbn,arr,kitapyazar);
				guncelleKitapOrnekforKitapUpdate(iter,tmpisbn,arrKO,ko);					
				strcpy(iter->kitapAdi,tmpad);
				strcpy(iter->ISBN,tmpisbn);
				KITAP_ORNEK* iterornek = iter->head;
				while(iterornek)
				{
					char tmp[30],sayi[3];
					strcpy(tmp,iterornek->EtiketNo);
					strtok(tmp,"_");
					strcpy(sayi,strtok(NULL,"\n"));
					strcat(tmp,"_");
					strcat(tmp,sayi);
					strcpy(iterornek->EtiketNo,tmp);
					iterornek = iterornek->next;
				}
			}
			iter = head;
			while(iter)
			{
				iter2 = head;
				while(iter2)
				{
					if(strcmp(iter->kitapAdi,iter2->kitapAdi)<0)
					{
						strcpy(tmpisbn,iter->ISBN);strcpy(tmpad,iter->kitapAdi); tmpadet = iter->adet ; KITAP_ORNEK* tmp = iter->head;
						strcpy(iter->ISBN,iter2->ISBN);strcpy(iter->kitapAdi,iter2->kitapAdi); iter->adet =  iter2->adet;iter->head = iter2->head;
						strcpy(iter2->ISBN,tmpisbn);strcpy(iter2->kitapAdi,tmpad); iter2->adet = tmpadet ; iter2->head = tmp;
					}
					if(strcmp(iter->kitapAdi,iter2->kitapAdi)==0 && strcmp(iter->ISBN,iter2->ISBN)<0)
					{
						strcpy(tmpisbn,iter->ISBN);strcpy(tmpad,iter->kitapAdi); tmpadet = iter->adet ; KITAP_ORNEK* tmp = iter->head;
						strcpy(iter->ISBN,iter2->ISBN);strcpy(iter->kitapAdi,iter2->kitapAdi); iter->adet =  iter2->adet;iter->head = iter2->head;
						strcpy(iter2->ISBN,tmpisbn);strcpy(iter2->kitapAdi,tmpad); iter2->adet = tmpadet ; iter2->head = tmp;			
					}			
					iter2=iter2->next;
				}
				iter=iter->next;
			}
		}
		else
		{
			if(prev == head)
			{
				if(strcmp(prev->kitapAdi,ad)==0)
					iter = prev;
				else
					iter = prev->next;
			}
			strcpy(iter->kitapAdi,tmpad);
			KITAP_ORNEK* iterornek = iter->head;
			while(iterornek)
			{
				char tmp[30],sayi[3];
				strcpy(tmp,iterornek->EtiketNo);
				strtok(tmp,"_");
				strcpy(sayi,strtok(NULL,"\n"));
				strcat(tmp,"_");
				strcat(tmp,sayi);
				strcpy(iterornek->EtiketNo,tmp);
				iterornek = iterornek->next;
			}
			iter = head;
			while(iter)
			{
				iter2 = head;
				while(iter2)
				{
					if(strcmp(iter->kitapAdi,iter2->kitapAdi)<0)
					{
						strcpy(tmpisbn,iter->ISBN);strcpy(tmpad,iter->kitapAdi); tmpadet = iter->adet ; KITAP_ORNEK* tmp = iter->head;
						strcpy(iter->ISBN,iter2->ISBN);strcpy(iter->kitapAdi,iter2->kitapAdi); iter->adet =  iter2->adet;iter->head = iter2->head;
						strcpy(iter2->ISBN,tmpisbn);strcpy(iter2->kitapAdi,tmpad); iter2->adet = tmpadet ; iter2->head = tmp;
					}
					if(strcmp(iter->kitapAdi,iter2->kitapAdi)==0 && strcmp(iter->ISBN,iter2->ISBN)<0)
					{
						strcpy(tmpisbn,iter->ISBN);strcpy(tmpad,iter->kitapAdi); tmpadet = iter->adet ; KITAP_ORNEK* tmp = iter->head;
						strcpy(iter->ISBN,iter2->ISBN);strcpy(iter->kitapAdi,iter2->kitapAdi); iter->adet =  iter2->adet;iter->head = iter2->head;
						strcpy(iter2->ISBN,tmpisbn);strcpy(iter2->kitapAdi,tmpad); iter2->adet = tmpadet ; iter2->head = tmp;			
					}			
					iter2=iter2->next;
				}
				iter=iter->next;
			}			
		}
	}
	fileKitapYazarYaz(arr,kitapyazar);
	fileKitapOduncYaz(arrKO,ko);
	fileKitapYaz(head);
	return head;	
}



KITAP_YAZAR** addKitapYazar(KITAP_YAZAR** arr,int* kitapyazar,YAZAR* y,char* yAd,char* ySoyad,KITAP* k,char* kAd)
{
	int i;
	YAZAR* yprev= bulYazar(y,yAd,ySoyad);
	YAZAR* yiter;
	KITAP* kprev= bulKitap(k,kAd);
	KITAP* kiter;
	if(!kprev)
		printf("Kitap Bulunamadi!\n");
	else if(!yprev)
		printf("Yazar Bulunamadi!\n");
	else
	{
		if(yprev == y)
		{
			if(strcmp(yprev->yazarAd,yAd)==0 && strcmp(yprev->yazarSoyad,ySoyad)==0)
				yiter = yprev;
			else
				yiter = yprev->next;
		}
		else
			yiter = yprev->next;
		if(kprev == k)
		{
			if(strcmp(kprev->kitapAdi,kAd)==0)
				kiter = kprev;
			else
				kiter = kprev->next;
		}
		else
			kiter = kprev->next;
		for(i=0;i<*kitapyazar;i++)
		{
			if(strcmp(arr[i]->ISBN,kiter->ISBN)==0 && arr[i]->YazarID == yiter->yazarID)
			{
				printf("Daha once bu eslestirme yapilmis!");
				return arr;
			}
		}	
		arr = (KITAP_YAZAR**)realloc(arr,sizeof(KITAP_YAZAR*)*(*kitapyazar+1));
		arr[*kitapyazar] = (KITAP_YAZAR*)malloc(sizeof(KITAP_YAZAR));
		strcpy(arr[*kitapyazar]->ISBN,kiter->ISBN);
		arr[*kitapyazar]->YazarID = yiter->yazarID;	
		(*kitapyazar)++;	
	}
	fileKitapYazarYaz(arr,*kitapyazar);
	return arr;
}
KITAP_YAZAR** guncelleKitapYazar(KITAP_YAZAR** arr,int* kitapyazar,YAZAR* y,char* yAd,char* ySoyad,KITAP* k,char* kAd)
{
	int i;
	YAZAR* yprev= bulYazar(y,yAd,ySoyad);
	YAZAR* yiter;
	KITAP* kprev= bulKitap(k,kAd);
	KITAP* kiter;
	char tmpstr[30];
	int tmpint,flag;
	if(!kprev)
		printf("Kitap Bulunamadi!\n");
	else if(!yprev)
		printf("Yazar Bulunamadi!\n");
	else
	{
		if(yprev == y)
		{
			if(strcmp(yprev->yazarAd,yAd)==0 && strcmp(yprev->yazarSoyad,ySoyad)==0)
				yiter = yprev;
			else
				yiter = yprev->next;
		}
		else
			yiter = yprev->next;
		if(kprev == k)
		{
			if(strcmp(kprev->kitapAdi,kAd)==0)
				kiter = kprev;
			else
				kiter = kprev->next;
		}
		else
			kiter = kprev->next;
		for(i=0;i<*kitapyazar;i++)
		{
			if(strcmp(arr[i]->ISBN,kiter->ISBN)==0 && arr[i]->YazarID == yiter->yazarID)
			{
				strcpy(tmpstr,arr[i]->ISBN);tmpint = arr[i]->YazarID;
				strcpy(arr[i]->ISBN,arr[*kitapyazar-1]->ISBN);arr[i]->YazarID = arr[*kitapyazar-1]->YazarID;
				strcpy(arr[*kitapyazar-1]->ISBN,tmpstr);arr[*kitapyazar-1]->YazarID = tmpint;
				free(arr[*kitapyazar-1]);
				(*kitapyazar)--;
				flag = 1;
			}
		}	
		if(flag == 0)
			printf("Aralarinda guncellenecek bir bag bulunamadi\n");	
	}
	fileKitapYazarYaz(arr,*kitapyazar);
	return arr;
}



KITAP_ODUNC** addKitapOdunc(KITAP_ODUNC** arr,int* kitapodunc,KITAP* k,char* kad,OGRENCI* o,char* oad,char* osoyad)
{
	TARIH t = tarihAl(arr,*kitapodunc);
	KITAP_ORNEK* kopya;
	OGRENCI* oiter = bulOgrenci(o,oad,osoyad);
	int i,j,gecensure,exit=1;
	int islemtipi;
	int returnable = 0;
	if(oiter == NULL)
		printf("Ogrenci bulunamadi!\n");
	else
	{
		printf("     Lutfen Islem Tipini Giriniz: Kitap Al '0' , Kitap Ver '1' \n			    ");
		scanf("%d",&islemtipi);
		while(islemtipi<0 || islemtipi>1)
			islemtipi = GecersizGiris();
		if(islemtipi == 0)
		{
			kopya = bulKitapOrnekforAdd(k,kad);
			if(kopya == NULL)
				printf("Bu kitabin bosta bulunan bir kopyasi yok!\n");
			else
			{
				if(o->puan<0)
					printf("Ogrenci Cezalidir Kitap Alamaz\n");
				else
				{
					arr = (KITAP_ODUNC**)realloc(arr,sizeof(KITAP_ODUNC*)*(*kitapodunc+1));
					arr[*kitapodunc] = (KITAP_ODUNC*)malloc(sizeof(KITAP_ODUNC));
					strcpy(arr[*kitapodunc]->EtiketNo,kopya->EtiketNo);
					strcpy(arr[*kitapodunc]->ogrID,oiter->ogrID);
					arr[*kitapodunc]->islemTipi = islemtipi;
					arr[*kitapodunc]->islemTarihi = t;	
					(*kitapodunc)++;
				}
			}
		}
		else
		{
			kopya = bulKitapOrnekforDelete(k,kad,oiter);
			if(kopya==NULL)
			{
				printf("Bu kitabin ogrencide bir kopyasi yok!\n");
				return arr;
			}
			i= *kitapodunc-1;
			while(i>0 && exit)
			{
				if(strcmp(arr[i]->ogrID,oiter->ogrID)==0 && strcmp(arr[i]->EtiketNo,kopya->EtiketNo)==0)
				{
					exit = 0;
					if(arr[i]->islemTipi==0)
						returnable = 1;
					else
						returnable = 0;	
				}
				i--;
			}
			if(returnable == 1)
			{
				gecensure = cmpTarih(t,arr[i+1]->islemTarihi);
				if(gecensure > 15)
					oiter->puan -= 10;
				arr = (KITAP_ODUNC**)realloc(arr,sizeof(KITAP_ODUNC*)*(*kitapodunc+1));
				arr[*kitapodunc] = (KITAP_ODUNC*)malloc(sizeof(KITAP_ODUNC));
				strcpy(arr[*kitapodunc]->EtiketNo,kopya->EtiketNo);
				strcpy(arr[*kitapodunc]->ogrID,oiter->ogrID);
				arr[*kitapodunc]->islemTipi = islemtipi;
				arr[*kitapodunc]->islemTarihi = t;	
				(*kitapodunc)++;				
			}
			else
			{
				printf("Kitap geri verilemedi.\n");
				printf("Coktan vermis ya da kitabi hic almamis olabilirsiniz.\n");
			}
		}
		fileOgrenciYaz(o);
		guncelleKitapOrnek(k,arr,*kitapodunc);
		fileKitapOduncYaz(arr,*kitapodunc);
		return arr;
	}
}



TARIH tarihAl(KITAP_ODUNC** arr,int kitapodunc)
{
	TARIH tmp;
	int i=0,gun,ay,yil;
	int flag,innerflag;
	do{
		do{
			innerflag = 1;
			printf(" 	\"GG.AA.YYYY\" seklinde tarih girisi yapiniz:\n			");
			scanf("%d.%d.%d",&gun,&ay,&yil);
			if(gun>31 || gun<0 || ay>12 || ay<0 || yil<0)
			{
				innerflag = 0;
				printf("		-1<Gun<32 && -1<Ay<13 && -1<Yil\n");
			}
		}while(gun>31 || gun<0 || ay>12 || ay<0 || yil<0);
		tmp.gun=gun;tmp.ay=ay;tmp.yil=yil;
		flag = 1;
		for(i=0;i<kitapodunc;i++)
		{
			if(cmpTarih(arr[i]->islemTarihi,tmp)>0)
			{
				flag = 0;
			}
		}
		if(flag == 0)
		{
			printf("		  Bu Tarih Coktan Gecti\n");
		}
	}while(flag == 0);
	return tmp;
}
int cmpTarih(TARIH t1,TARIH t2)
{
	return (t1.gun-t2.gun) + (t1.ay-t2.ay)*30 + (t1.yil-t2.yil)*365;	
}

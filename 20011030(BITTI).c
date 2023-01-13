#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct Linkli
{
	int deger;
	struct Linkli *sonraki;
	int kademe;
};

struct Linkli *SiraliEkle(struct Linkli *ilk,int deger)
{
	struct Linkli *ozelkutu;
	if(ilk==NULL)
	{
		ilk=(struct Linkli *)malloc(sizeof(struct Linkli));
		ilk->sonraki=NULL;
		ilk->deger=deger;
		ilk->kademe=1;
		return ilk;
	}
	if(ilk->deger>deger)
	{
		struct Linkli *tmp=(struct Linkli *)malloc(sizeof(struct Linkli));
		tmp->deger=deger;
		tmp->sonraki=ilk;
		tmp->kademe=1;
		return tmp;
	}
	struct Linkli *gezen = ilk;
	while(gezen->sonraki!=NULL && gezen->sonraki->deger < deger)
	{
		gezen=gezen->sonraki;
	}
	struct Linkli *tmp = (struct Linkli *)malloc(sizeof(struct Linkli));	
	tmp->sonraki=gezen->sonraki;
	gezen->sonraki=tmp;
	tmp->deger=deger;
	tmp->kademe=1;
	return ilk;
}

void LinkliYazdir(struct Linkli *kutu)
{
	if(kutu==NULL)
	{
		printf("NULL\n");
	}
	else
	{
		printf("%d-->",kutu->deger);
	}	
}

void ListeYazdir(struct Linkli *liste,int elemansayisi)
{
	printf("LISTE\n");
	struct Linkli *boyut;
	boyut = liste;
	if(boyut==NULL)
	{
		printf("BOS\n");
	}
	else
	{
		int i=(log(elemansayisi)/log(2));	
		while(i!=0)
		{
			while(boyut!=NULL)	
			{
				if(boyut->kademe>=i)
				{
					LinkliYazdir(boyut);
				}
				boyut=boyut->sonraki;
			}
		boyut=liste;
		printf("NULL\n");
		i--;
		}
	}
}

void Temizlik(struct Linkli *liste)
{
	struct Linkli *ileri;
	while(liste!=NULL)
	{
		ileri=liste->sonraki;
		printf("%d TEMIZLENDI\n",liste->deger);
		free(liste);
		liste=ileri;
	}
}

void KademeleriOlustur(struct Linkli *ilk,int elemansayisi)
{
	int i;
	struct Linkli *gezen=ilk;
	if(gezen->kademe==1)
	{
		do
		{
			gezen->kademe++;
			gezen=gezen->sonraki->sonraki;
		}
		while(gezen!=NULL && gezen->sonraki!=NULL);
	}
	else if(gezen->kademe==2)
	{
		do
		{	
			if(gezen->kademe==2)
			{
				gezen->kademe++;
			}
			gezen=gezen->sonraki->sonraki->sonraki->sonraki;
		}
		while(gezen!=NULL && gezen->sonraki!=NULL && gezen->sonraki->sonraki!=NULL && gezen->sonraki->sonraki->sonraki!=NULL);
	}
	else if(gezen->kademe==3)
	{
		do
		{	
			if(gezen->kademe==3)
			{
				gezen->kademe++;
			}
			gezen=gezen->sonraki->sonraki->sonraki->sonraki->sonraki->sonraki->sonraki->sonraki;
		}
		while(gezen!=NULL && gezen->sonraki!=NULL && gezen->sonraki->sonraki!=NULL && gezen->sonraki->sonraki->sonraki!=NULL && gezen->sonraki->sonraki->sonraki->sonraki!=NULL && gezen->sonraki->sonraki->sonraki->sonraki->sonraki!=NULL);
	}
	printf("KADEMELER OLUSTURULDU\n");
}


int Arama(struct Linkli *ilk,int aranan)
{
	struct Linkli *gezen=ilk;
	int ilkinkademesi = ilk->kademe;
	if(gezen->kademe==4)
	{
		do
		{
			if(gezen->deger==aranan)
			{
				printf("ARAMA BASARILI, ELEMAN LISTEDE VAR\n");
				ilk->kademe=ilkinkademesi;
				return gezen->kademe;
			}
			gezen=gezen->sonraki->sonraki->sonraki->sonraki->sonraki->sonraki->sonraki->sonraki;	
		}
		while(gezen!=NULL && gezen->sonraki!=NULL && gezen->sonraki->sonraki!=NULL && gezen->sonraki->sonraki->sonraki!=NULL && gezen->sonraki->sonraki->sonraki->sonraki!=NULL && gezen->sonraki->sonraki->sonraki->sonraki->sonraki!=NULL);
		gezen=ilk;
		gezen->kademe=3;
	}
	if(gezen->kademe==3)
	{
		do
		{
			if(gezen->deger==aranan)
			{
				printf("ARAMA BASARILI, ELEMAN LISTEDE VAR\n");
				ilk->kademe=ilkinkademesi;
				return gezen->kademe;
			}
			gezen=gezen->sonraki->sonraki->sonraki->sonraki;	
		}
		while(gezen!=NULL && gezen->sonraki!=NULL && gezen->sonraki->sonraki!=NULL && gezen->sonraki->sonraki->sonraki!=NULL);		
		gezen=ilk;
		gezen->kademe=2;
	}
	if(gezen->kademe==2)
	{
		do
		{
		
			if(gezen->deger==aranan)
			{
				printf("ARAMA BASARILI, ELEMAN LISTEDE VAR\n");
				ilk->kademe=ilkinkademesi;
				return gezen->kademe;
			}
			gezen=gezen->sonraki->sonraki;	
		}
		while(gezen!=NULL && gezen->sonraki!=NULL);	
		gezen=ilk;
		gezen->kademe=1;
	}
	if(gezen->kademe==1)
	{
		do
		{
		
			if(gezen->deger==aranan)
			{
				printf("ARAMA BASARILI, ELEMAN LISTEDE VAR\n");
				ilk->kademe=ilkinkademesi;
				return gezen->kademe;
			}
			gezen=gezen->sonraki;
		}
		while(gezen!=NULL);
		printf("ARAMA BASARISIZ, ELEMAN LISTEDE YOK\n");
		ilk->kademe=ilkinkademesi;
		return -1;
	}
}

struct Linkli *Sil(struct Linkli *ilk,int silinen)
{
	struct Linkli *gezen=ilk;
	struct Linkli *tmp;
	if(ilk->deger==silinen)
	{
		tmp = ilk;
		ilk = ilk->sonraki;
		printf("ELEMAN SILINDI\n");
		free(tmp);
		return ilk;
	}
	while(gezen->sonraki != NULL && gezen->sonraki->deger != silinen)
	{
		gezen= gezen->sonraki;		
	}
	if(gezen->sonraki == NULL)
	{
		printf("ELEMAN LISTEDE MEVCUT DEGIL\n");
		return ilk;
	}
	tmp= gezen->sonraki;
	gezen->sonraki = gezen->sonraki->sonraki;
	free(tmp);
	printf("ELEMAN SILINDI\n");
	return ilk;
	
		
}

void Kademeleri0la(struct Linkli *ilk)
{
	struct Linkli *gezen=ilk;
	while(gezen!=NULL)
	{
		gezen->kademe=1;
		gezen=gezen->sonraki;
	}
	
	printf("KADEMELER SIFIRLANDI.\n");
}


int main()
{
	struct Linkli *yeni;
	struct Linkli *ilk = NULL;
	int deger;
	char eylem[50];
	int sonuc;
	int elemansayisi=0;
	int silinen;
	//int forRastgele[50];	
	int aranan;
	//srand(time(NULL));
	
	while(1)
	{
		printf("SAYI EKLEMEK ICIN(ekle)\n");
		printf("SAYI SILMEK ICIN(sil)\n");
		printf("KADEMELERI OLUSTURMAK ICIN(kademe)\n");
		printf("ARAMAK ICIN(arama)\n");
		printf("LISTEYI GORUNTULEMEK ICIN(yazdir)\n");
		printf("PROGRAMI SONLANDIRMAK ICIN(cikis)\n");
		scanf("%s",eylem);
		if(strcmp("cikis",eylem)==0)
		{
			printf("!!!!!PROGRAM KAPANIYOR!!!!!\n");
			break;
		}
		else if(strcmp("sil",eylem)==0)
		{
			printf("SILMEK ISTEDIGINIZ SAYI : ");
			scanf("%d",&silinen);
			ilk=Sil(ilk,silinen);
			Kademeleri0la(ilk);
		}
		else if(strcmp("arama",eylem)==0)
		{
			printf("ARAMAK ISTEDIGINIZ SAYIYI GIRINIZ: ");
			scanf("%d",&aranan);
			sonuc=Arama(ilk,aranan);
			if(sonuc!=-1)
				printf("ARADIGINIZ SAYI %d. KATMANDA\n",sonuc);
		}
		else if(strcmp("yazdir",eylem)==0)
		{
			ListeYazdir(ilk,elemansayisi);
		}
		else if(strcmp("kademe",eylem)==0)
		{
			KademeleriOlustur(ilk,elemansayisi);
		}
		else if(strcmp("ekle",eylem)==0)
		{
			printf("EKLEMEK ISTEDIGINIZ DEGERI GIRINIZ: ");
			scanf("%d",&deger);
			ilk=SiraliEkle(ilk,deger);
			Kademeleri0la(ilk);
			elemansayisi++;	
		}
	}
	Temizlik(ilk);	
	return 0;
}





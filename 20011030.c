#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 15
 
int check(int** mat,int sutun,int satir)
{
	int flag = 0;
	int i,j,k;
	i=0;
	while(i<sutun && flag == 0)
	{
		j=0;
		while(j<satir && flag == 0)
		{
			k=j+1;
			while(k<satir && flag == 0)
			{
				if(mat[j][i]==mat[k][i])
					flag = 1;
				k++;
			}
			j++;
		}
		i++;
	}
	return !flag;
}

void rotate(int** mat,int n,int i)
{
	int j, son = mat[i][n-1];
	for(j=n-1;j>0;j--)
		mat[i][j]=mat[i][j-1];
	mat[i][0] = son;
}

void printMatris(int** mat,int n,char** strings)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%s ",strings[mat[i][j]]);	
		}
		printf("\n");
	}	
} 

int** createMat(int renk_sayisi,char** renkler)
{
	char renk[MAX];
	char satir_renkler[renk_sayisi][MAX];
	int mevcut_renk = 0;
	int index_sutun = 0;
	int i,j,k,flag,satir_flag,eklenebilir,index;
	
	int** mat = (int**)malloc(sizeof(int*)*renk_sayisi);
	for(i=0;i<renk_sayisi;i++)
		mat[i] = (int*)malloc(sizeof(int)*renk_sayisi);
		
	for(i=0;i<renk_sayisi;i++)
	{
		for(j=0;j<renk_sayisi;j++)
			strcpy(satir_renkler[j],"Empty");
		index_sutun= 0;	
		for(j=0;j<renk_sayisi;j++)
		{
			do
			{
				flag = 0;
				satir_flag = 0;
				eklenebilir = 1;				
				printf("OYUN TAHTASI [%d][%d]: ",i,j);
				scanf("%s",renk);
				for(k=0;k<mevcut_renk;k++)
				{
					if(strcmp(renkler[k],renk)==0)
					{
						flag = 1;
						index = k;
					}
					if(strcmp(satir_renkler[k],renk)==0)
						satir_flag = 1;
				}
				if(!flag)
				{
					if(mevcut_renk<renk_sayisi)
					{
						strcpy(renkler[mevcut_renk],renk);
						index = mevcut_renk;
						mevcut_renk++;						
					}
					else
					{
						printf("Daha Fazla Renk Cesidi Giremezsiniz!!!\n");
						eklenebilir = 0;
					}	
				}
				if(eklenebilir)
				{	
					if(!satir_flag)
					{
						strcpy(satir_renkler[index_sutun],renk);
						index_sutun++;					
					}
					else
					{
						eklenebilir = 0;
						printf("Bu Satirda Bu Renk Kullanildi!!!\n");
					}
				}
				if(eklenebilir)
				{
					mat[i][j]=index;
				}
			}while(eklenebilir == 0);
		}
	}

	return mat;	
}
 
int BackTrackingforDetay(int** mat,int n,int i,char** renkler)
{
	int j,result;
	if(i==n)
		return 1;
	j=0;
	result = check(mat,n,i+1);
	while(j<n)
	{
		if(result==1)
		{
			result = BackTrackingforDetay(mat,n,i+1,renkler);
			if(result == 1)
				return 1;
		}
		if(result==0)
		{
			rotate(mat,n,i);
			result = check(mat,n,i+1);
			printf("=================\n");
			printf("%d.Satir Rotate Edildi\n",i);
			printMatris(mat,n,renkler);
			printf("=================\n");
		}
		j++;
	}
	return 0;
}

int BackTracking(int** mat,int n,int i)
{
	int j,result;
	if(i==n)
		return 1;
	j=0;
	result = check(mat,n,i+1);
	while(j<n)
	{
		if(result==1)
		{
			result = BackTracking(mat,n,i+1);
			if(result == 1)
				return 1;
		}
		if(result==0)
		{
			rotate(mat,n,i);
			result = check(mat,n,i+1);
		}
		j++;
	}
	return 0;
}
 
int main()
{
	int renk_sayisi,i,j,a;
	int result,menu,exit=1,inner_menu,inner_exit=1;
	int** mat;
	char** renkler;
	
	
	while(exit)
	{
		printf("===============BACKTRACKING==============\n");
		do
		{
			printf("Oyuna Girmek                   '1'\n");
			printf("Cikis Yapmak                   '0'\n");
			printf("                    ");	
			scanf("%d",&menu);
		}while(menu<0 || menu>1);
		if(menu==0)
			exit = 0;
		else
		{
			inner_exit = 1;
			while(inner_exit)
			{
				do
				{				
					printf("Normal Mod                     '1'\n");
					printf("Detay Mod                      '0'\n");
					printf("Menuye Donmek                  '9'\n");
					printf("                    ");	
					scanf("%d",&inner_menu);
				}while((inner_menu<0 || inner_menu>1) && inner_menu!= 9);
				if(inner_menu == 0)
				{
					do{	
						printf("Renk Sayisini Giriniz: ");
						scanf("%d",&renk_sayisi);
					}while(renk_sayisi>8 || renk_sayisi<3);
					renkler = (char**)malloc(sizeof(char*)*renk_sayisi);
					for(i=0;i<renk_sayisi;i++)
						renkler[i] = (char*)malloc(sizeof(char)*MAX);
					mat = createMat(renk_sayisi,renkler);					
					result=BackTrackingforDetay(mat,renk_sayisi,1,renkler);
					if(result == 1)
					{	
						printf("              Sart Saglandi!\n");
						printf("Matris'in Yeni Hali:\n");	
						printMatris(mat,renk_sayisi,renkler);	
					}
					else
						printf("             Sart Saglanamadi!\n");
					for(i=0;i<renk_sayisi;i++)
						free(mat[i]);
					free(mat);				
				}
				else if(inner_menu == 1)
				{
					do{	
						printf("Renk Sayisini Giriniz: ");
						scanf("%d",&renk_sayisi);
					}while(renk_sayisi>8 || renk_sayisi<3);
					renkler = (char**)malloc(sizeof(char*)*renk_sayisi);
					for(i=0;i<renk_sayisi;i++)
						renkler[i] = (char*)malloc(sizeof(char)*MAX);
					mat = createMat(renk_sayisi,renkler);
					result=BackTracking(mat,renk_sayisi,1);
					if(result == 1)
					{	
						printf("              Sart Saglandi!\n");
						printf("Matris'in Yeni Hali:\n");	
						printMatris(mat,renk_sayisi,renkler);	
					}
					else
						printf("             Sart Saglanamadi!\n");
					for(i=0;i<renk_sayisi;i++)
						free(mat[i]);
					free(mat);	
				}
				else
					inner_exit = 0;
			}	
		}
	}
	return 0;
 }
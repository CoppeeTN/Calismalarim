#include <stdio.h>
#define MAX 50

int isEmpty(char STACK[],int top)
{
    if(top==0)
        return 1;
    else
        return 0;
}

int isFull(char STACK[],int top)
{
    if(top==MAX-1)
        return 1;
    else
        return 0;
}

void push(char X,char STACK[],int *top)
{
    STACK[*top]=X;
    *top+=1;
}

void pop(int *top,char STACK[])
{
	*top-=1;
	STACK[*top]='\0';
}

char peek(char STACK[],int top)
{
	char X=STACK[top-1];
    return X;
}

void decimaltobinary(char str[],int value)
{
	int i,digit;
	if(value<128 && value>-129)
    {
        for (i = 7; i >= 0; i--)
        {
        	digit = value >> i;
        	if(digit & 1)
        		str[7-i]='1';
			else
				str[7-i]='0';
		}
		str[8]='\0';
    }
    else if(value<32768 && value>-32769)
    {
    	for(i = 15; i >= 0; i--)
    	{
    		digit = value >> i;
    		if(digit & 1)
    			str[15-i]='1';
			else
				str[15-i]='0';
		}
		str[16]='\0';
	}
	else if(value<8388608 && value>-8388609)
    {
    	for(i = 23; i >= 0; i--)
    	{
    		digit = value >> i;
    		if(digit & 1)
    			str[23-i]='1';
			else
				str[23-i]='0';
		}
		str[24]='\0';
	}
}

void output(char STACK[],int *top)
{
	char k;
	int popcounter=0;
	k = peek(STACK,*top);
	if(isEmpty(STACK,*top))
		printf("0 ve 1 ler esit sayidadir.\n");
	else
	{
		printf("%c sayisi fazladir. ",k);
		while(!isEmpty(STACK,*top))
		{
			pop(top,STACK);
			popcounter++;
		}
		printf("%d tane %c lazim.",popcounter,k^1);
	}
}

void stack(char str[],char STACK[],int *top)
{
	int i=0;
	while(str[i]!='\0' &&  !isFull(STACK,*top))
	{
		if(isEmpty(STACK,*top))
			push(str[i],STACK,top);
		else if(str[i]!=peek(STACK,*top))
			pop(top,STACK);
		else
			push(str[i],STACK,top);
		i++;		
	}
}


int main()
{
    int value,top=0;
	char str[100],STACK[MAX]={'\0'};
    
	printf("Decimal: ");
  	scanf("%d", &value);

	decimaltobinary(str,value);
	printf("(String e donusturuldukten sonra: %s)\n",str);
	stack(str,STACK,&top);
	output(STACK,&top);
    return 0;
}

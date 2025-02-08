
#include <pic16f877a.h>
#include <stdlib.h>
#include <math.h>
#define byte unsigned char



byte Current_ind;

byte Check_buttons(void)  
{ 
	byte tmp, tmp_PORTB=PORTB, tmp_TRISB=TRISB; 
	TRISB&=0x0F; 
	PORTB|=0xF0; 
	tmp=PORTB^0xFF; 
	PORTB=tmp_PORTB; 
	TRISB=tmp_TRISB; 
	return(tmp>>4); 
}


void delay(unsigned int tmp) 
{ 
	while(tmp--);
	return;
}

void delay_next(unsigned int tmp) 
{ 
int tmp1=tmp;
for(int i=0; i<7; i++)
{
	while(tmp--);

int tmp=tmp1;
}
	return;
}

void Pulse(unsigned int x) 
{ 
	RB2=1; 
	delay(x);
	RB2=0;
	delay(x);
} 


void Send_Command_LCD (byte tmp)//
{ 
	while (Check_buttons())delay(1000); 
	RB1=0; 
	PORTB=(PORTB & 0x0F)+ (tmp & 0xF0); 
	Pulse(100); 
	PORTB=(PORTB & 0x0F)+ (tmp<<4); 
	Pulse(100); 
	RB1=1; 
	delay(1000); 
} 


void Init_LCD(void) 
{ 
	delay(1000); 
	TRISB=0; 
	PORTB=0x30; 
	Pulse(100); 
	Pulse(100);
	Pulse(100); 
	PORTB=0x20; 
	Pulse(100); 
	Send_Command_LCD (0x28); 
	Send_Command_LCD (0x0C); 
	Send_Command_LCD (0x06); 
	Send_Command_LCD (0x02); 
	Current_ind=0; 
} 

void Set_Coord_LCD(byte i, byte j) 
{ 
	 if(i==0)
	 {
		Current_ind=j;
		Send_Command_LCD(0x80+j);
	 } 
	 else 
	 {
		Current_ind=16+j;
		Send_Command_LCD(0xC0+j);
	 }; 
	 return; 
} 

void Send_Byte_LCD (byte tmp) 
{
	while (Check_buttons())delay(1000); 
	PORTB=(PORTB & 0x0F)+ (tmp & 0xF0); 
	Pulse(10); 
	PORTB=(PORTB & 0x0F)+ (tmp<<4); 
	Pulse(10); 
	Current_ind++; 
	if(Current_ind==16)
	{
		Set_Coord_LCD(1,0); 
	}
} 
 void Show_String_LCD(const char * mySTRING);


static const char str_BLANK[] = "                 ";
void Clr_LCD(void) 
{ 
	Set_Coord_LCD(0,0); 
	Show_String_LCD(str_BLANK); 
	Show_String_LCD(str_BLANK); 
	Set_Coord_LCD(0,0); 
}


void Show_String_LCD(const char * mySTRING) 
{
	while(*mySTRING)
	{
		Send_Byte_LCD(*(mySTRING++));
	}; 
}

char* itoa1(int a,char *num)
{
	int i =0;
	int number=0;
	char num2[10];
if(a==0)
{
num2[i] = '0';
i=i+1;
}
	while (a!=0)
	{
		number = a%10;
		if (number==0) num2[i] = '0';
		if (number==1) num2[i] = '1';
		if (number==2) num2[i] = '2';
		if (number==3) num2[i] = '3';
		if (number==4) num2[i] = '4';
		if (number==5) num2[i] = '5';
		if (number==6) num2[i] = '6';
		if (number==7) num2[i] = '7';
		if (number==8) num2[i] = '8';
		if (number==9) num2[i] = '9';
		a = a/10;
		i=i+1;
	}

	num2[i] = '\0';
	
	int gran = i;
	i=i-1;
	int j;
	for (j=0;j<gran;j++)
	{
		num[j] = num2[i];
		i--;
	}
	num[gran] = '\0';
	
	return num;
}

int atoi1(char *num, int size)
{
	int count =0;
	int i=0;
	for (i=0; i<size+1; i++)
	{
		if (num[i]=='0') count = (0)*0+count;
		if (num[i]=='1') count = (pow(10,size-i-1))*1+count;
		if (num[i]=='2') count = (pow(10,size-i-1))*2+count;
		if (num[i]=='3') count = (pow(10,size-i-1))*3+count;
		if (num[i]=='4') count = (pow(10,size-i-1))*4+count;
		if (num[i]=='5') count = (pow(10,size-i-1))*5+count;
		if (num[i]=='6') count = (pow(10,size-i-1))*6+count;
		if (num[i]=='7') count = (pow(10,size-i-1))*7+count;
		if (num[i]=='8') count = (pow(10,size-i-1))*8+count;
		if (num[i]=='9') count = (pow(10,size-i-1))*9+count;
	}
	return count;
}

int sravn(char *ch1, char* ch2)
{
	int f=1;
	int i=0;
 	int len=0;
    int len2=0;
	int j;
	
	while (ch1[i]!='\0')
	{
		len=len+1;
		i=i+1;
	}
	len=len+1;
	i=0;
    while (ch2[i]!='\0')
	{
		len2=len2+1;
		i=i+1;
	}
	len2=len2+1;
	if (len!=len2)
	{
 		f=2;
		return f;
	}
 	else
	{
		i=len-2;
		for (j=0;j<len-1;j++)
		{
			if (ch1[i] != ch2[j])
			{
				f=0;
				return f;
			}
			i--;
		}	
	}
	return f;
}




void main(void){
	
	TRISD = 0x00;
	int first=0;
	int second =0;
	char str1[10] ="FIRST";
	char str2[10] ="SECOND";
	int len1=0;
	int len2=0;
	int i=0;
	PORTD = 0x00;
	Init_LCD();
	Clr_LCD();
	Show_String_LCD(str1);
	Set_Coord_LCD(1,0);
	Show_String_LCD(str2);
	while (1)
	{
	   	delay(10000);
		if (Check_buttons() == 1)
			{	
				

				first=first+1;
				itoa1(first,str1);
				delay(100);
				Clr_LCD();
				Show_String_LCD(str1);

				Set_Coord_LCD(1,0);
				itoa1(second,str2);
				Show_String_LCD(str2);
			}

		if (Check_buttons() == 2)
			{	

				second=second+1;
				itoa1(second,str2);
				delay(100);
				Clr_LCD();
				itoa1(first,str1);
				Show_String_LCD(str1);

				Set_Coord_LCD(1,0);
				Show_String_LCD(str2);
				
			}

	if (Check_buttons() == 3)
			{	
				
				first=first*10;
				itoa1(first,str1);
				delay(100);
				Clr_LCD();
				Show_String_LCD(str1);

				Set_Coord_LCD(1,0);
				itoa1(second,str2);
				Show_String_LCD(str2);
				
			}
	if (Check_buttons() == 6)
			{	
				
				second=second*10;
				itoa1(second,str2);
				delay(100);
				Clr_LCD();
				itoa1(first,str1);
				Show_String_LCD(str1);

				Set_Coord_LCD(1,0);
				Show_String_LCD(str2);
				
			}

	if (Check_buttons() == 8)
			{	

	

if(sravn(str1,str2)==1)
{
Clr_LCD();
char str4[10]="YES";
Show_String_LCD(str4);
delay_next(90000000);
Clr_LCD();
Show_String_LCD(str1);
Set_Coord_LCD(1,0);
Show_String_LCD(str2);

while(1)
{

RB3 = 1;
delay(10);
RB3 = 0;
delay(10);

if(Check_buttons() == 4)
break;
}
}
else 
{
Clr_LCD();
char str5[10]="NO";
Show_String_LCD(str5);
delay_next(90000000);

Clr_LCD();
Show_String_LCD(str1);
Set_Coord_LCD(1,0);
Show_String_LCD(str2);
}
				
			}



if (Check_buttons() == 12)
{
Clr_LCD();
first=0;
second=0;
itoa1(first,str1);
itoa1(second,str2);
Show_String_LCD(str1);
Set_Coord_LCD(1,0);
Show_String_LCD(str2);
}


	}
}

//				LEADIND and TRAILING of all non-terminals
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 22-3-06 23:19
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<process.h>
void display();
void lead(char,char []);
void trail(char,char []);
void disp_lead();
void disp_trail();
struct productions
{	int np;
	char str[10][10];
	int ln[10];
}p[20];
struct lead_trail
{	char str[20];
}l[20],t[20];
char non_term[20],str[20],cur_str;
int nt;
void main()
{	char i,j,k,bool1,ss,*temp,tmp_str[20];
	clrscr();
	cout<<"Enter no. of non terminals:";
	cin>>nt;
	for(i=0;i<nt;i++)
	{	cout<<"Enter the symbol of a non terminal no. "<<i+1<<"(in capitals only):";
		cin>>non_term[i];
	}
	for(i=0;i<nt;i++)
	{	cout<<"For non terminal "<<non_term[i]<<":";
		cout<<"\n\t\tEnter no. of productions: ";
		cin>>p[i].np;
		for(j=0;j<p[i].np;j++)
		{	cout<<"\t\tEnter the production "<<j+1<<": ";
			cin>>p[i].str[j];
			p[i].ln[j]=strlen(p[i].str[j]);
			l[i].str[0]='\0';
		}
	}
	cout<<"\nProductions are:";
	display();
	for(i=nt-1;i>=0;i--)
	{	lead(non_term[i],l[i].str);
		trail(non_term[i],t[i].str);
	}
	disp_lead();
	disp_trail();
	getch();
	exit(0);
}
void lead(char c1,char c2[20])
{   char c3[10]="\0";
	int i,j,k;
	for(i=0;i<nt;i++)
		if(non_term[i]==c1)
			break;
	for(j=p[i].np-1;j>=0;j--)	//for all productions
	{   if(strcmp(p[i].str[j],"epsilon")==0)
			continue;
		c3[0]='\0';
		for(k=0;k<strlen(p[i].str[j]);k++)	//for every character
		{	if(p[i].str[j][k]<'A' || p[i].str[j][k]>'Z')	//if terminal
			{	c3[0]=p[i].str[j][k];
				c3[1]='\0';
				strcat(c2,c3);
				break;
			}
			else if(strlen(p[i].str[j])==1 && p[i].str[j][k]>='A' && p[i].str[j][k]<='Z' && p[i].str[j][k+1]=='\0')
				lead(p[i].str[j][0],c2);			//if non-terminal and single lt. production
		}
	}
}
void trail(char c1,char c2[20])
{   char c3[10]="\0";
	int i,j,k;
	for(i=0;i<nt;i++)
		if(non_term[i]==c1)
			break;
	for(j=p[i].np-1;j>=0;j--)	//for all productions
	{	if(strcmp(p[i].str[j],"epsilon")==0)
			continue;
		c3[0]='\0';
		for(k=strlen(p[i].str[j])-1;k>=0;k--)	//for every character
		{	if(p[i].str[j][k]<'A' || p[i].str[j][k]>'Z')	//if terminal
			{	c3[0]=p[i].str[j][k];
				c3[1]='\0';
				strcat(c2,c3);
				break;
			}
			else if(strlen(p[i].str[j])==1 && p[i].str[j][k]>='A' && p[i].str[j][k]<='Z' && p[i].str[j][k+1]=='\0')
				trail(p[i].str[j][0],c2);			//if non-terminal and single lt. production
		}
	}
}
void display()
{	int i,j;
	for(i=0;i<nt;i++)
	{	cout<<"\n\t"<<non_term[i]<<" ----->";
		for(j=0;j<p[i].np;j++)
			cout<<"\\"<<p[i].str[j];
	}
}
void disp_lead()
{	int i;
	for(i=0;i<nt;i++)
		cout<<"\n\t"<<"lead("<<non_term[i]<<")"<<" ----->"<<l[i].str;
}
void disp_trail()
{	int i;
	for(i=0;i<nt;i++)
		cout<<"\n\t"<<"trail("<<non_term[i]<<")"<<" ----->"<<t[i].str;
}
/*
O/P:
Enter no. of non terminals:2
Enter the symbol of a non terminal no. 1(in capitals only):S
Enter the symbol of a non terminal no. 2(in capitals only):T

	For non terminal S:
		Enter no. of productions: 3
		Enter the production 1: a
		Enter the production 2: ^
		Enter the production 3: (T)

	For non terminal T:
		Enter no. of productions: 2
		Enter the production 1: T,S
		Enter the production 2: S

Productions are:
	S ----->\a\^\(T)
	T ----->\T,S\S
	lead(S) ----->(^a
	lead(T) ----->(^a,
	trail(S) ----->)^a
	trail(T) ----->)^a,
*/
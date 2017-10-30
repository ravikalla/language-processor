//					To find FIRST of all non-terminals
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 20-3-06 4:18
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<process.h>
struct productions
{   int np;
	char str[10][10];
	int ln[10];
}p[20];
struct first1
{	char str[20];
}f[20];
char non_term[20],str[20],cur_str;
int nt;
void first(char c1[20],char c2[20])
{   char c3[10]="\0";
	int i,j,k;
	if(c1[0]=='\0')						//if null string
		return;
	else if(strcmp(c1,"epsilon")==0)	//if epsilon
	{	strcat(c2,"E");
		return;
	}
	else if(c1[0]<'A' || c1[0]>'Z')		//if terminal
	{   c3[0]=c1[0];
		c3[1]='\0';
		strcat(c2,c3);
		return;
	}
	else if(c1[0]>='A' && c1[0]<='Z')	//if non-terminal
	{   c3[0]='\0';
		for(i=0;i<nt;i++)
			if(non_term[i]==c1[0])
				break;
		for(j=0;j<p[i].np;j++)
			first(p[i].str[j],c3);
		strcat(c2,c3);
		for(j=strlen(c3)-1;j>=0;j--)
			if(c3[j]=='E')				//if epsilon is present
			{	first(c1+1,c2);
				break;
			}
	}
}
void display()
{   int i,j;
	for(i=0;i<nt;i++)
	{   cout<<"\n\t"<<non_term[i]<<" ----->";
		for(j=0;j<p[i].np;j++)
			cout<<"\\"<<p[i].str[j];
	}
}
void disp_first()
{	int i;
	for(i=0;i<nt;i++)
		cout<<"\n\t"<<"first("<<non_term[i]<<")"<<" ----->"<<f[i].str;
}
void main()
{	char i,j,k,bool1,ss,*temp,tmp_str[20];
	int start;
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

			f[i].str[0]='\0';
		}
	}
	cout<<"\nProductions are:";
	display();
	for(i=nt-1;i>=0;i--)
	{   tmp_str[0]=non_term[i];
		tmp_str[1]='\0';
		first(tmp_str,f[i].str);
	}
	disp_first();
	getch();
}
/*
O/P:
Enter no. of non terminals:5
Enter the symbol of a non terminal no. 1(in capitals only):E
Enter the symbol of a non terminal no. 2(in capitals only):X
Enter the symbol of a non terminal no. 3(in capitals only):F
Enter the symbol of a non terminal no. 4(in capitals only):Y
Enter the symbol of a non terminal no. 5(in capitals only):T
	For non terminal E:
		Enter no. of productions: 1
		Enter the production 1: FX
	For non terminal X:
		Enter no. of productions: 2
		Enter the production 1: +FX
		Enter the production 2: epsilon
	For non terminal F:
		Enter no. of productions: 1
		Enter the production 1: TY
	For non terminal Y:
		Enter no. of productions: 2
		Enter the production 1: *TY
		Enter the production 2: epsilon
	For non terminal T:
		Enter no. of productions: 2
		Enter the production 1: (E)
		Enter the production 2: i
Productions are:
	E ----->\FX
	X ----->\+FX\epsilon
	F ----->\TY
	Y ----->\*TY\epsilon
	T ----->\(E)\i
	first(E) ----->(i
	first(X) ----->+E
	first(F) ----->(i
	first(Y) ----->*E
	first(T) ----->(i
*/
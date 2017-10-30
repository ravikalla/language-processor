//				PREDICTIVE PARSING TABLE
//epsilon is mentioned by "epsilon"
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 22-3-06 01:36
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdio.h>
struct productions
{   int np;
	char str[10][10];
	int ln[10];
}p[20];
struct first1
{	char str[20];
}f1[20],f2[20];
char non_term[20],str[20],ss,ip_symb[20],table[10][20][15];
int nt,ip_no;
void first(char c1[20],char c2[20])
{   char c3[10]="\0";
	int i,j,k;
	if(c1[0]=='\0');					//if null string
	else if(strcmp(c1,"epsilon")==0)	//if epsilon
		strcat(c2,"E");					//E stands for epsilon in the string
	else if(c1[0]<'A' || c1[0]>'Z')		//if terminal
	{   c3[0]=c1[0];
		c3[1]='\0';
		strcat(c2,c3);
	}
	else if(c1[0]>='A' && c1[0]<='Z')	//if non-terminal
	{   c3[0]='\0';
		for(i=0;i<nt;i++)				//for finding the index of non-terminal
			if(non_term[i]==c1[0])
				break;
		for(j=0;j<p[i].np;j++)
			first(p[i].str[j],c3);		//finding FIRST for every production
		strcat(c2,c3);
		for(j=strlen(c3)-1;j>=0;j--)	//check if epsilon values are there
			if(c3[j]=='E')				//if epsilon is present
			{	first(c1+1,c2);
				break;
			}
	}
}
void follow(char c1,char c2[20])
{	char c3[10]="\0",c4[2]="\0";
	int j,k,l,m;
	if(c1==ss)
		strcat(c2,"$");
	for(j=0;j<nt;j++)				//for every non-terminal
		for(k=0;k<p[j].np;k++)		//for productions of non-terminal
			for(l=strlen(p[j].str[k])-1;l>=0;l--)//for characters of non-terminal
				if(p[j].str[k][l]==c1)
				{	strcpy(c3,"\0");
					first(p[j].str[k]+l+1,c3);
					if(c3[0]=='\0')
						if(c1==non_term[j])
							continue;
						else
							follow(non_term[j],c2);
					for(m=strlen(c3)-1;m>=0;m--)//copying to follow string
						if(c3[m]!='E')
						{	c4[0]=c3[m];
							c4[1]='\0';
							strcat(c2,c4);
						}
						else
							if(c1==non_term[j])
								continue;
							else
								follow(non_term[j],c2);
				}
}
void pred()
{	int i,j,k,l,m,n;
	char c3[20],c4[20];

	ip_no=0;
	for(i=0;i<nt;i++)
		for(j=0;j<p[i].np;j++)
		{   if(strcmp(p[i].str[j],"epsilon")==0)
				continue;
			for(k=strlen(p[i].str[j])-1;k>=0;k--)
			{   for(l=0;l<ip_no;l++)
					if(p[i].str[j][k]==ip_symb[l] && (p[i].str[j][k]<'A' || p[i].str[j][k]>'Z'))
						break;
				if(l==ip_no && (p[i].str[j][k]<'A' || p[i].str[j][k]>'Z'))
				{	ip_symb[l]=p[i].str[j][k];
					ip_no++;
				}
			}
		}
	ip_symb[ip_no]='$';
	ip_no++;
	for(i=0;i<nt;i++)
		for(j=0;j<ip_no;j++)
			strcpy(table[i][j],"\0");
	for(i=0;i<nt;i++)
	{	for(k=0;k<p[i].np;k++)
		{	c3[0]='\0';
			first(p[i].str[k],c3);
			for(j=0;j<ip_no;j++)
			{	for(l=strlen(c3)-1;l>=0;l--)
				{	if(c3[l]==ip_symb[j])
					{	strcpy(table[i][j],p[i].str[k]);
						break;
					}
					if(c3[l]=='E')
					{	c4[0]='\0';
						follow(non_term[i],c4);
						for(m=strlen(c4)-1;m>=0;m--)
							for(n=0;n<ip_no;n++)
								if(c4[m]==ip_symb[n])
									strcpy(table[i][n],p[i].str[k]);
					}
				}
			}
		}
	}
}
void display()							//for displaying grammar
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
		cout<<"\n\t"<<"first("<<non_term[i]<<")"<<" ----->"<<f1[i].str;
}
void disp_follow()
{	int i;
	for(i=0;i<nt;i++)
		cout<<"\n\t"<<"FOLLOW("<<non_term[i]<<")"<<" ----->"<<f2[i].str;
}
void disp_table()
{	int i,j;
	cout<<"\n\n\t\tPREDECTIVE PARSER TABLE";
	printf("\n\n        |");
	for(i=0;i<ip_no;i++)
		printf("%8c|",ip_symb[i]);
	for(i=0;i<nt;i++)
	{	cout<<"\n";
		printf("%8c|",non_term[i]);
		for(j=0;j<ip_no;j++)
			printf("%8s|",table[i][j]);
	}
}
void main()
{	char i,j,k,bool1,*temp,tmp_str[20];
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
			f1[i].str[0]='\0';
			f2[i].str[0]='\0';
		}
	}
	cout<<"Enter the start symbol:";
	cin>>ss;
	cout<<"\nProductions are:";
	//for finding first of all non-terminals
	for(i=nt-1;i>=0;i--)
	{   tmp_str[0]=non_term[i];
		tmp_str[1]='\0';
		first(tmp_str,f1[i].str);
	}
	//for finding follow of all non-terminals
	for(i=0;i<nt;i++)
		follow(non_term[i],f2[i].str);
	//for finding the predictive parser table
	pred();
	display();
	disp_first();
	disp_follow();
	disp_table();
	getch();
}
/*
O/P:
Enter no. of non terminals:5
Enter the symbol of a non terminal no. 1(in capitals only):E
Enter the symbol of a non terminal no. 2(in capitals only):X
Enter the symbol of a non terminal no. 3(in capitals only):T
Enter the symbol of a non terminal no. 4(in capitals only):Y
Enter the symbol of a non terminal no. 5(in capitals only):F
	For non terminal E:
		Enter no. of productions: 1
		Enter the production 1: TX
	For non terminal X:
		Enter no. of productions: 2
		Enter the production 1: +TX
		Enter the production 2: epsilon
	For non terminal T:
		Enter no. of productions: 1
		Enter the production 1: FY
	For non terminal Y:
		Enter no. of productions: 2
		Enter the production 1: *FY
		Enter the production 2: epsilon
	For non terminal F:
		Enter no. of productions: 2
		Enter the production 1: (E)
		Enter the production 2: i
	Enter the start symbol: E

Productions are:
	E ----->\TX
	X ----->\+TX\epsilon
	T ----->\FY
	Y ----->\*FY\epsilon
	F ----->\(E)\i
	first(E) ----->(i
	first(X) ----->+E
	first(T) ----->(i
	first(Y) ----->*E
	first(F) ----->(i
	FOLLOW(E) ----->$)
	FOLLOW(X) ----->$)
	FOLLOW(T) ----->$)+$)+
	FOLLOW(Y) ----->$)+$)+
	FOLLOW(F) ----->$)+$)+*$)+$)+*

						PREDECTIVE PARSER TABLE
						=======================

        |       +|       *|       )|       (|       i|       $|
      --|--------|--------|--------|--------|--------|--------|
       E|        |        |        |      TX|      TX|        |
       X|     +TX|        | epsilon|        |        | epsilon|
       T|        |        |        |      FY|      FY|        |
       Y| epsilon|     *FY| epsilon|        |        | epsilon|
       F|        |        |        |     (E)|       i|        |
*/
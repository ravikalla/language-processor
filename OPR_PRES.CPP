//					OPERATOR PRECIDENCE TABLE
//epsilon is mentioned by "epsilon"
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 29-3-06 03:20
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdio.h>
struct productions
{	int np;
	char str[10][10];
	int ln[10];
}p[20];
struct lead_trail
{	char str[20];
}l1[20],t1[20];
char non_term[20],ss,ip_symb[20],table[20][20];
int nt,ip_no;
void lead(char c1,char c2[20])
{   char c3[10]="\0";
	int i,j,k;
	for(i=0;i<nt;i++)
		if(non_term[i]==c1)
			break;
	for(j=p[i].np-1;j>=0;j--)	//for all productions
	{	c3[0]='\0';
		for(k=0;k<strlen(p[i].str[j]);k++)	//for every character
			if(p[i].str[j][k]<'A' || p[i].str[j][k]>'Z')	//if terminal
			{	c3[0]=p[i].str[j][k];
				c3[1]='\0';
				strcat(c2,c3);
				break;
			}
			else if(strlen(p[i].str[j])==1 && p[i].str[j][k]>='A' && p[i].str[j][k]<='Z' && p[i].str[j][k+1]=='\0')
				lead(p[i].str[j][0],c2);			//if non-terminal and single lt. production
	}
}
void trail(char c1,char c2[20])
{   char c3[10]="\0";
	int i,j,k;
	for(i=0;i<nt;i++)
		if(non_term[i]==c1)
			break;
	for(j=p[i].np-1;j>=0;j--)	//for all productions
	{	c3[0]='\0';
		for(k=strlen(p[i].str[j])-1;k>=0;k--)	//for every character
			if(p[i].str[j][k]<'A' || p[i].str[j][k]>'Z')	//if terminal
			{	c3[0]=p[i].str[j][k];
				c3[1]='\0';
				strcat(c2,c3);
				break;
			}
			else if(strlen(p[i].str[j])==1 && p[i].str[j][k]>='A' && p[i].str[j][k]<='Z' && p[i].str[j][k+1]=='\0')
				trail(p[i].str[j][0],c2);			//if non-terminal and single lt. production
	}
}
void plot(char c1,char c2,char c3)	//placing operator c1 in table(c2,c3)
{	int i,j;
	for(i=0;i<ip_no;i++)
		if(c2==ip_symb[i])
			break;
	for(j=0;j<ip_no;j++)
		if(c3==ip_symb[j])
			break;
	table[i][j]=c1;
}
void op_pre()
{	int i,j,k,l,m,n;
	char c3[20],c4[20];
	ip_no=0;
	for(i=0;i<nt;i++)
		for(j=0;j<p[i].np;j++)
		{   if(strcmp(p[i].str[j],"epsilon")==0)
				continue;
			//insert all terminals in to "ip_symb" array
			for(k=strlen(p[i].str[j])-1;k>=0;k--)
			{   for(l=0;l<ip_no;l++)	//checking if the terminal is already present in the "ip_symb" table
					if(p[i].str[j][k]==ip_symb[l] && (p[i].str[j][k]<'A' || p[i].str[j][k]>'Z'))
						break;
				if(l==ip_no && (p[i].str[j][k]<'A' || p[i].str[j][k]>'Z'))//if not present,insert the terminal
				{	ip_symb[l]=p[i].str[j][k];
					ip_no++;
				}
			}
		}
	ip_symb[ip_no]='$';	//insert $ at the end of the "ip_symbol" array
	ip_no++;
	for(i=0;i<ip_no;i++)//insert null values in all entries of the table
		for(j=0;j<ip_no;j++)
			table[i][j]='\0';
	for(i=0;i<nt;i++)	//checking all the non-termianls
	{	for(j=0;j<p[i].np;j++)	//checking all the productions
		{	for(k=strlen(p[i].str[j])-3;k>=0;k--)	//checking all characters in the production
				if((p[i].str[j][k]<'A'||p[i].str[j][k]>'Z')&&(p[i].str[j][k+1]>='A'&&p[i].str[j][k+1]<='Z')&&(p[i].str[j][k+2]<'A'||p[i].str[j][k+2]>'Z'))
					plot('=',p[i].str[j][k],p[i].str[j][k+2]);//if the sequence is of the form "terminal non-terminal terminal", then terminal = terminal
			for(k=strlen(p[i].str[j])-2;k>=0;k--)
				if((p[i].str[j][k]<'A'||p[i].str[j][k]>'Z')&&(p[i].str[j][k+1]>='A'&&p[i].str[j][k+1]<='Z'))
				{	c3[0]='\0';//if the sequence is "terminal non-termianl", terminal < leading(non-terminal)
					lead(p[i].str[j][k+1],c3);
					for(l=strlen(c3)-1;l>=0;l--)
						plot('<',p[i].str[j][k],c3[l]);
				}
			for(k=strlen(p[i].str[j])-2;k>=0;k--)
				if((p[i].str[j][k+1]<'A'||p[i].str[j][k+1]>'Z')&&(p[i].str[j][k]>='A'&&p[i].str[j][k]<='Z'))
				{	c3[0]='\0';//if the sequence is "non-terminal termianl", trailing(non-terminal) > terminal
					trail(p[i].str[j][k],c3);
					for(l=strlen(c3)-1;l>=0;l--)
						plot('>',c3[l],p[i].str[j][k+1]);
				}
		}
	}
	c3[0]='\0';
	lead(ss,c3);
	for(l=strlen(c3)-1;l>=0;l--)
		plot('<','$',c3[l]);
	c3[0]='\0';
	trail(ss,c3);
	for(l=strlen(c3)-1;l>=0;l--)
		plot('>',c3[l],'$');
}
void disp_table()
{	int i,j;
	cout<<"\n\n\t\tOPERATOR PRECEDENCE TABLE";
	printf("\n\n    |");
	for(i=0;i<ip_no;i++)
		printf("%4c|",ip_symb[i]);
	for(i=0;i<ip_no;i++)
	{	printf("\n%4c|",ip_symb[i]);
		for(j=0;j<ip_no;j++)
			printf("%4c|",table[i][j]);
	}
}
void main()
{	char i,j,k,bool1,*temp,tmp_str[20];
	cout<<"\nEnter no. of non terminals:";
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
			l1[i].str[0]='\0';
		}
	}
	cout<<"\nEnter the start symbol:";
	cin>>ss;
	for(i=nt-1;i>=0;i--)
	{	lead(non_term[i],l1[i].str);
		trail(non_term[i],t1[i].str);
	}
	op_pre();
	disp_table();
	getch();
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

Enter the start symbol: S

	OPERATOR PRECEDENCE TABLE
	=========================

    |   a|   ^|   )|   (|   ,|   $|
   -|----|----|----|----|----|----|
   a|    |    |   >|    |    |    |
   ^|    |    |   >|    |   >|   >|
   )|    |    |   >|    |   >|   >|
   (|   <|   <|   =|   <|   <|    |
   ,|   <|   <|   >|   <|   >|    |
   $|   <|   <|    |   <|    |    |
*/
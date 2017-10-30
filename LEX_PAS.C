//				LEXICAL ANALYSER for PASCAL patterns
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 17/JAN/06 1:34
#include<stdio.h>
#include<conio.h>
#include<string.h>
void main(void)
{	FILE *p1;
	char c[100],temp[100];
	//PASCAL keywords
	char keys=40,key[50][20]={"PROGRAM","INOUT","INPUT","OUTPUT","var","real",
							"integer","begin","READ","WRITELN","WRITE","end",
							"div","mod","and","or","not","if","then","else",
							"case","of","with","while","do","repeat","until",
							"for","to","const","type","PROCEDURE","FUNCTION",
							"array","file","record","set","nil","goto","label",
							"in"};
	//PASCAL special symbols
	char sps=23,sp[50][2]={"\'","{","}","(",")","[","]",";",",",":=",":","=",".",
							"+","-","*","/","#","<",">","<>",">=","<="};
	char get,*d,*e;
	int i,j,k;
	p1=fopen("test.pas","r");	//file to be checked for
	clrscr();
	do
	{	fscanf(p1,"%s",c);		//scanning a string
		if(strcmp(c,"")==0)		//if no string is read,then break
			break;
		printf("\nscanned::%s\n",c);
		for(j=0;j<keys;j++)		//checking for keywords
		{	if(strstr(c,key[j])!=NULL)
			{	printf("\n%20s     ----->is a keyword",key[j]);
				strcpy(c+(strstr(c,key[j])-c),c+(strstr(c,key[j])-c)+strlen(key[j]));
				j=-1;
			}
		}
		for(j=0;j<sps;j++)		//checking for special symbols
		{	if(strstr(c,sp[j])!=NULL)
			{	printf("\n%20s     ----->is a special symbol",sp[j]);
				if(strcmp(sp[j],"\'")==0)	//checking for string
				{   printf("\n");
					i=strstr(c,sp[j])-c;
					k=0;
					strcpy(c+(strstr(c,sp[j])-c),c+(strstr(c,sp[j])-c)+strlen(sp[j]));
					for(;c[i]!='\'';i++)
					{	if(c[i]!='\0')
						{	temp[k++]=c[i];
							c[i]=' ';
						}
						else if(c[i]=='\0')
						{	i=-1;
							fscanf(p1,"%s",c);
							printf("\nscanned::%s\n",c);
						}
					}
					temp[k]='\0';
					printf("%20s     ----->is a string",temp);
					printf("\n                   \'     ----->is a special symbol");
				}
				strcpy(c+(strstr(c,sp[j])-c),c+(strstr(c,sp[j])-c)+strlen(sp[j]));
				j=-1;
			}
		}
		getch();
	}while(1);
	getch();
}
//				LEXICAL ANALYSER for C patterns
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 15/JAN/06	at 2:45 am
#include<stdio.h>
#include<conio.h>
#include<string.h>
void main(void)
{	FILE *p1;
	char c[100],temp[100];
	//	All key words{keys=no.of keywords,key=array of character strings}
	char keys=20,key[50][20]={"include",
	"main","printf","scanf","getch","getche","getchar","putchar","exit",
	"int","float","double","long","char","void",
	"for","while","do","break","continue"};
	//	All special symbols{sps=no.of apecial symbols,sp=array of special symbol strings}
	char sps=17,sp[50][2]={"#","\"","<",">","(",")","{","}",";","\\",
							"'","+","-","*","/",".","="};
	char get,*d,*e,header=0;
	int i,j,k;
	p1=fopen("test.c","r");//open the file which is to be tested
	clrscr();
	do
	{	fscanf(p1,"%s",c);
		if(strcmp(c,"")==0)
			break;							//if no character is read, quit
		for(j=0;j<keys;j++)					//check all the keywords
		{	if(strstr(c,key[j])!=NULL)
			{	printf("\n%20s     ----->is a keyword",key[j]);
				strcpy(c+(strstr(c,key[j])-c),c+(strstr(c,key[j])-c)+strlen(key[j]));
				j=-1;
			}
		}
		for(j=0;j<sps;j++)					//check all special symbols
		{	if(strstr(c,sp[j])!=NULL)
			{	printf("\n%20s     ----->is a special symbol",sp[j]);
				if(strcmp(sp[j],"<")==0)	//for header file
				{   k=0;
					for(i=(strstr(c,sp[j])-c)+1;c[i]!='>';i++)
					{	temp[k++]=c[i];
						c[i]=' ';
					}
					temp[k]='\0';
					printf("\n%20s     ----->is a header file",temp);
				}
				if(strcmp(sp[j],"\"")==0)	//for string
				{   printf("\n");
					i=strstr(c,sp[j])-c;
					k=0;
					strcpy(c+(strstr(c,sp[j])-c),c+(strstr(c,sp[j])-c)+strlen(sp[j]));
					for(;c[i]!='\"';i++)
					{	if(c[i]!='\0')
						{	temp[k++]=c[i];
							c[i]=' ';
						}
						else if(c[i]=='\0')
						{	i=-1;
							fscanf(p1,"%s",c);
						}
					}
					temp[k]='\0';
					printf("%20s     ----->is a string",temp);
					printf("\n                   \"     ----->is a special symbol");
				}
				strcpy(c+(strstr(c,sp[j])-c),c+(strstr(c,sp[j])-c)+strlen(sp[j]));
				j=-1;
			}
		}
		getch();
	}while(1);
	getch();
}
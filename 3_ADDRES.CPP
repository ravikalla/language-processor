
//			3-address code generator
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 4-4-06 01:31
#include<iostream.h>
#include<conio.h>
#include<string.h>
#define PRODUCTIONS 40
void main()
{   char str[20],assign,symb[3],symbol[PRODUCTIONS]="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",arr[PRODUCTIONS][5];
	int i,j,k,pos1,pos2,max=0;
	clrscr();
	cout<<"Enter the expression:";
	cin>>str;
	assign=str[0];
	strcpy(str,str+2);
	for(k=0;str[k]!='\0';k++)
	{	if(str[k]=='(')
			pos1=k;
		else if(str[k]==')')
		{	pos2=k;
			for(strcpy(symb,"*/"),j=0;j<2;j++)
			{	for(i=pos1+1;i<pos2;i++)
				{	if(str[i]==symb[0]||str[i]==symb[1])
					{	strcpy(arr[max],str+i-1);
						arr[max][3]='\0';
						str[i-1]=symbol[max++];
						strcpy(str+i,str+i+2);
						pos2-=2;
						i=pos1;
					}
				}
				strcpy(symb,"+-");
			}
			strcpy(str+pos2,str+pos2+1);
			strcpy(str+pos1,str+pos1+1);
			k=-1;
		}
	}
	for(j=0,strcpy(symb,"*/");j<2;j++)
	{	for(i=0;str[i]!='\0';i++)
		{	if(str[i]==symb[0]||str[i]==symb[1])
			{	strcpy(arr[max],str+i-1);
				arr[max][3]='\0';
				str[i-1]=symbol[max++];
				strcpy(str+i,str+i+2);
				i=-1;
			}
		}
		strcpy(symb,"+-");
	}
	for(i=0;i<max;i++)
		cout<<"\n\t"<<symbol[i]<<":="<<arr[i];
	cout<<"\n\t"<<assign<<":="<<str;
	getch();
}
/*O/P:-
Enter the expression:	a=(b+c*(d/e+f*g)-h)

		A:=d/e
		B:=f*g
		C:=A+B
		D:=c*C
		E:=b+D
		F:=E-h
		a:=F
*/
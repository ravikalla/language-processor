//					ELIMINATION OF LEFT RECURSION
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 3-3-06 8:24
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<process.h>
class productions
{   public:
		int np;
		char str[10][10];
		int ln[10];
}p[10];
void elim();
void display();
char non_term[20],str[20],cur_str;
int nt;
void main()
{	char i,j,k,bool1,ss,*temp;
	int start;
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

			//to sort the productions in increasing order
			{	bool1=0;
				for(k=0;k<j;k++)
				{	if(p[i].ln[k]<p[i].ln[j])
					{	bool1=1;
						break;
					}
				}
				if(bool1==1)
				{	strcpy(temp,p[i].str[j]);
					strcpy(p[i].str[j],p[i].str[k]);
					strcpy(p[i].str[k],temp);
					p[i].ln[j]+=p[i].ln[k];
					p[i].ln[k]=p[i].ln[j]-p[i].ln[k];
					p[i].ln[j]-=p[i].ln[k];
				}
			}
		}
		//to move epsilon  production to the end
		for(j=0;j<p[i].np;j++)
		{	if(strcmp(p[i].str[j],"epsilon")==0)
			{   p[i].ln[j]=0;
				for(k=j;k<p[i].np;k++)
				{	strcpy(temp,p[i].str[k+1]);
					strcpy(p[i].str[k+1],p[i].str[k]);
					strcpy(p[i].str[k],temp);
					p[i].ln[k+1]+=p[i].ln[k];
					p[i].ln[k]=p[i].ln[k+1]-p[i].ln[k];
					p[i].ln[k+1]-=p[i].ln[k];
				}
				break;
			}
		}
	}
	display();
	elim();
	display();
}

void elim()
{   int i,j,k,first;
	char new_prod,*temp,*temp1;
	new_prod='1';
	for(i=0;i<nt;i++)
	{	for(j=0;j<p[i].np;j++)
		{	if(p[i].str[j][0]==non_term[i])
			{   first=0;
				for(k=0;k<p[i].np;k++)
				{	if(strcmp(p[i].str[k],"epsilon")!=0 && p[i].str[k][0]>='a' && p[i].str[k][0]<='z')
					{	if(first==0)
						{	first=1;
							non_term[nt]=new_prod;
							p[nt].np=2;
							strcpy(temp,p[i].str[j]+1);
							temp1[0]=new_prod;
							temp1[1]='\0';
							strcpy(p[nt].str[0],strcat(temp,temp1));
							strcpy(p[nt].str[1],"epsilon");
						}
						strcpy(p[i].str[k],strcat(p[i].str[k],temp1));
					}
				}
				if(first==1)
				{	nt++;
					new_prod++;
					p[i].np--;
					strcpy(p[i].str[j],p[i].str[p[i].np]);
					j--;
				}
			}
		}
	}
}
void display()
{   int i,j;
	cout<<"\nProductions are:";
	for(i=0;i<nt;i++)
	{   cout<<"\n\t"<<non_term[i]<<" ----->";
		for(j=0;j<p[i].np;j++)
		{	cout<<"\\"<<p[i].str[j];
		}
	}
	getch();
}
/*
O/P:
Enter no. of non terminals:3
Enter the symbol of a non terminal no. 1(in capitals only):A
Enter the symbol of a non terminal no. 2(in capitals only):B
Enter the symbol of a non terminal no. 3(in capitals only):C

For non terminal A:
		Enter no. of productions:3
		Enter the production 1:Abc
		Enter the production 2:de
		Enter the production 3:f

For non terminal B:
		Enter no. of productions:3
		Enter the production 1:aBc
		Enter the production 2:Bde
		Enter the production 3:fgh

For non terminal C:
		Enter no. of productions:4
		Enter the production 1:abc
		Enter the production 2:Cab
		Enter the production 3:de
		Enter the production 4:epsilon
Productions are:
	A ----->\Abc\de\f
	B ----->\aBc\Bde\fgh
	C ----->\Cab\de\abc\
Productions after elimination of left recursion are:
	A ----->\f1\de1
	B ----->\aBc2\fgh2
	C ----->\de3\abc3
	1 ----->\bc1\epsilon
	2 ----->\de2\epsilon
	3 ----->\ab3\epsilon
*/
//				LEFT FACTORING
//Created on 17/APR/06	at 2:58 am
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<process.h>
char non_term[20],str[20],cur_str;
int nt;
class productions
{   public:
		int np;
		char str[10][10];
		int ln[10];
}p[10];
void match(char c1[30],char c2[30],char c3[30])
{	for(int i=0;c1[i]!='\0' && c2[i]!='\0' && c1[i]==c2[i];i++)
		c3[i]=c1[i];
	c3[i]='\0';
}
void fact()
{   int i,j,k,l,bool1,bool2,matched;
	char new_prod,temp[30],temp1[30],temp2[30];
	new_prod='1';
	for(i=0;i<nt;i++)				//for every non-terminal
	{	for(j=0;j<p[i].np;j++)		//for every production
		{   if(strcmp(p[i].str[j],"epsilon")==0)
				continue;
			matched=strlen(p[i].str[j]);
			bool1=0;				//boolean1=0 means not matched
			for(k=0;k<p[i].np;k++)	//check the production with every other production
			{	if(k!=j)			//to avoid checking a production with itself
				{	match(p[i].str[j],p[i].str[k],temp2);
					l=strlen(temp2);
					if(l>0 && l<=matched)
					{	matched=l;
						bool1=1;
						strcpy(temp,temp2);//temp contains the smallest matched string
					}
				}
			}
			if(bool1==1)			//if there is a match in the strings
			{	bool2=0;
				for(k=0;k<p[i].np;k++)//check every production with the smallest matched string
				{	match(temp,p[i].str[k],temp1);
					if(strcmp(temp,temp1)==0)
					{	if(bool2==0)//if it is the first match, create a new production
						{	temp2[0]=new_prod;
							temp2[1]='\0';
							non_term[nt]=new_prod;
							p[nt].np=0;
						}
						if(strcmp(p[i].str[k],temp)==0)	//if it is the actual production,keep "epsilon" in the new non terminal
						{	strcpy(p[nt].str[p[nt].np],"epsilon");
							p[nt].np++;
						}
						else
						{	strcpy(p[nt].str[p[nt].np],p[i].str[k]+strlen(temp));
							p[nt].np++;
						}
						if(bool2==0)
						{	bool2=1;
							strcpy(p[i].str[k],strcat(temp1,temp2));
						}
						else
						{	for(l=k;l<p[i].np-1;l++)
								strcpy(p[i].str[l],p[i].str[l+1]);
							p[i].np--;
						}
					}
				}
				new_prod++;
				nt++;
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
			cout<<"\\"<<p[i].str[j];
	}
	getch();
}
void main()
{	char i,j,k,bool1,*temp;
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
	fact();
	display();
}
/*
O/P:
Enter no. of non terminals:2
Enter the symbol of a non terminal no. 1(in capitals only):A
Enter the symbol of a non terminal no. 2(in capitals only):S

	For non terminal A:
		Enter no. of productions: 3
		Enter the production 1: abc
		Enter the production 2: abcd
		Enter the production 3: ab

	For non terminal S:
		Enter no. of productions: 3
		Enter the production 1: ABCD
		Enter the production 2: ABC
		Enter the production 3: AB

Productions are:
	A ----->\abcd\abc\ab
	S ----->\ABCD\ABC\AB
Productions are:
	A ----->\ab2
	S ----->\AB4
	1 ----->\c5
	2 ----->\1\epsilon
	3 ----->\C6
	4 ----->\3\epsilon
	5 ----->\d\epsilon
	6 ----->\D\epsilon
*/
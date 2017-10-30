//				TOP DOWN PARSING
//epsilon is mentioned by "epsilon"
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 3-3-06 02:24
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
char non_term[20],str[20],cur_str;
int nt,ln;
char rec(int *i)
{	int st_pos,prod_no,prod_pos,k,l;
	for(k=0;k<nt;k++)
		if(non_term[k]==cur_str)
			break;
	for(prod_no=0;prod_no<p[k].np;prod_no++)
	{	st_pos=*i;
		for(prod_pos=0;;prod_pos++)
			if(p[k].str[prod_no][prod_pos]=='\0')
			{   *i=st_pos;
				return('y');
			}
			else if(str[st_pos]=='\0')
				break;
			else if(p[k].str[prod_no][prod_pos]==str[st_pos])
				st_pos++;
			else if(p[k].str[prod_no][prod_pos]>='a' && p[k].str[prod_no][prod_pos]<='z')
				break;
			else if(p[k].str[prod_no][prod_pos]>='A' && p[k].str[prod_no][prod_pos]<='Z')
			{	cur_str=p[k].str[prod_no][prod_pos];
				if(rec(&st_pos)=='y')
					continue;
				else
					break;
			}
			else
				exit(0);
	}
	return('n');
}
void main()
{	char i,j,k,bool1,ss,*temp;
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
			{	bool1=0;
				for(k=0;k<j;k++)
					if(p[i].ln[k]<p[i].ln[j])
					{	bool1=1;
						break;
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
		//to keep epsilon  production at the end
		for(j=0;j<p[i].np;j++)
			if(strcmp(p[i].str[j],"epsilon")==0)
			{	for(k=j;k<p[i].np;k++)
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
	cout<<"Enter the start symbol:";
	cin>>ss;
	do
	{   cout<<"\nProductions are:";
		for(i=0;i<nt;i++)
		{   cout<<"\n\t"<<non_term[i]<<" ----->";
			for(j=0;j<p[i].np;j++)
			{	cout<<"\\"<<p[i].str[j];
			}
		}
		cur_str=ss;
		cout<<"\nEnter the input string:";
		cin>>str;
		ln=strlen(str);
		start=0;
		if(rec(&start)=='y' && start==ln )
			cout<<"\nString accepted";
		else
			cout<<"\nStringnot accepted";
		cout<<"\nDo u enter another string(y/n): ";
	}while(getche()!='n');
}
/*	O/P:-
		Enter no. of non terminals:2
			Enter non_terminal 1:S
			Enter non_terminal 2:E

		For production S:
			Enter no. of productions:3

			Enter production 1:iEtS
			Enter production 2:iEtSeS
			Enter production 3:a

		For production E:
			Enter no. of productions:1

			Enter production 1:b

		Enter start symbol:S
		Productions are:
							S----->\iEtS\iEtSeS\a
							E----->\b
		Enter the input string to be accepted:ibtibtaea
		String accepted.
		Do u enter another string(y/n):-y
		Productions are:
							S----->\iEtS\iEtSeS\a
							E----->\b
		Enter the input string to be accepted:ibtaea
		String accepted.
		Do u enter another string(y/n):-y
		Productions are:
							S----->\iEtS\iEtSeS\a
							E----->\b
		Enter the input string to be accepted:ibt
		String not accepted.
		Do u enter another string(y/n):-n
*/
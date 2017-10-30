//checking an input string if it is accepted by DFA(taking string DFA and string as I/P)
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 3-3-06	8:24
#include"stdio.h"
#include"conio.h"
#include"process.h"
struct state
{	char s_name[10];	//name of the state
	char t_name[10];	//names of the transition characters
	char traversed;		//whether the state is traversed or not
	struct state *child[10];	//links of the children
};
void main(void)
{   char name[20][10],temp[10],st_name[10],end_name[10],accepted='y',st_index;
	int i,j,k,ns,nt;
	struct state s[20],*t;
	clrscr();
	printf("\nEnter no. of states:");
	scanf("%d",&ns);
	if(isascii(ns)==0)
	{	printf("ERROR");
		exit(0);
	}
	printf("Enter no. of transitions from each state:");
	scanf("%d",&nt);
	if(isascii(nt)==0)
	{	printf("ERROR");
		exit(0);
	}
	for(i=0;i<ns;i++)		//state names can be strings
	{   printf("Enter the name of the state :",i+1);
		scanf("%s",s[i].s_name);
		s[i].traversed='n';
	}
	for(j=0;j<nt;j++)		//transition names can be single characters
	{   flushall();
		printf("Enter the transition name %3d:",j+1);
		scanf("%c",&s[0].t_name[j]);
	}
	for(i=0;i<ns;i++)
	{   printf("\nFor state %s::\n",s[i].s_name);
		for(j=0;j<nt;j++)
		{	s[i].t_name[j]=s[0].t_name[j];
			printf("Enter the next from state %s on %c:",s[i].s_name,s[i].t_name[j]);
			scanf("%s",temp);
			for(k=0;k<ns;k++)
			{	if(strcmp(temp,s[k].s_name)==0)
				{	s[i].child[j]=&s[k];
					break;
				}
			}
		}
	}
	printf("Enter the START state:");
	scanf("%s",st_name);
	printf("Enter the FINAL state:");
	scanf("%s",end_name);
	for(k=0;k<ns;k++)
		if(strcmp(st_name,s[k].s_name)==0)
			break;
	st_index=k;
	do
	{   {	/*to print the Transition table*/
			clrscr();
			printf("%20s\n%20s\n\n\t","TRANSITION TABLE\n","****************");
			for(i=0;i<nt;i++)
				printf(" %3c",s[0].t_name[i]);
			printf(" \n\t");
			for(i=0;i<nt;i++)
				printf("%5s","-----");
			printf("\n");
			for(i=0;i<ns;i++)
			{	printf("%5s|",s[i].s_name);
				for(j=0;j<nt;j++)
					printf("%5s",s[i].child[j]->s_name);
				printf("\n");
			}
		}
		//taking input string
		printf("\nEnter the input string to be checked:");
		scanf("%s",temp);
		t=&s[st_index];
		j=0;
		printf("\nstate:: %10s",t->s_name);
		for(i=0;i<nt;i++)
		{   if(temp[j]!='\0')
			{   if(t->t_name[i]==temp[j])
				{	j++;
					t=t->child[i];
					printf("--->%s",t->s_name);
					i=-1;
				}
			}
			else if(temp[j]=='\0')
			{	if(strcmp(t->s_name,end_name)==0)
				{	printf("\nString accepted");
					break;
				}
				else
				{	accepted='n';
					break;
				}
			}
		}
		if(i==nt)
			accepted='n';
		if(accepted=='n')
		{	printf("\nString not accepted");
			accepted='y';
		}
		printf("\nDo u enter another string(y/n):");
		flushall();
	}while(tolower(getche())!='n');
	getch();
}
/*
O/P:
Enter no. of states:4
Enter no. of transitions from each state:2
Enter the name of the state :p0
Enter the name of the state :p1
Enter the name of the state :p2
Enter the name of the state :p3
Enter the transition name   1:0
Enter the transition name   2:1

For state p0::
Enter the next from state p0 on 0:p1
Enter the next from state p0 on 1:p2

For state p1::
Enter the next from state p1 on 0:p1
Enter the next from state p1 on 1:p0

For state p2::
Enter the next from state p2 on 0:p1
Enter the next from state p2 on 1:p3

For state p3::
Enter the next from state p3 on 0:p2
Enter the next from state p3 on 1:p0

Enter the START state:p0
Enter the FINAL state:p3

     TRANSITION TABLE
     ****************

	 |  0   1
	-|----------
   p0|   p1   p2
   p1|   p1   p0
   p2|   p1   p3
   p3|   p2   p0

Enter the input string to be checked:
state::         p0--->p1--->p0--->p2--->p1--->p1--->p1--->p0--->p2--->p3--->p2--->p3
String accepted
Do u enter another string(y/n):n
*/
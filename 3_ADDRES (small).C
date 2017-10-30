//			3-address code generator
//Author : Ravi Kalla
//Email : ravikalla@ravikalla.in
//Created on 4-4-06 01:31
char s[20],a,s2[3],b[40][5],i,k,c,d,e=0,s1[40]="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
z()
{for(strcpy(s2,"*/"),i=c+1;(i<d)||((strcmp(s2,"*/")==0)&&((((int)(strcpy(s2,"+-"))*(i=c+1)))||1));((s[i]==s2[0]||s[i]==s2[1])&&((int)(strcpy(b[e],s+i-1))*(int)(strcpy(s+i,s+i+2))*(b[e][3]='\0')*(printf("\n%c:=%s",s1[e],b[e]))*(s[i-1]=s1[e++])*(d-=2)*(i=c))),i++);
}
void main()
{for(scanf("%s",s),a=s[0],strcpy(s,s+2),k=0;(((s[k]!='\0')||(c=0)*(d=strlen(s))*(z())==1))||((printf("\n%c:=%s",a,s))==-1);(((s[k]=='(')&&(c=k)))||((s[k]==')')&&((d=k)&&(z())*(int)(strcpy(s+d,s+d+1))*(int)(strcpy(s+c,s+c+1))*(k=-1))),k++);
}
/*O/P:-
		a=(b+c*(d/e+f*g)-h)

		A:=d/e
		B:=f*g
		C:=A+B
		D:=c*C
		E:=b+D
		F:=E-h
		a:=F
*/
#include <stdio.h>
#include <stdlib.h>
char buffer[2000] ; char c;int flag=0 ; int index=0 ;
int nline = 1 ; int line = 1 ;
char *keys[]={"let","match", "member" ,"module","mutable","namespace","new", "null" ,"of" ,"open" ,"or"
 ,"override", "private", "public", "rec", "return" ,"sig" ,"static", "struct" ,"then" ,"to"
 ,"true" ,"try" ,"type", "upcast" ,"use", "val", "void" ,"when" ,"while" ,"with" ,"yield","else","if",
 "abstract" ,"and", "as" ,"assert" ,"base" ,"begin" ,"class" ,"default", "delegate" ,"do",
 "downcast" ,"downto" ,"elif" ,"else", "end" ,"exception" ,"extern", "false" ,"finally",
 "fun" ,"function" ,"global","if" ,"in", "inherit", "inline" ,"interface", "internal"  } ;
void checkEndLine(){
if(nline>line){printf("$$\n");line=nline;}
}

void deleteComments(){
if(c=='('){
c=getchar();
if(c=='*'){
    while(1){
    while((c=getchar())!='*'){}
    if((c=getchar())==')'){break;}
    }
    c=getchar() ;
}
else{checkEndLine(); printf("( \n",nline);}
}
else if(c=='/'){
    c=getchar() ; //printf("CCCCCC %c\n",c ) ;
    if(c=='/'){
        while(c!='\n'){c=getchar();}
    }
    else{
        checkEndLine() ;;// printf("/\n") ;
    }
}
}

void isDelimiter(){
if(c==' '){c=getchar() ;}
else if(c=='('||c==')'||c==';'||c==':'){
   if(c!='('){ checkEndLine() ;printf("%c\n",c) ;c=getchar() ;}
   else{
    c=getchar();
if(c=='*'){
    while(1){
    while((c=getchar())!='*'){}
    if((c=getchar())==')'){break;}
    }
    c=getchar() ;
}
else{ checkEndLine() ;printf("(\n");}
   }
}
else if(c=='['){
   c=getchar() ;
   if(c=='|'){ checkEndLine() ; printf("[|\n");c=getchar() ;}
   else{ checkEndLine() ; printf("[\n");}
}
else if(c=='|'){
c=getchar() ;
if(c==']'){
  checkEndLine() ;   printf("|]\n");
}
else{
     checkEndLine() ; printf("invalid token encountered\n") ;
}
}

}

void isString(){
if(c=='"'){
        int state = 1 ; char g[2000];int tmp=0;
while(1){
switch(state){
case 1:c = getchar();g[tmp++]=c;
if(c=='"'){state=3;}
else if(c=='\n'){state=4;}
break;

case 3: g[--tmp]='\0' ;c=getchar() ;  checkEndLine() ;printf("%s\n",g) ;return ;

case 4:g[--tmp]='\0' ; c=getchar() ;  checkEndLine() ;printf("%s\n",g) ;return ;

        }
      }
   }
}

void isIdentifier(){
    char s[200]; int in=0;
if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_'){ s[in++]=c;
   int state = 1 ;
while(1){
switch(state){
case 1: c=getchar() ;s[in++]=c;
if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_'||(c>='0'&&c<='9')||(c=='\'')){state=1;}
else{state=2;}
break;
case 2:
s[--in]='\0' ;
if(checkKey(s)){ checkEndLine() ; printf("%s\n",s);return; }
else{ checkEndLine() ; printf("%s\n",s);return ;}
break;
        }
      }
    }
}

int checkKey(char *s){ int i = 0;
for( i=0;i<50;i++){
    if(!strcmp(s,keys[i])){
       return 1 ;
    }
}
return 0 ;
}
void checkD(char *s){ int dotcnt = 0 ; s[1]=c ;int in=2;
while((c>='0'&&c<='9')||c=='.'){
  if(c=='.'){dotcnt++;}  s[in++] = c = getchar() ;
}
s[--in]='\0' ;
if(dotcnt==1){ checkEndLine() ; printf("%s\n",s) ;}
else if(dotcnt==0){ checkEndLine() ; printf("%s\n",s) ;}
else{printf("line no. %d ERROR more than 1 decimals not possible\n",nline) ;}
return ;
}
void isOperator(){
int state=0 ;char s[200]; int in=0;
while(1){
switch(state){
case 0:
if(c=='+'||c=='-'){state=1 ;s[in++]=c ;c=getchar() ;}
else if(c>='0'&&c<='9'){ s[in++]=c ;c=getchar() ; checkD(s);}
else if(c=='%'||c=='/'){
        checkEndLine() ; printf("%c\n",c) ;  return ;
}// ||c=='/' case to be included
else if(c=='>'||c=='<'||c=='='){state=2;s[in++]=c ;c=getchar() ; }
else if(c=='&'||c=='|'||c=='*'){state = 3 ;s[in++]=c ; c=getchar() ;}
else{return ;}
break;
case 1:
if((c>='0'&&c<='9')){checkD(s);return ;}
else { checkEndLine() ;printf("%c\n",s[0]) ;return ;}
break;
case 2:
if(c=='='){s[in++]=c ; s[in]='\0' ; checkEndLine() ; printf("%s\n",s) ;return ;}
else{ checkEndLine() ;printf("%c\n",s[0]);return ;}
break;
case 3:
if(c==s[0]){
    checkEndLine() ; printf("%c%c\n",c,c) ;return ;
}
else if(s[0]=='*'){ checkEndLine() ;printf("*\n");return ; }
else{printf("line no. %d ERROR not a valid operator\n",nline);return;}
break;
  }
}
}



void lexical(){ c=getchar();
    while(c!=EOF){
    if(c=='\n'){nline++;c=getchar();}
    if(c==EOF){break;}
        deleteComments() ;
        isDelimiter() ;
        isString() ;
        isIdentifier() ;
        isOperator() ;
    }
}

int main()
{
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
 //FILE *fp = fopen("input.txt","r") ;
  c = 21 ;

 lexical() ;


}


// if(nline>line){printf("$$\n");line=nline;}

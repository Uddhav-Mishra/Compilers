#include <stdio.h>
#include <stdlib.h>
char buffer[2000] ; char c;int flag=0 ; int index=0 ;
int nline = 1 ;
char *keys[]={"let","match", "member" ,"module","mutable","namespace","new", "null" ,"of" ,"open" ,"or"
 ,"override", "private", "public", "rec", "return" ,"sig" ,"static", "struct" ,"then" ,"to"
 ,"true" ,"try" ,"type", "upcast" ,"use", "val", "void" ,"when" ,"while" ,"with" ,"yield","else","if",
 "abstract" ,"and", "as" ,"assert" ,"base" ,"begin" ,"class" ,"default", "delegate" ,"do",
 "downcast" ,"downto" ,"elif" ,"else", "end" ,"exception" ,"extern", "false" ,"finally",
 "fun" ,"function" ,"global","if" ,"in", "inherit", "inline" ,"interface", "internal"  } ;
// to delete 2 types of comments // and /**/
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
else{ printf("line no. %d token ( \n",nline);}
}
else if(c=='/'){
    c=getchar() ; //printf("CCCCCC %c\n",c ) ;
    if(c=='/'){
        while(c!='\n'){c=getchar();}
    }
    else{
         printf("line no.%d operator /",nline) ;
    }
}
}

void isDelimiter(){
if(c==' '){c=getchar() ;}
else if(c=='('||c==')'||c==';'||c==':'){
   if(c!='('){ printf("line no. %d token %c \n",nline,c) ;c=getchar() ;}
   else{
    c=getchar();
if(c=='*'){
    while(1){
    while((c=getchar())!='*'){}
    if((c=getchar())==')'){break;}
    }
    c=getchar() ;
}
else{printf("line no. %d delimiter ( \n",nline);}
   }
}
else if(c=='['){
   c=getchar() ;
   if(c=='|'){printf("line no. %d token [|\n",nline);c=getchar() ;}
   else{printf("line no. %d token [\n",nline);}
}
else if(c=='|'){
c=getchar() ;
if(c==']'){
    printf("line no. %d token |]\n",nline);
}
else{

}
}

}

void isString(){
if(c=='"'){
        int state = 1 ; char g[2000];int tmp=0;
while(1){
switch(state){
case 1:c = getchar();g[tmp++]=c;
if(c=='\\'){state=2;}
else if(c=='"'){state=3;}
break;
case 2:c=getchar() ;g[tmp++]=c;
state=1;break;
case 3: g[--tmp]='\0' ;c=getchar() ; printf("line no. %d String literal %s\n",nline,g) ;return ;
}
}
}
}

void isIdentifier(){ char s[200]; int in=0;
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
if(checkKey(s)){printf("line no. %d keyword %s\n",nline,s);return; }
else{printf("line no. %d identifier %s\n",nline,s);return ;}
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

void isOperator(){
int state=0 ;char s[200]; int in=0;
while(1){
switch(state){
case 0:
if(c=='+'||c=='-'){state=1 ;s[in++]=c ;c=getchar() ;}
else if(c>='0'&&c<='9'){ s[in++]=c ;c=getchar() ;checkD(s);}
else if(c=='%'){printf("line no. %d operator %c\n",nline,c) ;  return ;}// ||c=='/' case to be included
else if(c=='>'||c=='<'||c=='='){state=2;s[in++]=c ;c=getchar() ; }
else if(c=='&'||c=='|'||c=='*'){state = 3 ;s[in++]=c ; c=getchar() ;}
else{return ;}
break;
case 1:
if((c>='0'&&c<='9')){checkD(s);return ;}
else {printf("line no. %d operator %c\n",nline,s[0]) ;return ;}
break;
case 2:
if(c=='='){s[in++]=c ; s[in]='\0' ; printf("line no. %d operator %s\n",nline,s) ;return ;}
else{printf("line no. %d operaor %c\n",nline,s[0]);return ;}
break;
case 3:
if(c==s[0]){
    printf("line no. %d operator %c%c\n",nline,c,c) ;return ;
}
else if(s[0]=='*'){printf("line no. %d operator *\n",nline);return ; }
else{printf("line no. %d ERROR not a valid operator\n",nline);return;}
break;
  }
}
}

void checkD(char *s){ int dotcnt = 0 ; s[1]=c ;int in=2;
while((c>='0'&&c<='9')||c=='.'){
  if(c=='.'){dotcnt++;}  s[in++] = c = getchar() ;
}
s[--in]='\0' ;
if(dotcnt<1){printf("line no. %d number%s\n",nline,s) ;}
else if(dotcnt==1){printf("line no. %d float%s\n",nline,s) ;}
else{printf("line no. ERROR more than 1 decimals not possible\n",nline) ;}
return ;
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

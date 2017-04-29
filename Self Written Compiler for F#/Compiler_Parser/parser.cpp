#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
FILE *fp;
int f = 0;
char lookahead[200];
int cn = 0;
int line = 1;
void statements();
void Ydash();
char a[100][100];
int id = 0;
void printst()
{
    for(int i = 0;i< id;i++)
    {
        cout<<a[i]<<endl;
    }
}
void errorrecovery()
{
    while(strcmp(lookahead,"$$") != 0 && !feof(fp))
                  {
                                fscanf(fp,"%s",lookahead);

                  }

          line++;
          if(!feof(fp))
          fscanf(fp,"%s",lookahead);
          f = 1;

}
int checkid(char a[100])
{
    if(feof(fp))
        {
            f = 1;
            return 0;
        }



 char *keys[]={"let","match", "member" ,"module","mutable","namespace","new", "null" ,"of" ,"open" ,"or"
 ,"override", "private", "public", "rec", "return" ,"sig" ,"static", "struct" ,"then" ,"to"
 ,"true" ,"try" ,"type", "upcast" ,"use", "val", "void" ,"when" ,"while" ,"with" ,"yield","else","if",
 "abstract" ,"and", "as" ,"assert" ,"base" ,"begin" ,"class" ,"default", "delegate" ,"do",
 "downcast" ,"downto" ,"elif" ,"else", "end" ,"exception" ,"extern", "false" ,"finally",
 "fun" ,"function" ,"global","if" ,"in", "inherit", "inline" ,"interface", "internal"  } ;
    for(int i = 0;i< strlen(*keys);i++)
    {
        if(strcmp(a,keys[i]) == 0)
        {
            printf("Error %s %s",a,keys[i]);
            //cout<<lookahead<<endl;
            errorrecovery();

                return 0;
        }

    }

//cout<<"nmnmnn"<<endl;
fscanf(fp,"%s",lookahead);
if(strcmp(lookahead,"$$") == 0 && !feof(fp))
    {
       fscanf(fp,"%s",lookahead);
        line++;
    }
           return 1;
}
void match(char a[100])
{
    if(feof(fp))
        {
            f  =1;
            return;
        }
    if(strcmp(lookahead,a) == 0)
    {
        fscanf(fp,"%s",lookahead);
    }
    else
    {
                printf("error %s %s\n",a,lookahead);
                 errorrecovery();
                 return;


    }
    if(strcmp(lookahead,"$$") == 0 && !feof(fp))
    {
       fscanf(fp,"%s",lookahead);
        line++;
    }
  //  cout<<"lookahead "<<lookahead<<endl;

}
void params()
{
    strcpy(a[id++],"params");
    if(feof(fp))
        {
            id--;
            return;
        }
    if(strcmp(lookahead,":") == 0)
        {
            id--;
            return;
        }
    checkid(lookahead);
    if(f)
        {
            id--;
            return;
        }
    params();
    id--;
}
void type()
{
    strcpy(a[id++],"type");
    //a[id++] = "type";
    if(strcmp(lookahead,"int") == 0)
    {
        match("int");
    }
    else if(strcmp(lookahead,"float") == 0)
    {
        match("float");
    }
    else if(strcmp(lookahead,"char") == 0)
    {
        match("char");
    }
    else
    {
        cout<<"Error in return type line "<<line<<endl;
        errorrecovery();
    }
    if(f)
        {
            id--;
            return;
        }
        id--;
}
void expression()
{
    strcpy(a[id++],"expression");
    //a[id++] = "expression";
    checkid("lookahead");
    if(f)
        {
            id--;
            return;
        }
    Ydash();
    id--;
}
int checkrelop(char a[100])
{
  char *b[] = {"<","<=",">",">=","==","<>"};
  for(int i = 0;i< strlen(*b);i++)
  {
  	if(strcmp(b[i],a) == 0)
      return 1;

  }
  return 0;

}


int checkboolop(char a[100]){
  if(strcmp(a,"&&")==0||strcmp(a,"||")==0||strcmp(a,"not")==0){
    return 1 ;
  }
  else{
    return 0 ;
  }

}



void Ydash()
{
    strcpy(a[id++],"YDASH");
     if(strcmp(lookahead,"=") == 0||strcmp(lookahead,"-") == 0||strcmp(lookahead,"+") == 0||strcmp(lookahead,"*") == 0)
    {
        match(lookahead);
        if(f)
            {
                id--;
                return;
            }
        expression();
    }
    else if(checkrelop(lookahead))
    {
        match(lookahead) ;
        if(f)
            {
                id--;
                return;
            }
      expression() ;
    }
    else if(checkboolop(lookahead)){
    match(lookahead) ;
    if(f)
            {
                id--;
                return;
            }
     expression() ;
    }
    else if(checkid(lookahead)){
    match(lookahead);
    if(f)
            {
                id--;
                return;
            }
     expression() ;
    }
            else{
                    errorrecovery();
      //error
            }
        id--;

}
void X()
{
    strcpy(a[id++],"X()");
    if(strcmp(lookahead,"=") == 0)
    {
       Ydash();
    }
    else{
        params();
        if(f)
            {
                id--;
                return;
            }
       // cout<<"after param"<<endl;
        //cout<<lookahead<<endl;
        match(":");
        if(f)
            {
                id--;
                return;
            }
           //     cout<<":"<<endl;

        type();
        //cout<<"type"<<endl;
        if(f)
            {
                id--;
                return;
            }
        match("=");
        if(f)
            {
                id--;
                return;
            }
        //cout<<"----"<<endl;
        statements();

    }
    id--;
}
void decl()
{
    strcpy(a[id++],"decl()");
    match("let");

    if(f)
            {
                id--;
                return;
            }
    checkid(lookahead);
    if(f)
        {
            id--;
            return;
        }
   // cout<<"after id"<<endl;
    //cout<<lookahead<<endl;
    X();
    id--;
}
void ifcon()
{
    strcpy(a[id++],"ifcon");
    match("if");
    if(f)
            {
                id--;
                return;
            }
    match("(");
    if(f)
            {
                id--;
                return;
            }
    expression();
    match(")");
    if(f)
            {
                id--;
                return;
            }
    match("then");
    if(f)
            {
                id--;
                return;
            }
    statements();
    id--;
}
void loops()
{
    strcpy(a[id++],"loop");

	match("while");
	if(f)
            {
                id--;
                return;
            }
  match("(");
  if(f)
            {
                id--;
                return;
            }
  expression();
  if(f)
            {
                id--;
                return;
            }
  match(")");
  if(f)
            {
                id--;
                return;
            }
  match("do");
  if(f)
            {
                id--;
                return;
            }
  statements();
id--;



}

void statement()
{
    if(feof(fp))
        return;
    strcpy(a[id++],"statement");
            printst();

    if(strcmp("let",lookahead) == 0)
    {
       // cout<<"dec"<<endl;
        decl();

    }
    else if(strcmp("while",lookahead) == 0)
    {
        loops();
    }
    else if(strcmp("if",lookahead) == 0)
    {
        cout<<"if"<<endl;
        ifcon();
    }
    id--;


}
void statements()
{
    if(feof(fp))
        return;
    strcpy(a[id++],"statements");
    statement();
    f = 0;
    statements();
    id--;
}
void program()
{
    strcpy(a[id++],"programs");
       statements();
    id--;
}

int main()
{
    fp = fopen("tokens.txt","r");
    fscanf(fp,"%s",lookahead);
   // cout<<lookahead<<endl;
    if(strcmp(lookahead,"$$") == 0)
    {
       fscanf(fp,"%s",lookahead);

        line++;
    }
    program();
		if(!feof(fp))
       cout<<"not all tokens matched"<<endl;

    fclose(fp);


}

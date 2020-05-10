#define al  20 //al为识别符的最大长度
#define nmax 14
#define worldsize 10000
typedef struct node{
	int count;
	char symbol[200];
	char value[200];
	//struct node *next;
} Node;
Node world[worldsize];
int tempp = 0;
int line1=1,line2=1;
char c = '0';
char va[20] = {0};
char sym[20] = {0};
char sm[20] = {0};
char va2[20] = {0};
char va3[20] = {0};
Node *r, *second, *third;
void intialize(char a[]);
void IsIDEN(FILE *fp);
void IsDidit(FILE *fp);
void IsOP(FILE *fp);
void Out(FILE *out);
void IsIDEN(FILE *fp){
		int k =0 ;
		do {
			if(k<al){
				va[k] = c;
				k = k + 1;
			}
			else
				error(3);
			c = fgetc(fp);
			}
			while(((c>='a' && c<= 'z') || (c>='A' && c<='Z')||(c>='0' && c<='9')||(c=='_')));
			if(strcmp(va,"const")==0)
				strcpy_s(sym,"CONST");
			else if(strcmp(va,"int")==0)
				strcpy_s(sym,"INT");
			else if(strcmp(va,"char")==0)
				strcpy_s(sym,"CHAR");
			else if(strcmp(va,"void")==0)
				strcpy_s(sym,"VOID");
			else if(strcmp(va,"mian")==0)
				strcpy_s(sym,"MAIN");
			else if(strcmp(va,"if")==0)
				strcpy_s(sym,"IF");
			else if(strcmp(va,"else")==0)
				strcpy_s(sym,"ELSE");
			else if(strcmp(va,"for")==0)
				strcpy_s(sym,"FOR");
			else if(strcmp(va,"switch")==0)
				strcpy_s(sym,"SWITCH");
			else if(strcmp(va,"case")==0)
				strcpy_s(sym,"CASE");
			else if(strcmp(va,"default")==0)
				strcpy_s(sym,"DEFAULT");
			else if(strcmp(va,"scanf")==0)
				strcpy_s(sym,"SCANF");
			else if(strcmp(va,"printf")==0)
				strcpy_s(sym,"PRINTF");
			else if(strcmp(va,"return")==0)
				strcpy_s(sym,"RETURN");
			else
				strcpy_s(sym,"IDEN");
}
void IsDidit(FILE *fp){
		int k =0 ;
		if (c>='0' && c<='9'){
			int k =0 ;
			do {
				va [k] = c;
				k  = k +1;
				if (k > nmax){
					error(4);
				}
				c = fgetc(fp);
			}  
			while((c>='0' && c<='9'));
				strcpy_s(sym,"NUM");
		}
}
void IsOP(FILE *fp){
		if (c == '!'){
			c = fgetc(fp);
			if (c == '='){
				va[0] = '!';
				va[1] = '=';
				c = fgetc(fp);
				strcpy_s(sym,"NEQ");
			}
			else{
				va[0] = '!';
				strcpy_s(sym,"EXCLA");
			}
		}
		else if(c == '<'){
			c = fgetc(fp);
			if (c == '='){
				va[0] = '<';
				va[1] = '=';
				c = fgetc(fp);
				strcpy_s(sym,"LE");
			}
			else {
				va[0] = '<';
				strcpy_s(sym,"LESS");
			}
		}
		else if (c == '>'){
			c = fgetc(fp);
			if(c == '='){
				va[0] = '>';
				va[1] = '=';
				c = fgetc(fp);
				strcpy_s(sym,"GE");
			}
			else {
				va[0] = '>';
				strcpy_s(sym,"GA");
			}
		}
		else if (c == '='){
			c = fgetc(fp);
			if(c == '='){
				va[0] = '=';
				va[1] = '=';
				c = fgetc(fp);
				strcpy_s(sym,"ASSIGN");
			}
			else {
				va[0] = '=';
				strcpy_s(sym,"EQ");
			}
		}
		else if (c == ';'){
			va[0]=';';
			c = fgetc(fp);
			strcpy_s(sym,"SEM");
		}
		else if (c == ':'){
			va[0]=':';
			c = fgetc(fp);
			strcpy_s(sym,"COLON");
		}
		else if (c == ','){
			va[0]=',';
			c = fgetc(fp);
			strcpy_s(sym,"COMMA");
		}
		else if (c == '('){
			va[0]='(';
			c = fgetc(fp);
			strcpy_s(sym,"LSP");
		}
		else if (c == ')'){
			va[0]=')';
			c = fgetc(fp);
			strcpy_s(sym,"RSP");
		}
		else if (c == '['){
			va[0]='[';
			c = fgetc(fp);
			strcpy_s(sym,"LMP");
		}
		else if (c == ']'){
			va[0]=']';
			c = fgetc(fp);
			strcpy_s(sym,"RMP");
		}

		else if (c == '{'){
			va[0]='{';
			c = fgetc(fp);
			strcpy_s(sym,"LBP");
		}
		else if (c == '}'){
			va[0]='}';
			c = fgetc(fp);
			strcpy_s(sym,"RBP");
		}
		else if (c == '+'){
			va[0]='+';
			c = fgetc(fp);
			strcpy_s(sym,"PLUS");
		}
		else if (c == '-'){
			va[0]='-';
			c = fgetc(fp);
			strcpy_s(sym,"SUB");
		}
		else if (c == '*'){
			va[0]='*';
			c = fgetc(fp);
			strcpy_s(sym,"MUL");
		}
		else if (c == '/'){
			va[0]='/';
			c = fgetc(fp);
			strcpy_s(sym,"DIV");
		}
		else if (c == '\''){
			va[0]='\'';
			c = fgetc(fp);
			strcpy_s(sym,"QUO");
		}
		else if (c == '"'){
			va[0]='"';
			c = fgetc(fp);
			strcpy_s(sym,"DQUO");
		}
		else if (c == ' '){
			va[0]=' ';
			c = fgetc(fp);
			strcpy_s(sym,"SPACE");
		}
		else if (c == '#'){
			va[0]='#';
			c = fgetc(fp);
			strcpy_s(sym,"###");
		}
		else if (c == '$'){
			va[0]='&';
			c = fgetc(fp);
			strcpy_s(sym,"$$$");
		}
		else if (c == '%'){
			va[0]='%';
			c = fgetc(fp);
			strcpy_s(sym,"%%%");
		}		
		else if (c == '&'){
			va[0]='&';
			c = fgetc(fp);
			strcpy_s(sym,"");
		}	
		else if (c == '?'){
			va[0]='?';
			c = fgetc(fp);
			strcpy_s(sym,"???");
		}
		else if (c == '@'){
			va[0]='@';
			c = fgetc(fp);
			strcpy_s(sym,"@@@");
		}
		else if (c == '\\'){
			va[0]='\\';
			c = fgetc(fp);
			strcpy_s(sym,"BACK");
		}
		else if (c == '^'){
			va[0]='^';
			c = fgetc(fp);
			strcpy_s(sym,"^^^");
		}		
		else if (c == '_'){
			va[0]='_';
			c = fgetc(fp);
			strcpy_s(sym,"___");
		}
		else if (c == '|'){
			va[0]='|';
			c = fgetc(fp);
			strcpy_s(sym,"|||");
		}
		else if (c == '~'){  
			va[0]='~';
			c = fgetc(fp);
			strcpy_s(sym,"~~~");
		}
		else if (c == '.'){  
			va[0]='.';
			c = fgetc(fp);
			strcpy_s(sym,".....");
		}
		else if (c == '`'){  
			va[0]='`';
			c = fgetc(fp);
			strcpy_s(sym,"`````````");
		}
		else 
			error(5);
}
void Out(FILE *out){
	int i =0;
	while(i< tempp && strcmp(world[i].symbol,"0") != 0){
		fprintf(out,"%3d   %10s %10s \n",world[i].count,world[i].symbol,world[i].value);
		i++;
	}
}
void intialize(char a[]){
	int i = 0;
	for (i = 0; i<20; i++){
		a[i]=0;
	}
}
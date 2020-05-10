#define size 20
#define length 5000
typedef struct code{
	char numb1[200];
	char numb2[200];
	char numb3[200];
	char numb4[200];
	char numb5[200];
	char numb6[200];
	int chara1;//立即数
	int chara2;//特性标志
}CODE;
typedef struct opn{//用来存放操作数
	char num[20];//操作数
	int character;//操作数特性
}OPN;
void midcode(char *op,char *operand1,char *operand2,char *result);

CODE mcode[length];
OPN opnum[500];
FILE *Midcode;
typedef char arr[200];
arr opstack[500],resul[500],Label[500];
arr string[500];//用来存字符串
int strnum = 1;//字符串数组位置
int element = 0;
int userequire = 0;//如果是for调用条件语句的话置1，if调用置0
char requirelabel[20];//用来存放条件语句的label
int local = 0;
char endfor[20];//用来存放for结束时的标签
//char endif[20];//用来存放if结束时的标签
char op[20];
char operand1[20];
char operand2[20];
char operand[20];
char result[20];
char funname[20];//用来存函数名字
char opnumb[20],op1[20],opnumb2[20];//用来存条件的三个元素
int operan;
int res = 1;
int ress = 1;
int label = 1;
int charact = 0;//字符调用标识符，为0表示由常量部分调用
int top1 = 1;//操作数顶；
int top2 = 1;
int opvalue;
void pushop(char *op){ //操作符进栈
	strcpy(opstack[top2],op);
	top2 ++;
}
void pushopnum(char *op,int m){ //操作数进栈
	if(strcmp(op,"[")!=0){
		midcode("sw",op,"0","$a2");
		midcode("addi","$a2","4","$a2");
	}
	strcpy(opnum[top1].num,op);
	opnum[top1].character = m;
	top1 ++;
}
void outopstack(){ 
	if(top2>0){
		strcpy(op,opstack[top2-1]);
		strcpy(opstack[top2-1],"000");//复原
		top2--;
	}
}
void outopnum(){
	if(top1>0){
		if(strcmp(operand,"[")!=0){
			midcode("addi","$a2","-4","$a2");
			midcode("lw",resul[15],"0","$a2");
			strcpy(operand,resul[15]);
		}
		else
			strcpy(operand,opnum[top1-1].num);
		strcpy(opnum[top1-1].num,"000");//复原
		top1--;
	}
}
void midcode(char *op,char *operand1,char *operand2,char *result){
	strcpy(mcode[local].numb1,op);
	strcpy(mcode[local].numb2,operand1);
	strcpy(mcode[local].numb3,operand2);
	strcpy(mcode[local].numb4,result);
	mcode[local].chara1 = opnum[top1].character;
	mcode[local].chara2 = opnum[top1+1].character;
	local++;
	fprintf(Midcode,"    %s,%s,%s,%s\n",op,operand1,operand2,result);
	//if(strcmp(operand1,"const")==0 || strcmp(operand1,"char")==0)
		//printf("%s,%s,%s,%d\n",op,operand1,operand2,result);
	//else 
		//printf("    %s,%s,%s,%s\n",op,operand1,operand2,result);
}
void midcode(char *op,char *operand1,char *operand2,char *operand3,char *operand4,char *result){
	strcpy(mcode[local].numb1,op);
	strcpy(mcode[local].numb2,operand1);
	strcpy(mcode[local].numb3,operand2);
	strcpy(mcode[local].numb4,operand3);
	strcpy(mcode[local].numb5,operand4);
	strcpy(mcode[local].numb6,result);
	local++;
	if(strcmp(result,"]")==0){
		fprintf(Midcode,"    %s,%s,%s%s%s%s\n",op,operand1,operand2,operand3,operand4,result);
		//printf("      %s,%s,%s%s%s%s\n",op,operand1,operand2,operand3,operand4,result);
	}
	else{
		fprintf(Midcode,"    %s,%s%s%s%s,%s\n",op,operand1,operand2,operand3,operand4,result);
		//printf("    %s,%s%s%s%s,%s\n",op,operand1,operand2,operand3,operand4,result);
	}
}
void midcode(char *operand1,char *operand2){
	strcpy(mcode[local].numb1,operand1);
	strcpy(mcode[local].numb2,operand2);
	local++;
	if(strcmp(operand2,":")!=0){
		fprintf(Midcode,"    %s %s\n",operand1,operand2);
		//printf("    %s %s\n",operand1,operand2);
	}
	else{
		fprintf(Midcode,"%s %s\n",operand1,operand2);
		//printf("%s %s\n",operand1,operand2);
	}
}
void midcode(char *operand1,char *operand2,char *operand3){
	strcpy(mcode[local].numb1,operand1);
	strcpy(mcode[local].numb2,operand2);
	strcpy(mcode[local].numb3,operand3);
	local++;
	fprintf(Midcode,"    %s %s,%s \n",operand1,operand2,operand3);
}

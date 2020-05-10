#include "SymTable.h"
#include "MidCode.h"
#include "Object.h"
void OpPlus();
void OpMul();
void OpRelation();
void Word (char c);
void Digit(int m);
void Not0(int m);
void Character();
void Ascii();
void Procedure();
void ConstState();
void ConstDefine();
void UnsignedInt();
void Integer();
void Iden();
void HeadState();
void VarState();
void VarDefine();
void Const();
void KindSym();
void ReFunction();
void NoReFunction();
void ComState();
void Parameter();
void ParaList();
void Main();
void Expres();
void Term ();
void Factor();
void Sentence();
void AssignState();
void RequireState();
void Require();
void ForState();
void Step();
void Switch();
void SwitchList(char switchvalu[20],char switchlabel[20]);
void SwitchSon(char switchvalu[20],char switchlabel[20]);
void Default();
void UseFunction();
void WortnParaList();
void StateList();
void ScanfState();
void PrintfState();
void ReturnState();
void getsym();

FILE *OutSyntax;
int readworld = 0;
void OpPlus(){        //<加法运算符> ::= +|-
	if((strcmp(va,"+")!=0) && (strcmp(va,"-")!=0))
		error(23);
	else
		getsym();
}
void OpMul(){         //<乘法运算符> ::= *|/
	if((strcmp(va,"*")!=0) && (strcmp(va,"/")!=0))
		error(24);
	else
		getsym();
}
void OpRelation(){   //<关系运算符> ::= <|<=|>|>=|!=|==
	if(strcmp(va,"<") !=0 && strcmp(va,"<=") !=0 && strcmp(va,">") !=0 && strcmp(va,">=") !=0 && strcmp(va,"!=") !=0 && strcmp(va,"==") !=0)
		error(25);
	else
		getsym();
}
void Word (char c){       //＜字母＞::= ＿｜a｜...｜z｜A｜...｜Z     
	if( !((c>='a'&&c<='z') ||(c>='A'&&c<='Z') ||(c=='_') ))
		error(26);
}
void Digit(int m){       //<数字> ::= 0|非零数字
	if(m < 0 || m > 9)
		error(27);
}
void Not0(int m){       //非零数字
	if(m < 1 || m > 9)
		error(28);
}
void Character(){   //＜字符＞::='＜加法运算符＞'｜'＜乘法运算符＞'｜'＜字母＞'｜'＜数字＞'
	int num,rr;
	if(strcmp(va,"'")==0){
		getsym();
		if(strcmp(va,"+")==0 || strcmp(va,"-")==0){
			value = (int) va[0];
			OpPlus();
		}
		else if(strcmp(va,"*")==0 || strcmp(va,"/")==0){
			value = (int) va[0];
			OpMul();
		}
		else if((va[0]>='A'&&va[0]<='Z') || (va[0]>='a' && va[0]<='z') || (strcmp(va,"_")==0)){
			Word(va[0]);
			value = (int) va[0];
			getsym();
		}
		else if(va[0]>='0' && va[0]<='9'){
			num = va[0] - '0';
			value = num;
			Digit(num);
			getsym();
		} 
		else
			error(17);
	}
	else 
		error(13);
	if(strcmp(va,"'")!=0)
		error(13);
	else 
		getsym();
	rr = value;//把int转成char;
	itoa(rr,result,10);
	if(charact ==1){
		midcode("li",resul[1],result);
		pushopnum(resul[1],1);
	}
	if(charact ==2){
		midcode("li","$t6",result);
	}
}
void Ascii(){        //＜字符串＞::= "｛十进制编码为32,33,35-126的ASCII字符｝"
	int i;
	char charstrnum[20];
	if(strcmp(va,"\"")==0){
		strcat(string[strnum],va);//将引号拼接到数组内
		getsym();
		strcat(string[strnum],va);//将一个va拼接到数组内
		strcat(string[strnum]," ");//一个字符后拼接一个空格
		while(strcmp(va,"\"")!=0){
			for(i =0; i<=20;){
				if(va[i] != '\0'){
					if((va[i]>=' ' && va[i]<='~' && va[i] != '"'))
						i++;
					else 
						error(18);
				}
				else 
					break;
			}
			getsym();
			strcat(string[strnum],va);
			if(strcmp(va,"\\")!=0)
				strcat(string[strnum]," ");
		}
		if(strcmp(va,"\"")!=0)
			error(14);
		else
			getsym();
	}
	else 
		error(14);
	itoa(strnum,charstrnum,10);
	midcode("Ascii",string[strnum],charstrnum);
	strnum++;//保存完一个字符串后数组向后移1
}
void Procedure(){     //＜程序＞::=［＜常量说明＞］［＜变量说明＞］{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞
	OutSyntax = fopen("OutSyntax.txt","w");//将语法部分的结果输出到文件中
	address = 0;
	if(strcmp(va,"const")==0){
		lev = 0;//符号表的第0层为全局的量
		flagconst = 0;
		ConstState();
	}
	if((strcmp(va,"int")==0 || strcmp(va,"char")==0) && strcmp(va3,"(") !=0){
		lev = 0;;
		VarState ();
	}
	midcode("j","main");//变量申明结束后直接跳向主函数
	while(((strcmp(va,"int")==0 || strcmp(va,"char")==0) && strcmp(va3,"(") ==0)   ||  (strcmp(va,"void") == 0 &&strcmp(va2,"main") != 0 ) ){
		if(strcmp(va,"int") ==0 || strcmp(va,"char")==0){
			lev++;
			address = 0;/////////////////////////
			ReFunction();
			strcpy(name,"end");
			insert();
		}
		else if(strcmp(va,"void") == 0){
			lev++;
			address =0;///////////////////////
			NoReFunction();
			strcpy(name,"end");
			insert();
		}
		else 
			error(20);
	}
	address = 0;
	Main();
	midcode("endprogram",":");
	fprintf(OutSyntax,"This is a Procedure. \n");
	fclose(OutSyntax);
}
void ConstState(){    //<常量说明>::=const<常量定义>;{const <常量定义>;}
	if(strcmp(va,"const")==0){
		getsym();
		ConstDefine();
		if(strcmp(va,";")!= 0)
			error(16);
		else 
			getsym();
		while(strcmp(va,"const")==0){
			getsym();
			ConstDefine();
			if(strcmp(va,";")!= 0)
				error(16);
			else 
				getsym();
		}
	}
	else 
		error(29);
	fprintf(OutSyntax,"This is a ConstState \n");
}
void ConstDefine(){   //＜常量定义＞::= int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}| char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}
	char addres[20];
	if(strcmp(va,"int") ==0){
		do{
			getsym();
			strcpy(name,va);//将标识符copy给符号表的name
			Iden();
			if(strcmp(va,"=")!= 0)
				error(12);
			else
				getsym();
			Integer();
			kind = 1;
			type = 1;
			address = address +4;
			itoa(address,addres,10);
			if(search()){////////////////////////////////////////////////////////////////
				insert();
				midcode("const","int",name,result);
				if(flagconst == 1){
					midcode("li","$t0",result);
					midcode("sw","$t0",addres,"$sp");
				}
			}
			value = 0;//除了常量、数组和变量定义部分外其他情况都为0；
		}
		while(strcmp(va,",")==0);
	}
	else if(strcmp(va,"char") ==0){
		do{
			getsym();
			strcpy(name,va);//将标识符copy给符号表的name
			Iden();
			if(strcmp(va,"=")!= 0)
				error(12);
			else
				getsym();
			charact =0;
			Character();
			kind = 1;
			type = 2;
			address = address +4;
			itoa(address,addres,10);
			if(search()){/////////////////////////////////////////////////////////////////////////
				insert();
				midcode("const","char",name,result);
				if(flagconst == 1){
					midcode("li","$t0",result);
					midcode("sw","$t0",addres,"$sp");
				}
			}
			value= 0;
		}
		while(strcmp(va,",")==0);
	}
	else 
		error(30);
}
void UnsignedInt(){   //<无符号整数> ::= ＜非零数字＞｛＜数字＞｝   此条按文法规则写无意义，只需直接判断传入的参数是否为无符号整数即可
	int i=0, num = 0, re = 0;
	if(va[i]>='0'&&va[i]<='9')
		num = va[i] - '0';
	else{ 
		error(19);
		getsym();
		return;
	}
	re = num;
	Not0(num); 
	for (i=1; i<20; i++){
		if(va[i] != '\0'){
			if(va[i]>='0'&&va[i]<='9'){
				num = va[i] - '0';
				re = re * 10 +num;
				Digit(num);
			}
			else{ 
				error(20);
	}
		}
		else{
			if(value == -111111)
				value = -re;
			else
				value = re;
			getsym();
			break;
		}
	}
	itoa(value,result,10);
}
void Integer(){       //＜整数＞::= ［＋｜－］＜无符号整数＞｜０
	if(strcmp(va,"+")== 0 || strcmp(va,"-")== 0){
		if(strcmp(va,"-")== 0)          
			value = -111111;
		getsym();
	}
	if(strcmp(va,"0")== 0){
		itoa(0,result,10);
		value = 0;
		getsym();
	}
	else
		UnsignedInt();
}
void Iden(){          //<标识符> ::= <字母>{<字母>|<数字>}
	int num;
	int i;
	for (i=0; i<20; i++){
		if(va[i] != '\0'){  
			if((va[i] >= 'A' && va[i] <='z'))
				Word(va[i]);
			else if(va[i] >= '0' && va[i] <='9'){
				num = va[i] - '0';
				Digit(num);
			}
			else 
				error(20);
		}
		else {
			getsym();
			break;
		}
	}
}
void HeadState(){   //＜声明头部＞::=  int＜标识符＞ |char＜标识符＞
	if(strcmp(va,"int")== 0){
		getsym();
		strcpy(name,va);//将标识符copy给符号表的name
		midcode(name,":");//每个函数有设立一个标签
		type = 1;
		Iden();
	}
	else if(strcmp(va,"char")== 0){
		getsym();
		strcpy(name,va);//将标识符copy给符号表的name
		midcode(name,":");//每个函数有设立一个标签
		type = 2;
		Iden();
	}
	else
		error(30);
	kind = 0;
	if(search()){
		//address = address +4;
		insert();
		if(type == 1)
			midcode("int",name,"()"," ");
		else if(type == 2)
			midcode("char",name,"()"," ");
		
	}
}
void VarState(){    //＜变量说明＞::= ＜变量定义＞;{＜变量定义＞;}
	do{
		VarDefine();
		if(strcmp(va,";")!=0)
			error(15);
		else 
			getsym();
	}
	while((strcmp(va,"int")==0 || strcmp(va,"char")==0) && strcmp(va3,"(") !=0);//防止将有返回值 函数当作变量定义来处理
	fprintf(OutSyntax,"This is a VarState \n");
}
void VarDefine(){  //＜变量定义＞::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’){,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’) }
	KindSym();
	strcpy(name,va);
	Iden();
	value = 0;
	if(strcmp(va,"[")==0){
		kind = 4;//表示为数组
		getsym();
		UnsignedInt();  
		address = address +4;
		if(search()){
			insert();//插入符号表
		}
		address = address +4*(value -1);
		if(strcmp(va,"]")!= 0)
			error(9);
		else{
			getsym();
		}
	}
	else{
		kind = 2;
		address = address +4;//不是数组地址加4
		if(search()){
				insert();//插入符号表
		}
	}
	if(kind == 4 && type ==1){
		midcode("var","int","array",name);
	}
	else if(kind == 4 && type ==2){
		midcode("var","char","array",name);
	}
	else if(kind == 2 && type ==1){
		midcode("var","int",name," ");
	}
	else if(kind == 2 && type ==2){
		midcode("var","char",name," ");
	}
	value = 0;
	while(strcmp(va,",")==0){
		getsym();
		strcpy(name,va);
		Iden();
		if(strcmp(va,"[")==0){
			kind =4;
			getsym();
			UnsignedInt();
			address = address +4;
			if(search())
				insert();//插入符号表
			address = address +4*(value -1);//插入符号表后，加上所占有的所有空间
			if(strcmp(va,"]")!= 0)
				error(9);
			else
				getsym();
		}
		else {
			kind =2;
			address = address +4;
			if(search())
				insert();//插入符号表
		}
		if(kind == 4 && type ==1){
			midcode("var","int","array",name);
		}
		else if(kind == 4 && type ==2){
			midcode("var","char","array",name);
		}
		else if(kind == 2 && type ==1){
			midcode("var","int",name," ");
		}
		else if(kind == 2 && type ==2){
			midcode("var","char",name," ");
		}
		value = 0;
	}
}
void Const(){      //＜常量＞::=  ＜整数＞|＜字符＞
	if(strcmp(va,"'")==0){
		charact =2;
		Character(); 
		}
	else{
		midcode("li","$t6",va);
		Integer();
	}
}
void KindSym(){    //＜类型标识符＞::=  int | char
	if(strcmp(va,"int")!=0 && strcmp(va,"char")!=0)
		error(30);
	else{
		if(strcmp(va,"int")==0)
			type = 1;
		else if(strcmp(va,"char")==0)
			type = 2;
		getsym();
	}
}
void ReFunction(){  //＜有返回值函数定义＞::= ＜声明头部＞‘(’＜参数＞‘)’ ‘{’＜复合语句＞‘}’
	HeadState();
	midcode("addi","$sp","-1024","$sp");
	midcode("sw","$ra","0","$sp");
	if(strcmp(va,"(")==0){
		getsym();
		Parameter();
		if(strcmp(va,")")!= 0)
			error(7);
		else 
			getsym();
	}   
	else
		error(6);
	if(strcmp(va,"{")==0){
		getsym();
		ComState();  //复合语句
		midcode("lw","$ra","0","$sp");
		midcode("addi","$sp","1024","$sp");
		midcode("jr","$ra");
		if(strcmp(va,"}")!= 0)
			error(11);
		else 
			getsym();
		} 
	else
		error(10);
	fprintf(OutSyntax,"This is a ReFunction. \n");
}
void NoReFunction(){      //＜无返回值函数定义＞::= void＜标识符＞‘(’＜参数＞‘)’‘{’＜复合语句＞‘}’
	if(strcmp(va,"void")==0){
		getsym();
		strcpy(name,va);
		kind = 0;
		type = 5;
		value = 0;
		if(search()){
			insert();
			midcode(name,":");//每个函数有设立一个标签
			midcode("void",name,"()"," ");
		}
		Iden();
		midcode("addi","$sp","-1024","$sp");
		midcode("sw","$ra","0","$sp");
		if(strcmp(va,"(")==0){
			getsym();
			Parameter();
			if(strcmp(va,")")!= 0)
				error(7);
			else
				getsym();
		}   
		else
			error(6);
		if(strcmp(va,"{")==0){
			getsym();
			ComState();  //复合语句
			midcode("lw","$ra","0","$sp");
			midcode("addi","$sp","1024","$sp");
			midcode("jr","$ra");
			if(strcmp(va,"}")!= 0)
				error(11);
			else 
				getsym();
		} 
		else
			error(10);
	}  
	else
		error(31);
	fprintf(OutSyntax,"This is a NoReFunction. \n");
}
void ComState(){      //＜复合语句＞::=［＜常量说明＞］［＜变量说明＞］＜语句列＞
	if(strcmp(va,"const")==0){
		flagconst = 1;
		ConstState();
	} 
	if((strcmp(va,"int")==0 || strcmp(va,"char")==0) && strcmp(va3,"(") !=0){
		VarState();
		}  
	StateList(); //语句列
	fprintf(OutSyntax,"This is a ComState. \n");
}
void Parameter(){    //＜参数＞::= ＜参数表＞
	ParaList();  //参数表
}
void ParaList(){     //＜参数表＞::= ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}|＜空＞
	if(strcmp(va,"int")==0 || strcmp(va,"char")==0){
		if(strcmp(va,"int")==0)
			type = 1;
		else if(strcmp(va,"char")==0)
			type = 2;
		KindSym();
		strcpy(name,va);
		kind = 3;
		value = 0;
		if(search()){
			address = address +4;
			insert();
			if(type == 1)
				midcode("para","int",name," ");
			else if(type == 2)
				midcode("para","char",name," ");
		}
		Iden();
		while(strcmp(va,",")==0){
			getsym();
			if(strcmp(va,"int")==0)
				type = 1;
			else if(strcmp(va,"char")==0)
				type = 2;
			KindSym();
			strcpy(name,va);
			kind = 3;
			if(search()){
				address = address +4;
				insert();
				if(type == 1)
					midcode("para","int",name," ");
				else if(type == 2)
					midcode("para","char",name," ");
			}
			Iden();
		}
	} 
	else 
		return; //空 //////////////
}
void Main(){      //＜主函数＞::= void main‘(’‘)’ ‘{’＜复合语句＞‘}’
	midcode("main",":");
	midcode("addi","$sp","-1024","$sp");
	midcode("la","$a1","parastack");//获取参数的开始地址
	midcode("la","$a2","opnumstack");
	if(strcmp(va,"void")==0){
		getsym();
		if(strcmp(va,"main")==0){
			strcpy(name,va);
			kind = 0;
			type = 5;
			lev ++;
			value = 0;
			if(search())
				//address = address +4;
				insert();
			getsym();
			if(strcmp(va,"(")==0){
				getsym();
				if(strcmp(va,")")==0){
					getsym();
					if(strcmp(va,"{")==0){
						getsym();
						ComState();
						if(strcmp(va,"}")!=0)
							error(11);
					}
					else 
						error(10);
				}
				else 
					error(7);
			}
			else 
				error(6);
		}
		else 
			error(20);
	}
	else
		error(20);
	midcode("addi","$sp","1024","$sp");
	fprintf(OutSyntax,"This is a Main. \n");
}
void Expres(){       //<表达式> ::= [+|-]<项>{<加法运算符><项>}
	if(strcmp(va,"+")==0 || strcmp(va,"-")==0){
		if(strcmp(va,"-")==0){
			pushop("*");
			midcode("li",resul[1],"-1");
			pushopnum(resul[1],1);
		}
		getsym();
	}
	Term();
	while(strcmp(va,"+")==0 || strcmp(va,"-")==0){
		if(strcmp(opstack[top2-1],"*")==0 || strcmp(opstack[top2-1],"/")==0 ||strcmp(opstack[top2-1],"+")==0 || strcmp(opstack[top2-1],"-")==0){
			outopstack();
			outopnum();
			midcode("move","$t3",operand);
			//strcpy(operand2,operand);
			outopnum();
			midcode("move","$t4",operand);
			//strcpy(operand1,operand);
			//strcpy(result,operand);
			midcode(op,"$t4","$t3","$t3");
			pushopnum("$t3",0);
			continue;//继续运算比当前优先级高或等级的运算
		}

		else if(strcmp(opstack[top2-1],"(")==0 || strcmp(opstack[top2-1],"[")==0){
			 pushop(va);
		}	
		else if(strcmp(opstack[top2-1],"#")==0 || strcmp(opstack[top2-1],"=")==0){
			pushop(va);
		}
		else if(strcmp(opstack[top2-1],"function")==0){
			pushop(va);
		}
		else if(strcmp(opstack[top2-1],"endfunction")==0){
			outopstack();
			if(strcmp(opstack[top2-1],"function")==0)
				outopstack();
			pushop(va);
		}
		OpPlus();
		Term();
	}
	while(top2 > 0 &&strcmp(opstack[top2-1],"#")!=0){////////////////////////////////////////////////
		if(strcmp(opstack[top2-1],"endfunction")==0){
			outopstack();
			if(strcmp(opstack[top2-1],"function")==0){
				if(strcmp(opstack[top2-2],"#")==0)
					break;
				else 
					outopstack();
			}
		} 
		if(strcmp(opstack[top2-1],"function")==0){
			break;
		}
		outopstack();
		if(strcmp(op,"=")==0){
			outopnum();
			midcode("move","$t3",operand);
			//strcpy(result,operand);
			outopnum();
			midcode("move","$t4",operand);
			//strcpy(operand1,operand);
			midcode("sw","$t3","0","$t4");
			//if(flagassign ==1 ||flagarray == 1){//赋值语句为一个全局变量赋值的情况
				//midcode("sw",result,"0",operand1);
			//}
			//else if(flagassign ==0||flagarray ==0){//赋值语句为一个局部变量赋值的情况
				//midcode("sw",result,operand1,"$sp");
			//}
		}
		else if(strcmp(op,"(")==0){
			break;
		}
		else if(strcmp(op,"[")==0){
			break;//直接跳出，在下方会把数组【】内的结果出栈
		}
		else{
			outopnum();
			midcode("move","$t3",operand);
			outopnum();
			midcode("move","$t4",operand);
			midcode(op,"$t4","$t3","$t3");
			pushopnum("$t3",0);
		}
	}
	if(strcmp(opnum[top1-1].num,"#")!=0 ){//&& strcmp(opstack[top2-1],"function")!=0
		outopnum();
		strcpy(result,operand);
	}
	fprintf(OutSyntax,"This is a Expres. \n");
}
void Term (){         //<项> ::= <因子>{<乘法运算符><因子>}
	Factor();
	while(strcmp(va,"*")==0 || strcmp(va,"/")==0){
		if(strcmp(opstack[top2 -1],"*")==0 || strcmp(opstack[top2 -1],"/")==0){
			outopstack();
			outopnum();
			midcode("move","$t3",operand);
			outopnum();
			midcode("move","$t4",operand);
			midcode(op,"$t4","$t3","$t3");
			pushopnum("$t3",0);
			continue;
		}
		else if(strcmp(opstack[top2-1],"#")==0 || strcmp(opstack[top2-1],"=")==0){
			pushop(va);
		}
		else {
			pushop(va);
		}
			
		getsym();
		Factor();
	}
}
void Factor(){        //＜因子＞::= ＜标识符＞｜＜标识符＞‘[’＜表达式＞‘]’｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞|‘(’＜表达式＞‘)’ 
	int addr = 0;
	int addr2 =0;//保存开始地址
	//int restemp ;
	int golbaltemp = 0;
	char addre[20];
	char identemp[20];
	char expressresult[20];
	if(strcmp(va,"'")==0){   //字符
		flagfunc =0;
		charact =1;
		Character();
	}
	else if(strcmp(va,"(")==0){  //表达式
		flagfunc =0;
		pushop(va);
		getsym();
		Expres(); 
		pushopnum(result,0);///////////////////////////////
		if(strcmp(va,")")!=0)
			error(7);
		else{
			getsym();
		}
	}
	else if(strcmp(va2,"(")==0){ //有返回值函数  调用语句
		flagfunc =1;
		pushop("function");


		UseFunction();
		pushop("endfunction");
		

		pushopnum("$v0",0);
	}
	else if(strcmp(va,"+")==0 || strcmp(va,"-")==0 ||strcmp(va,"0")==0 || (va[0]>= '1'&&va[0]<='9')){  //整数
		flagfunc =0;
		Integer();
		midcode("li",resul[1],result);
		pushopnum(resul[1],1);
	}
	else if((va[0] >= 'A' && va[0] <='Z') || (va[0] >= 'a' && va[0] <='z') || (va[0] =='_')){
		flagfunc =0;
		if(NotInTable(va))
			error(22);
		strcpy(identemp,va);
		addr = InTableAddress(va,lev);
		golbaltemp = golbal;
		itoa(addr,addre,10);
		Iden();  //标识符
		if(strcmp(va,"[")==0){  //标识符 【表达式】
			pushop(va);
			getsym();
			Expres();
			midcode("move","$t3",result);
			strcpy(expressresult,"$t3");
			midcode("*",expressresult,"4",expressresult);//计算数组的偏移量
			if(strcmp(va,"]")!=0)
				error(9);
			else{
				if(golbaltemp ==1){//变量为全局变量的时候
					midcode("la","$a0",identemp);
					midcode("+","$a0",expressresult,"$a0");//计算数组的地址
					midcode("lw",expressresult,"0","$a0");
					pushopnum(expressresult,0);//将算出的数组值推入栈参与运算//结果一般为$t0
				}
				else if(golbaltemp ==0){
					midcode("addi",expressresult,addre,"$a0");//计算数组的地址
					midcode("+","$a0","$sp","$a0");
					midcode("lw",expressresult,"0","$a0");
					pushopnum(expressresult,0);
				}
				else
					error(20);


				//pushopnum(expressresult,0);//将算出的数组值推入栈参与运算//结果一般为$t0
				getsym();
			}
		}
		else{
			if(golbaltemp ==1){//变量为全局变量的时候
				midcode("la","$a0",identemp);
				midcode("lw",resul[1],"0","$a0");
				pushopnum(resul[1],0);
			}
			else if(golbaltemp ==0){
				midcode("lw",resul[1],addre,"$sp");
				pushopnum(resul[1],0);
			}
			else
				error(20);
		}
	}
	else 
		error(20);
}
void Sentence(){   //＜语句＞::= ＜条件语句＞｜＜循环语句＞| ‘{’＜语句列＞‘}’｜＜有返回值函数调用语句＞;| ＜无返回值函数调用语句＞;｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜空＞;|＜情况语句＞｜＜返回语句＞;
	if(strcmp(va,"if")==0)
		RequireState();
	else if(strcmp(va,"for")==0)
		ForState();
	else if(strcmp(va,"{")==0){
		getsym();	
		StateList();
		if(strcmp(va,"}")!=0)
			error(11);
		else 
			getsym();
	}
	else if(strcmp(va,"scanf")==0){
		ScanfState();
		if(strcmp(va,";")!=0)
			error(15);
		else
			getsym();
	}
	else if(strcmp(va,"printf")==0){
		PrintfState();
		if(strcmp(va,";")!=0)
			error(15);
		else
			getsym();
	}
	else if(strcmp(va,"switch")==0){
		Switch();
	}
	else if(strcmp(va,"return")==0){
		ReturnState();
		if(strcmp(va,";")!=0)
			error(15);
		else
			getsym();
	}
	else if(strcmp(va,";")==0){   //空语句
		getsym();
	}	
	else if(strcmp(va2,"=")==0 || strcmp(va2,"[")==0){
		AssignState();
		if(strcmp(va,";")!=0)
			error(15);
		else
			getsym();
	}
	else if(strcmp(va2,"(")==0){
		UseFunction();
		if(strcmp(va,";")!=0)
			error(15);
		else
			getsym();
	}
	else 
		error(6);
}
void AssignState(){    //＜赋值语句＞::=＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞
	int addr = 0;
	int valu = 0;
	int golbaltemp =0;
	char addre[20];
	char expressresult[20];
	if(NotInTable(va))//如果赋值语句的标识符不在符号表中，则报未定义的标识符
		error(22);
	strcpy(idenassign,va);
	addr = InTableAddress(va,lev);
	flagassign =golbal;
	itoa(addr,addre,10);
	valu = InTableValue(va);
	Iden();
	if(strcmp(va,"[")==0){
		flagarray = 1;
		pushop(va);
		getsym();
		Expres();
		midcode("move","$t3",result);
		strcpy(expressresult,"$t3");//把表达式的结果存起来，即数组为第几个
		midcode("*",expressresult,"4",expressresult);
		if(flagassign ==1){
			midcode("la","$a0",idenassign);
			midcode("+",expressresult,"$a0",expressresult);
		}
		else if(flagassign ==0){
			midcode("addi",expressresult,addre,expressresult);
			midcode("+",expressresult,"$sp",expressresult);
		}
		else 
			error(55);
		if(strcmp(va,"]")!=0)
			error(9);
		else{
			pushopnum(expressresult,0);
			getsym();
		}
	}
	else{//不是数组的时候
		flagarray = 0;
		if(flagassign ==1){
			midcode("la","$a0",idenassign);
			pushopnum("$a0",0);
		}
		else if(flagassign ==0){
			midcode("li",resul[1],addre);
			midcode("+",resul[1],"$sp",resul[1]);
			pushopnum(resul[1],0);
		}
		else 
			error(55);
	}
	if(strcmp(va,"=")!=0)
		error(12);
	else{
		pushop("=");
		getsym();
	}
	Expres();
	fprintf(OutSyntax,"This is a AssignStatament \n");
}
void RequireState(){ //＜条件语句＞::=  if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］
	char iflabel[20];//if标签
	char endif[20];
	strcpy(iflabel,Label[label]);//预先给if留一个标签用在else处
	label++;
	strcpy(endif,Label[label]);//预先给if留一个标签，用在末尾处
	label++;
	if (strcmp(va,"if") == 0){
		getsym();
		if(strcmp(va,"(")!=0)
			error(6);
		else
			getsym();
		userequire = 0;
		Require();
		if(strcmp(va,")")!=0)
			error(7);
		else
			getsym();
		Sentence();
		midcode("j",endif);
		if(strcmp(va,"else")==0){
			midcode(iflabel,":");
			getsym();
			Sentence();
			midcode(endif,":");
		}
		else {
			midcode(iflabel,":");
			midcode(endif,":");
		}
	}
	else 
		error(32);
	fprintf(OutSyntax,"This is a RequireState\n");
}
void Require(){      //＜条件＞::= ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞ //表达式为0条件为假，否则为真
	char endfortemp[20];
	if(userequire ==1){
		strcpy(endfortemp,endfor);//将for结束的标签传给临时变量
		midcode(Label[label],":");//是for给条件先设立一个标签
		strcpy(requirelabel,Label[label]);
		label++;
	}
	Expres();    //<|<=|>|>=|!=|==
	midcode("move","$s1",result);
	//strcpy(opnumb,result);
	if (strcmp(va,"<")==0 ||strcmp(va,"<=")==0||strcmp(va,">")==0||strcmp(va,">=")==0||strcmp(va,"!=")==0||strcmp(va,"==")==0){
		strcpy(op1,va);
		OpRelation();
		Expres();
		midcode("move","$s2",result);
		//strcpy(operand2,result);
		//strcpy(opnumb2,result);
		midcode("require","$s1",op1,"$s2");
		if (strcmp(op1,"<")==0){ // >=
			if(userequire==0)//代表这是if语句
				midcode("bge","$s1","$s2",Label[label-2]);
			else 
				midcode("blt","$s1","$s2",Label[label]);
		}
		else if (strcmp(op1,"<=")==0 ){ // >
			if(userequire==0)
				midcode("bgt","$s1","$s2",Label[label-2]);
			else 
				midcode("ble","$s1","$s2",Label[label]);
		}
		else if (strcmp(op1,">")==0){ // <=
			if(userequire==0)
				midcode("ble","$s1","$s2",Label[label-2]);
			else 
				midcode("bgt","$s1","$s2",Label[label]);
		}
		else if (strcmp(op1,">=")==0 ){// <
			if(userequire==0)
				midcode("blt","$s1","$s2",Label[label-2]);
			else 
				midcode("bge","$s1","$s2",Label[label]);
		}
		else if (strcmp(op1,"!=")==0 ){// ==
			if(userequire==0)
				midcode("beq","$s1","$s2",Label[label-2]);
			else 
				midcode("bne","$s1","$s2",Label[label]);
		}
		else if (strcmp(op1,"==")==0 ){// !=
			if(userequire==0)
				midcode("bne","$s1","$s2",Label[label-2]);
			else 
				midcode("beq","$s1","$s2",Label[label]);
		}
		if(userequire == 1)
			midcode("j",endfortemp);
	}
	else{
		if(userequire==0)
			midcode("beq","$s1","0",Label[label-2]);
		else{ 
			midcode("bne","$s1","0",Label[label]);
			midcode("j",endfortemp);
		}
	}
}
void ForState(){     //＜循环语句＞::= for‘(’＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞‘)’＜语句＞
	char id[20],idstep[20];//id为第一个标识符
	char forlabel[20];	
	char requirelabeltemp[20];//存放条件标签的临时变量
	char endfortemp[20];
	char addre[20];
	char opnumbt[20],op1t[20],opnumb2t[20];//用来临时存条件的三个元素
	char opaddorsub[20],opstep[20];//＜标识符＞＝＜标识符＞(+|-)＜步长＞ 用来存它
	int addr = 0;
	int flagforid1 =0;
	int flagforid2 =0;
	strcpy(endfor,Label[label]);//调用for之前先给for预留一个结束标签，传给条件
	strcpy(endfortemp,endfor);//将for结束的标签传给临时变量
	label++;
	if(strcmp(va,"for")==0){
		getsym();
		if(strcmp(va,"(")!=0)
			error(6);
		else
			getsym();
		if(NotInTable(va))
			error(22);
		addr = InTableAddress(va,lev);
		itoa(addr,addre,10);
		flagassign =golbal;
		if(golbal ==1){//如果是全局变量
			midcode("la","$a0",va);//获取地址
			pushopnum("$a0",0);
		}
		else if(golbal ==0){
			midcode("li",resul[1],addre);
			midcode("+",resul[1],"$sp",resul[1]);
			pushopnum(resul[1],0);
		}
		else 
			error(55);
		Iden();
		if(strcmp(va,"=")!=0)
			error(12);
		else{
			pushop(va);
			getsym();
		}
		flagarray = 0;
		Expres();
		if(strcmp(va,";")!=0)
			error(15);
		else
			getsym();
		userequire =1;
		midcode("j",Label[label+1]);
		Require();
		strcpy(requirelabeltemp,requirelabel);//将条件的标签传递过来
		strcpy(opnumbt,opnumb);//将条件的三个元素传给临时变量
		strcpy(op1t,op1);
		strcpy(opnumb2t,opnumb2);
		if(strcmp(va,";")!=0)
			error(15);
		else
			getsym();
		strcpy(id,va);
		addr = InTableAddress(va,lev);
		flagforid1 = golbal;
		if(NotInTable(va))
			error(22);
		Iden();
		if(strcmp(va,"=")!=0)
			error(12);
		else
			getsym();////＜标识符＞＝＜标识符＞(+|-)＜步长＞ 用来存标识符
		addr = InTableAddress(va,lev);
		flagforid2 = golbal;
		itoa(addr,addre,10);
		strcpy(idstep,va);
		if(NotInTable(va))
			error(22);
		Iden();
		if(strcmp(va,"+")==0||strcmp(va,"-")==0){
			strcpy(opaddorsub,va);
			getsym();
			strcpy(opstep,va);
			midcode(Label[label],":");
			strcpy(forlabel,Label[label]);
			label++;
			
			Step();
			if(strcmp(va,")")!=0)
				error(7);
			else
				getsym();
			Sentence();
			if(flagforid2 ==1){//如果是全局变量
				midcode("la","$a0",idstep);//获取地址
				midcode("lw","$t0","0","$a0");
			}
			else if(flagforid2 ==0){
				midcode("lw","$t0",addre,"$sp");
			}
			else 
				error(20);
			if(strcmp(opaddorsub,"+")==0)
				midcode("addi","$t0",opstep,"$t0");
			else if(strcmp(opaddorsub,"-")==0)
				midcode("-","$t0",opstep,"$t0");
			addr = InTableAddress(id,lev);
			itoa(addr,addre,10);
			if(flagforid1 ==1){//如果是全局变量
				midcode("la","$a0",id);//获取地址
				midcode("sw","$t0","0","$a0");
			}
			else if(flagforid1 ==0){
				midcode("sw","$t0",addre,"$sp");
			}
			else 
				error(20);
			midcode("j",requirelabeltemp);
			midcode(endfortemp,":");//////////////////////////////////
		}
		else
			error(23);
	}
	else 
		error(32);
	fprintf(OutSyntax,"This is a ForState. \n");
}
void Step(){     //＜步长＞::=＜非零数字＞｛＜数字＞｝
	int num,i;
	num = va[0] - '0';
	Not0(num);
	for(i =1;1 <= 21; i++){
		if(va[i] != '\0'){
			num = va[i] - '0';
			Digit(num);
		}
		else {
			getsym();
			break;
		}
	}
}
void Switch(){    //＜情况语句＞::= switch ‘(’＜表达式＞‘)’ ‘{’＜情况表＞＜缺省＞‘}’
	char switchvalu[20];//用来保存 switch语句表达式的结果
	char switchlabel[20];//用来存放switch语句结束后的标签
	strcpy(switchlabel,Label[label]);//先用一个标签
	label++;
	if(strcmp(va,"switch")==0){
		getsym();
		if(strcmp(va,"(")==0){
			getsym();
			Expres();
			midcode("move","$t5",result);
			strcpy(switchvalu,"$t5");
			//strcpy(switchvalu,result);
			if(strcmp(va,")")!=0)
				error(7);
			else
				getsym();
		}
		else
			error(6);
		if(strcmp(va,"{")!=0)
			error(10);
		else{
			getsym();
			SwitchList(switchvalu,switchlabel);
			Default();
			midcode("j",switchlabel);
			if(strcmp(va,"}")!=0)
				error(11);
			else
				getsym();
		}
		midcode(switchlabel,":");
	}
	else 
		error(34);
	fprintf(OutSyntax,"This is a Switch. \n");
}
void SwitchList(char switchvalu[20],char switchlabel[20]){  //＜情况表＞::= ＜情况子语句＞{＜情况子语句＞}
	SwitchSon(switchvalu,switchlabel);
	while(strcmp(va,"case")==0){
		SwitchSon(switchvalu,switchlabel);
	}
}
void SwitchSon(char switchvalu[20],char switchlabel[20]){   //＜情况子语句＞::= case＜常量＞：＜语句＞
	char caselabel[20];
	if(strcmp(va,"case")==0){
		getsym();
		Const();
		midcode("bne",switchvalu,"$t6",Label[label]);
		strcpy(caselabel,Label[label]);
		label++;
		if(strcmp(va,":")!=0)
			error(16);
		else
			getsym();
		Sentence();
		midcode("j",switchlabel);
		midcode(caselabel,":");
	}
	else 
		error(35);
}
void Default(){   //＜缺省＞::= default : ＜语句＞
	if(strcmp(va,"default")==0){
		getsym();
		if(strcmp(va,":")!=0)
			error(16);
		else
			getsym();
		Sentence();
	}
	else 
		error(36);
}
void UseFunction(){   //＜有、无返回值函数调用语句＞::=＜标识符＞‘(’＜值参数表＞‘)’
	char funnametemp[20];
	int paratemp =0;
	int sizefuntemp = 0;
	char sizefunctemp[20];
	//sizefun = InTableFunSize(va)+4;//加4存函数的ra
	//sizefuntemp = sizefun;
	//itoa(sizefuntemp,sizefunctemp,10);
	strcpy(funname,va);//将函数的名字保存起来
	strcpy(funnametemp,funname);//方便递归
	para = InTableParanum(va);
	paratemp = para;
	Iden();
	if(strcmp(va,"(")!=0)
		error(6);
	else{
		getsym();
	}
	WortnParaList();
	
	midcode("call",funnametemp);
	if(strcmp(va,")")!=0)
		error(7);
	else
		getsym();
	//midcode("addi","$sp",sizefunctemp,"$sp");
	fprintf(OutSyntax,"This is a UseFunction. \n");
}
void WortnParaList(){  //＜值参数表＞::=＜表达式＞{,＜表达式＞}｜＜空＞
	int addr = 0;
	int paranum = 0;//记录参数的数目
	int i;
	int sizepara = 0;
	char addre[20];
	char funnametemp[20];
	char sizepar[20];
	int addr2 = 0;
	char addre2[20];
	int sizefuntemp = 0;
	char sizefunctemp[20];
	sizefuntemp = -sizefun;
	itoa(sizefuntemp,sizefunctemp,10);
	paranum = para;
	sizepara = paranum *4+4;
	itoa(sizepara,sizepar,10);
	midcode("addi","$a1",sizepar,"$a1");//调用一个函数的时候先为其的参数预留空间
	strcpy(funnametemp,funname);//方便递归
	addr =0;//第一个参数的地址
	itoa(addr,addre,10);
	strcpy(op,"push");
	if(strcmp(va,")")==0)  //空
		paranum =0;
	else{
		paranum = paranum +1;
		Expres();
		midcode("push",result);		
		midcode("sw",result,"0","$a1");//将参数先存起来
		while(strcmp(va,",")==0){ 
			paranum = paranum +1;
			addr =addr -4;//其后的每个参数加4
			itoa(addr,addre,10);
			getsym();
			Expres();  
			midcode("push",result);
			midcode("sw",result,addre,"$a1");//将参数先存起来
		}
	}
	//midcode("sw","$ra","0","$sp");
	//midcode("addi","$sp",sizefunctemp,"$sp");
	midcode("addi","$sp","-1024","$sp");
	addr = 4;
	addr2 = 0;
	for(i = 0;i<paranum; i++){
		addr =addr -4;//第一个参数的地址
		addr2 = addr2 +4;
		itoa(addr,addre,10);
		itoa(addr2,addre2,10);
		midcode("lw","$t0",addre,"$a1");
		midcode("sw","$t0",addre2,"$sp");
	}
	midcode("addi","$sp","1024","$sp");
	midcode("-","$a1",sizepar,"$a1");
}
void StateList(){   //＜语句列＞   ::= ｛＜语句＞｝      
	while(strcmp(va,"if")==0 || strcmp(va,"for")==0 || strcmp(va,"{")==0 || strcmp(va,"for")==0 || strcmp(va,"scanf")==0 || strcmp(va,"printf")==0

		|| strcmp(va,"for")==0 || strcmp(va,"switch")==0 || strcmp(va,"return")==0 || strcmp(va,";")==0 ||(strcmp(va2,"=")==0 ||strcmp(va2,"[")==0) || strcmp(va2,"(")==0 ){
	Sentence();
                                                                                                                                                                                                                                                         	} 
}
void ScanfState(){   //<读语句> ::= scanf'('<标识符>{,<标识符>}')'
	int addr = 0;
	int typetemp = 0;
	char addre[20];
	if(strcmp(va,"scanf") == 0){
		getsym();
		if(strcmp(va,"(") == 0){
			getsym();
			if(NotInTable(va))
				error(22);
			addr = InTableAddress(va,lev);
			itoa(addr,addre,10);
			typetemp = InTableType(va,lev);
			if(typetemp == 1)
				midcode("li","$v0","5");
			else if(typetemp == 2)
				midcode("li","$v0","12");
			midcode("syscall"," ");
			midcode("move","$t0","$v0");
			if(golbal ==1){
				midcode("la","$a0",va);
				midcode("sw","$t0","0","$a0");
			}
			else if(golbal == 0){
				midcode("sw","$t0",addre,"$sp");
			}
			else 
				error(55);
			Iden();
			while(strcmp(va,",") == 0){
				getsym();
				if(NotInTable(va))
					error(22);
				addr = InTableAddress(va,lev);
				itoa(addr,addre,10);
				typetemp = InTableType(va,lev);
				if(typetemp == 1)
					midcode("li","$v0","5");
				else if(typetemp == 2)
					midcode("li","$v0","12");
				midcode("syscall"," ");
				midcode("move","$t0","$v0");

				if(golbal ==1){
					midcode("la","$a0",va);
					midcode("sw","$t0","0","$a0");
				}
				else if(golbal == 0){
					midcode("sw","$t0",addre,"$sp");
				}
				else 
					error(55);
				Iden();
			}
			if (strcmp(va,")")!=0)
				error(7);
			else 
				getsym();
		}
		else 
			error(6);
	}
	else 
		error(37);
	fprintf(OutSyntax,"This is a ScanfStatement \n");
}
void PrintfState(){    //＜写语句＞::= printf ‘(’ ＜字符串＞,＜表达式＞ ‘)’| printf ‘(’＜字符串＞ ‘)’| printf ‘(’＜表达式＞‘)’
	int typetemp = 0;
	char strnumtemp[20];
	if(strcmp(va,"printf") == 0){
		getsym();
		if(strcmp(va,"(") != 0)
			error(6);
		else
			getsym();
		if(strcmp(va,"\"") == 0){
			Ascii();
			itoa(strnum-1,strnumtemp,10);
			midcode("la1","$a0",strnumtemp);
			midcode("li","$v0","4");
			midcode("syscall"," ");
			if(strcmp(va,",") == 0){
				getsym();
				typetemp = InTableType(va,lev);
				Expres();
				midcode("move","$a0",result);
				if(typetemp == 2)
					midcode("li","$v0","11");
				else
					midcode("li","$v0","1");
				midcode("syscall"," ");
			}
		}
		else{ 
			typetemp = InTableType(va,lev);
			Expres();
			midcode("move","$a0",result);
			if(typetemp == 2)
				midcode("li","$v0","11");
			else
				midcode("li","$v0","1");
			midcode("syscall"," ");
		}

		midcode("la1","$a0","0");//执行完一次写语句后输出换行
		midcode("li","$v0","4");
		midcode("syscall"," ");

		if(strcmp(va,")") != 0)
			error(7);
		else
			getsym();
	}
	else 
		error(38);
	fprintf(OutSyntax,"This is a PrintfState. \n");
}
void ReturnState(){    //＜返回语句＞   ::=  return[‘(’＜表达式＞‘)’]  
	if(strcmp(va,"return") == 0){
		getsym();
		if(strcmp(va,"(") == 0){
			getsym();
			Expres();
			midcode("ret",result," "," ");
			midcode("move","$v0",result);
			midcode("lw","$ra","0","$sp");
			midcode("addi","$sp","1024","$sp");
			midcode("beq","$ra","0","endprogram");
			midcode("jr","$ra");
			if(strcmp(va,")") != 0)
				error(7);
			else 
				getsym();
		}
		else{
			midcode("lw","$ra","0","$sp");
			midcode("addi","$sp","1024","$sp");
			midcode("beq","$ra","0","endprogram");
			midcode("jr","$ra");
		}
	}
	else 
		error(39);
	fprintf(OutSyntax,"This is a ReturnState. \n");
}
void getsym(){
	int m,n;
	m = readworld+1;
	n = readworld+2;
	if(readworld == tempp+1){
		strcpy(va,"endpproduce");
		return;
	}
	if(readworld<=tempp && strcmp(world[readworld].symbol,"0") != 0){
		strcpy(va,world[readworld].value);
		line2 = world[readworld].count;
	}
	if(m<=tempp && strcmp(world[m].symbol,"0") != 0){
		strcpy(va2,world[m].value);
	}
	if(n<=tempp && strcmp(world[n].symbol,"0") != 0){
		strcpy(va3,world[n].value);
	}
	readworld++;
}  	 
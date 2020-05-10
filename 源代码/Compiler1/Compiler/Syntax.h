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
void OpPlus(){        //<�ӷ������> ::= +|-
	if((strcmp(va,"+")!=0) && (strcmp(va,"-")!=0))
		error(23);
	else
		getsym();
}
void OpMul(){         //<�˷������> ::= *|/
	if((strcmp(va,"*")!=0) && (strcmp(va,"/")!=0))
		error(24);
	else
		getsym();
}
void OpRelation(){   //<��ϵ�����> ::= <|<=|>|>=|!=|==
	if(strcmp(va,"<") !=0 && strcmp(va,"<=") !=0 && strcmp(va,">") !=0 && strcmp(va,">=") !=0 && strcmp(va,"!=") !=0 && strcmp(va,"==") !=0)
		error(25);
	else
		getsym();
}
void Word (char c){       //����ĸ��::= �ߣ�a��...��z��A��...��Z     
	if( !((c>='a'&&c<='z') ||(c>='A'&&c<='Z') ||(c=='_') ))
		error(26);
}
void Digit(int m){       //<����> ::= 0|��������
	if(m < 0 || m > 9)
		error(27);
}
void Not0(int m){       //��������
	if(m < 1 || m > 9)
		error(28);
}
void Character(){   //���ַ���::='���ӷ��������'��'���˷��������'��'����ĸ��'��'�����֣�'
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
	rr = value;//��intת��char;
	itoa(rr,result,10);
	if(charact ==1){
		midcode("li",resul[1],result);
		pushopnum(resul[1],1);
	}
	if(charact ==2){
		midcode("li","$t6",result);
	}
}
void Ascii(){        //���ַ�����::= "��ʮ���Ʊ���Ϊ32,33,35-126��ASCII�ַ���"
	int i;
	char charstrnum[20];
	if(strcmp(va,"\"")==0){
		strcat(string[strnum],va);//������ƴ�ӵ�������
		getsym();
		strcat(string[strnum],va);//��һ��vaƴ�ӵ�������
		strcat(string[strnum]," ");//һ���ַ���ƴ��һ���ո�
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
	strnum++;//������һ���ַ��������������1
}
void Procedure(){     //������::=�ۣ�����˵�����ݣۣ�����˵������{���з���ֵ�������壾|���޷���ֵ�������壾}����������
	OutSyntax = fopen("OutSyntax.txt","w");//���﷨���ֵĽ��������ļ���
	address = 0;
	if(strcmp(va,"const")==0){
		lev = 0;//���ű�ĵ�0��Ϊȫ�ֵ���
		flagconst = 0;
		ConstState();
	}
	if((strcmp(va,"int")==0 || strcmp(va,"char")==0) && strcmp(va3,"(") !=0){
		lev = 0;;
		VarState ();
	}
	midcode("j","main");//��������������ֱ������������
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
void ConstState(){    //<����˵��>::=const<��������>;{const <��������>;}
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
void ConstDefine(){   //���������壾::= int����ʶ��������������{,����ʶ��������������}| char����ʶ���������ַ���{,����ʶ���������ַ���}
	char addres[20];
	if(strcmp(va,"int") ==0){
		do{
			getsym();
			strcpy(name,va);//����ʶ��copy�����ű��name
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
			value = 0;//���˳���������ͱ������岿�������������Ϊ0��
		}
		while(strcmp(va,",")==0);
	}
	else if(strcmp(va,"char") ==0){
		do{
			getsym();
			strcpy(name,va);//����ʶ��copy�����ű��name
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
void UnsignedInt(){   //<�޷�������> ::= ���������֣��������֣���   �������ķ�����д�����壬ֻ��ֱ���жϴ���Ĳ����Ƿ�Ϊ�޷�����������
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
void Integer(){       //��������::= �ۣ������ݣ��޷�������������
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
void Iden(){          //<��ʶ��> ::= <��ĸ>{<��ĸ>|<����>}
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
void HeadState(){   //������ͷ����::=  int����ʶ���� |char����ʶ����
	if(strcmp(va,"int")== 0){
		getsym();
		strcpy(name,va);//����ʶ��copy�����ű��name
		midcode(name,":");//ÿ������������һ����ǩ
		type = 1;
		Iden();
	}
	else if(strcmp(va,"char")== 0){
		getsym();
		strcpy(name,va);//����ʶ��copy�����ű��name
		midcode(name,":");//ÿ������������һ����ǩ
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
void VarState(){    //������˵����::= ���������壾;{���������壾;}
	do{
		VarDefine();
		if(strcmp(va,";")!=0)
			error(15);
		else 
			getsym();
	}
	while((strcmp(va,"int")==0 || strcmp(va,"char")==0) && strcmp(va3,"(") !=0);//��ֹ���з���ֵ ����������������������
	fprintf(OutSyntax,"This is a VarState \n");
}
void VarDefine(){  //���������壾::= �����ͱ�ʶ����(����ʶ����|����ʶ������[�����޷�����������]��){,(����ʶ����|����ʶ������[�����޷�����������]��) }
	KindSym();
	strcpy(name,va);
	Iden();
	value = 0;
	if(strcmp(va,"[")==0){
		kind = 4;//��ʾΪ����
		getsym();
		UnsignedInt();  
		address = address +4;
		if(search()){
			insert();//������ű�
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
		address = address +4;//���������ַ��4
		if(search()){
				insert();//������ű�
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
				insert();//������ű�
			address = address +4*(value -1);//������ű�󣬼�����ռ�е����пռ�
			if(strcmp(va,"]")!= 0)
				error(9);
			else
				getsym();
		}
		else {
			kind =2;
			address = address +4;
			if(search())
				insert();//������ű�
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
void Const(){      //��������::=  ��������|���ַ���
	if(strcmp(va,"'")==0){
		charact =2;
		Character(); 
		}
	else{
		midcode("li","$t6",va);
		Integer();
	}
}
void KindSym(){    //�����ͱ�ʶ����::=  int | char
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
void ReFunction(){  //���з���ֵ�������壾::= ������ͷ������(������������)�� ��{����������䣾��}��
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
		ComState();  //�������
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
void NoReFunction(){      //���޷���ֵ�������壾::= void����ʶ������(������������)����{����������䣾��}��
	if(strcmp(va,"void")==0){
		getsym();
		strcpy(name,va);
		kind = 0;
		type = 5;
		value = 0;
		if(search()){
			insert();
			midcode(name,":");//ÿ������������һ����ǩ
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
			ComState();  //�������
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
void ComState(){      //��������䣾::=�ۣ�����˵�����ݣۣ�����˵�����ݣ�����У�
	if(strcmp(va,"const")==0){
		flagconst = 1;
		ConstState();
	} 
	if((strcmp(va,"int")==0 || strcmp(va,"char")==0) && strcmp(va3,"(") !=0){
		VarState();
		}  
	StateList(); //�����
	fprintf(OutSyntax,"This is a ComState. \n");
}
void Parameter(){    //��������::= ��������
	ParaList();  //������
}
void ParaList(){     //��������::= �����ͱ�ʶ��������ʶ����{,�����ͱ�ʶ��������ʶ����}|���գ�
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
		return; //�� //////////////
}
void Main(){      //����������::= void main��(����)�� ��{����������䣾��}��
	midcode("main",":");
	midcode("addi","$sp","-1024","$sp");
	midcode("la","$a1","parastack");//��ȡ�����Ŀ�ʼ��ַ
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
void Expres(){       //<���ʽ> ::= [+|-]<��>{<�ӷ������><��>}
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
			continue;//��������ȵ�ǰ���ȼ��߻�ȼ�������
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
			//if(flagassign ==1 ||flagarray == 1){//��ֵ���Ϊһ��ȫ�ֱ�����ֵ�����
				//midcode("sw",result,"0",operand1);
			//}
			//else if(flagassign ==0||flagarray ==0){//��ֵ���Ϊһ���ֲ�������ֵ�����
				//midcode("sw",result,operand1,"$sp");
			//}
		}
		else if(strcmp(op,"(")==0){
			break;
		}
		else if(strcmp(op,"[")==0){
			break;//ֱ�����������·�������顾���ڵĽ����ջ
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
void Term (){         //<��> ::= <����>{<�˷������><����>}
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
void Factor(){        //�����ӣ�::= ����ʶ����������ʶ������[�������ʽ����]������������|���ַ��������з���ֵ����������䣾|��(�������ʽ����)�� 
	int addr = 0;
	int addr2 =0;//���濪ʼ��ַ
	//int restemp ;
	int golbaltemp = 0;
	char addre[20];
	char identemp[20];
	char expressresult[20];
	if(strcmp(va,"'")==0){   //�ַ�
		flagfunc =0;
		charact =1;
		Character();
	}
	else if(strcmp(va,"(")==0){  //���ʽ
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
	else if(strcmp(va2,"(")==0){ //�з���ֵ����  �������
		flagfunc =1;
		pushop("function");


		UseFunction();
		pushop("endfunction");
		

		pushopnum("$v0",0);
	}
	else if(strcmp(va,"+")==0 || strcmp(va,"-")==0 ||strcmp(va,"0")==0 || (va[0]>= '1'&&va[0]<='9')){  //����
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
		Iden();  //��ʶ��
		if(strcmp(va,"[")==0){  //��ʶ�� �����ʽ��
			pushop(va);
			getsym();
			Expres();
			midcode("move","$t3",result);
			strcpy(expressresult,"$t3");
			midcode("*",expressresult,"4",expressresult);//���������ƫ����
			if(strcmp(va,"]")!=0)
				error(9);
			else{
				if(golbaltemp ==1){//����Ϊȫ�ֱ�����ʱ��
					midcode("la","$a0",identemp);
					midcode("+","$a0",expressresult,"$a0");//��������ĵ�ַ
					midcode("lw",expressresult,"0","$a0");
					pushopnum(expressresult,0);//�����������ֵ����ջ��������//���һ��Ϊ$t0
				}
				else if(golbaltemp ==0){
					midcode("addi",expressresult,addre,"$a0");//��������ĵ�ַ
					midcode("+","$a0","$sp","$a0");
					midcode("lw",expressresult,"0","$a0");
					pushopnum(expressresult,0);
				}
				else
					error(20);


				//pushopnum(expressresult,0);//�����������ֵ����ջ��������//���һ��Ϊ$t0
				getsym();
			}
		}
		else{
			if(golbaltemp ==1){//����Ϊȫ�ֱ�����ʱ��
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
void Sentence(){   //����䣾::= ��������䣾����ѭ����䣾| ��{��������У���}�������з���ֵ����������䣾;| ���޷���ֵ����������䣾;������ֵ��䣾;��������䣾;����д��䣾;�����գ�;|�������䣾����������䣾;
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
	else if(strcmp(va,";")==0){   //�����
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
void AssignState(){    //����ֵ��䣾::=����ʶ�����������ʽ��|����ʶ������[�������ʽ����]��=�����ʽ��
	int addr = 0;
	int valu = 0;
	int golbaltemp =0;
	char addre[20];
	char expressresult[20];
	if(NotInTable(va))//�����ֵ���ı�ʶ�����ڷ��ű��У���δ����ı�ʶ��
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
		strcpy(expressresult,"$t3");//�ѱ��ʽ�Ľ����������������Ϊ�ڼ���
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
	else{//���������ʱ��
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
void RequireState(){ //��������䣾::=  if ��(������������)������䣾��else����䣾��
	char iflabel[20];//if��ǩ
	char endif[20];
	strcpy(iflabel,Label[label]);//Ԥ�ȸ�if��һ����ǩ����else��
	label++;
	strcpy(endif,Label[label]);//Ԥ�ȸ�if��һ����ǩ������ĩβ��
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
void Require(){      //��������::= �����ʽ������ϵ������������ʽ���������ʽ�� //���ʽΪ0����Ϊ�٣�����Ϊ��
	char endfortemp[20];
	if(userequire ==1){
		strcpy(endfortemp,endfor);//��for�����ı�ǩ������ʱ����
		midcode(Label[label],":");//��for������������һ����ǩ
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
			if(userequire==0)//��������if���
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
void ForState(){     //��ѭ����䣾::= for��(������ʶ�����������ʽ��;��������;����ʶ����������ʶ����(+|-)����������)������䣾
	char id[20],idstep[20];//idΪ��һ����ʶ��
	char forlabel[20];	
	char requirelabeltemp[20];//���������ǩ����ʱ����
	char endfortemp[20];
	char addre[20];
	char opnumbt[20],op1t[20],opnumb2t[20];//������ʱ������������Ԫ��
	char opaddorsub[20],opstep[20];//����ʶ����������ʶ����(+|-)�������� ��������
	int addr = 0;
	int flagforid1 =0;
	int flagforid2 =0;
	strcpy(endfor,Label[label]);//����for֮ǰ�ȸ�forԤ��һ��������ǩ����������
	strcpy(endfortemp,endfor);//��for�����ı�ǩ������ʱ����
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
		if(golbal ==1){//�����ȫ�ֱ���
			midcode("la","$a0",va);//��ȡ��ַ
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
		strcpy(requirelabeltemp,requirelabel);//�������ı�ǩ���ݹ���
		strcpy(opnumbt,opnumb);//������������Ԫ�ش�����ʱ����
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
			getsym();////����ʶ����������ʶ����(+|-)�������� �������ʶ��
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
			if(flagforid2 ==1){//�����ȫ�ֱ���
				midcode("la","$a0",idstep);//��ȡ��ַ
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
			if(flagforid1 ==1){//�����ȫ�ֱ���
				midcode("la","$a0",id);//��ȡ��ַ
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
void Step(){     //��������::=���������֣��������֣���
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
void Switch(){    //�������䣾::= switch ��(�������ʽ����)�� ��{�����������ȱʡ����}��
	char switchvalu[20];//�������� switch�����ʽ�Ľ��
	char switchlabel[20];//�������switch��������ı�ǩ
	strcpy(switchlabel,Label[label]);//����һ����ǩ
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
void SwitchList(char switchvalu[20],char switchlabel[20]){  //�������::= ���������䣾{���������䣾}
	SwitchSon(switchvalu,switchlabel);
	while(strcmp(va,"case")==0){
		SwitchSon(switchvalu,switchlabel);
	}
}
void SwitchSon(char switchvalu[20],char switchlabel[20]){   //���������䣾::= case��������������䣾
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
void Default(){   //��ȱʡ��::= default : ����䣾
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
void UseFunction(){   //���С��޷���ֵ����������䣾::=����ʶ������(����ֵ��������)��
	char funnametemp[20];
	int paratemp =0;
	int sizefuntemp = 0;
	char sizefunctemp[20];
	//sizefun = InTableFunSize(va)+4;//��4�溯����ra
	//sizefuntemp = sizefun;
	//itoa(sizefuntemp,sizefunctemp,10);
	strcpy(funname,va);//�����������ֱ�������
	strcpy(funnametemp,funname);//����ݹ�
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
void WortnParaList(){  //��ֵ������::=�����ʽ��{,�����ʽ��}�����գ�
	int addr = 0;
	int paranum = 0;//��¼��������Ŀ
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
	midcode("addi","$a1",sizepar,"$a1");//����һ��������ʱ����Ϊ��Ĳ���Ԥ���ռ�
	strcpy(funnametemp,funname);//����ݹ�
	addr =0;//��һ�������ĵ�ַ
	itoa(addr,addre,10);
	strcpy(op,"push");
	if(strcmp(va,")")==0)  //��
		paranum =0;
	else{
		paranum = paranum +1;
		Expres();
		midcode("push",result);		
		midcode("sw",result,"0","$a1");//�������ȴ�����
		while(strcmp(va,",")==0){ 
			paranum = paranum +1;
			addr =addr -4;//����ÿ��������4
			itoa(addr,addre,10);
			getsym();
			Expres();  
			midcode("push",result);
			midcode("sw",result,addre,"$a1");//�������ȴ�����
		}
	}
	//midcode("sw","$ra","0","$sp");
	//midcode("addi","$sp",sizefunctemp,"$sp");
	midcode("addi","$sp","-1024","$sp");
	addr = 4;
	addr2 = 0;
	for(i = 0;i<paranum; i++){
		addr =addr -4;//��һ�������ĵ�ַ
		addr2 = addr2 +4;
		itoa(addr,addre,10);
		itoa(addr2,addre2,10);
		midcode("lw","$t0",addre,"$a1");
		midcode("sw","$t0",addre2,"$sp");
	}
	midcode("addi","$sp","1024","$sp");
	midcode("-","$a1",sizepar,"$a1");
}
void StateList(){   //������У�   ::= ������䣾��      
	while(strcmp(va,"if")==0 || strcmp(va,"for")==0 || strcmp(va,"{")==0 || strcmp(va,"for")==0 || strcmp(va,"scanf")==0 || strcmp(va,"printf")==0

		|| strcmp(va,"for")==0 || strcmp(va,"switch")==0 || strcmp(va,"return")==0 || strcmp(va,";")==0 ||(strcmp(va2,"=")==0 ||strcmp(va2,"[")==0) || strcmp(va2,"(")==0 ){
	Sentence();
                                                                                                                                                                                                                                                         	} 
}
void ScanfState(){   //<�����> ::= scanf'('<��ʶ��>{,<��ʶ��>}')'
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
void PrintfState(){    //��д��䣾::= printf ��(�� ���ַ�����,�����ʽ�� ��)��| printf ��(�����ַ����� ��)��| printf ��(�������ʽ����)��
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

		midcode("la1","$a0","0");//ִ����һ��д�����������
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
void ReturnState(){    //��������䣾   ::=  return[��(�������ʽ����)��]  
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
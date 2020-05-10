void objectmain();
void findTable();
void object1();
void object2();
void ascii();
void add();
void assign();
void sub();
void mul();
void div();
void li();
void lw();
void lw1();
void sw1();
void blt();
void ble();
void bgt();
void bge();
void bne();
void beq();
void printflabel();
void j();
void jal();
void jr();
void syscall();
void move();
void la1();
void la();
char num1[20], num2[20], num3[20], num4[20];
FILE *Object;
int midlocat = 0;
int golbal =0;
int flagassign = 0;
char idenassign[20];
int flagfunc = 0;
int flagarray = 0;
int para  =0;//表示一个函数的个数
int sizefun = 0;
int flagopnum = 0;
int flagconst = 1;
//int flagfunction = 0;
void objectmain(){
	Object = fopen("Object.txt","w");
	object1();
	object2();
	fclose(Object);
}
void findTable(){//遍历符号表为常量和变量固定自己的物理位置
	int arraysize;
	Table *l;
	l = u;
	while(l->lev == 0){
		if(l->kind == 1){//常量
			fprintf(Object,"	%s:    .word    %d\n",l->name,l->value);
			l = l->next;
		}
		else if(l->kind == 2){//变量
			fprintf(Object,"	%s:    .space    4\n",l->name);
			l = l->next;
		}
		else if(l->kind == 4){//数组
			arraysize = l->value *4;
			fprintf(Object,"	%s:    .space    %d\n",l->name,arraysize);
			l = l->next;
		}
		else
			l = l->next;
	}
	fprintf(Object,"	parastack:    .space    10000\n");//在数据段存函数的参数
	fprintf(Object,"	opnumstack:    .space    10000\n");//在数据段存表达式的因子，方便运算
}
int InTableAddress(char *va){//遇到变量的时候扫描符号表，返回地址
	int address = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){
		if(strcmp(va,cur->name)==0){
			address = cur->address;
			golbal =0;
			return address;//若存在，返回其值
		}
		else
			cur = cur->next;
	}
	return 0;
}

int InTableFunSize(char *va){//遇到变量的时候扫描符号表，返回其所需空间
	int sizefunc = 0;
	int lev =0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){
		if(strcmp(va,cur->name)==0){
			lev = cur->lev;
			while(lev == cur->lev){
				sizefunc = cur ->address;
				cur = cur->next;
			}
			return sizefunc;
		}
		else
			cur = cur->next;
	}
	return 0;
}


int InTableParanum(char *va){//遇到变量的时候扫描符号表，返回参数个数
	int num = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){
		if(strcmp(va,cur->name) == 0){
			cur = cur->next;
			while(cur->kind == 3){
				num = num +1;
				cur = cur->next;
			}
			return num;//若存在，返回其参数个数
		}
		else
			cur = cur->next;
	}
	return 0;
}








int InTableType(char *va,int lev){//遇到变量的时候扫描符号表，返回其类型
	int type = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){//先扫描同一层次
		if(lev > cur->lev){
			cur = cur->next;
			continue;
		}
		else if(cur->lev == lev){
			if(strcmp(va,cur->name)==0){
				type = cur->type;
				return type;//若存在，返回其类型
			}
			else
				cur = cur->next;
		}
		else if(cur->lev >lev)
			break;
	}
	cur = u;//再扫一遍，只扫第0层的全局变量
	while(cur->next != NULL){
		if(cur->lev != 0)//如果第一次！=0说明没有全局变量的声明，直接退出即可，当扫描完第0层后也退出
			break;
		else if(cur->lev == 0){
			if(strcmp(va,cur->name)==0){
				type = cur->type;
				return type;//若存在，返回其类型
			}
			else
				cur = cur->next;
		}
	}
	return 0;
}


















int InTableAddress(char *va,int lev){//遇到变量的时候扫描符号表，返回其地址
	int address = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){//先扫描同一层次
		if(lev > cur->lev){
			cur = cur->next;
			continue;
		}
		else if(cur->lev == lev){
			if(strcmp(va,cur->name)==0){
				address = cur->address;
				golbal =0;
				return address;//若存在，返回其地址
			}
			else
				cur = cur->next;
		}
		else if(cur->lev >lev)
			break;
	}
	cur = u;//再扫一遍，只扫第0层的全局变量
	while(cur->next != NULL){
		if(cur->lev != 0)//如果第一次！=0说明没有全局变量的声明，直接退出即可，当扫描完第0层后也退出
			break;
		else if(cur->lev == 0){
			if(strcmp(va,cur->name)==0){
				address = cur->address;
				// 
				midcode("la","$a0",cur->name);
				golbal =1;
				return address;//若存在，返回其地址
			}
			else
				cur = cur->next;
		}
	}
	return 0;
}
int InTableValue(char *va){//遇到变量的时候扫描符号表，返回value
	int value = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){
		if(strcmp(va,cur->name)==0){
			value = cur->value;
			return value;//若存在，返回其值
		}
		else
			cur = cur->next;
	}
	return 0;
}
void object1(){//数据段
	midlocat = 0;
	fprintf(Object,".data\n");
	findTable();
	fprintf(Object,"	string0: .asciiz \"\\n\" \n");
	while(midlocat < local){
		if(strcmp(mcode[midlocat].numb1,"Ascii")==0)
			ascii();
		midlocat ++;
	}
}
void object2(){//代码段
	midlocat = 0;
	fprintf(Object,".text\n");
	while(midlocat < local){
		if(strcmp(mcode[midlocat].numb1,"+")==0|| strcmp(mcode[midlocat].numb1,"addi")==0)//在for循环里将addi和sub写死的缘故
			add();
		else if(strcmp(mcode[midlocat].numb1,"-")==0 || strcmp(mcode[midlocat].numb1,"sub")==0)
			sub();
		else if(strcmp(mcode[midlocat].numb1,"*")==0)
			mul();
		else if(strcmp(mcode[midlocat].numb1,"/")==0)
			div();
		else if(strcmp(mcode[midlocat].numb1,"=")==0)
			assign();//赋值语句
		else if(strcmp(mcode[midlocat].numb1,"blt")==0)
			blt();
		else if(strcmp(mcode[midlocat].numb1,"ble")==0)
			ble();
		else if(strcmp(mcode[midlocat].numb1,"bgt")==0)
			bgt();
		else if(strcmp(mcode[midlocat].numb1,"bge")==0)
			bge();
		else if(strcmp(mcode[midlocat].numb1,"bne")==0)
			bne();
		else if(strcmp(mcode[midlocat].numb1,"beq")==0)
			beq();
		else if(strcmp(mcode[midlocat].numb2,":")==0)
			printflabel();
		else if(strcmp(mcode[midlocat].numb1,"j")==0)     
			j();
		else if(strcmp(mcode[midlocat].numb1,"call")==0)
			jal();
		else if(strcmp(mcode[midlocat].numb1,"jr")==0)
			jr();
		else if(strcmp(mcode[midlocat].numb1,"li")==0)
			li();
		else if(strcmp(mcode[midlocat].numb1,"lw1")==0)
			lw1();
		else if(strcmp(mcode[midlocat].numb1,"lw")==0)
			lw();
		else if(strcmp(mcode[midlocat].numb1,"sw")==0)
			sw1();
		else if(strcmp(mcode[midlocat].numb1,"syscall")==0)
			syscall();
		else if(strcmp(mcode[midlocat].numb1,"move")==0)
			move();
		else if(strcmp(mcode[midlocat].numb1,"la1")==0)
			la1();
		else if(strcmp(mcode[midlocat].numb1,"la")==0)
			la();
		midlocat ++;
	}
}
void ascii(){
	fprintf(Object,"	string%s: .asciiz %s\n",mcode[midlocat].numb3,mcode[midlocat].numb2);
}
void add(){
	if(strcmp(mcode[midlocat].numb1,"addi")==0)
		fprintf(Object,"	addi,%s,%s,%s\n",mcode[midlocat].numb4,mcode[midlocat].numb2,mcode[midlocat].numb3);
	else
		fprintf(Object,"	add,%s,%s,%s\n",mcode[midlocat].numb4,mcode[midlocat].numb2,mcode[midlocat].numb3);
}


void assign(){
	fprintf(Object,"	sw %s,(%s)\n",mcode[midlocat].numb3,mcode[midlocat].numb2);
}

void sub(){
	fprintf(Object,"	sub,%s,%s,%s\n",mcode[midlocat].numb4,mcode[midlocat].numb2,mcode[midlocat].numb3);
} 
void mul(){
	fprintf(Object,"	mul,%s,%s,%s\n",mcode[midlocat].numb4,mcode[midlocat].numb2,mcode[midlocat].numb3);
}
void div(){
	fprintf(Object,"	div,%s,%s,%s\n",mcode[midlocat].numb4,mcode[midlocat].numb2,mcode[midlocat].numb3);
}
void li(){
	fprintf(Object,"	li %s,%s\n",mcode[midlocat].numb2,mcode[midlocat].numb3);
}
void lw1(){
	fprintf(Object,"	lw %s,(%s)\n",mcode[midlocat].numb2,mcode[midlocat].numb3);
}
void lw(){
	fprintf(Object,"	lw %s,%s(%s)\n",mcode[midlocat].numb2,mcode[midlocat].numb3,mcode[midlocat].numb4);
}
void sw1(){
	fprintf(Object,"	sw %s,%s(%s)\n",mcode[midlocat].numb2,mcode[midlocat].numb3,mcode[midlocat].numb4);
}
void blt(){
	fprintf(Object,"	%s,%s,%s,%s\n",mcode[midlocat].numb1,mcode[midlocat].numb2,mcode[midlocat].numb3,mcode[midlocat].numb4);
	fprintf(Object,"	nop\n");
}
void ble(){
	fprintf(Object,"	%s,%s,%s,%s\n",mcode[midlocat].numb1,mcode[midlocat].numb2,mcode[midlocat].numb3,mcode[midlocat].numb4);
	fprintf(Object,"	nop\n");
}
void bgt(){
	fprintf(Object,"	%s,%s,%s,%s\n",mcode[midlocat].numb1,mcode[midlocat].numb2,mcode[midlocat].numb3,mcode[midlocat].numb4);
	fprintf(Object,"	nop\n");
}
void bge(){
	fprintf(Object,"	%s,%s,%s,%s\n",mcode[midlocat].numb1,mcode[midlocat].numb2,mcode[midlocat].numb3,mcode[midlocat].numb4);
	fprintf(Object,"	nop\n");
}
void bne(){
	fprintf(Object,"	%s,%s,%s,%s\n",mcode[midlocat].numb1,mcode[midlocat].numb2,mcode[midlocat].numb3,mcode[midlocat].numb4);
	fprintf(Object,"	nop\n");
}
void beq(){
	fprintf(Object,"	%s,%s,%s,%s\n",mcode[midlocat].numb1,mcode[midlocat].numb2,mcode[midlocat].numb3,mcode[midlocat].numb4);
	fprintf(Object,"	nop\n");
}
void printflabel(){
	fprintf(Object,"%s%s\n",mcode[midlocat].numb1,mcode[midlocat].numb2);
}
void j(){
	fprintf(Object,"	j %s\n",mcode[midlocat].numb2);
	fprintf(Object,"	nop\n");
}
void jal(){
	fprintf(Object,"	jal %s\n",mcode[midlocat].numb2);
	fprintf(Object,"	nop\n");
}
void jr(){
	fprintf(Object,"	jr %s\n",mcode[midlocat].numb2);
	fprintf(Object,"	nop\n");
}
void syscall(){
	fprintf(Object,"	syscall\n");
}
void move(){
	fprintf(Object,"	move %s,%s\n",mcode[midlocat].numb2,mcode[midlocat].numb3);
}
void la1(){
	fprintf(Object,"	la %s,string%s\n",mcode[midlocat].numb2,mcode[midlocat].numb3);
}
void la(){
	fprintf(Object,"	la %s,%s\n",mcode[midlocat].numb2,mcode[midlocat].numb3);
}



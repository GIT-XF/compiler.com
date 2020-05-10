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
void la();
char num1[20], num2[20], num3[20], num4[20];
FILE *Object;
int midlocat = 0;
void objectmain(){
	Object = fopen("Object.txt","w");
	object1();
	object2();
	fclose(Object);
}
void findTable(){//�������ű�Ϊ�����ͱ����̶��Լ�������λ��
	Table *l;
	l = u;
	while(l->next != NULL){
		if(l->kind == 1){
			fprintf(Object,"	li $t0,%d\n",l->address);//��ȡ��ַ
			fprintf(Object,"	li $t1,%d\n",l->value);//����Ӧ��ֵ������Ӧ�ĵ�ַ
			fprintf(Object,"	sw $t1,($t0)\n");
			l = l->next;
		}
		else
			l = l->next;
	}
}
int InTableAddress(char *va){//����������ʱ��ɨ����ű����ص�ַ
	int address = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){
		if(strcmp(va,cur->name)==0){
			address = cur->address;
			return address;//�����ڣ�������ֵ
		}
		else
			cur = cur->next;
	}
	return 0;
}
//int InTableAddress(int lev){//����������ʱ��ɨ����ű����ص�ַ
//	int address = 0;
//	Table *cur;
//	cur = u;
//	while(cur->next != NULL){
//		if(lev ==cur->lev){
//			address = cur->address;
//			return address;//�����ڣ�������ֵ
//		}
//		else
//			cur = cur->next;
//	}
//	return 0;
//}








int InTableType(char *va,int lev){//����������ʱ��ɨ����ű�����������
	int type = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){//��ɨ��ͬһ���
		if(lev > cur->lev){
			cur = cur->next;
			continue;
		}
		else if(cur->lev == lev){
			if(strcmp(va,cur->name)==0){
				type = cur->type;
				return type;//�����ڣ�����������
			}
			else
				cur = cur->next;
		}
		else if(cur->lev >lev)
			break;
	}
	cur = u;//��ɨһ�飬ֻɨ��0���ȫ�ֱ���
	while(cur->next != NULL){
		if(cur->lev != 0)//�����һ�Σ�=0˵��û��ȫ�ֱ�����������ֱ���˳����ɣ���ɨ�����0���Ҳ�˳�
			break;
		else if(cur->lev == 0){
			if(strcmp(va,cur->name)==0){
				type = cur->type;
				return type;//�����ڣ�����������
			}
			else
				cur = cur->next;
		}
	}
	return 0;
}


















int InTableAddress(char *va,int lev){//����������ʱ��ɨ����ű��������ַ
	int address = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){//��ɨ��ͬһ���
		if(lev > cur->lev){
			cur = cur->next;
			continue;
		}
		else if(cur->lev == lev){
			if(strcmp(va,cur->name)==0){
				address = cur->address;
				return address;//�����ڣ��������ַ
			}
			else
				cur = cur->next;
		}
		else if(cur->lev >lev)
			break;
	}
	cur = u;//��ɨһ�飬ֻɨ��0���ȫ�ֱ���
	while(cur->next != NULL){
		if(cur->lev != 0)//�����һ�Σ�=0˵��û��ȫ�ֱ�����������ֱ���˳����ɣ���ɨ�����0���Ҳ�˳�
			break;
		else if(cur->lev == 0){
			if(strcmp(va,cur->name)==0){
				address = cur->address;
				return address;//�����ڣ��������ַ
			}
			else
				cur = cur->next;
		}
	}
	return 0;
}
int InTableValue(char *va){//����������ʱ��ɨ����ű�����value
	int value = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){
		if(strcmp(va,cur->name)==0){
			value = cur->value;
			return value;//�����ڣ�������ֵ
		}
		else
			cur = cur->next;
	}
	return 0;
}
void object1(){//���ݶ�
	midlocat = 0;
	fprintf(Object,".data\n");
	fprintf(Object,"	string0: .asciiz \"\\n\" \n");
	while(midlocat < local){
		if(strcmp(mcode[midlocat].numb1,"Ascii")==0)
			ascii();
		midlocat ++;
	}
}
void object2(){//�����
	midlocat = 0;
	fprintf(Object,".text\n");
	findTable();
	while(midlocat < local){
		if(strcmp(mcode[midlocat].numb1,"+")==0|| strcmp(mcode[midlocat].numb1,"addi")==0)//��forѭ���ｫaddi��subд����Ե��
			add();
		else if(strcmp(mcode[midlocat].numb1,"-")==0 || strcmp(mcode[midlocat].numb1,"sub")==0)
			sub();
		else if(strcmp(mcode[midlocat].numb1,"*")==0)
			mul();
		else if(strcmp(mcode[midlocat].numb1,"/")==0)
			div();
		else if(strcmp(mcode[midlocat].numb1,"=")==0)
			assign();//��ֵ���
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
		else if(strcmp(mcode[midlocat].numb1,"lw")==0)
			lw();
		else if(strcmp(mcode[midlocat].numb1,"lw1")==0)
			lw1();
		else if(strcmp(mcode[midlocat].numb1,"sw")==0)
			sw1();
		else if(strcmp(mcode[midlocat].numb1,"syscall")==0)
			syscall();
		else if(strcmp(mcode[midlocat].numb1,"move")==0)
			move();
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
void lw(){
	fprintf(Object,"	lw %s,(%s)\n",mcode[midlocat].numb2,mcode[midlocat].numb3);
}
void lw1(){
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
void la(){
	fprintf(Object,"	la %s,string%s\n",mcode[midlocat].numb2,mcode[midlocat].numb3);
}



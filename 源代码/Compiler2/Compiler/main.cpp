#include<stdio.h>  //feof 若文件未结束返回0；
#include<string.h> //需要字符数组时需要  strlen  strcmp  strcpy
#include<stdlib.h> //malloc  free  
#include "Error.h"
#include "World.h"
#include "Syntax.h"
#define size 20
int main (){
	strcpy(opnum[0].num,"#");
	strcpy(opstack[0],"#");
	strcpy(resul[1],"$t0");
	strcpy(resul[2],"$t1");
	strcpy(resul[3],"$t2");
	strcpy(resul[4],"$t3");
	strcpy(resul[5],"$t4");
	strcpy(resul[6],"$t5");
	strcpy(resul[7],"$t6");
	strcpy(resul[8],"$t7");
	strcpy(resul[9],"$s1");
	strcpy(resul[10],"$s2");
	strcpy(resul[11],"$s3");
	strcpy(resul[12],"$s4");
	strcpy(resul[13],"$s5");
	strcpy(resul[14],"$s6");
	strcpy(resul[15],"$s7");
	/////////////////////////////////////////关系符   //<|<=|>|>=|!=|==
	strcpy(Label[1],"Label_1");
	strcpy(Label[2],"Label_2");
	strcpy(Label[3],"Label_3");
	strcpy(Label[4],"Label_4");
	strcpy(Label[5],"Label_5");
	strcpy(Label[6],"Label_6");
	strcpy(Label[7],"Label_7");
	strcpy(Label[8],"Label_8");
	strcpy(Label[9],"Label_9");
	strcpy(Label[10],"Label_10");
	strcpy(Label[11],"Label_11");
	strcpy(Label[12],"Label_12");
	strcpy(Label[13],"Label_13");
	strcpy(Label[14],"Label_14");
	strcpy(Label[15],"Label_15");
	strcpy(Label[16],"Label_16");
	strcpy(Label[17],"Label_17");
	strcpy(Label[18],"Label_18");
	strcpy(Label[19],"Label_19");
	strcpy(Label[20],"Label_20");
	strcpy(Label[21],"Label_21");
	strcpy(Label[22],"Label_22");
	strcpy(Label[23],"Label_23");
	strcpy(Label[24],"Label_24");
	strcpy(Label[25],"Label_25");
	strcpy(Label[26],"Label_26");
	strcpy(Label[27],"Label_27");
	strcpy(Label[28],"Label_28");
	strcpy(Label[29],"Label_29");
	strcpy(Label[30],"Label_30");
	strcpy(Label[31],"Label_31");
	strcpy(Label[32],"Label_32");
	strcpy(Label[33],"Label_33");
	strcpy(Label[34],"Label_34");
	strcpy(Label[35],"Label_35");
	strcpy(Label[36],"Label_36");
	strcpy(Label[37],"Label_37");
	strcpy(Label[38],"Label_38");
	strcpy(Label[39],"Label_39");
	strcpy(Label[40],"Label_40");
	strcpy(Label[41],"Label_41");
	strcpy(Label[42],"Label_42");
	strcpy(Label[43],"Label_43");
	strcpy(Label[44],"Label_44");
	strcpy(Label[45],"Label_45");
	strcpy(Label[46],"Label_46");
	strcpy(Label[47],"Label_47");
	strcpy(Label[48],"Label_48");
	strcpy(Label[49],"Label_49");
	strcpy(Label[50],"Label_50");
	strcpy(Label[51],"Label_51");
	strcpy(Label[52],"Label_52");
	strcpy(Label[53],"Label_53");
	strcpy(Label[54],"Label_54");
	strcpy(Label[55],"Label_55");
	strcpy(Label[56],"Label_56");
	strcpy(Label[57],"Label_57");
	strcpy(Label[58],"Label_58");
	strcpy(Label[59],"Label_59");
	strcpy(Label[60],"Label_60");
	strcpy(Label[61],"Label_61");
	strcpy(Label[62],"Label_62");
	strcpy(Label[63],"Label_63");
	strcpy(Label[64],"Label_64");
	strcpy(Label[65],"Label_65");
	strcpy(Label[66],"Label_66");
	strcpy(Label[67],"Label_67");
	strcpy(Label[68],"Label_68");
	strcpy(Label[69],"Label_69");
	strcpy(Label[70],"Label_70");
	FILE *fp;
	FILE *OutWorld;
	char filename[80]={0};
	scanf("%s",&filename);
	fp = fopen(filename,"r");
	OutWorld = fopen("OutWorld.txt","w");
	Midcode = fopen("MidCode.txt","w");
	if(fp == NULL){
		error(1);
		return 0;
	}
	c = fgetc(fp);
	if(c == EOF){
		error(2);
		return 0;
	}
	world[tempp].count = line1;
	strcpy(world[tempp].symbol,"0");
	//////////////////////////////////////// 符号表
	u = v = w = (struct table *)malloc(sizeof(struct table));
	v->name = (char *)malloc(max);
	v->type = 0;
	v->kind = 0;
	v->address =0;
	v->value =0;
	v->lev =0;
	v->next = NULL;
	///////////////////////////////////////////////中间代码
	while(true){
		while(c==' '|| c == '\n' || c == '\t'){
			if(c=='\n'){
				line1++;
				world[tempp].count = line1;//当读到换行符的时候更新count
			}
			c = fgetc(fp);
		}
		if(c == EOF){
			strcpy(world[tempp].symbol,"0");
			break;
		}
		if((c>='a' && c<= 'z') || (c>='A' && c<='Z') || (c =='_')){
			IsIDEN(fp);
			strcpy(world[tempp].value,va);
			strcpy(world[tempp].symbol,sym);
			intialize(va);
		}
		else if (c>='0' && c<='9'){
			IsDidit(fp);
			strcpy(world[tempp].value,va);
			strcpy(world[tempp].symbol,sym);
			intialize(va);
		}
		else{
			IsOP(fp);
			strcpy(world[tempp].value,va);
			strcpy(world[tempp].symbol,sym);
			intialize(va);
		}
		if((feof(fp)!=0)){
			break;
		}
		world[tempp].count = line1;
		tempp++;
	}
	Out(OutWorld);
	fclose(fp);
	fclose(OutWorld);
	getsym();
	Procedure();
	outtable();
	fclose(Midcode);
	//fclose(Object);
	objectmain();//调用目标函数
	printf("END");
}
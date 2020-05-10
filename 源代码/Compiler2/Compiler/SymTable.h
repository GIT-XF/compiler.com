#define max 1024
typedef struct table{
    char *name ; //name of identifier
    int kind;//1-const 2-var 3-para,4-array
    int type; //1-int,2-char,3-void,5-function;
	int value;//常量的值，数组的大小
	int address ;//标识符存储地址或者地址位移
	int lev;
	struct table *next;
}Table;
Table *u, *v, *w;
char name[max];
int type = 0;
int kind = 0;
int value = 0;
int address = 268435456;//常变量地址从4096开始
int addres = 448;//现场保护开始地址
int lev = 0;

void insert();
int search();
void outtable();

void insert(){
	strcpy(v->name,name);
	v->type = type;
	v->kind = kind;
	v->value = value;
	v->address =address;
	v->lev =lev;
	
	w = (struct table *)malloc(sizeof(struct table));//建立一个新结点
	w->next = NULL;
	w->name = (char *)malloc(max);
	w->type = 0;
	w->kind = 0;
	w->value = 0;
	w->address =0;
	w->lev =0;
	v->next = w;//指向新结点
	v = v->next;
	
}
int search(){//符号表的内容检擦
	Table *o;
	o = u;
	while(o->next != NULL){
		if(lev > o->lev){
			o = o->next;
			continue;
		}
		else{//也就是等于的时候
			if(strcmp(name,o->name)==0){
				error(21);
				return 0;//表示同一层次重复申明；
			}
			else
				o = o->next;
		}
	}
	return 1;
}
void outtable(){
	FILE *outtable;
	outtable = fopen("OutTable.txt","w");
	Table *m;
	m = u;
	fprintf(outtable,"       name      kind        type       value       address       lev\n");
	fprintf(outtable,"_____________________________________________________________________________________\n");
	while(m->next != NULL){
		//printf("%10s %10d %10d %10d %10d %10d \n",m->name,m->kind,m->type,m->value,m->address,m->lev);
		fprintf(outtable,"%10s %10d %10d %10d %10d %10d \n",m->name,m->kind,m->type,m->value,m->address,m->lev);
		m = m->next;
	}
	fclose(outtable);
}
int NotInTable(char *va){
	int curlev = lev;//获取当前层次
	int retu = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){//先扫描同一层次
		if(curlev > cur->lev){
			cur = cur->next;
			continue;
		}
		else{//也就是等于的时候
			if(strcmp(va,cur->name)==0){
				return 0;//表示变量已在符号表中找到，返回退出；
			}
			else
				cur = cur->next;
		}
	}
	cur = u;//再扫一遍
	while(cur->next != NULL){
		if(cur->lev != 0)//如果第一次！=0说明没有全局变量的声明，直接退出即可
			break;
		else{
			if(strcmp(va,cur->name)==0){
				return 0;//表示同一层次重复申明；
			}
			else
				cur = cur->next;
		}
	}
	printf("ERROR: '%s' ",va);
	return 1;
}
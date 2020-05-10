#define max 1024
typedef struct table{
    char *name ; //name of identifier
    int kind;//1-const 2-var 3-para,4-array
    int type; //1-int,2-char,3-void,5-function;
	int value;//������ֵ������Ĵ�С
	int address ;//��ʶ���洢��ַ���ߵ�ַλ��
	int lev;
	struct table *next;
}Table;
Table *u, *v, *w;
char name[max];
int type = 0;
int kind = 0;
int value = 0;
int address = 0;//��������ַ��4096��ʼ
//int addres = 448;//�ֳ�������ʼ��ַ
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
	
	w = (struct table *)malloc(sizeof(struct table));//����һ���½��
	w->next = NULL;
	w->name = (char *)malloc(max);
	w->type = 0;
	w->kind = 0;
	w->value = 0;
	w->address =0;
	w->lev =0;
	v->next = w;//ָ���½��
	v = v->next;
	
}
int search(){//���ű�����ݼ��
	Table *o;
	o = u;
	while(o->next != NULL){
		if(lev > o->lev){
			o = o->next;
			continue;
		}
		else{//Ҳ���ǵ��ڵ�ʱ��
			if(strcmp(name,o->name)==0){
				error(21);
				return 0;//��ʾͬһ����ظ�������
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
	int curlev = lev;//��ȡ��ǰ���
	int retu = 0;
	Table *cur;
	cur = u;
	while(cur->next != NULL){//��ɨ��ͬһ���
		if(curlev > cur->lev){
			cur = cur->next;
			continue;
		}
		else{//Ҳ���ǵ��ڵ�ʱ��
			if(strcmp(va,cur->name)==0){
				return 0;//��ʾ�������ڷ��ű����ҵ��������˳���
			}
			else
				cur = cur->next;
		}
	}
	cur = u;//��ɨһ��
	while(cur->next != NULL){
		if(cur->lev != 0)//�����һ�Σ�=0˵��û��ȫ�ֱ�����������ֱ���˳�����
			break;
		else{
			if(strcmp(va,cur->name)==0){
				return 0;//��ʾͬһ����ظ�������
			}
			else
				cur = cur->next;
		}
	}
	printf("ERROR: '%s' ",va);
	return 1;
}
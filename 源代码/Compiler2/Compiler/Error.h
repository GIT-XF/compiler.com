extern int line2;
void error(int m);
void error(int m){
	switch(m){
	case 1 : printf("ERROR: open file error!\n"); //文件打开错误
		break;
	case 2 : printf("ERROR: The file is empty!\n");//当文件是一个空文件的时候，输出错误提醒
		break;
	case 3 : printf("ERROR: IDEN is too long\n");//
		break;
	case 4 : printf("ERROR: Number is too long\n");
		break;
	case 5 : printf("ERROR: Undefined characters.\n");//当程序识别到其不能判断的字符时，提醒其不能识别这个字符
		break;
		
	case 6 : printf("ERROR: Expect a '(' in %d line.\n",line2);
		break;
	case 7 : printf("ERROR: Expect a ')' in %d line.\n",line2);
		break;
	case 8 : printf("ERROR: Expect a '[' in %d line.\n",line2);
		break;
	case 9 : printf("ERROR: Expect a ']' in %d line.\n",line2);
		break;	
	case 10: printf("ERROR: Expect a '{' in %d line.\n",line2);
		break;
	case 11: printf("ERROR: Expect a '}' in %d line.\n",line2);
		break;		
	case 12: printf("ERROR: Expect a '=' in %d line.\n",line2);
		break;
	case 13: printf("ERROR: Expect a ''' in %d line.\n",line2);
		break;
	case 14: printf("ERROR: Expect a '\"' in %d line.\n",line2);
		break;
	case 15: printf("ERROR: Expect a ';' in %d line.\n",line2);
		break;
	case 16: printf("ERROR: Expect a ':' in %d line.\n",line2);
		break;
	case 17: printf("ERROR: Illega character in %d line.\n",line2);
		break;
	case 18: printf("ERROR: Illega Ascii in %d line.\n",line2);
		break;
	case 19: printf("ERROR: Expect a UnsignedInt in %d line.\n",line2);
		break;
		
	case 20: printf("ERROR: There is a error in %d line.\n",line2);
		break;
	case 21: printf("ERROR: Parameter repetition declaration in %d line.\n",line2);
		break;
	case 22: printf("NOT in symtable  %d line.\n",line2);
		break;
	default :printf("Unknown error number!\n");//当调用error函数的时候可能输错编号，便提醒未知的错误编号
	}
}
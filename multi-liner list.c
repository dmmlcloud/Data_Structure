#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define SPEC 2
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; 

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define MENU_INIT_SIZE 20
#define NAME_MAX_SIZE 20

typedef struct SQlist{  
	ElemType * elem;
	int length;
	int listsize;
}SqList;

typedef struct MenuName
{
	char name[NAME_MAX_SIZE];
	SqList *lists;
}MenuName;

typedef struct Menu{
	MenuName menuname[MENU_INIT_SIZE];
	int length;
	int menusize; 	 	
}Menu; 

status FindList(Menu M, char name[NAME_MAX_SIZE], int *e);
status IntiaMenu(Menu *M);
status IntiaList(SqList *L);
status DestroyMenu(Menu *M);
status DestroyList(SqList *L);
int MenuLength(Menu M);
status MenuTrabverse(Menu M);
status ClearList(SqList *L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType *e);
int LocateElem(SqList L,ElemType e,status (*Compare) (ElemType x,ElemType y)); 
status PriorElem(SqList L,ElemType cur,ElemType *pre_e);
status NextElem(SqList L,ElemType cur,ElemType *next_e);
status ListInsert(SqList *L,int i,ElemType e);
status ListDelete(SqList *L,int i,ElemType *e);
status ListTrabverse(SqList L);
status ClearMenu(Menu *M);
status Compare(ElemType x,ElemType y);
/*--------------------------------------------*/
void main(void){
    Menu M;  SqList L;  int op = 1, found = 1;
    FILE *fp;
	while(op)
	{	
		status flag, flag2;
		int e = 0, i = 0, loc = 0, cur_e = 0, pre_e = 0, next_e = 0;
		char name[NAME_MAX_SIZE];
		system("cls");	
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-----------------------------------------------------------\n");
		printf("    	  1. IntiaMenu         11. LocateElem\n");
		printf("    	  2. IntiaList         12. PriorElem\n");
		printf("    	  3. DestroyMenu       13. NextElem\n");
		printf("    	  4. DestroyList       14. ListInsert\n");
		printf("    	  5. MenuLength        15. ListDelete\n");
		printf("    	  6. MenuTrabverse     16. ListTrabverse\n");
		printf("    	  7. ClearList	       17. ClearMenu\n");
		printf("    	  8. ListEmpty         18. LoadData\n");
		printf("    	  9. ListLength        19. SaveData\n");
		printf("         10. GetElem            0. Exit\n"); 
		printf("-----------------------------------------------------------\n");
		printf("    请选择你的操作[0~19]:");
		scanf("%d",&op);
	    switch(op)
		{
		    case 1:
			 //IntiaMenu
				if(IntiaMenu(&M) == OK)
					printf("总线性表创建成功！\n");	
			    else 
					printf("总线性表创建失败！\n");
			 	getchar();
				getchar();
			 	break;
		    case 2:
			 //IntiaList     
			 	if(IntiaList(&L) == OK)
				{
					M.menuname[M.length].lists = &L;
					printf("请输入创建的线性表的名称：\n");
					scanf("%s",M.menuname[M.length].name);
					M.length++; 
					printf("线性表创建成功！\n");
					found = 0;	
				} 	
			    else 
					printf("线性表创建失败！\n");
			 	getchar();
				getchar();
			 	break;
		    case 3:
			 //DestroyMenu
				if(found || DestroyMenu(&M) == ERROR) 	
					printf("总线性表中无线性表！\n"); 	
				else 
					printf("销毁总线性表成功！\n");    
				getchar();
				getchar();
				break;
		    case 4:
			 //DestroyList
			 	if(found || M.menuname[0].lists== NULL) 	
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;
				}	
				printf("请输入想要销毁的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！\n");
				else 
				{
					DestroyList(M.menuname[e].lists);
					M.length--; 
					printf("销毁线性表成功！\n");	
				}	
				getchar();
				getchar();
				break;
		    case 5:
			 //MenuLength     
				if(found || M.menuname[0].lists == NULL)
					printf("总线性表中无线性表！\n");
				else
					printf("线性表中元素个数为 %d\n",MenuLength(M));
				getchar();
				getchar();
				break;
		    case 6:
			 //MenuTrabverse    
				if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}	
				if(!MenuTrabverse(M)) 
					printf("线性表是空表！\n");
				getchar();
				getchar();
				break;
		    case 7:
		     //ClearList
		     	if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
		     	printf("请输入想要清空的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！\n");	
				else 
				{
					ClearList(M.menuname[e].lists);
					printf("清空线性表成功！\n");	
				}
				getchar();
				getchar();
				break;
	 	    case 8:
	 	     //ListEmpty
				if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				printf("请输入查询的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！");	
				else
				{
					flag2 = ListEmpty(L);
					if(flag2 == OK) 	
						printf("线性表为空！\n");	
					else 
						printf("线性表不为空！\n") ;
				}  
				getchar();
				getchar();     
			 	break;
		    case 9:
			 //ListLength;
			   if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				printf("请输入查询的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！");	
			    else 
					printf("线性表中元素个数为 %d\n",ListLength(L));
				getchar();
				getchar();
				break;
		    case 10:
			 //GetElem    
				if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				printf("请输入查询的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！");	
				else
				{
					printf("请输入要查询的元素的位置：");
					scanf("%d",&i);
					flag2 = GetElem(L, i, &e);
					if(flag2 == ERROR) 	
						printf("输入位置有误!\n");
					else
						printf("线性表中第%d个元素为%d\n",i ,e);	    
				}
				getchar();
				getchar();
				break;
		    case 11:
		     //LocateElem
				if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				printf("请输入查询的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！");	
				else
				{
					printf("请输入要查询的元素："); 
					scanf("%d",&e);  
					loc = LocateElem(L,e,Compare);
					if(loc == ERROR)
						printf("线性表中无满足关系的元素!");
					else
						printf("线性表中与%d满足的关系的元素的位置为%d\n",e,loc);
				}	   
			 	getchar();
				getchar();
			 	break;
		    case 12:
			 //PriorElem
			    if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				printf("请输入查询的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！");	
				else
				{
					printf("请输入要查询的元素："); 
					scanf("%d",&cur_e);
					flag2 = PriorElem(L,cur_e,&pre_e);
					if(flag2 == ERROR)
						printf("该元素不在线性表中！\n");
					else if(flag2 == SPEC)
						printf("该元素为第一个元素，无前驱！\n");
					else
						printf("该元素在线性表中的前驱为%d\n",pre_e);
				}
			 	getchar();
				getchar();
			 	break;
			case 13:
			 //NextElem
			 	if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				printf("请输入查询的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！");	
				else
				{
					printf("请输入要查询的元素：");
					scanf("%d",&cur_e);  
					flag2 = NextElem(L,cur_e,&next_e);
					if(flag2 == ERROR)
						printf("该元素不在线性表中！\n");
					else if(flag2 == SPEC)
						printf("该元素为最后一个元素，无后继！\n");
					else
						printf("该元素在线性表中的后继为%d\n",next_e);
				}
				getchar();
				getchar();
				break;
			case 14:
			 //ListInsert
			    if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				printf("请输入查询的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！");	
				else
				{
					printf("请输入要插入的位置：");
					scanf("%d",&i);
					printf("请输入要插入的元素：");
					scanf("%d",&e);
					flag2 = ListInsert(&L, i, e);
					if(flag2 == ERROR)
						printf("插入失败，线性表已满无法插入！\n");
					else if(flag2 == SPEC)
						printf("插入失败，位置输入错误！\n") ;
					else
						printf("插入成功！\n");
				}
				getchar();
				getchar();
				break;
			case 15:
			 //ListDelete
			 	if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				printf("请输入查询的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！");	
				else
				{
					printf("请输入要删除的元素的位置：");
					scanf("%d",&i);
					flag2 = ListDelet(&L, i, &e);
					if(flag2 == ERROR)
						printf("删除失败，线性表为空无法删除！\n");
					else if(flag2 == SPEC)
						printf("删除失败，位置输入错误！\n") ;
					else
						printf("删除成功！删除的元素值为%d!\n",e);
				}
				getchar();
				getchar();
				break;
			case 16:
			 //ListTrabverse
			    if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				printf("请输入查询的线性表的名称：\n");
				scanf("%s",name);
				flag = FindList(M, name, &e);
				if(flag == ERROR)
					printf("未找到相应名称的线性表！");	
				else
				{
					if(!ListTrabverse(L)) 
						printf("线性表是空表！\n");
				}
				getchar();
				getchar();
				break;
			case 17:
			//ClearMenu
				if(found || ClearMenu(&M) == ERROR) 	
					printf("总线性表中无线性表！\n"); 	
				else 
					printf("清空线性表成功！\n");   
				getchar();
				getchar();
				break;
			case 18:
			 //LoadData
				if((fp = fopen("test.txt","r")) == NULL)
				{
					printf("文件无法打开!\n");
					getchar();
					getchar();
					break;
				}
				IntiaMenu(&M);
				fscanf(fp, "%d", &M.length);
				for(i = 0;i < M.length;i++)
				{
					IntiaList(&L);
					M.menuname[i].lists = &L;
				}
				found = 0;
				for(i = 0;i < M.length;i++)
				{
					fgets(M.menuname[i].name, NAME_MAX_SIZE, fp);
					strtok(M.menuname[i].name,"\n");
				}
					
				for(i = 0;i < M.length;i++)
					fscanf(fp, "%d", &M.menuname[i].lists->length);
				for(e = 0;e < M.length;e++)
				{
					for(i = 0;i < M.menuname[e].lists->length;i++)
						fscanf(fp, "%d", (M.menuname[e].lists->elem + i));
				}
				fclose(fp);
				printf("文件读取成功！\n");		
				getchar();
				getchar();
				break;
			case 19:
			 //SaveData
			 	if(found || M.menuname[0].lists == NULL)
				{
					printf("总线性表中无线性表！\n");
					getchar();
					getchar();
					break;	
				}
				if((fp = fopen("test.txt","w")) == NULL)
				{
					printf("文件无法打开!\n");
					getchar();
					getchar();
					break;
				}
				fprintf(fp, "%d", M.length);
				for(i = 0;i < M.length;i++)
					fprintf(fp, "%s\n", M.menuname[i].name);
				for(i = 0;i < M.length;i++)
					fprintf(fp, "%d ", M.menuname[i].lists->length);
				for(e = 0;e < M.length;e++)
				{
					for(i = 0;i < M.menuname[e].lists->length;i++)
						fprintf(fp, "%d ", *(M.menuname[e].lists->elem + i));
				}
				fclose(fp);	
				printf("文件保存成功！\n");
				getchar();
				getchar();
				break;	
		    case 0:
	         break;
		}//end of switch
   }//end of while
   
   printf("欢迎下次再使用本系统！\n");
}//end of main()
/*--------page 23 on textbook --------------------*/

status FindList(Menu M, char name[NAME_MAX_SIZE], int *e)
{
	int i = 0;
	for(;i < M.length;i++)
	{
		if(!strcmp(name,M.menuname[i].name))
		{
			*e = i;
			return OK;
		}
	}
	return ERROR;
}

status IntiaMenu(Menu *M)
{
	int i = 0;
	for(;i < MENU_INIT_SIZE;i++)
		M->menuname[i].lists = NULL;
	M->length = 0;
	M->menusize = MENU_INIT_SIZE;
	return OK;
}

status IntiaList(SqList *L)
{
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof (ElemType));
    if(!L->elem) 
		exit(OVERFLOW);
	L->length = 0;
    L->listsize = LIST_INIT_SIZE;
	return OK;
}

status DestroyMenu(Menu *M)
{
	int i = M->length - 1;
	if(M->menuname[0].lists == NULL)
		return ERROR;
	else
	{
		for(;i >= 0;i--)
			M->menuname[i].lists = NULL;
		M->length = 0;
		return OK; 	
	}
}

status DestroyList(SqList *L)
{
	if(L->elem == NULL)
		return ERROR;
	else
	{
		free(L->elem);
		L->elem = NULL;
		L->length = 0;
		return OK; 	
	}
}

int MenuLength(Menu M)
{
	return M.length;
}


status MenuTrabverse(Menu M)
{
    int i;
    printf("\n-----------all lists' names -----------------------\n");
	for(i=0;i<M.length;i++) 
		printf("%s ",M.menuname[i].name);
	printf("\n------------------ end ------------------------\n");
   	return M.length;
}

status ClearList(SqList *L)
{
	if(L->elem == NULL)
		return ERROR;
	else
	{
		L->length = 0;
		return OK; 	
	}
} 

status ListEmpty(SqList L)
{
	if(L.elem == NULL)
		return ERROR;
	else
	{
		if(L.length == 0)
			return OK;
		else
			return SPEC;
	}		
}

int ListLength(SqList L)
{
	return L.length;
}

status GetElem(SqList L,int i,ElemType *e)
{
	if(i < 1 || i > L.length)
		return ERROR;
	else 
	{
		*e = *(L.elem + i - 1);
		return OK;
	}
}

int LocateElem(SqList L,int e,status (*Compare)(ElemType x,ElemType y))
{
	int loc = 0;
	for(;loc < L.length;loc++)
	{
		if(Compare(*(L.elem + loc),e))
			return (loc + 1);	
	}
	return ERROR;		
}

status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e)
{
	int loc = 0;
	for(;loc < L.length;loc++)
	{
		if(*(L.elem + loc) == cur_e)
			{
				if(loc == 0)
					return SPEC;
				else
				{
					*pre_e = *(L.elem + loc - 1);
					return OK;	
				}
			}
	}
	return ERROR;
}

status NextElem(SqList L,ElemType cur_e,ElemType *next_e)
{
	int loc = 0;
	for(;loc < L.length;loc++)
	{
		if(*(L.elem + loc) == cur_e)
			{
				if(loc == (L.length - 1))
					return SPEC;
				else
				{
					*next_e = *(L.elem + loc + 1);
					return OK;	
				}
			}
	}
	return ERROR;
}

status ListInsert(SqList *L,int i,ElemType e)
{
	int loc = L->length;
	if(L->length == L->listsize)
		return ERROR;
	if(i < 1||i > L->length + 1)
		return	SPEC;
	while(loc >= i)
	{
		*(L->elem + loc) = *(L->elem + loc - 1);
		loc--;
	}
	*(L->elem + loc) = e;
	L->length++;
	return OK;
}

status ListDelet(SqList *L,int i,ElemType *e)
{
	int loc = i - 1;
	if(ListEmpty(*L) == OK)
		return ERROR;
	if(i < 1||i > L->length)
		return	SPEC;
	*e = *(L->elem + loc);
	while(loc < L->length - 1)
	{
		*(L->elem + loc) = *(L->elem + loc + 1);
		loc++;
	}
	L->length--;
	return OK;
}

status ListTrabverse(SqList L)
{
    int i;
    printf("\n-----------all elements -----------------------\n");
	for(i=0;i<L.length;i++) 
		printf("%d ",L.elem[i]);
	printf("\n------------------ end ------------------------\n");
   	return L.length;
}


status ClearMenu(Menu *M)
{
	if(M->menuname[0].lists == NULL)
		return ERROR;
	else
	{
		M->length = 0;
		return OK; 	
	}
} 

status Compare(ElemType x,ElemType y)
{
	if(x == y)
		return OK;
	else
		return ERROR;
}

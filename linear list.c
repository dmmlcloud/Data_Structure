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
typedef struct SQlist{  
	ElemType * elem;
	int length;
	int listsize;
}SqList;

status IntiaList(SqList *L);
status DestroyList(SqList *L);
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
status Compare(ElemType x,ElemType y);
/*--------------------------------------------*/
void main(void){
    SqList L;  int op = 1, found = 1;
    FILE *fp;
	while(op)
	{	
		status flag;
		int e = 0, i = 0, loc = 0, cur_e = 0, pre_e = 0, next_e = 0;
		system("cls");	
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. IntiaList       8. PriorElem\n");
		printf("    	  2. DestroyList     9. NextElem\n");
		printf("    	  3. ClearList      10. ListInsert\n");
		printf("    	  4. ListEmpty      11. ListDelete\n");
		printf("    	  5. ListLength     12. ListTrabverse\n");
		printf("    	  6. GetElem        13. SaveData\n");
		printf("    	  7. LocateElem     14. LoadData\n");
		printf("          0. Exit\n"); 
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~14]:");
		scanf("%d",&op);
	    switch(op)
		{
		    case 1:
				if(IntiaList(&L) == OK)
				{
					printf("线性表创建成功！\n");
					found = 0;	
				} 	
			    else 
					printf("线性表创建失败！\n");
			 	getchar();
				getchar();
			 	break;
		    case 2:   
			 	if(found || DestroyList(&L) == ERROR) 	
					printf("线性表不存在！\n");	
			    else 
					printf("销毁线性表成功！\n");
			 	getchar();
			 	getchar();
			 	break;
		    case 3:
				if(found || ClearList(&L) == ERROR) 	
					printf("线性表不存在！\n"); 	
				else 
					printf("清空线性表成功！\n");    
				getchar();
				getchar();
				break;
		    case 4:
				if(found)
				{
					printf("线性表不存在！\n");
					getchar();
					getchar();
					break;	
				}		
				flag = ListEmpty(L);
				if(flag == OK) 	
					printf("线性表为空！\n");	
				else if(flag == ERROR) 
					printf("线性表不存在！\n");
				else 
					printf("线性表不为空！\n") ;    
				getchar();
				getchar();     
			 	break;
		    case 5:   
				if(found || L.elem == NULL)
					printf("线性表不存在！\n");
				else
					printf("线性表中元素个数为 %d\n",ListLength(L));
				getchar();
				getchar();
				break;
		    case 6:
				if(found || L.elem == NULL)
				{
					printf("线性表不存在！\n");
					getchar();
					getchar();
					break;	
				}	
				printf("请输入要查询的元素的位置：");
				scanf("%d",&i);
				flag = GetElem(L, i, &e);
				if(flag == ERROR) 	
					printf("输入位置有误!\n");
				else
					printf("线性表中第%d个元素为%d\n",i ,e);	    
				getchar();
				getchar();
				break;
		    case 7:
				if(found || L.elem == NULL)
				{
					printf("线性表不存在！\n");
					getchar();
					getchar();
					break;	
				}	
				printf("请输入要查询的元素："); 
				scanf("%d",&e);  
				loc = LocateElem(L,e,Compare);
				if(loc == ERROR)
					printf("线性表中无满足关系的元素!");
				else
					printf("线性表中与%d满足的关系的元素的位置为%d\n",e,loc);	   
			 	getchar();
				getchar();
			 	break;
	 	    case 8:  
			 	if(found || L.elem == NULL)
				{
					printf("线性表不存在！\n");
					getchar();
					getchar();
					break;	
				}	
				printf("请输入要查询的元素："); 
				scanf("%d",&cur_e);
				flag = PriorElem(L,cur_e,&pre_e);
				if(flag == ERROR)
					printf("该元素不在线性表中！\n");
				else if(flag == SPEC)
					printf("该元素为第一个元素，无前驱！\n");
				else
					printf("该元素在线性表中的前驱为%d\n",pre_e);  
			 	getchar();
				getchar();
			 	break;
		    case 9:   
				if(found || L.elem == NULL)
				{
					printf("线性表不存在！\n");
					getchar();
					getchar();
					break;	
				}	
				printf("请输入要查询的元素：");
				scanf("%d",&cur_e);  
				flag = NextElem(L,cur_e,&next_e);
				if(flag == ERROR)
					printf("该元素不在线性表中！\n");
				else if(flag == SPEC)
					printf("该元素为最后一个元素，无后继！\n");
				else
					printf("该元素在线性表中的后继为%d\n",next_e);
			 	getchar();
				getchar();
			 	break;
		    case 10:  
				if(found || L.elem == NULL)
				{
					printf("线性表不存在！\n");
					getchar();
					getchar();
					break;	
				}	
				printf("请输入要插入的位置：");
				scanf("%d",&i);
				printf("请输入要插入的元素：");
				scanf("%d",&e);
				flag = ListInsert(&L, i, e);
				if(flag == ERROR)
					printf("扩充失败！\n");
				else if(flag == SPEC)
					printf("插入失败，位置输入错误！\n") ;
				else
					printf("插入成功！\n");
				getchar();
				getchar();
				break;
		    case 11:
				if(found || L.elem == NULL)
				{
					printf("线性表不存在！\n");
					getchar();
					getchar();
					break;	
				}	
				printf("请输入要删除的元素的位置：");
				scanf("%d",&i);
				flag = ListDelet(&L, i, &e);
				if(flag == ERROR)
					printf("删除失败，线性表为空无法删除！\n");
				else if(flag == SPEC)
					printf("删除失败，位置输入错误！\n") ;
				else
					printf("删除成功！删除的元素值为%d!\n",e);
				getchar();
				getchar();
				break;
		    case 12:
			    if(found || L.elem == NULL)
			    {
			    	printf("线性表不存在！\n");
			    	getchar();
			    	getchar();
					break;
				}
				if(!ListTrabverse(L)) 
					printf("线性表是空表！\n");
				getchar();
				getchar();
				break;
			case 13:
				if(found || L.elem == NULL)
				{
					printf("线性表不存在！\n");
					getchar();
					getchar();
					break;
				}
				if((fp = fopen("full.txt","w")) == NULL)
				{
					printf("文件无法打开!\n");
					break;
				}
				
				for(i = 0;i < L.length;i++)
					fprintf(fp, "%d", *(L.elem + i));
				fclose(fp);	
				printf("文件保存成功！\n");
				getchar();
				getchar();
				break;
			case 14:
				if((fp = fopen("full.txt","r")) == NULL)
				{
					printf("文件无法打开!\n");
					break;
				}
				if(found || L.elem == NULL)
				{
					flag = IntiaList(&L);
					found = 0;
				}
        		else
        			flag = ClearList(&L);
				if(flag)
				{
					i = 0;
					while(fscanf(fp, "%d", (L.elem + i)) == 1)
						i++;
					L.length = i;
	        		fclose(fp);
					printf("文件读取成功！\n");	
				}
				getchar();
				getchar();
				break;
		    case 0:
	         break;
		}
   }
   
   printf("欢迎下次再使用本系统！\n");
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
	if(i < 1||i > L->length + 1)
		return	SPEC;
	if((L->length + 1) > L->listsize)
		{
			ElemType *newbase;
			newbase = (ElemType *)realloc(L->elem,(++L->listsize) * sizeof(ElemType));
			if(newbase == NULL)
				return ERROR;
			L->elem = newbase;
			while(loc >= i)
			{
				*(L->elem + loc) = *(L->elem + loc - 1);
				loc--;
			}
			*(L->elem + loc) = e;
			L->length++;
			return OK;
		} 
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

status Compare(ElemType x,ElemType y)
{
	if(x > y)
		return OK;
	else
		return ERROR;
}

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define SPEC -2 

#define NAME_MAX_SIZE 20
#define TEL_MAX_SIZE 15
#define TREE_MAX_SIZE 200
#define TREE_NAME_SIZE 20
#define MENU_INIT_SIZE 50

typedef int status; 
typedef char ElemType1;
typedef char ElemType2;

typedef struct BiTNode{
	ElemType1 name[NAME_MAX_SIZE];
	ElemType2 tel[TEL_MAX_SIZE];
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode;

typedef struct MenuName
{
	char name[TREE_NAME_SIZE];
	BiTNode *bitree;
}MenuName;

typedef struct Menu{
	MenuName *menuname;
	int length;
	int menusize; 	 	
}Menu;

int flag = 0;
static int count = 0;
static char menu_name[TREE_NAME_SIZE];

#define LENG sizeof(BiTNode)

status InitBiTree(BiTNode **T);
status DestroyBiTree(BiTNode **T);
status CreateBiTree(BiTNode **T, ElemType1 definition[2][TREE_MAX_SIZE][NAME_MAX_SIZE]);
status ClearBiTree(BiTNode **T);
status BiTreeEmpty(BiTNode *T);
int BiTreeDepth(BiTNode *T);
BiTNode *Root(BiTNode *T);
ElemType2 *Value(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]);
status Assign(BiTNode *T, ElemType1 e[NAME_MAX_SIZE], ElemType2 value[TEL_MAX_SIZE]);
BiTNode *Parent(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]);
BiTNode *LeftChild(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]);
BiTNode *RightChild(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]);
BiTNode *LeftSibling(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]);
BiTNode *RightSibling(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]);
status InsertChild(BiTNode *T, BiTNode *p, int LR, BiTNode *c);
status DeleteChild(BiTNode *T, BiTNode *p, int LR);
status PreOrderTraverse(BiTNode *T,void (*Visit)(BiTNode *T));
status InOrderTraverse(BiTNode *T,void (*Visit)(BiTNode *T));
status PostOrderTraverse(BiTNode *T,void (*Visit)(BiTNode *T));
status LevelOrderTraverse(BiTNode *T,void (*Visit)(BiTNode *T));
void Visit(BiTNode *T);
BiTNode *Find(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]);
status Output(BiTNode *T, FILE *fp);
status MenuInsert(Menu *M, BiTNode *T, char name[TREE_NAME_SIZE]);
status NewBiTree(BiTNode **T);
int FindBiTree(Menu M, char name[TREE_NAME_SIZE]);
BiTNode *ChooseBiTree(Menu M, char name[TREE_NAME_SIZE]);
status MenuDelete(Menu *M, char name[TREE_NAME_SIZE]);

void main(void){
    int i = 0;
	Menu M;
	BiTNode *T;
	int op = 1, length;
    FILE *fp;
    ElemType1 definition[2][TREE_MAX_SIZE][NAME_MAX_SIZE];
    M.menuname = (MenuName *)malloc(MENU_INIT_SIZE * sizeof(MenuName));
	M.length = 0;
	M.menusize = MENU_INIT_SIZE;
	while(op)
	{	
		int i = 0, p = 0;
		for(i = 0;i < TREE_MAX_SIZE;i++)
		{
			strcpy(definition[0][i], "#");
			strcpy(definition[1][i], "#");
		}
		i = 0;
		ElemType1 e[NAME_MAX_SIZE];
		ElemType2 t[TEL_MAX_SIZE];
		BiTNode *N = NULL;
		char tree_name[TREE_NAME_SIZE];
		system("cls");	printf("\n\n");
		printf("      Menu for Binary Tree On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	1. InitBiTree       11. LeftChild\n");
		printf("        2. DestroyBiTree    12. RightChild\n");
		printf("    	3. CreateBiTree     13. LeftSibling \n");
		printf("    	4. ClearBiTree      14. RightSibling\n");
		printf("    	5. BiTreeEmpty      15. InsertChild\n");
		printf("    	6. BiTreeDepth      16. DeleteChild\n");
		printf("        7. Root             17. PreOrderTraverse\n");
		printf("    	8. Value            18. InOrderTraverse\n");
		printf("    	9. Assign           19. PostOrderTraverse\n");
		printf("       10. Parent           20. LevelOrderTraverse\n");
		printf("-------------------------------------------------\n");
		printf("       21. DataSave         24. MenuDelete\n");
		printf("       22. DataLoad         25. NewTree\n");
		printf("       23. MenuInsert       26. ChooseTree\n");
		printf("    	0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~26]:");
		scanf("%d",&op);
		switch(op){
		    case 1:
			//InitBiTree
			InitBiTree(&T);
			printf("二叉树创建成功！\n");
			getchar();
			getchar();
			break;
		    case 2:
		   	//DestroyBiTree
			if(DestroyBiTree(&T) == ERROR)
				printf("二叉树未创建！\n");
			else
				printf("二叉树销毁成功！\n");
			M.menuname[FindBiTree(M, menu_name)].bitree = NULL;
			getchar();
			getchar();
			break;
		    case 3:
		    //CreateBiTree
		    printf("请输入二叉树长度：\n");
		    scanf("%d", &length);
		    for(i = 0;i < length;i++)
		    {
		   		printf("请输入结点的名称：\n");
				scanf("%s", definition[0][i]);
				if(strcmp(definition[0][i], "#"))
				{
					printf("请输入结点的值：\n");
		  			scanf("%s", definition[1][i]);
				}			
			}
			CreateBiTree(&T, definition);
			printf("二叉树创建成功！\n");
			count = 0;
			getchar();
			getchar();
			break;
		    case 4:
		    //ClearBiTree
		    p = ClearBiTree(&T);
			if(p == ERROR)
				printf("二叉树未创建！\n");
			else if(p == SPEC)
				printf("二叉树已为空！\n");
			else
				printf("二叉树清空成功！\n");
			M.menuname[FindBiTree(M, menu_name)].bitree = NULL;
			getchar();
			getchar();
			break;
		    case 5:
			//BiTreeEmpty
			i = BiTreeEmpty(T);
			if(i == SPEC)
				printf("二叉树未创建！\n");
			else if(i == FALSE)
				printf("二叉树不为空！\n");
			else if(i == TRUE)
				printf("二叉树为空！\n");
			getchar();
			getchar();
			break;
		    case 6:
		    //BiTreeDepth
			i = BiTreeDepth(T);
			if(i == SPEC)
				printf("二叉树未创建！\n");
			else if(i == ERROR)
				printf("二叉树为空！\n");
			else
				printf("二叉树深度为%d！\n", i); 
			getchar();
			getchar();
			break;
		    case 7:
		    //Root
		    printf("根节点为：\n"); 
			Visit(Root(T));
			getchar();
			getchar();
			break;
		    case 8:
		    //Value
		    if(flag == 0)
			{
				printf("二叉树未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要查询的结点的名称：\n");
			scanf("%s", e);
			if(Find(T, e) == NULL)
			{
				printf("未找到相应结点！\n");
				getchar();
				getchar();
				break;
			} 
			printf("查询的结点的值为%s\n", Value(T, e));
			getchar();
			getchar();
			break;
		    case 9:
			//Assign 
			if(flag == 0)
			{
				printf("二叉树未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要赋值的结点的名称：\n");
			scanf("%s", e);
			printf("请输入要赋予的值：\n");
			scanf("%s", t);
			if(Find(T, e) == NULL)
			{
				printf("未找到相应结点！\n");
				getchar();
				getchar();
				break;
			} 
			if(Assign(T, e, t) == ERROR)
				printf("未找到相应结点！\n");
			else
				printf("赋值成功！\n"); 
			getchar();
			getchar();
			break;
		    case 10:
		    //Parent
			printf("请输入要查询的结点的名称：\n");
			scanf("%s", e);
			N = Parent(T, e);
			if(N == NULL)
				printf("未找到相应的结点或表未创建！\n");
			else
				printf("%s的双亲结点是%s", e, N->name);
			getchar();
			getchar();
			break;
		    case 11:
			//LeftChild
			printf("请输入要查询的结点的名称：\n");
			scanf("%s", e);
			N = LeftChild(T, e);
			if(N == NULL)
				printf("未找到相应的结点或表未创建！\n");
			else
				printf("%s的左孩子结点是%s", e, N->name);
			getchar();
			getchar();
			break;
		    case 12:
			//RightChild
			printf("请输入要查询的结点的名称：\n");
			scanf("%s", e);
			N = RightChild(T, e);
			if(N == NULL)
				printf("未找到相应的结点或表未创建！\n");
			else
				printf("%s的右孩子结点是%s", e, N->name);
			getchar();
			getchar();
			break;
			case 13:
	        //LeftSibling
	        printf("请输入要查询的结点的名称：\n");
			scanf("%s", e);
			N = LeftSibling(T, e);
			if(N == NULL)
				printf("未找到相应的结点或表未创建！\n");
			else
				printf("%s的左兄弟结点是%s", e, N->name);
			getchar();
			getchar();
			break;
			case 14:
			//RightSibling
			printf("请输入要查询的结点的名称：\n");
			scanf("%s", e);
			N = RightSibling(T, e);
			if(N == NULL)
				printf("未找到相应的结点或表未创建！\n");
			else
				printf("%s的右兄弟结点是%s", e, N->name);
			getchar();
			getchar();
			break;
			case 15:
			//InsertChild
			if(flag == 0)
			{
				printf("二叉树未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要插入的子树的名称：\n");
			scanf("%s", e);
			printf("请选择插入左子树或者右子树（0为左子树，1为右子树）：\n");
			scanf("%d", &p);
			if(Find(T, e) == NULL)
			{
				printf("未找到相应结点！\n");
				getchar();
				getchar();
				break;
			}
			printf("创建要插入的二叉树\n");
			printf("请输入要插入的二叉树长度：\n");
		    scanf("%d", &length);
		    for(i = 0;i < length;i++)
		    {
		   		printf("请输入结点的名称：\n");
				scanf("%s", definition[0][i]);
				if(strcmp(definition[0][i], "#"))
				{
					printf("请输入结点的值：\n");
		  			scanf("%s", definition[1][i]);
				}			
			}
			CreateBiTree(&N, definition);
			count = 0;
			if(InsertChild(T, Find(T, e), p, N) == SPEC)
				printf("二叉树未创建！\n");
			else
				printf("插入子树成功！\n");
			getchar();
			getchar();
			break;
			case 16:
			//DeleteChild
			if(flag == 0)
			{
				printf("二叉树未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要删除的子树的名称：\n");
			scanf("%s", e);
			printf("请选择删除左子树或者右子树（0为左子树，1为右子树）：\n");
			scanf("%d", &i);
			if(Find(T, e) == NULL)
			{
				printf("未找到相应结点！\n");
				getchar();
				getchar();
				break;
			}
			if(DeleteChild(T, Find(T, e), i) == SPEC)
				printf("删除失败！\n");
			else
				printf("删除成功！\n"); 
			getchar();
			getchar();
			break;
			case 17:
			//PreOrderTraverse
			if(PreOrderTraverse(T, Visit) == ERROR)
				printf("二叉树为空或未创建！\n");
			else
				printf("以上为先序遍历！\n");
			getchar();
			getchar();
			break;
			case 18:
			//InOrderTraverse
			if(InOrderTraverse(T, Visit) == ERROR)
				printf("二叉树为空或未创建！\n");
			else
				printf("以上为中序遍历！\n");
			getchar();
			getchar();
			break;
			case 19:
			//PostOrderTraverse
			if(PostOrderTraverse(T, Visit) == ERROR)
				printf("二叉树为空或未创建！\n");
			else
				printf("以上为后序遍历！\n");
			getchar();
			getchar();
			break;
			case 20:
			//LevelOrderTraverse
			if(LevelOrderTraverse(T, Visit) == ERROR)
				printf("二叉树为空或未创建！\n");
			else
				printf("以上为层序遍历！\n");
			getchar();
			getchar();
			break;
			case 21:
			//DataSave
			if((fp = fopen("test.txt","w")) == NULL)
			{
				printf("文件无法打开!\n");
				break;
			}
			p = Output(T, fp);
			if(p == SPEC)
				printf("二叉树未创建！\n");
			else if(p == ERROR)
				printf("二叉树为空！\n");
			else
				printf("二叉树保存成功！\n");
			fclose(fp); 
			getchar();
			getchar();
			break;
			case 22:
			//DataLoad
			if((fp = fopen("test.txt","r")) == NULL)
			{
				printf("文件无法打开!\n");
				break;
			}
			while(1)
			{
				if(fscanf(fp, "%s", definition[0][i]) == EOF)
					break;
				if(strcmp(definition[0][i], "#"))
					fscanf(fp, "%s", definition[1][i]);
				i++;
			}
			CreateBiTree(&T, definition);
			printf("二叉树读取成功！\n");
			count = 0;
			fclose(fp);
			getchar();
			getchar();
			break;
			case 23:
			//MenuInsert
			if(flag == 0) 
			{
				printf("二叉树未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入二叉树的名称！\n");
			scanf("%s", tree_name);
			MenuInsert(&M, T, tree_name);
			printf("二叉树插入成功！\n"); 
			strcpy(menu_name, tree_name);
			getchar();
			getchar();
			break;
			case 24:
			//MenuDelete
			printf("请输入要删除的二叉树的名称\n");
			scanf("%s", tree_name);
			if(MenuDelete(&M, tree_name) == ERROR)
				printf("未找到相应名称的二叉树！\n");
			else
				printf("二叉树删除成功！\n");
			getchar();
			getchar();
			break;
			case 25:
			//NewTree
			NewBiTree(&T);
			printf("已创建新的二叉树！\n");
			getchar();
			getchar();
			break;
			case 26:
			//ChooseBiTree
			printf("请输入要操作的二叉树的名称！\n");
			scanf("%s", tree_name);
			N = ChooseBiTree(M, tree_name);
			if(N == NULL && FindBiTree(M, tree_name) == -1)
				printf("未找到相应名称的二叉树！\n");	
			else
			{
				T = N;
				strcpy(menu_name, tree_name);
				printf("已成功找到二叉树，请进行操作！\n");	
			}
			getchar();
			getchar();
			break;
		}
	}
  printf("欢迎下次再使用本系统！\n");
}

status InitBiTree(BiTNode **T){
	*T = NULL;
	flag = 1;
	return OK;
/*	if(*T != NULL)
		retrun ERROR;
	BiTNode *N;
	N = (BiTNode *)malloc(LENG);
	if(!N)
		return OVERFLOW;
	N->lchild = NULL;
	N->rchild = NULL;
	N->name = NULL;
	N->tel = NULL;
	*T = N;
	return OK;
	*/
}	

status DestroyBiTree(BiTNode **T){
	if(flag == 0 )
		return ERROR;
	if(*T == NULL)
	{
		flag = 0;
		return OK;
	}
	BiTNode *N = *T;
	if(N->lchild != NULL)
		DestroyBiTree(&N->lchild);
	if(N->rchild != NULL)
		DestroyBiTree(&N->rchild);
	free(N);
	N = NULL;
	*T = N;
	flag = 0;
	return OK;
}

status CreateBiTree(BiTNode **T, ElemType1 definition[2][TREE_MAX_SIZE][NAME_MAX_SIZE]){
	BiTNode *N = *T;
	if (!strcmp(definition[0][count], "#"))
	{
		N = NULL;
		count++;
	}
	else
	{
		if (!(N = (BiTNode *) malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		strcpy(N->name, definition[0][count]); 
		strcpy(N->tel, definition[1][count]);
		count++;
		CreateBiTree(&N->lchild, definition); 
		CreateBiTree(&N->rchild, definition); 
	}
	*T = N;
	flag = 1;
	return OK;
}

status ClearBiTree(BiTNode **T){
	if(*T == NULL)
		return SPEC;
	if(flag == 0)
		return ERROR;
	BiTNode *N = *T;
	if(N->lchild != NULL)
		ClearBiTree(&N->lchild);
	if(N->rchild != NULL)
		ClearBiTree(&N->rchild);
	free(N);
	N = NULL;
	*T = N;
	return OK;
}

status BiTreeEmpty(BiTNode *T){
	if(flag == 0)
		return SPEC;
	else if(T == NULL)
		return TRUE;
	else
		return FALSE;
}

int BiTreeDepth(BiTNode *T){
	if(flag == 0)
		return SPEC;
	if(T == NULL)
		return 0;
	int depth, left_depth, right_depth;
	left_depth = BiTreeDepth(T->lchild);
	right_depth = BiTreeDepth(T->rchild);
	if(left_depth > right_depth)
		depth = 1 + left_depth;
	else
		depth = 1 + right_depth;
	return depth;
}

BiTNode *Root(BiTNode *T){
	if(flag == 0)
		return NULL;
	return T;
}

ElemType2 *Value(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]){	
	ElemType2 *N = NULL;
	ElemType2 *P = NULL;
	if(T == NULL)
		return NULL;
	if(!strcmp(T->name, e))
		N = T->tel;
	P = Value(T->lchild, e);
	if(P)
		N = P;
	P = Value(T->rchild, e);
	if(P)
		N = P;
	return N;
}

status Assign(BiTNode *T, ElemType1 e[NAME_MAX_SIZE], ElemType2 value[TEL_MAX_SIZE]){
	if(T == NULL)
		return ERROR;
	else
	{
		if(!strcmp(T->name, e))
			strcpy(T->tel, value);	
		Assign(T->lchild, e, value);
		Assign(T->rchild, e, value);
	}
	return OK;
}

BiTNode *Parent(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]){
	BiTNode *N = NULL, *P = NULL;
	if(T == NULL)
		return NULL;
	if(T->lchild != NULL)
	{
		if(!strcmp(T->lchild->name, e))
			N = T;
	}
	if(T->rchild != NULL)
	{
		if(!strcmp(T->rchild->name, e))
			N = T;
	}	
	P = Parent(T->lchild, e);
	if(P)
		N = P;
	P = Parent(T->rchild, e);
	if(P)
		N = P;
	return N; 
}

BiTNode *LeftChild(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]){
	BiTNode *N = NULL, *P = NULL;
	if(T == NULL)
		return NULL;
	if(!strcmp(T->name, e))
		N = T->lchild;
	P = LeftChild(T->lchild, e);
	if(P)
		N = P;
	P = LeftChild(T->rchild, e);
	if(P)
		N = P;
	return N;
}

BiTNode *RightChild(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]){
	BiTNode *N = NULL, *P = NULL;
	if(T == NULL)
		return NULL;
	if(!strcmp(T->name, e))
		N = T->rchild;
	P = RightChild(T->lchild, e);
	if(P)
		N = P;
	P = RightChild(T->rchild, e);
	if(P)
		N = P;
	return N;
}

BiTNode *LeftSibling(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]){
	BiTNode *N = NULL, *P = NULL;
	if(T == NULL)
		return NULL;
	if(T->lchild != NULL)
	{
		if(!strcmp(T->lchild->name, e))
			N = NULL;
	}
	if(T->rchild != NULL)
	{
		if(!strcmp(T->rchild->name, e))
			N = T->lchild;
	}
	P = LeftSibling(T->lchild, e);
	if(P)
		N = P;
	P = LeftSibling(T->rchild, e);
	if(P)
		N = P;
	return N;
}

BiTNode *RightSibling(BiTNode *T, ElemType1 e[NAME_MAX_SIZE]){
	BiTNode *N = NULL, *P = NULL;
	if(T == NULL)
		return NULL;
	if(T->rchild != NULL)
	{
		if(!strcmp(T->rchild->name, e))
			N = NULL;
	}
	if(T->lchild != NULL)
	{
		if(!strcmp(T->lchild->name, e))
			N = T->rchild;
	}
	P = RightSibling(T->lchild, e);
	if(P)
		N = P;
	P = RightSibling(T->rchild, e);
	if(P)
		N = P;
	return N;
}

status InsertChild(BiTNode *T, BiTNode *p, int LR, BiTNode *c){
	if(LR == 0)
	{
		c->rchild = p->lchild;
		p->lchild = c;
	}
	else if(LR == 1)
	{
		c->rchild = p->rchild;
		p->rchild = c;
	}
	return OK;
}

status DeleteChild(BiTNode *T, BiTNode *p, int LR){
	if(LR == 0)
	{
		if(p->lchild != NULL)
			ClearBiTree(&(p->lchild));
		else
		{
			printf("左子树为空！\n");
			return SPEC; 
		} 		
	}	
	if(LR == 1)
	{
		if(p->rchild != NULL)
			ClearBiTree(&(p->rchild));
		else
		{
			printf("右子树为空！\n");
			return SPEC;
		}
	}	
	return OK;
}

status PreOrderTraverse(BiTNode *T,void (*Visit)(BiTNode *T)){
	if(T == NULL)
		return ERROR;
	else 
	{
		Visit(T); 
		PreOrderTraverse(T->lchild, Visit); 
		PreOrderTraverse(T->rchild, Visit); 
	}
	return OK;
}

status InOrderTraverse(BiTNode *T,void (*Visit)(BiTNode *T)){
	BiTNode *st[TREE_MAX_SIZE + 1];
	int top = 0;
	if(T == NULL)
		return ERROR;
	while(T || top)
	{
		while(T)
		{
			if(top == TREE_MAX_SIZE)
				exit(OVERFLOW);
			st[++top] = T;
			T = T->lchild;
		}
		if(top)
		{
			T = st[top--];
			Visit(T);
			T = T->rchild;
		}
	}
	return OK;
}

status PostOrderTraverse(BiTNode *T,void (*Visit)(BiTNode *T)){
	if(T == NULL)
		return ERROR;
	else 
	{
		PostOrderTraverse(T->lchild, Visit); 
		PostOrderTraverse(T->rchild, Visit);
		Visit(T);
	}
	return OK;
}


status LevelOrderTraverse(BiTNode *T, void (*Visit)(BiTNode *T)){
	BiTNode *st[TREE_MAX_SIZE + 1];
	int top = 0, tail = 1;
	if(T == NULL)
		return ERROR;
	st[++top] = T;
	while(top <= tail)
	{
		T = st[top++];
		Visit(T);
		if(T->lchild)
			st[++tail] = T->lchild;
		if(tail == TREE_MAX_SIZE)
				exit(OVERFLOW);
		if(T->rchild)
			st[++tail] = T->rchild;
		if(tail == TREE_MAX_SIZE)
				exit(OVERFLOW);	
	}
	return OK; 
}

void Visit(BiTNode *T){
	if(flag == 0)
		printf("二叉树未创建！\n");
	else if(!T)
		printf("二叉树为空！\n");
	else
	{
		printf("%s\t",T->name);
		printf("%s\n",T->tel);	
	} 	
}

BiTNode *Find(BiTNode *T, ElemType1 e[NAME_MAX_SIZE])
{
	BiTNode *N = NULL, *P = NULL;
	if(T == NULL)
		return NULL;
	if(!strcmp(T->name, e))
		N = T;
	P = Find(T->lchild, e);
	if(P)
		N = P;
	P = Find(T->rchild, e);
	if(P)
		N = P;
	return N; 	
}

status Output(BiTNode *T, FILE *fp){
	if(flag == 0)
		return SPEC;
	if(T == NULL)
	{
		fprintf(fp, "#\n");
		return ERROR;
	}
	fprintf(fp, "%s ", T->name);
	if(strcmp(T->name, "#"))
		fprintf(fp, "%s", T->tel);
	fprintf(fp, "\n");
	Output(T->lchild, fp);
	Output(T->rchild, fp);
	return OK;
} 

status MenuInsert(Menu *M, BiTNode *T, char name[TREE_NAME_SIZE]){
	MenuName *newbase;
	if(M->length >= M->menusize)
	{
		newbase = (MenuName*)realloc(M->menuname, (++M->menusize) * sizeof(MenuName));	
		if(!newbase)
			exit(OVERFLOW);
		M->menuname = newbase;
	}
	strcpy((M->menuname + M->length)->name, name);
	(M->menuname + M->length)->bitree = T;
	M->length++;	
	return OK;	
}

status NewBiTree(BiTNode **T){
	*T = (BiTNode *)malloc(LENG);
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	flag = 0;
	return OK;
}

int FindBiTree(Menu M, char name[TREE_NAME_SIZE]){
	int i = 0;
	for(;i < M.length; i++)
	{
		if(!strcmp(M.menuname[i].name, name))
			return i;
	}
	return -1;
}

BiTNode *ChooseBiTree(Menu M, char name[TREE_NAME_SIZE]){
	int i = FindBiTree(M, name);
	if(i == -1)
		return NULL;
	else
		return M.menuname[i].bitree;
}

status MenuDelete(Menu *M, char name[TREE_NAME_SIZE]){
	int loc = FindBiTree(*M, name);
	if(loc == -1)
		return ERROR;
	DestroyBiTree(&(M->menuname[loc].bitree));
	for(;loc < M->length - 1; loc++)
		M->menuname[loc] = M->menuname[loc + 1];
	M->length--;
	return OK;
}

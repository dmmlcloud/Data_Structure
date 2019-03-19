#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define SPEC -2 
#define NONE -1

typedef int status; 
typedef int ElemType_Arc;
typedef int ElemType_Ver;

#define MAX_VERTEX_NUM 20
#define MAX_ARC_NUM 200
#define MAX_ARC_NAME 20
#define MAX_VERTEX_NAME 20
#define GRAPH_NAME_SIZE 20
#define MENU_INIT_SIZE 50

int visited[50];
static char menu_name[GRAPH_NAME_SIZE];

typedef struct ArcInfo{
	char arc_name[MAX_ARC_NAME];
	ElemType_Arc arc_info;
}ArcInfo; 

typedef struct VInfo{
	char ver_name[MAX_VERTEX_NAME];
	ElemType_Ver ver_info;
}VInfo;

typedef struct ArcNode{//表结点结构类型
	int adjvex; //该弧(边)的终点位置
	struct ArcNode *nextarc; //指向下一条弧的指针
	ArcInfo *info; //该弧的相关信息的指针
} ArcNode;

typedef struct VNode {//头结点的类型
	VInfo data; //顶点信息
	ArcNode *firstarc; //指向第一条弧
}VNode, AdjList;

typedef struct {//邻接表
	AdjList *vertices;
	int vexnum, arcnum; //图中顶点数n和边数e
	int kind; //图的类型
} ALGraph;

typedef struct {
	int adjvex_start;
	int adjvex_end;
	ArcInfo arc_data;
}ArcCreateInfo;

typedef struct MenuName
{
	char name[GRAPH_NAME_SIZE];
	ALGraph graph;
}MenuName;

typedef struct Menu{
	MenuName *menuname;
	int length;
	int menusize; 	 	
}Menu;

status CreateGraph(ALGraph *G,VInfo *V,ArcCreateInfo *VR);
status DestroyGraph(ALGraph *G);
int LocateVex(ALGraph G, int u);
ElemType_Ver GetVex(ALGraph G, int v);
status PutVex(ALGraph *G, int v, ElemType_Ver value);
int FirstAdjVex(ALGraph G, int v);
int NextAdjVex(ALGraph G, int v, int w);
status InsertVex(ALGraph *G, VInfo V);
status DeleteVex(ALGraph *G, int v);
status InsertArc(ALGraph *G, int v, int w);
status DeleteArc(ALGraph *G, int v, int w);
void DFSTraverse(ALGraph G, void (*Visit) (VNode V));
void DFS(ALGraph G, int v, void (*Visit) (VNode V)); 
void BFSTraverse(ALGraph G, void (*Visit) (VNode V));
void Visit(VNode V);
status FindArcNode(ALGraph G, int v, int w);
status MenuInsert(Menu *M, ALGraph G, char name[GRAPH_NAME_SIZE]);
status NewGraph(ALGraph *G);
int FindGraph(Menu M, char name[GRAPH_NAME_SIZE]);
ALGraph ChooseGraph(Menu M, char name[GRAPH_NAME_SIZE]);
status MenuDelete(Menu *M, char name[GRAPH_NAME_SIZE]);

void main(void){
	int i = 1, op = 1;
	FILE *fp;
	ALGraph G;
	G.vertices = (AdjList *)malloc((MAX_VERTEX_NUM + 1) * sizeof(AdjList));
	for(;i <= MAX_VERTEX_NUM;i++)
	{
		G.vertices[i].firstarc = NULL;
		strcpy(G.vertices[i].data.ver_name, "#");
		G.vertices[i].data.ver_info = 0;
	}
	VInfo V[MAX_VERTEX_NUM + 2];
	ArcCreateInfo VR[MAX_ARC_NUM + 2];
	char graph_name[GRAPH_NAME_SIZE];
	G.arcnum = 0;
	G.vexnum = 0;
	G.kind = 0;
	Menu M;
	M.menuname = (MenuName *)malloc(MENU_INIT_SIZE * sizeof(MenuName));
	M.length = 0;
	M.menusize = MENU_INIT_SIZE;
	while(op)
	{	
		ALGraph L;
		int e = 1,re = 0, u = 0, v = 0, value = 0, w = 0;
		ElemType_Ver re_ver;
		VInfo VE;
		int ver_num;
		char ver_name[MAX_VERTEX_NAME];
		ArcNode *N;
		ALGraph A; 
		system("cls");	printf("\n\n");
		printf("      Menu for Binary Tree On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	1. CreateGraph       8. InsertVex\n");
		printf("        2. DestroyGraph      9. DeleteVex\n");
		printf("    	3. LocateVex        10. InsertArc \n");
		printf("    	4. GetVex           11. DeleteArc\n");
		printf("    	5. PutVex           12. DFSTraverse\n");
		printf("    	6. FirstAdjVex      13. BFSTraverse\n");
		printf("        7. NextAdjVex\n");
		printf("-------------------------------------------------\n");
		printf("       14. DataSave         17. MenuDelete\n");
		printf("       15. DataLoad         18. NewGraph\n");
		printf("       16. MenuInsert       19. ChooseGraph\n");
		printf("    	0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~19]:");
		scanf("%d",&op);
		switch(op){
			case 1:
			//CreateGraph
			printf("下面录入顶点集的信息：（输入'#'结束）\n"); 
			while(1)
			{
				if(e >= MAX_VERTEX_NUM)
					break;
				printf("请输入顶点的名称：\n");
				scanf("%s", V[e].ver_name);
				if(!strcmp(V[e].ver_name, "#"))
					break;
				printf("请输入顶点的元素值：\n");
				scanf("%d", &V[e].ver_info);
				printf("\n");
				e++;
			}
			e = 1;
			printf("下面录入弧集的信息：（输入'0'结束）\n");
			while(1)
			{
				if(e >= MAX_ARC_NUM)
					break;
				printf("请输入弧的起点：\n");
				scanf("%d", &VR[e].adjvex_start);
				if(VR[e].adjvex_start == 0)
					break;
				printf("请输入弧的终点：\n");
				scanf("%d", &VR[e].adjvex_end);
				printf("请输入弧的名称：\n");
				scanf("%s", VR[e].arc_data.arc_name);
				printf("请输入弧的值：\n");
				scanf("%d", &VR[e].arc_data.arc_info);
				printf("\n");
				e++;
			}
			if(CreateGraph(&G, V, VR))
				printf("创建成功！\n");
			else
				printf("创建失败！\n");
			getchar();
			getchar();
			break;
			case 2:
			//DestroyGraph
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			DestroyGraph(&G);
			printf("销毁成功！\n"); 
			getchar();
			getchar();
			break;
			case 3:
			//LocateVex
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要查询的顶点元素值：\n");
			scanf("%d", &u);
			re = LocateVex(G, u);
			if(re == ERROR)
				printf("未找到相应的顶点！\n");
			else
				printf("所查询的顶点的位置为%d\n", re);
			getchar();
			getchar();
			break;
			case 4:
			//GetVex
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要查询的顶点的位置：\n");
			scanf("%d", &v);
			re_ver = GetVex(G, v);
			if(re_ver == ERROR)
				printf("位置输入错误！\n");
			else
				printf("查询的顶点的元素值为%d", re_ver);
			getchar();
			getchar();
			break;
			case 5:
			//PutVex
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要赋值的顶点的位置：\n");
			scanf("%d", &v);
			printf("请输入要赋给顶点的值：\n");
			scanf("%d", &value);
			if(PutVex(&G, v, value) == ERROR)
				printf("位置输入错误！\n");
			else
				printf("赋值成功！\n"); 
			getchar();
			getchar();
			break;
			case 6:
			//FirstAdjVex
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要查询的顶点的位置：\n");
			scanf("%d", &v);
			re = FirstAdjVex(G, v);
			if(re == NONE)
				printf("该顶点没有邻接点！\n");
			else if(re == ERROR)
				printf("位置输入错误！\n");
			else 
				printf("该顶点邻接点的位置为%d", re);
			getchar();
			getchar();
			break;
			case 7:
			//NextAdjVex
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要查询的顶点的位置：\n");
			scanf("%d", &v);
			printf("请输入当前邻接点的位置：\n");
			scanf("%d", &w);
			re = NextAdjVex(G, v, w);
			if(re == NONE)
				printf("该邻接点为最后一个邻接点！\n");
			else if(re == ERROR)
				printf("位置输入错误！\n");
			else if(re == SPEC)
				printf("未找到相应的邻接点！\n"); 
			else 
				printf("下一个邻接点的位置为%d", re);
			getchar();
			getchar();
			break;
			case 8:
			//InsertVex
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要插入的顶点的名称：\n");
			scanf("%s", VE.ver_name);
			printf("请输入要插入的顶点的值：\n");
			scanf("%d", &VE.ver_info);
			if(InsertVex(&G, VE) == ERROR)
				printf("顶点插入失败！\n");
			else
				printf("顶点插入成功！\n");
			getchar();
			getchar();
			break;
			case 9:
			//DeleteVex
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要删除的结点的位置：\n");
			scanf("%d", &v);
			if(DeleteVex(&G, v) == ERROR)
				printf("位置输入错误！\n");
			else
				printf("顶点删除成功！\n");
			getchar();
			getchar();
			break;
			case 10:
			//InsertArc
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要插入的弧的起点：\n");
			scanf("%d", &v);
			printf("请输入要插入的弧的终点：\n");
			scanf("%d", &w);
			if(InsertArc(&G, v, w) == OK)
				printf("弧插入成功！\n");
			else
				printf("弧插入失败！\n");
			getchar();
			getchar();
			break;
			case 11:
			//DeleteArc
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入要删除的弧的起点：\n");
			scanf("%d", &v);
			printf("请输入要删除的弧的终点：\n");
			scanf("%d", &w);
			if(DeleteArc(&G, v, w) == OK)
				printf("弧删除成功！\n");
			else
				printf("弧删除失败！\n");
			getchar();
			getchar();
			break;
			case 12:
			//DFSTraverse
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			DFSTraverse(G, Visit);
			getchar();
			getchar();
			break;
			case 13:
			//BFSTraverse
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			BFSTraverse(G, Visit);
			getchar();
			getchar();
			break;
			case 14:
			//DataSave
			if((fp = fopen("test.txt","w")) == NULL)
			{
				printf("文件无法打开!\n");
				getchar();
				getchar();
				break;
			}
			fprintf(fp, "%d\n", G.vexnum);
			for(e = 1; e <= G.vexnum; e++)
			{
				fprintf(fp, "%s ", G.vertices[e].data.ver_name);
				fprintf(fp, "%d\n", G.vertices[e].data.ver_info);
			}
			fprintf(fp, "#\n");
			for(e = 1; e <= G.vexnum; e++)
			{
				N = G.vertices[e].firstarc;
				while(N != NULL)
				{
					fprintf(fp, "%d ", e);
					fprintf(fp, "%d ", N->adjvex);
					fprintf(fp, "%s ", N->info->arc_name);
					fprintf(fp, "%d\n", N->info->arc_info);
					N = N->nextarc;
				}
			}
			printf("文件保存成功！\n");
			fclose(fp);
			getchar();
			getchar();
			break;
			case 15:
			//DataLoad
			if((fp = fopen("test.txt","r")) == NULL)
			{
				printf("文件无法打开!\n");
				getchar();
				getchar();
				break;
			}
			fscanf(fp, "%d", &ver_num);
			for(e = 1; e <= ver_num; e++)
			{
				fscanf(fp, "%s", V[e].ver_name);
				fscanf(fp, "%d", &V[e].ver_info);
			}
			fscanf(fp, "%s", V[e].ver_name);
			e = 1;
			while(fscanf(fp, "%d", &VR[e].adjvex_start) != EOF)
			{
				fscanf(fp, "%d", &VR[e].adjvex_end);
				fscanf(fp, "%s", VR[e].arc_data.arc_name);
				fscanf(fp, "%d", &VR[e].arc_data.arc_info);
				e++; 
			}
			VR[e].adjvex_start = 0;
			CreateGraph(&G, V, VR);
			printf("文件读取成功！\n");
			fclose(fp);
			getchar();
			getchar();
			break;
			case 16:
			//MenuInsert
			if(G.vexnum == 0)
			{
				printf("图未创建！\n");
				getchar();
				getchar();
				break;
			}
			printf("请输入图的名称！\n");
			scanf("%s", graph_name);
			MenuInsert(&M, G, graph_name);
			printf("图插入成功！\n"); 
			strcpy(menu_name, graph_name);
			getchar();
			getchar();
			break;
			case 17:
			//MenuDelete
			printf("请输入要删除的图的名称\n");
			scanf("%s", graph_name);
			if(MenuDelete(&M, graph_name) == ERROR)
				printf("未找到相应名称的图！\n");
			else
				printf("图删除成功！\n");
			getchar();
			getchar();
			break;
			case 18:
			//NewGraph
			NewGraph(&L);
			G = L;
			printf("已创建新的图！\n");
			getchar();
			getchar();
			break;
			case 19:
			//ChooseGraph
			printf("请输入要操作的图的名称！\n");
			scanf("%s", graph_name);
			A = ChooseGraph(M, graph_name);
			if(FindGraph(M, graph_name) == -1)
				printf("未找到相应名称的图！\n");	
			else
			{
				G = A;
				strcpy(menu_name, graph_name);
				printf("已成功找到图，请进行操作！\n");	
			}
			getchar();
			getchar();
			break;
		}
	}
}

status CreateGraph(ALGraph *G,VInfo *V,ArcCreateInfo *VR){
	int i = 1;
	while(strcmp(V[i].ver_name, "#"))
	{
		strcpy(G->vertices[i].data.ver_name, V[i].ver_name); 
		G->vertices[i].data.ver_info = V[i].ver_info;
		G->vexnum++;
		i++;
	}
	for(i = 1; VR[i].adjvex_start != 0; i++)
	{
		if(FindArcNode(*G, VR[i].adjvex_end, VR[i].adjvex_start))
			continue;
		ArcNode *A = (ArcNode *)malloc(sizeof(ArcNode));
		if(!A)
			exit(OVERFLOW);
		ArcInfo *AI = (ArcInfo *)malloc(sizeof(ArcInfo));
		if(!AI)
			exit(OVERFLOW);
		A->adjvex = VR[i].adjvex_end;
		A->nextarc = NULL;
		AI->arc_info = VR[i].arc_data.arc_info;
		strcpy(AI->arc_name, VR[i].arc_data.arc_name);
		A->info = AI;
		if(G->vertices[VR[i].adjvex_start].firstarc == NULL)
			G->vertices[VR[i].adjvex_start].firstarc = A;
		else
		{
			ArcNode *N = G->vertices[VR[i].adjvex_start].firstarc;
			while(N->nextarc != NULL)
				N = N->nextarc;
			N->nextarc = A;
		}
		ArcNode *B = (ArcNode *)malloc(sizeof(ArcNode));
		if(!B)
			exit(OVERFLOW);
		ArcInfo *BI = (ArcInfo *)malloc(sizeof(ArcInfo));
		if(!BI)
			exit(OVERFLOW);
		B->adjvex = VR[i].adjvex_start;
		B->nextarc = NULL;
		BI->arc_info = VR[i].arc_data.arc_info;
		strcpy(BI->arc_name, VR[i].arc_data.arc_name);
		B->info = BI;
		if(G->vertices[VR[i].adjvex_end].firstarc == NULL)
			G->vertices[VR[i].adjvex_end].firstarc = B;
		else
		{
			ArcNode *P = G->vertices[VR[i].adjvex_end].firstarc;
			while(P->nextarc != NULL)
				P = P->nextarc;
			P->nextarc = B;
		}
		G->arcnum = G->arcnum + 2;
	}
	return OK;
}

status DestroyGraph(ALGraph *G){
	int i = 1;
	ArcNode *P, *N;
	for(i = 1;i <= G->vexnum; i++)
	{
		if(G->vertices[i].firstarc != NULL)
		{
			P = G->vertices[i].firstarc;
			N = G->vertices[i].firstarc->nextarc;
			while(N != NULL)
			{
				if(P->info != NULL)
					free(P->info);
				P->info = NULL;
				free(P);
				P = N;
				N = N->nextarc;
			}
			free(P);
			G->vertices[i].firstarc = NULL;
		}
	}
	G->arcnum = 0;
	G->vexnum = 0;
	return OK;
}

int LocateVex(ALGraph G, int u){
	int i;
	if(u == 0)
		return ERROR;
	for(i = 1;i <= G.vexnum; i++)
	{
		if(G.vertices[i].data.ver_info == u)
			return i;
	}
	return ERROR;
}

ElemType_Ver GetVex(ALGraph G, int v){
	if(v <= 0 || v > G.vexnum)
		return ERROR;
	else if(G.vertices[v].data.ver_info == 0)
		return ERROR;
	else
		return G.vertices[v].data.ver_info;
}

status PutVex(ALGraph *G, int v, ElemType_Ver value){
	if(v <= 0 || v > G->vexnum)
		return ERROR;
	else if(G->vertices[v].data.ver_info == 0)
		return ERROR;
	else
	{
		G->vertices[v].data.ver_info = value;
		return OK;
	}
}

int FirstAdjVex(ALGraph G, int v){
	if(v <= 0 || v > G.vexnum)
		return ERROR;
	else
	{
		if(G.vertices[v].firstarc == NULL)
			return NONE;
		else
			return G.vertices[v].firstarc->adjvex;
	}
}

int NextAdjVex(ALGraph G, int v, int w){
	ArcNode *N = NULL;
	if(v <= 0 || v > G.vexnum)
		return ERROR;
	else
	{
		N = G.vertices[v].firstarc;
		while(1)
		{
			if(N == NULL)
				return SPEC;
			if(N->adjvex == w)
				break;
			N = N->nextarc;
		}
		if(N->nextarc == NULL)
			return NONE;
		else
			return N->nextarc->adjvex;
	}
}

status InsertVex(ALGraph *G, VInfo V){
	if(G->vexnum >= MAX_VERTEX_NUM)
	{
		AdjList *newbase;
		newbase = (AdjList *)realloc(G->vertices, (G->vexnum + 2) * sizeof(AdjList));
		if(newbase == NULL)
			return ERROR;
		G->vertices = newbase;
	}
	G->vexnum++;
	strcpy(G->vertices[G->vexnum].data.ver_name, V.ver_name);
	G->vertices[G->vexnum].data.ver_info = V.ver_info;
	G->vertices[G->vexnum].firstarc = NULL;
	return OK;
} 

status DeleteVex(ALGraph *G, int v){
	int i = 1;
	if(v <= 0 || v > G->vexnum)
		return ERROR;
	ArcNode *N, *P;
	if(G->vertices[v].firstarc != NULL)
	{
		P = G->vertices[v].firstarc;
		N = G->vertices[v].firstarc->nextarc;
		while(N != NULL)
		{
			free(P->info);
			P->info = NULL;
			free(P);
			P = N;
			N = N->nextarc;
			G->arcnum--;
		}
		free(P);
	}
	G->vertices[v].firstarc = NULL;
	G->vertices[v].data.ver_info = 0;
	strcpy(G->vertices[v].data.ver_name, "#");
	for(i = 1; i < G->vexnum; i++)
	{
		if(G->vertices[i].firstarc != NULL)
		{	
			P = G->vertices[i].firstarc;
			N = G->vertices[i].firstarc->nextarc;
			if(P->adjvex == v)
			{
				free(P);
				P = NULL;
				if(N == NULL) 
					G->vertices[i].firstarc = NULL;
				else
					G->vertices[i].firstarc = N;
				G->arcnum--;
			}
			else
			{
				while(N != NULL)
				{
					if(N->adjvex == v)
					{
						P->nextarc = N->nextarc;
						free(N);
						N = NULL;
						G->arcnum--;
						break;
					}
					P = P->nextarc;
					N = N->nextarc;
				}
			}
		}
	}
	return OK;
}

status InsertArc(ALGraph *G, int v, int w){
	int arc_info;
	char arc_name[MAX_ARC_NAME];
	if(v <= 0 || v > G->vexnum)
		return ERROR;
	if(w <= 0 || w > G->vexnum)
		return ERROR;
	ArcNode *N;
	ArcNode *A = (ArcNode *)malloc(sizeof(ArcNode));
	if(!A)
		exit(OVERFLOW);
	A->adjvex = w;
	A->nextarc = NULL;
	A->info = (ArcInfo *)malloc(sizeof(ArcInfo));
	if(!A->info)
		exit(OVERFLOW);
	printf("请输入弧的名称：\n");
	scanf("%s",arc_name);
	printf("请输入弧的值：\n");
	scanf("%d",&arc_info);
	strcpy(A->info->arc_name, arc_name);
	A->info->arc_info = arc_info;
	N = G->vertices[v].firstarc;
	if(N == NULL)
		G->vertices[v].firstarc = A;
	else
	{
		while(N->nextarc != NULL)
			N = N->nextarc;
		N->nextarc = A;
	}
	ArcNode *B = (ArcNode *)malloc(sizeof(ArcNode));
	if(!B)
		exit(OVERFLOW);
	B->adjvex = v;
	B->nextarc = NULL;
	B->info = (ArcInfo *)malloc(sizeof(ArcInfo));
	if(!B->info)
		exit(OVERFLOW);
	strcpy(B->info->arc_name, arc_name);
	B->info->arc_info = arc_info;
	N = G->vertices[w].firstarc;
	if(N == NULL)
		G->vertices[w].firstarc = B;
	else
	{
		while(N->nextarc != NULL)
			N = N->nextarc;
		N->nextarc = B;
	}
	
	G->arcnum = G->arcnum + 2;
	return OK;
}

status DeleteArc(ALGraph *G, int v, int w){
	ArcNode *N, *P;
	int flag = 0;
	if(G->vertices[v].firstarc != NULL)
	{
		P = G->vertices[v].firstarc;
		N = G->vertices[v].firstarc->nextarc;
		if(P->adjvex == w)
		{
			free(P);
			P = NULL;
			if(N == NULL) 
				G->vertices[v].firstarc = NULL;
			else
				G->vertices[v].firstarc = N;
			G->arcnum--;
			flag = 1;
		}
		else
		{
			while(N != NULL)
			{
				if(N->adjvex == w)
				{
					P->nextarc = N->nextarc;
					free(N);
					N = NULL;
					G->arcnum--;
					flag = 1;
					break;
				}
				P = P->nextarc;
				N = N->nextarc;
			}
		}
	}
	if(!flag)
		return ERROR;
	P = G->vertices[w].firstarc;
	N = G->vertices[w].firstarc->nextarc;
	if(P->adjvex == v)
	{
		free(P);
		P = NULL;
		if(N == NULL) 
			G->vertices[w].firstarc = NULL;
		else
			G->vertices[w].firstarc = N;
		G->arcnum--;
	}
	else
	{
		while(N != NULL)
		{
			if(N->adjvex == v)
			{
				P->nextarc = N->nextarc;
				free(N);
				N = NULL;
				G->arcnum--;
				break;
			}
			P = P->nextarc;
			N = N->nextarc;
		}
	}
	return OK;
}

void DFSTraverse(ALGraph G, void (*Visit) (VNode V)){
	int i;
	for(i = 1;i <= G.vexnum; i++)
		visited[i] = 0;
	for(i = 1;i <= G.vexnum; i++)
	{
		if(!visited[i])
			DFS(G, i, Visit);
	}
	printf("以上为图的深度优先遍历！\n");
}

void DFS(ALGraph G, int v, void (*Visit) (VNode V)){
	int w;
	visited[v] = 1;
	Visit(G.vertices[v]);
	for(w = FirstAdjVex(G, v); w >= 1; w = NextAdjVex(G, v, w))
	{
		if(!visited[w])
			DFS(G, w, Visit);
	}
}

void BFSTraverse(ALGraph G, void (*Visit) (VNode V)){
	int i, u, w;
	int Q[G.vexnum + 1];
	ArcNode *N = G.vertices[i].firstarc;
	for(i = 1;i <= G.vexnum; i++)
		visited[i] = 0;
	for(i = 1;i <= G.vexnum; i++)
	{
		int top = 1, tail = 1;
		if(!visited[i])
		{
			visited[i] = 1;
			Visit(G.vertices[i]);
			Q[tail] = i;
			while(top <= tail)
			{
				u = Q[top++];
				for(w = FirstAdjVex(G, u); w >= 1; w = NextAdjVex(G, u, w))
				{
					if(!visited[w])
					{
						visited[w] = 1;
						Visit(G.vertices[w]);
						Q[++tail] = w;
					}
				}
			}
		}
	}
	printf("以上为图的广度优先遍历！\n");
}

void Visit(VNode V){
	if(strcmp(V.data.ver_name, "#"))
		printf("结点名称为：%s\n", V.data.ver_name);
	if(V.data.ver_info != 0)
		printf("结点值为：%d\n", V.data.ver_info); 
}

status FindArcNode(ALGraph G, int v, int w){
	ArcNode *N = G.vertices[v].firstarc;
	while(N != NULL)
	{
		if(N->adjvex == w)
			return OK;
		N = N->nextarc;
	}
	return ERROR;
}

status MenuInsert(Menu *M, ALGraph G, char name[GRAPH_NAME_SIZE]){
	MenuName *newbase;
	if(M->length >= M->menusize)
	{
		newbase = (MenuName*)realloc(M->menuname, (++M->menusize) * sizeof(MenuName));	
		if(!newbase)
			exit(OVERFLOW);
		M->menuname = newbase;
	}
	strcpy((M->menuname + M->length)->name, name);
	(M->menuname + M->length)->graph = G;
	M->length++;	
	return OK;	
}

status NewGraph(ALGraph *G){
	int i = 1;
	G->vertices = (AdjList *)malloc((MAX_VERTEX_NUM + 1) * sizeof(AdjList));
	for(i = 1;i <= MAX_VERTEX_NUM;i++)
	{
		G->vertices[i].firstarc = NULL;
		strcpy(G->vertices[i].data.ver_name, "#");
		G->vertices[i].data.ver_info = 0;
	}
	G->arcnum = 0;
	G->vexnum = 0;
	G->kind = 0;
	return OK;
}

int FindGraph(Menu M, char name[GRAPH_NAME_SIZE]){
	int i = 0;
	for(;i < M.length; i++)
	{
		if(!strcmp(M.menuname[i].name, name))
			return i;
	}
	return -1;
}

ALGraph ChooseGraph(Menu M, char name[GRAPH_NAME_SIZE]){
	int i = FindGraph(M, name);
	ALGraph G;
	G.vexnum = 0;
	if(i == -1)
		return G;
	else
		return M.menuname[i].graph;
}

status MenuDelete(Menu *M, char name[GRAPH_NAME_SIZE]){
	int loc = FindGraph(*M, name);
	if(loc == -1)
		return ERROR;
	DestroyGraph(&M->menuname[loc].graph);
	for(;loc < M->length - 1; loc++)
		M->menuname[loc] = M->menuname[loc + 1];
	M->length--;
	return OK;
}

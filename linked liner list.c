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
#define SPEC 2 

typedef int status; 
typedef int ElemType; 

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define NAME_MAX_SIZE 20
typedef struct Lnode{  
	ElemType data;
	struct Lnode *next;
}Lnode, *Linklist;

typedef struct Lname{
	char name[NAME_MAX_SIZE];
	Lnode *lists;
}Lname;

typedef struct Slist{
	Lname listname;
	struct Slist *next;
}Slist, *LinkSlist;

#define LENG sizeof(struct Lnode)
#define SLENG sizeof(struct Slist)

status IntiaList(Lnode **head);
status DestroyList(Lnode **head);
status ClearList(Lnode *head);
status ListEmpty(Lnode *head);
int ListLength(Lnode *head);
status GetElem(Lnode *head,int i,ElemType *e);
int LocateElem(Lnode *head,ElemType e,status (*Compare) (ElemType x,ElemType y));
status PriorElem(Lnode *head,ElemType cur_e,ElemType *pre_e);
status NextElem(Lnode *head,ElemType cur_e,ElemType *next_e);
status ListInsert(Lnode *head,int i,ElemType e);
status ListDelete(Lnode *head,int i,ElemType *e);
status ListTrabverse(Lnode *head); 
status Compare(ElemType x,ElemType y);
status IntiaSList(Slist **shead);
status DestroySList(Slist **shead);
status SListInsert(Slist *shead, int i, char name[NAME_MAX_SIZE]);
status SListDelete(Slist *shead, int i, char name[NAME_MAX_SIZE]);

void main(void){
    Linklist head = NULL;  
	LinkSlist shead = NULL;
	int op=1;
    FILE *fp;
    while(op)
	{	
	  	int e = 0, i = 0, flag = 0, cur_e = 0, pre_e = 0, next_e = 0;
	  	char name[NAME_MAX_SIZE];
		system("cls");	printf("\n\n");
		printf("      Menu for Chain Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. IntiaList       7. LocateElem\n");
		printf("    	  2. DestroyList     8. PriorElem\n");
		printf("    	  3. ClearList       9. NextElem \n");
		printf("    	  4. ListEmpty      10. ListInsert\n");
		printf("    	  5. ListLength     11. ListDelete\n");
		printf("    	  6. GetElem        12. ListTrabverse\n");
		printf("-------------------------------------------------\n");
		printf("    	 13. DataLoad       16. DestroySList\n");
		printf("    	 14. DataSave       17. SListInsert\n");
		printf("    	 15. IntiaSList     18. SListDelete\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~18]:");
		scanf("%d",&op);
		if(op > 0 && op < 15)
		{
			if(shead != NULL)
		    {
				head = NULL; 
		    	if(op == 1)
				{
					printf("���Ѵ�����\n");
					getchar();
					getchar();
					continue;
				}
				char name[NAME_MAX_SIZE]; 
				printf("������Ҫ�����ı�����ƣ�\n");
				scanf("%s",name);
		    	Slist *loc = shead->next;
		    	while(loc != NULL)
		    	{
		    		if(!strcmp(loc->listname.name,name))
		    			break;
		    		loc = loc->next;
				}
				if(loc == NULL)	
				{
					printf("����������ڣ�\n");
					getchar();
					getchar();
					continue;	
				}
		   		head = loc->listname.lists;		
			}
		}
	    switch(op){
		    case 1:
			//IntiaList
			if(IntiaList(&head)==OK) 
				printf("���Ա����ɹ���\n");
			else 
				printf("���Ա���ʧ�ܣ�\n");
			getchar();
			getchar();
			break;
		    case 2:
		   	//DestroyList
			if(head == NULL)
				printf("���Ա�δ������\n");
			else
			{
				DestroyList(&head);	
				printf("���Ա����ٳɹ���\n"); 
			}
			getchar();
			getchar();
			break;
		    case 3:
		    //ClearList
			if(head == NULL)
				printf("���Ա�δ������\n");
			else
			{
				ClearList(head);	
				printf("���Ա�����ɹ���\n"); 
			}
			getchar();
			getchar();
			break;
		    case 4:
		    //ListEmpty
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			}	
			if(ListEmpty(head) == OK)
				printf("���Ա�Ϊ�գ�\n"); 
			else
				printf("���Ա�Ϊ�գ�\n");
			getchar();
			getchar();
			break;
		    case 5:
			//ListLength
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			}	
			printf("���Ա���Ϊ%d!\n",ListLength(head));
			getchar();
			getchar();
			break;
		    case 6:
		    //GetElem
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			}
			printf("��������Ҫ��ѯ��Ԫ�ص�λ�ã�\n");
			scanf("%d",&i);
			if(GetElem(head, i, &e) == ERROR)	
				printf("���Ա����޶�ӦԪ��!\n");
			else
				printf("���Ա���%dλ�õ�Ԫ��Ϊ%d\n",i,e); 
			getchar();
			getchar();
			break;
		    case 7:
		    //LocateElem
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			}
			printf("��������Ҫ��ѯ��Ԫ�أ�\n");
			scanf("%d",&e);
			i = LocateElem(head, e, Compare);
			if(i == ERROR)	
				printf("���Ա����޶�ӦԪ��!\n");
			else
				printf("���Ա�������������ϵ��Ԫ�ص�λ��Ϊ%d\n",i); 
			getchar();
			getchar();
			break;
		    case 8:
		    //PriorElem
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			}
			printf("��������Ҫ��ѯ��Ԫ�أ�\n");
			scanf("%d",&cur_e);
			flag = PriorElem(head, cur_e, &pre_e); 
			if(flag == ERROR)	
				printf("���Ա����޶�ӦԪ��!\n");
			else if(flag == SPEC)
				printf("��Ԫ��Ϊ��һ��Ԫ�أ���ǰ����\n"); 
			else
				printf("Ԫ��%d��ǰ��Ϊ%d!\n",cur_e,pre_e);
			getchar();
			getchar();
			break;
		    case 9:
			//NextElem 
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			}
			printf("��������Ҫ��ѯ��Ԫ�أ�\n");
			scanf("%d",&cur_e);
			flag = NextElem(head, cur_e, &next_e); 
			if(flag == ERROR)	
				printf("���Ա����޶�ӦԪ��!\n");
			else if(flag == SPEC)
				printf("��Ԫ��Ϊ���һ��Ԫ�أ��޺�̣�\n"); 
			else
				printf("Ԫ��%d�ĺ��Ϊ%d!\n",cur_e,next_e);
			getchar();
			getchar();
			break;
		    case 10:
		    //ListInsert
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			}
			printf("��������Ҫ�����Ԫ�ص�λ�ã�\n");
			scanf("%d",&i);
			printf("��������Ҫ�����Ԫ�أ�\n");
			scanf("%d",&e);
			flag = ListInsert(head, i, e); 
			if(flag == ERROR)	
				printf("����ʧ��! ����λ�ô���!\n");
			else if(flag == OVERFLOW)
				printf("����ʧ��! �ռ����!\n"); 
			else
				printf("����ɹ�!\n");
			getchar();
			getchar();
			break;
		    case 11:
			//ListDelet
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			}
			printf("��������Ҫɾ����Ԫ�ص�λ�ã�\n");
			scanf("%d",&i);
			flag = ListDelete(head, i, &e); 
			if(flag == ERROR)	
				printf("ɾ��ʧ��! ����λ�ô���!\n");
			else
				printf("ɾ���ɹ�! ��ɾ����Ԫ��Ϊ%d!\n",e);
			getchar();
			getchar();
			break;
		    case 12:
			//ListTrabverse 
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			} 
			if(!ListTrabverse(head)) printf("���Ա��ǿձ�\n");
			getchar();
			getchar();
			break;
		    case 0:
	        break;
			case 13:
	        //DataLoad
	        if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			} 
	        if((fp = fopen("test.txt","r")) == NULL)
	        {
	        	printf("�ļ��޷���!\n");
				break;
			}
			for(i = 1; fscanf(fp, "%d", &e) == 1; i++)  
				ListInsert(head, i, e);
			fclose(fp);
			printf("�ļ���ȡ�ɹ���\n");
			getchar();
			getchar();
			break;
			case 14:
			//DataSave
			if(head == NULL)
			{
				printf("���Ա�δ������\n");
				getchar();
				getchar();
				break;
			} 
			if((fp = fopen("stest.txt","w")) == NULL)
			{
				printf("�ļ��޷���!\n");
				break;
			}
			Lnode *n =head->next;
			while(n != NULL)
			{
				fprintf(fp, "%d ", n->data);
				n = n->next;
			}
			fclose(fp);	
			printf("�ļ�����ɹ���\n");
			getchar();
			getchar();
			break;
			case 15:
			//IntiaSList
			if(IntiaSList(&shead)==OK) 
				printf("�����Ա����ɹ���\n");
			else 
				printf("�����Ա���ʧ�ܣ�\n");
			getchar();
			getchar();
			break;
			case 16:
			//DestroySList
			if(shead == NULL)
				printf("�����Ա�δ������\n");
			else
			{
				DestroySList(&shead);	
				printf("�����Ա����ٳɹ���\n"); 
			}
			getchar();
			getchar();
			break;
			case 17:
			//SListInsert
			if(shead == NULL)
			{
				printf("�����Ա�δ������\n");
				getchar();
				getchar();
				break;	
			}	
			printf("��������Ҫ����ı��λ�ã�\n");
			scanf("%d",&i);
			printf("��������Ҫ����ı�����ƣ�\n");
			scanf("%s",name);
			flag = SListInsert(shead, i, name); 
			if(flag == ERROR)	
				printf("����ʧ��! ����λ�ô���!\n");
			else if(flag == OVERFLOW)
				printf("����ʧ��! �ռ����!\n"); 
			else
				printf("����ɹ�!\n");
			getchar();
			getchar();
			break;
			case 18:
			//SListDelete
			if(shead == NULL)
			{
				printf("�����Ա�δ������\n");
				getchar();
				getchar();
				break;	
			}
			printf("��������Ҫɾ���ı��λ�ã�\n");
			scanf("%d",&i);
			flag = SListDelete(shead, i, name); 
			if(flag == ERROR)	
				printf("ɾ��ʧ��! ����λ�ô���!\n");
			else
				printf("ɾ���ɹ�! ��ɾ����Ԫ��Ϊ%s!\n",name);
			getchar();
			getchar();
			break;	
		}
	}
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}

status IntiaList(Lnode **head){
	Lnode *L;
	L = (Lnode *)malloc(LENG);
	if(!L)
		return OVERFLOW;
	L->next = NULL;
	*head = L;
	return OK;
}

status IntiaSList(Slist **shead){
	Slist *S;
	S = (Slist *)malloc(SLENG);
	if(!S)
		return OVERFLOW;
	S->next = NULL;
	*shead = S;
	return OK;
}

status DestroyList(Lnode **head){
	Lnode *p , *n;
	p = *head;
	n = p->next;
	while(n != NULL)
	{
		free(p);
		p = n;
		n = n->next;		
	}
	free(p);
	*head = NULL;
	return OK;	
}

status DestroySList(Slist **shead){
	Slist *s, *t;
	s = *shead;
	t = s->next;
	if(t != NULL)
	{
		while(t != NULL)
		{
			DestroyList(&(s->listname.lists));
			free(s);
			s = t;
			t = t->next;
		}
		free(s);
	}
	else
		free(s);
	*shead = NULL;
	return OK;
}

status ClearList(Lnode *head){
	Lnode *p, *n;
	p = head;
	n = p->next;
	if(n == NULL)
		return OK;
	else
	{
		p = n;
		n = n->next;
		while(n != NULL)
		{
			free(p);
			p = n;
			n = n->next;		
		}
		free(p);
	}
	head->next = NULL;
}

status ListEmpty(Lnode *head){
	Lnode *p = head->next;
	if(p != NULL)
		return ERROR;
	else
		return OK;
}

int ListLength(Lnode *head)
{
	Lnode *p = head->next;
	int length = 0;
	while(p != NULL)
	{
		length++;
		p = p->next;
	}
	return length;
}

status GetElem(Lnode *head, int i, ElemType *e){
	int length = ListLength(head);
	if(i < 1 || i > length)
		return ERROR;
	Lnode *n;
	n = head;
	while(i--)
		n = n->next;
	*e = n->data;
	return OK;
}

int LocateElem(Lnode *head,int e,status (*Compare)(ElemType x,ElemType y)){
	Lnode *n = head->next;
	int loc = 1;
	while(n != NULL)
	{
		if(Compare(n->data, e))
			return loc;
		loc++;
		n = n->next;
	}
	return ERROR;
}

status PriorElem(Lnode *head, ElemType cur_e, ElemType *pre_e){
	Lnode *n = head->next, *p = head;
	if(n == NULL)
		return ERROR;
	else
	{
		if(n->data == cur_e)
			return SPEC;
		else
		{
			while(n->next != NULL)
			{
				p = n;
				n = n->next;
				if(n->data == cur_e)
				{
					*pre_e = p->data;
					return OK;	
				}
			}
			return ERROR;	
		}		
	}
}

status NextElem(Lnode *head, ElemType cur_e, ElemType *next_e){
	Lnode *n = head->next;
	if(n == NULL)
		return ERROR;
	else
	{
		while(n->next != NULL)
		{
			if(n->data == cur_e)
			{
				*next_e = n->next->data;
				return OK;
			}
			n = n->next;
		}
		if(n->data == cur_e)
			return SPEC;
		return ERROR;
	}
}

status ListInsert(Lnode *head, int i, ElemType e){
	if(i < 1)
		return ERROR;
	Lnode *n = head, *newnode;
	while(--i)
	{
		n = n->next;
		if(n == NULL)
			return ERROR;	
	}
	newnode = (Lnode *)malloc(LENG);
	if(!newnode)
		return OVERFLOW;
	newnode->next = n->next;
	n->next = newnode;
	newnode->data = e;
	return OK;
}

status SListInsert(Slist *shead, int i, char name[NAME_MAX_SIZE]){
	if(i < 1)
		return ERROR;
	Slist *n = shead, *newnode;
	while(--i)
	{
		n = n->next;
		if(n == NULL)
			return ERROR;	
	}
	newnode = (Slist *)malloc(SLENG);
	if(!newnode)
		return OVERFLOW;
	newnode->next = n->next;
	n->next = newnode;
	strcpy(newnode->listname.name, name);
	IntiaList(&(newnode->listname.lists));
	return OK;
}

status ListDelete(Lnode *head, int i, ElemType *e){
	if(i < 1)
		return ERROR;
	Lnode *n = head, *denode;
	while(--i)
	{
		n = n->next;
		if(n->next == NULL)
			return ERROR;	
	}
	denode = n->next;
	*e = denode->data;
	n->next = n->next->next;
	free(denode);
	return OK;
}

status SListDelete(Slist *shead, int i, char name[NAME_MAX_SIZE]){
	if(i < 1)
		return ERROR;
	Slist *n = shead, *denode;
	while(--i)
	{
		n = n->next;
		if(n == NULL)
			return ERROR;	
	}
	denode = n->next;
	strcpy(name,denode->listname.name);
	n->next = n->next->next;
	free(denode);
	return OK;
}

status ListTrabverse(Lnode *head){
	Lnode *n = head->next;
	if(n == NULL)
		return ERROR;
    printf("\n-----------all elements -----------------------\n");
    while(n != NULL)
    {
   		printf("%d ",n->data);
   		n = n->next;
    }
    printf("\n------------------ end ------------------------\n");
    return OK;
}

status Compare(ElemType x,ElemType y)
{
	if(x > y)
		return OK;
	else
		return ERROR;
}

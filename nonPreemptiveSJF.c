#include <stdio.h>
#include <stdlib.h>

struct Process
{
	int id;
	int at;
	int bt;
	int tat;
	int wt;
	int ct;
};

struct node
{
	struct Process data;
	struct node* next;
};

int curr_time = 0;

struct Process createProcess()
{
	struct Process p;
	printf("Id : ");
	scanf_s("%d", &p.id);
	printf("Arrival Time of Process %d : ", p.id);
	scanf_s("%d", &p.at);
	printf("Burst Time of Process %d : ", p.id);
	scanf_s("%d", &p.bt);
	p.tat = -1;
	p.wt = -1;
	p.ct = -1;
	return p;
}

void printProcess(struct Process p)
{
	printf("\nProcess Id : %d\nArrival Time : %d\nBurst Time : %d\nTurnAround : %d\nWaiting Time : %d\nCompletion Time : %d\n\n", p.id, p.at, p.bt, p.tat, p.wt, p.ct);
}

struct node* insertProcess(struct node* head, struct Process p)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = p;
	newNode->next = NULL;
	struct node* temp = head;
	
	if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}
	return head;
}

struct node* deleteProcess(struct node* head, int deletionId)
{
	if (head == NULL)
		return NULL;
	struct node* temp = head;
	struct node* fr = NULL;
	if (head->data.id == deletionId)
	{
		fr = head;
		head = head->next;
		free(fr);
	}
	else
	{
		while (temp->next != NULL && temp->next->data.id != deletionId)
		{
			temp = temp->next;
		}
		if (temp->next == NULL)
		{
			printf("Id not in List\n");
			return NULL;
		}
		else
		{
			fr = temp->next;
			temp->next = temp->next->next;
			free(fr);
		}
	}
	return head;
}

void printList(struct node* head)
{
	struct node* temp = head;
	while (temp != NULL)
	{
		printProcess(temp->data);
		temp = temp->next;
	}
}

void addAvlProcess(struct node** ptrToAllProcessHead, struct node** ptrToAvlProcessHead, int n)
{
	if (*ptrToAllProcessHead == NULL)
		return;
	struct node* temp = *ptrToAllProcessHead;
	struct Process pToAdd;
	int* idToDeleteArr = (int*)malloc(sizeof(int)*n);
	int idCount = 0;
	while (temp != NULL)
	{
		if (temp->data.at <= curr_time)
		{
			idToDeleteArr[idCount] = temp->data.id;
			idCount++;
			pToAdd = temp->data;
			*ptrToAvlProcessHead = insertProcess(*ptrToAvlProcessHead, pToAdd);
		}
		temp = temp->next;
	}
	for (int i = 0; i < idCount; i++)
	{
		int deletionId = idToDeleteArr[i];
		*ptrToAllProcessHead = deleteProcess(*ptrToAllProcessHead, deletionId);
	}
}

void executeProcess(struct Process p)
{
	static int finishProcessCount = 0;
	curr_time = curr_time + p.bt;
	p.ct = curr_time;
	p.tat = p.ct - p.at;
	p.wt = p.tat - p.bt;
	printf("\n--------------------------\n\n");
	printf("\tFINSHED PROCESS\n");
	printProcess(p);
	printf("\n--------------------------\n\n");
}

void selectSJF(struct node** ptrToAvlProcessHead)
{
	struct node* temp = *ptrToAvlProcessHead;
	int smallestBt = (*ptrToAvlProcessHead)->data.bt;
	struct node* smallestNode = (*ptrToAvlProcessHead);
	while (temp != NULL)
	{
		if (temp->data.bt < smallestBt)
		{
			smallestNode = temp;
		}
		temp = temp->next;
	}
	executeProcess(smallestNode->data);
	*ptrToAvlProcessHead = deleteProcess(*ptrToAvlProcessHead, smallestNode->data.id);
}

int main()
{
	int n;
	printf("Enter Number of Process : ");
	scanf_s("%d", &n);
	struct node* allProcessHead = NULL;
	struct node* avlProcessHead = NULL;
	for (int i = 0; i < n; i++)
	{
		struct Process p = createProcess();
		allProcessHead = insertProcess(allProcessHead, p);
	}
	while (allProcessHead != NULL || avlProcessHead != NULL)
	{
		addAvlProcess(&allProcessHead, &avlProcessHead, n);
		selectSJF(&avlProcessHead);
	}
}

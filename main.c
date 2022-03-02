#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int n;			// number of nodes
	int *visited;	// visit check array
	int **adj_mat;	// adjaceny matrix
} TreeType;

typedef struct {
	int top;
	int size;		// stack size
	int *stack;		// stack array
} StackType;

/*typedef struct {
	int *data;	//ť ������ �迭
	int front, rear;
}QueueType;*/

typedef struct {

	int front, rear;

	int size; // queue size = �迭 ũ��

	int *queue; // queue array

} QueueType;

void init(QueueType *q, int no) {
	q->front = q->rear = 1;
	q->size = no;
	q->queue = (int *)malloc(sizeof(int) * (q->size + 1)); //�迭 ����

	for (int i = 1; i <= no; i++)	//�迭 �ʱ�ȭ
		q->queue[i] = 0;
}

int is_empty(QueueType *q) {
	return (q->front == q->rear);
}

int is_full(QueueType *q) {
	return((q->rear + 1) % q->size == q->front);
}

void enqueue(QueueType *q, int item) {
	if (is_full(q, q->size))
		printf("ť�� ��ȭ�����Դϴ�\n");
	q->rear = (q->rear + 1) % q->size;
	q->queue[q->rear] = item;
}

int dequeue(QueueType *q) {
	if (is_empty(q))
		printf("ť�� ���� �����Դϴ�\m");
	q->front = (q->front + 1) % q->size;
	return q->queue[q->front];
}

void makeTree(TreeType *tr, int no)
{
	tr->n = no;
	tr->visited = (int *)malloc(sizeof(int) * (no + 1));
	tr->adj_mat = (int **)malloc((sizeof(int *) * (no + 1)));
	for (int i = 1; i <= no; i++) {
		tr->adj_mat[i] = (int *)malloc(sizeof(int) * (no + 1));
		tr->visited[i] = 0;
	}
	for (int i = 1; i <= no; i++) {
		tr->visited[i] = 0;
		for (int j = 1; j <= no; j++)
			tr->adj_mat[i][j] = 0;
	}
}

// ���� ��ķ� ǥ���� Ʈ���� ���� ���� �켱 Ž��
void DFS(TreeType *tr, int v)
{
	int w;
	tr->visited[v] = 1;		// ���� v�� �湮 ǥ�� 
	printf("%d ", v);		// �湮�� ���� ���
	for (w = 1; w <= tr->n; w++) 		// ���� ���� Ž��
		if (tr->adj_mat[v][w] && !tr->visited[w])
			DFS(tr, w);	//���� w���� DFS ���ν���
}

//���� ��ķ� ǥ���� Ʈ���� ���� ���� �켱 Ž��
void BFS(TreeType *tr, int v) {
	int w;
	tr->visited[v] = 1; //���� v�� �湮 ǥ��
	printf("%d ", v);//��Ʈ���
	for (w = 1; w <= tr->n; w++) 		// ���� ���� Ž��
		if (tr->adj_mat[v][w] && !tr->visited[w])
			BFS(tr, w);	//���� w���� DFS ���ν���
}

//���� ��ķ� ǥ���� Ʈ���� ���� ���� �켱 Ž�� [ť]
void BFS_queue(TreeType *tr, int v, int no) {
	int w;
	QueueType q;
	init(&q, no);
	tr->visited[v] = 1;
	printf("%d ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = 1; w <= tr->n; w++)
			if (tr->adj_mat[v][w] && !tr->visited[w]) {
				tr->visited[w] = 1;
				printf("%d ", w);
				enqueue(&q, w);
			}
	}
}

void st_push(StackType *st, int n)
{
	if (st->top == st->size - 1)
		return;		// full
	st->stack[++(st->top)] = n;
}

int st_pop(StackType *st)
{
	if (st->top == -1)
		return;		// empty
	return st->stack[(st->top)--];
}

void DFS_stack(TreeType *tr, int v)
{
	StackType st;
	int w;

	st.top = -1;
	st.size = tr->n + 1;
	st.stack = (int *)malloc(sizeof(int) * st.size);
	st_push(&st, v);
	tr->visited[v] = 1;		// ���� v�� �湮 ǥ�� 
	while (st.top != -1) {
		v = st_pop(&st);
		printf("%d ", v);		// �湮�� ���� ���
								//		for (w = 1; w <= tr->n; w++) 		// ���� ���� Ž��
		for (w = tr->n; w >= 1; w--) 		// ���� ���� Ž��
			if (tr->adj_mat[v][w] && !tr->visited[w]) {
				st_push(&st, w);
				tr->visited[w] = 1;		// ���� v�� �湮 ǥ�� 
			}
	}
}

void addTreeEdge(TreeType *tr, int a, int b)
{
	tr->adj_mat[a][b] = 1;
}

void main()
{
	TreeType tr1;
	int no, v;

	//	printf("Type the number of nodes in tree1: ");
	//	scanf("%d", &no);
#if 1
	no = 7;
	makeTree(&tr1, no);
	addTreeEdge(&tr1, 1, 2);
	addTreeEdge(&tr1, 1, 7);
	addTreeEdge(&tr1, 2, 3);
	addTreeEdge(&tr1, 2, 6);
	addTreeEdge(&tr1, 3, 1);
	addTreeEdge(&tr1, 3, 4);
	addTreeEdge(&tr1, 3, 5);
#else
	no = 4;
	makeTree(&tr1, no);
	addTreeEdge(&tr1, 1, 2);
	addTreeEdge(&tr1, 1, 3);
	addTreeEdge(&tr1, 2, 3);
	addTreeEdge(&tr1, 3, 1);
	addTreeEdge(&tr1, 3, 4);
	addTreeEdge(&tr1, 4, 4);
#endif

	printf("Type the number of start node in tree1 for DFS(1~%d): ", no);
	scanf("%d", &v);
	DFS(&tr1, v);
	for (int i = 0; i <= no; i++)
		tr1.visited[i] = 0;
	printf("\n");
	DFS_stack(&tr1, v);
	printf("\n");


	printf("BFS ť\n");
	printf("Type the number of start node in tree1 for BFS(1~%d): ", no);
	scanf("%d", &v);
	/*BFS(&tr1, v);*/
	for (int i = 0; i <= no; i++)
		tr1.visited[i] = 0;
	printf("\n");
	BFS_queue(&tr1, v, no);	//ppt ���� BFS�� �°� ��ȯ + ����+ BFS �Լ� �����
}


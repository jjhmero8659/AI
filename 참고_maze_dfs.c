#include <stdio.h>



#include <stdlib.h>



#include <time.h>



/*�������*/

#define ROW 30
#define COL 40

#define STACK_SIZE ROW * COL  /*������ �ִ� ũ��*/

#define TRUE 1                /*TRUE*/

#define FALSE 0                /*FALSE*/

int total_visit = 0;
int goal_path = 0;



typedef struct {                /*element*/
	short int row;
	short int col;
	short int dir;
}element;



typedef struct {
	short int vert;
	short int horiz;
}offsets;



/*��������*/



offsets move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };/*���� ǥ��*/

element stack[STACK_SIZE];



int maze[ROW][COL];                /*�̷� ����*/

int mark[ROW][COL];                /*������ �� ǥ���� ����*/

int direction[ROW][COL];          /*�̵� ���� ����*/

int i, j, row, col, next_row, next_col, dir, found = FALSE;

int top;



int maze[ROW][COL] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,1},
{1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,1,0,0,1},
{1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,1,0,1,1,1,1,1,0,1,0,0,1},
{1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,0,0,0,1,0,1,0,0,1},
{1,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,1,0,1,0,0,1},
{1,1,1,1,0,1,0,0,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,1,0,0,0,0,0,0,0,1,1,0,1},
{1,0,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1},
{1,0,1,0,0,1,0,1,0,1,0,1,0,1,1,0,0,1,0,0,1,1,0,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,0,1},
{1,0,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,1,1,0,1,0,1,1,1,0,1,0,1,0,0,0,0,1,0,1,0,1},
{1,0,0,1,1,0,0,1,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,1,0,1},
{1,1,0,1,1,1,0,0,1,1,0,1,0,1,1,1,0,1,0,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1},
{1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,1,1,1,0,1,0,1,0,1,0,1,0,0,1},
{1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,0,1,0,1},
{1,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,0,1,0,1},
{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,0,1,0,0,0,1,1,1,1,0,1},
{1,0,1,1,1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,0,0,0,1},
{1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,0,1,1,1,0,1,1,0,1},
{1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,1,1,0,0,1,1,0,1},
{1,0,0,1,1,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,1,0,1},
{1,1,0,0,0,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1},
{1,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,1,1,0,1,0,1,0,1,1,1,0,1,1,0,0,0,0,0,0,1,0,1,0,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1},
{1,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,0,0,1,0,0,0,0,0,0,0,1},
{1,1,0,1,0,1,0,1,1,0,1,1,0,1,1,1,0,0,0,1,0,1,0,1,0,0,0,0,1,1,0,1,0,1,0,1,0,1,0,1},
{1,0,0,1,0,1,0,1,0,0,1,0,1,1,0,0,1,1,0,1,0,1,0,1,0,1,1,0,1,1,1,1,0,1,0,0,1,1,0,1},
{1,1,0,0,0,1,0,1,0,1,1,0,1,0,0,1,1,1,0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,1,1,1,1,1,0,1},
{1,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};




void push(int* top, element position)            /*���ÿ� Ǫ��*/

{

	(*top)++;

	stack[*top].row = position.row;

	stack[*top].col = position.col;

	stack[*top].dir = position.dir;

}



element pop(int* top)                    /* ���ÿ��� ��*/

{
	element result;
	if (*top < 0) {
		printf("Stack is Empty.\n");
	}

	else {
		result = stack[*top];
		(*top)--;
	}
	return result;
}





element peek(int* top)                   /* ���ÿ��� ��*/

{
	element result;
	if (*top < 0) {
		printf("Stack is Empty.\n");
	}
	else {
		result = stack[*top];
	}
	return result;
}





void find_path()

{

	/*�̷��� ���� ã�Ƽ� ������ ���ÿ� ����*/

	element position;

	mark[1][1] = 1;

	top = 0;

	stack[0].row = 1;

	stack[0].col = 1;

	stack[0].dir = 1;



	while (top > -1 && !found)

	{
		total_visit++;
		position = pop(&top);                        /*������ top�� ����*/

		row = position.row;

		col = position.col;

		dir = position.dir;

		while (dir < 8 && !found)                /*dir�������� �̵��� ���� ������ �̵� ������ �ٽ� ���ƿ�*/
		{
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;
			if (next_row == ROW - 1 && next_col == COL - 1)  /*�ⱸ�� ã���� ���� ã�Ҵٰ� ǥ������*/
			{
				found = TRUE;
			}

			else if (!maze[next_row][next_col] && !mark[next_row][next_col])
			{
				
				mark[next_row][next_col] = TRUE;

				direction[row][col] = dir;

				position.row = row;

				position.col = col;

				position.dir = dir++;/*���� ����*/

				push(&top, position);                /*���ÿ� ����*/

				row = next_row;

				col = next_col;

				dir = 0;

			}

			else ++dir;

		}

	}

}





void print_path()

{

	/*���� ã���� ���*/

	if (found)

	{

		for (i = 0; i < ROW; i++)                 /*stack�� �̿��ϱ����ؼ� �ʱ�ȭ*/

		{

			for (j = 0; j <= COL; j++)

			{

				mark[i][j] = 0;

			}

		}



		printf("The path is : \n");

		printf("row col\n");







		for (i = 0; i <= top; i++)

		{
			goal_path++;
			printf("!!%2d%5d\n", stack[i].row, stack[i].col);
			mark[stack[i].row][stack[i].col] = 1;           /*stack�� ������ִ� �κи� ��� ���!*/

		}



		printf("%2d%5d\n", row, col);

		printf("\n�̵���θ� ����մϴ�.\n");

		printf("\n");



		for (row = 0; row < ROW; row++)

		{

			for (col = 0; col < COL; col++)

			{

				if ((row == 1) && (col == 1))

				{

					printf(" S");

				}



				else if ((row == ROW - 2) && (col == COL - 2))

				{

					printf(" E");

				}







				else

				{

					if ((mark[row][col] == FALSE)) /*mark ���� �ƴϸ� XȤ�� ��������ä��*/

					{
						if (maze[row][col] == 1)  /* ���ΰ�쿡 X*/

						{

							printf("%2c", 'X');

						}

						else               /*���� �ƴѰ�쿡�� �������� ���*/

						{

							printf("%2c", ' ');

						}

					}

					else

					{

						switch (direction[row][col])  /*���⿡���� ǥ��*/

						{

						case 0:

							printf("��");

							break;

						case 1:

							printf("��");

							break;

						case 2:

							printf("��");

							break;

						case 3:

							printf("��");

							break;

						case 4:

							printf("��");

							break;

						case 5:

							printf("��");

							break;

						case 6:

							printf("��");

							break;

						case 7:

							printf("��");

							break;

						}

					}

				}

			}

			printf("\n");

		}

	}

	else printf("----have no path---\n");

}















int main(void)

{

	find_path();

	print_path();
	printf("total_visit : %d \n",total_visit+ goal_path);
	printf("goal_path : %d \n\n\n\n", goal_path);
	return 0;

}

































/*
typedef struct node{
	int data;
	struct node* next;
}NODE;

NODE* head = NULL;
NODE** tmp = NULL;
//��� ����
NODE* init(int data) {
	NODE* new = (NODE*)malloc(sizeof(NODE));

	new->data = data;
	new->next = NULL;

	return new;
}
//��� add
void add(NODE** head_ptr, int data) {
	if ((*head_ptr) == NULL) {
		NODE* new = init(data);
		(*head_ptr) = new;
		return;
	}

	add(&(*head_ptr)->next, data);
}

//��� ����
void insert(NODE** head_ptr,int index, int data) {
	int cnt = 1;

	while ((cnt != index) && ((head_ptr) != NULL)) {
		head_ptr = &(*head_ptr)->next;
		cnt++;
	}

	if (cnt == index) {
		NODE* new = init(data);
		new->next = (*head_ptr);
		(*head_ptr) = new;
		return;
	}
}

//��� ����
void delete(NODE** head_ptr, int data) {

	if ((*head_ptr) == NULL) {
		printf("������ �����Ͱ� �����ϴ�.\n");
		return;
	}

	if ((*head_ptr)->data == data) { //�����Ͱ� ������
		NODE* target = (*head_ptr);
		(*head_ptr) = (*head_ptr)->next;
		free(target);
		return;
	}

	delete(&((*head_ptr)->next), data);
}
//��� ���
void print(NODE ** head_ptr) {
	if (*head_ptr != NULL) {
		printf("%d\n", (*head_ptr)->data);
		print(&(*head_ptr)->next);
	}
	else
		return;
}
/*
void peek() {
	NODE* tmp = head;
	while (tmp) {
		printf("%d \n", tmp->data);
		tmp = tmp->next;
	}
}*//*

void print2(NODE* head_copy) {
	if (head_copy != NULL) {
		printf("%d\n", head_copy->data);
		print2(head_copy->next);
	}
	else
		return;
	
}

int insert1(NODE** p, int index, int new_data) {
	// p : 0x1000
	// index : 0
	// new_data : 100
	// cnt : 0
	int cnt = 0;
	while (cnt != index && *p != NULL) {
		p = &(*p)->next;
		cnt++;
	}
	if (cnt == index) {
		// new_node = 0x500
		NODE* new_node = init(new_data);
		new_node->next = *p;
		*p = new_node;
		return TRUE;
	}
	return FALSE;
}

int remove(NODE** parent, int data) {
	// parent : ������ ����� �� ��� ��, next�� �ּ� 
	//          head�� �ּ� 
	//			==> ������ ����� �ּҰ� �־��� ���� �ּ�
	if (*parent == NULL) {
		printf("�������� \n");
		return FALSE;
	}

	if ((*parent)->data == data) { // ���� ����
		NODE* target = *parent;
		*parent = target->next;
		free(target);
		return TRUE;
	}

	remove(&(*parent)->next, data); // ���� ��带 ������� remove() ���ȣ��
}

int main() {
	add(&head, 10);
	add(&head, 20);
	add(&head, 30);


	//peek();
	printf("\n");
	print(&head);
	printf("\n");
	//print2(head);
	printf("\n");

	delete(&head, 0);
	//remove(&head, 20);
	print(&head);
	printf("\n");
	insert(&head, 2,500);

	print(&head);
}
*/



//���߿��� ����
/*
typedef struct node {
	struct node* previous;
	int data;
	struct node* next;
}NODE;

NODE* head = NULL;
NODE* tail = NULL;

//��� ����
NODE* init(int data) {
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->previous = NULL;
	new->data = data;
	new->next = NULL;
	return new;
}

//��� �߰�
void add(NODE ** head_ptr,int data) {
	if (head == NULL) { //������ ���
		(*head_ptr) = init(data);
		tail = (*head_ptr);
		return;
	}

	if ((*head_ptr) == NULL) {
		(*head_ptr) = init(data);
		tail = (*head_ptr);
		return;
	}

	add(&((*head_ptr)->next), data);
}

//��� ����
void insert(NODE** head_ptr,int index, int data) {
	int cnt = 1;
	
	while (cnt != index && (*head_ptr) != NULL) {
		cnt++;
		head_ptr = &((*head_ptr)->next);
	}

	if ((*head_ptr) == NULL) {
		printf("index�� �߸��Ǿ����ϴ�.\n");
		return;
	}

	if (cnt == index) {
		NODE* new = init(data);
		new->next = (*head_ptr);
		new->previous = (*head_ptr)->previous;
		(*head_ptr)->previous = new;
		(*head_ptr) = new;
		return;
	}

}

//��� ����
void delete(NODE ** head_ptr,int data) {
	if ((*head_ptr) == NULL) {
		printf("������ �����Ͱ� �����ϴ�.\n");
		return;
	}

	if ((*head_ptr)->data == data) {
		NODE* target = *head_ptr;
		if ((*head_ptr)->next == NULL) {
			tail = (*head_ptr)->previous;
			(*head_ptr) = NULL;
			free(target);
			printf("��������� �����۵�!\n");
			return;
		}
		target->next->previous = target->previous;
		*head_ptr = target->next;
		free(target);
		return;
	}

	delete(&((*head_ptr)->next), data);
}
//��� ���
void print(NODE ** head_ptr) {
	if ((*head_ptr) == NULL) {
		return;
	}
	printf("%d\n", (*head_ptr)->data);
	print(&((*head_ptr)->next));
}

int main() {
	add(&head, 10);
	add(&head, 20);
	add(&head, 30);
	add(&head, 40);
	add(&head, 50);


	print(&head);
	printf("\n");
	insert(&head, 2, 500);

	print(&head);
	printf("\n");
	delete(&head, 50);
	print(&head);
}

*/












/*
#define WIDTH 4
#define HEIGHT 4
#define TRUE  1
#define FALSE  0

int num = 0;

typedef struct{
	char name[20];
	int age;
}POINT;


void show_point(POINT *test1) {
	
	printf("%s : %d ��\n", test1->name, test1->age);
}

void buffer_clear() {
	printf("getchar�Լ��۵�\n");
	while (getchar() != '\n');
	printf("getchar�Լ���\n");
}

void scan_point(POINT* test1,void (*clear)()) {
	int len;
	printf("�̸��� �Է��ϼ��� :");
	fgets(test1->name, sizeof(test1->name), stdin);
	len = strlen(test1->name);
	test1->name[len - 1] = 0;
	printf("���ؽ�\n");
	//ikclear();
	fflush(stdout);
	printf("���̸� �Է��ϼ��� :");
	scanf_s("%d", &test1->age);
	
}

int main() {
	//POINT test;
	//scan_point(&test,buffer_clear);
	//show_point(&test);

	char* str = (char*)malloc(sizeof(char) * 10);
	char str_arr[10];

	fputs("�����Ҵ� ���ڿ� ���� �Է��ϼ��� : ", stdout);
	fgets(str, 10, stdin);
	int len = strlen(str);
	str[len - 1] = 0;
	rewind(stdin);
	fputs("�迭 ���� �Է��ϼ��� : ", stdout);
	fgets(str_arr, sizeof(str_arr), stdin);

	printf("�����Ҵ� ���ڿ� : %s\n", str); 
	printf("�迭 ���ڿ� : %s\n", str_arr);

	free(str);
}




int copy(int(*array)[WIDTH], int(*array_copy)[WIDTH]) {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++)
		{
			array[i][j] = array_copy[i][j];
		}
	}
}
void right_shift(int (*array)[WIDTH], int (*array_copy)[WIDTH], int (*cpy)(arr1,arr2)) {
	for (int total = 0; total < 2; total++) {

			for (int j = 0; j < 3; j++) {
				array_copy[j][WIDTH - (total+1)] = array[total][j];
			}
			for (int j = 0; j < 3; j++) {
				array_copy[HEIGHT-(total+1)][WIDTH-(j+1)] = array[j][WIDTH - (total+1)];
			}
			for (int j = 0; j < 3; j++) {
				array_copy[HEIGHT - (j + 1)][total] = array[HEIGHT - (total + 1)][WIDTH - (j + 1)];
			}
			for (int j = 0; j < 3; j++) {
				array_copy[total][j] = array[HEIGHT - (j + 1)][total];
			}

	}
	cpy(array,array_copy);

}

void print_arr(int (*arr)[WIDTH]) {
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

int main() {

	int arr[WIDTH][HEIGHT] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16},
	};

	int arr_copy[WIDTH][HEIGHT];

	print_arr(arr);
	printf("\n");

	right_shift(arr,arr_copy,copy);
	right_shift(arr, arr_copy, copy);
	right_shift(arr, arr_copy, copy);
	right_shift(arr, arr_copy, copy);

	print_arr(arr);

}


int fill_row(int row , int (*array)[WIDTH]) {
	for (int i = 0; i < WIDTH; i++)
	{
		if (array[row][i] == 0) {
			scanf_s("%d", &num);
			array[row][i] = num;
		}
	}
}

int fill_col(int col, int(*array)[WIDTH]) {
	for (int i = 0; i < HEIGHT; i++)
	{
		if (array[i][col] == 0) {
			scanf_s("%d", &num);
			array[i][col] = num;
		}
	}
}

int reverse_fill_row(int row, int(*array)[WIDTH]) {
	for (int i = 0; i < WIDTH; i++)
	{
		if (array[row][WIDTH - (i+1)] == 0) {
			scanf_s("%d", &num);
			array[row][WIDTH - (i + 1)] = num;
		}
	}
}

int reverse_fill_col(int col, int(*array)[WIDTH]) {
	for (int i = 0; i < HEIGHT; i++)
	{
		if (array[HEIGHT - (i+1)][col] == 0) {
			scanf_s("%d", &num);
			array[HEIGHT - (i + 1)][col] = num;
		}
	}
}
int fill_array(int (*array)[HEIGHT]) {


	for (int j = 0; j < (HEIGHT-2); j++)
	{
		fill_row(0 + j, array);
		fill_col(3 - j, array);
		reverse_fill_row(3 - j, array);
		reverse_fill_col(0 + j, array);
	}
}

int print_array(int (*arr)[WIDTH]) {
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

int main() {
	int arr[WIDTH][HEIGHT] = {0,};

	fill_array(arr);
	print_array(arr);
}*/

/*
//�ؽ� ���̺�
#define MAX 10

typedef struct node {
	int data;
	struct node* next;
}NODE;

NODE* table[MAX];

int mod(int data) {
	return data % 10;
}

NODE* init(int data) {
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->data = data;
	new->next = NULL;

	return new;
}

void add(int data) {
	int index = mod(data);
	if (table[index] == NULL) {
		table[index] = init(data);
		return;
	}
	else {
		NODE* tmp = table[index];
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = init(data);
		return;
	}
}

void print() {
	NODE* tmp;
	for (int i = 0; i < MAX; i++)
	{
		tmp = table[i];
		printf("table[%d] :", i);
		while (tmp != NULL) {
			printf("%d ", tmp->data);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

void search(int data) {
	int cnt = 1;
	NODE* tmp = table[mod(data)];
	while (tmp != NULL) {
		if (tmp->data == data) {
			printf("�ش��ϴ� �����ʹ� table[%d] �� %d ��° �Դϴ�.\n", mod(data), cnt);
			return;
		}
		cnt++;
		tmp = tmp->next;
	}
	printf("�ش��ϴ� �����Ͱ� �������� �ʽ��ϴ�.\n");
	return;
}

void delete(int data) {
	NODE** head_ptr = &table[mod(data)];

	while (TRUE) {
		if ((*head_ptr)->data == data) {
			NODE* target = *head_ptr;
			*head_ptr = target->next;
			free(target);
			return;
		}

		head_ptr = &((*head_ptr)->next);
	}
	
}


int main() {
	int select,num;

	int test = 1;
	int arr[5];
	arr[1] = test;
	while (TRUE) {
		printf("1.��� �߰� �ϱ�\n");
		printf("2.��� �˻� �ϱ�\n");
		printf("3. ��� ���� �ϱ�\n");
		printf("4. �۵� ���� �ϱ�\n");
		printf("�Է� :");
		scanf_s("%d", &select);
		if (select == 1) {
			printf("�߰��� ��� ���� �Է����ּ��� :");
			scanf_s("%d", &num);
			add(num);
			printf("test %p\n",&test);
			printf("arr[1] %d\n", arr[1]);
			printf("&arr[1] %p\n", &arr[1]);
			printf("%p\n", &table[5]);
			printf("%p\n", table[5]);
			printf("%p\n", &(table[5]->data));
			printf("%p\n", &(table[5]->next));

		}
		else if (select == 2) {
			printf("search �� data ���� �Է����ּ��� :");
			scanf_s("%d", &num);
			search(num);
			print();
		}
		else if (select == 3) {
			printf("delete �� data ���� �Է����ּ��� :");
			scanf_s("%d", &num);
			delete(num);
			print();
		}
		else {
			return;
		}
	}
}*/
/*
int add(int array1[], int size, int array2[5] = {0,}){
	int sum1 = 0;
	int sum2 = 0;
	int i;

	for (i = 0; i < size; i++)
	{
		sum1 += array1[i];
		sum2 += array2[i];
		
	}
	return (sum1 + sum2);
}
//if (array2 != 0) ���ϸ� ���� ���
//if (array2[i] != 0)  array2�� b���� �Է� �Ǵµ� ��� ������ �߻�;

int main()
{
	int a[] = { 1,2,3,4,5 };
	int b[] = { 6,7,8,9,10 };
	int c = add(a, 5);
	int d = add(a, 5, b);
	printf("c�� �� : %d\n", c);
	printf("d�� �� : %d\n", d);
}*/




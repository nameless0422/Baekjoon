#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;

typedef struct stacknode {
	element data;
	struct stacknode* link;
}stacknode;

stacknode* top;

element empty() {
	if (top == NULL) return 1;
	else return 0;
}

void push(element item) {
	stacknode* temp = (stacknode*)malloc(sizeof(stacknode));
	temp->data = item;
	temp->link = top;
	top = temp;
}

element pop() {
	element item;
	stacknode* temp = top;
	if (top == NULL) return -1;
	else {
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
}

element topf() {
	if (top == NULL) return -1;
	else {
		return top->data;
	}
}

element sizeofstack() {
	stacknode* temp = top;
	element size = 0;
	while (temp)
	{
		size++;
		temp = temp->link;
	}
	return size;
}

int main() {
	element item;
	element N;
	char string[6];
	top = NULL;
	
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf(" %s", string);
		if (strcmp(string, "push")==0) {
			scanf("%d", &item);
			push(item);
		}
		else if (strcmp(string, "top")==0) {
			printf("%d\n",topf());
		}
		else if (strcmp(string, "size") == 0) {
			printf("%d\n",sizeofstack());
		}
		else if (strcmp(string, "pop") == 0) {
			printf("%d\n", pop());
		}
		else if (strcmp(string, "empty") == 0) {
			printf("%d\n", empty());
		}
	}
}
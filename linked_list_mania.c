#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

// features to create:
// - insert/delete first, last, and into using pointer-to-node and pointer-to-pointer-to-node
// - read and write linked list from 'llmData.bin'
// - display linked list and linked list length

void displayLinkedList(Node *head);
int getLinkedListLength(Node *head);
void insertLast(Node **head, int value);
void insertFirst(Node **head, int value);
void insertInto(Node **head, int value, int index);
void insertLastPointer(Node **head, int value);
void insertIntoPointer(Node **head, int value, int index);
void deleteLast(Node **head);
void deleteFirst(Node **head);
void deleteAtIndex(Node **head, int index);
void deleteLastPointer(Node **head);
void deleteAtIndexPointer(Node **head, int index);
void deleteLinkedList(Node **head);
void loadLinkedList(Node **head);
void saveLinkedList(Node **head);

int main() {
	int choice = -1;
	int value = -1;
	int index = -1;
	Node *head = NULL;
	
	printf("Welcome to Linked List Mania 2.0! (Now with file handling!)\n");
	while (choice != 0) {
		printf("0 - Exit program\n");
		printf("1 - Display current linked list and length\n");
		printf("2 - Load linked list from file\n");
		printf("3 - Save linked list to file\n");
		printf("4 - Insert last using pointer to node\n");
		printf("5 - Insert first\n");
		printf("6 - Insert into using pointer to node\n");
		printf("7 - Insert last using pointer to pointer to node\n");
		printf("8 - Insert into using pointer to pointer to node\n");
		printf("9 - Delete last using pointer to node\n");
		printf("10 - Delete first\n");
		printf("11 - Delete node at index using pointer to node\n");
		printf("12 - Delete last using pointer to pointer to node\n");
		printf("13 - Delete node at index using pointer to pointer to node\n");
		printf("14 - Clear Linked List\n");
		
		scanf("%d", &choice);
		switch(choice) {
			case 0:
				printf("Exiting program...\n");
				break;
			case 1: 
				printf("Displaying current linked list...\n");
				displayLinkedList(head);
				break;
			case 2:
				printf("Loading linked list from file..\n");
				loadLinkedList(&head);
				break;
			case 3:
				printf("Saving linked list to file...\n");
				saveLinkedList(&head);
				break;
			case 4:
				printf("Inserting last using pointer to node...\n");
				printf("Enter value to insert: ");
				scanf("%d", &value);
				insertLast(&head, value);
				break;
			case 5:
				printf("Inserting first...\n");
				printf("Enter value to insert: ");
				scanf("%d", &value);
				insertFirst(&head, value);
				break;
			case 6:
				printf("Inserting into using pointer to node...\n");
				printf("Enter value to insert: ");
				scanf("%d", &value);
				printf("Enter index to insert into: ");
				scanf("%d", &index);
				insertInto(&head, value, index);
				break;
			case 7:
				printf("Inserting last using pointer to pointer to node...\n");
				printf("Inserting last using pointer to node...\n");
				printf("Enter value to insert: ");
				scanf("%d", &value);
				insertLastPointer(&head, value);
				break;
			case 8:
				printf("Inserting into using pointer to pointer to node...\n");
				printf("Enter value to insert: ");
				scanf("%d", &value);
				printf("Enter index to insert into: ");
				scanf("%d", &index);
				insertIntoPointer(&head, value, index);
				break;
			case 9:
				printf("Deleting last node in linked list using pointer to node...\n");
				deleteLast(&head);
				break;
			case 10:
				printf("Deleting first node in linked list...\n");
				deleteFirst(&head);
				break;
			case 11:
				printf("Deleting node at index using pointer to node...\n");
				printf("Enter index to delete into: ");
				scanf("%d", &index);
				deleteAtIndex(&head, index);
				break;
			case 12:
				printf("Deleting last node in linked list using pointer to pointer to node...\n");
				deleteLastPointer(&head);
				break;
			case 13:
				printf("Deleting node at index using pointer to pointer node...");
				printf("Enter index to delete into: ");
				scanf("%d", &index);
				deleteAtIndexPointer(&head, index);
				break;
			case 14:
				printf("Clearing linked list...");
				deleteLinkedList(&head);
				break;
			default:
				printf("Please enter a valid choice...\n");
			
		}
	}
	
}

void displayLinkedList(Node *head) {
	int i = 0;
	int length = getLinkedListLength(head);
	if (length == 0) {
		printf("Linked list is empty!!!\n");
		return;
	}
	while (head != NULL) {
		printf("Index: [%d], value: %d\n", i, head->value);
		head = head->next;
		i++;
	}
}

int getLinkedListLength(Node *head) {
	int length = 0;
	while (head != NULL) {
		length++;
		head = head->next;
	}
	return length;
}


void insertLast(Node **head, int value) {
	Node *newNode = malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->value = value;
	if (*head == NULL) {
		*head = newNode;
	} else {
		Node *temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	printf("Node succesfully inserted!!!\n");
}

void insertFirst(Node **head, int value) {
	Node *newNode = malloc(sizeof(Node));
	newNode->value = value;
	newNode->next = *head;
	*head = newNode;
	printf("Node succesfully inserted!!!\n");
}

void insertInto(Node **head, int value, int index) {
	Node *newNode = malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->value = value;
	if (*head == NULL) {
		*head = newNode;
	} else {
		if (index == 0) {
			insertFirst(head, value);
		} else if (index >= getLinkedListLength(*head)) {
			insertLast(head, value);
		} else {
			Node *temp = *head;
			int i = 0;
			while (temp->next != NULL && i < index - 1) {
				temp = temp->next;
				i++;
			}
			newNode->next = temp->next;
			temp->next = newNode;
		}
	}
	printf("Node succesfully inserted!!!\n");
}

void insertLastPointer(Node **head, int value) {
	Node *newNode = malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->value = value;
	while (*head != NULL) {
		head = &(*head)->next;
	}
	*head = newNode;
	printf("Node succesfully inserted!!!\n");
}

void insertIntoPointer(Node **head, int value, int index) {
	Node *newNode = malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->value = value;
	if (index == 0) {
		insertFirst(head, value);
	} else if (index >= getLinkedListLength(*head)) {
		insertLast(head, value);
	} else {
		int i = 0;
		while (*head != NULL && i < index) {
			head = &(*head)->next;
			i++;
		}
		newNode->next = *head;
		*head = newNode;
	}
	printf("Node succesfully inserted!!!\n");
}

void deleteLast(Node **head) {
	if (*head == NULL) {
		printf("List is already empty!\n");
	} else if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
		printf("Node successfully deleted!\n");
	} else {
		Node *temp = *head;
		while (temp->next->next != NULL) {
			temp = temp->next;
		}
		free(temp->next);
		temp->next = NULL;
		printf("Node successfully deleted!\n");
	}
}

void deleteFirst(Node **head) {
	if (*head == NULL) {
		printf("List is already empty!\n");
	} else if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
		printf("Node successfully deleted!\n");
	} else {
		Node *temp = *head;
		*head = temp->next;
		free(temp);
		printf("Node successfully deleted!\n");
	}
}

void deleteAtIndex(Node **head, int index) {
	if (*head == NULL) {
		printf("List is already empty!\n");
	} else if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
		printf("Node successfully deleted!\n");
	} else {
		if (index == 0) {
			deleteFirst(head);
		} else if (index >= getLinkedListLength(*head)) {
			deleteLast(head);
		} else {
			Node *temp = *head;
			int i = 0;
			while (temp->next->next != NULL && i < index - 1) {
				temp = temp->next;
				i++;
			}
			Node *del = temp->next;
			temp->next = del->next;
			free(del);
			printf("Node successfully deleted!\n");
		}
	}
}

void deleteLastPointer(Node **head) {
	if (*head == NULL) {
		printf("List is already empty!\n");
	} else if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
			printf("Node successfully deleted!\n");
	} else {
		while ((*head)->next != NULL) {
			head = &(*head)->next;
		}
		free(*head);
		*head = NULL;
			printf("Node successfully deleted!\n");
	}
}

void deleteAtIndexPointer(Node **head, int index) {
	if (*head == NULL) {
		printf("List is already empty!\n");
	} else if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
			printf("Node successfully deleted!\n");
	} else {
		if (index == 0) {
			deleteFirst(head);
		} else if (index >= getLinkedListLength(*head)) {
			deleteLast(head);
		} else {
			int i = 0;
			while ((*head)->next->next != NULL && i < index) {
				head = &(*head)->next;
				i++;
			}
			Node *temp = *head;
			*head = temp->next;
			free(temp);
			printf("Node successfully deleted!\n");
		}
	}
}

void deleteLinkedList(Node **head) {
	int length = getLinkedListLength(*head);
	for (int i = 0; i < length; i++) {
		deleteLast(head);
	}
	printf("Linked list fully cleared!\n");
}

void loadLinkedList(Node **head) {
	deleteLinkedList(head);
	FILE *fp = fopen("data.dat", "rb");
	if (fp == NULL) {
		printf("Unable to open 'data.dat'");
		return;
	}
	int value = 0;
	while (fread(&value, sizeof(int), 1, fp) == 1) {
		insertLast(head, value);
	}
	fclose(fp);
	printf("Linked list successfully loaded!\n");
}

void saveLinkedList(Node **head) {
	FILE *fp = fopen("data.dat", "wb");
	if (fp == NULL) {
		printf("Unable to open 'data.dat'");
		return;
	}
	while (*head != NULL) {
		fwrite(&(*head)->value, sizeof(int), 1, fp);
		head = &(*head)->next;
	}
	fclose(fp);
	printf("Linked list successfully saved!\n");
}

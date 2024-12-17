/*Napisati program koji pomo�u vezanih listi (stabala) predstavlja strukturu direktorija.
Omogu�iti unos novih direktorija i pod-direktorija, ispis sadr�aja direktorija i
povratak u prethodni direktorij. To�nije program treba preko menija simulirati
kori�tenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 � izlaz.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct Directory* dirPosition;
typedef struct Directory {
	char name[100];
	dirPosition child; 
	dirPosition sibling;
	dirPosition parent;

}Directory;


typedef struct levelStack* stackPosition;
typedef struct levelStack {
	dirPosition dirLevelEl; //za trenutnu razinu
	stackPosition next;
}levelStack;

dirPosition createDirectory(char name[MAX_NAME_LENGTH], dirPosition parent);
dirPosition createSubDirectory(char name[MAX_NAME_LENGTH], dirPosition current);
dirPosition changeDirectory(char name, dirPosition current);
dirPosition goBack(dirPosition current); //cd..
void listDirectories(dirPosition current);
int push(stackPosition stackHead, dirPosition dirLevel);
dirPosition pop(stackPosition stackTop);

int main() {
	
	Directory dirHead = { {0}, NULL, NULL };
	levelStack stackHead = { NULL,NULL };
	dirPosition rootDir = NULL;

	rootDir = createSubDirectory("C:", &dirHead);		//moze i bez head-a jer ne triba brisat cijelo stablo

	push(&stackHead, rootDir);

	
	
	int choice;
	char name[100];
	printf("Struktura direktorija\n");
	printf("1 - md <ime>    (kreiraj direktorij)\n");
	printf("2 - cd <ime>    (udi u pod-direktorij)\n");
	printf("3 - cd..        (vrati se u roditeljski direktorij)\n");
	printf("4 - dir         (ispis sadrzaja direktorija)\n");
	printf("5 - izlaz\n");
	
	dirPosition currentDir = rootDir, result = NULL;
;
	while(1){
		while (1) {
			printf("Unesite izbor: ");
			scanf("%d", &choice);
			while (getchar() != '\n'); 

			switch (choice) {
			case 1:
				printf("Unesite ime novog direktorija: ");
				scanf("%s", name);
				result = createSubDirectory(name, currentDir);
				continue;
			case 2:
				printf("Unesite ime subdirektorija: ");
				scanf("%s", name);
				result = changeDirectory(name, currentDir);
				continue;
			case 3:
				currentDir = goBack(currentDir);
				continue;
			case 4:
				listDirectories(currentDir);
				continue;
			case 5:
				printf("Izlaz iz programa\n");
				exit(0);
				break;
			default:
				printf("Greska! Unesite ispravan izbor.\n");
				continue;
			}
			break;
		}

	return 0;
}
	free(rootDir);
	
}

dirPosition createDirectory(char name[MAX_NAME_LENGTH], dirPosition parent) {
	dirPosition new_dir = NULL;
	new_dir = (dirPosition)malloc(sizeof(Directory));
	if (!new_dir) {
		printf("Greska pri alokaciji memorije\n");
		return NULL;
	}
	strcpy(new_dir->name, name);
	new_dir->child = NULL;
	new_dir->sibling = NULL;
	new_dir->parent = parent;

	return new_dir;
}

dirPosition createSubDirectory(char name[MAX_NAME_LENGTH], dirPosition current) {
	dirPosition new_dir = NULL;
	new_dir = createDirectory(name, current);
	if (!new_dir) {
		printf("Greska pri stvaranju novog direktorija\n");
		return NULL;
	}
	if (current->child == NULL) {
		current->child = new_dir;
	}
	//dodajemo novi direktorij na kraj liste siblinga
	else {
		dirPosition temp = current->child;
		while (temp->sibling != NULL) {
			temp = temp->sibling;
		}
		temp->sibling = new_dir;
	}
	return new_dir;
}

dirPosition changeDirectory(char name[MAX_NAME_LENGTH], dirPosition current) {
	dirPosition temp = current->child;
	while (temp != NULL) {
		if (strcmp(temp->name, name) == 0) {
			return temp;
		}
		temp = temp->sibling;
	}
	printf("Direktorij '%s' ne postoji\n");
	return current;
}

void listDirectories(dirPosition current) {
	if (current->child == NULL) {
		printf("Direktorij '%s' je prazan\n", current->name);
		return;
	}
	printf("Sadrzaj direktorija '%s':\n", current->name);
	dirPosition temp = current->child;
	while (temp != NULL) {
		printf(" - %s\n", temp->name);
		temp = temp->sibling;
	}

}

dirPosition goBack(dirPosition current) {
	if (current->parent != NULL) {
		printf("Vraceno u direktorij '%s'\n", current->parent->name);
		return current->parent;
	}
	else {
		printf("Nalazite se u pocetnom direktoriju");
		return current;
	}
}

int push(stackPosition stackTop, dirPosition dirLevel) {
	stackPosition newStackNode = NULL;

	newStackNode = malloc(sizeof(levelStack));

	if (!newStackNode) {
		printf("\nNije moguce alocirati memoriju za newStackNode\n");
		return NULL;
	}

	newStackNode->dirLevelEl = dirLevel;

	newStackNode->next = stackTop->next;
	stackTop->next = newStackNode;

	return EXIT_SUCCESS;
}

dirPosition pop(stackPosition stackTop) {
	dirPosition dirLevel = NULL;
	stackPosition toDel = stackTop->next;

	stackTop->next = toDel->next;
	free(toDel);

	if (stackTop->next != NULL)
		dirLevel = stackTop->next->dirLevelEl;

	return dirLevel;
}
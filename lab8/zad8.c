/*8. Napisati program koji omoguæava rad s binarnim stablom pretraživanja. Treba
omoguæiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct TreeNode* position;
typedef struct TreeNode {
	int el;
	position leftChild, rightChild;
}treeNode;
//za levelorder
typedef struct Qnode* qposition;
typedef struct Qnode {
	position treeNode;
	qposition nextNode;
}qnode;

position find(position root, int wantedEl);
position insert(position root, int newEl);
position createNode(int newEl);
position delete(position root, int delEl);
int inorderPrint(position root);
int postorderPrint(position root);
int preorderPrint(position root);
int levelOrderPrint(position root);
qposition createQNode(position treeNode);
int menu(position root);

int main() {
	position root = NULL;
	int rootVal = 0;
	printf("unesite vrijednost korijena: ");
	scanf("%d", &rootVal);

	root = insert(root, rootVal);
	menu(root);
	return EXIT_SUCCESS;
}
int menu(position root) {
	char choice = '\0';
	int el = 0;
	position result = NULL;

	while (1) {
		printf("\nUpisite '1' za naci odreden element u stablu, '2' za dodati novi element u stablo, '3' za izbrisati element iz stabla, '4' za ispisati stablo u inorder obliku, '5' za ispisati stablo u postorder obliku, '6' za ispisati stablo u preorder obliku,'7' za ispisati stablo u levelorder obliku a 0 za izaci iz programa\n");
		scanf(" %c", &choice);

		switch (choice) {
		case '0':
			printf("Kraj programa\n");
			break;
		case '1':
			printf("Unesite vrijednost elementa kojeg zelite pronaci u stablu\n");
			scanf("%d", &el);

			result = find(root, el);
			if (result != NULL)
				printf("Element %d se nalazi na adresi %p\n", el, result);
			else
				printf("Neuspjelo pronalazenje elementa %d\n", el);
			continue;
		case '2':

			printf("\nUnesite vrijednost elementa kojeg zelite dodati u stablo: ");
			scanf("%d", &el);

			root = insert(root, el);

			continue;

		case '3':

			printf("\nUnesite vrijednost elementa kojeg zelite izbrisati iz stabla: ");
			scanf("%d", &el);

			root = delete(root, el);

			continue;

		case '4':

			inorderPrint(root);

			continue;


		case '5':

			postorderPrint(root);

			continue;

		case '6':

			preorderPrint(root);

			continue;

		case '7':

			levelOrderPrint(root);

			continue;

		default:

			printf("\nKrivi unos!!\n");

			continue;
		}

		break;
		}
	return EXIT_SUCCESS;
	}

position find(position root, int wantedEl) {
	if (root == NULL)
		return NULL;
	else if (wantedEl < root->el)
		return find(root->leftChild, wantedEl);
	else if (wantedEl > root->el)
		return find(root->rightChild, wantedEl);
	return root;
}
position insert(position root, int newEl) {
	if (root == NULL)
		return createNode(newEl);
	if (newEl <= root->el)
		root->leftChild = insert(root->leftChild, newEl);
	else if (newEl > root->el)
		root->rightChild = insert(root->rightChild, newEl);
	return root;
}
position createNode(int newEl) {
	position newNode = NULL;
	newNode = malloc(sizeof(treeNode));
	if (!newNode) {
		printf("Greska pri alokaciji memorije\n");
		return NULL;
	}
	newNode->el = newEl;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	return newNode;
}

position delete(position root, int delEl) {
	position temp;
	if (root == NULL)
		printf("element kojeg zelite obrisati se ne nalazi u stablu\n");
	else if (delEl < root->el)
		root->leftChild = delete(root->leftChild, delEl);
	else if (delEl > root->el)
		root-> rightChild = delete(root->rightChild, delEl);
	else if (root->leftChild != NULL && root->rightChild != NULL) {
		temp = root->rightChild;
		while (temp->leftChild != NULL)
			temp = temp->leftChild;
		root->el = temp->el;
		root->rightChild = delete(root->rightChild, temp->el);
	}
	else {
		temp = root;
		if (root->leftChild != NULL)
			root = root->leftChild;
		else
			root = root->rightChild;
		free(temp);
	}
	return root;
}

int inorderPrint(position root) {
	if (root != NULL) {
		inorderPrint(root->leftChild);
		printf("%d ", root->el);
		inorderPrint(root->rightChild);
	}
}

int postorderPrint(position root) {
	if (root != NULL) {
		postorderPrint(root->leftChild);
		postorderPrint(root->rightChild); 
		printf("%d ", root->el);

	}
	return EXIT_SUCCESS;
}

int preorderPrint(position root) {
	if (root != NULL) {
		printf("%d ", root->el);
		preorderPrint(root->leftChild);
		preorderPrint(root->rightChild);
	

	}
	return EXIT_SUCCESS;
}

int levelOrderPrint(position root) {
	position currentTreeNode = NULL;
	qposition temp = NULL, front = NULL, rear = NULL;
	front = rear = createQNode(root);

	while (front != NULL) {
		currentTreeNode = front->treeNode;

		printf("%d ", currentTreeNode->el);
		if (currentTreeNode->leftChild != NULL) {
			temp = rear;
			rear = createQNode(currentTreeNode->leftChild);
			temp->nextNode = rear;
		}
		if (currentTreeNode->rightChild != NULL) {
			temp = rear;
			rear = createQNode(currentTreeNode->rightChild);
			temp->nextNode = rear;
		}
		temp = front;
		front = front->nextNode;
		free(temp);
	}
	return EXIT_SUCCESS;
}

qposition createQNode(position treeNode) {
	qposition temp, newNode = NULL;
	newNode = malloc(sizeof(qnode));

	if (!newNode) {
		printf("greska pri alokaciji memorije\n");
		return NULL;
	}
	newNode->treeNode = treeNode;
	newNode->nextNode = NULL;
	return newNode;
}
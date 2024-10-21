/*2. Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
A.dinamički dodaje novi element na početak liste,
B.ispisuje listu,
C.dinamički dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CTR_SECURE_NO_WORNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define ERROR (-1)

typedef struct _person* head;
typedef struct _person {
    char firstname[MAX];
    char lastname[MAX];
    int birthYear;
    head next;

} person;

int addAtBegining(head h);
int addAtEnd(head h);
int findByLastName(head h);
int deleteElement(head h);
int printList(head h);

int main(){
    person HEAD;
    HEAD.next = NULL;
    int choice1 = 0, choice2 = 0;

    do{
        printf("Zelite li raditi nesto sa listom? ");
        printf("\n Unesite 1 za DA");
        printf("\nUnesite 2 za NE\n");
        printf("\nUnesite broj:");
        scanf("%d", &choice1);
        if(choice1 == 1){
            printf("\nIzaberite sto biste htjeli napraviti:\n");
            printf("Unesite broj 1 za dodavanje osobe na pocetak liste\n");
            printf("Unesite broj 2 za dodavanje osobe na kraj liste\n");
            printf("Unesite broj 3 za trazenje osobe po prezimenu u listi\n");
            printf("Unesite broj 4 za brisanje osobe iz liste\n");
            printf("Unesite broj 5 za ispis liste\n");
            printf("\nUnesite broj: ");
            scanf("%d", &choice2);
            printf("\n");
            if(choice2 == 1){
                addAtBegining(&HEAD);
            }
            if(choice2 == 2){
                addAtEnd(&HEAD);
            }
            if(choice2 == 3){
                findByLastName(HEAD.next);
            }
            if(choice2 == 4){
                deleteElement(&HEAD);
            }
            if(choice2 == 5){
                printList(HEAD.next);
            }

        }
    }while (choice1 == 1);
}

int addAtBegining(head h){
    head p = NULL;
    p = (head)malloc(sizeof(person));
    if(p == NULL){
        printf("\nNeuspjesna alokacija memorije!");
        return ERROR;
    }
    printf("Unesite ime osobe:\n");
    scanf("%s", p->firstname);
    printf("Unesite prezime osobe:\n");
    scanf("%s", p->lastname);
    printf("Unesite godinu rodenja osobe: \n");
    scanf("%d", &(p->birthYear));
    p->next = h->next;
    h->next = p;
    return 0;
}

int addAtEnd(head h){
    while (h -> next != NULL){
        h = h->next;
    }
    head p = NULL;
    p = (head)malloc(sizeof(person));

    if(p == NULL)
    {
        printf("\nNeuspjesna alokacija memorije!");
        return ERROR;
    }

    printf("\nUnesite ime osobe: ");
    scanf(" %s", p->firstname);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s",p->lastname);
    printf("\nUnesite godinu rodenja: ");
    scanf("%d", &p->birthYear);
    printf("\n");
    p->next = h->next;
    h->next = p;
    return 0;
}

int findByLastName(head h){
    char lastn[MAX];
    printf("Unesite prezime osobe koju zelite pronaci: ");
    scanf("%s", lastn);
    printf("\n");
    while(h != NULL && strcmp(lastn, h->lastname) != 0){
        h = h->next;
    }
    if(h == NULL)
        printf("Osoba s prezimenom %s ne postoji u listi!\n", lastn);
    else
        printf("Adresa trazene osobe je: %p", h);
    return 0;    
}

int deleteElement(head h) {
    head before = h;
    head temp = h->next;
    char lastn[MAX];

    printf("Unesite prezime osobe koju zelite izbrisati: ");
    scanf("%s", lastn);
    printf("\n");

    while(temp != NULL && strcmp(lastn, temp->lastname) != 0) {
        before = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("Osoba s prezimenom %s ne postoji u listi!\n", lastn);
        return ERROR;
    }

    before->next = temp->next;
    
    free(temp);

    printf("Osoba s prezimenom %s je izbrisana.\n", lastn);

    return 0;
}

int printList(head h){
    while(h != NULL){
        printf("%s %s %d\n", h->firstname, h->lastname, h->birthYear);
        h = h->next;
    }
    return 0;
}


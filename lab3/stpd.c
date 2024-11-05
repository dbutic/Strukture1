#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define END_OF_PROGRAM (0)
#define MAX (256)
#define ERROR (-1)

struct person;
typedef struct person* Position;

typedef struct person {
    char firstname[MAX];
    char lastname[MAX];
    int birthYear;
    Position next;

}Person;

int AddPerson(Position);
int InsertData(Position);
int PrintList(Position);
int InsertInTheEnd(Position);
int FindPersonByLastName(Position);
int DeletePerson(Position);
Position FindPrevious(Position, char *);
int AddAfter(Position);
Position Find(Position, char *);
int AddBefore(Position);
Position FindBefore(Position, char *);
void Sort(Position);
int WriteToFile(Position);
int ReadFromFile(Position);
void DeleteFromBegining(Position);

int main(){
    int NumofFunc;

    Person head = {
        .firstname = {0},
        .lastname = {0},
        .birthYear = 0,
        .next = NULL
    };

    while(1){
        printf("\nUpisite broj funkcije koju zelite pokrenuti: ");
        printf("\n1. Dodavanje osobe na pocetak liste");
        printf("\n2. Ispis liste");
        printf("\n3. Dodavanje osobe na kraj liste");
        printf("\n4. Pronalazenje osobe u listi po prezimenu");
        printf("\n5. Brisanje osobe iz liste");
        printf("\n6. Dodavanje osobe nakon odredene osobe");
        printf("\n7. Dodavanje osobe prije odredene osobe");
        printf("\n8. Sortiranje liste po prezimenu");
        printf("\n9. Upisnivanje liste u datoteku");
        printf("\n10. Citanje liste iz datoteke");
        printf("\n11. Kraj programa");
        printf("\n");
        scanf("%d", &NumofFunc);

        if(NumofFunc == 1)
            AddPerson(&head);

        else if(NumofFunc == 2)
            PrintList(&head);

        else if(NumofFunc == 3)
            InsertInTheEnd(&head);

        else if(NumofFunc == 4)
            FindPersonByLastName(&head);

        else if(NumofFunc == 5)
            DeletePerson(&head);

        else if(NumofFunc == 6)
            AddAfter(&head);

        else if(NumofFunc == 7)
            AddBefore(&head);

        else if(NumofFunc == 8)
            Sort(&head);

        else if(NumofFunc == 9)
            WriteToFile(&head);

        else if(NumofFunc == 10)
            ReadFromFile(&head);

        else if(NumofFunc == 11){
            DeleteFromBegining(&head);
            printf("Memory is clean!");
            break;        

        }

    else
        printf("\nPogrešan unos!\n");

    printf("\n");

    }

    return END_OF_PROGRAM;
}

int InsertData(Position p) {
    printf("\nUnesite ime, prezime i godinu rodenja osobe: ");
    scanf(" %s %s %d", p->firstname, p->lastname, &p->birthYear);

    return END_OF_PROGRAM;
}

int AddPerson(Position p){
    Position q = NULL;

    q = (Position)malloc(sizeof(struct person));

    if(q == NULL)
        return ERROR;

    InsertData(q);
    q-> next = p->next;
    p->next = q;

    return END_OF_PROGRAM;
}

int PrintList(Position p) {
    if (p->next == NULL) {
        printf("The list is empty");
    } else {
        printf("\n");

        p = p->next; 

        while (p != NULL) {
            
            printf("\n%s %s %d", p->firstname, p->lastname, p->birthYear);
            p = p->next;
        }
    }
    return END_OF_PROGRAM;
}


int InsertInTheEnd(Position p){
    Position q = NULL;

    while(p->next != NULL)
        p = p->next;

    q = p;

    AddPerson(q);

    return END_OF_PROGRAM; 
}

int FindPersonByLastName(Position p){
    char lastn[MAX] = { 0 };

    printf("\nUnesite prezime osobe: ");
    scanf(" %s", lastn);

    while(p->next != NULL && strcmp(p->lastname, lastn) != 0)
        p = p->next;

    printf("%s %s %d", p->firstname, p->lastname, p->birthYear);

    return END_OF_PROGRAM;
}

int AddAfter(Position p){
    char lastn[MAX] = { 0 };

    printf("\nUnesite prezime osobe: ");
    scanf(" %s", lastn);
    Position prev = NULL;
    
    prev = Find(p, lastn);

    if(prev == NULL)
        return ERROR;

    AddPerson(prev);

    return END_OF_PROGRAM;    
}

int DeletePerson(Position p){
    char lastn[MAX] = { 0 };

    printf("\nUnesite prezime osobe: ");
    scanf(" %s", lastn);

    Position previous = NULL;
    Position Current = NULL;

    previous = FindPrevious(p, lastn);

    if(previous == NULL)
        return ERROR;
    
    Current = previous->next;
    previous->next = previous->next->next;

    free(Current);

    return END_OF_PROGRAM;
}

Position FindPrevious(Position p, char* lastn){
    
    Position Previous = NULL;
    Position Current = NULL;

    Previous = p;
    Current = Previous->next;

    while(Current != NULL && (strcmp(lastn, Current->lastname) != 0)){
        Previous = Current;
        Current = Previous->next;
    
    }

    if(Current == NULL)
        return NULL;

    return Previous;
}

Position Find(Position p, char* lastn){
    while(p->next != NULL && strcmp(p->lastname, lastn) != 0)
        p = p->next;

    if(p == NULL)
        printf("\nOsoba ne postoji! ");

    return p; 

}

int AddBefore(Position p){

    char lastn[MAX] = { 0 };

    printf("\nUnesite prezime osobe:");
    scanf(" %s", lastn);

    Position prevp = NULL;
    prevp = FindBefore(p, lastn);

    if(prevp == NULL)
        return ERROR;
    
    AddPerson(prevp);

    return END_OF_PROGRAM;
    
}

Position FindBefore(Position p, char* lastn){
    Position prev = NULL;
    Position curr = NULL;

    prev = p;
    curr = prev->next;

    while(curr != NULL && strcmp(curr->lastname, lastn) != 0){

        prev = curr;
        curr = prev->next;
    }

    if(curr == NULL)
        return NULL;

    return prev;
}

void Sort(Position p){
    Position j, prev_j, temp, end;

    end = NULL;

    while(p->next != end){

            prev_j = p;
            j = p->next;

            while (j->next != end){
                 if(strcmp(j->lastname, j->next->lastname) > 0){
                    temp = j->next;
                    prev_j->next = temp;
                    j->next = temp->next;
                    temp->next = j;

                    j = temp;
                }

                prev_j = j;
             j = j->next;
           
            }
        end = j;
    }
}

int WriteToFile(Position p){
    FILE* fp = NULL;

    char filename[MAX];

    printf("\nUnesite ime datoteke: ");
    scanf(" %s", filename);

    fp = fopen(filename, "w");

    if(fp == NULL)
        return ERROR;

    p = p->next;

    while(p != NULL){

        fprintf(fp, "\n%s %s %d", p->firstname, p->lastname, p->birthYear);
        p = p->next;
    }

    fclose(fp);

    return END_OF_PROGRAM;
}

int ReadFromFile(Position p){

    FILE* fp;
    char filename[MAX];

    Position temp;

    printf("\nUnesite ime datoteke: ");
    scanf(" %s", filename);

    fp = fopen(filename, "r");

    if(fp == NULL)
        return ERROR;

    while(feof(fp) == 0){

        temp = (Position)malloc(sizeof(struct person));

        fscanf(fp, "\n%s %s %d", temp->firstname, temp->lastname, &temp->birthYear);

        temp->next = p->next;
        p->next = temp;
        p = temp;
    }

    fclose(fp);

    return END_OF_PROGRAM;
}

void DeleteFromBegining(Position p){

    Position temp;
    while(p->next != NULL){
        temp = p->next;
        p->next = p->next->next;
        free(temp);
    }
}
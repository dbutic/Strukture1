#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END (0)
#define ERROR (-1)
#define MAX_LINE (1024)

typedef struct Stog* Position;

typedef struct Stog {
    float broj;
    Position next;
} Stog;

int Push(Position* head, float x);
float Pop(Position* head);
float ReadFromFile(char* filename);
void FreeStack(Position head);

int main() {
    float result = 0.0;
    char filename[MAX_LINE] = { 0 };
    Position head = NULL; 

    printf("Unesite ime datoteke: ");
    scanf(" %s", filename);

    result = ReadFromFile(filename);

    if (result != -1)
        printf("Rezultat: %.2f\n", result);

    FreeStack(head);

    return END;
}

float ReadFromFile(char* filename) {
    char buffer[MAX_LINE] = { 0 }, mark[MAX_LINE] = { 0 };
    char* p = NULL;
    float num1 = 0.0, num2 = 0.0, value = 0.0;
    int n = 0;
    Position head = NULL;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Datoteka se nije otvorila!\n");
        return ERROR;
    }

    fgets(buffer, MAX_LINE, fp);
    p = buffer;

    while (strlen(p) > 0) {
        if (sscanf(p, "%f %n", &value, &n) > 0) {
            Push(&head, value); // Ako je broj, dodajemo na stog
        }
        else if (sscanf(p, "%s %n", mark, &n) > 0) {
            if (strcmp(mark, "+") != 0 && strcmp(mark, "-") != 0 && strcmp(mark, "*") != 0 && strcmp(mark, "/") != 0) {
                printf("Operator '%s' nije ispravan!\n", mark);
                FreeStack(head);
                fclose(fp);
                return ERROR;
            }

            if (head == NULL || head->next == NULL) {
                printf("Nema dovoljno elemenata na stogu za operaciju '%s'!\n", mark);
                FreeStack(head);
                fclose(fp);
                return ERROR;
            }

            num1 = Pop(&head);
            num2 = Pop(&head);

            switch (mark[0]) {
            case '+':
                Push(&head, num2 + num1);
                break;
            case '-':
                Push(&head, num2 - num1);
                break;
            case '*':
                Push(&head, num2 * num1);
                break;
            case '/':
                if (num1 == 0.0) {
                    printf("Dijeljenje s nulom nije definirano!\n");
                    FreeStack(head);
                    fclose(fp);
                    return ERROR;
                }
                Push(&head, num2 / num1);
                break;
            default:
                printf("Nepoznata operacija '%s'!\n", mark);
                FreeStack(head);
                fclose(fp);
                return ERROR;
            }
        }
        else {
            printf("Neispravan unos u datoteci!\n");
            FreeStack(head);
            fclose(fp);
            return ERROR;
        }

        p += n;
    }

    if (head != NULL && head->next == NULL) {
        float result = Pop(&head);
        FreeStack(head);
        fclose(fp);
        return result;
    }

    printf("Na stogu je ostalo više od jednog elementa!\n");
    FreeStack(head);
    fclose(fp);
    return ERROR;
}

int Push(Position* head, float x) {
    Position temp = (Position)malloc(sizeof(Stog));
    if (temp == NULL) {
        printf("Greška pri alokaciji memorije!\n");
        return ERROR;
    }

    temp->broj = x;
    temp->next = *head;
    *head = temp;

    return END;
}

float Pop(Position* head) {
    if (*head == NULL) {
        printf("Stog je prazan!\n");
        return ERROR;
    }

    Position temp = *head;
    float result = temp->broj;

    *head = (*head)->next;
    free(temp);

    return result;
}

void FreeStack(Position head) {
    while (head != NULL) {
        Position temp = head;
        head = head->next;
        free(temp);
    }
}

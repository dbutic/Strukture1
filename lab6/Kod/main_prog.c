#include "Liste.h"

int main(){
    
    char fileName[MAX_NUM_OF_CHAR] = {0};
    char article[MAX_NUM_OF_CHAR] = {0}, user_input[MAX_NUM_OF_CHAR] = {0};
    int year_1 = 0, month_1 = 0, day_1 = 0, year_2 = 0, month_2 = 0, day_2 = 0;
    racun Head_r = { .Artikl = {0}, .Kolicina = 0, .Cijena = 0.0, .next = NULL};
    racuni Head = { .Racun_ID = {0}, .Godina = 0, .Mjesec = 0, .Dan = 0, .next = NULL, .Sadrzaj = &Head_r};

    strcpy(fileName, "/Users/pierstrbad/Desktop/Sistem u Ducanima/racuni.txt");
    readFromFile(&Head, fileName);
    
    while(1){
        printf("Print Bills: YES/NO\n C> ");
        scanf(" %[^\n]s",user_input);

        if(strcmp(user_input,"YES") == 0){
            printWithRecursionDateAndName(Head.next);
            printf("OPTIONS:\n");
            printf("\t1. To stop the program type the keyword STOP.\n");
            printf("\t2. To check out the status of an article type the keyword CONTINUE.\n\t C> ");
            scanf(" %[^\n]s",user_input);
            if(strcmp(user_input,"CONTINUE") == 0){
                printf("\tTo check out the status of an article enter a specific time period:\n\t");
                printf("\tFrom: ");
                scanf("%d %d %d", &year_1, &month_1, &day_1);
                printf("\t\tTo: ");
                scanf("%d %d %d", &year_2, &month_2, &day_2);
                printf("\t\tArticle: ");
                scanf(" %s",article);
                if(moneySpent(Head.next, article, year_1, month_1, day_1, year_2, month_2, day_2) == -1)
                    return END;
            }
        }
        else if(strcmp(user_input, "NO") == 0){
            printf("\tYou have chosen to not print the Bills.\n");
            printf("\tTo stop the program type the keyword STOP.\n");
            printf("\tTo print the bills type the keyword CONTINUE.\n\t C> ");
            scanf(" %[^\n]s",user_input);
        }
        else
            printf("\n\n\tUKNOWN KEYWORD!\n\n");

        if(strcmp(user_input,"STOP") == 0)
            break;
        else if(strcmp(user_input,"CONTINUE") == 0)
            continue;
        else
            printf("\n\n\tUKNOWN KEYWORD!\n\n");

    }
    freeMemoryWithRecursion(&Head);
    return END;
}
/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj.koliko ima studenata
zapisanih u datoteci.Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata(ime, prezime, bodovi) i učitati iz datoteke sve zapise.Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova / max_br_bodova * 100*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define MAX_POINTS 100.0 

typedef struct {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    float points;
} Student;

int countStudents(const char *filename) {
    FILE *file = fopen(filename, "r");
    int studentCount = 0;
    char firstName[MAX_LENGTH], lastName[MAX_LENGTH];
    float points;

    if (file == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    while (!feof(file)) {
        if (fscanf(file, "%s %s %f", firstName, lastName, &points) == 3) {
            studentCount++;
        }
    }

    fclose(file);
    return studentCount;
}

int loadStudents(const char *filename, Student *students, int studentCount) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int i = 0;

    while (!feof(file) && i < studentCount) {
        if (fscanf(file, "%s %s %f", students[i].firstName, students[i].lastName, &students[i].points) == 3) {
            i++;
        }
    }

    fclose(file);
    return 0;
}

void printStudents(Student *students, int studentCount) {
    printf("Students and their points:\n");
    for (int i = 0; i < studentCount; i++) {
        float relativePoints = (students[i].points / MAX_POINTS) * 100.0;
        printf("%s %s - Absolute points: %.2f, Relative points: %.2f%%\n",
               students[i].firstName, students[i].lastName, students[i].points, relativePoints);
    }
}

int main() {
    Student *students;
    int studentCount;
    const char *filename = "students.txt";

    studentCount = countStudents(filename);
    if (studentCount <= 0) {
        printf("No students in the file or error reading the file.\n");
        return 1;
    }

    students = (Student *)malloc(studentCount * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation error!\n");
        return 1;
    }

    if (loadStudents(filename, students, studentCount) != 0) {
        free(students);
        return 1;
    }

    printStudents(students, studentCount);

    free(students);

    return 0;
}

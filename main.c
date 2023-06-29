#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 100

typedef struct {
    int rollNumber;
    char lastName[50];
    char firstName[50];
    char middleName[50];
    char faculty[50];
    char specialty[50];
} Student;

void addStudent(Student students[], int *count)
{
    if (*count >= MAX_STUDENTS) {
        printf("Data base is full!\n");
        return;
    }

    Student student;

    printf("Enter the credit card number: ");
    scanf("%d", &student.rollNumber);
    // Проверка на плагиат
    for (int i = 0; i < *count; i++) {
        if (students[i].rollNumber == student.rollNumber) {
            printf("A student with such a record book number already exists!\n");
            return;
        }
    }

    printf("Enter shurname: ");
    scanf("%s", student.lastName);

    printf("Enter name: ");
    scanf("%s", student.firstName);

    printf("Enter middlename: ");
    scanf("%s", student.middleName);

    printf("Enter faculty: ");
    scanf("%s", student.faculty);

    printf("Enter speciality: ");
    scanf("%s", student.specialty);

    students[*count] = student;
    (*count)++;

    printf("Complete successfully!\n");
}

void removeStudent(Student students[], int *count)
{
    int rollNumber;
    int found = 0;

    printf("Enter the student's credit card number ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < *count; i++) {
        if (students[i].rollNumber == rollNumber) {
            for (int j = i; j < (*count) - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Student successfully removed!\n");
    } else {
        printf("A student with such a record book number has not been found!\n");
    }
}

void backupDatabase(Student students[], int count)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char filename[100];

    sprintf(filename, "students_%04d-%02d-%02d-%02d-%02d-%02d.csv",
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec);

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error!\n");
        return;
    }

    fprintf(file, "Credit card number,Surname,Name,Midllename,Faculty,Speciality\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%s\n",
                students[i].rollNumber, students[i].lastName, students[i].firstName,
                students[i].middleName, students[i].faculty, students[i].specialty);
    }

    fclose(file);

    printf("Backup was successfully created in the file %s!\n", filename);
}

void restoreDatabase(Student students[], int *count)
{
    char filename[100];

    printf("Enter the backup file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Failed to open backup file!\n");
        return;
    }

    *count = 0;

    char line[256];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Student student;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%s",
               &student.rollNumber, student.lastName, student.firstName,
               student.middleName, student.faculty, student.specialty);
        students[*count] = student;
        (*count)++;
    }

    fclose(file);

    printf("The database was successfully restored from the file %s!\n", filename);
}

void searchByLastName(Student students[], int count)
{
    char lastName[50];
    int found = 0;

    printf("Enter the student's last name: ");
    scanf("%s", lastName);

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("Credit card number: %d\n", students[i].rollNumber);
            printf("Surname: %s\n", students[i].lastName);
            printf("Name: %s\n", students[i].firstName);
            printf("Middlename: %s\n", students[i].middleName);
            printf("Faculty: %s\n", students[i].faculty);
            printf("Speciality: %s\n", students[i].specialty);
            found = 1;
        }
    }

    if (!found) {
        printf("A student with this surname has not been found!\n");
    }
}

void saveDatabaseToFile(Student students[], int count)
{
    FILE *file = fopen("students.csv", "w");

    if (file == NULL) {
        printf("Failed to save database to file!\n");
        return;
    }

    fprintf(file, "Credit card number,Surname,Name,Midllename,Faculty,Speciality\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%s\n",
                students[i].rollNumber, students[i].lastName, students[i].firstName,
                students[i].middleName, students[i].faculty, students[i].specialty);
    }

    fclose(file);

    printf("The database has been successfully saved to a file!\n");
}

void loadDatabaseFromFile(Student students[], int *count)
{
    FILE *file = fopen("C:\\Users\\dzhik\\CLionProjects\\sem\\cmake-build-debug\\students.csv", "r");

    if (file == NULL) {
        printf("The database file could not be opened!\n");
        return;
    }

    *count = 0;

    char line[256];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Student student;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%s",
               &student.rollNumber, student.lastName, student.firstName,
               student.middleName, student.faculty, student.specialty);
        students[*count] = student;
        (*count)++;
    }

    fclose(file);
}

int main()
{
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;
    char filename[100];
    loadDatabaseFromFile(students, &count);

    while (1) {
        printf("\nMenu: \n");
        printf("1. Add student\n");
        printf("2. Dekete student\n");
        printf("3. Make backup\n");
        printf("4. Restore a database from a backup file\n");
        printf("5. Search by student's last name\n");
        printf("6. Shut down the program\n");
        printf("Select an operation (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                removeStudent(students, &count);
                break;
            case 3:
                backupDatabase(students, count);
                break;
            case 4:
                restoreDatabase(students, &count);
                break;
            case 5:
                searchByLastName(students, count);
                break;
            case 6:
                saveDatabaseToFile(students, count);
                return 0;
            default:
                printf("Error!\n");
                break;
        }
    }
    return 0;
}

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_DEPT_LEN 50
#define MAX_EMPLOYEES 100

typedef struct employee_t {
    int id;
    char name[MAX_NAME_LEN];
    char sex;
    double salary;
    char department[MAX_DEPT_LEN];
    int age;
} Employee;

void add_employee(Employee emp, FILE *fp);
void update_employee(int id, FILE *fp);
void delete_employee(int id, FILE *fp);
void search_employee(int id, FILE *fp);
void list_employees(FILE *fp);

#endif 

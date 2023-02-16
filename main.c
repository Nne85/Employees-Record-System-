#include "main.h"

int main(void) {
    FILE *fp;
    int choice, id;
    Employee emp;

    fp = fopen("employees.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employees.dat", "wb+");
        if (fp == NULL) {
            printf("Cannot create file\n");
            exit(1);
        }
    }

    while (1) {
        printf("\nEmployee Record System\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Search Employee\n");
        printf("5. List Employees\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the following details:\n");
                printf("ID: ");
                scanf("%d", &emp.id);
                printf("Name: ");
                scanf("%s", emp.name);
                printf("Sex (M/F): ");
                scanf(" %c", &emp.sex);
                printf("Salary: ");
                scanf("%lf", &emp.salary);
                printf("Department: ");
                scanf("%s", emp.department);
                printf("Age: ");
                scanf("%d", &emp.age);
                add_employee(emp, fp);
                break;
            case 2:
                printf("Enter the ID of the employee to update: ");
                scanf("%d", &id);
                update_employee(id, fp);
                break;
            case 3:
                printf("Enter the ID of the employee to delete: ");
                scanf("%d", &id);
                delete_employee(id, fp);
                break;
            case 4:
                printf("Enter the ID of the employee to search: ");
                scanf("%d", &id);
                search_employee(id, fp);
                break;
            case 5:
                list_employees(fp);
                break;
            case 6:
                fclose(fp);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}



void add_employee(Employee emp, FILE *fp) {
    fseek(fp, 0, SEEK_END);
    fwrite(&emp, sizeof(Employee), 1, fp);
    printf("Employee added successfully!\n");
}

void update_employee(int id, FILE *fp) {
    int found = 0;
    Employee emp;
    rewind(fp);
    while (fread(&emp, sizeof(Employee), 1, fp)) {
        if (emp.id == id) {
            printf("Enter new employee details: \n");
            printf("Name: ");
            scanf("%s", emp.name);
            printf("Sex (M/F): ");
            scanf(" %c", &emp.sex);
            printf("Salary: ");
            scanf("%lf", &emp.salary);
            printf("Department: ");
            scanf("%s", emp.department);
            printf("Age: ");
            scanf("%d", &emp.age);
            fseek(fp, -sizeof(Employee), SEEK_CUR);
            fwrite(&emp, sizeof(Employee), 1, fp);
            printf("Employee details updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Employee with id %d not found!\n", id);
    }
}

void delete_employee(int id, FILE *fp) {
    FILE *temp = fopen("temp.txt", "wb");
    int found = 0;
    Employee emp;
    rewind(fp);
    while (fread(&emp, sizeof(Employee), 1, fp)) {
        if (emp.id != id) {
            fwrite(&emp, sizeof(Employee), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove("employee.txt");
    rename("temp.txt", "employee.txt");
    if (found) {
        printf("Employee with id %d deleted successfully!\n", id);
    } else {
        printf("Employee with id %d not found!\n", id);
    }
}

void search_employee(int id, FILE *fp) {
    Employee emp;
    fseek(fp, (id-1)*sizeof(Employee), SEEK_SET);
    fread(&emp, sizeof(Employee), 1, fp);
    if (emp.id == -1) {
        printf("Employee with ID %d not found.\n", id);
    } else {
        printf("ID: %d\n", emp.id);
        printf("Name: %s\n", emp.name);
        printf("Sex: %c\n", emp.sex);
        printf("Salary: %.2lf\n", emp.salary);
        printf("Department: %s\n", emp.department);
        printf("Age: %d\n", emp.age);
    }
}

void list_employees(FILE *fp) {
    Employee emp;
    int count = 0;
    printf("ID\tName\tSex\tSalary\t\tDepartment\tAge\n");
    while (fread(&emp, sizeof(Employee), 1, fp)) {
        if (emp.id != -1) {
            printf("%d\t%s\t%c\t%.2lf\t%s\t\t%d\n", emp.id, emp.name, emp.sex, emp.salary, emp.department, emp.age);
            count++;
        }
    }
    if (count == 0) {
        printf("No employees found.\n");
    }
}

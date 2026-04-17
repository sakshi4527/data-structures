
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float marks;
} Student;

typedef struct {
    Student data[MAX_STUDENTS];
    int count;
} StudentDatabase;

// Initialize database
void initDB(StudentDatabase *db) {
    db->count = 0;
}

// Add a student
int addStudent(StudentDatabase *db, int id, const char *name, float marks) {
    if (db->count >= MAX_STUDENTS) {
        printf("Database full!\n");
        return 0;
    }
    
    Student *s = &db->data[db->count];
    s->id = id;
    strncpy(s->name, name, NAME_LENGTH - 1);
    s->name[NAME_LENGTH - 1] = '\0';
    s->marks = marks;
    db->count++;
    return 1;
}

// Display a student
void displayStudent(const Student *s) {
    printf("ID: %-5d | Name: %-20s | Marks: %.2f\n", s->id, s->name, s->marks);
}

// Display all students
void displayAll(const StudentDatabase *db) {
    printf("\n%-5s | %-20s | %s\n", "ID", "Name", "Marks");
    printf("------------------------------------------\n");
    for (int i = 0; i < db->count; i++) {
        displayStudent(&db->data[i]);
    }
    printf("Total students: %d\n", db->count);
}

// ============== SORTING ALGORITHMS ==============

// Quick Sort by marks (descending) - O(n log n) average
int partitionByMarks(Student arr[], int low, int high) {
    float pivot = arr[high].marks;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].marks > pivot) {  // Descending order
            i++;
            Student temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Student temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSortByMarks(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partitionByMarks(arr, low, high);
        quickSortByMarks(arr, low, pi - 1);
        quickSortByMarks(arr, pi + 1, high);
    }
}

// Quick Sort by ID (ascending) - O(n log n) average
int partitionByID(Student arr[], int low, int high) {
    int pivot = arr[high].id;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].id < pivot) {
            i++;
            Student temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Student temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSortByID(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partitionByID(arr, low, high);
        quickSortByID(arr, low, pi - 1);
        quickSortByID(arr, pi + 1, high);
    }
}

// Sort by name (alphabetical) using Merge Sort - O(n log n)
void merge(Student arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    Student *L = malloc(n1 * sizeof(Student));
    Student *R = malloc(n2 * sizeof(Student));
    
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].name, R[j].name) <= 0)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSortByName(Student arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortByName(arr, l, m);
        mergeSortByName(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ============== SEARCHING ALGORITHMS ==============

// Binary Search by ID - O(log n) - requires sorted data
int binarySearchByID(StudentDatabase *db, int id) {
    quickSortByID(db->data, 0, db->count - 1);  // Ensure sorted
    
    int low = 0, high = db->count - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (db->data[mid].id == id)
            return mid;
        else if (db->data[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;  // Not found
}

// Linear Search by name - O(n)
int linearSearchByName(const StudentDatabase *db, const char *name) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->data[i].name, name) == 0)
            return i;
    }
    return -1;
}

// Search students by marks range - O(n)
void searchByMarksRange(const StudentDatabase *db, float min, float max) {
    printf("\nStudents with marks between %.2f and %.2f:\n", min, max);
    printf("------------------------------------------\n");
    int found = 0;
    for (int i = 0; i < db->count; i++) {
        if (db->data[i].marks >= min && db->data[i].marks <= max) {
            displayStudent(&db->data[i]);
            found++;
        }
    }
    if (!found) printf("No students found in this range.\n");
}

// ============== MENU SYSTEM ==============

void printMenu() {
    printf("\n========== STUDENT MARKS SYSTEM ==========\n");
    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Sort by Marks (Descending)\n");
    printf("4. Sort by ID (Ascending)\n");
    printf("5. Sort by Name (Alphabetical)\n");
    printf("6. Search by ID (Binary Search)\n");
    printf("7. Search by Name (Linear Search)\n");
    printf("8. Search by Marks Range\n");
    printf("0. Exit\n");
    printf("==========================================\n");
    printf("Choice: ");
}

int main() {
    StudentDatabase db;
    initDB(&db);
    
    // Sample data
    addStudent(&db, 101, "Alice Johnson", 85.5);
    addStudent(&db, 103, "Bob Smith", 72.0);
    addStudent(&db, 102, "Charlie Brown", 91.5);
    addStudent(&db, 105, "Diana Ross", 68.0);
    addStudent(&db, 104, "Eve Wilson", 95.0);
    
    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        getchar();  // Clear newline
        
        switch (choice) {
            case 1: {
                int id;
                char name[NAME_LENGTH];
                float marks;
                printf("Enter ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Name: ");
                fgets(name, NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter Marks: ");
                scanf("%f", &marks);
                addStudent(&db, id, name, marks);
                printf("Student added successfully!\n");
                break;
            }
            case 2:
                displayAll(&db);
                break;
            case 3:
                quickSortByMarks(db.data, 0, db.count - 1);
                printf("Sorted by marks (highest first):\n");
                displayAll(&db);
                break;
            case 4:
                quickSortByID(db.data, 0, db.count - 1);
                printf("Sorted by ID:\n");
                displayAll(&db);
                break;
            case 5:
                mergeSortByName(db.data, 0, db.count - 1);
                printf("Sorted by name:\n");
                displayAll(&db);
                break;
            case 6: {
                int id;
                printf("Enter ID to search: ");
                scanf("%d", &id);
                int idx = binarySearchByID(&db, id);
                if (idx != -1) {
                    printf("Found:\n");
                    displayStudent(&db.data[idx]);
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 7: {
                char name[NAME_LENGTH];
                printf("Enter name to search: ");
                fgets(name, NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0';
                int idx = linearSearchByName(&db, name);
                if (idx != -1) {
                    printf("Found:\n");
                    displayStudent(&db.data[idx]);
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 8: {
                float min, max;
                printf("Enter minimum marks: ");
                scanf("%f", &min);
                printf("Enter maximum marks: ");
                scanf("%f", &max);
                searchByMarksRange(&db, min, max);
                break;
            }
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
    
    return 0;
}

#include <stdio.h>
#include <string.h>

#define N 100

struct Student {
    int roll;
    char name[50];
    int sub1, sub2, sub3;
};

struct Student stack[N];
int top = -1;

// Push
void push(struct Student s) {
    if (top == N - 1)
        printf("Stack Overflow\n");
    else {
        stack[++top] = s;
        printf("Student added.\n");
    }
}

// Pop
void pop() {
    if (top == -1)
        printf("Stack Underflow\n");
    else {
        printf("Removed: %s\n", stack[top].name);
        top--;
    }
}

// Delete at position
void deleteAtPosition() {
    if (top == -1) {
        printf("No records available.\n");
        return;
    }

    int pos;
    printf("Enter position: ");
    scanf("%d", &pos);

    if (pos < 1 || pos > top + 1) {
        printf("Invalid position\n");
        return;
    }

    printf("Deleted: %s\n", stack[pos - 1].name);

    for (int i = pos - 1; i < top; i++) {
        stack[i] = stack[i + 1];
    }
    top--;
}

// Display
void display() {
    if (top == -1) {
        printf("Empty\n");
        return;
    }

    for (int i = top; i >= 0; i--) {
        int total = stack[i].sub1 + stack[i].sub2 + stack[i].sub3;
        float avg = total / 3.0;

        printf("Pos:%d | Roll:%d | Name:%s | Total:%d | Avg:%.2f\n",
               i + 1, stack[i].roll, stack[i].name, total, avg);
    }
}

// Highest
void highestTotal() {
    if (top == -1) {
        printf("No records available.\n");
        return;
    }

    int max = 0, idx = 0;

    for (int i = 0; i <= top; i++) {
        int total = stack[i].sub1 + stack[i].sub2 + stack[i].sub3;
        if (total > max) {
            max = total;
            idx = i;
        }
    }

    printf("Top Student: %s (Roll %d) Total: %d\n",
           stack[idx].name, stack[idx].roll, max);
}

// Lowest (same naming style)
void lowestTotal() {
    if (top == -1) {
        printf("No records available.\n");
        return;
    }

    int min = stack[0].sub1 + stack[0].sub2 + stack[0].sub3;
    int idx = 0;

    for (int i = 1; i <= top; i++) {
        int total = stack[i].sub1 + stack[i].sub2 + stack[i].sub3;
        if (total < min) {
            min = total;
            idx = i;
        }
    }

    printf("Lowest Student: %s (Roll %d) Total: %d\n",
           stack[idx].name, stack[idx].roll, min);
}

// Sort
void sortStudents() {
    if (top == -1) {
        printf("No records to sort.\n");
        return;
    }

    struct Student temp;

    for (int i = 0; i <= top; i++) {
        for (int j = i + 1; j <= top; j++) {
            int t1 = stack[i].sub1 + stack[i].sub2 + stack[i].sub3;
            int t2 = stack[j].sub1 + stack[j].sub2 + stack[j].sub3;

            if (t2 > t1) {
                temp = stack[i];
                stack[i] = stack[j];
                stack[j] = temp;
            }
        }
    }

    printf("Students sorted successfully.\n");
}

// Search
void searchByRoll() {
    if (top == -1) {
        printf("No records available.\n");
        return;
    }

    int roll;
    printf("Enter roll number: ");
    scanf("%d", &roll);

    for (int i = 0; i <= top; i++) {
        if (stack[i].roll == roll) {
            int total = stack[i].sub1 + stack[i].sub2 + stack[i].sub3;
            float avg = total / 3.0;

            printf("Found: Roll:%d | Name:%s | Total:%d | Avg:%.2f\n",
                   stack[i].roll, stack[i].name, total, avg);
            return;
        }
    }

    printf("Student not found.\n");
}

// Main
int main() {
    int choice;
    struct Student s;

    do {
        printf("\n--- Menu ---\n");
        printf("1.Add Student\n");
        printf("2.Remove Latly Added Student\n");
        printf("3.Display Records\n");
        printf("4.Highest Marks\n");
        printf("5.Lowest Marks\n");
        printf("6.Sort Students\n");
        printf("7.Search by Roll\n");
        printf("8.Delete at Position\n");
        printf("0.Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Roll, Name, Marks(3): ");
                scanf("%d %s %d %d %d",
                      &s.roll, s.name, &s.sub1, &s.sub2, &s.sub3);
                push(s);
                break;

            case 2:
                pop();
                break;

            case 3:
                display();
                break;

            case 4:
                highestTotal();
                break;

            case 5:
                lowestTotal();
                break;

            case 6:
                sortStudents();
                break;

            case 7:
                searchByRoll();
                break;

            case 8:
                deleteAtPosition();
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while (choice != 0);

    return 0;
}

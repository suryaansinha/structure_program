#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

// Define the structure
struct Student {
    int roll_no;
    char name[NAME_LENGTH];
    float marks;
};

// Function to clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to read a line safely
void read_name(char *name, int max_length) {
    if (fgets(name, max_length, stdin) != NULL) {
        // Remove trailing newline if present
        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
        }
    }
}

// Function to validate marks (0-100)
int validate_marks(float marks) {
    return (marks >= 0.0 && marks <= 100.0);
}

// Function to input student details with validation
int input_student(struct Student *s) {
    printf("\nRoll Number: ");
    if (scanf("%d", &s->roll_no) != 1) {
        printf("Invalid input for roll number!\n");
        clear_input_buffer();
        return 0;
    }
    clear_input_buffer(); // Clear buffer after scanf
    
    if (s->roll_no <= 0) {
        printf("Roll number must be positive!\n");
        return 0;
    }

    printf("Name: ");
    read_name(s->name, NAME_LENGTH);
    
    // Check if name is empty
    if (strlen(s->name) == 0) {
        printf("Name cannot be empty!\n");
        return 0;
    }

    printf("Marks (0-100): ");
    if (scanf("%f", &s->marks) != 1) {
        printf("Invalid input for marks!\n");
        clear_input_buffer();
        return 0;
    }
    clear_input_buffer();
    
    if (!validate_marks(s->marks)) {
        printf("Marks must be between 0 and 100!\n");
        return 0;
    }

    return 1; // Success
}

// Function to calculate average marks
float calculate_average(struct Student students[], int n) {
    if (n == 0) {
        return 0.0;
    }
    
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += students[i].marks;
    }
    return sum / n;
}

// Function to find student with highest marks
int find_top_student(struct Student students[], int n) {
    if (n == 0) return -1;
    
    int top_index = 0;
    for (int i = 1; i < n; i++) {
        if (students[i].marks > students[top_index].marks) {
            top_index = i;
        }
    }
    return top_index;
}

// Function to print all student records
void print_all_students(struct Student students[], int n) {
    if (n == 0) {
        printf("\nNo student records available.\n");
        return;
    }
    
    printf("\n%-10s %-30s %-10s\n", "Roll No", "Name", "Marks");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-30s %-10.2f\n", 
               students[i].roll_no, 
               students[i].name, 
               students[i].marks);
    }
}

// Function to print students who scored below average
void print_students_below_average(struct Student students[], int n, float average) {
    printf("\n--- Students Below Average Marks (%.2f) ---\n", average);
    
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].marks < average) {
            printf("Roll: %d, Name: %s, Marks: %.2f\n", 
                   students[i].roll_no, 
                   students[i].name, 
                   students[i].marks);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No students are below the average.\n");
    }
}

// Function to search student by roll number
void search_student(struct Student students[], int n) {
    int roll;
    printf("\nEnter roll number to search: ");
    if (scanf("%d", &roll) != 1) {
        printf("Invalid input!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].roll_no == roll) {
            printf("\nStudent Found:\n");
            printf("Roll: %d, Name: %s, Marks: %.2f\n", 
                   students[i].roll_no, 
                   students[i].name, 
                   students[i].marks);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Student with roll number %d not found.\n", roll);
    }
}

int main() {
    struct Student studentArray[MAX_STUDENTS];
    int num_students;

    // Get number of students with validation
    do {
        printf("Enter number of students (1-%d): ", MAX_STUDENTS);
        if (scanf("%d", &num_students) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        if (num_students < 1 || num_students > MAX_STUDENTS) {
            printf("Number must be between 1 and %d.\n", MAX_STUDENTS);
        }
    } while (num_students < 1 || num_students > MAX_STUDENTS);

    // Input student details with retry on error
    int count = 0;
    while (count < num_students) {
        printf("\n=== Enter details for Student %d ===", count + 1);
        if (input_student(&studentArray[count])) {
            count++;
        } else {
            printf("Please try again.\n");
        }
    }

    // Print all student records
    printf("\n\n=== ALL STUDENT RECORDS ===");
    print_all_students(studentArray, num_students);

    // Calculate and print average marks
    float avg = calculate_average(studentArray, num_students);
    printf("\nAverage Marks: %.2f\n", avg);

    // Print students below average
    print_students_below_average(studentArray, num_students, avg);

    // Find and display top student
    int top = find_top_student(studentArray, num_students);
    if (top != -1) {
        printf("\n--- Top Performing Student ---\n");
        printf("Roll: %d, Name: %s, Marks: %.2f\n", 
               studentArray[top].roll_no, 
               studentArray[top].name, 
               studentArray[top].marks);
    }

    // Optional: Search functionality
    char choice;
    printf("\nDo you want to search for a student? (y/n): ");
    scanf(" %c", &choice);
    clear_input_buffer();
    
    if (choice == 'y' || choice == 'Y') {
        search_student(studentArray, num_students);
    }

    return 0;
}
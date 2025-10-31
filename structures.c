//Write a C program to manage student records.

#include <stdio.h>

// Define the structure outside main so it's accessible by all functions
struct Student {
    int roll_no;
    char name[50];
    float marks;
};

// Function to calculate average marks
// It takes the array of students and the count as input
float calculate_average(struct Student students[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += students[i].marks;
    }
    return sum / n;
}

// Function to print students who scored below average
void print_students_below_average(struct Student students[], int n, float average) {
    printf("\n--- Students Below Average Marks (%.2f) ---\n", average);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].marks < average) {
            printf("Roll: %d, Name: %s, Marks: %.2f\n", students[i].roll_no, students[i].name, students[i].marks);
            found = 1;
        }
    }
    if (!found) {
        printf("No students are below the average.\n");
    }
}

int main() {
    int num_students = 5;
    // Declare an array of Student structures directly
    struct Student studentArray[num_students];

    // Use a loop to get input for all students
    for (int i = 0; i < num_students; i++) {
        printf("\nEnter details for Student %d:\n", i + 1);
        printf("Roll Number: ");
        scanf("%d", &studentArray[i].roll_no);

        printf("Name: ");
        scanf(" %[^\n]", studentArray[i].name); 

        printf("Marks: ");
        scanf("%f", &studentArray[i].marks);
    
        if (marks < 0 || marks > 100) {
            printf("Invalid marks! Enter between 0-100\n");
            i--;  // Retry this student
        continue;
        }
    }
    // Print all student records
    printf("\n--- All Student Records ---\n");
    for (int i = 0; i < num_students; i++) {
        printf("Roll: %d, Name: %s, Marks: %.2f\n", studentArray[i].roll_no, studentArray[i].name, studentArray[i].marks);
    }

    // Calculate and print average marks
    float avg = calculate_average(studentArray, num_students);
    printf("\nAverage Marks: %.2f\n", avg);

    // Print students below average
    print_students_below_average(studentArray, num_students, avg);

    return 0;
}

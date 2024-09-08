#include <stdio.h>   // For input/output functions
#include <stdlib.h>  // For memory allocation and utility functions
#include <string.h>  // For string manipulation functions

// Define the Task structure
struct task {
    int id;
    char taskd[100];
    int isActive; // 1 for active, 0 for completed or deleted
};

// Global variables
struct task *tasks = NULL; // Pointer to array of tasks
int taskCount = 0;         // Number of tasks

// Function to add a task
void addTask(const char *description) {
    struct task *temp = realloc(tasks, (taskCount + 1) * sizeof(struct task));
    if (temp == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    tasks = temp;

    tasks[taskCount].id = taskCount + 1;
    strcpy(tasks[taskCount].taskd, description);
    tasks[taskCount].isActive = 1; // Set status to active
    taskCount++;
}

// Function to mark a task as completed
void markAsComplete(int id) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id && tasks[i].isActive == 1) {
            tasks[i].isActive = 0; // Mark as completed
            return;
        }
    }
    printf("Task ID %d not found or already completed.\n", id);
}

// Function to delete a task
void deleteTask(int id) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id && tasks[i].isActive == 1) {
            tasks[i].isActive = -1; // Mark as deleted
            return;
        }
    }
    printf("Task ID %d not found or already deleted.\n", id);
}

// Function to display tasks based on status
void displayTasksByStatus(int status) {
    printf("\nTasks with status %d:\n", status);
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].isActive == status) {
            printf("ID %d: %s\n", tasks[i].id, tasks[i].taskd);
        }
    }
}

// Function to display all tasks
void displayAllTasks() {
    printf("\nActive Tasks:\n");
    displayTasksByStatus(1); // Active tasks
    printf("\nCompleted Tasks:\n");
    displayTasksByStatus(0); // Completed tasks
    printf("\nDeleted Tasks:\n");
    displayTasksByStatus(-1); // Deleted tasks
}

int main() {
    int choice, id;
    char description[100];
    
    while (1) {
        // Display menu
        printf("\nTo Do List Menu:\n");
        printf("1. Add Task\n");
        printf("2. Mark Task as Complete\n");
        printf("3. Delete Task\n");
        printf("4. Display All Tasks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from input buffer

        switch (choice) {
            case 1: // Add Task
                printf("Enter task description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0'; // Remove newline character
                addTask(description);
                break;

            case 2: // Mark Task as Complete
                printf("Enter task ID to mark as complete: ");
                scanf("%d", &id);
                markAsComplete(id);
                break;

            case 3: // Delete Task
                printf("Enter task ID to delete: ");
                scanf("%d", &id);
                deleteTask(id);
                break;

            case 4: // Display All Tasks
                displayAllTasks();
                break;

            case 5: // Exit
                free(tasks); // Free allocated memory
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }

        // Display tasks after each operation
        displayAllTasks();

        // Ask user if they want to continue
        printf("\nDo you want to continue (y/n)? ");
        char cont = getchar();
        getchar(); // Clear newline character from input buffer
        if (cont == 'n' || cont == 'N') {
            break;
        }
    }

    // Free allocated memory
    free(tasks);
    return 0;
}

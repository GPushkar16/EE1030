#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000
#define MAX_HISTORY 100

// Chronicle and history stacks for UNDO/REDO operations
char chronicle[MAX_LENGTH] = "";
char history[MAX_HISTORY][MAX_LENGTH];
int history_index = 0;
char redo_stack[MAX_HISTORY][MAX_LENGTH];
int redo_index = 0;

// Function to insert spell at the end of the chronicle
void insert(const char *spell) {
    strcpy(history[history_index++], chronicle); // Save current state for UNDO
    strcat(chronicle, spell);
    redo_index = 0; // Clear redo stack after new action
}

// Function to delete last k characters from the chronicle
void delete(int k) {
    int len = strlen(chronicle);
    if (k > len) k = len;
    strcpy(history[history_index++], chronicle); // Save current state for UNDO
    chronicle[len - k] = '\0';
    redo_index = 0; // Clear redo stack after new action
}

// Function to undo last operation
void undo() {
    if (history_index > 0) {
        strcpy(redo_stack[redo_index++], chronicle); // Save current state for REDO
        strcpy(chronicle, history[--history_index]); // Revert to last state
    }
}

// Function to redo last undone operation
void redo() {
    if (redo_index > 0) {
        strcpy(history[history_index++], chronicle); // Save current state for UNDO
        strcpy(chronicle, redo_stack[--redo_index]); // Reapply last undone state
    }
}

// Function to process commands from input files
void process_commands(FILE *input_file) {
    int n; // Number of operations
    fscanf(input_file, "%d", &n);
    char command[20], spell[MAX_LENGTH];
    int k;

    for (int i = 0; i < n; i++) {
        fscanf(input_file, "%s", command);
        if (strcmp(command, "INSERT") == 0) {
            fscanf(input_file, " %[^\n]", spell); // Read the entire spell
            insert(spell);
        } else if (strcmp(command, "DELETE") == 0) {
            fscanf(input_file, "%d", &k);
            delete(k);
        } else if (strcmp(command, "UNDO") == 0) {
            undo();
        } else if (strcmp(command, "REDO") == 0) {
            redo();
        }
    }
}

// Main function
int main() {
    int t;
    scanf("%d", &t); // Read number of test cases

    char input_filename[50], output_filename[50];
    for (int i = 1; i <= t; i++) {
        sprintf(input_filename, "input/input_%d.txt", i);
        sprintf(output_filename, "solution/output_%d.txt", i);
        
        FILE *input_file = fopen(input_filename, "r");
        if (!input_file) {
            fprintf(stderr, "Error: Could not open %s\n", input_filename);
            continue;
        }

        // Reset chronicle and indices for each test case
        strcpy(chronicle, "");
        history_index = redo_index = 0;

        process_commands(input_file);
        fclose(input_file);

        // Write the final state of the chronicle to output file
        FILE *output_file = fopen(output_filename, "w");
        if (strlen(chronicle) == 0) {
            fprintf(output_file, "EMPTY\n");
        } else {
            fprintf(output_file, "%s\n", chronicle);
        }
        fclose(output_file);
    }
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to remove spaces from a string
void removeSpaces(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ')
            str[count++] = str[i];
    }
    str[count] = '\0';
}

// Function to perform row-column transposition
void rowColumnTransposition(char *plaintext, int key) {
    int length = strlen(plaintext);
    int rows = length / key;
    if (length % key != 0)
        rows++;

    char matrix[rows][key];

    // Initialize matrix with spaces
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            matrix[i][j] = ' ';
        }
    }

    int k = 0;
    // Fill the matrix row-wise with the plaintext
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key && k < length; j++) {
            matrix[i][j] = plaintext[k++];
        }
    }

    // Print the matrix column-wise
    printf("Encrypted Message: ");
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] != ' ')
                printf("%c", matrix[i][j]);
        }
    }
    printf("\n");
}

int main() {
    char plaintext[1000];
    int key;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    removeSpaces(plaintext);

    printf("Enter the key (number of columns): ");
    scanf("%d", &key);

    rowColumnTransposition(plaintext, key);

    return 0;
}

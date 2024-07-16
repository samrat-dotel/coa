#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void decimalToBinary(int n, int *binary, int size) {
    if (n < 0) {
        n = abs(n);
    }

    for (int i = size - 1; i >= 0; i--) {
        binary[i] = n % 2;
        n = n / 2;
    }
}

void twosComplement(int *binary, int size) {
    int carry = 1;

    for (int i = 0; i < size; i++) {
        binary[i] = binary[i] == 0 ? 1 : 0;
    }

    for (int i = size - 1; i >= 0; i--) {
        binary[i] = binary[i] + carry;
        if (binary[i] == 2) {
            binary[i] = 0;
            carry = 1;
        } else {
            carry = 0;
        }
    }
}

void addTwoBinaries(int *binary1, int *binary2, int size) {
    int carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        binary1[i] = binary1[i] + binary2[i] + carry;
        if (binary1[i] == 2) {
            binary1[i] = 0;
            carry = 1;
        } else if (binary1[i] == 3) {
            binary1[i] = 1;
            carry = 1;
        } else {
            carry = 0;
        }
    }
}

void subtractTwoBinaries(int *binary1, int *binary2, int size) {
    int twosComp[SIZE];
    
    for (int i = 0; i < size; i++) {
        twosComp[i] = binary2[i];
    }
    
    twosComplement(twosComp, size);
    addTwoBinaries(binary1, twosComp, size);
}

void printBinary(int *binary, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", binary[i]);
    }
    printf("\n");
}

int main() {
    int a1, b1, a[SIZE], b[SIZE];

    printf("Enter the first number: ");
    scanf("%d", &a1);
    printf("Enter the second number: ");
    scanf("%d", &b1);
    printf("\n");

    decimalToBinary(a1, a, SIZE);
    if (a1 < 0) {
        twosComplement(a, SIZE);
    }

    printf("First number in binary: ");
    printBinary(a, SIZE);

    decimalToBinary(b1, b, SIZE);
    if (b1 < 0) {
        twosComplement(b, SIZE);
    }

    printf("Second number in binary: ");
    printBinary(b, SIZE);
    printf("\n");

    int sum[SIZE];
    for (int i = 0; i < SIZE; i++) {
        sum[i] = a[i];
    }
    addTwoBinaries(sum, b, SIZE);

    printf("Sum of the given two numbers: ");
    printBinary(sum, SIZE);

    int diff[SIZE];
    for (int i = 0; i < SIZE; i++) {
        diff[i] = a[i];
    }
    subtractTwoBinaries(diff, b, SIZE);

    printf("Difference of the given two numbers: ");
    printBinary(diff, SIZE);

    return 0;
}

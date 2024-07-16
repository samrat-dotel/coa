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

void shiftLeft(int *A, int *Q) {
    for (int i = 0; i < SIZE - 1; i++) {
        A[i] = A[i + 1];
    }
    A[SIZE - 1] = Q[0];

    for (int i = 0; i < SIZE - 2; i++) {
        Q[i] = Q[i + 1];
    }
    Q[SIZE - 2] = 0;
}

void addTwoBinaries(int *binary1, int *binary2, int size){
    int carry = 0;
    for (int i = size - 1; i >= 0; i--){
        binary1[i] = binary1[i] + binary2[i] + carry;
        if (binary1[i] == 2){
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

void printTableHeader() {
    printf("A      Q       Count       Remarks\n");
    printf("----------------------------------\n");
}

void printTableRow(int *A, int *Q, int count, const char *remarks) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d", A[i]);
    }
    printf("  ");
    for (int i = 0; i < SIZE - 1; i++) {
        printf("%d", Q[i]);
    }
    printf("     %d       %s\n", count, remarks);
}

int main() {
    int dividend, divisor, count = SIZE, remainder[SIZE], quotient[SIZE - 1];
    int Q[SIZE - 1] = {0};
    int M[SIZE] = {0};
    int Mcomp[SIZE] = {0};
    int A[SIZE] = {0}; 
    int sign = 1;

    printf("Enter the value of dividend: ");
    scanf("%d", &dividend);
    printf("Enter the value of divisor: ");
    scanf("%d", &divisor);

    if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0)) {
        sign = -1;
    }

    decimalToBinary(dividend, Q, SIZE - 1);

    if (dividend < 0){
        twosComplement(Q, SIZE - 1);
    }
    decimalToBinary(divisor, M, SIZE);

    if (divisor < 0){
        twosComplement(M, SIZE);
    }

    printf("Binary representation of dividend (Q): ");
    for (int i = 0; i < SIZE - 1; i++) {
        printf("%d", Q[i]);
    }
    printf("\n");

    printf("Binary representation of divisor (M): ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d", M[i]);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++){
        Mcomp[i] = M[i];
    }

    twosComplement(Mcomp, SIZE);

    printf("2's complement of M (Mcomp): ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d", Mcomp[i]);
    }
    printf("\n");

    printTableHeader();

    shiftLeft(A, Q);
    printTableRow(A, Q, count, "Initial");

    while (count > 0){
        if (A[0] == 0){
            shiftLeft(A, Q);
            addTwoBinaries(A, M, SIZE);
            printTableRow(A, Q, count, "Shift left, A=A+M");
        }
        else{
            shiftLeft(A, Q);
            addTwoBinaries(A, Mcomp, SIZE);
            printTableRow(A, Q, count, "Shift left, A=A-M");
        }

        if (A[0] == 0){
            Q[SIZE - 2] = 1;
            printTableRow(A, Q, count, "Q0=1");
        }
        else{
            Q[SIZE - 2] = 0;
            printTableRow(A, Q, count, "Q0=0");
        }

        count--;
    }

    if (A[0] == 1){
        addTwoBinaries(A, M, SIZE);
        printTableRow(A, Q, count, "Restore A");
    }

    printf("The remainder is: ");
    for (int i = 0; i < SIZE; i++){
        printf("%d", A[i]);
    }
    printf("\n");

    printf("The quotient is: ");
    for (int i = 0; i < SIZE - 1; i++){
        printf("%d", Q[i]);
    }
    printf("\n");

    if (sign == -1) {
        printf("Quotient is negative.\n");
    } else {
        printf("Quotient is positive.\n");
    }

    return 0;
}

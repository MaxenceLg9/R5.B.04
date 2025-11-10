#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 32

typedef struct {
    int (*aFaire)(int, int);
    int op1;
    int op2;
} oper;

// différentes fonctions d'opérations
int add(int a, int b) { return (a + b); }

int substract(int a, int b) { return (a - b); }

int time(int a, int b) { return (a * b); }

int divide(int a, int b) {
    // gestion de l'erreur division par 0
    if (b == 0) {
        printf("Erreur : division par zéro\n");
        return 0;
    }
    return (a / b);
}

int mod(int a, int b) { return (a % b); }

// execute the calcul inside p
void affiche(void* p, const char symbol) {
    const oper *local = (oper*)p;
    const int res = local->aFaire(local->op1, local->op2);
    printf("%d %c %d = %d\n", local->op1, symbol, local->op2, res);
};

// flushing stdin
void flush() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard until newline
    }
}

// read characters from input up to 32 bytes
// if less than 32 bytes read, doesn't flush stdin
char *read_line(char *buffer) {// initial buffer
    size_t len = 0;
    if (!buffer) return NULL;

    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if(len >= BUFFER_SIZE){
            //printf("Flushing stdin : len %d\n",len);
            flush();
            break;
        }
        buffer[len++] = (char)c;
    }
    //printf("%d characters read\n",len);
    buffer[len] = '\0';
    return buffer;
}

int main(void) {
    // DEFINITIONS OF VARIABLES
    // array of function pointers
    int (*funcs[])(int, int) = {add, substract, time, divide, mod};
    // String to display
    char string[] = "Quelle opération souhaitez-vous effectuer ? +,-,*,/,%";
    // Reference of the + as index 0 isnide the string to display
    const char *plus_ptr = strchr(string,'+');
    char *endPointer = NULL;
    oper Calcul;
    char buff[BUFFER_SIZE + 1];
    while (1) {
        printf("%s\nQuittez avec Q\n", string);
        // Getting one char from stdin, the operand
        const int operation = fgetc(stdin);
        flush();
        if (operation == 'Q') exit(0);

        // Computing the operand with the reference of plus (plus_ptr) to determine which operand has been selected
        const long ptr = (strchr(plus_ptr,operation) - plus_ptr) / 2;
        if (ptr < 0 || ptr > 4) {
            printf("Opération invalide\n");
            continue;
        }
        Calcul.aFaire = funcs[ptr];

        // First number input from stdin
        printf("Entrez le premier nombre : \n");
        read_line(buff);
        // Converting into number
        int n = strtol(buff, &endPointer, 10);
        if (endPointer == buff) {
            printf("Erreur\n");
            continue;
        }
        if (*endPointer != '\0' && *endPointer != '\n') {
            printf("Invalid character: %c\n", *endPointer);
            continue;
        }
        Calcul.op1 = n;
        // Second number to input from stdin
        printf("Entrez le deuxième nombre : \n");
        read_line(buff);
        // Converting it into number
        n = strtol(buff,&endPointer,10);
        if (endPointer == buff) {
            printf("Erreur\n");
            continue;
        }
        if (*endPointer != '\0' && *endPointer != '\n') {
            printf("Invalid character: %c\n", *endPointer);
            continue;
        }
        Calcul.op2 = n;
        // Making the calcul
        affiche(&Calcul, operation);
    }
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 32

typedef struct {
    int (*aFaire)(int, int);
    char symbol;
    int op1;
    int op2;
} oper;

//struct to encapsulate the operation to do and the result to get from the function
struct Calcul {
    oper oper;
    int result;
};

// différentes fonctions d'opérations
int add(int a, int b) { return (a + b); }

int substract(int a, int b) { return (a - b); }

int times(int a, int b) { return (a * b); }

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
void* affiche1(void* arg) {
    struct Calcul *calcul_var = (struct Calcul *)arg;
    const oper *oper_var = &calcul_var->oper;
    calcul_var->result = oper_var->aFaire(oper_var->op1, oper_var->op2);
    printf("%d %c %d = %d\n", oper_var->op1, oper_var->symbol, oper_var->op2, calcul_var->result);
    return NULL;
};

void* affiche2(void* arg) {
    const oper *oper_var = (oper *)arg;
    int *res = malloc(sizeof(int));
    *res = oper_var->aFaire(oper_var->op1, oper_var->op2);
    printf("%d %c %d = %d\n", oper_var->op1, oper_var->symbol, oper_var->op2, *res);
    return res;
}

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
    int (*funcs[])(int, int) = {add, substract, times, divide, mod};
    pthread_t thread[2];
    // String to display
    char string[] = "Quelle opération souhaitez-vous effectuer ? +,-,*,/,%";
    // Reference of the + as index 0 isnide the string to display
    const char *plus_ptr = strchr(string,'+');
    char *endPointer = NULL;
    oper oper_var;
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
        oper_var.symbol = operation;
        oper_var.aFaire = funcs[ptr];

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
        oper_var.op1 = n;
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
        oper_var.op2 = n;
        // Making the calcul
        struct Calcul calcul_var;
        calcul_var.oper = oper_var;
        int err = pthread_create(&thread[0],NULL,affiche1,&calcul_var);
        if (err) {
            perror("eror creating thread\n");
            exit(EXIT_FAILURE);
        }
        err = pthread_create(&thread[1],NULL,affiche2,&oper_var);
        if (err) {
            perror("eror creating thread\n");
            exit(EXIT_FAILURE);
        }
        int *resultat;
        pthread_join(thread[0],NULL);
        pthread_join(thread[1],(void *)&resultat);
        printf("From thread 1, %lu, got result : %d\n", thread[0], calcul_var.result);
        printf("From thread 2, %lu, got result : %d\n", thread[1], *resultat);
    }
}

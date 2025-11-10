/* Gestion des processus sous Linux */
/* TDM1 - Exercice 1 */
/* avec l'utilisation d'un tableau de pointeurs */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wait.h>
#include <string.h>


/* Prototypes des fonctions associées aux fils */
void traitFils1();
void traitFils2();
void traitFils3();

int main() {
    pid_t idProc;
    int i, rapport, numSignal, statut;

    // définition d'une variable 'traitements' de type anaonyme
    // tableau de pointeurs de fonctions sans paramètres (2ème void)
    // ne retournant rien (1er void)
    void (*traitements[])(void) = {traitFils1, traitFils2, traitFils3};

    time_t bonjour = time(NULL);

    /* processus père */
    /* Présentation d'usage */
    printf("\nJe suis : %s et mon UID est :  %d\n", getlogin(), getuid());
    printf("Nous sommes le : %s\n", ctime(&bonjour));

    /* creation des fils */
    for (i = 0; i < 3; i++) {
        idProc = fork();
        switch (idProc) {
        case -1: perror("echec fork");
            exit(1); /* erreur */
        case 0: traitements[i]();
            exit(1); /* traitement associé au fils n° i  */
        }
    }


    /* suite du processus pere */
    /* attente de la terminaison de tous les fils */
    idProc = wait(&rapport);
    while (idProc != -1) {
        printf("\nTerminaison du fils de PID = %d\n", idProc);
        if WIFEXITED(rapport) {
            statut = WEXITSTATUS(rapport);
            printf("Fin normale, statut = %d\n", statut);
        }
        else {
            if WIFSIGNALED(rapport) {
                numSignal = WTERMSIG(rapport);
                printf("Fin anormale, numSignal = %d qui correspond à %s\n", numSignal, strsignal(numSignal));
            }
            else { perror("Erreur système"); }
        }
        idProc = wait(&rapport);
    }
}


/* fin du processus pere */

/* fonction de traitement du fils1 */
/* affiche son pid et se termine normalement en retournant 3 */
void traitFils1() {
    printf("\n***fils1 --> PID= %d\n", getpid());
    exit(3);
}

/* fonction de traitement du fils2 */
/* affiche son pid et tente d'écrire en mémoire à l'adresse NULL */
void traitFils2() {
    int v = 10;
    printf("\n***fils2 --> PID= %d\n", getpid());
    *(int*)NULL = v;
}

/* fonction de traitement du fils3 */
/* affiche son pid et tente d'effectuer une division sournoise par zéro */
void traitFils3() {
    int i, v = 10;
    printf("\n***fils3 --> PID= %d\n", getpid());
    i = 10;
    v = 1 / (v - i);
}

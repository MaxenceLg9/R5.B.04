//
// Created by jean-paul.carrara on 01/11/2025.
// Comment rendre un programme C multiplateforme
//
#include <stdio.h>

#ifdef WINDOWS
#include <windows.h>
#elifdef LINUX
#include <unistd.h>
#endif

int main() {
    int nbCoeurs = 0;

#if defined(WINDOWS)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    nbCoeurs = sysinfo.dwNumberOfProcessors;
#elif defined(LINUX)
    nbCoeurs = sysconf(_SC_NPROCESSORS_ONLN);
#endif
#if defined(WINDOWS) || defined(LINUX)
    printf("Nombre de cœurs du processeur : %d", nbCoeurs);
    return 0;
#else
    printf("Plateforme non supportée");
    return 1;
#endif
}

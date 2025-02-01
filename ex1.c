#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main(void) {
    const key_t key = ftok("./", 'h');
    if (key == -1) { perror("ftok"); return EXIT_FAILURE; }

    const int shmID = shmget(key, sizeof(char)*SHM_SIZE, IPC_CREAT | 0644);
    if (shmID == -1) { perror("shmget"); return EXIT_FAILURE; }

    char *shmPtr = shmat(shmID, NULL, 0);
    if (shmPtr == (void *) -1) { perror("shmat"); return EXIT_FAILURE; }

    const pid_t pid = fork();
    if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }
    if (pid > 0) {
        // Parent process.
        int status;
        if (waitpid(pid, &status, 0) == -1) { perror("waitpid"); return EXIT_FAILURE; }
        if (WIFEXITED(status)) {
            printf("%s", shmPtr);
        }

        printf("Child exited with code %d\n", WEXITSTATUS(status));

        if (shmdt(shmPtr) == -1) { perror("shmdt"); return EXIT_FAILURE; }
        if (shmctl(shmID, IPC_RMID, NULL) == -1) { perror("shmctl"); return EXIT_FAILURE; }
    } else {
        // Child process.
        strcpy(shmPtr, "Ceci est le mssage zbi");
        if (shmdt(shmPtr) == -1) {
            perror("shmdt"); return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BORNE_SUP 50000
#define BORNE_INF 50

int main() {
    const key_t key = ftok("./", 'h');
    if (key == -1) { perror("ftok"); return EXIT_FAILURE; }

    const int shmID = shmget(key, sizeof(int), IPC_CREAT | 0644);
    if (shmID == -1) { perror("shmget"); return EXIT_FAILURE; }

    int *shmPtr = shmat(shmID, NULL, 0);
    if (shmPtr == (void *) -1) { perror("shmat"); return EXIT_FAILURE; }

    const pid_t pid = fork();
    if (pid == -1) { perror("fork"); return EXIT_FAILURE; }
    if (pid > 0) {
        // Parent process
        int status;
        if (waitpid(pid, &status, 0) == -1) { perror("waitpid"); return EXIT_FAILURE; }
        if (WIFEXITED(status)) {
            const int value = *shmPtr;
            const double pow = value * value;
            printf("%d^2 = %lf\n", value, pow);
        }

        printf("Child exited with code %d\n", WEXITSTATUS(status));
    } else {
        // Child process
        srand(arc4random());
        const int rn = BORNE_INF + random() % (BORNE_SUP - BORNE_INF + 1);
        *shmPtr = rn;
        if (shmdt(shmPtr) == -1) { perror("shmdt"); return EXIT_FAILURE; }
    }

    return EXIT_SUCCESS;
}

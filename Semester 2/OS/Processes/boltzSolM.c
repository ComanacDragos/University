#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

bool is_divisible_by_seven(int number) {
    return (number % 7) == 0;
}

bool contains_seven(int number) {
    while (number > 0) {
        if ((number % 10) == 7) {
            return true;
        }
        number = number/10;
    }
    return false;
}

void play(int id, int read_from, int write_to) {
    int number = 1;
    srandom(getpid());

    while(number >= 0) {
        if(0 > read(read_from, &number, sizeof(int))) {
            perror("Error on read from pipe");
            number = -1;
        }

        if(number >= 0) {
            int chance = random() % 10;
            number++;
            if(is_divisible_by_seven(number) || contains_seven(number)) {
                if (chance == 0) {
                    printf("%d --- %d --- Failed\n", id, number);
                    number = -1;
                } else {
                    printf("%d --- Boltz\n", id);
                }
            } else {
                printf("%d --- %d\n", id, number);
            }
        } else {
            printf("%d received %d --- Exiting\n", id, number);
        }
        if(0 > write(write_to, &number, sizeof(int))) {
            perror("Error on write in pipe");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide exactly one argument.\n");
        exit(1);
    }
    int n = atoi(argv[1]), i;
    int children[n-1], p[n][2];

    for (i = 0; i < n; i++) {
        pipe(p[i]);
    }

    for (i = 0; i < n-1; i++) {
        children[i] = fork();
        if(-1 == children[i]) {
            perror("Error on fork");
            exit(1);
        } else if (0 == children[i]) {
            // Child process
            int id = i + 1;
            int read_from = id;
            int write_to = (id + 1) % n;
            play(id, p[read_from][0], p[write_to][1]);
            exit(0);
        }
    }

    int number = 1;
    int id = 0;
    int read_from = id;
    int write_to = id + 1;
    srandom(getpid());
    
    printf("%d --- %d\n", id, number);
    if(0 > write(p[write_to][1], &number, sizeof(int))) {
        perror("Error on write in pipe");
    }
    play(id, p[read_from][0], p[write_to][1]);
    for (i = 0; i < n; i++) {
        wait(0);
    }

    for (i = 0; i < n-1; i++) {
        close(p[i][0]);
        close(p[i][1]);
    }
    return 0;
}

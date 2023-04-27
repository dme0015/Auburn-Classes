#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
/*
// David Estrada
// processes.c
// I used Geeks for geeks to learn more about pipes and forks. www.geeksforgeeks.org/pipe-system-call/
// I used Prof Shaiks ppt to see the structure of forks and pipes.
// Execution Instructions:
// If you want to test files rename in fopen function.
// run few times if output buffer kicks in
// Linux Ubuntu compile:  gcc -o processes processes.c
// Linux Ubuntu compile:  ./processes
*/

int main(int argc, char *argv[])
{
    FILE *the_file = fopen("input.txt", "r"); // open file

    if (the_file == NULL) // error checking if: file name is empty or not fetched.
    {
        perror("Unable to open file!");
        exit(1);
    }

    int letters_count_a = 0;
    int letters_count_b = 0;
    int letters_count_total;

    char line1[1000]; // size 1000
    char line2[1000]; // size 1000

    int fd[2]; // //pipes : fd[0] = read, fd[1] = write
    if (pipe(fd) == -1)
    { // error checking if: pipe fails
        return 1;
    }
    fflush(stdout);
    pid_t child_a, child_b;

    child_a = fork();

    if (child_a == 0)
    {
        /* Child A code */
        close(fd[0]);

        // opens line in child process
        fgets(line1, sizeof(line1), the_file); // gets .txt file from main process
        //  count the number of alphabetical characters in first line
        for (int i = 0; line1[i] != '\0'; i++)
        {
            if (isalpha((unsigned int)line1[i]))
            {
                letters_count_a++;
            }
        }

        write(fd[1], line1, sizeof(line1));                      // pipe write to parent process
        write(fd[1], &letters_count_a, sizeof(letters_count_a)); // pipe write to parent process *
        close(fd[1]);
    }
    else
    {
        child_b = fork();
        if (child_b == 0)
        {
            /* Child B code */
            close(fd[0]);
            // opens line in child process
            fgets(line2, sizeof(line2), the_file); // gets .txt file from main process
            //  count the number of alphabetical characters in first line
            for (int i = 0; line2[i] != '\0'; i++)
            {
                if (isalpha((unsigned int)line2[i]))
                {
                    letters_count_b++;
                }
            }
            write(fd[1], line2, sizeof(line2));                      // pipe write to parent process
            write(fd[1], &letters_count_b, sizeof(letters_count_b)); // pipe write to parent process *
            // write(fd[1], &the_file, sizeof(the_file));
            close(fd[1]);
        }
        else
        {
            /* Parent Code */
            wait(NULL);   // wait for child process to finish executing
            close(fd[1]); // close pipe write

            // int lettersCount;
            read(fd[0], line1, sizeof(line1));                      // pipe read from child_a
            read(fd[0], &letters_count_a, sizeof(letters_count_a)); // pipe read from child
            printf("Alphabetic count in line 1 = %d\n", letters_count_a);

            // sleep(.7);
            read(fd[0], line2, sizeof(line2));                      // pipe read from child_b
            read(fd[0], &letters_count_b, sizeof(letters_count_b)); // pipe read from child
            printf("Alphabetic count in line 2 = %d\n", letters_count_b);

            fclose(the_file);
            getpid();     // Get process ID's for child processes
            close(fd[0]); // close pipe read
            letters_count_total = letters_count_a + letters_count_b;
            printf("Alphabetic count in file = %d\n", letters_count_total);
        }
    }
    return 0;
}
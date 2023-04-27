#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
/*
// David Estrada
// threads.c
// I used Geeks for geeks to learn more about multithreading. www.geeksforgeeks.org/multithreading-c-2/
// Execution Instructions:
// Linux Ubuntu compile:  gcc -pthread -o threads threads.c
// Linux Ubuntu compile:  ./threads
*/
void *processInputLine()
{
    // printf("Test from threads\n");
    FILE *the_file = fopen("input.txt", "r"); // open file
    if (the_file == NULL)                     // error checking if: file name is empty or not fetched.
    {
        perror("Unable to open file!");
        exit(1);
    }
    int letters_count_a = 0; //-used
    int letters_count_b = 0;
    int letters_count_total;

    char line1[1000]; // size 1000 -used
    char line2[1000]; // size 1000
    // opens first line in thread
    fgets(line1, sizeof(line1), the_file);
    for (int i = 0; line1[i] != '\0'; i++)
    {
        if (isalpha((unsigned int)line1[i]))
        {
            letters_count_a++;
        }
    }

    // opens second line in thread
    fgets(line2, sizeof(line2), the_file); // gets .txt file from main process
    //  count the number of alphabetical characters in first line
    for (int i = 0; line2[i] != '\0'; i++)
    {
        if (isalpha((unsigned int)line2[i]))
        {
            letters_count_b++;
        }
    }
}
void *countAlphaChars()
{
    // printf("Test from threads\n");
    FILE *the_file = fopen("input.txt", "r"); // open file
    if (the_file == NULL)                     // error checking if: file name is empty or not fetched.
    {
        perror("Unable to open file!");
        exit(1);
    }
    int letters_count_a = 0; //-used
    int letters_count_b = 0;
    int letters_count_total;

    char line1[1000]; // size 1000 -used
    char line2[1000]; // size 1000
    // opens first line in thread
    fgets(line1, sizeof(line1), the_file);
    for (int i = 0; line1[i] != '\0'; i++)
    {
        if (isalpha((unsigned int)line1[i]))
        {
            letters_count_a++;
        }
    }

    // opens second line in thread
    fgets(line2, sizeof(line2), the_file); // gets .txt file from main process
    //  count the number of alphabetical characters in first line
    for (int i = 0; line2[i] != '\0'; i++)
    {
        if (isalpha((unsigned int)line2[i]))
        {
            letters_count_b++;
        }
    }

    letters_count_total = letters_count_a + letters_count_b;
    printf("Alphabetic count in file = %d\n", letters_count_total);
}
int main(int argc, char *argv[])
{
    pthread_t NewThread, ChildThread;
    pthread_create(&NewThread, NULL, &processInputLine, NULL);
    pthread_join(NewThread, NULL);

    pthread_create(&ChildThread, NULL, &countAlphaChars, NULL);
    pthread_join(ChildThread, NULL);
    return 0;
}
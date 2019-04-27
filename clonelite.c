#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Function to print the Clone Lite Prompt
 *
 * @return void
 */
void print_prompt()
{
    printf("CloneLite > ");
}

/**
 * Function to get the input and return it to be stored into the buffer
 *
 * @param buffer A pointer to the input buffer
 *
 * @return void
 */
void get_input(char * buffer)
{
    scanf("%s", buffer);
}

/**
 * Main Function
 *
 * @param argc: The argument count
 * @param argv: The argument values
 * @return The program exit status
 */
int main(int argc, char * argv[])
{
    char buffer[100];

    while (true) {
        print_prompt();
        get_input(buffer);

        if (strcmp(buffer, ".exit") == 0) {
            printf("[+] Exiting. Good Bye!");
            exit(EXIT_SUCCESS);
        } else {
            printf("[+] Invalid Command '%s'.\n", buffer);
        }
    }

    return 0;
}
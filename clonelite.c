#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum META_COMMAND_RESULT_T {
    META_COMMAND_SUCCESS,
    META_COMMAND_INVALID
};

typedef enum META_COMMAND_RESULT_T META_COMMAND_RESULT;

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
 * Function to check if command is a meta command
 *
 * @param buffer The buffer containing the command
 *
 * @return bool Whether it is a meta command or not
 */
bool is_meta_command(char * buffer)
{
    if (buffer[0] == '.') {
        return true;
    }

    return false;
}

/**
 * Function to execute meta commands
 *
 * @param buffer The buffer containing the command
 *
 * @return META_COMMAND_RESULT The status of running the command
 */
META_COMMAND_RESULT execute_meta_command(char * buffer)
{
    if (strcmp(buffer, ".exit") == 0) {
        printf("[+] Exiting. Good Bye!");

        exit(EXIT_SUCCESS);
    }

    return META_COMMAND_INVALID;
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

        if (is_meta_command(buffer)) {
            switch (execute_meta_command(buffer)) {
                case META_COMMAND_SUCCESS:
                    break;
                case META_COMMAND_INVALID:
                    printf("[+] Invalid Command '%s'.\n", buffer);
                    break;
            }
        } else {
            printf("[+] Invalid Command '%s'.\n", buffer);
        }
    }

    return 0;
}
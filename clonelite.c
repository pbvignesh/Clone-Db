#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum META_COMMAND_RESULT_T {
    META_COMMAND_SUCCESS,
    META_COMMAND_FAILURE_INVALID
};

enum PREPARE_COMMAND_RESULT_T {
    PREPARE_SUCCESS,
    PREPARE_FAILURE_INVALID
};

enum STATEMENT_TYPE_T {
    STATEMENT_SELECT,
    STATEMENT_INSERT
};

typedef enum META_COMMAND_RESULT_T META_COMMAND_RESULT;
typedef enum PREPARE_COMMAND_RESULT_T PREPARE_COMMAND_RESULT;
typedef enum STATEMENT_TYPE_T STATEMENT_TYPE;
typedef struct Statement_t Statement;

struct Statement_t {
    STATEMENT_TYPE type;
};

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

    return META_COMMAND_FAILURE_INVALID;
}

/**
 * Function to prepare the statement for execution
 *
 * @param buffer The buffer containing the command
 * @param statement The final prepared statement output
 *
 * @return PREPARE_COMMAND_RESULT The status of preparing the command
 */
PREPARE_COMMAND_RESULT prepare_statement(char * buffer, Statement * statement)
{
    if (strncmp(buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;

        return PREPARE_SUCCESS;
    }

    if (strncmp(buffer, "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;

        return PREPARE_SUCCESS;
    }

    return PREPARE_FAILURE_INVALID;
}

/**
 * Function to execute the non meta commands
 *
 * @param statement The prepared statement
 *
 * @return void
 */
void execute_statement(Statement * statement)
{
    switch (statement->type) {
        case STATEMENT_INSERT:
            // TODO: Handle Insertion Logic
            break;
        case STATEMENT_SELECT:
            // TODO: Handle Selection Logic
            break;
    }
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
                    continue;
                case META_COMMAND_FAILURE_INVALID:
                    printf("[+] Invalid Command '%s'.\n", buffer);
                    continue;
            }
        } else {
            Statement statement;
            switch (prepare_statement(buffer, &statement)) {
                case PREPARE_SUCCESS:
                    break;
                case PREPARE_FAILURE_INVALID:
                    printf("[+] Invalid Keyword at start of '%s'\n", buffer);
                    continue;
            }

            // No need to check if this ran correctly because it will run correctly for sure
            execute_statement(&statement);
            printf("[+] Statement Executed.\n");
        }
    }

    return 0;
}
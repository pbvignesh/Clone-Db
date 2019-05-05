#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 100

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
typedef struct Buffer_t Buffer;

struct Statement_t {
    STATEMENT_TYPE type;
};

struct Buffer_t {
    char * buffer;
    size_t size;
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
void get_input(Buffer * buffer)
{
    ssize_t bytes_read = getline(&buffer->buffer, &buffer->size, stdin);

    // Ignoring Trailing newline
    buffer->buffer[bytes_read - 1] = 0;
}

/**
 * Function to check if command is a meta command
 *
 * @param buffer The buffer containing the command
 *
 * @return bool Whether it is a meta command or not
 */
bool is_meta_command(Buffer * buffer)
{
    if (buffer->buffer[0] == '.') {
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
META_COMMAND_RESULT execute_meta_command(Buffer * buffer)
{
    if (strcmp(buffer->buffer, ".exit") == 0) {
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
PREPARE_COMMAND_RESULT prepare_statement(Buffer * buffer, Statement * statement)
{
    if (strncmp(buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;

        return PREPARE_SUCCESS;
    }

    if (strncmp(buffer->buffer, "select", 6) == 0) {
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
 * Method to create an empty buffer
 *
 * @return buffer An empty buffer
 */
Buffer * create_buffer()
{
    Buffer * buffer = (Buffer *) malloc (sizeof(Buffer));
    buffer->size = BUFFER_SIZE;
    buffer->buffer = NULL;

    return buffer;
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
    Buffer * buffer = create_buffer();

    while (true) {
        print_prompt();
        get_input(buffer);

        if (is_meta_command(buffer)) {
            switch (execute_meta_command(buffer)) {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_FAILURE_INVALID:
                    printf("[+] Invalid Command '%s'.\n", buffer->buffer);
                    continue;
            }
        } else {
            Statement statement;
            switch (prepare_statement(buffer, &statement)) {
                case PREPARE_SUCCESS:
                    break;
                case PREPARE_FAILURE_INVALID:
                    printf("[+] Invalid Keyword at start of '%s'\n", buffer->buffer);
                    continue;
            }

            // No need to check if this ran correctly because it will run correctly for sure
            execute_statement(&statement);
            printf("[+] Statement Executed.\n");
        }
    }

    return 0;
}
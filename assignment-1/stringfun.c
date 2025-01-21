#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int count_words(char *, int, int);

//add additional prototypes here
void reverse_string(char *, int);
void print_words(char *, int, int);
int replace_string(char *buff, int buff_len, char *str1, char *str2);

int setup_buff(char *buff, char *user_str, int len) {
    int buff_index = 0;
    char *user_ptr = user_str;

    while (*user_ptr != '\0') {
        if (*user_ptr != ' ' && *user_ptr != '\t') {
            if (buff_index >= len) {
                return -1;
            }
            buff[buff_index++] = *user_ptr;
        } else if (buff_index > 0 && buff[buff_index - 1] != ' ') {
            if (buff_index >= len) {
                return -1;
            }
            buff[buff_index++] = ' ';
        }
        user_ptr++;
    }

    while (buff_index > 0 && buff[buff_index - 1] == ' ') {
        buff_index--;
    }

    for (int i = buff_index; i < len; i++) {
        buff[i] = '.';
    }

    return buff_index;
}


void print_buff(char *buff, int len) {
    printf("Buffer:  [");
    for (int i = 0; i < len; i++) {
        putchar(*(buff + i));
    }
    putchar(']');
    putchar('\n');
}

void usage(char *exename) {
    char *basename = exename; // Start with the full path
    char *dot = NULL;

    // Extract the file name without the path
    for (char *p = exename; *p != '\0'; p++) {
        if (*p == '\\' || *p == '/') {
            basename = p + 1;
        }
    }

    // Remove the .exe
    dot = strrchr(basename, '.');
    if (dot != NULL) {
        *dot = '\0';
    }

    // Print the usage message
    printf("usage: ./%s [-h|c|r|w|x] \"string\" [other args]\n", basename);
}


int count_words(char *buff, int len, int str_len) {
    len += 0; // "Using" buff_len to avoid warnings
    if (str_len == 0) return 0;
    int word_count = 0;
    int at_start = 1;
    for (int i = 0; i < str_len; i++) {
        if (*(buff + i) != ' ') {
            if (at_start) {
                word_count++;
                at_start = 0;
            }
        } else {
            at_start = 1;
        }
    }
    return word_count;

}

void reverse_string(char *buff, int str_len) {
    char temp;
    for (int i = 0; i < str_len / 2; i++) {
        temp = *(buff + i);
        *(buff + i) = *(buff + (str_len - 1 - i));
        *(buff + (str_len - 1 - i)) = temp;
    }
}

void print_words(char *buff, int buff_len, int str_len) {
    buff_len += 0; // "Using" buff_len to avoid warnings
    if (str_len == 0) return;
    printf("Word Print\n");
    printf("----------\n");
    int word_num = 1;
    int word_len = 0;
    int word_count = 0;

    for (int i = 0; i < str_len; i++) {
        if (*(buff + i) != ' ') {
            putchar(*(buff + i));
            word_len++;
        } else {
            printf("(%d)\n", word_len);
            word_len = 0;
            word_num++;
            if (i < str_len - 1 && *(buff + i + 1) != ' ') {
                printf("%d. ", word_num);
            }
            word_count++;
        }
    }
    printf("(%d)\n", word_len);
    word_count++;
    printf("\nNumber of words returned: %d\n", word_count);
}

int replace_string(char *buff, int buff_len, char *str1, char *str2) {
    int str1_len = strlen(str1);
    int str2_len = strlen(str2);
    int i = 0;

    while (i < buff_len) {
        if (strncmp(buff + i, str1, str1_len) == 0) {
            int diff = str2_len - str1_len;
            int chars_to_copy = str2_len;

            if (buff_len + diff > BUFFER_SZ) {
                chars_to_copy = BUFFER_SZ - (buff_len - str1_len);
                if (chars_to_copy < 0) chars_to_copy = 0;
            }

            if (diff > 0) {
                memmove(buff + i + str2_len, buff + i + str1_len, buff_len - (i + str1_len));
            } else if (diff < 0) {
                memmove(buff + i + str2_len, buff + i + str1_len, buff_len - (i + str1_len));
                 for (int l = buff_len + diff; l < BUFFER_SZ; l++){
                        *(buff + l) = '.';
                    }
            }

            memcpy(buff + i, str2, chars_to_copy);
            buff_len += diff;
            i += str2_len;
            continue;
        }
        i++;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    char *buff;
    char *input_string;
    char opt;
    int rc;
    int user_str_len;

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    // This is safe because if argc is less than 2, the condition (argc < 2) will evaluate to true, 
    // and the if statement will execute, preventing the program from attempting to access argv[1]
    if ((argc < 2) || (*argv[1] != '-')) {
        usage(argv[0]);
        exit(1);
    }

    opt = (char) * (argv[1] + 1);   //get the option fla

    //handle the help flag and then exit normally
    if (opt == 'h') {
        usage(argv[0]);
        exit(0);
    }

    //TODO:  #2 Document the purpose of the if statement below
    // This if statement checks if the number of command line arguments is less than 3. If it is, it means the user has not provided the input string, so the usage message is printed, and the program exits with an error code of 1.
    if (argc < 3) {
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    buff = (char *) malloc(BUFFER_SZ * sizeof(char));
    if (buff == NULL) {
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);
    if (user_str_len < 0) {
        printf("Error setting up buffer, error = %d\n", user_str_len);
        free(buff);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);
            if (rc < 0) {
                printf("Error counting words, rc = %d\n", rc);
                free(buff);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        case 'r':
            reverse_string(buff, user_str_len);
            printf("Reversed String: ");
            for (int i = 0; i < user_str_len; i++) {
                putchar(*(buff + i));
            }
            putchar('\n');
            break;

        case 'w':
            print_words(buff, BUFFER_SZ, user_str_len);
            break;

        case 'x':
            if (argc != 5) {
                usage(argv[0]);
                free(buff);
                exit(1);
            }
            rc = replace_string(buff, user_str_len, argv[3], argv[4]);
            if (rc != 0) {
                printf("Error with replace operation, rc = %d\n", rc);
                free(buff);
                exit(3);
            }
            break;

        default:
            usage(argv[0]);
            free(buff);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff, BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE 
// Providing both the pointer and the length is good practice because:
// A) It prevents accidental access beyond the allocated memory (the helper functions don't inherently know the buffer size), and
// B) The helper functions become more "general purpose," if this project required more functionality

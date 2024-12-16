#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


int items[10];
int stage = 0;
int locked = 1;

int ask(char *str, char *expected_values[]) {
    char input[64];
    char valid_input[64];

    valid_input[0] = '\0';
    input[0] = '\0';

    int num_strings = 0;
    while (expected_values[num_strings] != NULL) {
        num_strings++;
    }

    for (int j = 0; j < num_strings; j++) {
        strcat(valid_input, expected_values[j]);
        strcat(valid_input, ", ");
    }
    if(strlen(valid_input) > 2)
       valid_input[strlen(valid_input) - 2] = '\0';

    printf("%s (%s) \n", str, valid_input);

    while (true) {
        // gets input
        fgets(input, sizeof(input), stdin);

        // removes newline
        int length = strlen(input);
        if (length > 0 && input[length - 1] == '\n') {
            input[length - 1] = '\0';
        }

        // cheks if input is valid
        for (int i = 0; i < num_strings; i++) {
            if (strcmp(input, expected_values[i]) == 0) {
                return i;
            }
        }

        printf("invalid intput, valid inputs are: %s \n", valid_input);
    }
}

int main(void) {
    int answer;
     // the variables here are local, so I removed the redeclaration.
    //int items[10];  // Shadowing the global
    //int stage; // Shadowing the global
    //int locked; // Shadowing the global


start:
    locked = 1;

    // start of intro
    printf("yesterday, you signed up to join the crew of posiden's hand, a "
           "experimental submarine designed to enter the rift that formed in the "
           "atlantic ocean a year ago. \nIt was a well-paying job but there are "
           "many of things I'm not being told\n\n");
    // sleep(5);
    printf("you cut that thought short, as you arrive to the docks where your "
           "home for the next few months is moored.\n\n");
    // printf("");

    char *values[10] = {"yes", "no", NULL};
    answer = ask("Do you your mind and look for another job?", values);

    // printf("\n%d\n", answer);

    if (answer == 0) {
        printf("ENDING 1 \n\nYou decide to return home and look for another job.\n");
        goto end;
    }

end:
    values[0] = "yes";
    values[1] = "no";
    values[2] = NULL;
    answer = ask("would you like to play again?", values);

    if (answer == 0) {
        printf("\033[2J\033[H");
        goto start;
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int check_cell(int **field, int rows, int columns, int i, int j);
void update_field (int **field, int rows, int columns);
void print_field(int **field, int rows, int columns);
void free_m(int **a, int rows);
int input(int **buffer, int rows, int columns);

int main () {
    
}

void choose_menu(int **field){
    
}

void game (int ** start_statement) {
    int height = 25, wight = 80;
    update_field(start_statement, height, wight);
    print_field(start_statement, height, wight);
}

void update_field(int **field, int rows, int columns) {
    int ** new_field = calloc(rows, sizeof(int *));

    for (int i = 0; i < rows; i++)
        new_field[i] = calloc(columns, sizeof(int));

    for (int i = 0; i < rows; i++) {
        for (int j =  0; j < columns; j++) {
            new_field[i][j] = check_cell(field, rows, columns, i, j);
        }
    }

    for (int i = 0; i < rows; i++){
        free(field[i]);
        field[i] = new_field[i];
    }

    free(new_field);
}

int mode(int coordinate, int size){

}

int check_cell(int **field, int rows, int columns, int i, int j) {

}//

void print_field(int **field, int rows, int columns) {

}//

int ** matrix_init(int *rows, int *columns) {
    int **pointers_matrix = NULL;

    if (scanf("%d", rows) == 0 || *rows <= 0) {
        printf("n/a");
    } else if (scanf("%d", columns) == 0 || *columns <= 0) {
        printf("n/a");
    } else {
        pointers_matrix = malloc(*rows * sizeof(int *));

        for (int i = 0; i < *rows; i++)
            pointers_matrix[i] = malloc(*columns * sizeof(int));

        if (input(pointers_matrix, *rows, *columns) == 1) {
            printf("n/a");

            free_m(pointers_matrix, *rows);
            pointers_matrix = NULL;
        }
    }

    return pointers_matrix;
}

void free_m(int **a, int rows) {
    for (int i = 0; i < rows; i++)
        free(a[i]);

    free(a);
}

int input(int **buffer, int rows, int columns) {
    int flag, trash;

    flag = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int temp;

            if (scanf("%d", &temp) == 0) {
                flag = 1;
                break;
            } else {
                buffer[i][j] = temp;
            }
        }
    }

    trash = getchar();

    while (trash == ' ' || trash == '\t')
        trash = getchar();

    if (trash != '\n')
        flag = 1;

    return flag;
}

void help(const char *mod){
    switch (mod[0]) {
        case 's':
            switch (mod[1]) {
                case 'm':
                    printf("0. Close.\n"
                           "1. Help.\n"
                           "2. Input field.\n"
                           "3. Chose field.\n");
                    break;
                case 'h':
                    printf("0. Close this program.\n"
                           "1. Print this text.\n"
                           "2. Allow you to input field by yourself.\n"
                           "3. Move to choose menu, where you can choose start field.\n"
                           "You can't start game before input/choose field.\n");
                    break;
                default:
                    printf("Wrong command, try again. Enter \"1\" for get more info about commands\n");
            }
            break;
        case 'm':
            switch (mod[1]) {
                case 'm':
                    printf("0. Close.\n"
                           "1. Help.\n"
                           "2. Input field.\n"
                           "3. Chose field.\n"
                           "4. Start.\n");
                    break;
                case 'h':
                    printf("0. Close this program.\n"
                           "1. Print this text.\n"
                           "2. Allow you to input field again by yourself.\n"
                           "\tYou need enter 25 rows with 80 integers inside.\n"
                           "\tIf you mistake field won't update.\n"
                           "3. Move to choose menu, where you can choose again start field.\n"
                           "4. Start the game.\n");
                    break;
                default:
                    printf("Wrong command, try again. Enter \"1\" for get more info about commands\n");
            }
            break;
        case 'c':
            switch (mod[1]) {
                case 'm':
                    printf("0. Back.\n"
                           "1. Help.\n"
                           "2. field_1.\n"
                           "3. field_2.\n"
                           "4. field_3.\n");
                    break;
                case 'h':
                    printf("0. Move to previous menu.\n"
                           "1. Print this text.\n"
                           "2. Make start field like (description field_1)\n"
                           "3. Make start field like (description field_2)\n"
                           "4. Make start field like (description field_3)\n");
                    break;
                default:
                    printf("Wrong command, try again. Enter \"1\" for get more info about commands\n");
            }
            break;
        default:
            printf("Wrong command, try again. Enter \"1\" for get more info about commands\n");
    }
}

void help_for_choose_menu(){
    
}

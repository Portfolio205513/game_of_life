#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>

int check_cell(int **field, int rows, int columns, int i, int j);
int update_field (int **field, int rows, int columns);
void print_field(int **field, int rows, int columns);
void free_m(int **a, int rows);
int input_field(int **buffer, int rows, int columns);
void game(int **field, int rows, int columns);
int ** matrix_init(int rows, int columns);
void to_not_canon();
void to_canon();
void output(int **buffer, int rows, int columns);

struct termios saved_attributes;

int main () {
    int **field;
    int rows, columns;

    rows = 25;
    columns = 80;

    field = matrix_init(rows, columns);


    if (field) {
        to_not_canon();
        game(field, rows, columns);
        to_canon();
    }
}

void game(int **field, int rows, int columns) {
    int input;
    double step, speed;
    clock_t start;

    step = 0.1;
    speed = 5;
    start = clock();

    while (1) {

        if ((speed != -1.0125 && (double) (clock() - start) / CLOCKS_PER_SEC >= speed * step) || (speed == -1.0125 && (input == 61 || input == 43))) {
            if (update_field(field, rows, columns) == 1){
                print_field(field, rows, columns);
                printf("end of game\n");
                break;
            }
                
            print_field(field, rows, columns);
            start = clock();
        }

        input = getchar();

        if (47 < input && input < 58)
            speed = (double) (1.1125) * (input - 48) - 1.0125;
    }
}

void to_not_canon() {
    struct termios termios_attr;
    int flags;
    flags = fcntl(0, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(0, F_SETFL, flags);
    tcgetattr(0, &saved_attributes);
    atexit(to_canon);
    tcgetattr(0, &termios_attr);
    termios_attr.c_lflag &= ~(ICANON|ECHO);
    termios_attr.c_cc[VMIN] = 1;
    termios_attr.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &termios_attr);
}

void to_canon() {
    tcsetattr(0, TCSAFLUSH, &saved_attributes);
}

int update_field(int **field, int rows, int columns) {
    int flag = 1;
    int ** new_field = calloc(rows, sizeof(int *));

    for (int i = 0; i < rows; i++)
        new_field[i] = calloc(columns, sizeof(int));

    for (int i = 0; i < rows; i++) {
        for (int j =  0; j < columns; j++) {
            new_field[i][j] = check_cell(field, rows, columns, i, j);
            if (new_field[i][j] == 1)
                flag = 0;
        }
    }

    for (int i = 0; i < rows; i++){
        free(field[i]);
        field[i] = new_field[i];
    }

    free(new_field);

    return flag;
}

int module(int coordinate, int size){
    if (coordinate >= 0) {
        coordinate = coordinate % size;
    } else {
        coordinate = size + (coordinate % size);
    }
    return coordinate;

}

int check_cell(int **field, int rows, int columns, int i, int j) {
    int neighbour, ans;

    neighbour = 0;

    if (field[module(i - 1, rows)][j] == 1) {
        neighbour += 1;
    }
    if (field[module(i + 1, rows)][j] == 1) {
        neighbour += 1;
    }
    if (field[module(i + 1, rows)][module(j + 1, columns)] == 1) {
        neighbour += 1;
    }
    if (field[module(i - 1, rows)][module(j - 1, columns)] == 1) {
        neighbour += 1;
    }
    if (field[module(i - 1, rows)][module(j + 1, columns)] == 1) {
        neighbour += 1;
    }
    if (field[module(i + 1, rows)][module(j - 1, columns)] == 1) {
        neighbour += 1;
    }
    if (field[i][module(j + 1, columns)] == 1) {
        neighbour += 1;
    }
    if (field[i][module(j - 1, columns)] == 1) {
        neighbour += 1;
    }


    if ((field[i][j] == 1 && neighbour == 2) || neighbour == 3)
        ans = 1;
    else
        ans = 0;

    return ans;
}

void print_field(int **field, int rows, int columns) {
    printf("\033[2J");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++){
            if (field[i][j] == 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int ** matrix_init(int rows, int columns) {
    int **pointers_matrix = NULL;

    pointers_matrix = malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++)
        pointers_matrix[i] = malloc(columns * sizeof(int));

    if (input_field(pointers_matrix, rows, columns) == 1) {
        printf("n/a");
        free_m(pointers_matrix, rows);
        pointers_matrix = NULL;
    }

    return pointers_matrix;
}

void free_m(int **a, int rows) {
    for (int i = 0; i < rows; i++)
        free(a[i]);

    free(a);
}

int input_field(int **buffer, int rows, int columns) {
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

void output(int **buffer, int rows, int columns) {
    for (int i = 0; i < rows - 1; i++) {
        printf("%d", buffer[i][0]);

        for (int j = 1; j < columns; j++)
            printf(" %d", buffer[i][j]);

        printf("\n");
    }

    printf("%d", buffer[rows - 1][0]);

    for (int j = 1; j < columns; j++)
        printf(" %d", buffer[rows - 1][j]);
}

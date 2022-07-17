#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>

int check_cell(int **field, int rows, int columns, int i, int j);
int **update_field(int **field, int rows, int columns, int *alive);
void print_field(int **field, int rows, int columns, int alive);
void free_m(int **a, int rows);
int input_field(int **buffer, int rows, int columns);
int input_field_file(int **buffer, int rows, int columns, char *path);
void game(int **field, int rows, int columns);
int ** matrix_init(int rows, int columns, char *path);
void to_not_canon();
void to_canon();
void output(int **buffer, int rows, int columns);
char *readline_();
char *freadline_(FILE *file);
int strlen_(char *str);
void memcpy_(char *dest, const char *source, size_t count);

struct termios saved_attributes;

int main (int argc, char **argv) {
    int **field;
    int rows, columns;

    rows = 25;
    columns = 80;

    if (argc > 2)
        printf("Too many arguments.\n");
    else if (argc == 2){
        field = matrix_init(rows, columns, argv[1]);
        if (field) {
            to_not_canon();
            game(field, rows, columns);
            to_canon();
        }

        free_m(field, rows);
    } else {
        printf("Enter matrix 25*80\n");
        field = matrix_init(rows, columns, NULL);
        if (field) {
            to_not_canon();
            game(field, rows, columns);
            to_canon();
        }

        free_m(field, rows);
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
        int alive = 0;

        if ((speed != -1.0125 && (double) (clock() - start) / CLOCKS_PER_SEC >= speed * step) || (speed == -1.0125 && (input == 61 || input == 43))) {
            field = update_field(field, rows, columns, &alive);
            if (alive == 0){
                print_field(field, rows, columns, alive);
                printf("end of game\n");
                break;
            }

            print_field(field, rows, columns, alive);
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

int **update_field(int **field, int rows, int columns, int *alive) {
    *alive = 0;
    int ** new_field = calloc(rows, sizeof(int *));

    for (int i = 0; i < rows; i++)
        new_field[i] = calloc(columns, sizeof(int));

    for (int i = 0; i < rows; i++) {
        for (int j =  0; j < columns; j++) {
            new_field[i][j] = check_cell(field, rows, columns, i, j);
            if (new_field[i][j] == 1)
                (*alive)++;
        }
    }

    free_m(field, rows);

    return new_field;
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

void print_field(int **field, int rows, int columns, int alive) {
    printf("\033[2J");

    for (int i = 0; i < 38; i++)
        printf(" ");

    printf("ALIFE:%d\n", alive);

    for (int i = 0; i < rows+2; i++) {
        for (int j = 0; j < columns+2; j++){
            if (i == 0 || i == 26)
                printf("=");
            else if (j == 0 || j == 81)
                printf("|");
            else if (field[i - 1][j - 1] == 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int ** matrix_init(int rows, int columns, char *path) {
    int **pointers_matrix;

    pointers_matrix = malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++)
        pointers_matrix[i] = malloc(columns * sizeof(int));

    if (path != NULL ? input_field_file(pointers_matrix, rows, columns, path) : input_field(pointers_matrix, rows, columns) == 1) {
        printf("Wrong format.\n");
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

            if (scanf("%d", &temp) == 0 || (temp != 1 && temp != 0)) {
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

int input_field_file(int **buffer, int rows, int columns, char *path) {
    int flag, trash;
    FILE *file;

    flag = 0;
    file = fopen(path, "r");

    if (!file){
        flag = 1;
        printf("Wrong path to file.\n");
    } else {
        for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
            int temp;

            if (fscanf(file, "%d", &temp) == 0 || (temp != 1 && temp != 0)) {
                flag = 1;
                break;
            } else {
                buffer[i][j] = temp;
            }
        }

    trash = fgetc(file);

    while (trash == ' ' || trash == '\t')
        trash = fgetc(file);

    if (trash != '\n')
        flag = 1;
    }

    fclose(file);

    return flag;
}

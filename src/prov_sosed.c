/* часть кода, которая будет проверять соеседей данной клетки. 
от этого зависит живая онаили мертвая будет в следующем обновлении поля(поколение, если по-умному)
*
правила:
    - если у МЕРТВОЙ клетки ровно 3 соседа, то она становится ЖИВОЙ
    - если у ЖИВОЙ клетки  2  ИЛИ  3  соседа, то она остается ЖИВОЙ
    - если у ЖИВОЙ клетки  меньше 2  соседок, то она становится МЕРТВОЙ
    - если у ЖИВОЙ клетки  больше 3  соседок, то она становится МЕРТВОЙ 
*/

check_cell(int **field, int rows, int columns, int i, int j); // объявление всей функции проверки соседей
int module(int coordinate, int size); // ф-я переноса "координаты" на противоположный край ((реализация карты в 3д формы тора))

int check_cell(int **field, int rows, int columns, int i, int j) {
    int neighbour; // счётчик соседей
    int ans; // значение, которое возвращает функция
    if (field[module(j - 1, rows)][i] == 1) {
        neighbour += 1;
    }
    if (field[module(j + 1, rows)][i] == 1) {
        neighbour += 1;
    }
    if (field[module(j + 1, rows)][module(i + 1, rows)] == 1) {
        neighbour += 1;
    }
    if (field[module(j - 1, rows)][module(i - 1, rows)] == 1) {
        neighbour += 1;
    }
    if (field[module(j - 1, rows)][module(i + 1, rows)] == 1) {
        neighbour += 1;
    }
    if (field[module(j + 1, rows)][module(i - 1, rows)] == 1) {
        neighbour += 1;
    }
    if (field[j][module(i + 1, rows)] == 1) {
        neighbour += 1;
    }
    if (field[j][module(i - 1, rows)] == 1) {
        neighbour += 1;
    }
    if ( neighbour == 2 || neighbour == 3) {
        ans = 1;
    } else {
        ans == 0;
    }
    return ans;
}

int module(int coordinate, int size) {   
    if ( coordinate >= 0) {
        coordinate = coordinate % size;
    } else {
        coordinate = 25 + (coordinate % size);
    }
    return coordinate;
}
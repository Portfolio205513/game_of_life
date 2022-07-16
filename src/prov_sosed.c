/* часть кода, которая будет проверять соеседей данной клетки. 
от этого зависит живая онаили мертвая будет в следующем обновлении поля(поколение, если по-умному)
*
правила:
    - если у МЕРТВОЙ клетки ровно 3 соседа, то она становится ЖИВОЙ
    - если у ЖИВОЙ клетки  2  ИЛИ  3  соседа, то она остается ЖИВОЙ
    - если у ЖИВОЙ клетки  меньше 2  соседок, то она становится МЕРТВОЙ
    - если у ЖИВОЙ клетки  больше 3  соседок, то она становится МЕРТВОЙ 
*/

neig_ch(int **field, int rows, int columns, int i, int j);

int neig_ch(int **field, int rows, int columns, int i, int j) {
    int neighbour;
    int ans;
    if (field[j - 1][i] == 1) {
        neighbour += 1;
    }
    if (field[j + 1][i] == 1) {
        neighbour += 1;
    }
    if (field[j + 1][i + 1] == 1) {
        neighbour += 1;
    }
    if (field[j - 1][i - 1] == 1) {
        neighbour += 1;
    }
    if (field[j - 1][i + 1] == 1) {
        neighbour += 1;
    }
    if (field[j + 1][i - 1] == 1) {
        neighbour += 1;
    }
    if (field[j][i + 1] == 1) {
        neighbour += 1;
    }
    if (field[j][i - 1] == 1) {
        neighbour += 1;
    }
    if ( neighbour == 2 || neighbour == 3) {
        ans = 1;
    } else {
        ans == 0;
    }
    return ans;
}
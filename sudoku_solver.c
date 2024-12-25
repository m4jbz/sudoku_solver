#include <stdio.h>

#define N 9

void print_board(int b[N][N])
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j % 3 == 0 && j > 0) {
                printf("| ");
            }
            printf("|%d", b[i][j]);
        }
        printf("|\n");
        if ((i+1) % 3 == 0 && (i+1) < 9) {
            printf("-----------------------\n");
        }
    }
}

int is_unassigned(int b[N][N], int* row, int* column) {
    for (*row = 0; *row < N; ++(*row)) {
        for (*column = 0; *column < N; ++(*column)) {
            if (b[*row][*column] == 0) {
                return 1;
            }
        }
    }

    return 0;
}

int used_in_col(int b[N][N], int column, int number)
{
    for (int row = 0; row < N; ++row) {
        if (b[row][column] == number) {
            return 1;
        }
    }

    return 0;
}

int used_in_row(int b[N][N], int row, int number)
{
    for (int column= 0; column < N; ++column) {
        if (b[row][column] == number) {
            return 1;
        }
    }

    return 0;
}

int used_in_box(int b[N][N], int s_row, int s_col, int number)
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (b[s_row + i][s_col + j] == number) {
                return 1;
            }
        }
    }

    return 0;
}

int is_valid(int b[N][N], int row, int column, int n) {
    if (!used_in_col(b, column, n) &&
        !used_in_row(b, row, n) &&
        !used_in_box(b, row - row % 3, column - column % 3, n)) {
        return 1;
    }

    return 0;
}

int solve_sudoku(int b[N][N])
{
    int r, c;

    if (!is_unassigned(b, &r, &c)) {
        return 1;
    }

    for (int i = 1; i < 10; ++i) {
        if (is_valid(b, r, c, i)) {
            b[r][c] = i;
            
            if (solve_sudoku(b)) {
                return 1;
            }

            b[r][c] = 0;
        }
    }

    return 0;
}


int main()
{
    int board[N][N] = {{0, 0, 4, 1, 0, 0, 6, 0, 0},
                       {2, 0, 0, 0, 9, 8, 7, 0, 0},
                       {8, 0, 5, 0, 0, 4, 0, 1, 0},
                       {3, 0, 0, 0, 2, 7, 5, 0, 0},
                       {7, 0, 0, 9, 0, 0, 0, 4, 0},
                       {4, 0, 0, 6, 0, 3, 0, 9, 0},
                       {0, 0, 0, 3, 0, 0, 0, 5, 1},
                       {0, 0, 0, 0, 0, 0, 9, 0, 0},
                       {1, 0, 8, 2, 0, 0, 0, 7, 0}};

    print_board(board);
    printf("\n\n");

    if (!solve_sudoku(board)) {
        printf("No tiene solucion.\n");
        return 0;
    }

    print_board(board);

    return 0;
}

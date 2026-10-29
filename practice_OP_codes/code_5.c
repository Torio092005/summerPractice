#include <stdio.h>

// Структура результата обработки
typedef struct {
    int error_flag; /* 0 — нет ошибок */
} Result;

// Ввод матрицы
int input_matrix(int *m, int *n, int A[50][50]) {
    int flag = 0;
    int tm, tn;

    printf("Введите размеры матрицы m n: ");
    if (scanf("%d %d", &tm, &tn) != 2) {
        flag = 1; // ошибка формата
    }

    else if (tm <= 0 || tn <= 0 || tm > 50 || tn > 50) {
            flag = 2; // некорректные размеры
    }

    else {
        *m = tm;
        *n = tn;
        printf("Введите элементы матрицы (%d строк по %d чисел):\n", tm, tn);

        int i = 0;
        while (i < tm && flag == 0) {
            int j = 0;
            while (j < tn && flag == 0) {
                if (scanf("%d", &A[i][j]) != 1) {
                    flag = 1;
                }
                j++;
            }
            i++;
        }
    }

    return flag;
}

/*
Обработка матрицы:
каждый элемент заменяется минимумом подматрицы (1..i, 1..j)
*/
Result process_matrix(int m, int n, int A[50][50]) {
    Result r;
    r.error_flag = 0;

    int i = 0;
    while (i < m) {
        int j = 0;
        while (j < n) {

            int min_val = A[0][0];
            int x = 0;

            // поиск минимума в подматрице
            while (x <= i) {
                int y = 0;
                while (y <= j) {
                    if (A[x][y] < min_val) {
                        min_val = A[x][y];
                    }
                    y++;
                }
                x++;
            }

            A[i][j] = min_val;
            j++;
        }
        i++;
    }

    return r;
}

// Вывод матрицы
void output_matrix(int m, int n, int A[50][50]) {
    printf("Результирующая матрица:\n");

    int i = 0;
    while (i < m) {
        int j = 0;
        while (j < n) {
            printf("%d ", A[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

int main(void) {
    int m, n;
    int A[50][50];

    int err = input_matrix(&m, &n, A);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный формат ввода.\n");
            return 1;
        case 2:
            printf("Ошибка: размеры матрицы должны быть в диапазоне 1..50.\n");
            return 1;
        default:
            printf("Неизвестная ошибка ввода.\n");
            return 1;
    }

    Result r = process_matrix(m, n, A);

    switch (r.error_flag) {
        case 0:
            output_matrix(m, n, A);
            break;
        default:
            printf("Неизвестная ошибка обработки.\n");
            break;
    }

    return 0;
}


#include <stdio.h>

#define MAXN 50

// Структура результата
typedef struct {
    int error_flag;
} Result;

// Ввод матрицы A(n,n)
int input_matrix(int *n, int A[MAXN][MAXN]) {
    int flag = 0;
    int tn;

    printf("Введите размер матрицы n: ");
    if (scanf("%d", &tn) != 1) {
        flag = 1;
    }

    if (flag == 0) {
        if (tn <= 0 || tn > MAXN) {
            flag = 2;
        }
    }

    if (flag == 0) {
        *n = tn;
        printf("Введите матрицу %d x %d:\n", tn, tn);

        int i = 0;
        while (i < tn && flag == 0) {
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
Разложение A = B + C + D
B — строго нижнетреугольная (i > j)
C — диагональная (i == j)
D — строго верхнетреугольная (i < j)
Все три матрицы храним в одномерных массивах
*/
Result decompose(int n, int A[MAXN][MAXN],
                 int B[], int C[], int D[])
{
    Result r;
    r.error_flag = 0;

    int idxB = 0;
    int idxC = 0;
    int idxD = 0;

    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < n) {

            // Строго нижний треугольник
            if (i > j) {
                // сохраняем A[i][j] в B
                B[idxB] = A[i][j];
                idxB++;
            }

            // Диагональ
            if (i == j) {
                // сохраняем A[i][j] в C
                C[idxC] = A[i][j];
                idxC++;
            }

            // Строго верхний треугольник
            if (i < j) {
                // сохраняем A[i][j] в D
                D[idxD] = A[i][j];
                idxD++;
            }

            j++;
        }
        i++;
    }

    return r;
}

/*
Вывод треугольной матрицы из упакованного массива
Тип:
 type = 1 → нижняя
 type = 2 → диагональ
 type = 3 → верхняя
*/
void output_triangular(int n, int arr[], int type) {
    int idx = 0;

    printf("\n");

    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < n) {

            if (type == 1) { // нижняя
                if (i > j) {
                    printf("%d ", arr[idx]);
                    idx++;
                } else {
                    printf("0 ");
                }
            }

            if (type == 2) { // диагональ
                if (i == j) {
                    printf("%d ", arr[idx]);
                    idx++;
                } else {
                    printf("0 ");
                }
            }

            if (type == 3) { // верхняя
                if (i < j) {
                    printf("%d ", arr[idx]);
                    idx++;
                } else {
                    printf("0 ");
                }
            }

            j++;
        }
        printf("\n");
        i++;
    }
}

int main(void) {
    int n;
    int A[MAXN][MAXN];

    int err = input_matrix(&n, A);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный формат ввода.\n");
            return 1;
        case 2:
            printf("Ошибка: n должно быть в диапазоне 1..%d.\n", MAXN);
            return 1;
        default:
            printf("Неизвестная ошибка ввода.\n");
            return 1;
    }

    // Размеры упакованных массивов
    int sizeB = n * (n - 1) / 2;
    int sizeC = n;
    int sizeD = n * (n - 1) / 2;

    int B[sizeB];
    int C[sizeC];
    int D[sizeD];

    Result r = decompose(n, A, B, C, D);

    switch (r.error_flag) {
        case 0:
            printf("\nСтрого нижняя треугольная матрица B:\n");
            output_triangular(n, B, 1);

            printf("\nДиагональная матрица C:\n");
            output_triangular(n, C, 2);

            printf("\nСтрого верхняя треугольная матрица D:\n");
            output_triangular(n, D, 3);
            break;

        default:
            printf("Неизвестная ошибка вычислений.\n");
            break;
    }

    return 0;
}


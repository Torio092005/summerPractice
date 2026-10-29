#include <stdio.h>

#define MAXM 100
#define MAXN 100

typedef struct {
    int error_flag;
} Result;

// Ввод поля m x n, проверка размеров и значений (0 или 1)
int input_field(int *m, int *n, int a[MAXM][MAXN]) {
    int flag = 0;
    int tm, tn;

    printf("Введите размеры поля m n: ");
    if (scanf("%d %d", &tm, &tn) != 2) {
        flag = 1;
    }

    else if (tm <= 0 || tn <= 0 || tm > MAXM || tn > MAXN) {
            flag = 2;
    }

    else {
        *m = tm;
        *n = tn;
        printf("Введите поле (%d строк по %d чисел: 1 — непрозрачный, 0 — прозрачный):\n", tm, tn);

        int i = 0;
        while (i < tm && flag == 0) {
            int j = 0;
            while (j < tn && flag == 0) {
                if (scanf("%d", &a[i][j]) != 1) {
                    flag = 1;
                } else if (!(a[i][j] == 0 || a[i][j] == 1)) {
                        flag = 3;
                }
                j++;
            }
            i++;
        }
    }

    return flag;
}

/*
Обработка поля:
удалить (сделать прозрачными) все непрозрачные кубики,
видимые хотя бы с одной из 4 сторон
*/
Result process_field(int m, int n, int a[MAXM][MAXN]) {
    Result r;
    r.error_flag = 0;

    int vis[MAXM][MAXN];

    int i = 0;
    while (i < m) {
        int j = 0;
        while (j < n) {
            vis[i][j] = 0;
            j++;
        }
        i++;
    }

    // Видимость слева
    i = 0;
    while (i < m) {
        int found = 0;
        int j = 0;
        while (j < n) {
            if (found == 0) {
                if (a[i][j] == 1) {
                    vis[i][j] = 1;
                    found = 1;
                }
            }
            j++;
        }
        i++;
    }

    // Видимость справа
    i = 0;
    while (i < m) {
        int found = 0;
        int j = n - 1;
        while (j >= 0) {
            if (found == 0) {
                if (a[i][j] == 1) {
                    vis[i][j] = 1;
                    found = 1;
                }
            }
            j--;
        }
        i++;
    }

    // Видимость сверху
    int j = 0;
    while (j < n) {
        int found = 0;
        i = 0;
        while (i < m) {
            if (found == 0) {
                if (a[i][j] == 1) {
                    vis[i][j] = 1;
                    found = 1;
                }
            }
            i++;
        }
        j++;
    }

    // Видимость снизу
    j = 0;
    while (j < n) {
        int found = 0;
        i = m - 1;
        while (i >= 0) {
            if (found == 0) {
                if (a[i][j] == 1) {
                    vis[i][j] = 1;
                    found = 1;
                }
            }
            i--;
        }
        j++;
    }

    // Удаление видимых непрозрачных кубиков
    i = 0;
    while (i < m) {
        j = 0;
        while (j < n) {
            if (a[i][j] == 1 && vis[i][j] == 1) {
                a[i][j] = 0;
            }
            j++;
        }
        i++;
    }

    return r;
}

// Вывод поля
void output_field(int m, int n, int a[MAXM][MAXN]) {
    int i = 0;
    printf("Поле после удаления видимых непрозрачных кубиков:\n");
    while (i < m) {
        int j = 0;
        while (j < n) {
            printf("%d ", a[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

// Основная функция
int main(void) {
    int m, n;
    int a[MAXM][MAXN];

    int err = input_field(&m, &n, a);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный формат ввода.\n");
            break;
        case 2:
            printf("Ошибка: размеры поля должны быть в диапазоне 1..%d x 1..%d.\n", MAXM, MAXN);
            break;
        case 3:
            printf("Ошибка: элементы поля должны быть только 0 или 1.\n");
            break;
        default:
            printf("Неизвестная ошибка ввода.\n");
            break;
    }

    Result r = process_field(m, n, a);

    switch (r.error_flag) {
        case 0:
            output_field(m, n, a);
            break;
        default:
            printf("Неизвестная ошибка обработки.\n");
            break;
    }

    return 0;
}


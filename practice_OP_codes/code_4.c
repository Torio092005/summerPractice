#include <stdio.h>

// Структура результата вычислений
typedef struct {
    double mean;       // среднее значение
    double variance;   // дисперсия
    unsigned short error_flag;    // код ошибки
} Result;

// Ввод данных: размер массива и элементы
int input_data(int *k, double *arr) {
    unsigned short flag = 0;
    int tk;

    printf("Введите количество элементов k: ");
    if (scanf("%d", &tk) != 1) {
        flag = 1; // ошибка формата
    }

    else if (tk <= 1 || tk > 1000) {
            flag = 2; // некорректный размер
    }

    else {
        *k = tk;
        printf("Введите %d элементов массива:\n", tk);

        unsigned short i = 0;
        while (i < tk && flag == 0) {
            if (scanf("%lf", &arr[i]) != 1) {
                flag = 1;
            }
            i++;
        }
    }

    return flag;
}

// Вычисление среднего и дисперсии за один проход массива
Result compute_stats(double *arr, int k) {
    Result r;
    r.mean = 0.0;
    r.variance = 0.0;
    r.error_flag = 0;

    double s1 = 0.0;
    double s2 = 0.0;

    int i = 0;
    while (i < k) {
        double x = arr[i];
        s1 += x;
        s2 += x * x;
        i++;
    }

    r.mean = s1 / k;
    r.variance = (s2 / (k - 1)) - (s1 * s1) / (k * (k - 1));

    return r;
}

// Вывод результата
void output_result(Result r) {
    printf("Среднее значение: %.6f\n", r.mean);
    printf("Дисперсия: %.6f\n", r.variance);
}

// Основная функция
int main(void) {
    int k;
    double arr[1000];

    int err = input_data(&k, arr);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный формат ввода.\n");
            return 1;
        case 2:
            printf("Ошибка: k должно быть > 1 и ≤ 1000.\n");
            return 1;
        default:
            printf("Неизвестная ошибка ввода.\n");
            return 1;
    }

    Result r = compute_stats(arr, k);

    switch (r.error_flag) {
        case 0:
            output_result(r);
            break;
        default:
            printf("Неизвестная ошибка вычислений.\n");
            break;
    }

    return 0;
}


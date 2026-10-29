#include <stdio.h>

/*
Структура результата вычислений
error_flag = 0  -> ошибок нет
error_flag != 0 -> ошибка, код передаётся в main()
*/
typedef struct {
    double a1;
    double a2;
    double a3;
    int error_flag;
} Result;

/*
Функция ввода данных
Проверяет корректность: p0 <= p1 <= p2 <= p3
*/
int input_data(double *p0, double *p1, double *p2, double *p3) {
    int flag = 0;
    double t0, t1, t2, t3;

    printf("Введите p0 p1 p2 p3: ");
    if (scanf("%lf %lf %lf %lf", &t0, &t1, &t2, &t3) != 4) {
        flag = 1; // ошибка ввода
    }

    if (flag == 0) {
        if (!(t0 >= 0 && t1 >= t0 && t2 >= t1 && t3 >= t2)) {
            flag = 2; // логическая ошибка входных данных
        }
    }

    if (flag == 0) {
        *p0 = t0;
        *p1 = t1;
        *p2 = t2;
        *p3 = t3;
    }

    return flag;
}

/*
Функция вычисления оплаты.
Делит p0 на троих, остальное — пропорционально времени
*/
Result compute_payment(double p0, double p1, double p2, double p3) {
    Result r;
    r.error_flag = 0;
    r.a1 = r.a2 = r.a3 = 0.0;

    double t1 = p1 - p0;
    double t2 = p2 - p0;
    double t3 = p3 - p0;

    double total_time = t1 + t2 + t3;

    if (total_time <= 0) {
        r.error_flag = 3; // невозможно распределить
    }

    if (r.error_flag == 0) {
        double base = p0 / 3.0;

        r.a1 = base + (t1 / total_time) * (p3 - p0);
        r.a2 = base + (t2 / total_time) * (p3 - p0);
        r.a3 = base + (t3 / total_time) * (p3 - p0);
    }

    return r;
}


// Функция вывода результата
void output_result(Result r) {
    if (r.error_flag == 0) {
        printf("Пассажир 1: %.2f рублей\n", r.a1);
        printf("Пассажир 2: %.2f рублей\n", r.a2);
        printf("Пассажир 3: %.2f рублей\n", r.a3);
    }
}


// Основная функция: обработка ошибок через switch-case
int main(void) {
    double p0, p1, p2, p3;
    int err = input_data(&p0, &p1, &p2, &p3);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный формат ввода.\n");
            return 1;
        case 2:
            printf("Ошибка: должны выполняться условия p0 <= p1 <= p2 <= p3.\n");
            return 1;
        default:
            printf("Неизвестная ошибка ввода.\n");
            return 1;
    }

    Result r = compute_payment(p0, p1, p2, p3);

    switch (r.error_flag) {
        case 0:
            output_result(r);
            break;
        case 3:
            printf("Ошибка: невозможно распределить стоимость.\n");
            break;
        default:
            printf("Неизвестная ошибка вычислений.\n");
            break;
    }

    return 0;
}


#include <stdio.h>

//Структура результата вычислений
typedef struct {
    int can_pay;      /* 1 — сможет погасить, 0 — нет */
    int years;        /* количество лет */
    int error_flag;   /* код ошибки */
} Result;

// Ввод данных с проверкой корректности
int input_data(double *k, double *p, double *r) {
    int flag = 0;
    double tk, tp, tr;

    printf("Введите k p r: ");
    if (scanf("%lf %lf %lf", &tk, &tp, &tr) != 3) {
        flag = 1; /* ошибка формата */
    }

    if (flag == 0) {
        if (tk <= 0 || tp < 0 || tr < 0) {
            flag = 2; /* логическая ошибка */
        }
    }

    if (flag == 0) {
        *k = tk;
        *p = tp;
        *r = tr;
    }

    return flag;
}

// Вычисление: сможет ли предприниматель погасить кредит
Result compute(double k, double p, double r) {
    Result res;
    res.can_pay = 0;
    res.years = 0;
    res.error_flag = 0;

    double debt = k;
    double rate = 1.0 + p / 100.0;

    // Проверка: если прибыль меньше процентов — погашение невозможно
    if (r <= k * (p / 100.0)) {
        res.can_pay = 0;
        return res;
    }

    // Иначе считаем по годам
    int y = 0;
    while (debt > 0) {
        double new_debt = debt * rate - r;
        debt = new_debt;
        y++;

        // Защита от бесконечного цикла (теоретически не нужна)
        if (y > 1000000) {
            res.error_flag = 3;
            return res;
        }
    }

    res.can_pay = 1;
    res.years = y;
    return res;
}

// Вывод результата
void output_result(Result r) {
    if (r.can_pay == 1) {
        printf("Предприниматель сможет погасить кредит за %d лет(года).\n", r.years);
    } else {
        printf("Предприниматель НЕ сможет погасить кредит.\n");
    }
}

int main(void) {
    double k, p, r;
    int err = input_data(&k, &p, &r);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный формат ввода.\n");
            return 1;
        case 2:
            printf("Ошибка: k > 0, p >= 0, r >= 0.\n");
            return 1;
        default:
            printf("Неизвестная ошибка ввода.\n");
            return 1;
    }

    Result res = compute(k, p, r);

    switch (res.error_flag) {
        case 0:
            output_result(res);
            break;
        case 3:
            printf("Ошибка: превышено допустимое число итераций.\n");
            break;
        default:
            printf("Неизвестная ошибка вычислений.\n");
            break;
    }

    return 0;
}


#include <stdio.h>
#include <math.h>

// Структура результата
typedef struct {
    int errorFlag;      // 0 — нет ошибок
    double x[200];
    double y1_pos[200];
    double y1_neg[200];
    double y2_pos[200];
    double y2_neg[200];
    int count;
} Table;

// Проверка входных данных
Table inputData(double start, double end, double step) {
    Table t;
    t.errorFlag = 0;
    t.count = 0;

    if (step <= 0) {
        t.errorFlag = 1;
    } else if (start > end) {
        t.errorFlag = 2;
    }

    return t;
}

// Вычисление значений
Table computeSystem(double start, double end, double step) {
    Table t;
    t.errorFlag = 0;
    t.count = 0;

    double x = start;
    int i = 0;

    while (x <= end + 1e-9) {
        if (i >= 200) {
            t.errorFlag = 3;
        } else {
            t.x[i] = x;

            // Эллипс 1: y = ±3*sqrt(1 - x^2/4)
            double expr1 = 1.0 - (x * x) / 4.0;
            if (expr1 >= 0) {
                t.y1_pos[i] = 3.0 * sqrt(expr1);
                t.y1_neg[i] = -3.0 * sqrt(expr1);
            } else {
                t.y1_pos[i] = 0;
                t.y1_neg[i] = 0;
            }

            // Эллипс 2: y = ±sqrt(1 - x^2/9)
            double expr2 = 1.0 - (x * x) / 9.0;
            if (expr2 >= 0) {
                t.y2_pos[i] = sqrt(expr2);
                t.y2_neg[i] = -sqrt(expr2);
            } else {
                t.y2_pos[i] = 0;
                t.y2_neg[i] = 0;
            }

            i++;
        }
        x += step;
    }

    t.count = i;
    return t;
}

// Вывод таблицы
void outputTable(Table t) {
    int i = 0;
    while (i < t.count) {
        printf("x = %.2f | y1+ = %.3f  y1- = %.3f | y2+ = %.3f  y2- = %.3f\n",
               t.x[i], t.y1_pos[i], t.y1_neg[i], t.y2_pos[i], t.y2_neg[i]);
        i++;
    }
}

int main() {
    double start = 0.0;
    double end = 3.0;
    double step = 0.2;

    Table check = inputData(start, end, step);

    if (check.errorFlag != 0) {
        switch (check.errorFlag) {
            case 1: printf("Ошибка: шаг должен быть положительным.\n"); break;
            case 2: printf("Ошибка: начало диапазона больше конца.\n"); break;
            default: printf("Неизвестная ошибка ввода.\n");
        }
        return 0;
    }

    Table result = computeSystem(start, end, step);

    if (result.errorFlag != 0) {
        switch (result.errorFlag) {
            case 3: printf("Ошибка: слишком много точек.\n"); break;
            default: printf("Неизвестная ошибка вычислений.\n");
        }
        return 0;
    }

    outputTable(result);

    return 0;
}

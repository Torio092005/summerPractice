#include <stdio.h>
#include <math.h>

// Структура результата
typedef struct {
    int errorFlag;      // 0 — нет ошибок
    double x[200];
    double y[200];
    int count;
} Table;

// Ввод данных
Table inputData(double start, double end, double step) {
    Table t;
    t.errorFlag = 0;
    t.count = 0;

    if (step <= 0) {
        t.errorFlag = 1; // неверный шаг
    } else if (start > end) {
        t.errorFlag = 2; // неверный диапазон
    }

    return t;
}

// Парабола 1: y^2 = 9x
Table computeParabola1(double start, double end, double step) {
    Table t;
    t.errorFlag = 0;
    t.count = 0;

    double x = start;
    int i = 0;

    while (x <= end + 1e-9) {
        if (i >= 200) {
            t.errorFlag = 3; // слишком много точек
        } else {
            t.x[i] = x;
            t.y[i] = (x >= 0) ? 3.0 * sqrt(x) : 0; // только правая ветвь
            i++;
        }
        x += step;
    }

    t.count = i;
    return t;
}

// Парабола 2: y = -x^2
Table computeParabola2(double start, double end, double step) {
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
            t.y[i] = -x * x;
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
        printf("x = %.2f   y = %.2f\n", t.x[i], t.y[i]);
        i++;
    }
}

int main() {
    double start = -3.0;
    double end = 3.0;
    double step = 0.25;

    Table check = inputData(start, end, step);

    if (check.errorFlag != 0) {
        switch (check.errorFlag) {
            case 1: printf("Ошибка: шаг должен быть положительным.\n"); break;
            case 2: printf("Ошибка: начало диапазона больше конца.\n"); break;
            default: printf("Неизвестная ошибка ввода.\n");
        }
        return 0;
    }

    printf("Парабола 1: y^2 = 9x\n");
    Table p1 = computeParabola1(start, end, step);

    if (p1.errorFlag != 0) {
        switch (p1.errorFlag) {
            case 3: printf("Ошибка: слишком много точек.\n"); break;
            default: printf("Неизвестная ошибка вычислений.\n");
        }
        return 0;
    }

    outputTable(p1);

    printf("\nПарабола 2: y = -x^2\n");
    Table p2 = computeParabola2(start, end, step);

    if (p2.errorFlag != 0) {
        switch (p2.errorFlag) {
            case 3: printf("Ошибка: слишком много точек.\n"); break;
            default: printf("Неизвестная ошибка вычислений.\n");
        }
        return 0;
    }

    outputTable(p2);

    return 0;
}


#include <stdio.h>

// Структура результата
typedef struct {
    int errorFlag;      // 0 — нет ошибок
    double x[300];
    double y[300];
    double z[300];
    int count;
} Table;

// Проверка входных данных
Table inputData(double xs, double xe, double dx,
                double ys, double ye, double dy) {
    Table t;
    t.errorFlag = 0;
    t.count = 0;

    if (dx <= 0 || dy <= 0) {
        t.errorFlag = 1; // неверный шаг
    } else if (xs > xe || ys > ye) {
        t.errorFlag = 2; // неверный диапазон
    }

    return t;
}

// Вычисление точек плоскости
Table computePlane(double xs, double xe, double dx,
                   double ys, double ye, double dy) {
    Table t;
    t.errorFlag = 0;
    t.count = 0;

    double zValue = 4.0;
    int i = 0;

    double x = xs;
    while (x <= xe + 1e-9) {

        double y = ys;
        while (y <= ye + 1e-9) {

            if (i >= 300) {
                t.errorFlag = 3; // слишком много точек
            } else {
                t.x[i] = x;
                t.y[i] = y;
                t.z[i] = zValue;
                i++;
            }

            y += dy;
        }

        x += dx;
    }

    t.count = i;
    return t;
}

// Вывод таблицы
void outputTable(Table t) {
    int i = 0;
    while (i < t.count) {
        printf("x = %.2f   y = %.2f   z = %.2f\n",
               t.x[i], t.y[i], t.z[i]);
        i++;
    }
}

int main() {
    double xs = 0.0, xe = 8.0, dx = 0.5;
    double ys = 0.0, ye = 8.0, dy = 1.0;

    Table check = inputData(xs, xe, dx, ys, ye, dy);

    if (check.errorFlag != 0) {
        switch (check.errorFlag) {
            case 1: printf("Ошибка: шаг должен быть положительным.\n"); break;
            case 2: printf("Ошибка: начало диапазона больше конца.\n"); break;
            default: printf("Неизвестная ошибка ввода.\n");
        }
        return 0;
    }

    Table result = computePlane(xs, xe, dx, ys, ye, dy);

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


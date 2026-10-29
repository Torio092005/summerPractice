#include <stdio.h>

// Структура для передачи результата и флага ошибки
typedef struct {
    int errorFlag;   /* 0 — всё хорошо, 1 — ошибка */
    double xValues[100];
    double yValues[100];
    int count;
} LineResult;

// Функция ввода
LineResult inputData(double start, double end, double step) {
    LineResult result;
    result.errorFlag = 0;
    result.count = 0;

    // Проверка корректности диапазона
    if (step <= 0) {
        result.errorFlag = 1; // ошибка шага
    } else if (start > end) {
        result.errorFlag = 2; // ошибка диапазона
    }

    return result;
}

// Функция вычисления
LineResult computeLine(double start, double end, double step) {
    LineResult result;
    result.errorFlag = 0;
    result.count = 0;

    double k = 1.5; // Угловой коэффициент прямой y = 1.5x
    double x = start;

    int i = 0;
    while (x <= end + 1e-9) { // учёт погрешности сравнения
        if (i >= 100) {
            result.errorFlag = 3; // слишком много точек
        } else {
            result.xValues[i] = x;
            result.yValues[i] = k * x;
            i++;
        }
        x += step;
    }

    result.count = i;
    return result;
}

// Функция вывода
void outputResult(LineResult data) {
    int i = 0;
    while (i < data.count) {
        printf("x = %.2f   y = %.2f\n", data.xValues[i], data.yValues[i]);
        i++;
    }
}

int main() {
    double start = -1.0;
    double end = 4.0;
    double step = 0.25;

    LineResult check = inputData(start, end, step);

    if (check.errorFlag != 0) {
        switch (check.errorFlag) {
            case 1:
                printf("Ошибка: шаг должен быть положительным.\n");
                break;
            case 2:
                printf("Ошибка: начало диапазона больше конца.\n");
                break;
            default:
                printf("Неизвестная ошибка ввода.\n");
        }
        return 0;
    }

    LineResult result = computeLine(start, end, step);

    if (result.errorFlag != 0) {
        switch (result.errorFlag) {
            case 3:
                printf("Ошибка: слишком много точек для хранения.\n");
                break;
            default:
                printf("Неизвестная ошибка вычислений.\n");
        }
        return 0;
    }

    outputResult(result);

    return 0;
}

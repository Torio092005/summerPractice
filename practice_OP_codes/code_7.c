#include <stdio.h>

#define MAXT 10000

// Структура результата
typedef struct {
    int error_flag;
} Result;

// Проверка, является ли число простым
int is_prime(int x) {
    int flag = 1;

    if (x < 2) {
        flag = 0;
    }

    int i = 2;
    while (i * i <= x && flag == 1) {
        if (x % i == 0) {
            flag = 0;
        }
        i++;
    }

    return flag;
}

// Ввод t
int input_t(int *t) {
    int flag = 0;
    int tt;

    printf("Введите t: ");
    if (scanf("%d", &tt) != 1) {
        flag = 1;
    } else {flag = 0};

    if (flag == 0) {
        if (tt <= 0 || tt > MAXT) {
            flag = 2;
        } else {flag = 0};
    }

    if (flag == 0) {
        *t = tt;
    }

    return flag;
}

// Генерация первых t простых чисел
Result generate_primes(int t, int primes[MAXT]) {
    Result r;
    r.error_flag = 0;

    int count = 0;
    int x = 2;

    while (count < t) {
        if (is_prime(x)) {
            primes[count] = x;
            count++;
        }
        x++;
    }

    return r;
}

// Вывод таблицы простых чисел
void output_primes(int t, int primes[MAXT]) {
    int i = 0;
    printf("Первые %d простых чисел:\n", t);
    while (i < t) {
        printf("%d ", primes[i]);
        i++;
    }
    printf("\n");
}

// Основная функция
int main(void) {
    int t;
    int primes[MAXT];

    int err = input_t(&t);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный формат ввода.\n");
            return 1;
        case 2:
            printf("Ошибка: t должно быть в диапазоне 1..%d.\n", MAXT);
            return 1;
        default:
            printf("Неизвестная ошибка ввода.\n");
            return 1;
    }

    Result r = generate_primes(t, primes);

    switch (r.error_flag) {
        case 0:
            output_primes(t, primes);
            break;
        default:
            printf("Неизвестная ошибка вычислений.\n");
            break;
    }

    return 0;
}


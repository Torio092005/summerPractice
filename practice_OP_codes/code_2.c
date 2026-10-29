#include <stdio.h>

/*
Структура результата проверки.
error_flag = 0  -> ошибок нет
error_flag != 0 -> ошибка, код передаётся в main()
*/
typedef struct {
    int inside;      // 1 — треугольник внутри области пересечения
    int error_flag;  // код ошибки
} Result;

// Проверка, лежит ли точка (x,y) внутри обоих кругов
int point_in_intersection(double x, double y,
                          double a1, double b1, double r1,
                          double a2, double b2, double r2)
{
    int flag = 0;
    double dx1 = x - a1;
    double dy1 = y - b1;
    double dx2 = x - a2;
    double dy2 = y - b2;

    double d1 = dx1 * dx1 + dy1 * dy1;
    double d2 = dx2 * dx2 + dy2 * dy2;

    if (d1 > r1 * r1) {
        flag = 1; // вне первого круга
    }

    if (flag == 0) {
        if (d2 > r2 * r2) {
            flag = 1; // вне второго круга
        }
    }

    return flag == 0;
}

/*
Функция ввода данных.
Проверяет корректность: радиусы > 0
*/
int input_data(double *ax, double *ay, double *bx, double *by,
               double *cx, double *cy,
               double *a1, double *b1, double *r1,
               double *a2, double *b2, double *r2)
{
    int flag = 0;

    double t_ax, t_ay, t_bx, t_by, t_cx, t_cy;
    double t_a1, t_b1, t_r1, t_a2, t_b2, t_r2;

    printf("Введите координаты A(x y), B(x y), C(x y): ");
    if (scanf("%lf %lf %lf %lf %lf %lf",
              &t_ax, &t_ay, &t_bx, &t_by, &t_cx, &t_cy) != 6) {
        flag = 1;
    }

    if (flag == 0) {
        printf("Введите параметры первого круга (a1 b1 r1): ");
        if (scanf("%lf %lf %lf", &t_a1, &t_b1, &t_r1) != 3) {
            flag = 1;
        }
    }

    if (flag == 0) {
        printf("Введите параметры второго круга (a2 b2 r2): ");
        if (scanf("%lf %lf %lf", &t_a2, &t_b2, &t_r2) != 3) {
            flag = 1;
        }
    }

    if (flag == 0) {
        if (t_r1 <= 0 || t_r2 <= 0) {
            flag = 2; // радиусы должны быть положительными
        }
    }

    if (flag == 0) {
        *ax = t_ax; *ay = t_ay;
        *bx = t_bx; *by = t_by;
        *cx = t_cx; *cy = t_cy;
        *a1 = t_a1; *b1 = t_b1; *r1 = t_r1;
        *a2 = t_a2; *b2 = t_b2; *r2 = t_r2;
    }

    return flag;
}

// Функция проверки треугольника
Result check_triangle(double ax, double ay,
                      double bx, double by,
                      double cx, double cy,
                      double a1, double b1, double r1,
                      double a2, double b2, double r2)
{
    Result r;
    r.error_flag = 0;
    r.inside = 0;

    int inA = point_in_intersection(ax, ay, a1, b1, r1, a2, b2, r2);
    int inB = point_in_intersection(bx, by, a1, b1, r1, a2, b2, r2);
    int inC = point_in_intersection(cx, cy, a1, b1, r1, a2, b2, r2);

    if (inA && inB && inC) {
        r.inside = 1;
    }

    return r;
}

// Вывод результата
void output_result(Result r) {
    if (r.inside == 1) {
        printf("Треугольник полностью лежит в области пересечения кругов.\n");
    } else {
        printf("Треугольник не лежит в области пересечения кругов.\n");
    }
}

// Основная функция
int main(void) {
    double ax, ay, bx, by, cx, cy;
    double a1, b1, r1, a2, b2, r2;

    int err = input_data(&ax, &ay, &bx, &by, &cx, &cy,
                         &a1, &b1, &r1, &a2, &b2, &r2);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный формат ввода.\n");
            return 1;
        case 2:
            printf("Ошибка: радиусы должны быть положительными.\n");
            return 1;
        default:
            printf("Неизвестная ошибка ввода.\n");
            return 1;
    }

    Result r = check_triangle(ax, ay, bx, by, cx, cy,
                              a1, b1, r1, a2, b2, r2);

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


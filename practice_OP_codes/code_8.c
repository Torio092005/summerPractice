#include <stdio.h>
#include <math.h>

// Структура результата
typedef struct {
    double dist;
    int error_flag;
} Result;

// Ввод координат
int input_data(double *px, double *py,
               double *ax, double *ay,
               double *bx, double *by,
               double *cx, double *cy)
{
    int flag = 0;

    printf("Введите координаты точки P(x y): ");
    if (scanf("%lf %lf", px, py) != 2) {
        flag = 1;
    }

    if (flag == 0) {
        printf("Введите координаты A(x y), B(x y), C(x y): ");
        if (scanf("%lf %lf %lf %lf %lf %lf",
                  ax, ay, bx, by, cx, cy) != 6) {
            flag = 1;
        }
    }

    return flag;
}

// Скалярное произведение
double dot(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}

// Квадрат длины вектора
double norm2(double x, double y) {
    return x * x + y * y;
}

/*
Расстояние от точки P до отрезка AB
(если проекция вне отрезка — возвращаем расстояние до ближайшей вершины)
*/
double dist_point_segment(double px, double py,
                          double ax, double ay,
                          double bx, double by)
{
    double vx = bx - ax;
    double vy = by - ay;
    double wx = px - ax;
    double wy = py - ay;

    double c1 = dot(wx, wy, vx, vy);
    double c2;
    double dist;

    if (c1 <= 0) {
        dist = sqrt(norm2(px - ax, py - ay));
    }
    else {
        c2 = dot(vx, vy, vx, vy);

        if (c2 <= c1) {
            dist = sqrt(norm2(px - bx, py - by));
        }
        else {
            double t = c1 / c2;
            double projx = ax + t * vx;
            double projy = ay + t * vy;

            dist = sqrt(norm2(px - projx, py - projy));
        }
    }

    return dist;
}

// Основная функция вычисления расстояния
Result compute_distance(double px, double py,
                        double ax, double ay,
                        double bx, double by,
                        double cx, double cy)
{
    Result r;
    r.error_flag = 0;
    r.dist = 0.0;

    double d1 = dist_point_segment(px, py, ax, ay, bx, by);
    double d2 = dist_point_segment(px, py, bx, by, cx, cy);
    double d3 = dist_point_segment(px, py, cx, cy, ax, ay);

    double min = d1;
    if (d2 < min) {
        min = d2;
    }
    if (d3 < min) {
        min = d3;
    }

    r.dist = min;
    return r;
}

// Вывод результата
void output_result(Result r) {
    printf("Расстояние от точки до треугольника: %.6f\n", r.dist);
}

int main(void) {
    double px, py, ax, ay, bx, by, cx, cy;

    int err = input_data(&px, &py, &ax, &ay, &bx, &by, &cx, &cy);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный формат ввода.\n");
            return 1;
        default:
            printf("Неизвестная ошибка ввода.\n");
            return 1;
    }

    Result r = compute_distance(px, py, ax, ay, bx, by, cx, cy);

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


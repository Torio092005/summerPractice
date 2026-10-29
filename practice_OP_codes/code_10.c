#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTEXT 5000
#define MAXLINE 60

// Структура результата
typedef struct {
    int error_flag;
} Result;

// Ввод текста целиком (до пустой строки)
int input_text(char *buf) {
    int flag = 0;

    printf("Введите текст (окончание — пустая строка):\n");

    buf[0] = '\0';
    char line[256];

    int first = 1;
    int done = 0;

    while (done == 0 && flag == 0) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            flag = 1;
        }

        if (flag == 0) {
            if (strcmp(line, "\n") == 0) {
                done = 1;
            } else {
                if (first == 1) {
                    strcpy(buf, line);
                    first = 0;
                } else {
                    strcat(buf, line);
                }
            }
        }
    }

    return flag;
}

// Удаление следующего слова после позиции i
int delete_next_word(char *s, int i) {
    int k = i;

    // Пропускаем пробелы
    while (s[k] == ' ' || s[k] == '\t') {
        k++;
    }

    // Пропускаем буквы слова
    while (s[k] != '\0' && s[k] != ' ' && s[k] != '\t') {
        k++;
    }

    // Сдвигаем строку влево
    int p = i;
    while (s[k] != '\0') {
        s[p] = s[k];
        p++;
        k++;
    }
    s[p] = '\0';

    return 0;
}

// Удаление следующей фразы (до точки)
int delete_next_phrase(char *s, int i) {
    int k = i;

    // Пропускаем пробелы
    while (s[k] == ' ' || s[k] == '\t') {
        k++;
    }

    // Идём до точки
    while (s[k] != '\0' && s[k] != '.') {
        k++;
    }

    if (s[k] == '.') {
        k++;
    }

    // Сдвигаем строку
    int p = i;
    while (s[k] != '\0') {
        s[p] = s[k];
        p++;
        k++;
    }
    s[p] = '\0';

    return 0;
}

// Основная корректировка текста
Result process_text(char *s) {
    Result r;
    r.error_flag = 0;

    int i = 0;
    int redline = 0;

    while (s[i] != '\0') {

        // Если встретили $, включаем красную строку
        if (s[i] == '$') {
            redline = 1;

            // Удаляем сам символ $
            int k = i + 1;
            int p = i;
            while (s[k] != '\0') {
                s[p] = s[k];
                p++;
                k++;
            }
            s[p] = '\0';
        }

        // Если встретили # — удаляем следующее слово
        if (s[i] == '#') {
            delete_next_word(s, i);

            // Удаляем сам символ #
            int k = i + 1;
            int p = i;
            while (s[k] != '\0') {
                s[p] = s[k];
                p++;
                k++;
            }
            s[p] = '\0';
        }

        // Если встретили @ — удаляем следующую фразу
        if (s[i] == '@') {
            delete_next_phrase(s, i);

            // Удаляем сам символ @
            int k = i + 1;
            int p = i;
            while (s[k] != '\0') {
                s[p] = s[k];
                p++;
                k++;
            }
            s[p] = '\0';
        }

        i++;
    }

    // Добавляем красную строку, если была команда $
    if (redline == 1) {
        char tmp[MAXTEXT];
        strcpy(tmp, s);
        s[0] = ' ';
        s[1] = ' ';
        s[2] = ' ';
        s[3] = ' ';
        s[4] = '\0';
        strcat(s, tmp);
    }

    return r;
}

// Вывод текста 60‑символьными строками
void output_formatted(char *s) {
    int len = strlen(s);
    int i = 0;

    while (i < len) {
        int j = 0;
        while (j < MAXLINE && i + j < len) {
            putchar(s[i + j]);
            j++;
        }
        putchar('\n');
        i += MAXLINE;
    }
}

int main(void) {
    char text[MAXTEXT];

    int err = input_text(text);

    switch (err) {
        case 0:
            break;
        case 1:
            printf("Ошибка: некорректный ввод текста.\n");
            return 1;
        default:
            printf("Неизвестная ошибка ввода.\n");
            return 1;
    }

    Result r = process_text(text);

    switch (r.error_flag) {
        case 0:
            output_formatted(text);
            break;
        default:
            printf("Неизвестная ошибка обработки.\n");
            break;
    }

    return 0;
}


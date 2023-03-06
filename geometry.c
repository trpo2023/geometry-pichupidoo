#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 25

typedef struct point {
    double x;
    double y;
} Point;

typedef struct circle {
    Point point;
    double radius;
    double perimetr;
    double area;
} Circle;

enum Errors {
    ER_NAME,
    ER_NOT_DOUBLE,
    ER_BACK_BRACE,
    ER_UNEXPECT_TOKEN,
    ER_EXPECT_COMMA,
    ER_UNEXPECT_COMMA,
};
void print_error(int column, int status)
{
    for (int i = 0; i < column; i++) {
        putchar(' ');
    }
    printf("^\n");
    switch (status) {
    case ER_NAME:
        printf("Error at column %d: expected "
               "'circle'\n",
               column);
        break;
    case ER_NOT_DOUBLE:
        printf("Error at column %d: expected "
               "'<double>'\n",
               column);
        break;
    case ER_BACK_BRACE:
        printf("Error at column %d: expected ')'\n",
               column);
        break;
    case ER_UNEXPECT_TOKEN:
        printf("Error at column %d: expected "
               "token\n",
               column);
        break;
    case ER_EXPECT_COMMA:
        printf("Error at column %d: expected ','\n",
                column);
        break;
    case ER_UNEXPECT_COMMA:
        printf("Error at column %d: expected ','\n",
               column);
    }
}
void del_space(int* column, FILE* file)
{
    char ch;
    while ((ch = getc(file)) == ' ') {
        *column += 1;
        continue;
    }
    if (ch != ' ')
        ungetc(ch, file);
}

double get_number(int* column, FILE* file)
{
    char temp[20];
    char ch;
    int point_count = 0;
    int i = 0;
    int minus_count = 0;

    del_space(column, file);

    while ((ch = getc(file)) != ' ') {
        temp[i] = ch;

        if (temp[i] == '.') {
            point_count++;
            if (point_count > 1) {
                print_error(*column + i + 1, ER_NOT_DOUBLE);
                exit(EXIT_FAILURE);
            }
        }

        if (temp[i] == '-') {
            minus_count++;
            if (minus_count > 1) {
                print_error(*column + i + 1, ER_NOT_DOUBLE);
                exit(EXIT_FAILURE);
            }
        }

        if (temp[i] == ')') {
            ungetc(temp[i], file);
            i++;
            break;
        }

        if (temp[i] == ',') {
            ungetc(temp[i], file);
            break;
        }

        if (temp[i] == '(') {
            i++;
            print_error(*column + i, ER_BACK_BRACE);
            exit(EXIT_FAILURE);
        }

        if (!isdigit(temp[i]) && temp[i] != '.' && temp[i] != '-') {
            i++;
            print_error(*column + i, ER_NOT_DOUBLE);
            exit(EXIT_FAILURE);
        }

        i++;
    }
    del_space(column, file);
    *column += i + 1;
    char* eptr;
    return strtod(temp, &eptr);
}


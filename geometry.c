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


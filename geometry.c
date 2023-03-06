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

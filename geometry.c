#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 20

typedef struct point {
    double x;
    double y;
} Point;

typedef struct circle {
    Point point;
    double radius;
} Circle;

enum Errors {
    NAME,
    NOT_DOUBLE,
    BACK_BRACE,
    UNEXPECT_TOKEN,
    EXPECT_COMMA,
    UNEXPECT_COMMA,
};

void print_error(int column, int status)
{
    for (int i = 0; i < column; i++) {
        putchar(' ');
    }
    printf("^\n");
    switch (status) {
    case NAME:
        printf("Error at column %d: expected 'circle'\n", column);
        break;
    case NOT_DOUBLE:
        printf("Error at column %d: expected '<double>'\n", column);
        break;
    case BACK_BRACE:
        printf("Error at column %d: expected ')'\n",column);
        break;
    case UNEXPECT_TOKEN:
        printf("Error at column %d: expected token\n", column);
        break;
    case EXPECT_COMMA:
        printf("Error at column %d: expected ','\n", column);
        break;
    case UNEXPECT_COMMA:
        printf("Error at column %d: expected ','\n", column);
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
                print_error(*column + i + 1, NOT_DOUBLE);
                exit(EXIT_FAILURE);
            }
        }

        if (temp[i] == '-') {
            minus_count++;
            if (minus_count > 1) {
                print_error(*column + i + 1, NOT_DOUBLE);
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
            print_error(*column + i, BACK_BRACE);
            exit(EXIT_FAILURE);
        }

        if (!isdigit(temp[i]) && temp[i] != '.' && temp[i] != '-') {
            i++;
            print_error(*column + i, NOT_DOUBLE);
            exit(EXIT_FAILURE);
        }

        i++;
    }
    del_space(column, file);
    *column += i + 1;
    char* eptr;
    return strtod(temp, &eptr);
}

bool expect(char expect, int* column, int status, FILE* file)
{
    char ch;
    if ((ch = getc(file)) == expect) {
        return true;
    } else {
            print_error(*column, status);
            exit(EXIT_FAILURE);
    }
}

bool unexpect(char unexpect, int* column, int status, FILE* file)
{
    char ch;
    if ((ch = getc(file)) == unexpect) {
        print_error(*column, status);
        exit(EXIT_FAILURE);
    }
    ungetc(ch, file);
    return true;
}

void get_point(Point* point, int* column, FILE* file)
{
    point->x = get_number(column, file);
    unexpect(',', column, UNEXPECT_COMMA, file);

    point->y = get_number(column, file);
}

void line_ending(int* column, FILE* file)
{
    char ch;
    while ((ch = getc(file)) != '\n' && ch != EOF) {
        if (ch != ' ') {
            print_error(*column, UNEXPECT_TOKEN);
            exit(EXIT_FAILURE);
        }
        *column += 1;
    }
}

void take_info_circle(Circle* circle, int* column, FILE* file)
{
        get_point(&circle->point, column, file);
        expect(',', column, EXPECT_COMMA, file);

        circle->radius = get_number(column, file);

        expect(')', column, BACK_BRACE, file);

        line_ending(column, file);
}

void show_info_circle(Circle* circle)
{
    printf("circle(%.2f %.2f, %.2f)\n",
           circle->point.x,
           circle->point.y,
           circle->radius);
}

void _stdin(FILE* stdin)
{
    char geom[NAME_SIZE] = {0};
    char ch;
    int column;

    puts("Enter a geometric shape (or q for exit):");
    while ((ch = getc(stdin)) != EOF && ch != 'q') {
        column = 0;
        do {
            if (ch == '(' || ch == ' ') {
                if (strcmp(geom, "circle") == 0) {
                    Circle circle;
                    take_info_circle(&circle, &column, stdin);
                    printf("\nYou have entered: \n");
                    show_info_circle(&circle);
                    break;
                } else {
                    print_error(0, NAME);
                    exit(EXIT_FAILURE);
                }
            }

            if (ch == ')') {
                print_error(column, BACK_BRACE);
                exit(EXIT_FAILURE);
            }

            geom[column++] = ch;

        } while ((ch = getc(stdin)) != '\n');
    }
}

int main()
{
    _stdin(stdin);

    return 0;
}
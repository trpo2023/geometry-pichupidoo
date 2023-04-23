#include <stdio.h>

#include "lexer.h"
#include "parser.h"

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


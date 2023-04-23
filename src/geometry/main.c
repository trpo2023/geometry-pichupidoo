#include <stdio.h>

#include "libgeometry/lexer.h"
#include "libgeometry/parser.h"


int main()
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

    return 0;
}
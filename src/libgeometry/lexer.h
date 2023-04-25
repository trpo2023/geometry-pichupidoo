#pragma once
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>

void print_error(int column, int status);
void get_point(Point* point, int* column, FILE* file);
double get_number(int* column, FILE* file);
void del_space(int* column, FILE* file);
bool expect(char expect, int* column, int status, FILE* file);
bool unexpect(char unexpect, int* column, int status, FILE* file);
void line_ending(int* column, FILE* file);

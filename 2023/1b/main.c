// SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: CC0-1.0

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

const int NO_DIGIT = -1;

bool cstr_equal(const char* cstr, const char* equal_cstr)
{
    if (strlen(cstr) < strlen(equal_cstr))
    {
        return false;
    }
    if (strncmp(cstr, equal_cstr, strlen(equal_cstr)) == 0)
    {
        return true;
    }
    return false;
}

int cstr_get_digit(const char* cstr, size_t length)
{
    if (isdigit(cstr[0]))
    {
        char short_cstr[2] = { cstr[0], '\0'};
        return atoi(short_cstr);
    }
    if (cstr_equal(cstr, "one"))
    {
        return 1;
    }
    if (cstr_equal(cstr, "two"))
    {
        return 2;
    }
    if (cstr_equal(cstr, "three"))
    {
        return 3;
    }
    if (cstr_equal(cstr, "four"))
    {
        return 4;
    }
    if (cstr_equal(cstr, "five"))
    {
        return 5;
    }
    if (cstr_equal(cstr, "six"))
    {
        return 6;
    }
    if (cstr_equal(cstr, "seven"))
    {
        return 7;
    }
    if (cstr_equal(cstr, "eight"))
    {
        return 8;
    }
    if (cstr_equal(cstr, "nine"))
    {
        return 9;
    }
    return NO_DIGIT;
}

int main()
{
    FILE* f = fopen("input", "r");
    if (f == NULL)
    {
        puts("error opening input file");
        exit(EXIT_FAILURE);
    }
    int result = 0;
    size_t capacity = 0;
    ssize_t length = 0;
    char* line = NULL;
    while ((length = getline(&line, &capacity, f)) != -1)
    {
        // first digit
        for (size_t codeunit_i = 0; codeunit_i < length; codeunit_i++)
        {
            int digit = cstr_get_digit(line + codeunit_i, length - codeunit_i);
            if (digit != NO_DIGIT)
            {
                result += digit * 10;
                break;
            }
        }
        // second digit
        for (size_t codeunit_i = length - 1; codeunit_i < length; codeunit_i--)
        {
            int digit = cstr_get_digit(line + codeunit_i, length - codeunit_i);
            if (digit != NO_DIGIT)
            {
                result += digit;
                break;
            }
        }
    }
    if (line != NULL)
    {
        free(line);
    }
    printf("%d\n", result);
    fclose(f);
    f = NULL;
    exit(EXIT_SUCCESS);
}
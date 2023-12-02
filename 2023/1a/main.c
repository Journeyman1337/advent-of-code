// SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: CC0-1.0

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

const int NO_DIGIT = -1;

int cstr_get_digit(char* cstr, size_t length)
{
    if (isdigit(cstr[0]))
    {
        char short_cstr[2] = { cstr[0], '\0'};
        return atoi(short_cstr);
    }
    if (strcmp(cstr, "zero") == 0)
    {
        return 0;
    }
    if (strcmp(cstr, "one") == 0)
    {
        return 1;
    }
    if (strcmp(cstr, "two") == 0)
    {
        return 2;
    }
    if (strcmp(cstr, "three") == 0)
    {
        return 3;
    }
    if (strcmp(cstr, "four") == 0)
    {
        return 4;
    }
    if (strcmp(cstr, "five") == 0)
    {
        return 5;
    }
    if (strcmp(cstr, "six") == 0)
    {
        return 6;
    }
    if (strcmp(cstr, "seven") == 0)
    {
        return 7;
    }
    if (strcmp(cstr, "eight") == 0)
    {
        return 8;
    }
    if (strcmp(cstr, "nine") == 0)
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
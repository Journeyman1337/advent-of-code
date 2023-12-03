// SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: CC0-1.0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

const int RED_MAX = 12;
const int GREEN_MAX = 13;
const int BLUE_MAX = 14;

const char* straft(const char* cstr, char codeunit)
{
    const char codeunit_cstr[] = { codeunit, '\0' };
    return strstr(cstr, codeunit_cstr) + 1;
}

bool strmatch(const char* cstr, const char* equal_cstr)
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

typedef enum
{
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_COUNT
} Color;

typedef struct
{
    int color_counts[COLOR_COUNT];
} color_count_set;

Color get_color(const char** line_it_ptr)
{
    const char* line_it = *line_it_ptr;
    if (strmatch(line_it, "red"))
    {
        line_it += strlen("red");
        *line_it_ptr = line_it;
        return COLOR_RED;
    }
    if (strmatch(line_it, "blue"))
    {
        line_it += strlen("blue");
        *line_it_ptr = line_it;
        return COLOR_BLUE;
    }
    if (strmatch(line_it, "green"))
    {
        line_it += strlen("green");
        *line_it_ptr = line_it;
        return COLOR_GREEN;
    }
    puts("no color");
    exit(EXIT_FAILURE);
}

color_count_set calculate_round_result(const char** line_it_ptr)
{
    const char* line_it = *line_it_ptr;
    // space at start
    line_it++;
    color_count_set result = {};
    while (line_it[0] != ';' && line_it[0] != '\n' && line_it[0] != '\0')
    {
        int count = atoi(line_it);
        while (isdigit(*(++line_it)));
        line_it++;
        Color color = get_color(&line_it);
        result.color_counts[color] = count;
        if (line_it[0] == ',')
        {
            line_it++;
            line_it++; // space
        }
    }
    *line_it_ptr = line_it;
    return result;
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
        color_count_set game_result = {};
        bool possible =  true;
        const char* line_it = line + strlen("Game ");
        const int game_i = atoi(line_it);
        line_it = straft(line_it, ':');
        while (line_it[0] != '\n' && line_it[0] != '\0')
        {
            color_count_set round_result = calculate_round_result(&line_it);
            for (int color_i = 0; color_i < COLOR_COUNT; color_i++)
            {
                if (game_result.color_counts[color_i] < round_result.color_counts[color_i])
                {
                    game_result.color_counts[color_i] = round_result.color_counts[color_i];
                }
            }
        }
        result +=
            game_result.color_counts[COLOR_RED] *
            game_result.color_counts[COLOR_GREEN] *
            game_result.color_counts[COLOR_BLUE];
    }
    if (line != NULL)
    {
        free(line);
        line = NULL;
    }
    printf("%d\n", result);
    fclose(f);
    f = NULL;
    exit(EXIT_SUCCESS);
}
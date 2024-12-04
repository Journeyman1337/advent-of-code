#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void sortList(int* list, size_t count)
{ // bubble sort
    int sorted = 0;
    while (sorted == 0)
    {
        sorted = 1;
        for (size_t i = 0; i < count - 1; i++)
        {
            const size_t next_i = i + 1;
            const int this = list[i];
            const int next = list[next_i];
            if (next < this)
            {
                sorted = 0;
                list[i] = next;
                list[next_i] = this;
            }
        }
    }
}

int main()
{
    FILE* file = fopen("2024_1a_input.txt", "r");
    if (file == NULL)
    {
        printf("error opening file");
        return 1;
    }
    size_t line_count = 0;
    char line[32];
    while (fgets(line, sizeof(line), file))
    {
        line_count++;
    }
    int* const list_a = (int*)malloc(line_count * sizeof(int));
    int* const list_b = (int*)malloc(line_count * sizeof(int));
    rewind(file);
    size_t line_i = 0;
    while (fgets(line, sizeof(line), file))
    {
        int first, second;
        if (sscanf(line, "%d %d", &first, &second))
        {
            list_a[line_i] = first;
            list_b[line_i] = second;
        }
        else
        {
            printf("error parsing line \"%s\"", line);
        }
        line_i++;
    }
    fclose(file);
    sortList(list_a, line_count);
    sortList(list_b, line_count);
    int total_distance = 0;
    for (size_t i = 0; i < line_count; i++)
    {
        int distance =
            MAX(list_a[i], list_b[i]) -
            MIN(list_a[i], list_b[i]);
        total_distance += distance;   
    }
    printf("The total distance is %d.\n", total_distance);
    free(list_a);
    free(list_b);
    return 0;
}
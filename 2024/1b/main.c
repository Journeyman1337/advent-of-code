#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t getHash(int num)
{ // fnv1a http://isthe.com/chongo/tech/comp/fnv/index.html
    uint64_t hash = 14695981039346656037UL;
    for (size_t byte_i = 0; byte_i < sizeof(int); byte_i++)
    {
        hash = hash ^ ((const uint8_t*)&num)[byte_i];
        hash = hash * 1099511628211UL;
    }
    return hash;
}

struct ValueCount
{
    struct ValueCount* next_value_ptr;
    int value;
    int left_count;
    int right_count;
};

const size_t BUCKET_COUNT = 64;

struct ValueCount* getValueCount(int value, struct ValueCount** buckets_ptr)
{
    const uint64_t hash = getHash(value);
    const size_t bucket_i = hash % BUCKET_COUNT;
    struct ValueCount** bucket_ptr = &buckets_ptr[bucket_i];
    struct ValueCount* value_ptr = *bucket_ptr;
    if (value_ptr == NULL)
    {
        value_ptr = (struct ValueCount*)malloc(sizeof(struct ValueCount));
        value_ptr->value = value;
        value_ptr->left_count = 0;
        value_ptr->right_count = 0;
        value_ptr->next_value_ptr = NULL;
        *bucket_ptr = value_ptr;
        return value_ptr;
    }
    while (1)
    {
        if (value_ptr->value == value)
        {
            break;
        }
        if (value_ptr->next_value_ptr == NULL)
        {
            value_ptr->next_value_ptr = (struct ValueCount*)malloc(sizeof(struct ValueCount));
            value_ptr = value_ptr->next_value_ptr;
            value_ptr->value = value;
            value_ptr->left_count = 0;
            value_ptr->right_count = 0;
            value_ptr->next_value_ptr = NULL;
            break;
        }
        value_ptr = value_ptr->next_value_ptr;
    }
    return value_ptr;
}

int main()
{
    FILE* file = fopen("2024_1b_input.txt", "r");
    if (file == NULL)
    {
        printf("error opening file");
        return 1;
    }
    struct ValueCount* buckets_ptr[BUCKET_COUNT];
    for (size_t bucket_i = 0; bucket_i < BUCKET_COUNT; bucket_i++)
    {
        buckets_ptr[bucket_i] = NULL; 
    }
    char line[32];
    while (fgets(line, sizeof(line), file))
    {
        int first, second;
        if (sscanf(line, "%d %d", &first, &second))
        {
            struct ValueCount* first_count_ptr = getValueCount(first, buckets_ptr);
            first_count_ptr->left_count++;
            struct ValueCount* second_count_ptr = getValueCount(second, buckets_ptr);
            second_count_ptr->right_count++;
        }
        else
        {
            printf("error parsing line \"%s\"", line);
        }
    }
    int total = 0;
    for (size_t bucket_i = 0; bucket_i < BUCKET_COUNT; bucket_i++)
    {
        struct ValueCount* value_ptr = buckets_ptr[bucket_i];
        while (value_ptr != NULL)
        {
            total += value_ptr->left_count * value_ptr->right_count * value_ptr->value;
            value_ptr = value_ptr->next_value_ptr;
        }
    }
    printf("the total is %d\n", total);
    fclose(file);
    return 0;
}
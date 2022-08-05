#include "fdf.h"

void    ft_freearr(void **arr)
{
    int i;
    
    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

void    ft_exit(void **arr1, void *arr2)
{
    if (arr1)
        ft_freearr(arr1);
    if (arr2)
        free(arr2);
    exit(0);
}
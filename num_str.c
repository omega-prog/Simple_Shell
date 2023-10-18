#include "shell.h"

/**
 * intToString - convert an integer to a string
 * @n: the number
 * Return: stringized number
 */

char *intToString(int n)
{
    int length, j, k, digit1, tmp2, i = 0;
    unsigned int num;
    char *nums = customMalloc(numberLength((n > 0) ? n : -1 * n) + 2);

    if (!nums)
        return (NULL);
    if (n < 0)
        n *= -1, *(nums + i) = '-', i++;
    num = n, length = numberLength(num), j = length - 1;
    if (num == 0)
        nums[i] = 48, i++;
    else
    {
        while (j >= 0)
        {
            if (num % powerOf(10, j) == 0 && j != 0)
            {
                nums[i] = (48 + num / powerOf(10, j)), i++;
                for (k = j; k > 0; k--)
                    nums[i] = 48, i++;
                j = -1;
            }
            else
            {
                digit1 = num / powerOf(10, j);
                nums[i] = digit1 + 48, i++;

                tmp2 = num;
                num -= powerOf(10, j) * digit1;
                if (numberLength(tmp2) - numberLength(num) == 2)
                    nums[i] = 48, i++, j--;
                j--;
            }
        }
    }
    return (nums);
}

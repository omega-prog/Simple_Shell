#include "shell.h"

/**
 * numberToString - convert a number to a string
 * @n: the number
 * Return: the string representation of the number
 */

char *numberToString(int n)
{
    int length, j, k, digit1, tmp2, i = 0;
    unsigned int num;
    char *nums = _malloc(num_len((n > 0) ? n : -1 * n) + 2);

    if (!nums)
        return (NULL);

    if (n < 0) {
        n *= -1;
        nums[i] = '-';
        i++;
    }

    num = n;
    length = num_len(num);
    j = length - 1;

    if (num == 0) {
        nums[i] = '0';
        i++;
    } else {
        while (j >= 0) {
            if (num % pow_b(10, j) == 0 && j != 0) {
                nums[i] = '0' + num / pow_b(10, j);
                i++;
                for (k = j; k > 0; k--) {
                    nums[i] = '0';
                    i++;
                }
                j = -1;
            } else {
                digit1 = num / pow_b(10, j);
                nums[i] = '0' + digit1;
                i++;

                tmp2 = num;
                num -= pow_b(10, j) * digit1;
                if (num_len(tmp2) - num_len(num) == 2) {
                    nums[i] = '0';
                    i++;
                    j--;
                }
                j--;
            }
        }
    }
    return (nums);
}

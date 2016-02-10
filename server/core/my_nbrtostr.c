/*
** my_put_nbr.c for my_put_nbr in /home/anzer_r/project/day05/anzer_r/my_put_nbr
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Sat Apr  4 09:11:24 2015 ANZER ryan
** Last update Thu Apr 16 09:10:04 2015 ANZER ryan
*/
#include "header.h"

char *my_nbrtostr(int n)
{
  int pow;
  int last;
  int max;
  int l;
  char *str;
  int f;

  l = my_numlen(n) + ((n < 0)? 1 : 0) + 2;
  if ((str = malloc(sizeof(char) * l)) == NULL)
    return (NULL);

  f = 0;
  my_memset(str, '\0', l - 1);
  if (n < 0)
    str[(f += 1) - 1] = '-';
  max = (n == -2147483648) ? 1 : 0;
  n = (n < 0) ? (n + max) * -1 : n;
  pow = my_pow(my_numlen(n), 10);
  last = 0;
  while (pow >= 1)
    {
      if (pow < 10)
        n = n + max;
      str[(f += 1) - 1] = ((n / pow) - (last * 10)) + 48;
      last = n / pow;
      pow = pow / 10;
    }
  str[l - 1] = '\0';
  my_putstr(str);
  my_putstr("\n");
  return (str);
}

/*
** main.c for main in /home/anzer_r/project/dicowesh/anzer_r/discowesh/core
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Fri Apr 17 10:36:53 2015 ANZER ryan
** Last update Sat Apr 18 13:55:35 2015 ANZER ryan
*/
#include "header.h"

char *getParam(int argc, char **argv, char *param)
{
  int i;

  i = 0;
  while (i < argc)
    {
      if (my_strcmp(argv[i], param) == 0 && i + 1 < argc)
	      {
	        return (argv[i + 1]);
	      }
      i += 1;
    }
  return (NULL);
}

void my_memset(void *buff, int put, size_t size)
{
  size_t i;
  char *mem;

  mem = buff;
  i = 0;
  while (i < size)
    {
      mem[i] = put;
      i++;
    }
}

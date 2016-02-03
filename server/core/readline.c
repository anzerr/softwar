/*
** readline.c for readline in /home/anzer_r/project/dicowesh/anzer_r/discowesh
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Fri Apr 17 12:34:05 2015 ANZER ryan
** Last update Sat Apr 18 13:55:51 2015 ANZER ryan
*/

#include "header.h"

char *readLine()
{
  char buffer[256];
  char *a;
  char *b;
  int part;
  int bSize;
  int out;
  
  bSize = 255;
  part = 1;
  a = NULL;
  while (1)
    {
      my_memset(buffer, 0, 256);
      out = read(0, buffer, bSize);
      if ((b = malloc(sizeof(char) * ((bSize * part) + 1))) == NULL)
	return (NULL);
      my_memset(b, 0, (bSize * part) + 1);
      my_strcat(b, (a != NULL) ? a : "");
      my_strcat(b, buffer);
      b[(bSize * part)] = '\0';
      if (a != NULL) 
	free(a);
      a = b;
      if (out >= bSize)
	part += 1;
      else
	break;
    }
  return (a);
}

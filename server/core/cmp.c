/*
** cmp.c for cmp in /home/anzer_r/project/dicowesh/anzer_r/discowesh
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Fri Apr 17 15:09:33 2015 ANZER ryan
** Last update Fri Apr 17 16:57:02 2015 ANZER ryan
*/
#include "header.h"

int cmpcommand(t_command *node, char *str)
{
  int l;

  l = my_strlen(node->command);
  return (my_strncmp(node->command, str, l));
}

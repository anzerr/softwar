/*
** cmd.c for cmd in /home/anzer_r/project/dicowesh/anzer_r/discowesh/core
**
** Made by ANZER ryan
** Login <anzer_r@etna-alternance.net>
**
** Started on Fri Apr 17 10:53:05 2015 ANZER ryan
** Last update Sat Apr 18 12:23:23 2015 ANZER ryan
*/
#include "header.h"

int auth(t_core *core, char *line)
{
  int l;

  l = my_strlen(line);
  if (l <= 255)
      write(core->sockfd, line, l);
  return (l <= 255);
}

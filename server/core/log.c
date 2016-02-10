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

int initLogs(t_core *core)
{
  core->logHandle = open(core->logPath, O_CREAT | O_WRONLY | O_APPEND);
  my_putstr("logs: ");
  my_putstr(core->logPath);
  my_putstr("\n");
  
  if (core->logHandle < 0) {
    error(core, "error opening file logs disabled\n");
    return (1);
  }
  return (put(core, "starting softwar logs\n"));
}

void closeLogs(t_core *core)
{
  close(core->logHandle);
}

int put(t_core *core, char *str)
{
  if (core->debug)
    my_putstr(str);
  if (core->logHandle >= 0)
    return (write(core->logHandle, str, my_strlen(str)) != my_strlen(str));
  else
    return (1);
}

int error(t_core *core, char *str)
{
  my_putstr(str);
  if (core->logHandle >= 0)
    return (write(core->logHandle, str, my_strlen(str)) != my_strlen(str));
  else
    return (1);
}

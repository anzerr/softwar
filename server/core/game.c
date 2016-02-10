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

void initGameMap(t_core *core)
{
  core->running = 1;
}

void initGameCycle(t_core *core)
{
  pthread_t thread_id;
  
  if (pthread_create(&thread_id, NULL, cycleRun, (void*) core) < 0)
    {
      error(core, "could not create thread\n\0");
    }
}

void *cycleRun(void *base)
{
  t_core *core;

  core = (t_core *)base;
  while (core->running)
    {
      
    }
  return (0);
}

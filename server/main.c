/*
** main.c for main in /home/anzer_r/project/dicowesh/anzer_r/discowesh/core
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Fri Apr 17 10:36:53 2015 ANZER ryan
** Last update Sat Apr 18 13:55:35 2015 ANZER ryan
*/
#include "core/header.h"


t_core *initCore()
{
  t_core *core;
  if ((core = malloc(sizeof(t_core))) == NULL)
    return (NULL);
  core->cmd = NULL;
  initCmd(core);
  return (core);
}

int main(int argc, char **argv)
{
  t_core *core;
  int run;
  char *line;
  
  core = initCore();
  if ((core->sockfd = connectSocket(argc, argv)) >= 0)
    {
      my_putstr("successfully connected.\n");
      run = 1;
      while (run)
	{
	  my_putstr("> ");
	  line = readLine();
	  run = runCmd(line, core);
	  free(line);
	}
      close(core->sockfd);
      core->sockfd = 0;
    }
  
  return (core->sockfd);
}

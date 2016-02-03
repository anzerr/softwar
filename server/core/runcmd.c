
/*
** main.c for main in /home/anzer_r/project/dicowesh/anzer_r/discowesh/core
**
** Made by ANZER ryan
** Login <anzer_r@etna-alternance.net>
**
** Started on Fri Apr 17 10:36:53 2015 ANZER ryan
** Last update Sat Apr 18 13:55:35 2015 ANZER ryan
*/
#include "header.h"

void addCmd(t_list **cmd, char *com, int (*func)())
{
  t_command *tmp;
  t_list *node;
  
  if ((tmp = malloc(sizeof(t_command))) == NULL)
    return;  
  tmp->command = my_strdup(com);
  tmp->func = func;
  node = my_add_list(cmd);
  node->data = tmp;
}


void initCmd(t_core *c)
{
  addCmd(&c->cmd, "/auth", &auth);
  addCmd(&c->cmd, "/list", &auth);
  addCmd(&c->cmd, "/hs", &auth);
  addCmd(&c->cmd, "/psychohistory", &auth);
  addCmd(&c->cmd, "/getstatus", &auth);
  addCmd(&c->cmd, "/me", &auth);
  addCmd(&c->cmd, "/setstatus", &auth);
}

int runCmd(char *line, t_core * core)
{
  t_command *tmp;
  t_list *list;
  int run;
  
  list = core->cmd;
  run = (my_strncmp(line, "/bye", 4) != 0);
  if (run)
    {
      tmp = (t_command*)my_find_list(list, line, &cmpcommand);
      if (tmp != NULL && tmp->func != NULL)
	{
	  if (tmp->func(core, line))
	    {
	      messageSocket(core);
	      return (1);
	    }
	}
    }
  my_putstr((run) ? "/ko\n" : "This isn't brave. It's murder.\n");
  return (run);
}


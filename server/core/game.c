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

void initGame(t_core *core)
{
  t_game *game;
  if ((game = malloc(sizeof(t_game))) == NULL)
    core->running = 0;
  else
    {
      game->maxPlayer = 4;
      game->stat = 0;
      game->countdown = core->countdown;
      core->game = game;
      initGameCycle(core);
    }
}

void initGameCycle(t_core *core)
{
  pthread_t thread_id;

  put(core, "init cycle\n");
  if (pthread_create(&thread_id, NULL, cycleRun, (void*) core) < 0)
    {
      error(core, "could not create thread\n\0");
    }
}

void runLobby(t_core *core)
{
  int c;
  int i;
  t_game *game;
  t_client *client;

  game = core->game;
  if (game->stat == 0)
    {
      c = (i = 0);
      while (i < game->maxPlayer)
	{
	  if (game->players[i] != NULL)
	    c += 1;
	  i += 1;
	}
      if (c == 4)
	{
	  put(core, "found 4 player in lobby starting count down\n");
	  game->countdown = core->countdown;
	  game->stat = 1;
	}
      else
	{
	  while (core->queue != NULL && c < game->maxPlayer)
	    {
	      client = (t_client *)((core->queue)->data);
	      i = 0;
	      while (i < game->maxPlayer)
		{
		  if (game->players[i] == NULL)
		    {
		      c += 1;
		      game->players[i] = client;
		      put(core, "player ");
		      put(core, client->name);
		      put(core, " has been added to queue\n");
		      my_remove_list(&core->queue, client->name, &cmpClientName);
		      break;
		    }
		  i += 1;
		}
	    }
	}
    }
}

void startGame(t_core *core)
{
  t_game *game;
  t_client *client;
  t_list *node;
  int i;
  int c;
  
  game = core->game;
  if (game->stat == 1)
    {
      put(core, "lobby countdown ");
      putnbr(core, game->countdown);
      put(core, "...\n");
      game->countdown += -1;
      if (game->countdown <= 0)
	{
	  put(core, "game is started\n");
	  game->stat = 2;
	}
    }
  if (game->stat == 2)
    {
      i = (c = 0);
      while (i < game->maxPlayer)
	{
	  if ((client = game->players[i]) != NULL)
	    {
	      c += 1;
	      client->action = 2;
	      client->power = client->power - core->powerDrain;
	      put(core, client->name);
	      putnbr(core, client->power);
	      putnbr(core, core->powerDrain);
	      put(core, "\n");
	      if (client->power <= 0)
		{
		  game->players[i] = NULL;
		  put(core, client->name);
		  put(core, " has died put back into queue\n");
		  node = NULL;
		  node = my_add_list(&node);
		  node->data = client;
		  my_add_list_to_list(&core->queue, node);
		}
	    }
	  i += 1;
	}
      if (c == 0)
	game->stat = 0;
    }
}

int clientDisconnect(t_core *core, char *name)
{
  int i;
  t_client *client;
  t_game *game;

  i = 0;
  game = core->game;
  my_remove_list(&core->queue, name, &cmpClientName);
  while (i < game->maxPlayer)
    {
      client = game->players[i];
      if (client != NULL && my_strcmp(client->name, name))
	{
	  game->players[i] = NULL;
	  if (game->stat == 1)
	    {
	      put(core, "game session has been aborted player left mid countdown\n");
	      game->stat = 0;
	    }
	  return (1);
	}
      i += 1;
    }
  return (0);
}

void *cycleRun(void *base)
{
  t_core *core;
  int e;
  struct timespec tim;
  struct timespec tim2;
 
  core = (t_core *)base;
  tim.tv_sec = 0;
  while (core->running)
    {
      tim.tv_nsec = (((core->game)->stat == 1) ? (500 * 1000000) : core->cycle);
      runLobby(core);
      startGame(core);
      if ((e = nanosleep(&tim , &tim2)) < 0)
	{
	  putnbr(core, e);
	  error(core, "Nano sleep system call failed \n");
	}
    }
  return (0);
}

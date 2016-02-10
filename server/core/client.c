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

int cmpClientName(t_client *node, char *str)
{
  return (my_strcmp(node->name, str));
}

char *clientName(t_core *core, t_client *client, int max)
{
  my_strcpy(client->name, "#0x00\0");
  client->name[3] = 48 + (rand() % 9);
  client->name[4] = 48 + (rand() % 9);
  if (my_find_list(core->queue, client->name, &cmpClientName) != NULL && max > 0)
    return (clientName(core, client, max - 1));
  put(core, "set client name ");
  put(core, client->name);
  put(core, "\n");
  return (client->name); 
}

t_client *initClient(t_core *core, int socket)
{
  t_client *client;
  t_list *node;

  if ((client = malloc(sizeof(t_client))) != NULL)
    {
      if ((client->name = malloc(sizeof(char) * 6)) != NULL)
	{
	  clientName(core, client, 5);
	  client->socket = socket;
	  client->power = -1;
	  client->action = -1;
	  node = my_add_list(&core->queue);
	  node->data = client;
	  return (client);
	}
    }
  return (NULL);
}

void sendAll(t_core *core, char *action, char *data)
{
  int i;
  t_game *game;
  
  i = 0;
  game = core->game;
  while (i < game->maxPlayer)
    {
      if (game->players[i] != NULL)
	sendAction((game->players[i])->socket, action, data);
      i += 1;
    }
}

void sendAction(int socket, char *action, char *data)
{
  int l;
  char *send;

  l = my_strlen(action) + my_strlen(data) + 3;
  if ((send = malloc(sizeof(char) * l)) != NULL)
    {
      my_memset(send, '\0', l - 1);
      my_strcat(send, action);
      my_strcat(send, ";");
      my_strcat(send, data);
      my_strcat(send, ";\0");
      write(socket, send, l - 1);
      free(send);
    }
}

void *connectionHandler(void *base)
{
  t_clientSocket *arg;
  int read_size;
  char client_message[2000];
  t_core *core;
  int sock;
  t_client *client;

  arg = (t_clientSocket*)base;
  core = arg->core;
  sock = arg->socket;

  if ((client = initClient(core, sock)) != NULL)
    {
      write(sock, "ping\n", 5);
      while ((read_size = read(sock, client_message, 2000)) > 0)
	{
	  client_message[read_size] = '\0';
	  my_putstr(client_message);
	  write(sock, client_message, strlen(client_message));
	}
      
      if(read_size == 0)
	{
	  put(core, "Client ");
	  put(core, client->name);
	  put(core, " disconnected\n");
	}
      else if(read_size == -1)
	{
	  error(core, "read failed\n");
	}
    }

  put(core, client->name);
  if (clientDisconnect(core, client->name))
    put(core, ((core->game)->stat == 2) ? " has been removed from lobby\n" : " has been removed from active game\n");
  else
    put(core, " not found is lobby or active game\n");
  close(sock);
  return 0;
}

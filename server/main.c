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

t_core *initCore(int argc, char **argv)
{
  t_core *core;
  if ((core = malloc(sizeof(t_core))) == NULL)
    return (NULL);
  core->running = 1;
  core->cycle = (getParam(argc, argv, "--cycle")) ? my_getnbr(getParam(argc, argv, "--cycle")) : 500000;
  core->debug = (getParam(argc, argv, "-v")) ? 1 : 0;
  core->logPath = (getParam(argc, argv, "--log")) ? getParam(argc, argv, "--log") : "softwar.log";
  core->size = (getParam(argc, argv, "--size")) ? my_getnbr(getParam(argc, argv, "--size")) : 8;
  if (initLogs(core) < 0)
    return (NULL);
  initGameMap(core);
  initGameCycle(core);
  return (core);
}

int listenClient(t_core *core)
{
  struct sockaddr_in cliaddr;
  pthread_t thread_id;
  int c;
  int socket;
  t_clientSocket *arg;

  if ((arg = malloc(sizeof(t_clientSocket))) == NULL)
    return (1);
  arg->core = core;
  
  c = sizeof(struct sockaddr_in);
  while (core->running)
    {
      if ((socket = accept(core->sockfd, (struct sockaddr *)&cliaddr, (socklen_t*)&c)) >= 0)
	{
	  if ((arg = malloc(sizeof(t_clientSocket))) == NULL)
	    return (1);
	  arg->core = core;
	  arg->socket = socket;

	  my_putstr("Connection accepted\n");
	  if (pthread_create(&thread_id, NULL, connectionHandler, (void*) arg) < 0)
	    {
	      my_putstr("could not create thread\n");
	      return (1);
	    }
	}
    }  
  return (0);
}

int main(int argc, char **argv)
{
  t_core *core;
  struct sockaddr_in servaddr;
  
  if (getParam(argc, argv, "--port") && (core = initCore(argc, argv)) != NULL)
    {
      if ((core->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
	  my_putstr("ERROR opening socket\n");
	  return (0);
	}
      my_memset(&servaddr, 0, sizeof(servaddr));
      servaddr.sin_family = AF_INET;
      servaddr.sin_addr.s_addr = INADDR_ANY;
      servaddr.sin_port = htons(my_getnbr(getParam(argc, argv, "--port")));
      
      if (bind(core->sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
	  my_putstr("ERROR on binding\n");
	  return (0);
	}
      
      listen(core->sockfd, 5);
      listenClient(core);
      closeLogs(core);
      return (0);
    }
  else
    {
      my_putstr("missing arguments\n");
      return (1);
    }
}

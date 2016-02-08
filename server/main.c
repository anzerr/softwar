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
  core->running = 1;
  return (core);
}

int main(int argc, char **argv)
{
  t_core *core;
  int newsockfd;
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;
  int pid;
  int c;
 
  getParam(argc, argv, "--port"); 
  core = initCore();
  if ((core->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      my_putstr("ERROR opening socket\n");
      return (0);
    }
  my_memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(1337);
  
  if (bind(core->sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
      my_putstr("ERROR on binding\n");
      return (0);
    }
  
  listen(core->sockfd, 5);
  c = sizeof(struct sockaddr_in);
  
  while (core->running)
    {
      if ((newsockfd = accept(core->sockfd, (struct sockaddr *)&cliaddr, (socklen_t*)&c)) < 0)
	      {
	        my_putstr("ERROR on accept\n");
	        core->running = 0;
	        break;
	      }      
      pid = fork();
      
      if (pid < 0)
	      {
	        my_putstr("ERROR on fork");
	        core->running = 0;
	        break;
	      }
      
      if (pid == 0)
	      {
	        close(core->sockfd);
	        my_putstr("something\n");
	        core->running = 0;
	        break;
	      }
      else
	      {
	        close(newsockfd);
	      }
    }

  return (0);
}

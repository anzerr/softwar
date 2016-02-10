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

void *connectionHandler(void *base)
{
  t_clientSocket *arg;
  int read_size;
  char client_message[2000];
  //t_core *core;
  int sock;

  arg = (t_clientSocket*)base;
  //core = arg->core;
  sock = arg->socket;
  
  write(sock, "ping\n", 5);
  while ((read_size = read(sock, client_message, 2000)) > 0)
    {
      client_message[read_size] = '\0';
      my_putstr(client_message);
      write(sock, client_message, strlen(client_message));
    }

  if(read_size == 0)
    {
      my_putstr("Client disconnected\n");
    }
  else if(read_size == -1)
    {
      my_putstr("recv failed\n");
    }

  close(sock);
  return 0;
}

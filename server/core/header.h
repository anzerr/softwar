
/*
** header.h for header in /home/anzer_r/project/dicowesh/anzer_r/discowesh/core
** 
** Made by ANZER ryan
** Login   <anzer_r@etna-alternance.net>
** 
** Started on  Fri Apr 17 10:38:11 2015 ANZER ryan
** Last update Sat Apr 18 12:24:36 2015 ANZER ryan
*/

#ifndef __HEADER__
#define __HEADER__

#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<pthread.h>
#include <string.h>
#include <errno.h>

typedef struct s_list
{
  void *data;
  struct s_list *next;
} t_list;

typedef struct s_core
{
  int sockfd;
  int running;
  int cycle;
  int debug;
  char *logPath;
  int size;
  int logHandle;
} t_core;

typedef struct s_clientSocket
{
  int socket;
  t_core *core;
} t_clientSocket;

int my_strlen(char *str);
void my_put_nbr(int nbr);
void my_putchar(char c);
void my_putstr(char *str);
char *my_strdup(char *str);
int my_strcmp(char *s1, char *s2);
int my_strncmp(char *s1, char *s2, int max);
char *my_strncpy(char *dest, char *src, int n);
char **my_str_to_wordtab(char *str);
int my_getnbr(char *str);
char *my_strcat(char *str1, char *str2);
void my_sort_list(t_list **begin, int (*cmp)());
t_list *my_add_list(t_list **begin);
void my_remove_list(t_list **begin, void *data_ref, int (*cmp)());
void *my_find_list(t_list *begin, void *data_ref, int (*cmp)());

void my_memset(void *buff, int put, size_t size);
char *getParam(int argc, char **argv, char *param);

void *connectionHandler(void *arg);

int initLogs(t_core *core);
void closeLogs(t_core *core);
int error(t_core *core, char *str);
int put(t_core *core, char *str);

void initGameMap(t_core *core);
void initGameCycle(t_core *core);
void *cycleRun(void *base);

#endif

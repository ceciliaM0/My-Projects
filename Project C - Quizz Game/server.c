#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define PORT 2908

extern int errno;

typedef struct thData{
	int idThread; 
	int cl; 
}thData;

static void *treat(void *); 
void raspunde(void *);

int main ()
{
  struct sockaddr_in server;
  struct sockaddr_in from;	
  char *nr;		
  int sd;		
  int pid;
  pthread_t th[100];    
	int i=0;

  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }

  int on=1;
  setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
  
  bzero (&server, sizeof (server));
  bzero (&from, sizeof (from));

    server.sin_family = AF_INET;	
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    server.sin_port = htons (PORT);
    
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Eroare la bind().\n");
      return errno;
    }

  if (listen (sd, 2) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }

  while (1)
    {
      int client;
      thData * td;  
      int length = sizeof (from);

      printf ("[server]Asteptam la portul %d...\n",PORT);
      fflush (stdout);

      if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0)
	{
	  perror ("[server]Eroare la accept().\n");
	  continue;
	}

	td=(struct thData*)malloc(sizeof(struct thData));	
	td->idThread=i++;
	td->cl=client;

	pthread_create(&th[i], NULL, &treat, td);	      
				
	}    
};				
static void *treat(void * arg)
{		
		struct thData tdL; 
		tdL= *((struct thData*)arg);	
		printf ("[thread]- %d - Asteptam mesajul...\n", tdL.idThread);
		fflush (stdout);		 
		pthread_detach(pthread_self());		
		raspunde((struct thData*)arg);
		/* am terminat cu acest client, inchidem conexiunea */
		close ((intptr_t)arg);
		return(NULL);	
  		
};


void raspunde(void *arg)
{
        char *nr, i=0;
	int scor=0;
	struct thData tdL; 
	tdL= *((struct thData*)arg);
	if (read (tdL.cl, &nr,sizeof(char*)) <= 0)
			{
			  printf("[Thread %d]\n",tdL.idThread);
			  perror ("Eroare la read() de la client.\n");
			
			}
	
	printf ("[Thread %d]Mesajul a fost receptionat...%s\n",tdL.idThread, nr);
	{
FILE* fp;
char s[2048];
fp = fopen("file.xml", "r");

if (fp == NULL)
    printf("ERROR");
    else {
int i = 0;
char *p1;
int scor=3;
char a[50];
char p[80];
p[0]='\0';
p[80]='\0';
while (!feof(fp))
{
    fgets(s,2048,fp);
    p1 = strstr(s, "<1>");
    if(p1)
    {
	strncat(p,p1+4,strlen(p1)-10);
        printf("%s\n",p);
        i++;
	if(strcmp(p,nr)==0)
	scor=scor+1;
    }
};
fclose(fp);
}
getchar();
}
		      
		      /*pregatim mesajul de raspuns */
		           
	printf("[Thread %d]Trimitem mesajul inapoi...%d\n",tdL.idThread, scor);
		      
		      
		      /* returnam mesajul clientului */
	 if (write (tdL.cl, &scor, sizeof(int)) <= 0)
		{
		 printf("[Thread %d] ",tdL.idThread);
		 perror ("[Thread]Eroare la write() catre client.\n");
		}
	else
		printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",tdL.idThread);	

}


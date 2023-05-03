#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <time.h>

int n_r=0;

void Meniu()
{
    printf("\n ------------------------* MENIU *----------------------------\n");
    printf("\n |A: Introduceti A pentru a va creea un cont ");
    printf("\n |B: Introduceti B pentru a incepe jocul ");
    printf("\n |D: Introduceti D pentru a afisa datele de logare");
    printf("\n |E: Introduceti E pentru a iesi din joc\n");
    printf("\n Alegeti una dintre variantele de mai sus:\n");
}  
struct jucator
{
    char prenume[20];
    char nume[20];
    int varsta;
    char sex[6];
};

char variante()
{
    char ch;
    while(1)
    {
       
        scanf("%c",&ch);
        if(ch=='A'||ch=='B'||ch=='D'||ch=='E')
        {
        break;
        }
        else
        {
            printf("\n Varianta imposibila!\n");
        }
    }
    return ch;
}
    

int varsta()
{
    int varsta;
    while(1)
    {
        printf("\n Introduceti varsta: ");
        scanf("%d",&varsta);
        if(varsta>=18 && varsta<=90)
        break;
        else
        {
            printf("\n > Varsta trebuie sa fie reala! (intre 18 si 90) ");
        }
    }

    return varsta;
}                                                                       

int sex()
{
    char ch1[6];
    while(1)
    {
        printf("\n Introduceti sexul:");
        scanf("%s",ch1);
        if((strcmp(ch1,"barbat")==0))
        {
            return 0;
        }
        else if((strcmp(ch1,"femeie")==0))
        {
            return 1;
        }
        else{
            printf("\n > Sexul trebuie sa fie de forma 'femeie'/'barbat!'");
        }
    }
}
void start1()
{
FILE* fp;
char buf[2048];
fp = fopen("file.xml", "r");

if (fp == NULL)
    printf("ERROR");
    else {
int i = 0;
char *p1;

while (!feof(fp))
{
    fgets(buf,2048,fp);
    p1 = strstr(buf, "<intrebare1>");
    if(p1)
    {
        printf("%s",buf);
        i++;
    }
};
fclose(fp);
}
getchar();

}
void raspunsuri1()
{
FILE* fp;
char buf[2048];
fp = fopen("file.xml", "r");

if (fp == NULL)
    printf("ERROR");
    else {
int i = 0;
char *p1;

while (!feof(fp))
{
    fgets(buf,2048,fp);
    p1 = strstr(buf, "<a>");
    if(p1)
    {
        printf("%s",buf);
        i++;
    }
};
fclose(fp);
}
getchar();

}
void start2()
{
FILE* fp;
char buf[2048];

fp = fopen("file.xml", "r");

if (fp == NULL)
    printf("ERROR");
    else {
int i = 0;
char *p1;

while (!feof(fp))
{
    fgets(buf,2048,fp);
    p1 = strstr(buf, "<intrebare2>");
    if(p1)
    {
        printf("%s",buf);
        i++;
    }
};
fclose(fp);
}
getchar();

}
void raspunsuri2()
{
FILE* fp;
char buf[2048];
fp = fopen("file.xml", "r");

if (fp == NULL)
    printf("ERROR");
    else {
int i = 0;
char *p1;

while (!feof(fp))
{
    fgets(buf,2048,fp);
    p1 = strstr(buf, "<b>");
    if(p1)
    {
        printf("%s",buf);
        i++;
    }
};
fclose(fp);
}
getchar();

}

void OutputDetalii()
{
    FILE *fp;
    struct jucator c;
    fp=fopen("jucator.txt","r");
    if(fp==NULL)
    {
        printf("\n Eroare deschidere file.");
        exit(1);
    }
    while(fread(&c,sizeof(struct jucator),1,fp))
    printf("\n Nume:%s %s \n Varsta=%d \n Sex=%s",c.prenume,c.nume,c.varsta,c.sex);

    fclose(fp);
}

void adauga()
{
    FILE *fp;
    struct jucator ch;
    if(n_r==0)
    {
        fp=fopen("jucator.txt","w");
        if(fp==NULL)
        {
            printf("\n Eroare deschidere file");
            exit(1);
        }
    }
    else
    {
        fp=fopen("jucator.txt","a");
        if(fp==NULL)
        {
            printf("\n Eroare deschidere file.");
            exit(1);
        }
    }

    printf("\n Introduceti prenumele:");
    scanf("%s",&ch.prenume);
    printf("\n Introduceti numele:");
    scanf("%s",&ch.nume);
    ch.varsta=varsta();
    if(sex())
    {
        strcpy(ch.sex,"Femeie");
        printf("\n Cont creat! \n");
        Meniu();
    }
    else
    {
        strcpy(ch.sex,"Barbat");
        printf("\n Cont creat! \n");
        Meniu();
    }
    fwrite(&ch,sizeof(struct jucator),1,fp);
    fclose(fp); 
}

void timer()
{
unsigned int minute=0;
	unsigned int secunde=0;
	unsigned int milisecunde=0;
	unsigned int timp=0,count_down=0,timp_left=0;

	clock_t startTime,countTime;
	count_down=10;
	startTime=clock(); //start
	timp_left=count_down-secunde;

	while (timp_left>0) 
	{
		countTime=clock(); 
		milisecunde=countTime-startTime;
		secunde=(milisecunde/(CLOCKS_PER_SEC))-(minute*60);
		minute=(milisecunde/(CLOCKS_PER_SEC))/60;
		timp_left=count_down-secunde;
		printf( "\r Mai aveti %d secunde ramase",timp_left,count_down);
	}
	printf( "\n Ai ramas fara timp!\n");


}
/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

int main(int argc, char *argv[])
{
	Meniu();
	char ch;
	while(1)
	{
        ch=variante();
        switch(ch)
        {
            case 'A':
            case 'a':
            adauga();
            n_r++;
            break;

            case 'B':
            case 'b':
            start1();
            raspunsuri1();
            timer();
            
            int sd;
  	    struct sockaddr_in server;
  	    char nr=0;
  	    char buf[10];

  	    if (argc != 3)
    	{
      	printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      	return -1;
    	}

  	port = atoi (argv[2]);

  	if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    	{
      	perror ("Eroare la socket().\n");
      	return errno;
    	}

  	server.sin_family = AF_INET;
  	server.sin_addr.s_addr = inet_addr(argv[1]);
  	server.sin_port = htons (port);
  
  	if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    	{
      perror ("[client]Eroare la connect().\n");
      return errno;
    	}

  	fflush (stdout);
  	read (0, buf, sizeof(buf));
  	nr=atoi(buf);

  	printf("[client] Am citit %c\n",nr);

  	if (write (sd,&nr,sizeof(char)) <= 0)
    	{
      	perror ("[client]Eroare la write() spre server.\n");
      	return errno;
   	 }

  	if (read (sd, &nr,sizeof(char)) < 0)
    	{
     	 perror ("[client]Eroare la read() de la server.\n");
      	return errno;
    	}
	close (sd);
  	start2();
  	raspunsuri2();
  	timer();
  	
  	
            n_r++;
            break;
            
            case 'D':
            case 'd':
            OutputDetalii();
            break;
            
            case 'E':
            case 'e':
             close (sd);
            printf("\n > Thank you for using Customer Management System!\n");
            printf("\n > Good Bye. \n");
            exit(0);
        }
    }

    return 0;
}

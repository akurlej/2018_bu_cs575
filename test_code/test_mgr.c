#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char **argv) {

	int pid[20];
	int i;
	char processid[100];

    for(i=1;i<=10;i++)
    {
    	pid[i]=fork();
        if(pid[i]==0)
    	{
    		sprintf(processid,"%2d",i);
          if (argc > 1){
            execlp("./tests","./tests",processid,argv[1],argv[2],NULL);
          } else {
    		    execlp("./tests","./tests",processid,"100000","1000",NULL);
          }
        }

    }
    for(i=1;i<=10;i++)
    {
    	wait(NULL);
    }
    return 0;
}

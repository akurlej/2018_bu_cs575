#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define LOOP_COUNT_MIN 100
#define LOOP_COUNT_MAX 100000000

int main (int argc, char *argv[])
{
  char *idStr;
  unsigned int	v;
  int	i = 0;
  int	iteration = 1;
  int	loopCount;
  int	maxloops;


  if (argc < 3 || argc > 4)
  {
    printf ("Usage: %s <id> <loop count> [max loops]\n", argv[0]);
    exit (-1);
  }

  v = getpid ();

  idStr = argv[1];

  loopCount = atoi (argv[2]);
  if ((loopCount < LOOP_COUNT_MIN) || (loopCount > LOOP_COUNT_MAX))
  {
    printf ("%s: loop count must be between %d and %d (passed %s)\n", argv[0], LOOP_COUNT_MIN, LOOP_COUNT_MAX, argv[2]);
    exit (-1);
  }
  if (argc == 4)
  {
    maxloops = atoi (argv[3]);
  }
  else
  {
    maxloops = 0;
  }


  struct timeval start,end,wait,curr; //store start, end (turnaround time) and temporary times for calculations
  long long waiting_time=0;
  long long turnaround_time=0;
  gettimeofday(&start,NULL);

  while (1)
  {
    v = (v << 4) - v;
    if (++i == loopCount)
    {
      if (iteration == maxloops)
      {
		 break;
      }

      gettimeofday(&wait,NULL);
      fflush(stdout);
      gettimeofday(&curr,NULL);

      waiting_time=waiting_time+
        1e6*(curr.tv_sec-wait.tv_sec)+(curr.tv_usec-wait.tv_usec);
        //subtime(wait,curr);// add to waiting time

      iteration += 1;
      i = 0;
    }

  }


  gettimeofday(&end,NULL);
  turnaround_time = (1e6*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec));
  printf("Turnaround time = %lld\n",turnaround_time);
  printf("Waiting time = %lld\n",waiting_time);
}

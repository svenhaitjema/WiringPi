#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>


#define	IN_PIN	19	


static volatile int globalCounter = 0 ;


void myInterrupt (void)
{
  ++globalCounter;
  printf(" GPIO state(%d): %d\n", globalCounter, digitalRead(IN_PIN)) ;
}


int main (void) {

  int value;

  if (wiringPiSetupGpio() < 0)  {
    fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
    return 1;
  }
  pinMode(IN_PIN, INPUT);
  pullUpDnControl(IN_PIN, PUD_DOWN);
  printf("input pin bcm(pulldown): %d\n\n", IN_PIN);
  printf("active polling (5 sec.):\n");
  for (int loop=0; loop<20; loop++)  {
    value = digitalRead(IN_PIN);
    printf(" GPIO state: %d\n", value);
    delay(250);
  }

  printf("edge detection (stop with crtl+c):\n", IN_PIN, value);
  if (wiringPiISR (IN_PIN, INT_EDGE_BOTH, &myInterrupt) < 0) {
    fprintf (stderr, "Unable to setup ISR: %s\n", strerror(errno)) ;
    return 1;
  }

  for (;;)  {
      delay (1000);
  }

  return 0;
}

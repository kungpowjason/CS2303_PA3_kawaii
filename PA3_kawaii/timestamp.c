/*
 * timestamp.c
 *
 *  Created on: Feb 6, 2017
 *      Author: ywu
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "timestamp.h"

/** Prints the contents of a timeval struct.
 * @param t Struct to print.
 */
void print_timeval(struct timeval t) {
  printf("Seconds: %ld, microseconds: %ld\n", t.tv_sec, t.tv_usec);
}

/** Calculates difference between two timestamps.
 * Note that this takes structs as parameters and returns a struct;
 * it does not use pointers.
 * @param time1 A time stamp
 * @param time2 another timestamp (assumed same as or later than time 1)
 * @return A timeval struct representing time2 - time1
 */
struct timeval timediff(struct timeval time1, struct timeval time2) {
  struct timeval diff;

  diff.tv_sec = time2.tv_sec - time1.tv_sec;
  diff.tv_usec = time2.tv_usec - time1.tv_usec;

  /* Check if time2 usec was less than time1 usec.
     If so, need to wraparound. */
  if (diff.tv_usec < 0) {
    // It was! So, add 1,000,000 (one whole second) usec to usec
    // and decrease sec by one to match.
    diff.tv_sec--;
    diff.tv_usec += USEC_IN_SEC;
  }

  return diff;
}


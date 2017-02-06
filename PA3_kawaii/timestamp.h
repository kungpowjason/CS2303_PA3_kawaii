/*
 * timestamp.h
 *
 *  Created on: Feb 6, 2017
 *      Author: ywu
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

/* Number of microsenconfds in a second. We need the 'L'
   because this is a long constant. */
#define USEC_IN_SEC (1000000L)

// Prototypes for time functions
void print_timeval(struct timeval t);
struct timeval timediff(struct timeval time1, struct timeval time2);


#endif /* TIMESTAMP_H_ */

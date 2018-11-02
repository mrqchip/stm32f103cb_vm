/*
 * butterworth.h
 *
 *  Created on: May 9, 2016
 *      Author: mirek
 */

#ifndef BUTTERWORTH_H_
#define BUTTERWORTH_H_

#define IIRLength 4

double ButterworthFilter(double sampleIn, uint32_t filter, double *SamplesBuffer);


#endif /* BUTTERWORTH_H_ */

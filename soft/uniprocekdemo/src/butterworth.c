/*
 * butterworth.c
 *
 *  Created on: May 9, 2016
 *      Author: mirek
 */


#include "fifobuf.h"
//#include "nonvolconfig.h"
#include "butterworth.h"
// parametry dla filtru wszechprzepustowego
//
const double IIRbNoFilter[IIRLength] = {
		1,
        0,
        0,
        0
};
const double IIRaNoFilter[IIRLength] = {
		0,
        0,
        0,
        0
};

// parametry dla butter(3,500/1000,'low')
// Butterworth 3rd order, fstop=500Hz, fsample=1000Hz, lowpass
const double IIRb0[IIRLength] = {
		1.666666666666666e-1,
        4.999999999999998e-1,
        4.999999999999998e-1,
        1.666666666666666e-1
};
const double IIRa0[IIRLength] = {
		1,
		-4.163336342344337e-16,
		3.333333333333333e-1,
		-1.850371707708594e-17
};

// parametry dla butter(3,200/1000,'low')
// Butterworth 3rd order, fstop=200Hz, fsample=1000Hz, lowpass
const double IIRb1[IIRLength] = {
	1.809893300751440e-2,
    5.429679902254321e-2,
    5.429679902254321e-2,
    1.809893300751440e-2
};
const double IIRa1[IIRLength] = {
		1,
        -1.760041880343169,
         1.182893262037831,
        -2.780599176345465e-1
};
// parametry dla butter(3,100/1000,'low')
// Butterworth 3rd order, fstop=100Hz, fsample=1000Hz, lowpass
const double IIRb2[IIRLength] = {
		2.898194633721414e-3,
        8.694583901164246e-3,
        8.694583901164246e-3,
        2.898194633721415e-3
};
const double IIRa2[IIRLength] = {
		1,
        -2.374094743709352,
         1.929355669091216,
        -5.320753683120919e-1
};
// parametry dla butter(3,75/1000,'low')
// Butterworth 3rd order, fstop=75Hz, fsample=1000Hz, lowpass
const double IIRb3[IIRLength] = {
		1.309251002054673e-3,
        3.927753006164020e-3,
        3.927753006164020e-3,
        1.309251002054673e-3
};
const double IIRa3[IIRLength] = {
		1,
        -2.529807143712161,
         2.163819746356808,
        -6.235385946282095e-1
};
// parametry dla butter(3,50/1000,'low')
// Butterworth 3rd order, fstop=50Hz, fsample=1000Hz, lowpass
const double IIRb4[IIRLength] = {
		4.165461390757824e-4,
        1.249638417227347e-3,
        1.249638417227347e-3,
        4.165461390757824e-4
};
const double IIRa4[IIRLength] = {
		1,
        -2.686157396548143,
         2.419655110966473,
        -7.301653453057230e-1
};
// parametry dla butter(3,30/1000,'low')
// Butterworth 3rd order, fstop=30Hz, fsample=1000Hz, lowpass
const double IIRb5[IIRLength] = {
		9.544250842374868e-5,
        2.863275252712461e-4,
        2.863275252712461e-4,
        9.544250842374868e-5
};
const double IIRa5[IIRLength] = {
		1,
        -2.811573677324689,
         2.640483492778340,
        -8.281462753862607e-1
};
// parametry dla butter(3,20/1000,'low')
// Butterworth 3rd order, fstop=20Hz, fsample=1000Hz, lowpass
const double IIRb6[IIRLength] = {
		2.914649446572604e-5,
		8.743948339717811e-5,
		8.743948339717811e-5,
		2.914649446572604e-5
};
const double IIRa6[IIRLength] = {
		1,
        -2.874356892677484,
         2.756483195225695,
        -8.818931305924855e-1
};
// parametry dla butter(3,10/1000,'low')
// Butterworth 3rd order, fstop=10Hz, fsample=1000Hz, lowpass
const double IIRb7[IIRLength] = {
		3.756838019758346e-6,
        1.127051405927504e-5,
        1.127051405927504e-5,
        3.756838019758346e-6
};
const double IIRa7[IIRLength] = {
		1,
        -2.937170728449891,
         2.876299723479332,
        -9.390989403252832e-1
};

const double *IIRa[9]={
		IIRaNoFilter,
		IIRa0,
		IIRa1,
		IIRa2,
		IIRa3,
		IIRa4,
		IIRa5,
		IIRa6,
		IIRa7,
};

const double *IIRb[9]={
		IIRbNoFilter,
		IIRb0,
		IIRb1,
		IIRb2,
		IIRb3,
		IIRb4,
		IIRb5,
		IIRb6,
		IIRb7,
};

/**
 * Oblicza wartosc odpowiedzi filtru na podstawie biezacej probki oraz zestawu probek historycznych
 */
double ButterworthFilter(double sampleIn, uint32_t filter, double *SamplesBuffer){
	int i;
	double sumA=0, sumB=0;
	for (i=IIRLength-1; i>0 ; i--){
		SamplesBuffer[i] = SamplesBuffer[i-1];
	}
	for (i=1 ; i<IIRLength; i++){
		sumA = sumA + IIRa[filter][i]*SamplesBuffer[i];
	}
	SamplesBuffer[0]=sampleIn-sumA;
	for (i=0 ; i<IIRLength;i++){
		sumB = sumB + IIRb[filter][i]*SamplesBuffer[i];
	}
	return sumB;
}

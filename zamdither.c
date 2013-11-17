/* zamdither.c  ZamDither LV2 dither plugin
 * Copyright (C) 2013  Damien Zammit
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#define ZAMDITHER_URI "http://zamaudio.com/lv2/zamdither"


typedef enum {
	ZAMDITHER_INPUTL = 0,
	ZAMDITHER_INPUTR = 1,
	ZAMDITHER_OUTPUTL = 2,
	ZAMDITHER_OUTPUTR = 3,

	ZAMDITHER_MODE = 4,
	ZAMDITHER_RESOLUTION = 5,
	ZAMDITHER_ZOOM = 6

} PortIndex;


typedef struct {
	float* inputl;
	float* inputr;
	float* outputl;
	float* outputr;
  
	float srate;
	
	float* fvarg0;
	float* fvarg1;
	float fvarg2;
	float* fvarg3;

	double fvarg4;
	double fvarg5;
	double fvarg6;
	double fvarg7;
	double fvarg8;
	double fvarg9;
	double fvarg10;
	double fvarg11;
	double fvarg12;
	double fvarg13;
	double fvarg14;
	double fvarg15;
	double fvarg16;
	double fvarg17;
	double fvarg18;
	double fvarg19;
	double fvarg20;
	double fvarg21;
	double fvarg22;
	double fvarg23;
	double fvarg24;
	double fvarg25;
	double fvarg26;
	double fvarg27;
	double fvarg28;
	double fvarg29;
	double fvarg30;
	double fvarg31;
	double fvarg32;
	double fvarg33;
	double fvarg34;
	double fvarg35;
	double fvarg36;
	double fvarg37;
	double fvarg38;
	double fvarg39;
	double fvarg40;
	double fvarg41;
	double fvarg42;
	double fvarg43;
	double fvarg44;
	double fvarg45;
	double fvarg46;
	double fvarg47;
	double fvarg48;
	double fvarg49;
	double fvarg50;
	double fvarg51;
	double fvarg52;
	double fvarg53;
	double fvarg54;
	double fvarg55;
	double fvarg56;
	double fvarg57;
	double fvarg58;
	double fvarg59;

	double b_gs1bufB1a;
	double b_gs2bufB1a;
	double b_gs3bufB1a;
	double b_gs4bufB1a;
	double b_gs5bufB1a;
	double b_gs1bufB1b;
	double b_gs2bufB1b;
	double b_gs3bufB1b;
	double b_gs4bufB1b;
	double b_gs5bufB1b;

	double b_gs1bufB2a;
	double b_gs2bufB2a;
	double b_gs3bufB2a;
	double b_gs4bufB2a;
	double b_gs5bufB2a;
	double b_gs1bufB2b;
	double b_gs2bufB2b;
	double b_gs3bufB2b;
	double b_gs4bufB2b;
	double b_gs5bufB2b;

	double b_gs1bufB3a;
	double b_gs2bufB3a;
	double b_gs3bufB3a;
	double b_gs4bufB3a;
	double b_gs5bufB3a;
	double b_gs1bufB3b;
	double b_gs2bufB3b;
	double b_gs3bufB3b;
	double b_gs4bufB3b;
	double b_gs5bufB3b;

	double b_gs1bufB4a;
	double b_gs2bufB4a;
	double b_gs3bufB4a;
	double b_gs4bufB4a;
	double b_gs5bufB4a;
	double b_gs1bufB4b;
	double b_gs2bufB4b;
	double b_gs3bufB4b;
	double b_gs4bufB4b;
	double b_gs5bufB4b;

	double b_lo1;
	double b_lo2;
	double b_hi1;
	double b_hi2;
	
	double b_err1[30];
	double b_err2[30];
	
	double b_noise;

} ZamDITHER;

static LV2_Handle
instantiate(const LV2_Descriptor* descriptor,
            double rate,
            const char* bundle_path,
            const LV2_Feature* const* features)
{
	ZamDITHER* zamdither = (ZamDITHER*)malloc(sizeof(ZamDITHER));
	zamdither->srate = rate;
  
	// Default positions for the faders and knobs
	zamdither->fvarg2 = 0.0;

	zamdither->fvarg4 = 0.2580;
	zamdither->fvarg5 = 0.5020;
	zamdither->fvarg6 = 0.7310;
	zamdither->fvarg7 = 1.0000;
	zamdither->fvarg8 = 0.2500;
	zamdither->fvarg9 = 0.0020;
	zamdither->fvarg10 = 0.1990;
	zamdither->fvarg11 = 0.2000;
	zamdither->fvarg12 = 0.2000;
	zamdither->fvarg13 = 0.0500;
	zamdither->fvarg14 = 0.1000;
	zamdither->fvarg15 = 0.0990;
	zamdither->fvarg16 = 0.1000;
	zamdither->fvarg17 = 0.1990;
	zamdither->fvarg18 = 0.5000;
	zamdither->fvarg19 = 0.2000;
	zamdither->fvarg20 = 0.0000;
	zamdither->fvarg21 = 0.0000;
	zamdither->fvarg22 = 0.0000;
	zamdither->fvarg23 = 0.0000;
	zamdither->fvarg24 = 0.0000;
	zamdither->fvarg25 = 0.0000;
	zamdither->fvarg26 = 0.0000;
	zamdither->fvarg27 = 0.0000;
	zamdither->fvarg28 = 0.0000;
	zamdither->fvarg29 = 0.0000;
	zamdither->fvarg30 = 0.0;
	zamdither->fvarg31 = 0.0;
	zamdither->fvarg32 = 0.0;
	zamdither->fvarg33 = 0.0000;
	zamdither->fvarg34 = 0.0100;
	zamdither->fvarg35 = 0.5010;
	zamdither->fvarg36 = 0.9980;
	zamdither->fvarg37 = 0.1200;
	zamdither->fvarg38 = 0.1150;
	zamdither->fvarg39 = 0.4990;
	zamdither->fvarg40 = 1.0;
	zamdither->fvarg41 = 0.4520;
	zamdither->fvarg42 = 0.5000;
	zamdither->fvarg43 = 0.4930;
	zamdither->fvarg44 = 0.4980;
	zamdither->fvarg45 = 0.5000; //
	zamdither->fvarg46 = 0.9510;
	zamdither->fvarg47 = 0.7550;
	zamdither->fvarg48 = 0.5600;
	zamdither->fvarg49 = 0.2600;
	zamdither->fvarg50 = 1.0000;
	zamdither->fvarg51 = 0.9860;
	zamdither->fvarg52 = 0.9990;
	zamdither->fvarg53 = 0.9990;
	zamdither->fvarg54 = 0.0610;
	zamdither->fvarg55 = 0.1050;
	zamdither->fvarg56 = 1.0;
	zamdither->fvarg57 = 0.3500;
	zamdither->fvarg58 = 0.0;
	zamdither->fvarg59 = 0.0;

	zamdither->b_lo1 = 0;
	zamdither->b_lo2 = 0;
	zamdither->b_hi1 = 0;
	zamdither->b_hi2 = 0;

	int i_cnt = 0;
	while (i_cnt < 30) {
		zamdither->b_err1[i_cnt] = 0;
		zamdither->b_err2[i_cnt] = 0;
	  	i_cnt++;
	}
//eq
	zamdither->b_noise = 0;

	zamdither->b_gs1bufB1a = 0;
	zamdither->b_gs2bufB1a = 0;
	zamdither->b_gs3bufB1a = 0;
	zamdither->b_gs4bufB1a = 0;
	zamdither->b_gs5bufB1a = 0;
	zamdither->b_gs1bufB1b = 0;
	zamdither->b_gs2bufB1b = 0;
	zamdither->b_gs3bufB1b = 0;
	zamdither->b_gs4bufB1b = 0;
	zamdither->b_gs5bufB1b = 0;

	zamdither->b_gs1bufB2a = 0;
	zamdither->b_gs2bufB2a = 0;
	zamdither->b_gs3bufB2a = 0;
	zamdither->b_gs4bufB2a = 0;
	zamdither->b_gs5bufB2a = 0;
	zamdither->b_gs1bufB2b = 0;
	zamdither->b_gs2bufB2b = 0;
	zamdither->b_gs3bufB2b = 0;
	zamdither->b_gs4bufB2b = 0;
	zamdither->b_gs5bufB2b = 0;

	zamdither->b_gs1bufB3a = 0;
	zamdither->b_gs2bufB3a = 0;
	zamdither->b_gs3bufB3a = 0;
	zamdither->b_gs4bufB3a = 0;
	zamdither->b_gs5bufB3a = 0;
	zamdither->b_gs1bufB3b = 0;
	zamdither->b_gs2bufB3b = 0;
	zamdither->b_gs3bufB3b = 0;
	zamdither->b_gs4bufB3b = 0;
	zamdither->b_gs5bufB3b = 0;

	zamdither->b_gs1bufB4a = 0;
	zamdither->b_gs2bufB4a = 0;
	zamdither->b_gs3bufB4a = 0;
	zamdither->b_gs4bufB4a = 0;
	zamdither->b_gs5bufB4a = 0;
	zamdither->b_gs1bufB4b = 0;
	zamdither->b_gs2bufB4b = 0;
	zamdither->b_gs3bufB4b = 0;
	zamdither->b_gs4bufB4b = 0;
	zamdither->b_gs5bufB4b = 0;

	return (LV2_Handle)zamdither;
}

static void
connect_port(LV2_Handle instance,
             uint32_t port,
             void* data)
{
	ZamDITHER* zamdither = (ZamDITHER*)instance;
  
	switch ((PortIndex)port) {
	case ZAMDITHER_INPUTL:
		zamdither->inputl = (float*)data;
  	break;
	case ZAMDITHER_INPUTR:
		zamdither->inputr = (float*)data;
  	break;
	case ZAMDITHER_OUTPUTL:
		zamdither->outputl = (float*)data;
  	break;
	case ZAMDITHER_OUTPUTR:
		zamdither->outputr = (float*)data;
  	break;
	case ZAMDITHER_MODE:
		zamdither->fvarg0 = (float*)data;
	break;
	case ZAMDITHER_RESOLUTION:
		zamdither->fvarg1 = (float*)data;
	break;
	case ZAMDITHER_ZOOM:
		zamdither->fvarg3 = (float*)data;
	break;
	}
  
}

static inline float
from_dB(float gdb) {
	return (exp(gdb/20.f*log(10.f)));
};

static inline float
to_dB(float g) {
	return (20.f*log10(g));
}

static void
activate(LV2_Handle instance)
{
}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
	ZamDITHER* zamdither = (ZamDITHER*)instance;
  
	float* in1 = zamdither->inputl;
	float* in2 = zamdither->inputr;

	float* out1 = zamdither->outputl;
	float* out2 = zamdither->outputr;
	
	double b_fbamt[30];

	b_fbamt[29] = zamdither->fvarg33;
	b_fbamt[28] = zamdither->fvarg32;
	b_fbamt[27] = zamdither->fvarg31;
	b_fbamt[26] = zamdither->fvarg30;
	b_fbamt[25] = zamdither->fvarg29;
	b_fbamt[24] = zamdither->fvarg28;
	b_fbamt[23] = zamdither->fvarg27;
	b_fbamt[22] = zamdither->fvarg26;
	b_fbamt[21] = zamdither->fvarg25;
	b_fbamt[20] = zamdither->fvarg24;
	b_fbamt[19] = zamdither->fvarg23;
	b_fbamt[18] = zamdither->fvarg22;
	b_fbamt[17] = zamdither->fvarg21;
	b_fbamt[16] = zamdither->fvarg20;

	b_fbamt[15] = zamdither->fvarg19;
	b_fbamt[14] = zamdither->fvarg18;
	b_fbamt[13] = zamdither->fvarg17;
	b_fbamt[12] = zamdither->fvarg16;
	b_fbamt[11] = zamdither->fvarg15;
	b_fbamt[10] = zamdither->fvarg14;
	b_fbamt[9] = zamdither->fvarg13;
	b_fbamt[8] = zamdither->fvarg12;
	b_fbamt[7] = zamdither->fvarg11;
	b_fbamt[6] = zamdither->fvarg10;
	b_fbamt[5] = zamdither->fvarg9;
	b_fbamt[4] = zamdither->fvarg8;
	b_fbamt[3] = zamdither->fvarg7;
	b_fbamt[2] = zamdither->fvarg6;
	b_fbamt[1] = zamdither->fvarg5;
	b_fbamt[0] = zamdither->fvarg4;

	double b_dmode = (*(zamdither->fvarg0) * 10) + 0.5;	
	int i_dmode = (int) b_dmode;
	double b_dln = (*(zamdither->fvarg1)*100) + 0.5;
	int i_dln = (int) b_dln; if (i_dln < 2) {i_dln = 2;}
	double b_steps = i_dln;
	b_steps = (pow(2,b_steps)) / 2;
	double b_sub = ((zamdither->fvarg2) * 100) + 0.5;
	int i_sub = (int) b_sub;
	b_sub = i_sub;
	double b_datt = (b_steps-b_sub) / b_steps;
	if (b_datt < 0) {b_datt = 0;}
		
	double b_dzoom = pow(2,(((- *(zamdither->fvarg3))*1000))/ 6); 

	double b_hig = pow(2,(((1-zamdither->fvarg36)*-100))/ 6); 
	double b_log = pow(2,(((zamdither->fvarg39-0.5)*10))/ 6); 
	double b_att2 = pow(2,(((zamdither->fvarg37)*-1))/ 6);

	//eq
	double b_of1,b_of2,b_of3,b_of4,b_of5;
	double b_cErr;
	double b_cSum;
	double b_cSumpre;
	double b_cSub;
	double b_cIn;
	
	// adjust to samplerate //
	float b_sr = zamdither->srate;                   
	double b_srt = b_sr/44100;

	// front
	//double b_ingain = pow(2,(((zamdither->fvarg40-0.5)*100))/ 6); 
	double b_intgain = pow(2,(((zamdither->fvarg55)*10000))/ 6); 
	double b_gain1 = pow(2,(((zamdither->fvarg41-0.5)*100))/ 6); 
	double b_gain2 = pow(2,(((zamdither->fvarg42-0.5)*100))/ 6); 
	double b_gain3 = pow(2,(((zamdither->fvarg43-0.5)*100))/ 6); 
	double b_gain4 = pow(2,(((zamdither->fvarg44-0.5)*100))/ 6); 
	double b_gain5 = pow(2,(((zamdither->fvarg45-0.5)*100))/ 6); 

	double b_B1f = (pow(2,(((1-(zamdither->fvarg46))*-50))/ 6)) / b_srt;  
	double b_B2f = (pow(2,(((1-(zamdither->fvarg47))*-50))/ 6)) / b_srt;  
	double b_B3f = (pow(2,(((1-(zamdither->fvarg48))*-50))/ 6)) / b_srt;  
	double b_B4f = (pow(2,(((1-(zamdither->fvarg49))*-50))/ 6)) / b_srt; 
	double b_B1o = (pow(2,(((1-(zamdither->fvarg50))*-10))/ 6)) / b_srt;  
	double b_B2o = (pow(2,(((1-(zamdither->fvarg51))*-10))/ 6)) / b_srt;  
	double b_B3o = (pow(2,(((1-(zamdither->fvarg52))*-10))/ 6)) / b_srt;  
	double b_B4o = (pow(2,(((1-(zamdither->fvarg53))*-10))/ 6)) / b_srt; 
	double b_maxslope = 1-(0.5*0.001);
	b_B1o = b_B1o * b_maxslope;
	b_B2o = b_B2o * b_maxslope;
	b_B3o = b_B3o * b_maxslope;
	b_B4o = b_B4o * b_maxslope;
	//double b_maskpoint = pow(2,(((zamdither->fvarg54+1)*-100))/ 6); 

	b_B1f = b_B1f / (4/2); // Oversampling most on highest frequency.
	//b_B2f = b_B2f / (2/2);
	//b_B3f = b_B3f / (2/2); 
	//b_B4f = b_B4f / (2/2);

	// gaussian filter(s)

	double b_gscutB1 = 1-(b_B1f); if (b_gscutB1 < 0.0010) {b_gscutB1 = 0.0010;}
	double b_gsslopeB1 = b_B1o;
	double b_gscutB2 = 1-(b_B2f); if (b_gscutB2 < 0.0010) {b_gscutB2 = 0.0010;}
	double b_gsslopeB2 = b_B2o;
	double b_gscutB3 = 1-(b_B3f); if (b_gscutB3 < 0.0010) {b_gscutB3 = 0.0010;}
	double b_gsslopeB3 = b_B3o;
	double b_gscutB4 = 1-(b_B4f); if (b_gscutB4 < 0.0010) {b_gscutB4 = 0.0010;}
	double b_gsslopeB4 = b_B4o;

	double b_gsnrm;
	
	double b_gs1gainB1;
	double b_gs2gainB1;
	double b_gs3gainB1;
	double b_gs4gainB1;
	double b_gs5gainB1;

	b_gs1gainB1 = 1;
	b_gs2gainB1 = -4;
	b_gs3gainB1 = 6;
	b_gs4gainB1 = -4;
	b_gs5gainB1 = 1;

	double b_gs1cutB1;
	double b_gs2cutB1;
	double b_gs3cutB1;
	double b_gs4cutB1;
	double b_gs5cutB1;
	
	b_gs1cutB1 = b_gscutB1 * b_gsslopeB1 * b_gsslopeB1 * b_gsslopeB1 * b_gsslopeB1;
	b_gs2cutB1 = b_gscutB1 * b_gsslopeB1 * b_gsslopeB1 * b_gsslopeB1;
	b_gs3cutB1 = b_gscutB1 * b_gsslopeB1 * b_gsslopeB1;
	b_gs4cutB1 = b_gscutB1 * b_gsslopeB1;
	b_gs5cutB1 = b_gscutB1;

	b_gs1cutB1 = 1-b_gs1cutB1;
	b_gs2cutB1 = 1-b_gs2cutB1;
	b_gs3cutB1 = 1-b_gs3cutB1;
	b_gs4cutB1 = 1-b_gs4cutB1;
	b_gs5cutB1 = 1-b_gs5cutB1;

	b_gs1gainB1 = b_gs1gainB1 / b_gs1cutB1;
	b_gs2gainB1 = b_gs2gainB1 / b_gs2cutB1;
	b_gs3gainB1 = b_gs3gainB1 / b_gs3cutB1;
	b_gs4gainB1 = b_gs4gainB1 / b_gs4cutB1;
	b_gs5gainB1 = b_gs5gainB1 / b_gs5cutB1;

	b_of1 = b_gs1gainB1;
	b_of2 = b_gs2gainB1;
	b_of3 = b_gs3gainB1;
	b_of4 = b_gs4gainB1;
	b_of5 = b_gs5gainB1;

	b_cErr = 0;
	b_cSum = 0;

	b_cIn = b_of1;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;
	
	b_cIn = b_of2;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of3;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of4;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of5;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;
	
	b_gsnrm = 1/b_cSum;

	b_gs1gainB1 = b_gs1gainB1 * b_gsnrm;
	b_gs2gainB1 = b_gs2gainB1 * b_gsnrm;
	b_gs3gainB1 = b_gs3gainB1 * b_gsnrm;
	b_gs4gainB1 = b_gs4gainB1 * b_gsnrm;
	b_gs5gainB1 = b_gs5gainB1 * b_gsnrm;

	double b_gs1gainB2;
	double b_gs2gainB2;
	double b_gs3gainB2;
	double b_gs4gainB2;
	double b_gs5gainB2;

	b_gs1gainB2 = 1;
	b_gs2gainB2 = -4;
	b_gs3gainB2 = 6;
	b_gs4gainB2 = -4;
	b_gs5gainB2 = 1;

	double b_gs1cutB2;
	double b_gs2cutB2;
	double b_gs3cutB2;
	double b_gs4cutB2;
	double b_gs5cutB2;
	
	b_gs1cutB2 = b_gscutB2 * b_gsslopeB2 * b_gsslopeB2 * b_gsslopeB2 * b_gsslopeB2;
	b_gs2cutB2 = b_gscutB2 * b_gsslopeB2 * b_gsslopeB2 * b_gsslopeB2;
	b_gs3cutB2 = b_gscutB2 * b_gsslopeB2 * b_gsslopeB2;
	b_gs4cutB2 = b_gscutB2 * b_gsslopeB2;
	b_gs5cutB2 = b_gscutB2;

	b_gs1cutB2 = 1-b_gs1cutB2;
	b_gs2cutB2 = 1-b_gs2cutB2;
	b_gs3cutB2 = 1-b_gs3cutB2;
	b_gs4cutB2 = 1-b_gs4cutB2;
	b_gs5cutB2 = 1-b_gs5cutB2;

	b_gs1gainB2 = b_gs1gainB2 / b_gs1cutB2;
	b_gs2gainB2 = b_gs2gainB2 / b_gs2cutB2;
	b_gs3gainB2 = b_gs3gainB2 / b_gs3cutB2;
	b_gs4gainB2 = b_gs4gainB2 / b_gs4cutB2;
	b_gs5gainB2 = b_gs5gainB2 / b_gs5cutB2;

	b_of1 = b_gs1gainB2;
	b_of2 = b_gs2gainB2;
	b_of3 = b_gs3gainB2;
	b_of4 = b_gs4gainB2;
	b_of5 = b_gs5gainB2;

	b_cErr = 0;
	b_cSum = 0;

	b_cIn = b_of1;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;
	
	b_cIn = b_of2;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of3;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of4;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of5;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;
	
	b_gsnrm = 1/b_cSum;

	b_gs1gainB2 = b_gs1gainB2 * b_gsnrm;
	b_gs2gainB2 = b_gs2gainB2 * b_gsnrm;
	b_gs3gainB2 = b_gs3gainB2 * b_gsnrm;
	b_gs4gainB2 = b_gs4gainB2 * b_gsnrm;
	b_gs5gainB2 = b_gs5gainB2 * b_gsnrm;

	double b_gs1gainB3;
	double b_gs2gainB3;
	double b_gs3gainB3;
	double b_gs4gainB3;
	double b_gs5gainB3;

	b_gs1gainB3 = 1;
	b_gs2gainB3 = -4;
	b_gs3gainB3 = 6;
	b_gs4gainB3 = -4;
	b_gs5gainB3 = 1;

	double b_gs1cutB3;
	double b_gs2cutB3;
	double b_gs3cutB3;
	double b_gs4cutB3;
	double b_gs5cutB3;
	
	b_gs1cutB3 = b_gscutB3 * b_gsslopeB3 * b_gsslopeB3 * b_gsslopeB3 * b_gsslopeB3;
	b_gs2cutB3 = b_gscutB3 * b_gsslopeB3 * b_gsslopeB3 * b_gsslopeB3;
	b_gs3cutB3 = b_gscutB3 * b_gsslopeB3 * b_gsslopeB3;
	b_gs4cutB3 = b_gscutB3 * b_gsslopeB3;
	b_gs5cutB3 = b_gscutB3;

	b_gs1cutB3 = 1-b_gs1cutB3;
	b_gs2cutB3 = 1-b_gs2cutB3;
	b_gs3cutB3 = 1-b_gs3cutB3;
	b_gs4cutB3 = 1-b_gs4cutB3;
	b_gs5cutB3 = 1-b_gs5cutB3;

	b_gs1gainB3 = b_gs1gainB3 / b_gs1cutB3;
	b_gs2gainB3 = b_gs2gainB3 / b_gs2cutB3;
	b_gs3gainB3 = b_gs3gainB3 / b_gs3cutB3;
	b_gs4gainB3 = b_gs4gainB3 / b_gs4cutB3;
	b_gs5gainB3 = b_gs5gainB3 / b_gs5cutB3;

	b_of1 = b_gs1gainB3;
	b_of2 = b_gs2gainB3;
	b_of3 = b_gs3gainB3;
	b_of4 = b_gs4gainB3;
	b_of5 = b_gs5gainB3;

	b_cErr = 0;
	b_cSum = 0;

	b_cIn = b_of1;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;
	
	b_cIn = b_of2;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of3;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of4;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of5;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;
	
	b_gsnrm = 1/b_cSum;

	b_gs1gainB3 = b_gs1gainB3 * b_gsnrm;
	b_gs2gainB3 = b_gs2gainB3 * b_gsnrm;
	b_gs3gainB3 = b_gs3gainB3 * b_gsnrm;
	b_gs4gainB3 = b_gs4gainB3 * b_gsnrm;
	b_gs5gainB3 = b_gs5gainB3 * b_gsnrm;

	double b_gs1gainB4;
	double b_gs2gainB4;
	double b_gs3gainB4;
	double b_gs4gainB4;
	double b_gs5gainB4;

	b_gs1gainB4 = 1;
	b_gs2gainB4 = -4;
	b_gs3gainB4 = 6;
	b_gs4gainB4 = -4;
	b_gs5gainB4 = 1;

	double b_gs1cutB4;
	double b_gs2cutB4;
	double b_gs3cutB4;
	double b_gs4cutB4;
	double b_gs5cutB4;
	
	b_gs1cutB4 = b_gscutB4 * b_gsslopeB4 * b_gsslopeB4 * b_gsslopeB4 * b_gsslopeB4;
	b_gs2cutB4 = b_gscutB4 * b_gsslopeB4 * b_gsslopeB4 * b_gsslopeB4;
	b_gs3cutB4 = b_gscutB4 * b_gsslopeB4 * b_gsslopeB4;
	b_gs4cutB4 = b_gscutB4 * b_gsslopeB4;
	b_gs5cutB4 = b_gscutB4;

	b_gs1cutB4 = 1-b_gs1cutB4;
	b_gs2cutB4 = 1-b_gs2cutB4;
	b_gs3cutB4 = 1-b_gs3cutB4;
	b_gs4cutB4 = 1-b_gs4cutB4;
	b_gs5cutB4 = 1-b_gs5cutB4;

	b_gs1gainB4 = b_gs1gainB4 / b_gs1cutB4;
	b_gs2gainB4 = b_gs2gainB4 / b_gs2cutB4;
	b_gs3gainB4 = b_gs3gainB4 / b_gs3cutB4;
	b_gs4gainB4 = b_gs4gainB4 / b_gs4cutB4;
	b_gs5gainB4 = b_gs5gainB4 / b_gs5cutB4;

	b_of1 = b_gs1gainB4;
	b_of2 = b_gs2gainB4;
	b_of3 = b_gs3gainB4;
	b_of4 = b_gs4gainB4;
	b_of5 = b_gs5gainB4;

	b_cErr = 0;
	b_cSum = 0;

	b_cIn = b_of1;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;
	
	b_cIn = b_of2;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of3;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of4;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;

	b_cIn = b_of5;
	b_cSub = b_cIn - b_cErr; b_cSumpre = b_cSum;
	b_cSum = b_cSum + b_cSub;
	b_cErr = (b_cSum-b_cSumpre) - b_cSub;
	
	b_gsnrm = 1/b_cSum;

	b_gs1gainB4 = b_gs1gainB4 * b_gsnrm;
	b_gs2gainB4 = b_gs2gainB4 * b_gsnrm;
	b_gs3gainB4 = b_gs3gainB4 * b_gsnrm;
	b_gs4gainB4 = b_gs4gainB4 * b_gsnrm;
	b_gs5gainB4 = b_gs5gainB4 * b_gsnrm;

	int i_pos = zamdither->fvarg54*100;

/////////////////////////////////////////////////////////////
// MAIN LOOP

	for (uint32_t i = 0; i < n_samples; ++i) {

		double b_in1 = *in1++;
		double b_in2 = *in2++;
		if (i_dmode != 0) { // 0 off, 1 enable, 2 round
  
			b_in1 = b_in1 * b_datt; // attenuate.
			b_in2 = b_in2 * b_datt;
			b_in1 = b_in1 * b_att2; // attenuate.
			b_in2 = b_in2 * b_att2;
  
			// zoom, to inspect dither.
			b_in1 = b_in1 * b_dzoom;
			b_in2 = b_in2 * b_dzoom;

			// negative feedback, for shifting the error upwards in the frequency spectrum.
			int i_cnt = 29; // orders-1
			while (i_cnt > -1) {
				if (i_cnt > 5) {
					b_in1 = b_in1 - (zamdither->b_err1[i_cnt] * (b_fbamt[i_cnt])* zamdither->fvarg34);
					b_in2 = b_in2 - (zamdither->b_err2[i_cnt] * (b_fbamt[i_cnt])* zamdither->fvarg34);
				} else {
					b_in1 = b_in1 - (zamdither->b_err1[i_cnt] * (b_fbamt[i_cnt])); // 
					b_in2 = b_in2 - (zamdither->b_err2[i_cnt] * (b_fbamt[i_cnt]));
				}
				i_cnt--;
			}
     
			double b_in1q = b_in1 * b_steps; // 16 max = 32767 min = -32768: subtract two, one to avoid clipping one side, one to avoid clip detectors.
			double b_in2q = b_in2 * b_steps;
	
			double b_in1nq = b_in1q;
			double b_in2nq = b_in2q;

			int i_in1q = b_in1q; // convert to signed integers, as used in CD players.
			int i_in2q = b_in2q;

			b_in1q = i_in1q;
			b_in2q = i_in2q;
			
			if (i_dmode == 2) { // round
				double b_roundat = zamdither->fvarg57; if (zamdither->fvarg56 == 0) {b_roundat = 0.5;}
				if (b_in1nq > 0) {
					double b_rerr =  b_in1nq-b_in1q;
					if (b_rerr > b_roundat) {b_in1q++;}
				} else if (b_in1nq < 0) {
					b_in1nq = -b_in1nq;
					b_in1q = -b_in1q;
					double b_rerr =  b_in1nq-b_in1q;
					if (b_rerr > b_roundat) {b_in1q++;} // -------------- fixed val here?
					b_in1nq = -b_in1nq;
					b_in1q = -b_in1q;
				}
				if (b_in2nq > 0) {
					double b_rerr =  b_in2nq-b_in2q;
					if (b_rerr > b_roundat) {b_in2q++;}
				} else if (b_in2nq < 0) {
					b_in2nq = -b_in2nq;
					b_in2q = -b_in2q;
					double b_rerr =  b_in2nq-b_in2q;
					if (b_rerr > b_roundat) {b_in2q++;}
					b_in2nq = -b_in2nq;
					b_in2q = -b_in2q;
				} 
			}
			
			b_in1q = b_in1q / b_steps;
			b_in2q = b_in2q / b_steps;
		
			double b_aerr1 =  b_in1q-b_in1;// Q Err
			double b_aerr2 =  b_in2q-b_in2;

			if (zamdither->fvarg40 == 0.0) {
				// aerr filter
				zamdither->b_lo1 = zamdither->b_lo1 + ((-zamdither->b_lo1 + b_aerr1) * zamdither->fvarg38);
				zamdither->b_lo2 = zamdither->b_lo2 + ((-zamdither->b_lo2 + b_aerr2) * zamdither->fvarg38);
				zamdither->b_hi1 = zamdither->b_hi1 + ((-zamdither->b_hi1 + b_aerr1) * zamdither->fvarg35);
				zamdither->b_hi2 = zamdither->b_hi2 + ((-zamdither->b_hi2 + b_aerr2) * zamdither->fvarg35);
				double b_hi1o = b_aerr1 - zamdither->b_hi1;
				double b_hi2o = b_aerr2 - zamdither->b_hi2;
				b_aerr1 = b_aerr1 - (zamdither->b_lo1 + b_hi1o);
				b_aerr2 = b_aerr2 - (zamdither->b_lo2 + b_hi2o);

				b_aerr1 = b_aerr1 + ((zamdither->b_lo1*b_log) + (b_hi1o*b_hig));
				b_aerr2 = b_aerr2 + ((zamdither->b_lo2*b_log) + (b_hi2o*b_hig));
			} else { // advanced aerr gaussian plateau EQ

				if (zamdither->fvarg40 >= 0.99) {
					// aerr filter
					zamdither->b_lo1 = zamdither->b_lo1 + ((-zamdither->b_lo1 + b_aerr1) * zamdither->fvarg38);
					zamdither->b_lo2 = zamdither->b_lo2 + ((-zamdither->b_lo2 + b_aerr2) * zamdither->fvarg38);
					zamdither->b_hi1 = zamdither->b_hi1 + ((-zamdither->b_hi1 + b_aerr1) * zamdither->fvarg35);
					zamdither->b_hi2 = zamdither->b_hi2 + ((-zamdither->b_hi2 + b_aerr2) * zamdither->fvarg35);
					double b_hi1o = b_aerr1 - zamdither->b_hi1;
					double b_hi2o = b_aerr2 - zamdither->b_hi2;
					b_aerr1 = b_aerr1 - (zamdither->b_lo1 + b_hi1o);
					b_aerr2 = b_aerr2 - (zamdither->b_lo2 + b_hi2o);		

					b_aerr1 = b_aerr1 + ((zamdither->b_lo1*b_log) + (b_hi1o*b_hig));
					b_aerr2 = b_aerr2 + ((zamdither->b_lo2*b_log) + (b_hi2o*b_hig));
				}

			zamdither->b_err1[i_pos] = zamdither->b_err1[i_pos] * b_intgain;
			zamdither->b_err2[i_pos] = zamdither->b_err2[i_pos] * b_intgain;

			double b_gs1gainB0 = 1;
			double b_gs2gainB0 = 1;
			double b_gs3gainB0 = 1;
			double b_gs4gainB0 = 1;
			double b_gs5gainB0 = 1;

			double b_gs1bufB0ao = zamdither->b_err1[i_pos];		double b_gs1bufB0bo = zamdither->b_err2[i_pos];
			double b_gs2bufB0ao = 0    ;		double b_gs2bufB0bo = 0    ;
			double b_gs3bufB0ao = 0    ;		double b_gs3bufB0bo = 0    ;
			double b_gs4bufB0ao = 0    ;		double b_gs4bufB0bo = 0    ;
			double b_gs5bufB0ao = 0    ;		double b_gs5bufB0bo = 0    ;

			double b_gs1gainB5 = 0;
			double b_gs2gainB5 = 0;
			double b_gs3gainB5 = 0;
			double b_gs4gainB5 = 0;
			double b_gs5gainB5 = 0;

			double b_gs1bufB5ao = 0;		double b_gs1bufB5bo = 0;
			double b_gs2bufB5ao = 0;		double b_gs2bufB5bo = 0;
			double b_gs3bufB5ao = 0;		double b_gs3bufB5bo = 0;
			double b_gs4bufB5ao = 0;		double b_gs4bufB5bo = 0;
			double b_gs5bufB5ao = 0;		double b_gs5bufB5bo = 0;

			double b_gs1bufB1ao;
			double b_gs2bufB1ao;
			double b_gs3bufB1ao;
			double b_gs4bufB1ao;
			double b_gs5bufB1ao;
			double b_gs1bufB1bo;
			double b_gs2bufB1bo;
			double b_gs3bufB1bo;
			double b_gs4bufB1bo;
			double b_gs5bufB1bo;

			double b_gs1bufB2ao;
			double b_gs2bufB2ao;
			double b_gs3bufB2ao;
			double b_gs4bufB2ao;
			double b_gs5bufB2ao;
			double b_gs1bufB2bo;
			double b_gs2bufB2bo;
			double b_gs3bufB2bo;
			double b_gs4bufB2bo;
			double b_gs5bufB2bo;

			double b_gs1bufB3ao;
			double b_gs2bufB3ao;
			double b_gs3bufB3ao;
			double b_gs4bufB3ao;
			double b_gs5bufB3ao;
			double b_gs1bufB3bo;
			double b_gs2bufB3bo;
			double b_gs3bufB3bo;
			double b_gs4bufB3bo;
			double b_gs5bufB3bo;

			double b_gs1bufB4ao;
			double b_gs2bufB4ao;
			double b_gs3bufB4ao;
			double b_gs4bufB4ao;
			double b_gs5bufB4ao;
			double b_gs1bufB4bo;
			double b_gs2bufB4bo;
			double b_gs3bufB4bo;
			double b_gs4bufB4bo;
			double b_gs5bufB4bo;

			zamdither->b_gs1bufB1a = zamdither->b_gs1bufB1a + ((-zamdither->b_gs1bufB1a + zamdither->b_err1[i_pos]) * b_gs1cutB1); b_gs1bufB1ao = zamdither->b_gs1bufB1a;
			zamdither->b_gs2bufB1a = zamdither->b_gs2bufB1a + ((-zamdither->b_gs2bufB1a + zamdither->b_err1[i_pos]) * b_gs2cutB1); b_gs2bufB1ao = zamdither->b_gs2bufB1a;
			zamdither->b_gs3bufB1a = zamdither->b_gs3bufB1a + ((-zamdither->b_gs3bufB1a + zamdither->b_err1[i_pos]) * b_gs3cutB1); b_gs3bufB1ao = zamdither->b_gs3bufB1a;
			zamdither->b_gs4bufB1a = zamdither->b_gs4bufB1a + ((-zamdither->b_gs4bufB1a + zamdither->b_err1[i_pos]) * b_gs4cutB1); b_gs4bufB1ao = zamdither->b_gs4bufB1a;
			zamdither->b_gs5bufB1a = zamdither->b_gs5bufB1a + ((-zamdither->b_gs5bufB1a + zamdither->b_err1[i_pos]) * b_gs5cutB1); b_gs5bufB1ao = zamdither->b_gs5bufB1a;
			zamdither->b_gs1bufB1a = zamdither->b_gs1bufB1a + ((-zamdither->b_gs1bufB1a +     0) * b_gs1cutB1); b_gs1bufB1ao = b_gs1bufB1ao + zamdither->b_gs1bufB1a;
			zamdither->b_gs2bufB1a = zamdither->b_gs2bufB1a + ((-zamdither->b_gs2bufB1a +     0) * b_gs2cutB1); b_gs2bufB1ao = b_gs2bufB1ao + zamdither->b_gs2bufB1a;
			zamdither->b_gs3bufB1a = zamdither->b_gs3bufB1a + ((-zamdither->b_gs3bufB1a +     0) * b_gs3cutB1); b_gs3bufB1ao = b_gs3bufB1ao + zamdither->b_gs3bufB1a;
			zamdither->b_gs4bufB1a = zamdither->b_gs4bufB1a + ((-zamdither->b_gs4bufB1a +     0) * b_gs4cutB1); b_gs4bufB1ao = b_gs4bufB1ao + zamdither->b_gs4bufB1a;
			zamdither->b_gs5bufB1a = zamdither->b_gs5bufB1a + ((-zamdither->b_gs5bufB1a +     0) * b_gs5cutB1); b_gs5bufB1ao = b_gs5bufB1ao + zamdither->b_gs5bufB1a;
			zamdither->b_gs1bufB1a = zamdither->b_gs1bufB1a + ((-zamdither->b_gs1bufB1a +     0) * b_gs1cutB1); b_gs1bufB1ao = b_gs1bufB1ao + zamdither->b_gs1bufB1a;
			zamdither->b_gs2bufB1a = zamdither->b_gs2bufB1a + ((-zamdither->b_gs2bufB1a +     0) * b_gs2cutB1); b_gs2bufB1ao = b_gs2bufB1ao + zamdither->b_gs2bufB1a;
			zamdither->b_gs3bufB1a = zamdither->b_gs3bufB1a + ((-zamdither->b_gs3bufB1a +     0) * b_gs3cutB1); b_gs3bufB1ao = b_gs3bufB1ao + zamdither->b_gs3bufB1a;
			zamdither->b_gs4bufB1a = zamdither->b_gs4bufB1a + ((-zamdither->b_gs4bufB1a +     0) * b_gs4cutB1); b_gs4bufB1ao = b_gs4bufB1ao + zamdither->b_gs4bufB1a;
			zamdither->b_gs5bufB1a = zamdither->b_gs5bufB1a + ((-zamdither->b_gs5bufB1a +     0) * b_gs5cutB1); b_gs5bufB1ao = b_gs5bufB1ao + zamdither->b_gs5bufB1a;
			zamdither->b_gs1bufB1a = zamdither->b_gs1bufB1a + ((-zamdither->b_gs1bufB1a +     0) * b_gs1cutB1); b_gs1bufB1ao = b_gs1bufB1ao + zamdither->b_gs1bufB1a;
			zamdither->b_gs2bufB1a = zamdither->b_gs2bufB1a + ((-zamdither->b_gs2bufB1a +     0) * b_gs2cutB1); b_gs2bufB1ao = b_gs2bufB1ao + zamdither->b_gs2bufB1a;
			zamdither->b_gs3bufB1a = zamdither->b_gs3bufB1a + ((-zamdither->b_gs3bufB1a +     0) * b_gs3cutB1); b_gs3bufB1ao = b_gs3bufB1ao + zamdither->b_gs3bufB1a;
			zamdither->b_gs4bufB1a = zamdither->b_gs4bufB1a + ((-zamdither->b_gs4bufB1a +     0) * b_gs4cutB1); b_gs4bufB1ao = b_gs4bufB1ao + zamdither->b_gs4bufB1a;
			zamdither->b_gs5bufB1a = zamdither->b_gs5bufB1a + ((-zamdither->b_gs5bufB1a +     0) * b_gs5cutB1); b_gs5bufB1ao = b_gs5bufB1ao + zamdither->b_gs5bufB1a;
			b_of1 = (b_gs1gainB0 * b_gs1bufB0ao) - (b_gs1gainB1*b_gs1bufB1ao);
			b_of2 = (b_gs2gainB0 * b_gs2bufB0ao) - (b_gs2gainB1*b_gs2bufB1ao);
			b_of3 = (b_gs3gainB0 * b_gs3bufB0ao) - (b_gs3gainB1*b_gs3bufB1ao);
			b_of4 = (b_gs4gainB0 * b_gs4bufB0ao) - (b_gs4gainB1*b_gs4bufB1ao);
			b_of5 = (b_gs5gainB0 * b_gs5bufB0ao) - (b_gs5gainB1*b_gs5bufB1ao);
			double b_B1outa = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			zamdither->b_gs1bufB1b = zamdither->b_gs1bufB1b + ((-zamdither->b_gs1bufB1b + zamdither->b_err2[i_pos]) * b_gs1cutB1); b_gs1bufB1bo = zamdither->b_gs1bufB1b; 
			zamdither->b_gs2bufB1b = zamdither->b_gs2bufB1b + ((-zamdither->b_gs2bufB1b + zamdither->b_err2[i_pos]) * b_gs2cutB1); b_gs2bufB1bo = zamdither->b_gs2bufB1b;
			zamdither->b_gs3bufB1b = zamdither->b_gs3bufB1b + ((-zamdither->b_gs3bufB1b + zamdither->b_err2[i_pos]) * b_gs3cutB1); b_gs3bufB1bo = zamdither->b_gs3bufB1b;
			zamdither->b_gs4bufB1b = zamdither->b_gs4bufB1b + ((-zamdither->b_gs4bufB1b + zamdither->b_err2[i_pos]) * b_gs4cutB1); b_gs4bufB1bo = zamdither->b_gs4bufB1b;
			zamdither->b_gs5bufB1b = zamdither->b_gs5bufB1b + ((-zamdither->b_gs5bufB1b + zamdither->b_err2[i_pos]) * b_gs5cutB1); b_gs5bufB1bo = zamdither->b_gs5bufB1b;
			zamdither->b_gs1bufB1b = zamdither->b_gs1bufB1b + ((-zamdither->b_gs1bufB1b +     0) * b_gs1cutB1); b_gs1bufB1bo = b_gs1bufB1bo + zamdither->b_gs1bufB1b;
			zamdither->b_gs2bufB1b = zamdither->b_gs2bufB1b + ((-zamdither->b_gs2bufB1b +     0) * b_gs2cutB1); b_gs2bufB1bo = b_gs2bufB1bo + zamdither->b_gs2bufB1b;
			zamdither->b_gs3bufB1b = zamdither->b_gs3bufB1b + ((-zamdither->b_gs3bufB1b +     0) * b_gs3cutB1); b_gs3bufB1bo = b_gs3bufB1bo + zamdither->b_gs3bufB1b;
			zamdither->b_gs4bufB1b = zamdither->b_gs4bufB1b + ((-zamdither->b_gs4bufB1b +     0) * b_gs4cutB1); b_gs4bufB1bo = b_gs4bufB1bo + zamdither->b_gs4bufB1b;
			zamdither->b_gs5bufB1b = zamdither->b_gs5bufB1b + ((-zamdither->b_gs5bufB1b +     0) * b_gs5cutB1); b_gs5bufB1bo = b_gs5bufB1bo + zamdither->b_gs5bufB1b;
			zamdither->b_gs1bufB1b = zamdither->b_gs1bufB1b + ((-zamdither->b_gs1bufB1b +     0) * b_gs1cutB1); b_gs1bufB1bo = b_gs1bufB1bo + zamdither->b_gs1bufB1b;
			zamdither->b_gs2bufB1b = zamdither->b_gs2bufB1b + ((-zamdither->b_gs2bufB1b +     0) * b_gs2cutB1); b_gs2bufB1bo = b_gs2bufB1bo + zamdither->b_gs2bufB1b;
			zamdither->b_gs3bufB1b = zamdither->b_gs3bufB1b + ((-zamdither->b_gs3bufB1b +     0) * b_gs3cutB1); b_gs3bufB1bo = b_gs3bufB1bo + zamdither->b_gs3bufB1b;
			zamdither->b_gs4bufB1b = zamdither->b_gs4bufB1b + ((-zamdither->b_gs4bufB1b +     0) * b_gs4cutB1); b_gs4bufB1bo = b_gs4bufB1bo + zamdither->b_gs4bufB1b;
			zamdither->b_gs5bufB1b = zamdither->b_gs5bufB1b + ((-zamdither->b_gs5bufB1b +     0) * b_gs5cutB1); b_gs5bufB1bo = b_gs5bufB1bo + zamdither->b_gs5bufB1b;
			zamdither->b_gs1bufB1b = zamdither->b_gs1bufB1b + ((-zamdither->b_gs1bufB1b +     0) * b_gs1cutB1); b_gs1bufB1bo = b_gs1bufB1bo + zamdither->b_gs1bufB1b;
			zamdither->b_gs2bufB1b = zamdither->b_gs2bufB1b + ((-zamdither->b_gs2bufB1b +     0) * b_gs2cutB1); b_gs2bufB1bo = b_gs2bufB1bo + zamdither->b_gs2bufB1b;
			zamdither->b_gs3bufB1b = zamdither->b_gs3bufB1b + ((-zamdither->b_gs3bufB1b +     0) * b_gs3cutB1); b_gs3bufB1bo = b_gs3bufB1bo + zamdither->b_gs3bufB1b;
			zamdither->b_gs4bufB1b = zamdither->b_gs4bufB1b + ((-zamdither->b_gs4bufB1b +     0) * b_gs4cutB1); b_gs4bufB1bo = b_gs4bufB1bo + zamdither->b_gs4bufB1b;
			zamdither->b_gs5bufB1b = zamdither->b_gs5bufB1b + ((-zamdither->b_gs5bufB1b +     0) * b_gs5cutB1); b_gs5bufB1bo = b_gs5bufB1bo + zamdither->b_gs5bufB1b;
			b_of1 = (b_gs1gainB0 * b_gs1bufB0bo) - (b_gs1gainB1*b_gs1bufB1bo);
			b_of2 = (b_gs2gainB0 * b_gs2bufB0bo) - (b_gs2gainB1*b_gs2bufB1bo);
			b_of3 = (b_gs3gainB0 * b_gs3bufB0bo) - (b_gs3gainB1*b_gs3bufB1bo);
			b_of4 = (b_gs4gainB0 * b_gs4bufB0bo) - (b_gs4gainB1*b_gs4bufB1bo);
			b_of5 = (b_gs5gainB0 * b_gs5bufB0bo) - (b_gs5gainB1*b_gs5bufB1bo);
			double b_B1outb = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			zamdither->b_gs1bufB2a = zamdither->b_gs1bufB2a + ((-zamdither->b_gs1bufB2a + zamdither->b_err1[i_pos]) * b_gs1cutB2); b_gs1bufB2ao = zamdither->b_gs1bufB2a;
			zamdither->b_gs2bufB2a = zamdither->b_gs2bufB2a + ((-zamdither->b_gs2bufB2a + zamdither->b_err1[i_pos]) * b_gs2cutB2); b_gs2bufB2ao = zamdither->b_gs2bufB2a;
			zamdither->b_gs3bufB2a = zamdither->b_gs3bufB2a + ((-zamdither->b_gs3bufB2a + zamdither->b_err1[i_pos]) * b_gs3cutB2); b_gs3bufB2ao = zamdither->b_gs3bufB2a;
			zamdither->b_gs4bufB2a = zamdither->b_gs4bufB2a + ((-zamdither->b_gs4bufB2a + zamdither->b_err1[i_pos]) * b_gs4cutB2); b_gs4bufB2ao = zamdither->b_gs4bufB2a;
			zamdither->b_gs5bufB2a = zamdither->b_gs5bufB2a + ((-zamdither->b_gs5bufB2a + zamdither->b_err1[i_pos]) * b_gs5cutB2); b_gs5bufB2ao = zamdither->b_gs5bufB2a;
			zamdither->b_gs1bufB2a = zamdither->b_gs1bufB2a + ((-zamdither->b_gs1bufB2a +     0) * b_gs1cutB2); b_gs1bufB2ao = b_gs1bufB2ao + zamdither->b_gs1bufB2a;
			zamdither->b_gs2bufB2a = zamdither->b_gs2bufB2a + ((-zamdither->b_gs2bufB2a +     0) * b_gs2cutB2); b_gs2bufB2ao = b_gs2bufB2ao + zamdither->b_gs2bufB2a;
			zamdither->b_gs3bufB2a = zamdither->b_gs3bufB2a + ((-zamdither->b_gs3bufB2a +     0) * b_gs3cutB2); b_gs3bufB2ao = b_gs3bufB2ao + zamdither->b_gs3bufB2a;
			zamdither->b_gs4bufB2a = zamdither->b_gs4bufB2a + ((-zamdither->b_gs4bufB2a +     0) * b_gs4cutB2); b_gs4bufB2ao = b_gs4bufB2ao + zamdither->b_gs4bufB2a;
			zamdither->b_gs5bufB2a = zamdither->b_gs5bufB2a + ((-zamdither->b_gs5bufB2a +     0) * b_gs5cutB2); b_gs5bufB2ao = b_gs5bufB2ao + zamdither->b_gs5bufB2a;
			b_of1 = (b_gs1gainB1 * b_gs1bufB1ao) - (b_gs1gainB2*b_gs1bufB2ao);
			b_of2 = (b_gs2gainB1 * b_gs2bufB1ao) - (b_gs2gainB2*b_gs2bufB2ao);
			b_of3 = (b_gs3gainB1 * b_gs3bufB1ao) - (b_gs3gainB2*b_gs3bufB2ao);
			b_of4 = (b_gs4gainB1 * b_gs4bufB1ao) - (b_gs4gainB2*b_gs4bufB2ao);
			b_of5 = (b_gs5gainB1 * b_gs5bufB1ao) - (b_gs5gainB2*b_gs5bufB2ao);
			double b_B2outa = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			zamdither->b_gs1bufB2b = zamdither->b_gs1bufB2b + ((-zamdither->b_gs1bufB2b + zamdither->b_err2[i_pos]) * b_gs1cutB2); b_gs1bufB2bo = zamdither->b_gs1bufB2b; 
			zamdither->b_gs2bufB2b = zamdither->b_gs2bufB2b + ((-zamdither->b_gs2bufB2b + zamdither->b_err2[i_pos]) * b_gs2cutB2); b_gs2bufB2bo = zamdither->b_gs2bufB2b;
			zamdither->b_gs3bufB2b = zamdither->b_gs3bufB2b + ((-zamdither->b_gs3bufB2b + zamdither->b_err2[i_pos]) * b_gs3cutB2); b_gs3bufB2bo = zamdither->b_gs3bufB2b;
			zamdither->b_gs4bufB2b = zamdither->b_gs4bufB2b + ((-zamdither->b_gs4bufB2b + zamdither->b_err2[i_pos]) * b_gs4cutB2); b_gs4bufB2bo = zamdither->b_gs4bufB2b;
			zamdither->b_gs5bufB2b = zamdither->b_gs5bufB2b + ((-zamdither->b_gs5bufB2b + zamdither->b_err2[i_pos]) * b_gs5cutB2); b_gs5bufB2bo = zamdither->b_gs5bufB2b;
			zamdither->b_gs1bufB2b = zamdither->b_gs1bufB2b + ((-zamdither->b_gs1bufB2b +     0) * b_gs1cutB2); b_gs1bufB2bo = b_gs1bufB2bo + zamdither->b_gs1bufB2b;
			zamdither->b_gs2bufB2b = zamdither->b_gs2bufB2b + ((-zamdither->b_gs2bufB2b +     0) * b_gs2cutB2); b_gs2bufB2bo = b_gs2bufB2bo + zamdither->b_gs2bufB2b;
			zamdither->b_gs3bufB2b = zamdither->b_gs3bufB2b + ((-zamdither->b_gs3bufB2b +     0) * b_gs3cutB2); b_gs3bufB2bo = b_gs3bufB2bo + zamdither->b_gs3bufB2b;
			zamdither->b_gs4bufB2b = zamdither->b_gs4bufB2b + ((-zamdither->b_gs4bufB2b +     0) * b_gs4cutB2); b_gs4bufB2bo = b_gs4bufB2bo + zamdither->b_gs4bufB2b;
			zamdither->b_gs5bufB2b = zamdither->b_gs5bufB2b + ((-zamdither->b_gs5bufB2b +     0) * b_gs5cutB2); b_gs5bufB2bo = b_gs5bufB2bo + zamdither->b_gs5bufB2b;
			b_of1 = (b_gs1gainB1 * b_gs1bufB1bo) - (b_gs1gainB2*b_gs1bufB2bo);
			b_of2 = (b_gs2gainB1 * b_gs2bufB1bo) - (b_gs2gainB2*b_gs2bufB2bo);
			b_of3 = (b_gs3gainB1 * b_gs3bufB1bo) - (b_gs3gainB2*b_gs3bufB2bo);
			b_of4 = (b_gs4gainB1 * b_gs4bufB1bo) - (b_gs4gainB2*b_gs4bufB2bo);
			b_of5 = (b_gs5gainB1 * b_gs5bufB1bo) - (b_gs5gainB2*b_gs5bufB2bo);
			double b_B2outb = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			zamdither->b_gs1bufB3a = zamdither->b_gs1bufB3a + ((-zamdither->b_gs1bufB3a + zamdither->b_err1[i_pos]) * b_gs1cutB3); b_gs1bufB3ao = zamdither->b_gs1bufB3a;
			zamdither->b_gs2bufB3a = zamdither->b_gs2bufB3a + ((-zamdither->b_gs2bufB3a + zamdither->b_err1[i_pos]) * b_gs2cutB3); b_gs2bufB3ao = zamdither->b_gs2bufB3a;
			zamdither->b_gs3bufB3a = zamdither->b_gs3bufB3a + ((-zamdither->b_gs3bufB3a + zamdither->b_err1[i_pos]) * b_gs3cutB3); b_gs3bufB3ao = zamdither->b_gs3bufB3a;
			zamdither->b_gs4bufB3a = zamdither->b_gs4bufB3a + ((-zamdither->b_gs4bufB3a + zamdither->b_err1[i_pos]) * b_gs4cutB3); b_gs4bufB3ao = zamdither->b_gs4bufB3a;
			zamdither->b_gs5bufB3a = zamdither->b_gs5bufB3a + ((-zamdither->b_gs5bufB3a + zamdither->b_err1[i_pos]) * b_gs5cutB3); b_gs5bufB3ao = zamdither->b_gs5bufB3a;
			zamdither->b_gs1bufB3a = zamdither->b_gs1bufB3a + ((-zamdither->b_gs1bufB3a +     0) * b_gs1cutB3); b_gs1bufB3ao = b_gs1bufB3ao + zamdither->b_gs1bufB3a;
			zamdither->b_gs2bufB3a = zamdither->b_gs2bufB3a + ((-zamdither->b_gs2bufB3a +     0) * b_gs2cutB3); b_gs2bufB3ao = b_gs2bufB3ao + zamdither->b_gs2bufB3a;
			zamdither->b_gs3bufB3a = zamdither->b_gs3bufB3a + ((-zamdither->b_gs3bufB3a +     0) * b_gs3cutB3); b_gs3bufB3ao = b_gs3bufB3ao + zamdither->b_gs3bufB3a;
			zamdither->b_gs4bufB3a = zamdither->b_gs4bufB3a + ((-zamdither->b_gs4bufB3a +     0) * b_gs4cutB3); b_gs4bufB3ao = b_gs4bufB3ao + zamdither->b_gs4bufB3a;
			zamdither->b_gs5bufB3a = zamdither->b_gs5bufB3a + ((-zamdither->b_gs5bufB3a +     0) * b_gs5cutB3); b_gs5bufB3ao = b_gs5bufB3ao + zamdither->b_gs5bufB3a;
			b_of1 = (b_gs1gainB2 * b_gs1bufB2ao) - (b_gs1gainB3*b_gs1bufB3ao);
			b_of2 = (b_gs2gainB2 * b_gs2bufB2ao) - (b_gs2gainB3*b_gs2bufB3ao);
			b_of3 = (b_gs3gainB2 * b_gs3bufB2ao) - (b_gs3gainB3*b_gs3bufB3ao);
			b_of4 = (b_gs4gainB2 * b_gs4bufB2ao) - (b_gs4gainB3*b_gs4bufB3ao);
			b_of5 = (b_gs5gainB2 * b_gs5bufB2ao) - (b_gs5gainB3*b_gs5bufB3ao);
			double b_B3outa = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			zamdither->b_gs1bufB3b = zamdither->b_gs1bufB3b + ((-zamdither->b_gs1bufB3b + zamdither->b_err2[i_pos]) * b_gs1cutB3); b_gs1bufB3bo = zamdither->b_gs1bufB3b; 
			zamdither->b_gs2bufB3b = zamdither->b_gs2bufB3b + ((-zamdither->b_gs2bufB3b + zamdither->b_err2[i_pos]) * b_gs2cutB3); b_gs2bufB3bo = zamdither->b_gs2bufB3b;
			zamdither->b_gs3bufB3b = zamdither->b_gs3bufB3b + ((-zamdither->b_gs3bufB3b + zamdither->b_err2[i_pos]) * b_gs3cutB3); b_gs3bufB3bo = zamdither->b_gs3bufB3b;
			zamdither->b_gs4bufB3b = zamdither->b_gs4bufB3b + ((-zamdither->b_gs4bufB3b + zamdither->b_err2[i_pos]) * b_gs4cutB3); b_gs4bufB3bo = zamdither->b_gs4bufB3b;
			zamdither->b_gs5bufB3b = zamdither->b_gs5bufB3b + ((-zamdither->b_gs5bufB3b + zamdither->b_err2[i_pos]) * b_gs5cutB3); b_gs5bufB3bo = zamdither->b_gs5bufB3b;
			zamdither->b_gs1bufB3b = zamdither->b_gs1bufB3b + ((-zamdither->b_gs1bufB3b +     0) * b_gs1cutB3); b_gs1bufB3bo = b_gs1bufB3bo + zamdither->b_gs1bufB3b;
			zamdither->b_gs2bufB3b = zamdither->b_gs2bufB3b + ((-zamdither->b_gs2bufB3b +     0) * b_gs2cutB3); b_gs2bufB3bo = b_gs2bufB3bo + zamdither->b_gs2bufB3b;
			zamdither->b_gs3bufB3b = zamdither->b_gs3bufB3b + ((-zamdither->b_gs3bufB3b +     0) * b_gs3cutB3); b_gs3bufB3bo = b_gs3bufB3bo + zamdither->b_gs3bufB3b;
			zamdither->b_gs4bufB3b = zamdither->b_gs4bufB3b + ((-zamdither->b_gs4bufB3b +     0) * b_gs4cutB3); b_gs4bufB3bo = b_gs4bufB3bo + zamdither->b_gs4bufB3b;
			zamdither->b_gs5bufB3b = zamdither->b_gs5bufB3b + ((-zamdither->b_gs5bufB3b +     0) * b_gs5cutB3); b_gs5bufB3bo = b_gs5bufB3bo + zamdither->b_gs5bufB3b;
			b_of1 = (b_gs1gainB2 * b_gs1bufB2bo) - (b_gs1gainB3*b_gs1bufB3bo);
			b_of2 = (b_gs2gainB2 * b_gs2bufB2bo) - (b_gs2gainB3*b_gs2bufB3bo);
			b_of3 = (b_gs3gainB2 * b_gs3bufB2bo) - (b_gs3gainB3*b_gs3bufB3bo);
			b_of4 = (b_gs4gainB2 * b_gs4bufB2bo) - (b_gs4gainB3*b_gs4bufB3bo);
			b_of5 = (b_gs5gainB2 * b_gs5bufB2bo) - (b_gs5gainB3*b_gs5bufB3bo);
			double b_B3outb = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			zamdither->b_gs1bufB4a = zamdither->b_gs1bufB4a + ((-zamdither->b_gs1bufB4a + zamdither->b_err1[i_pos]) * b_gs1cutB4); b_gs1bufB4ao = zamdither->b_gs1bufB4a;
			zamdither->b_gs2bufB4a = zamdither->b_gs2bufB4a + ((-zamdither->b_gs2bufB4a + zamdither->b_err1[i_pos]) * b_gs2cutB4); b_gs2bufB4ao = zamdither->b_gs2bufB4a;
			zamdither->b_gs3bufB4a = zamdither->b_gs3bufB4a + ((-zamdither->b_gs3bufB4a + zamdither->b_err1[i_pos]) * b_gs3cutB4); b_gs3bufB4ao = zamdither->b_gs3bufB4a;
			zamdither->b_gs4bufB4a = zamdither->b_gs4bufB4a + ((-zamdither->b_gs4bufB4a + zamdither->b_err1[i_pos]) * b_gs4cutB4); b_gs4bufB4ao = zamdither->b_gs4bufB4a;
			zamdither->b_gs5bufB4a = zamdither->b_gs5bufB4a + ((-zamdither->b_gs5bufB4a + zamdither->b_err1[i_pos]) * b_gs5cutB4); b_gs5bufB4ao = zamdither->b_gs5bufB4a;
			zamdither->b_gs1bufB4a = zamdither->b_gs1bufB4a + ((-zamdither->b_gs1bufB4a +     0) * b_gs1cutB4); b_gs1bufB4ao = b_gs1bufB4ao + zamdither->b_gs1bufB4a;
			zamdither->b_gs2bufB4a = zamdither->b_gs2bufB4a + ((-zamdither->b_gs2bufB4a +     0) * b_gs2cutB4); b_gs2bufB4ao = b_gs2bufB4ao + zamdither->b_gs2bufB4a;
			zamdither->b_gs3bufB4a = zamdither->b_gs3bufB4a + ((-zamdither->b_gs3bufB4a +     0) * b_gs3cutB4); b_gs3bufB4ao = b_gs3bufB4ao + zamdither->b_gs3bufB4a;
			zamdither->b_gs4bufB4a = zamdither->b_gs4bufB4a + ((-zamdither->b_gs4bufB4a +     0) * b_gs4cutB4); b_gs4bufB4ao = b_gs4bufB4ao + zamdither->b_gs4bufB4a;
			zamdither->b_gs5bufB4a = zamdither->b_gs5bufB4a + ((-zamdither->b_gs5bufB4a +     0) * b_gs5cutB4); b_gs5bufB4ao = b_gs5bufB4ao + zamdither->b_gs5bufB4a;
			b_of1 = (b_gs1gainB3 * b_gs1bufB3ao) - (b_gs1gainB4*b_gs1bufB4ao);
			b_of2 = (b_gs2gainB3 * b_gs2bufB3ao) - (b_gs2gainB4*b_gs2bufB4ao);
			b_of3 = (b_gs3gainB3 * b_gs3bufB3ao) - (b_gs3gainB4*b_gs3bufB4ao);
			b_of4 = (b_gs4gainB3 * b_gs4bufB3ao) - (b_gs4gainB4*b_gs4bufB4ao);
			b_of5 = (b_gs5gainB3 * b_gs5bufB3ao) - (b_gs5gainB4*b_gs5bufB4ao);
			double b_B4outa = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			zamdither->b_gs1bufB4b = zamdither->b_gs1bufB4b + ((-zamdither->b_gs1bufB4b + zamdither->b_err2[i_pos]) * b_gs1cutB4); b_gs1bufB4bo = zamdither->b_gs1bufB4b; 
			zamdither->b_gs2bufB4b = zamdither->b_gs2bufB4b + ((-zamdither->b_gs2bufB4b + zamdither->b_err2[i_pos]) * b_gs2cutB4); b_gs2bufB4bo = zamdither->b_gs2bufB4b;
			zamdither->b_gs3bufB4b = zamdither->b_gs3bufB4b + ((-zamdither->b_gs3bufB4b + zamdither->b_err2[i_pos]) * b_gs3cutB4); b_gs3bufB4bo = zamdither->b_gs3bufB4b;
			zamdither->b_gs4bufB4b = zamdither->b_gs4bufB4b + ((-zamdither->b_gs4bufB4b + zamdither->b_err2[i_pos]) * b_gs4cutB4); b_gs4bufB4bo = zamdither->b_gs4bufB4b;
			zamdither->b_gs5bufB4b = zamdither->b_gs5bufB4b + ((-zamdither->b_gs5bufB4b + zamdither->b_err2[i_pos]) * b_gs5cutB4); b_gs5bufB4bo = zamdither->b_gs5bufB4b;
			zamdither->b_gs1bufB4b = zamdither->b_gs1bufB4b + ((-zamdither->b_gs1bufB4b +     0) * b_gs1cutB4); b_gs1bufB4bo = b_gs1bufB4bo + zamdither->b_gs1bufB4b;
			zamdither->b_gs2bufB4b = zamdither->b_gs2bufB4b + ((-zamdither->b_gs2bufB4b +     0) * b_gs2cutB4); b_gs2bufB4bo = b_gs2bufB4bo + zamdither->b_gs2bufB4b;
			zamdither->b_gs3bufB4b = zamdither->b_gs3bufB4b + ((-zamdither->b_gs3bufB4b +     0) * b_gs3cutB4); b_gs3bufB4bo = b_gs3bufB4bo + zamdither->b_gs3bufB4b;
			zamdither->b_gs4bufB4b = zamdither->b_gs4bufB4b + ((-zamdither->b_gs4bufB4b +     0) * b_gs4cutB4); b_gs4bufB4bo = b_gs4bufB4bo + zamdither->b_gs4bufB4b;
			zamdither->b_gs5bufB4b = zamdither->b_gs5bufB4b + ((-zamdither->b_gs5bufB4b +     0) * b_gs5cutB4); b_gs5bufB4bo = b_gs5bufB4bo + zamdither->b_gs5bufB4b;
			b_of1 = (b_gs1gainB3 * b_gs1bufB3bo) - (b_gs1gainB4*b_gs1bufB4bo);
			b_of2 = (b_gs2gainB3 * b_gs2bufB3bo) - (b_gs2gainB4*b_gs2bufB4bo);
			b_of3 = (b_gs3gainB3 * b_gs3bufB3bo) - (b_gs3gainB4*b_gs3bufB4bo);
			b_of4 = (b_gs4gainB3 * b_gs4bufB3bo) - (b_gs4gainB4*b_gs4bufB4bo);
			b_of5 = (b_gs5gainB3 * b_gs5bufB3bo) - (b_gs5gainB4*b_gs5bufB4bo);
			double b_B4outb = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			b_of1 = (b_gs1gainB4 * b_gs1bufB4ao) - (b_gs1gainB5*b_gs1bufB5ao);
			b_of2 = (b_gs2gainB4 * b_gs2bufB4ao) - (b_gs2gainB5*b_gs2bufB5ao);
			b_of3 = (b_gs3gainB4 * b_gs3bufB4ao) - (b_gs3gainB5*b_gs3bufB5ao);
			b_of4 = (b_gs4gainB4 * b_gs4bufB4ao) - (b_gs4gainB5*b_gs4bufB5ao);
			b_of5 = (b_gs5gainB4 * b_gs5bufB4ao) - (b_gs5gainB5*b_gs5bufB5ao);
			double b_B5outa = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			b_of1 = (b_gs1gainB4 * b_gs1bufB4bo) - (b_gs1gainB5*b_gs1bufB5bo);
			b_of2 = (b_gs2gainB4 * b_gs2bufB4bo) - (b_gs2gainB5*b_gs2bufB5bo);
			b_of3 = (b_gs3gainB4 * b_gs3bufB4bo) - (b_gs3gainB5*b_gs3bufB5bo);
			b_of4 = (b_gs4gainB4 * b_gs4bufB4bo) - (b_gs4gainB5*b_gs4bufB5bo);
			b_of5 = (b_gs5gainB4 * b_gs5bufB4bo) - (b_gs5gainB5*b_gs5bufB5bo);
			double b_B5outb = b_of1 + b_of2 + b_of3 + b_of4 + b_of5;

			zamdither->b_err1[i_pos] = (b_B1outa * b_gain1) +
					(b_B2outa * b_gain2) +
					(b_B3outa * b_gain3) +
					(b_B4outa * b_gain4) +
					(b_B5outa * b_gain5) ;

			zamdither->b_err2[i_pos] = (b_B1outb * b_gain1) +
					(b_B2outb * b_gain2) +
					(b_B3outb * b_gain3) +
					(b_B4outb * b_gain4) +
					(b_B5outb * b_gain5) ;

			zamdither->b_err1[i_pos] = zamdither->b_err1[i_pos] / b_intgain;
			zamdither->b_err2[i_pos] = zamdither->b_err2[i_pos] / b_intgain;

			}

			zamdither->b_err1[29] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19] - zamdither->b_err1[20] - zamdither->b_err1[21] - zamdither->b_err1[22] - zamdither->b_err1[23] - zamdither->b_err1[24] - zamdither->b_err1[25] - zamdither->b_err1[26] - zamdither->b_err1[27] - zamdither->b_err1[28];
			zamdither->b_err2[29] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19] - zamdither->b_err2[20] - zamdither->b_err2[21] - zamdither->b_err2[22] - zamdither->b_err2[23] - zamdither->b_err2[24] - zamdither->b_err2[25] - zamdither->b_err2[26] - zamdither->b_err2[27] - zamdither->b_err2[28];
			zamdither->b_err1[28] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19] - zamdither->b_err1[20] - zamdither->b_err1[21] - zamdither->b_err1[22] - zamdither->b_err1[23] - zamdither->b_err1[24] - zamdither->b_err1[25] - zamdither->b_err1[26] - zamdither->b_err1[27];
			zamdither->b_err2[28] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19] - zamdither->b_err2[20] - zamdither->b_err2[21] - zamdither->b_err2[22] - zamdither->b_err2[23] - zamdither->b_err2[24] - zamdither->b_err2[25] - zamdither->b_err2[26] - zamdither->b_err2[27];
			zamdither->b_err1[27] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19] - zamdither->b_err1[20] - zamdither->b_err1[21] - zamdither->b_err1[22] - zamdither->b_err1[23] - zamdither->b_err1[24] - zamdither->b_err1[25] - zamdither->b_err1[26];
			zamdither->b_err2[27] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19] - zamdither->b_err2[20] - zamdither->b_err2[21] - zamdither->b_err2[22] - zamdither->b_err2[23] - zamdither->b_err2[24] - zamdither->b_err2[25] - zamdither->b_err2[26];
			zamdither->b_err1[26] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19] - zamdither->b_err1[20] - zamdither->b_err1[21] - zamdither->b_err1[22] - zamdither->b_err1[23] - zamdither->b_err1[24] - zamdither->b_err1[25];
			zamdither->b_err2[26] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19] - zamdither->b_err2[20] - zamdither->b_err2[21] - zamdither->b_err2[22] - zamdither->b_err2[23] - zamdither->b_err2[24] - zamdither->b_err2[25];
			zamdither->b_err1[25] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19] - zamdither->b_err1[20] - zamdither->b_err1[21] - zamdither->b_err1[22] - zamdither->b_err1[23] - zamdither->b_err1[24];
			zamdither->b_err2[25] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19] - zamdither->b_err2[20] - zamdither->b_err2[21] - zamdither->b_err2[22] - zamdither->b_err2[23] - zamdither->b_err2[24];
			zamdither->b_err1[24] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19] - zamdither->b_err1[20] - zamdither->b_err1[21] - zamdither->b_err1[22] - zamdither->b_err1[23];
			zamdither->b_err2[24] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19] - zamdither->b_err2[20] - zamdither->b_err2[21] - zamdither->b_err2[22] - zamdither->b_err2[23];
			zamdither->b_err1[23] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19] - zamdither->b_err1[20] - zamdither->b_err1[21] - zamdither->b_err1[22];
			zamdither->b_err2[23] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19] - zamdither->b_err2[20] - zamdither->b_err2[21] - zamdither->b_err2[22];
			zamdither->b_err1[22] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19] - zamdither->b_err1[20] - zamdither->b_err1[21];
			zamdither->b_err2[22] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19] - zamdither->b_err2[20] - zamdither->b_err2[21];

			zamdither->b_err1[21] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19] - zamdither->b_err1[20];
			zamdither->b_err2[21] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19] - zamdither->b_err2[20];
			zamdither->b_err1[20] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18] - zamdither->b_err1[19];
			zamdither->b_err2[20] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18] - zamdither->b_err2[19];
			zamdither->b_err1[19] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17] - zamdither->b_err1[18];
			zamdither->b_err2[19] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17] - zamdither->b_err2[18];
			zamdither->b_err1[18] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16] - zamdither->b_err1[17];
			zamdither->b_err2[18] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16] - zamdither->b_err2[17];
			zamdither->b_err1[17] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15] - zamdither->b_err1[16];
			zamdither->b_err2[17] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15] - zamdither->b_err2[16];
			zamdither->b_err1[16] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] - zamdither->b_err1[15];
			zamdither->b_err2[16] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] - zamdither->b_err2[15];

			zamdither->b_err1[15] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] - zamdither->b_err1[14] ;
			zamdither->b_err2[15] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] - zamdither->b_err2[14] ;	
			zamdither->b_err1[14] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] - zamdither->b_err1[13] ;
			zamdither->b_err2[14] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] - zamdither->b_err2[13] ;	
			zamdither->b_err1[13] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] - zamdither->b_err1[12] ;
			zamdither->b_err2[13] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] - zamdither->b_err2[12] ;	
			zamdither->b_err1[12] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] - zamdither->b_err1[11] ;
			zamdither->b_err2[12] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] - zamdither->b_err2[11] ;	
			zamdither->b_err1[11] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] - zamdither->b_err1[10] ;
			zamdither->b_err2[11] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] - zamdither->b_err2[10] ;	
			zamdither->b_err1[10] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] - zamdither->b_err1[9] ;
			zamdither->b_err2[10] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] - zamdither->b_err2[9] ;	
			zamdither->b_err1[9] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] - zamdither->b_err1[8] ;
			zamdither->b_err2[9] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] - zamdither->b_err2[8] ;
			zamdither->b_err1[8] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] - zamdither->b_err1[7] ;
			zamdither->b_err2[8] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] - zamdither->b_err2[7] ;
			zamdither->b_err1[7] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] - zamdither->b_err1[6] ;
			zamdither->b_err2[7] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] - zamdither->b_err2[6] ;
			zamdither->b_err1[6] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] - zamdither->b_err1[5] ;
			zamdither->b_err2[6] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] - zamdither->b_err2[5] ;
			zamdither->b_err1[5] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] - zamdither->b_err1[4] ;
			zamdither->b_err2[5] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] - zamdither->b_err2[4] ;
			zamdither->b_err1[4] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] - zamdither->b_err1[3] ;
			zamdither->b_err2[4] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] - zamdither->b_err2[3] ;
			zamdither->b_err1[3] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] - zamdither->b_err1[2] ;
			zamdither->b_err2[3] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] - zamdither->b_err2[2] ;
			zamdither->b_err1[2] = b_aerr1 - zamdither->b_err1[0] - zamdither->b_err1[1] ;
			zamdither->b_err2[2] = b_aerr2 - zamdither->b_err2[0] - zamdither->b_err2[1] ;
			zamdither->b_err1[1] = b_aerr1 - zamdither->b_err1[0] ;
			zamdither->b_err2[1] = b_aerr2 - zamdither->b_err2[0] ;
			zamdither->b_err1[0] = b_aerr1 ;
			zamdither->b_err2[0] = b_aerr2 ;
			
			b_in1 = b_in1q;
			b_in2 = b_in2q;

			// zoom back
			b_in1 = b_in1 / b_dzoom;
			b_in2 = b_in2 / b_dzoom;

			}//else

		(*out1++) = b_in1; // output L
		(*out2++) = b_in2; // output R
	}
}

static void
deactivate(LV2_Handle instance)
{
}

static void
cleanup(LV2_Handle instance)
{
	free(instance);
}

const void*
extension_data(const char* uri)
{
	return NULL;
}

static const LV2_Descriptor descriptor = {
	ZAMDITHER_URI,
	instantiate,
	connect_port,
	activate,
	run,
	deactivate,
	cleanup,
	extension_data
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
	switch (index) {
	case 0:
		return &descriptor;
	default:
		return NULL;
	}
}

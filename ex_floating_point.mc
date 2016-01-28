/* $Id: ex01.mc,v 2.1 2005/06/14 22:16:46 jls Exp $ */

/*
 * Copyright 2005 SRC Computers, Inc.  All Rights Reserved.
 *
 *	Manufactured in the United States of America.
 *
 * SRC Computers, Inc.
 * 4240 N Nevada Avenue
 * Colorado Springs, CO 80907
 * (v) (719) 262-0213
 * (f) (719) 262-0223
 *
 * No permission has been granted to distribute this software
 * without the express permission of SRC Computers, Inc.
 *
 * This program is distributed WITHOUT ANY WARRANTY OF ANY KIND.
 */

#include <libmap.h>


int32_t comp (int64_t a);

void subr (int64_t f_arr[], double d_arr[], int64_t f_res[], double d_res[], int m, int64_t *time, int mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, double, MAX_OBM_SIZE)
    OBM_BANK_C (CL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_D (DL, double, MAX_OBM_SIZE)
    int i;
    float f0, f1, r0, r1;
    int64_t t0, t1;


    buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe (1,"A"), f_arr, 1, m/2*8);
    buffered_dma_cpu (CM2OBM, PATH_0, BL, MAP_OBM_stripe (1,"B"), d_arr, 1, m*8);


    read_timer (&t0);


    for (i=0; i<m; i++) {
    split_64to32_flt_flt (AL[i], &f0, &f1);
    r0 = f0 + 17;
    r1 = f1 + 17;
    comb_32to64_flt_flt (r0, r1, &CL[i]);
    DL[i] = BL[i] + 34;
    }

    read_timer (&t1);
    *time = t1 - t0;




    buffered_dma_cpu (OBM2CM, PATH_0, CL, MAP_OBM_stripe (1,"C"), f_res, 1, m/2*8);
    buffered_dma_cpu (OBM2CM, PATH_0, DL, MAP_OBM_stripe (1,"D"), d_res, 1, m*8);

}

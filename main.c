static char const cvsid[] = "$Id: main.c,v 2.2 2005/06/27 16:56:56 hammes Exp $";

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
#include <stdlib.h>


void subr (float f_arr[], double d_arr[], float f_res[], double d_res[], int m, int64_t *tm, int mapnum);


int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, num;
    float *F_src, *F_res;
    double *D_src, *D_res;
    int64_t tm;
    int mapnum = 0;

    if ((res_map = fopen ("res_map.flt", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_map.flt'\n");
        exit (1);
        }

    if ((res_cpu = fopen ("res_cpu.flt", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_cpu.flt'\n");
        exit (1);
        }

    if (argc < 2) {
	fprintf (stderr, "need number of elements as arg\n");
	exit (1);
	}

    if (sscanf (argv[1], "%d", &num) < 1) {
	fprintf (stderr, "need number of elements as arg\n");
	exit (1);
	}

    if ((num < 1) || (num > MAX_OBM_SIZE)) {
        fprintf (stderr, "number of elements must be in the range 1 through %d\n", MAX_OBM_SIZE);
	exit (1);
	}

    if (num & 0x1) {
        fprintf (stderr, "number of elements must be even\n");
	exit (1);
	}

    F_src = (float*) malloc (num * sizeof (float));
    F_res = (float*) malloc (num * sizeof (float));
    D_src = (double*) malloc (num * sizeof (double));
    D_res = (double*) malloc (num * sizeof (double));

    srandom (99);

    for (i=0; i<num; i++) {
        F_src[i] = (float)random() / random();
        D_src[i] = (double)random() / random();
	fprintf (res_cpu, "%i %10.4f %lf\n", i, F_src[i]+17, D_src[i]+34);
	}

    map_allocate (1);

    subr (F_src, D_src, F_res, D_res, num, &tm, mapnum);

    printf ("%lld clocks\n", tm);

    for (i=0; i<num; i++)
	fprintf (res_map, "%i %10.4f %lf\n", i, F_res[i], D_res[i]);

    map_free (1);

    exit(0);
    }


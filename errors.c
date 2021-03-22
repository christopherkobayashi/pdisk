//
// errors.c - error & help routines
//
// Written by Eryk Vershen
//

/*
 * Copyright 1996,1997,1998 by Apple Computer, Inc.
 *              All Rights Reserved 
 *  
 * Permission to use, copy, modify, and distribute this software and 
 * its documentation for any purpose and without fee is hereby granted, 
 * provided that the above copyright notice appears in all copies and 
 * that both the copyright notice and this permission notice appear in 
 * supporting documentation. 
 *  
 * APPLE COMPUTER DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE. 
 *  
 * IN NO EVENT SHALL APPLE COMPUTER BE LIABLE FOR ANY SPECIAL, INDIRECT, OR 
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT, 
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION 
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
 */

// for *printf()
#include <stdio.h>
#include <errno.h>

#include <stdlib.h>
#include <string.h>

// for va_start(), etc.
#include <stdarg.h>

#include "errors.h"
#include "cmdline.h"


//
// Defines
//


//
// Types
//


//
// Global Constants
//


//
// Global Variables
//
char *program_name;


//
// Forward declarations
//


//
// Routines
//
void
init_program_name(char **argv)
{
    if ((program_name = strrchr(argv[0], '/')) != (char *)NULL) {
	program_name++;
    } else {
	program_name = argv[0];
    }
}


void
do_help()
{
    fprintf(stderr, "usage:");
    fprintf(stderr, "\t%s [-h|--help]\n", program_name);
    fprintf(stderr, "\t%s [-i|--interactive]\n", program_name);
    fprintf(stderr, "\t%s [-l|--list] [name] [...]\n", program_name);
    fprintf(stderr, "\t%s [-r|--readonly] name [...]\n", program_name);
    fprintf(stderr, "\t%s [-v|--version]\n", program_name);
    fprintf(stderr, "\t%s name [...]\n", program_name);
    fprintf(stderr, "\t%s name command\n", program_name);
/*
	{"debug",	no_argument,		0,	'd'},
	{"abbr",	no_argument,		0,	'a'},
	{"fs",		no_argument,		0,	'f'},
	{"logical",	no_argument,		0,	kLogicalOption},
	{"compute_size", no_argument,		0,	'c'},
*/
    fprintf(stderr, "\n");
    do_command_help();
}


void
usage(const char *kind)
{
    error(-1, "bad usage - %s\n", kind);
    hflag = 1;
}


//
// Print a message on standard error and exit with value.
// Values in the range of system error numbers will add
// the perror(3) message.
//
void
fatal(int value, const char *fmt, ...)
{
    va_list ap;

    fprintf(stderr, "%s: ", program_name);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    if (value > 0) {
	fprintf(stderr, "  (%s)\n", strerror(value));
    } else {
	fprintf(stderr, "\n");
    }
    exit(value);
}


//
// Print a message on standard error.
// Values in the range of system error numbers will add
// the perror(3) message.
//
void
error(int value, const char *fmt, ...)
{
    va_list ap;

    fprintf(stderr, "%s: ", program_name);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    if (value > 0) {
	fprintf(stderr, "  (%s)\n", strerror(value));
    } else {
	fprintf(stderr, "\n");
    }
}

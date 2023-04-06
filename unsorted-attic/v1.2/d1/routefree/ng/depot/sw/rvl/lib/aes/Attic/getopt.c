/*******************************************************************************
 * 
 *   (C) 2000 ARTX INC..  ALL RIGHTS RESERVED.  UNPUBLISHED -- RIGHTS
 *   RESERVED UNDER THE COPYRIGHT LAWS OF THE UNITED STATES.  USE OF A
 *   COPYRIGHT NOTICE IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 *   OR DISCLOSURE.
 *
 *   THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF
 *   ARTX INC..  USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED WITHOUT
 *   THE PRIOR EXPRESS WRITTEN PERMISSION OF ARTX INC..
 *
 *                   RESTRICTED RIGHTS LEGEND
 *
 *   Use, duplication, or disclosure by the Government is subject to
 *   restrictions as set forth in subparagraph (c)(1)(ii) of the Rights
 *   in Technical Data and Computer Software clause at DFARS 252.227-7013
 *   or subparagraphs (c)(1) and (2) of Commercial Computer Software --
 *   Restricted Rights at 48 CFR 52.227-19, as applicable. 
 *
 *   ArtX Inc.
 *   3400 Hillview Ave, Bldg 5
 *   Palo Alto, CA 94304
 *
 ******************************************************************************/


#include <getopt.h>

char *optarg;
int   optind;

#define isalnum(x)      (((x >= 'a') && (x <= 'z')) || \
                         ((x >= 'A') && (x <= 'Z')) || \
                         ((x >= '0') && (x <= '9')))

int
getopt(int ac, char *av[], char *opts)
{
    static int first = 1;
    static int kind;
    char *op;
    int c;

    if ( first ) {
        first = 0;
        kind = 1;
    }

    optind = kind;

    if ( kind >= ac ) {
        return 0;
    }

    // all done
    if ( *av[kind] != '-' ) {
        return 0;
    }
    
    c = av[kind][1];

    if ( !isalnum(c) ) {
        kind++;
        return '?';
    }

    // look for the option
    for( op = opts ; *op && (c != *op) ; op++ ) {
    }

    // unknown option
    if ( *op == '\0' ) {
        kind++;
        return '?';
    }

    // return the optional arg
    if ( op[1] == ':' ) {
        if ( (kind + 1) >= ac ) {
            return '?';
        }
        optarg = av[kind+1];
        kind += 2;
    }
    else {
        kind++;
    }

    return c;
}

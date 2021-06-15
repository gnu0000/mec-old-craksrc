/*
 *
 * lk.c
 * Wednesday, 8/20/1997.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gnutype.h>
#include <gnumisc.h>

CHAR szBuff [11000];

int _cdecl main (int argc, char *argv[])
   {
   FILE   *fp;
   USHORT i, uLen, *pu;
   ULONG  ulAddr, ul6, ul4;

   if (!(fp = fopen (argv[1], "rb")))
      Error ("Cant open input file (param #1)");

   uLen = 0;
   ul6 = ul4 = 0;
   for (ulAddr=0; TRUE; ulAddr+=uLen)
      {
      if (!(uLen = fread (szBuff, 1, 10240, fp)))
         break;

      for (i=0; i<uLen; i++)
         {
         pu = (PUINT)(PVOID)(szBuff+i);
         if (*pu == 640)
            {
            ul6 = ulAddr+i;
            printf ("%8.8lx : 02 80 (%8lx)\n", ul6, ul6-ul4);
            }
         if (*pu == 480)
            {
            ul4 = ulAddr+i;
            printf ("%8.8lx : 01 E0 (%8lx)\n", ul4, ul4-ul6);
            }
         if ((i+1 == uLen) && (*pu==256 || *pu==512))
            printf ("Warning!\n");
         }
      }
   return 0;
   }


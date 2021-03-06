#include <stdio.h>
#include "constants.h"
#include "macros.h"
// START FUNC DECL
int
pos_sel_copy___XTYPE1_____XTYPE2__(
    __ITYPE1__ *f1, 
    long long nR1, 
    __ITYPE2__ *f2, 
    long long nR2, 
    __ITYPE1__ lb,
    __ITYPE1__ ub,
    __ITYPE1__ *f3,
    long long *ptr_cnt
    )
// STOP FUNC DECL
{
  int status = 0;
  long long cnt = 0;
  long long i3 = 0;
  for ( long long i2 = 0; i2 < nR2; i2++ ) {
    __ITYPE2__ f1idx = f2[i2];
    if ( ( f1idx < 0 ) || ( f1idx >= nR1 ) ) { go_BYE(-1); }
    __ITYPE1__ val = f1[f1idx];
    if ( ( val >= lb ) && ( val <= ub ) ) {
      f3[i3++] = val;
      cnt++;
    }
  }
  *ptr_cnt = cnt;
BYE:
  return(status);
}


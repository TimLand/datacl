// START FUNC DECL
void
nn_f_to_s___XOP_____XTYPE__(
    __ITYPE__ *X,
    char *nn_X,
    long long nX,
    long long *ptr_cnt,
    __ITYPE__ *ptr_rslt
    )
// STOP FUNC DECL
{
  __ITYPE__ rslt = *ptr_rslt;
  long long cnt = *ptr_cnt;
  for ( long long i = 0; i < nX; i++ ) { 
    if ( nn_X[i] == 0 ) { continue; }
    if ( X[i] __IOP__ rslt ) {
      rslt = X[i];
    }
    cnt++;
  }
  *ptr_rslt = rslt;
  *ptr_cnt  = cnt;
}

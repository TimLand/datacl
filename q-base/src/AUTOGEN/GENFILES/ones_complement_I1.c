// START FUNC DECL
void
ones_complement_I1( 
			    char *in, 
			    int nR, 
			    char * restrict out
			    )
// STOP FUNC DECL
{
  for ( long long i = 0; i < nR; i++ ) { 
    *out++ = ~ (*in); in++;
  }
}


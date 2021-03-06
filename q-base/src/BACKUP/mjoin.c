#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include "constants.h"
#include "macros.h"
#include "qtypes.h"
#include "sqlite3.h"
#include "fsize.h"
#include "auxil.h"
#include "dbauxil.h"
#include "fld_meta.h"
#include "aux_fld_meta.h"
#include "add_fld.h"
#include "add_aux_fld.h"
#include "bin_search.h"
#include "sort.h"
#include "mjoin.h"
#include "mjoin_int.h"
#include "mjoin_longlong.h"
#include "get_nR.h"
#include "aux_join.h"

//---------------------------------------------------------------
int 
mjoin(
      char *docroot,
      sqlite3 *in_db,
      char *src_tbl,
      char *src_lnk,
      char *src_fld,
      char *dst_tbl,
      char *dst_lnk,
      char *dst_fld,
      char *op
      )
{
  int status = 0;
  sqlite3 *db = NULL;
  char *src_fld_X = NULL; size_t src_fld_nX = 0;
  char *src_lnk_X = NULL; size_t src_lnk_nX = 0;
  char *dst_lnk_X = NULL; size_t dst_lnk_nX = 0;
  FLD_META_TYPE src_fld_meta, src_lnk_meta;
  FLD_META_TYPE nn_src_fld_meta, nn_src_lnk_meta;
  FLD_META_TYPE dst_lnk_meta;
  FLD_META_TYPE nn_dst_lnk_meta;
  long long src_nR, dst_nR;
  char str_meta_data[256];
  char *nn_dst_fld = NULL;
  int imjoin_op;
  bool is_any_null; char *nn_opfile = NULL;
  char *nn_src_fld_X = NULL; size_t nn_src_fld_nX = 0;
  char *nn_src_lnk_X = NULL; size_t nn_src_lnk_nX = 0;
  char *nn_dst_lnk_X = NULL; size_t nn_dst_lnk_nX = 0;
  //----------------------------------------------------------------
  zero_string(str_meta_data, 256);
  status = mk_mjoin_op(op, &imjoin_op);
  cBYE(status);
  //----------------------------------------------------------------
  status = join_prep(docroot, in_db, src_tbl, src_lnk, src_fld, dst_tbl, 
      dst_lnk, dst_fld, &src_fld_meta, &src_lnk_meta, &nn_src_fld_meta,
	&nn_src_lnk_meta, &dst_lnk_meta, &nn_dst_lnk_meta, &src_nR,
	&dst_nR, &src_fld_X, &src_fld_nX, &src_lnk_X, &src_lnk_nX,
	&nn_src_fld_X, &nn_src_fld_nX, &nn_src_lnk_X, &nn_src_lnk_nX,
	&dst_lnk_X, &dst_lnk_nX, &nn_dst_lnk_X, &nn_dst_lnk_nX);
  cBYE(status);
  //--------------------------------------------------------
  if ( strcmp(src_lnk_meta.fldtype, "int") == 0 ) { 
    // Source field must be integer and link fields must be integer
    if ( strcmp(dst_lnk_meta.fldtype, "int") != 0 ) { go_BYE(-1); }
    if ( strcmp(src_fld_meta.fldtype, "int") != 0 ) { go_BYE(-1); }
    /* Source fldtype = destination fldtype */
    sprintf(str_meta_data, "fldtype=int:n_sizeof=4:filename=");
    status = mjoin_int( src_fld_X, src_lnk_X, dst_lnk_X, nn_src_fld_X,
	  nn_src_lnk_X, nn_dst_lnk_X, src_nR, dst_nR, &is_any_null,
	  str_meta_data, &nn_opfile, imjoin_op);
    cBYE(status);
  }
  else if ( strcmp(src_lnk_meta.fldtype, "long long") == 0 ) { 
    // Source field must be long long and link fields must be integer
    if ( strcmp(dst_lnk_meta.fldtype, "long long") != 0 ) { go_BYE(-1); }
    if ( strcmp(src_fld_meta.fldtype, "long long") != 0 ) { go_BYE(-1); }
    /* Source fldtype = destination fldtype */
    sprintf(str_meta_data, "fldtype=long long:n_sizeof=8:filename=");
    status = mjoin_longlong( src_fld_X, src_lnk_X, dst_lnk_X, nn_src_fld_X,
	  nn_src_lnk_X, nn_dst_lnk_X, src_nR, dst_nR, &is_any_null,
	  str_meta_data, &nn_opfile, imjoin_op);
    cBYE(status);
  }
  else {
    go_BYE(-1);
  }

  // Add output field to meta data 
  status = add_fld(docroot, db, dst_tbl, dst_fld, str_meta_data);
  cBYE(status);
  if ( is_any_null == true ) {
    status = add_aux_fld(docroot, db, dst_tbl, dst_fld, nn_opfile, "nn");
    cBYE(status);
  }
  else {
    unlink(nn_opfile);
  }
 BYE:
  if ( in_db == NULL ) { sqlite3_close(db); }
  rs_munmap(src_fld_X, src_fld_nX);
  rs_munmap(src_lnk_X, src_lnk_nX);
  rs_munmap(dst_lnk_X, dst_lnk_nX);

  free_if_non_null(nn_dst_fld);
  free_if_non_null(nn_opfile);

  rs_munmap(nn_src_fld_X, nn_src_fld_nX);
  rs_munmap(nn_src_lnk_X, nn_src_lnk_nX);
  rs_munmap(nn_dst_lnk_X, nn_dst_lnk_nX);
  return(status);
}

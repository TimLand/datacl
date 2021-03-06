/*
© [2013] LinkedIn Corp. All rights reserved.
Licensed under the Apache License, Version 2.0 (the "License"); you may
not use this file except in compliance with the License. You may obtain
a copy of the License at  http://www.apache.org/licenses/LICENSE-2.0
 
Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an "AS IS"
BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
implied.
*/
extern int set_min_max_sum(
		    const char *attr, 
		    const char *value, 
		    int fld_id
		    )
;
//----------------------------
extern int
int_set_meta(
	     int tbl_id,
	     int fld_id,
	     const char *attr,
	     const char *value,
	     bool is_internal
	     )
;
//----------------------------
extern int
set_meta(
	 const char *tbl,
	 const char *fld,
	 const char *attr,
	 const char *value
	 )
;
//----------------------------

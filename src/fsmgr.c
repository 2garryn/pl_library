#include "fsmgr.h"
#include "syscalls.c"



FRESULT fr;
FATFS fs;
FIL index_file;
FIL size_file;



void init_fsmgr() {
  //mount fs
  
  fr = f_mount(&fs, "", 1);

  //return if error
  if (fr != FR_OK) {
    RET_ERROR(tFATFS, fr);
  };
  
  //try toi update index of files
  update_index();

  //return if error happened
  RET_ON_PREV_ERROR;

  //return ok
  RET_OK(tFATFS);

};


void update_index() {

  
};


void read_file_system(char * current_path) {
  char   path[2048];
  FILINFO fno;
  DIR dir;
  int i;
  char *fn;   /* This function is assuming non-Unicode cfg. */
  char toprint[1024];
  // we need to work on new path, otherwise will get all thrash in current_path
  strcpy(path, current_path);

  static char lfn[_MAX_LFN + 1];   /* Buffer to store the LFN */
  fno.lfname = lfn;
  fno.lfsize = sizeof lfn;
  //try to open directory
  fr = f_opendir(&dir, path); 
  // if it is no ok, return error of fatfs
  if (fr != FR_OK) {
    RET_ERROR(tFATFS, fr);
  };
  i = strlen(path);
  
  for (;;) {
    fr = f_readdir(&dir, &fno);                   /* Read a directory item */
    if (fr != FR_OK) {      /* Break on error or end of dir */
      f_closedir(&dir);  
      RET_ERROR(tFATFS, fr);
    };
    
    if (fno.fname[0] == 0) {
      f_closedir(&dir);
      RET_OK(tFATFS);
    };

    if (fno.fname[0] == '.') continue; 
    fn = *fno.lfname ? fno.lfname : fno.fname;
    if (fno.fattrib & AM_DIR) {                    /* It is a directory */

      sprintf(&path[i], "/%s", fn);

      // make recursive
      read_file_system(path);
      // if scan_files return error or end of dir

      if (IS_ERROR) {
	f_closedir(&dir); 
       	RET_ON_PREV_ERROR;
      };

      path[i] = 0;
    } else {                                       /* It is a file. */

      memset(toprint, 0, 1024);
      sprintf(toprint, "file: %s/%s\n\r", path, fn);
      print_msg(toprint);
      
    };
  };
};




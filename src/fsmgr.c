#include "emgr.h"
#include "fsmgr.h"
#include "ff.h"




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

  //return if index is not update
  RET_ON_PREV_ERROR;

};


void update_index() {
  
};

/* void read_file_system(char * path) { */
/*   FRESULT res; */
/*   FILINFO fno; */
/*   DIR dir; */
/*   int i; */
/*   char *fn;   /\* This function is assuming non-Unicode cfg. *\/ */
  
/*   static char lfn[_MAX_LFN + 1];   /\* Buffer to store the LFN *\/ */
/*   fno.lfname = lfn; */
/*   fno.lfsize = sizeof lfn; */
  
/*   res = f_opendir(&dir, path);                       /\* Open the directory *\/ */
  
/*   if (res == FR_OK) { */
/*         i = strlen(path); */
/*         for (;;) { */
/*             res = f_readdir(&dir, &fno);                   /\* Read a directory item *\/ */
/*             if (res != FR_OK || fno.fname[0] == 0) break;  /\* Break on error or end of dir *\/ */
/*             if (fno.fname[0] == '.') continue;             /\* Ignore dot entry *\/ */

/*             fn = *fno.lfname ? fno.lfname : fno.fname; */

/*             if (fno.fattrib & AM_DIR) {                    /\* It is a directory *\/ */
/*                 sprintf(&path[i], "/%s", fn); */
/*                 res = scan_files(path); */
/*                 if (res != FR_OK) break; */
/*                 path[i] = 0; */
/*             } else {                                       /\* It is a file. *\/ */
/*                 printf("%s/%s\n", path, fn); */
/*             } */
/*         } */
/*         f_closedir(&dir) */
/*     } */

/*     return res; */
/* }; */

void read_file_system(char * path) {
  FILINFO fno;
  DIR dir;
  int i;
  char *fn;   /* This function is assuming non-Unicode cfg. */
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
    if (fr != FR_OK || fno.fname[0] == 0) {      /* Break on error or end of dir */
      f_closedir(%dir);  
      RET_ERROR(tFATFS, fr);
    };
    
    if (fno.fname[0] == '.') continue; 
    fn = *fno.lfname ? fno.lfname : fno.fname;
    
    if (fno.fattrib & AM_DIR) {                    /* It is a directory */
      sprintf(&path[i], "/%s", fn);
      // make recursive
      scan_files(path);
      // if scan_files return error or end of dir
      if (IS_ERROR) {
	f_closedir(%dir); 
	RET_ON_PREV_ERROR;
      };

      path[i] = 0;
    } else {                                       /* It is a file. */
      // TODO: insert sending file name to UART
      printf("%s/%s\n", path, fn);
    }
  };

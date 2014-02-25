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

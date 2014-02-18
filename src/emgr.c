#include "emgr.h"
#include <stdio.h>

extern emgr_err_struct emgr_struct;

void init_emgr(){
  //Initialization code
  emgr_reset( &emgr_struct );


};

void emgr_error1(emgr_err_struct * estruct, emgr_err_type type, uint8_t code, char * desc) {
  estruct->is_error = ERROR;
  estruct->type = type;
  estruct->code = code;
  memcpy(estruct->desc, desc, sizeof(char) * DESC_SIZE);
  //  estruct->desc = desc;
};

void emgr_error2(emgr_err_struct * estruct, emgr_err_type type, uint8_t code){
  estruct->is_error = ERROR;
  estruct->type = type;
  estruct->code = code;
  memset(estruct->desc, 0, sizeof(estruct->desc));
};


// make ok result
void emgr_ok(emgr_err_struct * estruct, emgr_err_type type){
  estruct->is_error = OK;
  estruct->type = type;
  estruct->code = 0;
  memset(estruct->desc, 0, sizeof(estruct->desc));
};
  
// test result on error
uint8_t emgr_is_error(emgr_err_struct * estruct){
  if (estruct->is_error == ERROR){
    return TRUE;
  }
  else {
    return FALSE;
  };
};

// test result on ok
uint8_t emgr_is_ok(emgr_err_struct * estruct){
  if (estruct->is_error == OK){
    return TRUE;
  }
  else {
    return FALSE;
  };
};

void emgr_reset(emgr_err_struct * estruct) {
  estruct->is_error = UNDEFINED;;
  estruct->type = tUndefined;;
  estruct->code = 0;
  memset(estruct->desc, 0, sizeof(estruct->desc));
}

//print result to somewhere
void emgr_print(emgr_err_struct * estruct){
#ifdef __DEBUG_MODE

#endif
};

void emgr_print_ffl(emgr_err_struct * estruct, const char * File, const char * Func,  int L){
#ifdef __DEBUG_MODE

  printf("is_error:%d type:%d code:%d File:%s Func:%s Line:%d\n",
	 estruct->is_error, estruct->type, estruct->code, File, Func,  L);
#endif
};

#include <stdio.h>
#include <emgr.h>

void test(int);
void check_on_test();

int main() {
 
  check_on_test();
  //  printf("Returned from test: %d\n", emgr_is_ok(&emgr_struct));
  return 0;

};

void check_on_test() {
  test(2);
  RET_ON_PREV_ERROR;
  printf("HUHASD UHASD ");
};


void test(int i){
  if (i == 1) {
    printf("Return ok from test\n");
    RET_OK(tFATFS);
    printf("Should not be printed from test\n");
  }
  else {
    printf("Return nothing from test\n");
    RET_ERROR(tFSMGR, 1);
  }
};
    
    
  
  
  

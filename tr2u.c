#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* from = "";
char* to = "";

int main(int argc, char* argv[]){
  if(argc != 3){
    printf("%s\n", "Error: Incorrect number of arguments");
    exit(1);
  }
  if(strlen(argv[1]) != strlen(argv[2])){
    printf("%s\n", "Error: Mismatched argument lengths");
    exit(1);
  }
  int i = 0;
  for(i;i<strlen(argv[1]);i++){
    if(strchr(argv[1],argv[1][i])!=strrchr(argv[1],argv[1][i])){
      printf("%s\n","Error: Ambiguous from argument");
      exit(1);
    }
  }
  char c;
  int j;
  ssize_t var = read(0,&c,1);
  ssize_t var2;
  while(var>0){
    j = 0;
    for(;j<strlen(argv[1]);j++){
      if(c == argv[1][j]){
	c = argv[2][j];
	break;
      }
    }
    var2 = write(1,&c,1);
    if(var2==-1){
      printf("%s\n","Error: Cannot write to stdout");
      exit(1);
    }
    var = read(0,&c,1);
  }
}

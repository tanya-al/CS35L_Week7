#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* from = "";
char* to = "";

int main(int argc, char* argv[]){
  if(argc != 3){
    fprintf(stderr, "%s\n", "Error: Incorrect number of arguments");
    exit(1);
  }
  if(strlen(argv[1]) != strlen(argv[2])){
    fprintf(stderr, "%s\n", "Error: Mismatched argument lengths");
    exit(1);
  }
  int i = 0;
  for(i;i<strlen(argv[1]);i++){
    if(strchr(argv[1],argv[1][i])!=strrchr(argv[1],argv[1][i])){
	fprintf(stderr,"%s\n","Error: Ambiguous from argument");
	exit(1);
    }
  }
  char c;
  int j;
  do{
    c = getchar();
    if(c == EOF){
      break;
    }
    j = 0;
    for(j;j<strlen(argv[1]);j++){
      if(c == argv[1][j]){
	c = argv[2][j];
	break;
      }
    }
    putchar(c);
  }
  while(c != EOF);
}

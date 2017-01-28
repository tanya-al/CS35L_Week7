#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int numCompare = 0;

int frobcmp(char const * a, char const * b){
  int y = 0, z = 0;
  while(a[y] != ' ' && b[z] != ' '){
    if((a[y]^42) > (b[z]^42)){
      return 1;
    }
    else if((a[y]^42) < (b[z]^42)){
      return -1;
    }
    y++;
    z++;
  }
  if(a[y]!=' '){
    return 1;
  }
  else if(b[z]!=' '){
    return -1;
  }
  else{
    return 0;
  }
}

int compare(void const * a, void const * b){
  numCompare+=1;
  return frobcmp(*(char const **)a, *(char const **) b);
}

int main(){
  struct stat fileStat;
  fstat(0, &fileStat);
  
  int i=1;
  int j=0;
  int k=0;

  int s = 0;
  int size = 0;
  int wordnum = 0;
  int charnum = 0;
  char t;
  char * total;
  
  if(S_ISREG(fileStat.st_mode)){
    size = fileStat.st_size;
    total = (char *)malloc(size);
    ssize_t r = read(0,&t,sizeof(char));
    while(r>0){
      if(((charnum+1)*sizeof(char))>size){
	size = (charnum+1)*sizeof(char);
	total=(char*)realloc(total,size);
      }
      total[charnum]=t;
      charnum++;
      r = read(0,&t,sizeof(char));
    }
  }
  else{
    total = (char *)malloc(1);
    ssize_t r = read(0,&t,sizeof(char));
    while(r>0){
      size = (charnum+1)*sizeof(char);
      total=(char*)realloc(total,size);
      total[charnum]=t;
      charnum++;
      r = read(0,&t,sizeof(char));
    }
  }
  if(size==0){
    
  }
  else{
  char* * order = (char* *)malloc(sizeof(char*));
  order[0]=total;
  wordnum++;
  for(i=1; i<charnum-1; i++){
    if(total[i]==' '){
      int resize = (wordnum+1)*sizeof(char*);
      order=(char**)realloc(order,resize);
      order[wordnum]=&total[i+1];
      wordnum++;
    }
  }
  char* val = total;
  int check = charnum;
  for(check=charnum;total[check]!=' ';check--){
    s++;
    val = &total[check];
  }

  qsort(order, wordnum, sizeof(char*), compare);
  char w;
  char space = ' ';
  for(j=0; j<wordnum; j++){
    for(k=0; order[j][k]!=' ';k++){
      if(order[j]!=val || (order[j]==val && k<s-1)){
	w = order[j][k];
	write(1,&w,sizeof(char));
      }
      else{
	break;
      }
    }
    write(1,&space,sizeof(char));
  }
  free(order);
  }
  free(total);
  fprintf(stderr,"\n%s%d\n","Comparisons: ",numCompare);
}

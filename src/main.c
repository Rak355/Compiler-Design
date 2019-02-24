#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <commons.h>

extern void lexer();

char *buffer;

FILE *obj_file;


char *file_name;
long file_size;
struct stat fileStat;

int main(){
  printf("\n|------------------------------|\n");
  file_name = "src_file.c";

  int file = open(file_name,O_RDONLY);

  fstat(file,&fileStat);
  file_size = fileStat.st_size;
  buffer = (char*)malloc(file_size);
  //printf("File size: %ld\n",file_size);

  obj_file = fopen(file_name,"rb");
  fread(buffer,sizeof(char),file_size,obj_file);
  /************************************************/
  lexer();
  printf("\n");
  return 0;
}

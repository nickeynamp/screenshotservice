#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
  FILE *urls= fopen("URLs.txt","r+");
  

  char *buffer=NULL;
  size_t size =0;
  
  while(1){
    int check = getline(&buffer,&size,urls);    
    if(check ==-1){ printf("End of file"); break;}
    
    printf("Current URL is: %s",buffer);
  }
  free(buffer);
  fclose(urls);
}

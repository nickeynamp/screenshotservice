#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]){
  if(argc>2) perror("Too many arguments");
  
  //opening the file with URLs and read every URL
  FILE *urls=fopen("URLs.txt","r+");
  char *buffer=NULL;
  size_t size=0;
  while(1){
    int err =getdelim(&buffer,&size,',',urls);
    if(err==-1) break;
    if(buffer[strlen(buffer)-1]== ',') buffer[strlen(buffer)-1]='\0';
    printf("This URL is: %s\n",buffer);

    //getting data from this URL and store this into a link(TCP client)
    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype = SOCK_STREAM; //TCP
    
    int err1= getaddrinfo(buffer, "80", &hints, &result);
    if(err1!=0){
      fprintf(stderr,"getaddrinfo:%s\n",gai_strerror(err1));
      exit(1);
    }

    int sock_fd = socket(result->ai_family,result->ai_socktype,0);
    connect(sock_fd,result->ai_addr,result->ai_addrlen);
    
    char *request="GET / HTTP/1.1\r\n\r\n";
    printf("SENDING: %s", request);
    printf("+++++++++++++++++++++++++++++++++++\n");
    write(sock_fd, request, strlen(request));
   
    char resp[1000];
    int len = read(sock_fd, &resp,999);
    resp[len]= '\0';
    printf("%s\n",resp);

    //convert the bitmap data to image and store images in current directory
    
  }
  free(buffer);
  fclose(urls);
  return 0;
}

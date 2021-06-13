#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 3072
#include "commands.h"
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#include <fcntl.h>
void *connection_handler(void *);

void download_file(int sockfd,char *fname){
    int n;
  FILE *fp;
        fp = fopen(fname, "w");        

    char buffer[SIZE];
    while (1) {

      n = recv(sockfd, buffer, SIZE, 0);
      fprintf(fp,"%s",buffer);
    
      if (n <= 0){
        fclose(fp);
        return;
      }
    bzero(buffer, SIZE);
  }

  return;
}

void list_files(char *files, int size){
         DIR *d;
    struct dirent *dir;
    int used =0;
    d = opendir("./");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
        if(size >= used)
           used += snprintf(files+used, size-used,"%s\n", dir->d_name);
        }
        closedir(d);
    
    }
    

}

void send_file(FILE *fp, int sockfd){
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (write(sockfd, &data, sizeof(data)) == -1) {
    	perror("Could not send the file\n");
      exit(1);
    }
    bzero(data, SIZE);
  }
  printf("File Sent!!\n");
}




int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;
    
  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("error occured during socket");
    return 1;
  }
  printf("Server socket created successfully\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("error occured during bind");
    return 2;
  }
  printf("Binding successfull.\n");

  if(listen(sockfd, 1) == 0){
		printf("Listening: \n");
	}else{
		perror("Error in listening");
    return 3;
	}

 

  while(1){
    addr_size = sizeof(new_addr);
  	pthread_t thread_id;
        new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
        puts("Connection accepted!\n");
        if(new_sock <0){
         perror("error occured during accept");
        return 3;
        }
         
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
                 pthread_detach(thread_id);    

     
     
  }

  

    

  return 0;
}



void *connection_handler(void *socket_desc)
{
  

    FILE *fp;
    int new_sock = *(int*)socket_desc;
     char buffer[SIZE];
	  struct messages_st msg;
    char fname [128]; 
    read(new_sock, &msg, sizeof(struct messages_st));
    
    strcpy(fname,msg.filename);
    if(msg.type == cmd_upload){
        download_file(new_sock,fname);
    }else if (msg.type == cmd_list){
    list_files(buffer,sizeof(buffer));

    write(new_sock, buffer, strlen(buffer));
    bzero(buffer, sizeof(buffer));
    }else if (msg.type == cmd_receive){
        fp = fopen(fname, "r");
        if (fp == NULL) {
        perror("Error in reading file.");
        exit(1);
        }

        send_file(fp,new_sock);
    }
  
         close(new_sock);
    return NULL;
} 
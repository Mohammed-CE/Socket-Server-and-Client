#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "commands.h"
#include <ctype.h>

#define SIZE 3072


void send_file(FILE *fp, int sockfd){
  char data[SIZE] = {0};


  while(fgets(data, SIZE, fp) != NULL)
    if (write(sockfd, &data, sizeof(data)) == -1) {
    	perror("Could not send the file\n");
      exit(1);
    }
  
  printf("File Sent!!\n");
}


void download_file(int sockfd,char *fname){

  int n;
  FILE *fp;
  char *filename = fname;
  char buffer[SIZE];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
        fprintf(fp, "%s", buffer);
    if (n <= 0){
      return;
    }
    bzero(buffer, SIZE);
  }
  return;
}

int main(){
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;
    char buffer[SIZE];

    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
      perror("Error in socket");
      exit(1);
    }
    printf("Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
      if(e == -1) {
      perror("Error in socket");
      exit(1);
    }
    struct messages_st msg;
    
    printf("Connected to Server.\n");
	  printf("Choose operation: \n");
	  printf("1) Upload files\n2) List files\n3) Download a file\n");
	  int s;
    char fname [30];

	  scanf("%d", &s);
    switch(s) {
		  case 1 :
        printf("Enter the file name: ");
        scanf("%s",fname);

        msg.type = cmd_upload;
	      msg.size = SIZE;
        strcpy(msg.filename, fname);
        write(sockfd, &msg, sizeof(struct messages_st));
			  fp = fopen(fname, "r");
        if (fp == NULL) {
          perror("Error in reading file.");
          exit(1);
        }
        send_file(fp, sockfd);
			break;
		case 2 :
    		msg.type = cmd_list;
            write(sockfd, &msg, sizeof(struct messages_st));
            read(sockfd, buffer, sizeof(buffer));
            printf("Files: %s",buffer);
            //bzero(buffer, sizeof(buffer));
            break;
		case 3 :
            printf("Enter the file name: ");
            scanf("%s",fname);
            strcpy(msg.filename, fname);
			msg.type = cmd_receive;
			msg.size = SIZE;
            write(sockfd, &msg, sizeof(struct messages_st));
            download_file(sockfd,msg.filename);

            break;

			break;
		default : 
			printf("Please enter a valied number from 1 to 3\n");
	  }
  
	
	  printf("Closing the connection\n");
	  close(sockfd);
    
    return 0;
}
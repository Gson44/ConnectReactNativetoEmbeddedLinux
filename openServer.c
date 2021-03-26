#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include <string.h>
#include<unistd.h>
#include<stdint.h>

void bbb(char *state){
	FILE *fp;
	fp = fopen("/sys/class/leds/beaglebone:green:usr2/brightness", "w");
	printf("%s\n",state);
	if(strstr(state,"turnOn") != NULL){
	fputs("1", fp);
	fclose(fp);
}else if(strstr(state,"turnOff") != NULL){
	fputs("0", fp);
	fclose(fp);
}
	
}

int main(){

    //Create socket
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0){
        printf("Error in creating socket...\n");
        exit(EXIT_FAILURE);
    } 

    //Create address
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.1.111");
    server.sin_port = htons(8080);
    printf("Address created...\n");

    //bind socket to address and port
    if(bind(socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0){
        printf("Issue in binding the socket to server address and port...\n");
        exit(EXIT_FAILURE);
    }
    
    //Listen to socket
    printf("Listening to server...\n");
    listen(socket_fd, 2);
    while(1 < 2){

    //Accepting connection
    int client_socket;
    char *message = "WTF are you doing...\n";
    client_socket = accept(socket_fd, NULL,NULL);

    //Receiving message
    char buffer[1024] = {0};
    int varRead;
    varRead = read(client_socket, buffer, 1024);

    char *ret;
    int ch = '\n';
    
    int len;
    ret = strrchr(buffer, ch);
    ret[strcspn(ret,"\n")] = "";
//    printf("%s\n", ret);
    bbb(ret);

    //Sending a message to client
    send(client_socket, message, sizeof(message), 0);
    
    //Closing the connecting
    close(client_socket);
   }
    return 0;
}

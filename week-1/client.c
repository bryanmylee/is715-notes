#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	//./client 10.0.106.246 <string>
	//argc = 3 
	int sockfd = 0;
	char recv_buf[1024];
	struct sockaddr_in serv_addr;
	
	if(argc != 3) {
		printf ("Usage: %s IP <string>\n", argv[0]);
		return 1;
	}
	
	memset (recv_buf, '0', sizeof(recv_buf));//set recv_buf to 0
	
	//If socket create failed, print the error information
	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0))<0) {
		printf("\n Error: Could not creat socket \n");
		return 1;
	}
	memset (&serv_addr, '0', sizeof(serv_addr));//Set serv_addr to 0
	
	serv_addr.sin_family = AF_INET;//Set protocol to IPv4
	serv_addr.sin_port = htons (5998);//Set port to 5005
	
	//Convert string of IP address to binary; print error info if failed
	if (inet_pton (AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
		printf ("\n inet_pton error occured\n");
		return 1;
	}
	
	//Request a connection to server; print error info if failed
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr))<0) {
		printf ("\n Error: Connect Failed\n");
		return 1;
	}
	
	char *str = argv[2];
	struct {
		unsigned nbytes;
		unsigned payload_addr;
	}v;
	
	v.nbytes = 4096;//Set size of data to be received as 4096 bytes
	write (sockfd, &v, sizeof (v.nbytes));//Send v to server without overwrite s.fp
	
	read(sockfd, recv_buf, sizeof (recv_buf) - 1);//Receive a message ("Okay") from client
	puts(recv_buf);//Print the received message
	
	char payload_buf [4096];
	memset(payload_buf, 0, sizeof(payload_buf));
	strcpy(payload_buf, str);//Copy the string to payload_buf
	write (sockfd, payload_buf, 4096);//Send payload_buf to server
	
	read (sockfd, recv_buf, sizeof (recv_buf) - 1);//Receive the converted string
   	puts (recv_buf);//Print the converted string
	
	return 0;
}

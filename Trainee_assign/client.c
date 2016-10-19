/* This is the code to run client aplication.Client application takes IP address
 * of server to connect as command line argument.On, successful connection estab-
 * lishment client starts reading a text file and sends it to server in 1KB 
 * chunks.Client writes the received data in output file. When whole file is 
 * converted to capital letters,client exits gracefully by closing the connection
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

#define CHUNK 20	//Number of pieces of bytes that is to be sended to server
#define LIMIT 10000
#define END   0x10


/**breif@Function	error
 *
 *	 arguments	const char *msg
 *
 *	 Description	This Function will print the error message on terminal
 *
 *	 return		none
 */
void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	FILE *fd, *fp;
	char c;
	int result = 0, sockfd, portno, n, z = 0;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	unsigned char buffer[LIMIT] = {0};
	unsigned char buff[LIMIT] = {0};
	int rc;

	if (argc != 5) {
		printf("note :  command not return properly\n");
		printf("usage: ./client <server_ip> <server_port> <input_filename>"
			" <output_filename>\n");
		return 0;
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");

	server = gethostbyname(argv[1]); // Take the hostname from command line
	if (server == NULL) {
		printf("ERROR, no such host\n");
		return 0;
	}
	printf("\n----------------Client Application-----------------\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
			(char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	rc = connect(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr));
	if (rc < 0) {
		error("ERROR connecting");
		return 0;
	} else
		puts("Socket Connected");

    	bzero(buffer,LIMIT);

	fd = fopen(argv[3], "r");
	if (fd == NULL) {
      		perror("\n");
		printf("---->Create a file %s if it is not there\n", argv[3]);
      		return 0;
   	}	

	fp = fopen(argv[4], "w");
	if (fp == NULL) {
		perror("Error opening writing file\n");
		return 0;
	}

	/* This loop will continues untill all the bytes been read from input file */
   	while (1) {

		result = fread(buffer, sizeof(char), CHUNK, fd);
		if (result == CHUNK) {
			n = write(sockfd, buffer, CHUNK);
		}
 		if (result < CHUNK) {
			if (feof(fd)) {
				n = write(sockfd, buffer, result);
				printf("End of file\n");
				result = END;
			}
                	if (ferror(fd))
                   		printf("Error reading\n");
		}
		if (n < 0)
			error("ERROR writing to socket");

		n = read(sockfd, buff, CHUNK);
		buff[n] = '\0';

		if (n < 0)
        		error("ERROR reading from socket");
		fprintf(fp, "%s", buff);

		if (result == END)
			break;
	}
	fclose(fd);
	fclose(fp);
	printf("Socket Terminated\n");
   	close(sockfd);

    	return 0;
}

/* This is the code to run server application.Server application takes 
 * port address to listen on as command line arguments.On receiving each chunk 
 * from client, server converts the text into all capital letter and sends it
 * back to client.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define LIMIT 		10000
#define CHUNK 		20
#define NO_OF_CLIENTS   10

/**breif@Function	strupr
 *
 *       argument	char *p		pointer to character
 *
 *       Description	This function converts all text into capital letters
 *
 *       return 	none
 */
void strupr(char *p)
{
	while (*p != '\0') {
		if (*p >= 97 && *p <= 122)
			*p -= 32;
		++p;
	}
}

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

/**breif@Function	client_handler
 *
 *	 arguments	void *sock
 *
 *	 Description	This Function will handle and communicates with client
 *			also reading and writing to buffer
 *
 *	 return		none
 */
void *client_handler(void *sock)
{
	int n ,bytesreceived = 0, k = 0;
	char buffer[LIMIT];
	int *socket = sock;

	bzero(buffer, LIMIT);
	/* The loop will continues untill all the bytes are been received */
	while ((bytesreceived = read(*socket, buffer, CHUNK)) > 0) {
		strupr(buffer);
		n = write(*socket, buffer, bytesreceived);
		if (n <= 0) {
			error("ERROR writing to socket");
			break;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	pthread_t thread;
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	int n;
	struct sockaddr_in serv_addr, client_addr;

	if (argc != 2) {
		printf("note : command not return properly\n");
		printf("usage: ./server <server_port> \n");
		exit(1);
	}

	printf("--------------Server Application----------------\n");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	else
		puts("Socket formation");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding Port Address Already in use.");
	else
		puts("\nBinding Succefull");

	listen(sockfd, NO_OF_CLIENTS);

	clilen = sizeof(client_addr);
	while (1) {
		newsockfd = accept(sockfd,
				(struct sockaddr *) &client_addr, &clilen);
		if (newsockfd < 0)
			error("ERROR on accept");
		else
			puts("Socket Accepted");

		/* This function will create thread and handle the client*/
		pthread_create(&thread, NULL, &client_handler, &newsockfd);
	}
	pthread_join(thread, NULL);
	return 0;
}

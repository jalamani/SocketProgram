#include <sys/types.h> /* This is the server code */
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define SERVER_PORT 5000 /* arbitrary, but client & server must agree */
#define BUF_SIZE 4096 /* block transfer size */
#define QUEUE_SIZE 10
struct DATA {
	int C;
	char H;
	float I;
};
float ReverseFloat( const float inFloat ) //convert float format
{
   float retVal;
   char *floatToConvert = ( char* ) & inFloat;
   char *returnFloat = ( char* ) & retVal;

   // swap the bytes into a temporary buffer
   returnFloat[0] = floatToConvert[3];
   returnFloat[1] = floatToConvert[2];
   returnFloat[2] = floatToConvert[1];
   returnFloat[3] = floatToConvert[0];

   return retVal;
}
int main(int argc, char *argv[])
{
struct DATA enteredDATA;
int s, b, l, fd, sa, bytes, on = 1;
char buf[BUF_SIZE]; /* buffer for outgoing file */
struct sockaddr_in channel; /* holds IP address */
/* Build address structure to bind to socket. */
memset(&channel, 0, sizeof(channel)); /* zero channel */
channel.sin_family = AF_INET;
channel.sin_addr.s_addr = htonl(INADDR_ANY);
channel.sin_port = htons(SERVER_PORT);
/* Passive open. Wait for connection. */
s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); /* create socket */
if (s < 0) fatal("socket failed");
setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
b = bind(s, (struct sockaddr *) &channel, sizeof(channel));
if (b < 0) fatal("bind failed");
l = listen(s, QUEUE_SIZE); /* specify queue size */
if (l < 0) fatal("listen failed");
/* Socket is now set up and bound. Wait for connection and process it. */
while (1) {
sa = accept(s, 0, 0); /* block for connection request */
if (sa < 0) fatal("accept failed");

//Read code
while(1) {
bytes = read(sa, &enteredDATA, sizeof(enteredDATA)); /* read file name from socket */
/* Get and return the file. */
if (bytes < 0) fatal("read failed");
else break;
}

enteredDATA.C = enteredDATA.C;
enteredDATA.H = enteredDATA.H;
enteredDATA.I = ReverseFloat(enteredDATA.I);
printf( "Changed DATA : %d\n", enteredDATA.C);
printf( "Changed DATA : %c\n", enteredDATA.H);
printf( "Changed DATA : %f\n", enteredDATA.I);

close(sa); /* close connection */

break;
}

}
fatal(char *string)
{
printf("%s\n", string);
exit(1);
}
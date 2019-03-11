#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define SERVER_PORT 5000 /* arbitrary, but client & server must agree */
#define BUF_SIZE 4096 /* block transfer size */

struct DATA {
	int C;
	char H;
	float I;
};
int main(int argc, char **argv)
{
struct DATA enteredDATA;
int w, c, s, bytes;
char buf[BUF_SIZE]; /* buffer for incoming file */
struct hostent *h; /* info about server */
struct sockaddr_in channel; /* holds IP address */

printf("Please enter the DATA (int): \n"); //enter data to be sent
scanf("%d", &enteredDATA.C);
printf("Please enter the DATA (char): \n");
scanf(" %c", &enteredDATA.H);
printf("Please enter the DATA (float): \n");
scanf("%f", &enteredDATA.I);

printf("You entered : %d, %c, %f\n", enteredDATA.C, enteredDATA.H, enteredDATA.I);

if (argc != 3) fatal("Usage: client server-name file-name");
h = gethostbyname(argv[1]); /* look up host’s IP address */
if (!h) fatal("gethostbyname failed");
s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP/IP family
if (s <0) fatal("socket");
memset(&channel, 0, sizeof(channel));
channel.sin_family= AF_INET;
memcpy(&channel.sin_addr.s_addr, h->h_addr, h->h_length);
channel.sin_port= htons(SERVER_PORT);


c = connect(s, (struct sockaddr *) &channel, sizeof(channel));
printf("Connecting with %s...\n", argv[1]);
if (c < 0) fatal("connect failed");
/* Connection is now established. Send file name including 0 byte at end. */


w = write(s,&enteredDATA,sizeof(enteredDATA));
printf("Writing to %s...\n", argv[1]);
if(w<0) fatal("write failed");
}

fatal(char *string)
{
printf("%s\n", string);
exit(1);
}
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>


#include "rs232.h"
#include "open_fd.h"
#include "termios.h"



struct conn *set_rs232(void)
{
	/* allocate the struct */
	struct conn *tty = malloc(sizeof(struct conn));

	
//	/* open the file descriptor */
//	printf("creating fd...\n");
//	int sock = serial_fd_open();
//
//	printf("creating termios\n");
//	struct termios *serial = get_termios_mios(sock);
//
//	tty->socket = sock;
//	tty->serial = serial;

	/* open the sock */
	printf("creating fd...\n");
	tty->socket = serial_fd_open();


	/* get termios struct */
	printf("creating termios\n");
	tty->serial = get_termios_mios(tty->socket);


	return tty;

}

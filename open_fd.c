#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */

#include "settings.h"

int serial_fd_open(void)
{
	/* ttyUSB0 is the FT232 based USB2SERIAL Converter   */
	/* O_RDWR   - Read/Write access to serial port       */
	/* O_NOCTTY - No terminal will control the process   */
	/* Open in blocking mode,read will wait              */
	int fd = open(PORT, O_RDWR | O_NONBLOCK | O_NDELAY);


	if (fd == -1) {
		perror("opening ttyUSB0");
		exit(-1);
	} else {
		printf("ttyUSB0 opened successfully\n\n");
	}

	//fcntl(tty->socket, F_SETFL, FNDELAY);
        //fcntl(fd, F_SETFL, O_NONBLOCK);       // make the reads non-blocking
        fcntl(fd, F_SETFL, 0);       // make the reads non-blocking
	return fd;

}

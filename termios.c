#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */
#include <errno.h>   /* ERROR Number Definitions           */


struct termios *get_termios_mios(int sock)
{
	// 9600 bps, Even parity, 7 data bits, 1 stop bit
	speed_t baud = B9600; /* baud rate */


	/* set the other settings (in this case, 9600 8N1) */
	struct termios *s = (struct termios *) malloc(sizeof(struct termios));
	printf("getting attributes...\n");


	/* tcgetattr() is used to get the current settings of the serial port to the structure we just declared*/
	if (tcgetattr(sock, s) < 0) {
		printf("error\n");;
		return NULL;
	}


	printf("setting baud...\n");
	cfsetispeed(s, baud); /* baud rate  read*/
	cfsetospeed(s, baud); /* baud rate  write*/


	/********************
	* Control options   *
	*********************/
	// The standard settings are as follows: 9,600
	// baud, 1 start bit, 7-bit data, even parity, and
	// 2 stop bits.


	s->c_cflag &= ~CSIZE; /* Mask the character size bits */
	s->c_cflag |= CS7; /* 7 bit data */
	s->c_cflag &= ~PARODD;
	s->c_cflag |= PARENB; // Even parity
	s->c_cflag |= CSTOPB;// 2 stop bits
	/* Enable receiver, Ignore Modem Control lines       */
	s->c_cflag |= (CREAD | CLOCAL);

	/*********************/


	/******************
	* Input options   *
	******************/
	/* Disable XON/XOFF flow control both i/p and o/p */
	s->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	/*****************/


	/******************
	* Output options   *
	******************/
	s->c_oflag &= ~OPOST; /* raw output */
	/****************/


	/*****************
	* Line options   *
	*  controls how input characters are managed by the serial driver *
	*****************/
        s->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	/****************/



	/*********************
	* Control characters *
	*********************/
    	/* fetch bytes as they become available */
    	s->c_cc[VMIN] = 133;
    	s->c_cc[VTIME] = 1;
	/********************/

	// s->c_cc[VMIN]  = 133; /* Read 133 characters */
	// s->c_cc[VTIME] = 1;  /* Wait indefinitely   */

	/* Set the attributes to the termios structure */
	printf("setting attributes...\n");
	if ((tcsetattr(sock, TCSANOW, s)) != 0) {
		printf("\n  ERROR ! in Setting attributes");
	}


	/**********************************************
	tcflush()
	discards data written to the object referred
	to by fd but not transmitted, or data
	received but not read, depending on the value
	of queue_selector
	***********************************************
	TCIFLUSH
   		flushes data received but not read.
	TCOFLUSH
    		flushes data written but not transmitted.
	TCIOFLUSH
    		flushes both data received but not read,
		and data written but not transmitted.
	**********************************************/

	//tcflush(sock, TCOFLUSH);

	printf("returning\n");
	return s;
}

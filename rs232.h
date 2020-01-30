
struct conn *set_rs232(void);

struct conn {
	int socket;
	struct termios *serial;
};

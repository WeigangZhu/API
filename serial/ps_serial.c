#include"ps_serial.h"


const int speed_arr[] = {B230400, B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300 };  
const int name_arr[]  = {230400,  115200,  38400,  19200,  9600,  4800,  2400,  1200,  300 };


int dev_open(char dev[])
{
    int fd, flag;
    
    speed_t baud_rate_i, baud_rate_o;

    fd = open(dev, O_RDWR | O_NONBLOCK );
    is_open(fd, dev); 
    
    /*
    struct termios term;
    flag = tcgetattr(fd, &term);
    baud_rate_i = cfgetispeed(&term);
    baud_rate_o = cfgetospeed(&term);
    printf("output baudrate before = %d，input baudrate = %d\n",baud_rate_i, baud_rate_o);
	*/
	
    set_speed(fd, 115200);
    
	/*
    flag = tcgetattr(fd, &term);
    baud_rate_i = cfgetispeed(&term);
    baud_rate_o = cfgetospeed(&term);
   	printf("baudrate now = %d，，input baudrate = %d\n",baud_rate_i, baud_rate_o);
   	*/

    if (set_parity(fd, 8, 1, 'N') == -1) 
	{
		printf("set parity error\n");
		exit(1);
	
    }
    return fd;
}

void set_speed(int fd, int speed)
{
    unsigned int i;
    int status;
    struct termios Opt;
    tcgetattr(fd, &Opt);
    for (i = 0; i < sizeof(speed_arr) / sizeof(int); i++) 
	{
		if (speed == name_arr[i]) 
		{
	    	tcflush(fd, TCIOFLUSH);
	    	cfsetispeed(&Opt, speed_arr[i]);
	    	cfsetospeed(&Opt, speed_arr[i]);
	    	status = tcsetattr(fd, TCSANOW, &Opt);
	    	if (status != 0) 
			{
				perror("tcsetattr fd");
				return;
	    	}
	    	tcflush(fd, TCIOFLUSH);
		}
    }
}




int set_parity(int fd, int databits, int stopbits, int parity)
{
    struct termios options;
    if (tcgetattr(fd, &options) != 0) {
		perror("setup serial");
		return -1;
    }
    options.c_cflag &= ~CSIZE;
    /* set databits */
    switch (databits) {		
    	case 7:
				options.c_cflag |= CS7;
				break;
    	case 8:
				options.c_cflag |= CS8;
				break;
    	default:
				fprintf(stderr, "unsupported data size\n");
				return -1;
    }
    
    switch (parity) {
    	case 'n':
    	case 'N':
				// options.c_cflag &= ~PARENB;   /* Clear parity enable */
				// options.c_iflag &= ~INPCK;     /* Enable parity checking */
				options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);	/*Input */
				options.c_oflag &= ~OPOST;	/*Output */
				break;
    	case 'o':
    	case 'O':
				options.c_cflag |= (PARODD | PARENB);	/* set Odd parity */
				options.c_iflag |= INPCK;	/* Disnable parity checking */
				break;
    	case 'e':
    	case 'E':
			options.c_cflag |= PARENB;	/* Enable parity */
			options.c_cflag &= ~PARODD;	/* set Even parity */
			options.c_iflag |= INPCK;	/* Disnable parity checking */
			break;
	    case 'S':
	    case 's':			/*as no parity */
			options.c_cflag &= ~PARENB;
			options.c_cflag &= ~CSTOPB;
			break;
	    default:
			fprintf(stderr, "unsupported parity\n");
			return -1;
    }
    
	/* set stopbits*/
    switch (stopbits) {
	    case 1:
			options.c_cflag &= ~CSTOPB;
			break;
	    case 2:
			options.c_cflag |= CSTOPB;
			break;
	    default:
			fprintf(stderr, "unsupported stop bits\n");
			return -1;
    }
    
	/* set input parity option */
    if ((parity != 'n') && (parity != 'N'))
		options.c_iflag |= INPCK;

    options.c_cc[VTIME] = 5;	// 0.5 seconds
    options.c_cc[VMIN] = 1;

    options.c_cflag &= ~HUPCL;
    options.c_iflag &= ~INPCK;
    options.c_iflag |= IGNBRK;
    options.c_iflag &= ~ICRNL;
    options.c_iflag &= ~IXON;
    options.c_lflag &= ~IEXTEN;
    options.c_lflag &= ~ECHOK;
    options.c_lflag &= ~ECHOCTL;
    options.c_lflag &= ~ECHOKE;
    options.c_oflag &= ~ONLCR;

    tcflush(fd, TCIFLUSH);	/* Update the options and do it NOW */
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
		perror("setup serial");
		return -1;
    }

    return 0;
}



// is open file ?
void is_open(int fd, char *file_name)
{
	if(fd == -1) {
		printf("not open %s\n",file_name);
		exit(1);
	}
	else
		printf("open %s sccussful!\n",file_name);
}



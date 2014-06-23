// Define the vendor ID and the product ID for the Arduino for USB identification
#ifndef	ARD_FILE
	#define ARD_FILE "/dev/ttyACM0"
#endif

#ifndef ARD_VID
#	define ARD_VID 0x2341
#endif

#ifndef ARD_PID
#	define ARD_PID 0x0043
#endif

#ifndef ARD_MAXPAN
#	define ARD_MAXPAN 149
#endif

#ifndef ARD_MINPAN
#	define ARD_MINPAN 0
#endif

#ifndef ARD_MAXTILT
#	define ARD_MAXTILT 149
#endif

#ifndef ARD_MINTILT
#	define ARD_MINTILT 0
#endif
//Tilt Pan instructions
#ifndef TP_LEFT
#	define TP_LEFT 0
#endif

#ifndef TP_RIGHT
#	define TP_RIGHT 1
#endif

#ifndef TP_DOWN
#	define TP_DOWN 2
#endif

#ifndef TP_UP
#	define TP_UP 3
#endif
//Drive instructions
#ifndef DRIVE_STOP
#	define DRIVE_STOP 4
#endif

#ifndef DRIVE_LEFTSTOP
#	define DRIVE_LEFTSTOP 5
#endif

#ifndef DRIVE_RIGHTSTOP
#	define DRIVE_RIGHTSTOP 6
#endif

#ifndef DRIVE_LEFTFORWARD
#	define DRIVE_LEFTFORWARD 7
#endif

#ifndef DRIVE_RIGHTFORWARD
#	define DRIVE_RIGHTFORWARD 8
#endif

#ifndef DRIVE_LEFTREVERSE
#	define DRIVE_LEFTREVERSE 9
#endif

#ifndef DRIVE_RIGHTREVERSE
#	define DRIVE_RIGHTREVERSE 10
#endif





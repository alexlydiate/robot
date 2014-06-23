#include "arduino_coms.h"

#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdexcept>

using namespace std;

/**
 * The Arduino control class.  It should be used in conjunction with the r_o_p.ino sketch loaded into the Arduino
 */
class Control {
	protected:
		int arduino;
		char instruction;

		void send() {
			write(this->arduino, &instruction, 1);
		}

	public:
		Control()
		{
			//Set Baud rate
			struct termios toptions;
			speed_t brate = B19200;

			cfsetispeed(&toptions, brate);
			cfsetospeed(&toptions, brate);

			//Get handle for Arduino dev file
			this->arduino = open(ARD_FILE, O_RDWR);
			this->instruction = 254;

			if (this->arduino == -1) {
				throw std::runtime_error("No Arduino");
			}
		}

		void camLeft()
		{
			instruction = TP_LEFT;
			this->send();
		}

		void camRight()
		{
			instruction = TP_RIGHT;
			this->send();
		}

		void camUp()
		{
			instruction = TP_UP;
			this->send();
		}

		void camDown()
		{
			instruction = TP_DOWN;
			this->send();
		}

		void driveStop()
		{
			instruction = DRIVE_STOP;
			this->send();
		}

		void driveLeftStop()
		{
			instruction = DRIVE_LEFTSTOP;
			this->send();
		}

		void driveRightStop()
		{
			instruction = DRIVE_RIGHTSTOP;
			this->send();
		}

		void driveLeftForward()
		{
			instruction = DRIVE_LEFTFORWARD;
			this->send();
		}

		void driveRightForward()
		{
			instruction = DRIVE_RIGHTFORWARD;
			this->send();
		}

		void driveLeftReverse()
		{
			instruction = DRIVE_LEFTREVERSE;
			this->send();
		}

		void driveRightReverse()
		{
			instruction = DRIVE_RIGHTREVERSE;
			this->send();
		}

		void driveForwardFast()
		{

		}

		void driveForwardMedium()
		{

		}

		void driveForwardSlow()
		{

		}

		void driveReverseFast()
		{

		}

		void driveReverseMedium()
		{

		}

		void driveReverseSlow()
		{

		}

		void driveRotateLeftSlow()
		{

		}

		void driveRotateRightSlow()
		{

		}

		void driveRotateLeftMedium()
		{

		}

		void driveRotateRightMedium()
		{

		}

		void driveRotateLeftFast()
		{

		}

		void driveRotateRightFast()
		{

		}
};

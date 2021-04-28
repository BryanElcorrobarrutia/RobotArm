import serial
from time import sleep


ser = serial.Serial()
ser.port = 'COM4'
ser.baudrate = 9600
ser.timeout = 1
ser.write_timeout = 1


def create_msg(q1,q2,q3):
	""" Converts the given configuration into a string of bytes
	understood by the robot arm. 

	Parameters:
		q1: The joint angle for the first (waist) axis.
		q2: The joint angle for the second (shoulder) axis.
		q3: The joint angle for the third (wrist) axis.
	Returns:
		The string of bytes. 
	"""
	return ('%d,%d,%d\n' % (q1,q2,q3)).encode()

def main():
	ser.open()
	sleep(2)

	ser.write(b'20,20,20\n')
	sleep(5)
	ser.write(create_msg(0,90,50))
	ser.close()

		

if __name__ =="__main__":
	main()
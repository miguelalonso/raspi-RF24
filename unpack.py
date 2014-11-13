>>> import struct
>>> x_bytes = ser.read(4)  # (where ser is your Serial instance)
>>> x = struct.unpack('<f', x_bytes)[0]
>>> x
17.229999542236328
>>> import struct
>>> x = [10, -41, -119, 65]
>>> struct.unpack('<f', struct.pack('4b', *x))[0]
17.229999542236328


datos=[0,1,2,3, 4,5,6,7, 8,9,10,11, 12,13,14,15, 16,17,18,19]
import struct
for j in range(4)
	x=datos(j*4:j*4+3)
	datos2[j]=struct.unpack('<f', struct.pack('4b', *x))[0]datos=[0,1,2,3, 4,5,6,7, 8,9,10,11, 12,13,14,15, 16,17,18,19]
import struct
for j in range(4)
	x=datos(j*4:j*4+3)
	datos2[j]=struct.unpack('<f', struct.pack('4b', *x))[0]

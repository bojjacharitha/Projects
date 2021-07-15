import socket			 
import os
import io


s = None
c = None
usePyAudio = True

if usePyAudio:
	import pyaudio
	import wave

def init(port):
	if not usePyAudio:
		out = os.popen("ifconfig").read().splitlines()
		print('Possible ip address:')
		for line in out:
			if 'inet' in line and 'inet6' not in line:
				ip = line.split(' ')[9]
				if ip != '127.0.0.1':
					print('  ', ip)
		global s, c
		s = socket.socket()		 
		s.bind(('', port))		 
		s.listen(1)	 
		print( "Socket listening on port", port)
		c, addr = s.accept()
		print ('Connected to ', addr )


def recvall(sock, n):
    data = bytearray()
    while len(data) < n:
        packet = sock.recv(n - len(data))
        if not packet:
            return None
        data.extend(packet)
    return data


def record(i):
	if usePyAudio:
		CHUNK = 1024 
		FORMAT = pyaudio.paInt16 #paInt8
		CHANNELS = 1
		RATE = 8000 #sample rate
		RECORD_SECONDS = i
		p = pyaudio.PyAudio()
		stream = p.open(format=FORMAT,channels=CHANNELS,rate=RATE,input=True,frames_per_buffer=CHUNK) #buffer
		print("* recording")
		frames = []
		for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
			data = stream.read(CHUNK)
			frames.append(data) # 2 bytes(16 bits) per channel
		print("* done recording")
		stream.stop_stream()
		stream.close()
		temp_file = io.BytesIO()
		wf = wave.open(temp_file, 'wb')
		wf.setnchannels(CHANNELS)
		wf.setsampwidth(p.get_sample_size(FORMAT))
		wf.setframerate(RATE)
		wf.writeframes(b''.join(frames))
		wf.close()
		temp_file.seek(0)
		ret = temp_file.read()
		temp_file.close()
		return ret
	else:
		print('recording...')
		data = bytearray()
		data.append(i)
		c.send(data)
		l = recvall(c, 4)
		l = l[0] + (l[1] << 8) + (l[2] << 16) + (l[3] << 24)
		dat = recvall(c, l)
		print('done recording')
		return dat
	
def close():
	if not usePyAudio:
		c.close()
		s.close()

btser = None
btsoc = None

def btinit(port):
	out = os.popen("ifconfig").read().splitlines()
	print('Possible ip address:')
	for line in out:
		if 'inet' in line and 'inet6' not in line:
			ip = line.split(' ')[9]
			if ip != '127.0.0.1':
				print('  ', ip)
	global btser, btsoc
	btser = socket.socket()		 
	btser.bind(('', port))		 
	btser.listen(1)	 
	print( "Socket listening on port", port)
	btsoc, addr = btser.accept()
	print ('Connected to ', addr )
	
def btclose():
	btsoc.close()
	btser.close()
	
def btwrite(dat):
	data = bytearray()
	data.append(len(dat))
	btsoc.send(data)
	btsoc.send(dat)

import speech_recognition as sr
from time import sleep
import serial

from gpiozero import Button, LED

# initialize serial
def serialsend(sending):
	serial.Serial(            
		port='/dev/serial0',
		baudrate = 19200,
		parity=serial.PARITY_NONE,
		stopbits=serial.STOPBITS_ONE,
		bytesize=serial.EIGHTBITS,
		timeout=1
		).write(sending)

#initialize inputs & outputs (14 and 15 are taken by UART)
readyspeak = Button(2)
listenled = LED(4)

#put startup tone here, pygame suggested solution
#its gonna be frikken cool

def numberwtod(parts, i):
	exit = 0
	if parts[i] == "ONE":
		number = "1"
	elif parts[i] == "TWO":
		number = "2"
	elif parts[i] == "THREE":
		number = "3"
	elif parts[i] == "FOUR":
		number = "4"
	elif parts[i] == "FIVE":
		number = "5"
	elif parts[i] == "SIX":
		number = "6"
	elif parts[i] == "SEVEN":
		number = "7"
	elif parts[i] == "EIGHT":
		number = "8"
		#uncomment below in final version
	#elif parts[i] == "TO"
		#number = "2"
	else:
		print("N CONVERSION ERROR\n")
		sleep(1)
		exit = 1
		number = "9"
	return number, exit

def piecewtol(parts, i):
	exit = 0
	if parts[i] == "PAWN":
		piece = "p"
	elif parts[i] == "ROOK":
		piece = "r"
	elif parts[i] == "KNIGHT":
		piece = "n"
	elif parts[i] == "BISHOP":
		piece = "b"
	elif parts[i] == "QUEEN":
		piece = "q"
	elif parts[i] == "KING":
		piece = "k"
	else:
		print("P CONVERSION ERROR\n")
		sleep(1)
		exit = 1
		piece = "lol"
	return piece, exit

def speechinput():
	speak = 1
	# Input goes here yo
	print("before while")
	while(speak):
		if (readyspeak.is_pressed or 1): # remove when button added
			listenled.on()
			# obtain audio from the microphone
			r = sr.Recognizer()
			with sr.Microphone() as source:
				print("Listening")
				audio = r.listen(source)
			
			# recognize speech using Sphinx
			try:
				Commandi = r.recognize_sphinx(audio) # save command as variable
				print(Commandi + "\n") # print variable, this will not be in the final version
			except sr.UnknownValueError:
				print("Sphinx could not understand audio")
				Commandi = "nope"
			except sr.RequestError as e:
				print("Sphinx error; {0}".format(e))		
		
			#checks if string is usable 
			if (len(Commandi) >= 20 and len(Commandi) <= 30): #16 and 23 for piece to intersect
				parts = Commandi.split(" ",4) # 3 for piece to intersect
				if (len(parts[4]) <= 5 and parts[0]+parts[1] != parts[3]+parts[4]):
					speak = 0
				else:
					listenled.blink()
					sleep(1)
					speak = 1
			else:
				listenled.blink()
				sleep(1)
				speak = 1
	return parts

def moveinputconvert():
	
	if (True):
		parts = speechinput()
	if True:
		print(converting)
		#convert to usable format
		#listenled.off() # processing
		#piece, ex = piecewtol(parts)
		number, ex = numberwtod(parts, 1)
		number1, ex = numberwtod(parts, 4)
		if (not ex):
			Commando = parts[0][0].lower()+number+parts[3][0].lower()+number1
			serialsend(Commando)
			sleep(1)
		
		ex = 0
		return Commando	
	
	
	#raw_input("")
#if remove.is_pressed:
	#play audio from here
#etc
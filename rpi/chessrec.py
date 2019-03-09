import speech_recognition as sr
import time
import serial
from gpiozero import Button, LED

# initialize serial
ser = serial.Serial(            
    port='/dev/serial0',
    baudrate = 19200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
    )
	
#initialize inputs & outputs (14 and 15 are taken by UART)
readyspeak = Button(2)
listenled = LED(4)

#put startup tone here, pygame suggested solution
#its gonna be frikken cool

#initialize variables
player = "WHITE"
convert = 0
speak = 0

while 1:

	   
	if (readyspeak.is_pressed or speak ):
		listenled.on()
	    # obtain audio from the microphone
        r = sr.Recognizer()
        with sr.Microphone() as source:
            print("Listening")
            audio = r.listen(source)
        
        # recognize speech using Sphinx
        try:
            Commandi = r.recognize_sphinx(audio) # save command as variable
            print(Commandi = "\n") # print variable, this will not be in the final version
        except sr.UnknownValueError:
            print("Sphinx could not understand audio")
        except sr.RequestError as e:
            print("Sphinx error; {0}".format(e))
                
		
		#checks if string is usable (add a flag or summon to invoke the listen loop) 
		if (len(Commandi) >= 16 and len(Commandi) <= 23):
			parts = Commandi.split(" ",3)
			if (len(parts[3]) >= 7):
				convert = 1
				speak = 0
			else:
				listenled.blink()
				sleep(1)
				speak = 1
		else:
			listenled.blink()
			sleep(1)
			speak = 1
			
	if convert:
		#convert to usable format
		listenled.off() # processing
		if parts[3] == "ONE":
			number = "1"
		elif parts[3] == "TWO":
			number = "2"
		elif parts[3] == "THREE":
			number = "3"
		elif parts[3] == "FOUR":
			number = "4"
		elif parts[3] == "FIVE":
			number = "5"
		elif parts[3] == "SIX":
			number = "6"
		elif parts[3] == "SEVEN":
			number = "7"
		else:
			listenled.blink()
			sleep(1)
			continue
		if parts[0] == "PAWN":
			piece = "p"
		elif parts[0] == "ROOK":
			piece = "r"
		elif parts[0] == "KNIGHT":
			piece = "n"
		elif parts[0] == "BISHOP":
			piece = "b"
		elif parts[0] == "QUEEN":
			piece = "q"
		elif parts[0] == "KING":
			piece = "k"
		else:
			listenled.blink()
			sleep(1)
			continue
		Commando = player[0].lower()+piece+parts[2][0].lower()+number
		if player == "WHITE":
			player = "BLACK"
		else:
			player = "WHITE"
		
		ser.write(Commando)
		sleep(1)
		convert = 0
		
		
		
        #raw_input("")
	#if remove.is_pressed:
	    #play audio from here
	#etc
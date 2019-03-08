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

while 1:

	   
	if readyspeak.is_pressed:
		listenled.on()
	    # obtain audio from the microphone
        r = sr.Recognizer()
        with sr.Microphone() as source:
            print("Listening")
            audio = r.listen(source)
        
        # recognize speech using Sphinx
        try:
            Commandi = r.recognize_sphinx(audio) +"\n" # save command as variable
            print(Commandi) # print variable, this will not be in the final version
        except sr.UnknownValueError:
            print("Sphinx could not understand audio")
        except sr.RequestError as e:
            print("Sphinx error; {0}".format(e))
                
		listenled.blink() # processing
		
		#checks if string is usable (add a flag or summon to invoke the listen loop) 
		parts = Commandi.split(" ",3)
		convert = 1
		
	if convert
		#convert to usable format
		if parts[3] == "ONE"
			number = "1"
		elif parts[3] == "TWO"
			number = "2"
		elif parts[3] == "THREE"
			number = "3"
		elif parts[3] == "FOUR"
			number = "4"
		elif parts[3] == "FIVE"
			number = "5"
		elif parts[3] == "SIX"
			number = "6"
		elif parts[3] == "SEVEN"
			number = "7"
		else
			for i in range(1,3):
				listenled.on()
				sleep(1)
				listenled.blink()
				sleep(1)
		Commando = player[0].lower()+parts[0][0].lower()+parts[2][0].lower()+number
		if player == "WHITE"
			player = "BLACK"
		else
			player = "WHITE"
		
		ser.write(Commando)
		sleep(1)
		convert = 0
		listenled.off()
		
		
        #raw_input("")
	#if remove.is_pressed:
	    #play audio from here
	#etc
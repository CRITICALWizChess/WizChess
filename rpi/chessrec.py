import speech_recognition as sr
import time
import serial
import gpiozero

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
            Command = r.recognize_sphinx(audio) +"\n" # save command as variable
            print(Command) # print variable, this will not be in the final version
        except sr.UnknownValueError:
            print("Sphinx could not understand audio")
        except sr.RequestError as e:
            print("Sphinx error; {0}".format(e))
        
        ser.write(Command)
		listenled.blink()
		sleep(1)
		listenled.off()
		
		
        #raw_input("")
	#if remove.is_pressed:
	    #play audio from here
	#etc
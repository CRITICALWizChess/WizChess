import speech_recognition as sr
from time import sleep
import serial
import spidev
import sys
import lcdfunc

from gpiozero import Button, LED




#initialize inputs & outputs (14 and 15 are taken by UART)
readyspeak = Button(2) # pin 3
enter = Button(3) # pin 5
right = Button(4) # pin 7
listenled = LED(17) # pin 11

#put startup tone here, pygame suggested solution
#its gonna be frikken cool (actually this would go 
# n the main program but the function would be here)

#sends over UART if enabled
def serialsend(sending):
	ser = serial.Serial(            
		port='/dev/serial0',
		baudrate = 19200,
		parity=serial.PARITY_NONE,
		stopbits=serial.STOPBITS_ONE,
		bytesize=serial.EIGHTBITS,
		timeout=1
		)
	ser.write(sending)

def spisend(sending):
	spi = spidev.SpiDev()
	spi.open(0,0)
	spi.max_speed_hz = 500000
	spi.mode = 0
	msg = [int(sending[0:2]), int(sending[2:4])]
	for x in range(0,50):
		spi.xfer2(msg)
	spi.close()


def numberwtod(parts, i):
	ext = 0
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
	elif parts[i] == "TO":
		number = "2"
	else:
		print("N CONVERSION ERROR\n")
		sleep(1)
		ext = 1
		number = "9"
	return number, ext

def natotod(parts):
	ext = 0
	i = 0
	for x in range(0,2):
		if parts[i] == "ALPHA":
			number = "1"
		elif parts[i] == "BRAVO":
			number = "2"
		elif parts[i] == "CHARLIE":
			number = "3"
		elif parts[i] == "DELTA":
			number = "4"
		elif parts[i] == "ECHO":
			number = "5"
		elif parts[i] == "FOXTROT":
			number = "6"
		elif parts[i] == "GOLF":
			number = "7"
		elif parts[i] == "HOTEL":
			number = "8"
		else:
			print("N CONVERSION ERROR\n")
			sleep(1)
			ext = 1
			number = "9"
		if (x == 0):
			number0 = number
			i = 3
	return number0, number, ext

def piecewtol(parts, i):
	ext = 0
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
	return piece, ext

def speechinput():
	speak = 1
	# Input goes here yo
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

def senddisplay(first, second, third, fourth):
    lcdfunc.lcd_string(first,lcdfunc.LCD_LINE_1,2)
    lcdfunc.lcd_string(second,lcdfunc.LCD_LINE_2,2)
    lcdfunc.lcd_string(third,lcdfunc.LCD_LINE_3,2)
    lcdfunc.lcd_string(fourth,lcdfunc.LCD_LINE_4,2)

def manualinput():
    columns = ["ALPHA", "BRAVO", "CHARLIE", "DELTA", "ECHO", "FOXTROT", "GOLF", "HOTEL"]
    rows = ["ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT"]
    senddisplay("Chose your start", "and end intersection", "Right to go next", "or middle to confirm")
	sleep(3)
    col = row = col1 = row1 = 0
    coli = rowi = col1i = row1i = 0
    while(row1 == 0):
        while(col1 == 0):
            while(row == 0):
                while(col == 0):
                    senddisplay(columns[coli], rows[rowi], columns[col1i], rows[row1i])
                    if(right.is_pressed):
                    # buttonfua = raw_input("Enter to right: ") or " "
                    # if (buttonfua == " "):
                        coli += 1
                        if (coli == 8):
                            coli = 0
                    # else:
                    #     col += 1
                    if(enter.is_pressed):
                        col += 1
                senddisplay(columns[coli], rows[rowi], columns[col1i], rows[row1i])
                if(right.is_pressed):
                # buttonfub = raw_input("Enter to right: ") or " "
                # if (buttonfub == " "):
                    rowi += 1
                    if (rowi == 8):
                        rowi = 0
                # else:
                #     row += 1
                if(enter.is_pressed):
                   row += 1
            senddisplay(columns[coli], rows[rowi], columns[col1i], rows[row1i])
            if(right.is_pressed):
            #buttonfuc = raw_input("Enter to right: ") or " "
            #if (buttonfuc == " "):
                col1i += 1
                if (col1i == 8):
                    col1i = 0
            #else:
            #    col1 += 1
            if(enter.is_pressed):
                col1 += 1
        senddisplay(columns[coli], rows[rowi], columns[col1i], rows[row1i])
        if(right.is_pressed):
        #buttonfud = raw_input("Enter to right: ") or " "
        #if (buttonfud == " "):
            row1i += 1
            if (row1i == 8):
                row1i = 0
        #else:
        #    row1 += 1
        if(enter.is_pressed):
            row1 += 1
    Commandi = columns[coli] + " " + rows[rowi] + " TO " + columns[col1i] + " " + rows[row1i]
    print(Commandi)
    parts = Commandi.split(" ",4)
    return parts

def moveinputconvert():
	lcdfunc.setuplcd()
	while(True):
		senddisplay("press left for voice", "or middle for manual", " ", " ")
		sleep(2) #change this for final version
		if (readyspeak.is_pressed):
			select = 1
			break
		if (enter.is_pressed):
			select = 2
			break
	if (select == 1):
		parts = speechinput()
	if (select == 2):
		parts = manualinput()
	if True:
		print("converting")
		#convert to usable format
		listenled.off() # processing
		#piece, ex = piecewtol(parts)
		number, ex = numberwtod(parts, 1)
		number1, ex = numberwtod(parts, 4)
		nat, nat1, ex = natotod(parts)
		if (not ex):
			Commando = parts[0][0].lower()+number+parts[3][0].lower()+number1
			Commandser = nat+number+nat1+number1
			spisend(Commandser)
			sleep(1)
		
		ex = 0
		return Commando	
	
	
	#raw_input("")
#if remove.is_pressed:
	#play audio from here
#etc
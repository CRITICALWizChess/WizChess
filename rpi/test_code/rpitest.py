#!/usr/bin/env python
from time import sleep


#initialize variables


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
		#uncomment below in final version
	#elif parts[i] == "TO"
		#number = "2"
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
		ext = 1
		piece = "lol"
	return piece, ext

def speechinput():
	speak = 1
	# Input goes here yo
	while(speak):
		Commandi = raw_input("Type your input\n").upper() # save command as variable
		#print("Input is " + Commandi) # print variable, this will not be in the final version		
		
		#checks if string is usable (add a flag or summon to invoke the listen loop) 
		if (len(Commandi) >= 20 and len(Commandi) <= 30): #16 and 23 for piece to intersect
			parts = Commandi.split(" ",4)
			if (len(parts[4]) <= 5 and parts[0]+parts[1] != parts[3]+parts[4]):
				speak = 0
			else:
				print("ERROR 3")
				sleep(1)
				speak = 1
		else:
			print("ERROR 1")
			sleep(1)
			speak = 1
	return parts

def moveinputconvert():
	if (True):
		parts = speechinput()
	if True:
		#convert to usable format
		#listenled.off() # processing
		#piece, ex = piecewtol(parts)
		number, ex = numberwtod(parts, 1)
		number1, ex = numberwtod(parts, 4)
		nat, nat1, ex = natotod(parts)
		Commando = " "
		if (not ex):
			Commando = parts[0][0].lower()+number+parts[3][0].lower()+number1
			Commandser = nat+number+nat1+number1
			print("Commando is " + Commando + "\n")
			print(Commandser)
			
		
		ex = 0
		return Commando	
		



#while 1:
 	#move = moveinputconvert()
			
		
		
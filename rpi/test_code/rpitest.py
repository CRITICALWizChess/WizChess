from time import sleep
	
#initialize variables
#player = "WHITE"
convert = 0
speak = 0


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
	#elif parts[i] == "TO"
		#number = "2"
	else:
		print("N CONVERSION ERROR\n")
		sleep(1)
		exit = 1
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
	return piece, exit


while 1:

	if (1 or speak ):

		Commandi = raw_input("Type your input\n") # save command as variable
		print("Input is " + Commandi) # print variable, this will not be in the final version		
		
		#checks if string is usable (add a flag or summon to invoke the listen loop) 
		if (len(Commandi) >= 20 and len(Commandi) <= 30): #16 and 23 for piece to intersect
			parts = Commandi.split(" ",4)
			if (len(parts[4]) <= 5 and parts[0]+parts[1] != parts[3]+parts[4]):
				convert = 1
				speak = 0
			else:
				print("ERROR 3")
				sleep(1)
				speak = 1
		else:
			print("ERROR 1")
			sleep(1)
			speak = 1
			
	if convert:
		#convert to usable format
		#listenled.off() # processing
		#piece, ex = piecewtol(parts)
		number, ex = numberwtod(parts, 1)
		number1, ex = numberwtod(parts, 4)
		if ex:
			ex = 0
			continue
		Commando = parts[1][0].lower()+number+parts[3][0].lower()+number1+"\n"
#		if player == "WHITE":
#			player = "BLACK"
#		else:
#			player = "WHITE"
		
		print("Commando is " + Commando + "\n")
		
		convert = 0
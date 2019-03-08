from time import sleep
	
#initialize variables
player = "WHITE"
convert = 0
speak = 0



while 1:

	if (1 or speak ):

		Commandi = raw_input("Type your input\n") # save command as variable
		print("Input is " + Commandi) # print variable, this will not be in the final version		
		
		#checks if string is usable (add a flag or summon to invoke the listen loop) 
		if (len(Commandi) >= 16 and len(Commandi) <= 23):
			parts = Commandi.split(" ",3)
			if (len(parts[3]) <= 5):
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
		elif parts[3] == "EIGHT":
			number = "8"
		else:
			print("N CONVERSION ERROR")
			sleep(1)
			break
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
			print("P CONVERSION ERROR")
			sleep(1)
			break
		Commando = player[0].lower()+piece+parts[2][0].lower()+number
		if player == "WHITE":
			player = "BLACK"
		else:
			player = "WHITE"
		
		print("Commando is " + Commando)
		
		convert = 0
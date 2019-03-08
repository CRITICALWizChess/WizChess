import time
	
#initialize variables
player = "WHITE"
convert = 0
speak = 0



while 1	   

	if (1 or speak ):

		Commandi = raw_input("Type your intput\n")	+"\n" # save command as variable
		print(Commandi) # print variable, this will not be in the final version		
		
		#checks if string is usable (add a flag or summon to invoke the listen loop) 
		if (len(Commandi) >= 16 and len(Commandi) <= 23)
			parts = Commandi.split(" ",3)
			if (len(parts[3]) >= 7)
				convert = 1
				speak = 0
			else	
				print("ERROR 3")
				sleep(1)
				speak = 1
		else
			print("ERROR 1")
			sleep(1)
			speak = 1
			
	if convert
		#convert to usable format
		#listenled.off() # processing
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
			print("CONVERSION ERROR")
			sleep(1)
		Commando = player[0].lower()+parts[0][0].lower()+parts[2][0].lower()+number+"\n"
		if player == "WHITE"
			player = "BLACK"
		else
			player = "WHITE"
		
		print("commando is" + Commando)
		
		convert = 0
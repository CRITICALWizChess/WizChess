# this code will generate a intersection to intersection corpus.txt file
# written by Matthew Vandermeer
# 
column = [ "alpha", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel" ]
row = [ "one", "two", "three", "four", "five", "six", "seven", "eight" ]

file = open("corpus.txt","w")

for a in range(0,8):
	aa = column[a]
	for b in range(0,8):
		bb = row[b]
		for c in range(0,8):
			cc = column[c]
			for d in range(0,8):
				dd = row[d]
				if ((aa + bb) != (cc + dd)  ):
					file.write(aa + " " + bb + " to " + cc + " " + dd + "\n")
				
file.close()
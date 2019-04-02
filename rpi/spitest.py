import chessrec
import sys

try:
    numberz = "1"
    while True:
        print("Welcome to the SPI testing program!\n")
        choice=raw_input("Input your command, press enter to resend, or type exit to close: ") or " "
            
        if choice == 'exit':
            print( "\nawww you're leaving?")
            break
        if choice == " ":
            chessrec.spisend(numberz)
        else:
            choice = numberz
            chessrec.spisend(numberz)
except KeyboardInterrupt:
        sys.exit("\n\nExiting now.")
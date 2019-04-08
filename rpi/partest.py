#!/usr/bin/python
import chessrec
import sys

try:
    numberz = "1"
    print("Welcome to the parallel testing program!\n")
    while True:
        choice=raw_input("Input your command, press enter to resend, or type exit to close: ") or " "
            
        if choice == 'exit':
            print( "\nawww you're leaving?")
            break
        if choice == " ":
            chessrec.parsend(numberz)
        else:
            numberz = choice
            chessrec.parsend(numberz)
        print(int(numberz))
except KeyboardInterrupt:
        sys.exit("\n\nExiting now.")
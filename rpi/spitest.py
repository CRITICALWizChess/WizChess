import chessrec

try:
    while True:
        print("Welcome to the SPI testing program!\n")
        choice=raw_input("Input your command or type exit to close: ")
            
        if choice == 'exit':
            print( "\nAs you wish. Welcome back!")
            break
        chessrec.spisend(choice)
except KeyboardInterrupt:
        sys.exit("\n\nExiting now.")
import chessrec

try:
        while True:
            print("Welcome to the SPI testing program!\n")
            choice=raw_input("Input your move: ")

            if choice == 'exit':
                print "\nAs you wish. Welcome back!"
                break
    except KeyboardInterrupt:
        sys.exit("\n\nExiting now.")
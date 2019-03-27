#LCD menu test
import func as lcdfunc
import time

select = 0
col = 0
row = 0
col1 = 0
row1 = 0
coli = 0
rowi = 0
col1i = 0
row1i = 0
columns = ["ALPHA", "BRAVO", "CHARLIE", "DELTA", "ECHO", "FOXTROT", "GOLF", "HOTEL"]
rows = ["ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT"]


while(select == 0):
    print("press left for voice")
    print("or middle for manual")
    time.sleep(5) #change this for final version
    #if (readyspeak.is_pressed):
    if (0):
        select = 1
    #if (enter.is_pressed):
    if (1):
        select = 2
if (select == 1):
    #parts = speechinput()
    print("how")
if (select == 2):
    print("Chose your start")
    print("and end intersection")
    print("Right to go next")
    print("or middle to confirm")
    while(row1 == 0):
        while(col1 == 0):
            while(row == 0):
                while(col == 0):
                    print(columns[coli])
                    print(rows[rowi])
                    print(columns[col1i])
                    print(rows[row1i])
                    #if(right.is_pressed):
                    buttonfua = raw_input("Enter to right") or " "
                    if (buttonfua == " "):
                        coli += 1
                        if (coli == 8):
                            coli = 0
                    #if(enter.is_pressed):
                    if (buttonfua != " "):
                        buttona = raw_input("Enter to enter") or "a"
                        if (buttona == "a"):
                            col += 1
                print(columns[coli])
                print(rows[rowi])
                print(columns[col1i])
                print(rows[row1i])
                #if(right.is_pressed):
                buttonfub = raw_input("Enter to right") or " "
                if (buttonfub == " "):
                    rowi += 1
                    if (rowi == 8):
                        rowi = 0
                #if(enter.is_pressed):
                if (buttonfub != " "):
                    buttonb = raw_input("Enter to enter") or "a"
                    if (buttonb == "a"):
                        row += 1
            print(columns[coli])
            print(rows[rowi])
            print(columns[col1i])
            print(rows[row1i])
            #if(right.is_pressed):
            buttonfuc = raw_input("Enter to right") or " "
            if (buttonfuc == " "):
                col1i += 1
                if (col1i == 8):
                    col1i = 0
            #if(enter.is_pressed):
            if (buttonfuc != " "):
                buttonc = raw_input("Enter to enter") or "a"
                if (buttonc == "a"):
                    col1 += 1
        print(columns[coli])
        print(rows[rowi])
        print(columns[col1i])
        print(rows[row1i])
        #if(right.is_pressed):
        buttonfud = raw_input("Enter to right") or " "
        if (buttonfud == " "):
            row1i += 1
            if (row1i == 8):
                row1i = 0
        #if(enter.is_pressed):
        if (buttonfud != " "):
            buttond = raw_input("Enter to enter") or "a"
            if (buttond == "a"):
                row1 += 1
    Commandi = columns[coli] + " " + rows[rowi] + " TO " + columns[col1i] + " " + rows[row1i]
    print(Commandi)
    time.sleep(20)
                    

        


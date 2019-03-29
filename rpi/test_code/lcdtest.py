#LCD menu test
import time

def senddisplay(first, second, third, fourth):
    print(first)
    print(second)
    print(third)
    print(fourth)

def manualinput():
    columns = ["ALPHA", "BRAVO", "CHARLIE", "DELTA", "ECHO", "FOXTROT", "GOLF", "HOTEL"]
    rows = ["ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT"]
    print("Chose your start")
    print("and end intersection")
    print("Right to go next")
    print("or middle to confirm")
    col = row = col1 = row1 = 0
    coli = rowi = col1i = row1i = 0
    while(row1 == 0):
        while(col1 == 0):
            while(row == 0):
                while(col == 0):
                    senddisplay(columns[coli], rows[rowi], columns[col1i], rows[row1i])
                    #if(right.is_pressed):
                    buttonfua = raw_input("Enter to right: ") or " "
                    if (buttonfua == " "):
                        coli += 1
                        if (coli == 8):
                            coli = 0
                    else:
                        col += 1
                    #if(enter.is_pressed):
                    #    col += 1
                senddisplay(columns[coli], rows[rowi], columns[col1i], rows[row1i])
                #if(right.is_pressed):
                buttonfub = raw_input("Enter to right: ") or " "
                if (buttonfub == " "):
                    rowi += 1
                    if (rowi == 8):
                        rowi = 0
                else:
                    row += 1
                #if(enter.is_pressed):
                #    row += 1
            senddisplay(columns[coli], rows[rowi], columns[col1i], rows[row1i])
            #if(right.is_pressed):
            buttonfuc = raw_input("Enter to right: ") or " "
            if (buttonfuc == " "):
                col1i += 1
                if (col1i == 8):
                    col1i = 0
            else:
                col1 += 1
            #if(enter.is_pressed):
            #    col1 += 1
        senddisplay(columns[coli], rows[rowi], columns[col1i], rows[row1i])
        #if(right.is_pressed):
        buttonfud = raw_input("Enter to right: ") or " "
        if (buttonfud == " "):
            row1i += 1
            if (row1i == 8):
                row1i = 0
        else:
            row1 += 1
        #if(enter.is_pressed):
        #    row1 += 1
    Commandi = columns[coli] + " " + rows[rowi] + " TO " + columns[col1i] + " " + rows[row1i]
    print(Commandi)
    parts = Commandi.split(" ",4)
    return parts

select = 0
while(select == 0):
    print("press left for voice")
    print("or middle for manual")
    time.sleep(2) #change this for final version
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
    parts = manualinput()
    print(parts)
time.sleep(1)
                    

        


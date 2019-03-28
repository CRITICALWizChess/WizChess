import lcdfunc
import time

def senddisplay(first, second, third, fourth):
    lcdfunc.lcd_string(first,lcdfunc.LCD_LINE_1,2)
    lcdfunc.lcd_string(second,lcdfunc.LCD_LINE_2,2)
    lcdfunc.lcd_string(third,lcdfunc.LCD_LINE_3,2)
    lcdfunc.lcd_string(fourth,lcdfunc.LCD_LINE_4,2)

def manualinput():
    columns = ["ALPHA", "BRAVO", "CHARLIE", "DELTA", "ECHO", "FOXTROT", "GOLF", "HOTEL"]
    rows = ["ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT"]
    senddisplay("Chose your start", "and end intersection", "Right to go next", "or middle to confirm")
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

lcdfunc.setuplcd()
while 1:
    select = 0
    while(select == 0):
        senddisplay("press left for voice", "or middle for manual", " ", " ")
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
                    

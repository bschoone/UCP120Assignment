CFLAGS = -Wall -pedantic -ansi -g
CC = gcc
OBJ = GoogleCalendar.o gui.o LinkedList.o readCal.o validation.o formatting.o
GTK = `pkg-config --cflags --libs gtk+-2.0`

GoogleCalendar: $(OBJ)
	$(CC) -o GoogleCalendar $(OBJ) $(GTK)

GoogleCalendar.o: GoogleCalendar.c GoogleCalendar.h gui.h readCal.h LinkedList.h
	$(CC) $(CFLAGS) -c GoogleCalendar.c $(GTK)
	
gui.o: gui.c gui.h
	$(CC) $(CFLAGS) -c gui.c $(GTK) 
		
LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c $(GTK) 
	
readCal.o: readCal.c readCal.h LinkedList.h gui.h GoogleCalendar.h formatting.h
	$(CC) $(CFLAGS) -c readCal.c $(GTK)
	
validation.o: validation.c validation.h 
	$(CC) $(CFLAGS) -c validation.c $(GTK)
	
formatting.o: formatting.c formatting.h 
	$(CC) $(CFLAGS) -c formatting.c $(GTK)
	

clean: 
	rm -f GoogleCalendar $(OBJ)
	rm -f *.*~

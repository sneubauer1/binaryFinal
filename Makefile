INCLUDE_DIRS	:=	/home/sam/Documents/Sam310/Assignments/finalProject/final2/
CC				:= g++
CFLAGS			:= -I$(INCLUDE_DIRS)

OBJECTS			:= customErrorClass.o binaryFile.o

excBinaryFile:	main.cpp ${OBJECTS}
	${CC} -o $@ $^ ${CFLAGS}

customErrorClass.o:	customErrorClass.cpp customErrorClass.h
	${CC} -c -o customErrorClass.o customErrorClass.cpp ${CFLAGS}

binaryFile.o:	binaryFile.cpp binaryFile.h
	${CC} -c -o binaryFile.o binaryFile.cpp ${CFLAGS}

.PHONY: clean

clean:
	rm *.o excBinaryFile
	rm binary_File.txt
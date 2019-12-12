CC = g++
CFLAGS = -Wall -std=c++11
EXEC_NAME = main5
INCLUDES =
LIBS =
OBJ_FILES = Circuit.o ANDx.o MUXx.o FA.o FunctionGate.o Gate.o InputGate.o OutputGate.o NANDx.o NORx.o NOTx.o ORx.o XORx.o XNORx.o Parseur.o ParseurVCD.o Trace.o Chronogramme.o BmpIO.o main5.o Signal.o
OBJ_VCD_FILES =  ./build/VCDFile.o ./build/VCDParser.o ./build/VCDValue.o ./build/VCDFileParser.o ./build/VCDScanner.o
all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(OBJ_VCD_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<


clean :
	rm -f $(EXEC_NAME) $(OBJ_FILES)

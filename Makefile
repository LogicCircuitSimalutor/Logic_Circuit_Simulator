CC = g++
CFLAGS = -Wall -std=c++11
EXEC_NAME = main5
INCLUDES =
LIBS =
<<<<<<< HEAD
OBJ_FILES = Circuit.o ANDx.o FunctionGate.o Gate.o InputGate.o NANDx.o NORx.o NOTx.o ORx.o XORx.o Parseur.o ParseurVCD.o main5.o
=======
OBJ_FILES = Circuit.o  ANDx.o FunctionGate.o Gate.o InputGate.o NANDx.o NORx.o NOTx.o ORx.o XORx.o MUXx.o Parseur.o ParseurVCD.o main.o
>>>>>>> FEAT_MUX	Start of MUX class, need improvements to calculate output ect
OBJ_VCD_FILES =  ./build/VCDFile.o ./build/VCDParser.o ./build/VCDValue.o ./build/VCDFileParser.o ./build/VCDScanner.o
all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(OBJ_VCD_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<


clean :
	rm -f $(EXEC_NAME) $(OBJ_FILES)

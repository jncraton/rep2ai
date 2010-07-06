BUILD = build
SRC = src

CPP  = g++
CC   = gcc
OBJ  = $(BUILD)/Action.o \
       $(BUILD)/ActionList.o \
       $(BUILD)/AI.o \
       $(BUILD)/main.o \
       $(BUILD)/Rep2AI.o \
       $(BUILD)/Replay.o \
       $(BUILD)/unpack.o
LIBS =  -lz -lmingw32
INCS =  
CXXINCS = 
BIN  = rep2ai.exe
CXXFLAGS = $(CXXINCS) -Wall -O2
CFLAGS = $(INCS)
RM = del

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(LIBS) $(CXXFLAGS)
	
$(BUILD)/Action.o: $(SRC)/Action.cpp
	$(CPP) -c $(SRC)/Action.cpp -o $(BUILD)/Action.o $(CXXFLAGS)
	
$(BUILD)/ActionList.o: $(SRC)/ActionList.cpp
	$(CPP) -c $(SRC)/ActionList.cpp -o $(BUILD)/ActionList.o $(CXXFLAGS)
	
$(BUILD)/AI.o: $(SRC)/AI.cpp
	$(CPP) -c $(SRC)/AI.cpp -o $(BUILD)/AI.o $(CXXFLAGS)
	
$(BUILD)/main.o: $(SRC)/main.cpp
	$(CPP) -c $(SRC)/main.cpp -o $(BUILD)/main.o $(CXXFLAGS)
	
$(BUILD)/Rep2AI.o: $(SRC)/Rep2AI.cpp
	$(CPP) -c $(SRC)/Rep2AI.cpp -o $(BUILD)/Rep2AI.o $(CXXFLAGS)
	
$(BUILD)/Replay.o: $(SRC)/Replay.cpp
	$(CPP) -c $(SRC)/Replay.cpp -o $(BUILD)/Replay.o $(CXXFLAGS)
	
$(BUILD)/unpack.o: $(SRC)/unpack.cpp
	$(CPP) -c $(SRC)/unpack.cpp -o $(BUILD)/unpack.o $(CXXFLAGS)
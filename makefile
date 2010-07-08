BUILD     = build
SRC       = src

WXLIBNAME = wxmsw28
CPP       = g++.exe
LINK      = g++.exe
WINDRES   = windres.exe

OBJ       = $(BUILD)/Action.o \
            $(BUILD)/ActionList.o \
            $(BUILD)/AI.o \
            $(BUILD)/Rep2AI.o \
            $(BUILD)/Replay.o \
            $(BUILD)/unpack.o
            
LIBS      = -l$(WXLIBNAME) \
            -lwxpng \
            -lwxtiff \
            -lwxjpeg \
            -lwxzlib \
            -lkernel32 \
            -luser32 \
            -lgdi32 \
            -lcomdlg32 \
            -lwinmm \
            -lshell32 \
            -lcomctl32 \
            -lole32 \
            -loleaut32 \
            -luuid \
            -lrpcrt4 \
            -ladvapi32 \
            -lodbc32

CXXFLAGS  = -ffunction-sections \
            -fdata-sections \
            -fno-exceptions \
            -fno-pcc-struct-return \
            -fstrict-aliasing \
            -Wall \
            -D__WXMSW__ \
            -D__GNUWIN32__ \
            -D__WIN95__ \
            -s

LDFLAGS   = -s -Wl,--gc-sections
RM        = rm -f

.PHONY: all all-before all-after clean clean-custom
all: all-before rep2ai.exe rep2ai_cl.exe all-after

clean: clean-custom
	$(RM) $(OBJ) "$(BIN)"

all-before:

rep2ai.exe: $(OBJ) $(BUILD)/App.o $(BUILD)/MainFrame.o
	$(LINK) $(OBJ) $(BUILD)/App.o $(BUILD)/MainFrame.o -o "rep2ai.exe" -mwindows $(LIBS) $(LDFLAGS)

rep2ai_cl.exe: $(OBJ) $(BUILD)/main.o
	$(LINK) $(OBJ) $(BUILD)/main.o -o "rep2ai_cl.exe" $(LIBS) $(LDFLAGS)

$(BUILD)/App.o: $(SRC)/App.cpp $(SRC)/App.h $(SRC)/MainFrame.h  
	$(CPP) -c $(SRC)/App.cpp -o $(BUILD)/App.o $(CXXFLAGS)

$(BUILD)/Resource.o: $(SRC)/Resource.rc icons/main.ico
	$(WINDRES) $(SRC)/Resource.rc $(BUILD)/Resource.o

$(BUILD)/MainFrame.o: $(SRC)/MainFrame.cpp $(SRC)/MainFrame.h  
	$(CPP) -c $(SRC)/MainFrame.cpp -o $(BUILD)/MainFrame.o $(CXXFLAGS)
	
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
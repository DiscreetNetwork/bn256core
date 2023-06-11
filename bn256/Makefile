CC = gcc
CPP = g++
BUILD = build
LIBF=linux
CFLAGS = -c -O3 -Wall -fPIC
INC=.
SOURCE=.
AS = nasm
ASFLAGS=-felf64

all: dirs core clean

build/verify.o: $(SOURCE)/verify.c $(SOURCE)/verify.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/verify.c -o $(BUILD)/verify.o

build/gfp_items.o: $(SOURCE)/gfp_items.asm
	$(AS) $(ASFLAGS) $(SOURCE)/gfp_items.asm -o $(BUILD)/gfp_items.o

build/sha256.o: $(SOURCE)/sha256.c $(SOURCE)/sha256.h $(SOURCE)/util.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/sha256.c -o $(BUILD)/sha256.o

build/hmacsha256.o: $(SOURCE)/hmacsha256.c $(SOURCE)/hmacsha256.h $(SOURCE)/sha256.h $(SOURCE)/util.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/hmacsha256.c -o $(BUILD)/hmacsha256.o

build/BigInt.o: $(SOURCE)/BigInt.c $(SOURCE)/BigInt.h $(SOURCE)/types.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/BigInt.c -o $(BUILD)/BigInt.o

build/constants.o: $(SOURCE)/constants.c $(SOURCE)/constants.h $(SOURCE)/BigInt.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/constants.c -o $(BUILD)/constants.o

build/gfp_generic.o: $(SOURCE)/gfp_generic.c $(SOURCE)/gfp_generic.h $(SOURCE)/constants.h $(SOURCE)/types.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/gfp_generic.c -o $(BUILD)/gfp_generic.o

build/gfp.o: $(SOURCE)/gfp.c $(SOURCE)/constants.h $(SOURCE)/gfp_generic.h $(SOURCE)/types.h $(SOURCE)/BigInt.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/gfp.c -o $(BUILD)/gfp.o

build/curve.o: $(SOURCE)/curve.c $(SOURCE)/types.h $(SOURCE)/gfp.h $(SOURCE)/gfp_generic.h $(SOURCE)/constants.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/curve.c -o $(BUILD)/curve.o

build/gfp2.o: $(SOURCE)/gfp2.c $(SOURCE)/types.h $(SOURCE)/gfp.h $(SOURCE)/gfp_generic.h $(SOURCE)/constants.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/gfp2.c -o $(BUILD)/gfp2.o

build/twist.o: $(SOURCE)/twist.c $(SOURCE)/types.h $(SOURCE)/gfp2.h $(SOURCE)/constants.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/twist.c -o $(BUILD)/twist.o

build/gfp6.o: $(SOURCE)/gfp6.c $(SOURCE)/types.h $(SOURCE)/gfp2.h $(SOURCE)/gfp.h $(SOURCE)/gfp_generic.h $(SOURCE)/constants.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/gfp6.c -o $(BUILD)/gfp6.o

build/gfp12.o: $(SOURCE)/gfp12.c $(SOURCE)/gfp6.h $(SOURCE)/constants.h $(SOURCE)/types.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/gfp12.c -o $(BUILD)/gfp12.o

build/hash.o: $(SOURCE)/hash.c $(SOURCE)/gfp.h $(SOURCE)/gfp_generic.h $(SOURCE)/constants.h $(SOURCE)/types.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/hash.c -o $(BUILD)/hash.o

build/pairing.o: $(SOURCE)/pairing.c $(SOURCE)/curve.h $(SOURCE)/gfp.h $(SOURCE)/gfp_generic.h $(SOURCE)/gfp2.h $(SOURCE)/gfp6.h $(SOURCE)/gfp12.h $(SOURCE)/types.h $(SOURCE)/constants.h $(SOURCE)/twist.h
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/pairing.c -o $(BUILD)/pairing.o

build/random.o: $(SOURCE)/random.c
	$(CC) $(CFLAGS) -I$(INC) $(SOURCE)/random.c -o $(BUILD)/random.o

# c++ stuff
build/exc.o: $(SOURCE)/exc.cpp $(SOURCE)/export.h
	$(CPP) $(CFLAGS) -I$(INC) $(SOURCE)/exc.cpp -o $(BUILD)/exc.o

build/bn256.o: $(SOURCE)/bn256.cpp $(SOURCE)/bn256.h $(SOURCE)/gfp.h $(SOURCE)/gfp_generic.h $(SOURCE)/constants.h $(SOURCE)/gfp2.h $(SOURCE)/gfp6.h $(SOURCE)/gfp12.h $(SOURCE)/curve.h $(SOURCE)/twist.h $(SOURCE)/pairing.h $(SOURCE)/BigInt.h $(SOURCE)/hash.h $(SOURCE)/export.h $(SOURCE)/random.h
	$(CPP) $(CFLAGS) -I$(INC) $(SOURCE)/bn256.cpp -o $(BUILD)/bn256.o

build/dllmain.o: $(SOURCE)/dllmain.cpp $(SOURCE)/export.h $(SOURCE)/gfp_generic.h
	$(CPP) $(CFLAGS) -I$(INC) $(SOURCE)/dllmain.cpp -o $(BUILD)/dllmain.o

dirs: 
	mkdir -p $(BUILD)
	mkdir -p $(LIBF)

core: $(BUILD)/verify.o $(BUILD)/gfp_items.o $(BUILD)/sha256.o $(BUILD)/hmacsha256.o $(BUILD)/BigInt.o $(BUILD)/constants.o $(BUILD)/gfp_generic.o $(BUILD)/gfp.o $(BUILD)/curve.o $(BUILD)/gfp2.o $(BUILD)/twist.o $(BUILD)/gfp6.o $(BUILD)/gfp12.o $(BUILD)/hash.o $(BUILD)/pairing.o $(BUILD)/random.o $(BUILD)/exc.o $(BUILD)/bn256.o $(BUILD)/dllmain.o
	$(CPP) -shared -o $(LIBF)/bn256.so $(BUILD)/sha256.o $(BUILD)/hmacsha256.o $(BUILD)/BigInt.o $(BUILD)/constants.o $(BUILD)/gfp_generic.o $(BUILD)/gfp_items.o $(BUILD)/gfp.o $(BUILD)/curve.o $(BUILD)/gfp2.o $(BUILD)/twist.o $(BUILD)/gfp6.o $(BUILD)/gfp12.o $(BUILD)/hash.o $(BUILD)/pairing.o $(BUILD)/random.o $(BUILD)/exc.o $(BUILD)/bn256.o $(BUILD)/dllmain.o

clean:
	rm -f $(BUILD)/*.o

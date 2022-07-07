CC = -std=c11
CFLAGS = -Wall -Werror
LDLIBS = -lm -lssl -lcrypto
OUTPUT = libvxcrypto.so
UNIT = lib_unit_runner
SOURCES = encrypt.c decrypt.c util.c base64.c libvxcrypto.c
UNIT_SOURCES = encrypt.c decrypt.c util.c base64.c lib_unit_runner.c
OBJECTS = encrypt.o decrypt.o util.o base64.o libvxcrypto.o
UNIT_OBJECTS = encrypt.o decrypt.o util.o base64.o lib_unit_runner.o
.DEFAULT_GOAL := run

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	gcc $(CC) $(CFLAGS) $^ $(LDLIBS) -o $(OUTPUT)

unit_runner: $(UNIT_OBJECTS)
	gcc $(CC) $(CFLAGS) $^ $(LDLIBS) -o $(UNIT)

encrypt.o: encrypt.c
	gcc $(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

decrypt.o: decrypt.c
	gcc $(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

util.o: util.c
	gcc $(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

base64.o: base64.c
	gcc $(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

libvxcrypto.o: libvxcrypto.c
	gcc $(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

lib_unit_runner.o: lib_unit_runner.c
	gcc $(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

clean:
	@rm -rf $(OUTPUT) $(UNIT) $(OBJECTS)

run: clean
	@clear
	@cat ~/intro2.txt
	@echo "==============================="
	@echo "Building library libvxcrypto.so ..."
	@echo "==============================="
	@echo ""
	@echo "==============================="
	@echo "Compiling ..."
	@echo "==============================="
	@echo ""
	@make all --no-print-directory
	@echo ""
	@echo "==============================="
	@echo "Build finished"
	@echo "==============================="
	@echo ""

test: clean
	@clear
	@cat ~/intro2.txt
	@echo "==============================="
	@echo "[UNIT] Running debug test for library libvxcrypto.so"
	@echo "==============================="
	@echo ""
	@echo "==============================="
	@echo "Compiling ..."
	@echo "==============================="
	@echo ""
	@make unit_runner --no-print-directory
	@echo ""
	@echo "==============================="
	@echo "Starting test executable ..."
	@echo "==============================="
	@echo ""
	@./lib_unit_runner
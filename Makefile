all: aarch64-ldxr-stxr-match aarch64-ldxr-stxr-samples.o

# cross compile sample .text
aarch64-ldxr-stxr-samples.o: aarch64-ldxr-stxr-samples.S
	aarch64-linux-gnu-gcc -o $@ -c $<

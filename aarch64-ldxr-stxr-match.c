#include <stdio.h>

#define STXR(x)	(((x) & 0x3fc00000) == 0x08000000)
#define LDXR(x)	(((x) & 0x3fc00000) == 0x08400000)

#define ARRAY_SZ(x) (sizeof(x) / sizeof((x)[0]))

struct insn {
	unsigned int op;
	char *mnemonic;
};
#define INSN(x,y) { (x), (y) }

int main(int argc, char *argv[])
{
	int i = 0;
	int matches = 0;
	struct insn insns[] = {
		INSN(0x885f7c00, "ldxr	w0, [x0]"),
		INSN(0xc85f7c00, "ldxr	x0, [x0]"),
		INSN(0x085f7c00, "ldxrb	w0, [x0]"),
		INSN(0x485f7c00, "ldxrh	w0, [x0]"),
		INSN(0x887f0000, "ldxp	w0, w0, [x0]"),
		INSN(0xc87f0000, "ldxp	x0, x0, [x0]"),
		INSN(0x88007c00, "stxr	w0, w0, [x0]"),
		INSN(0xc8007c00, "stxr	w0, x0, [x0]"),
		INSN(0x08007c00, "stxrb	w0, w0, [x0]"),
		INSN(0x48007c00, "stxrh	w0, w0, [x0]"),
		INSN(0x88200000, "stxp	w0, w0, w0, [x0]"),
		INSN(0xc8200000, "stxp	w0, x0, x0, [x0]"),
		INSN(0x885ffc00, "ldaxr	w0, [x0]"),
		INSN(0xc85ffc00, "ldaxr	x0, [x0]"),
		INSN(0x085ffc00, "ldaxrb	w0, [x0]"),
		INSN(0x485ffc00, "ldaxrh	w0, [x0]"),
		INSN(0x887f8000, "ldaxp	w0, w0, [x0]"),
		INSN(0xc87f8000, "ldaxp	x0, x0, [x0]"),
		INSN(0x8800fc00, "stlxr	w0, w0, [x0]"),
		INSN(0xc800fc00, "stlxr	w0, x0, [x0]"),
		INSN(0x0800fc00, "stlxrb	w0, w0, [x0]"),
		INSN(0x4800fc00, "stlxrh	w0, w0, [x0]"),
		INSN(0x88208000, "stlxp	w0, w0, w0, [x0]"),
		INSN(0xc8208000, "stlxp	w0, x0, x0, [x0]"),
	};

	while (i < ARRAY_SZ(insns)) {
		if (STXR(insns[i].op))
			printf("0x%08lx \"%s\" is a stxr\n", insns[i].op, insns[i].mnemonic), matches++;
		if (LDXR(insns[i].op))
			printf("0x%08lx \"%s\" is a ldxr\n", insns[i].op, insns[i].mnemonic), matches++;

		i++;
	}

	printf("%d of %d insns matched\n", matches, ARRAY_SZ(insns));

	return 0;
}

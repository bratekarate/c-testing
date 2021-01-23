CC=tcc
CFLAGS=-I.
DEPS=
OUTDIR=out
OBJ=$(OUTDIR)/$(NAME).o

$(OUTDIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

CC=tcc
CFLAGS=-I.
CLIBS=-lcurl
DEPS=
SRCDIR=src
OUTDIR=out
OBJ=$(OUTDIR)/$(NAME).o

$(OUTDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

watch:
	@command -v inotifywait > /dev/null || \
		{ \
			echo "Please install inotifywait"; exit 2; \
		}
	@while true ; do \
		NAME=$$(inotifywait \
			-e create,modify \
			--include '.*\.c' \
			--format '%w%f' \
			"$(SRCDIR)"); \
		export NAME=$$(basename "$${NAME%%.c}"); \
		($(MAKE)); \
	done



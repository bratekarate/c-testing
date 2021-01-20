#!/bin/sh

inotifywait -m -e modify --include '.*\.c' --format '%w%f' "${1:-./src}" |
  while IFS= read -r F; do
    OUT=out/$(basename "${F%%.c}")
    tcc -o "$OUT" \
      $(pkg-config --libs --cflags nettle) \
      $(pkg-config --libs --cflags olm) \
      $(pkg-config --libs --cflags python3) -lpython3 \
      $(pkg-config --libs --cflags openssl) \
      "$F"
    #"$OUT"
    #printf 'Exit code: %s\n\n' $?
  done

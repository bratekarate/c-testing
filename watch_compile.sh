#!/bin/sh
SRC=${1:-./src}

PKGS=
#PKGS=\
#nettle,\
#olm,\
#openssl,\
#python3

set --
OLDIFS=$IFS
IFS=,
for PKG in $PKGS; do
  set -- "$@" $(pkg-config --libs --cflags "$PKG")
done

#EXTRA_FLAGS=-lpython3
EXTRA_FLAGS=

for FLAG in $EXTRA_FLAGS; do
  set -- "$@" "$FLAG"
done
IFS=$OLDIFS

inotifywait -m -e modify --include '.*\.c' --format '%w%f' "$SRC" |
  while IFS= read -r F; do
    OUT=out/$(basename "${F%%.c}")
    tcc -o "$OUT" $@ "$F"
    #"$OUT"
    #printf 'Exit code: %s\n\n' $?
  done

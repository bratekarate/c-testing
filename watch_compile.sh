#!/bin/sh

inotifywait -m -e modify --include '.*\.c' --format '%w%f' "${1:-./src}" |
  while IFS= read -r F; do
    OUT=out/$(basename "${F%%.c}")
    tcc -o "$OUT" "$F"
    "$OUT"
    printf 'Exit code: %s\n\n' $?
  done

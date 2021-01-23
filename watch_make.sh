#!/bin/sh
SRC=${1:-./src}

find "$SRC" -type f -name '*.c' -exec sh -c 'NAME=$(basename "${1%%.c}") make' _ {} \;

inotifywait -m -e modify --include '.*\.c' --format '%w%f' "$SRC" |
  while IFS= read -r F; do
    NAME=$(basename "${F%%.c}") make
  done

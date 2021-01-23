#!/bin/sh
SRC=${1:-./src}

find "$SRC" -type f -name '*.c' -exec sh -c 'NAME=$(basename "${1%%.c}") make' _ {} \;

#while :; do echo src/socket_client.c; sleep 1; done |
inotifywait -m -e modify --include '.*\.c' --format '%w%f' "$SRC" |
  while IFS= read -r F; do
    echo "NAME=$(basename "${F%%.c}") make"
    NAME=$(basename "${F%%.c}") make
  done

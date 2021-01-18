import sys
import pbkdf2
from Crypto.Hash import SHA512
from Crypto.Hash import HMAC

passphrase = sys.argv[1]
iterations = sys.argv[2]

salt = b''
with open("/tmp/salt", "rb") as f:
    byte = f.read(1)
    salt += byte
    while byte != b"":
        # Do stuff with byte.
        byte = f.read(1)
        salt += byte

key = pbkdf2.PBKDF2(passphrase, salt, int(
    iterations), SHA512, HMAC).hexread(64)
print(key)

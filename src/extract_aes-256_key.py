import sys
import pbkdf2
from Crypto.Hash import SHA512
from Crypto.Hash import HMAC
# from Crypto.Cipher import AES

passphrase = sys.argv[1]
iterations = sys.argv[2]
# iv = sys.argv[3]

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

# TODO: make decryption work
# cipher = AES.new(key, AES.MODE_CTR, iv)

# with open("/tmp/json_enc", "rb") as f:
    # content = f.read()
    # result = cipher.decrypt(content)
    # print(result)


import os
from base64 import b64encode
import bitarray


def generate_key(length):
    # generate random key 128 bits (16 bytes)
    key = os.urandom(length)
    # print(key)

    # convert string key to unicode
    token = b64encode(key).decode('utf-8')
    # print(token)

    # convert unicode to binary
    b = bitarray.bitarray()
    b.fromstring(token)
    # print(b.to01())
    # print(len(b.to01()))
    return b.to01()

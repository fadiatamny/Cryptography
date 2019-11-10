import sys

if len(sys.argv) != 4:
    print("Usage:" + sys.argv[0] + " file1 file2 out")
    sys.exit(1);

file1bytes = open(sys.argv[1], "rb").read()
file2bytes = open(sys.argv[2], "rb").read()

if len(file1bytes) != len(file2bytes):
    print("Input files need to have the same length.")
    sys.exit(2)

result = bytearray()
with open(sys.argv[3], "wb") as f:
    for i in range(0, len(file1bytes)):
        result.append(file1bytes[i] ^ file2bytes[i])
    f.write(result)
sys.exit(0)

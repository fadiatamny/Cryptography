import sys

if len(sys.argv) != 3:
    print("Usage:" + sys.argv[0] + " word charcount")
    sys.exit(1);

fullWords = int(sys.argv[2]) // len(sys.argv[1])
remainder = int(sys.argv[2]) % len(sys.argv[1])

for i in range(0, fullWords):
    sys.stdout.write(sys.argv[1])
for i in range(0, remainder):
    sys.stdout.write(sys.argv[1][i])

sys.exit(0)

def GetRandomNumber(seed):
    seed = (seed * 1103515245) + 12345
    n = int(seed / 65536) % 32768
    return [n,seed]

def test(a,b):
    c = 0
    a = a << 17

    while True:
        a = a+1
        print(a)
        res = int((a / 65536) % 32768)
        print(res)
        if res == b:
            print(a)
            break
    


s = int(input())

res = GetRandomNumber(s)
s = res[1]
a = res[0]

res = GetRandomNumber(s)
s = res[1]
b = res[0]

test(a,b)
import random

dicinary = {}
letters = []


def insertLetters():

    i = 97
    while i < 123:
        letters.append(chr(i))
        i += 1

def gen():

    for c in letters:
        
        x = chr(random.randint(97,122))
        while x in dicinary.values():
            x = chr(random.randint(97,122))

        dicinary[c] = x

def enc(s):
    ret = ""
    for c in s:
        if ord(c) >= 97 and ord(c) <= 122:
            ret+=(dicinary.get(c))
        else:
            ret+=(c)

    return ret

def dec(s):
    ret = ""
    for c in s:
        if ord(c) >= 97 and ord(c) <= 122:
            for key, value in dicinary.items(): 
                if c == value: 

                    ret += key 
        else:
            ret+=(c)

    return ret

insertLetters()
gen()

tests = ["ABC","LETS TEST THIS CODE","THIS IS A TEST"]

for s in tests:
    decre = enc(s.lower())
    print(s, "\t",decre,"\t", dec(decre))
    print("\n")

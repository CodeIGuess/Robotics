import sys
#f = list(open("lolxd/src/main.cpp").read())
f = list("snake_case_test camelCaseTest")
#f = list(open(sys.argv[0], "r").read())

for a in range(len(f)-1):
    if a > len(f):
        break
    c = f[a:a+2]
    if len(c) != 0 and c[0] == "_" and c[1].lower() in "qwertyuiopasdfghjklzxcvbnm":
        del f[a]
        f[a] = f[a].upper()

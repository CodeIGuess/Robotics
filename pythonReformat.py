import sys
f = list(open("lolxd/main.cpp"))
#f = list(open(sys.argv[0], "r").read())

for a in range(len(f)-1):
    c = f[a:a+1]
    print(c)
    #if c[0] == "_" and c[1].lower() in "qwertyuiopasdfghjklzxcvbnm":
    #    f[2]

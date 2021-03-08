d = {1:"hello","world":2,"test":3}
print (d)
print (d[1])
print (d["world"])
d[1] = "new 1"
print (d[1])
d.setdefault(1,"2")
print (d)
d.setdefault(3,"3!!default")
print (d)


del d[1]

print(d)
del d['world']

print(d)
del d[3]
print(d)
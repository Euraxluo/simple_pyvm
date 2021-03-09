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

d[4]="test2"
print ("sorted")
print(d)
print ("keys......")
print (d.keys())
for k in d.keys():
    print(k)
    print(d[k])


print ("values......")
for v in d.values():
    print (v)

print ("items......")
print(d.items())
for k,v in d.items():
    print(k)
    print(d[k])
    print(";")

print ("container......")
for k in d:
    print(k)
    print(d[k])
    print(";")

print ("iterkeys......")
for k in d.iterkeys():
    print(k)
    print(d[k])
    print(";")

print ("itervalues......")
for v in d.itervalues():
    print (v)

print ("iteritems......")
for k,v in d.iteritems():
    print(k)
    print(d[k])
    print(";")


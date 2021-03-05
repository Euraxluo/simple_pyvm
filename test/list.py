list = [1,2,3]
print(list)
list = ["4","5","6"]
print(list)
list = [7,"832","9"]
print(list)

print(list[1])
strx="Test"
print(strx[0])

if "832" in list:
    print("yes")
else:
    print ("no")

if "3" in list:
    print("yes")
else:
    print("no")

if "3" not in list:
    print("yes")
else:
    print ("no")

if "Eu" in "Euraxluo":
    print("Eu in Euraxluo,yes")
else:
    print("Eu in Euraxluo,yes")



list.append([1,2,3])
print(list)

list.insert(0,[1,2,3])
print(list)

# print (list.index('832',0))
# print (list.index('832',1))
# print (list.index('832',2))
# print (list.index('832',0,1))
# print (list.index('832'))

list[1]=["t","e","s","t"]
print(list)
list[1]=["t","e","s","t","2"]
print(list)


print ("remove from list")

list.pop(-2)
print(list)

list.pop(0)
print(list)

list.pop()
print(list)

list.remove('832')
print(list)


list.append("xixixi")
print(list)

del list[-2]
print(list)


del list[-1]
print(list)

while True:
    # list.append(0)
    print(list)
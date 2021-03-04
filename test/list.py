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
import test_overload
print ("TEST BEGIN!!!")
a = test_overload.A(1)
b = test_overload.A(2)
c = a+b
print (a)
print (b.value)
print (c.value)

print("TEST SUCCESS!!!")
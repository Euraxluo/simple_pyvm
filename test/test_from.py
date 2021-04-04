# import test_overload
from test_overload import A as B
print ("TEST BEGIN!!!")
print(B)
a = B(1)
b = B(2)
c = a+b
print (a)
print (b.value)
print (c.value)

print("TEST SUCCESS!!!")
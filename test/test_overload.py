m = dict()
class A(object):

    def __init__(self,value):
        self.value=value

    def __add__(self, other):
        return A(self.value+other.value)

    def __getattr__(self, item):
        print ("__getattr__",item,m[item])
        return m[item]

    def __setattr__(self, key, value):
        m[key] = value
        print("__setattr__",m)

print ("TEST BEGIN!!!")
a = A(1)
b = A(2)
c = a+b
print (a)
print (b.value)
print (c.value)

print("TEST SUCCESS!!!")
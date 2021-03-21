class A(object):
    value = 1
    def __init__(self,v):
        self.value = v

    def say(self,new_v):
        self.value = new_v
        print (self.value)

print(A)

a = A("hello")
print(a)
print(a.value)

a.say("world")



a.field = "hello world"
print(a.field)



a = A(1)
b = A(2)
print(a.value)
print(b.value)
A.field = "A.field"
a.field = "a.field"


print(a.field)
print(b.field)

#bound method
#append bound the lst
a = A(3)
lst = list()
lst.append("test")
print (lst)
a.lfunc = lst.append
a.lfunc("case")
print(lst)

a = A(1)
b = A(2)
def func(self,s):
    print(self.value,s)
a.bar = func
A.bar = func
a.bar(a,"hello")
b.bar("world")


class B(object):
    def __init__(self,len):
        self.len =len
    def __len__(self):
        return self.len
b = B(10000)
print(len(b))


print("TEST SUCCESS!!!")
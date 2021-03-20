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





print("TEST SUCCESS!!!")
class Z(object):
    def say(self):
        print(Z)

class X(Z):
    def say(self):
        print(X)

class Y(Z):
    def say(self):
        print(Y)

class A(X,Y):
    pass
    # def say(self):
    #     print(A)
class B(Z):
    pass
    # def say(self):
    #     print("B")

class C(B,A):
    pass

c = C()
c.say()

print("TEST SUCCESS!!!")
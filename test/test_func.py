def foo():
    return "121"


print(foo())

def foo(x):
    return (x)

print (foo(213))


def foo(a,b):

    return (a+b)
print (foo(1,2))



def foo(a,b):

    return a+b
print (foo(b=2,a=1))

#10
def foo(*args):
    t = 0
    for i in args:
        t+=i
    return t


print (foo(1,2,3,4))

#12
def foo(a,b=2,* args,** kwargs):
    print (a)#3
    print (b)#2
    t = 0
    print ("args:")
    print (args)
    for i in args:
        t+=i
    print (kwargs)
    for i in kwargs.keys():
        t+=kwargs[i]
    return t

#12
m = foo(3, 1,1,0, c=5, d=6)
print (m)



def foo(a, *alist):
    return alist[0] + alist[1]

print foo(2, 3, 4)



print("TEST SUCCESS!!!")
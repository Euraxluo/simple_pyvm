def foo():
    print("foo")

print(foo())

def foo():
    a="dsa"
    print("foo"+a)

print(foo())

def foo():
    a="dsa"
    print("foo"+a)
    return a

print(foo())


def fqq(x):
    print(x)

print(fqq(1))


def fqq(x):
    a=1
    print(x+a)

print(fqq(1))

def fqq(x):
    a=1
    print(x+a)
    return a+x

print(fqq(1))


def add(a,b):
    return a+b

print(add(1,2))


def add(a,b):
    c=3
    print(a+b+c)
    return a+b+c

print(add(1,2))


def add(a,b,c):
    d=c
    print(a+b+d)
    return a+b+d

print(add(1,2,3))


def add(a,b,c=4):
    d=c
    print(a+b+d)
    return a+b+d

print(add(1,2))


def add(a,b=100,c=4):
    d=c
    print(a+b+d)
    return a+b+d

print(add(1))


def make_fun(x):
    a=1
    def add(a=a,b=2,c=x):
        return a+b+c
    return add

adds=make_fun(100)
a=10
b=20
c=3
print(adds())
print(adds(a))
print(adds(a,b))
print(adds(a,b,c))

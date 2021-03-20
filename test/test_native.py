s="Hello World"
print(s)
print(len(s))

def my_len():
    s="Hello World"
    def x(m):
        print(m)
    print( x(s))
    return len(s)
print(my_len())


s="Hello World"
def my_len(o=s):
    return len(o)
print(my_len())
print(my_len(s+'121'))
print("TEST SUCCESS!!!")
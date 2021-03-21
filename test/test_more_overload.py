m = dict()
class Test(object):
    def __init__(self):
        print ("__init__")

    def __add__(self, other):
        print ("__add__")

    def __sub__(self, other):
        print ("__sub__")

    def __mul__(self, other):
        print ("__mul__")

    def __div__(self, other):
        print ("__div__")


    def __lt__(self, other):
        print ("__lt__")

    def __gt__(self, other):
        print ("__gt__")

    def __le__(self, other):
        print ("__le__")

    def __ge__(self, other):
        print ("__ge__")

    def __eq__(self, other):
        print ("__eq__")

    def __ne__(self, other):
        print ("__ne__")

    def __len__(self):
        print ("__len__")

    def __abs__(self):
        print ("__abs_")

    def __complex__(self):
        print ("__complex__")

    def __int__(self):
        print("__int__")
        return 1

    def __float__(self):
        print ("__float__")

    def __hex__(self):
        print ("__hex__")

    def __oct__(self):
        print ("__oct__")

    def __hash__(self):
        print ("__hash__")

    def __pow__(self, power, modulo=None):
        print ("__pow__")

    def __call__(self, *args, **kwargs):
        print ("__call__",args,kwargs)

    def __getitem__(self, item):
        print ("__getitem__",item)
        # return None

    def __setitem__(self, key, value):
        print ("__setitem__",key,value)

    def __getattr__(self, item):
        print ("__getattr__",m,item,m[item])
        return m[item]

    def __setattr__(self, key, value):
        m[key] = value
        print("__setattr__",m)
print("TEST BEGIN!!!")
x = Test()
# y = Test()
# add = x+y
# sub = x-y
# mul = x*y
# div = x/y
# lt = x<y
# gt = x>y
# le = x<=y
# ge = x>=y
# eq = x==y
# ne = x!=y
#
# len(x)
# abs(x)
# pow(x,y)
# complex(x)
# int(x)
# print(int(12))
# float(x)
# hex(x)
# oct(x)
# hash(x)
# x("sas",3123,q=1)
# x["test"] = "setItem"
# x["test"]
# x.foo = 1
# x.foo
print("TEST SUCCESS!!!")
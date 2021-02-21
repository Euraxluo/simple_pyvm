global x
x = 0


def func():
    global x
    x = "ewqeqwewq"


func()
print(x)


def goo():
    return None


if goo() is None:
    print(True)
    print(None)
    print(False)
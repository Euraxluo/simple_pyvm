# global x
# x = 0
#
# # g
# def func():
#     global x
#     x = "ewqeqwewq"
#
#
# func()
# print(x)
#
#
# #l
# def goo():
#     return None
#
#
# #b
# if goo() is None:
#     print(True)
#     print(None)
#     print(False)


#e
def func():
    x = 2
    def say():
        # x=3
        print(x)
    return say
f = func()
f()
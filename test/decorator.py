# def call_cnt(fn):
#     cnt = [0,]
#     def inner_func(*args):
#         cnt[0]+=1
#         print (cnt[0])
#         return fn
#     return inner_func
#
# @call_cnt
# def add(a,b=2):
#     print (a+b)
#     return a+b
#
# # print (add(1,2))
# # print (add(2,3))
# # print (add(4,5))
# x = add(1,2)
# # print(x(1,2))

def func(x = 5):
    def say():
        print x
    x = 3
    print x
    return say
f = func()
f()

def foo():
    x = 2
    def bar():
        print x
    x = 3
    print x
    return bar
f = foo()
f()
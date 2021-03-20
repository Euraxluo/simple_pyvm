def call_cnt(fn):
    cnt = [0,] #build list,store defer,load closure(cnt,fn)
    def inner_func(*args):
        cnt[0]+=1
        print ("cnt:",cnt[0])
        return fn(*args)
    return inner_func

#add = call_cnt(add) == inner_func
@call_cnt
def add(a,b):
    return a+b

print("add:",add(1,2))
print("add:",add(1,3))
print("add:",add(1,4))
print("add:",add(1,5))

print("TEST SUCCESS!!!")
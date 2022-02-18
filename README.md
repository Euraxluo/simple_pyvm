# simple_pyvm

`bash test/test.sh ../cmake-build-debug/simple_pyvm`
```bash
/home/yons/Project/luoyou/simple_pyvm/test
 test_builtin.py test_decorator.py test_define_class.py test_dict.py test_from.py test_func.py test_hello.py test_if.py test_import.py test_legb.py test_list.py test_method.py test_more_overload.py test_name__.py test_native.py test_object_compare.py test_overload.py test_param.py test_super.py test_token.py test_type.py test_unpack.py test_var.py test_while.py
lexical_analysis.py  test_define_class.py  test_hello.py   test_list.py           test_native.py          test.sh        test_unpack.py
show_co.py           test_dict.py          test_if.py      test_method.py         test_object_compare.py  test_super.py  test_var.py
test_builtin.py      test_from.py          test_import.py  test_more_overload.py  test_overload.py        test_token.py  test_while.py
test_decorator.py    test_func.py          test_legb.py    test_name__.py         test_param.py           test_type.py
*******************OriginVM*******************
*******************SimpleVM*******************
**********************************************
**********************************************
原生虚拟机结果
total test case : 24
success test case : 24
error test case : 0
SimpleVM虚拟机结果
total test case : 24
success test case : 24
error test case : 0
```



useage:
1. build 

`cmake --build ./cmake-build-debug --target simple_pyvm -- -j 12`

2.run

`simple_pyvm/cmake-build-debug/simple_pyvm ../test/test_builtin.pyc` 

```shell
     ____          __   __                 _    __ __  ___
    / __ \ __  __ / /_ / /_   ____   ____ | |  / //  |/  /
   / /_/ // / / // __// __ \ / __ \ / __ \| | / // /|_/ / 
  / ____// /_/ // /_ / / / // /_/ // / / /| |/ // /  / /  
 /_/     \__, / \__//_/ /_/ \____//_/ /_/ |___//_/  /_/   
        /____/             _                             
                    /     (_
                   ()(/ ()/ 
     ______          /                __            
    / ____/__  __ _____ ____ _ _  __ / /__  __ ____ 
   / __/  / / / // ___// __ `/| |/_// // / / // __ \
  / /___ / /_/ // /   / /_/ /_>  < / // /_/ // /_/ /
 /_____/ \__,_//_/    \__,_//_/|_|/_/ \__,_/ \____/ 
type's mro is object, 
int's mro is object, 
str's mro is object, 
list's mro is object, 
map's mro is object, 
function's mro is object, 
method's mro is function, object, 
native function's mro is function, object, 
cell's mro is object, 
*magic number is 0xa0df303,168686339
moddate is 0x6069f150,1617555792,2021-04-04 17:03:12
argcount is 0x0 0
nlocals is 0x0 0
stacksize is 0x1 1
flags is 0x40 64
argcount is 0x2 2
nlocals is 0x4 4
stacksize is 0x4 4
flags is 0x43 67
argcount is 0x2 2
nlocals is 0x4 4
stacksize is 0x3 3
flags is 0x43 67
argcount is 0x2 2
nlocals is 0x4 4
stacksize is 0x3 3
flags is 0x43 67
argcount is 0x0 0
nlocals is 0x5 5
stacksize is 0x2 2
flags is 0x47 71

parse OK!
*magic number is 0xa0df303,168686339
moddate is 0x620faf40,1645195072,2022-02-18 14:37:52
argcount is 0x0 0
nlocals is 0x0 0
stacksize is 0x1 1
flags is 0x40 64

parse OK!
main_code is _argcount(0),_nlocals(0),_stack_size(1),_flag(64),_bytecodes(6500008300005A0100640000474864010053),_names[listlst],_consts[TEST SUCCESS!!!0],_var_names[],_free_vars[],_cell_vars[],_co_name(<module>),_file_name(test_builtin.py),_lineno(1),_notable(091B)
```
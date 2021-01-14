//
// Created by euraxluo on 2020/12/10.
//

#ifndef SIMPLE_PYVM_BINARYFILEPARSER_HPP
#define SIMPLE_PYVM_BINARYFILEPARSER_HPP

#include "codeObject.hpp"
#include "integer.hpp"
#include "helper.hpp"
#include "../object/integer.hpp"


class BinaryFileParser{
private:
    BufferedInputStream * file_stream;
    int current;
    ArrayList<String*> _string_table;
public:
    BinaryFileParser(BufferedInputStream* bufferedInputStream){
        file_stream = bufferedInputStream;
    }

    CodeObject *get_code_object() {
        //解析co结构
        int argcount = get_int();//第一个域是整型，表示参数个数
        int nlocals = get_int();//第二个域是整型，表示局部变量个数
        int stacksize = get_int();//第三个域是整型，表示操作数栈的最大深度
        int flags = get_int();//第四个域是整型，表示code的属性值
//        printf("argcount is 0x%x %d\n",argcount,argcount);
//        printf("nlocals is 0x%x %d\n",nlocals,nlocals);
//        printf("stacksize is 0x%x %d\n",stacksize,stacksize);
//        printf("flags is 0x%x %d\n",flags,flags);

        //接下来是字节码，以字符s开头，然后是整型，表示字节码长度，剩余字节就是字节
        String* byte_codes = get_byte_codes();
        auto * hex = Helper::string2hex(byte_codes);
        printf("\nbyte_codes is $%s$",hex->c_str());
        delete hex;

        //接下来是常量表，以字符'('开始,接下来是整型，表示这个list的长度，接下来就是第一个元素的类型,根据类型，可以知道我们应该取多少个字节
        ArrayList<Object*>* consts = get_consts();
//        printf("\nconsts length:%d\n",consts->size());
//        for (int i = 0; i < consts->size(); ++i) {
//            auto o =  consts->get(i);
//            printf("consts %d:%s\n",i,o->toString());
//        }

        ArrayList<Object*>* names = get_names();
//        printf("names length:%d\n",names->size());
//        for (int i = 0; i < names->size(); ++i) {
//            auto o=  names->get(i);
//            printf("names %d:%s\n",i,o->toString());
//        }


        ArrayList<Object*>* var_names = get_var_names();
//        printf("var_names length:%d\n",var_names->size());
//        for (int i = 0; i < var_names->size(); ++i) {
//            auto o=  var_names->get(i);
//            printf("var_names %d:%s\n",i,o->toString());
//        }


        ArrayList<Object*>* free_vars = get_free_vars();
//        printf("free_vars length:%d\n",free_vars->size());
//        for (int i = 0; i < free_vars->size(); ++i) {
//            auto o=  free_vars->get(i);
//            printf("free_vars %d:%s\n",i,o->toString());
//        }


        ArrayList<Object*>* cell_vars = get_cell_vars();
//        printf("cell_vars length:%d\n",cell_vars->size());
//        for (int i = 0; i < cell_vars->size(); ++i) {
//            auto o=  cell_vars->get(i);
//            printf("cell_vars %d:%s\n",i,o->toString());
//        }

        String* file_name = get_file_name();
        String* module_name = get_name();
        int begin_line_no = get_int();
        String* lnotab = get_no_table();

//        printf("file_name is %s\n",file_name->c_str());
//        printf("module_name is %s\n",module_name->c_str());
//        printf("begin_line_no is %d\n",begin_line_no);
//        String * lno_tab_hex = Helper::string2hex(lnotab);
//        printf("\nlno_tab is $%s$\n",lno_tab_hex->c_str());
//        delete lno_tab_hex;

        //实例化co对象
        return new CodeObject(argcount,nlocals,stacksize,flags,
                              byte_codes,consts,names,var_names,free_vars,cell_vars,
                              file_name,module_name,begin_line_no,lnotab);

    }

    String* get_byte_codes(){
        //接下来是字节码，以字符s开头，然后是整型，表示字节码长度，剩余字节就是字节码
        assert(file_stream->read() == 's');//校验，字节码格式
        return get_string();//获取这段字节码
    }
    String* get_string(){
        //这样定义一个字符串，前四个字节，表示一个整型，指示字符串长度，后面字符串长度个字节，就是字符串
        auto length = file_stream->read_int();
        String *str_ptr = new String(length);
        for (int i = 0; i < length; ++i) {
            char code =  file_stream->read();
            str_ptr->insert(i,code);
        }
        return str_ptr;
    }
    ArrayList<Object*>* get_consts(){
        // 常量表，以字符'('开始,
        // 然后是整型，表示这个tuple的长度length
        // 再读取length个元素
        // 每个元素先用一个字符标识类型，'s'表示string,'('表示元组
        if (file_stream->read() == '('){
            return get_tuple();
        }
        file_stream->unread();
        return nullptr;
    }
    ArrayList<Object*>* get_tuple(){
        //获取标识这个tuple的长度length
        size_t length = size_t (file_stream->read_int());
        String *str;
        ArrayList<Object*>* list = new ArrayList<Object*>(length);
        //接下来就读取length个元素
        for (int i = 0; i < length; ++i) {
            char obj_type = file_stream->read();
            switch (obj_type){
                case 'c'://code obj
                    list->push(get_code_object());
                    break;
                case 'i'://int
                    list->push(new Integer(file_stream->read_int()));
                    break;
                case 'N':
                    list->push(new Integer(0));
                    break;
                case 't'://t,也表示字符串，但是要加入到string_table中
                    str = get_string();
                    list->push(str);
                    _string_table.push(str);
                    break;
                case 's':
                    list->push(get_string());
                    break;
                case 'R':
                    list->push(_string_table.get(file_stream->read_int()));
                    break;
                default:
                    printf("parser,unrecognized type :%c\n",obj_type);
            }
        }
        return list;
    }
    ArrayList<Object*>* get_names(){
        if (file_stream->read() == '('){
            return get_tuple();
        }
        file_stream->unread();
        return nullptr;
    }

    ArrayList<Object*>* get_var_names(){
        if (file_stream->read() == '('){
            return get_tuple();
        }
        file_stream->unread();
        return nullptr;
    }

    ArrayList<Object*>* get_free_vars(){
        if (file_stream->read() == '('){
            return get_tuple();
        }
        file_stream->unread();
        return nullptr;
    }

    ArrayList<Object*>* get_cell_vars(){
        if (file_stream->read() == '('){
            return get_tuple();
        }
        file_stream->unread();
        return nullptr;
    }
    String* get_file_name(){
        return get_name();
    }
    String* get_name(){
        char ch = file_stream->read();
        if (ch=='s'){//file name
            return get_string();
        } else if (ch == 't'){//module name
            String* str_ptr=get_string();
            _string_table.push(str_ptr);
            return str_ptr;
        } else if (ch == 'R'){
            return _string_table.get(file_stream->read_int());
        }

        return nullptr;
    }

    String* get_no_table(){
        char ch = file_stream->read();
        if (ch != 's' && ch != 't'){
            file_stream->unread();
            return nullptr;
        }
        return get_string();
    }

    int get_int(){
        return file_stream->read_int();
    }

    CodeObject * parse(){
        int magic_number = file_stream->read_int();//拿魔数，四字节
        printf("*magic number is 0x%x,%d\n",magic_number,magic_number);
        int moddate = file_stream->read_int();//获取文件创建时间，四字节
        String * moddatatime = Helper::timestamp2time(moddate);
        printf("moddate is 0x%x,%d,%s\n",moddate,moddate,moddatatime->c_str());



        char object_type = file_stream->read();//读取第九个字节，标识符‘c’
        if (object_type == 'c'){
            CodeObject * result = get_code_object();
//            printf("\ncode:\n%s\n",result->toString());
            printf("\nparse OK!\n");
            return result;
        }
        return nullptr;
    }
};

#endif //SIMPLE_PYVM_BINARYFILEPARSER_HPP

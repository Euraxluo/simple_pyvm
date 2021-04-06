#include <iostream>
#include <stdio.h>
#include <runtime/interpreter.hpp>
#include "src/object/object.hpp"
#include "src/object/string.hpp"
#include "src/util/arrayList.hpp"
#include "src/util/bufferedInputStream.hpp"
#include "src/code/binaryFileParser.hpp"
#include "hashMap.hpp"
using namespace std;

int main(int argc, char **argv) {
    printf("     ____          __   __                 _    __ __  ___\n"
           "    / __ \\ __  __ / /_ / /_   ____   ____ | |  / //  |/  /\n"
           "   / /_/ // / / // __// __ \\ / __ \\ / __ \\| | / // /|_/ / \n"
           "  / ____// /_/ // /_ / / / // /_/ // / / /| |/ // /  / /  \n"
           " /_/     \\__, / \\__//_/ /_/ \\____//_/ /_/ |___//_/  /_/   \n"
           "        /____/             _                             \n");
    printf("                    /     (_\n"
           "                   ()(/ ()/ \n");
    printf("     ______          /                __            \n"
           "    / ____/__  __ _____ ____ _ _  __ / /__  __ ____ \n"
           "   / __/  / / / // ___// __ `/| |/_// // / / // __ \\\n"
           "  / /___ / /_/ // /   / /_/ /_>  < / // /_/ // /_/ /\n"
           " /_____/ \\__,_//_/    \\__,_//_/|_|/_/ \\__,_/ \\____/ \n");

    if (argc <= 1) {
        printf("vm need a parameter : filename\n");
        return 0;
    }

    BufferedInputStream::getInstance()->readFileName(argv[1]);
    BufferedInputStream::getInstance()->addDirPath("/mnt/c/home/Repository/simple_pyvm/src");
    BinaryFileParser parser(BufferedInputStream::getInstance());
    CodeObject *main_code = parser.parse();
    printf("main_code is %s \n", main_code->toString());

    Universe::genesis();//初始化一些值
    Interpreter::getInstance()->run(main_code);
    return 0;
}



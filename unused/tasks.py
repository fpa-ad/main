import invoke

#invoke.run("g++ -O3 -Wall -Werror -shared -std=c++20 -fPIC myutils.C -o libtest.so ")

invoke.run("g++ -O3 -Wall -shared -std=c++20 -fPIC -I /usr/include/python3.10/ -I ../src wrapper.cpp -o libFCpython.cpython-310-x86_64-linux-gnu.so -L ../lib -l FC -Wl,-rpath,.")
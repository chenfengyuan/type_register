# type_register
## build and run
`mkdir build && cd build && cmake .. && make && ./TypeRegister`
## results
    Int:int times: 2
    if int is Int: 1
    if long is Int: 0
    if float is Int: 0

    Float:double times: 3
    if int is Float: 0
    if double is Float: 1
    if float is Float: 1

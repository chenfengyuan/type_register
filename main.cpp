#include <iostream>
#include <type_traits>
using namespace std;
#if defined(__clang__)
enum { max_depth = 256};
#else
enum { max_depth = 100}
#endif

#define INIT_REGISTER(REG) \
    template<typename T, int N> \
    struct REG:REG<T, N-1>{ \
        enum {value = N}; \
    }; \
    template<typename T> \
    struct REG<T, 0>{ \
        enum {value = 0}; \
    }; \
    template <typename T> \
    REG<T, 0> get(REG<T, 0>){ \
        return {}; \
    }

#define GET_REGISTERED_TIMES(REG, T) \
    decltype(get(REG<T, max_depth>()))::value

#define REGISTER(REG, T) \
    REG<T, GET_REGISTERED_TIMES(REG, T) + 1> get(REG<T, GET_REGISTERED_TIMES(REG, T) + 1>){ \
        return {}; \
    }\
    static_assert(true, "")
#define IF_REGISTED(REG, T) \
    (GET_REGISTERED_TIMES(REG, T) > 0)


INIT_REGISTER(Int);
REGISTER(Int, int);
REGISTER(Int, int);

INIT_REGISTER(Float);
REGISTER(Float, float);
REGISTER(Float, float);
REGISTER(Float, double);
REGISTER(Float, double);
REGISTER(Float, double);


int main()
{
    cout << "Int:int times: " << GET_REGISTERED_TIMES(Int, int) << "\n";
    cout << "if int is Int: " << IF_REGISTED(Int, int) << "\n";
    cout << "if long is Int: " << IF_REGISTED(Int, long) << "\n";
    cout << "if float is Int: " << IF_REGISTED(Int, float) << "\n\n";

    cout << "Float:double times: " << GET_REGISTERED_TIMES(Float, double) << "\n";
    cout << "if int is Float: " << IF_REGISTED(Float, int) << "\n";
    cout << "if double is Float: " << IF_REGISTED(Float, double) << "\n";
    cout << "if float is Float: " << IF_REGISTED(Float, float) << "\n";
    std::enable_if<IF_REGISTED(Float, float), float>::type a{};
    (void)a;

    return 0;
}
#undef GET_REGISTERED_TIMES
#undef IF_REGISTED
#undef INIT_REGISTER
#undef REGISTER


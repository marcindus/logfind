#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>



//To do: doda petle do {} while(0) bez srednika tak jak w makrze ASSERT
//wymusi to dodawania średnikow podczas wstawiania makra do kodu

#ifdef NDEBUG
    #define debug(M, ...)
#else
    #define debug(M, ...) fprintf(stderr, "debug %s:%d: " M "\n", \
        __FILE__, __LINE__, ##__VA_ARGS__)
#endif


#define clean_errno() (errno == 0 ? "None" : strerror(errno))


#define log_err(M, ...) fprintf(stderr, \
        "[ERROR] (function %s %s : %d errno: %s  ) " M "\n", __func__, __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, \
        "[WARN]  (function %s %s : %d errno: %s  ) " M "\n",__func__,  __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, \
        "[INFO]  (function %s %s : %d errno: %s ) " M "\n",__func__,  __FILE__, __LINE__, , clean_errno(), ##__VA_ARGS__)

#define check(A,M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__);  errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); \
    errno=0; goto error; }

#define ASSERT(A,M, ...) do {                                             \
    if (!(A)) {                                                           \
        log_err(M, ##__VA_ARGS__);                                        \
        exit(1);                                                          \
    }                                                                     \
} while(0) 


///__func__


#endif //__dbg_h__


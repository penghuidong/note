
typedef struct redisAsyncContext {
    redisContext c;
    int err;
    char* errstr;
    void* data;
    struct {
        void* data;
        void (*addRead)(void* privdata);
        void (*delRead)(void* privdata);
        void (*addWrite)(void* privdata);
        void (*delWrite)(void* privdata);
        void (*cleanup)(void* privdata);
    } ev;

    redisDisconnnectCallback* onDisconnect;
    redisConnectCallback* onConnect;
    redisCallbackList replies;
    struct {
        redisCallbackList invalid;
        struct dict* channels;
        struct dict* patterns;
    } sub;
} redisAsyncContext;


typedef void (redisCallbackFn)(struct redisAsyncContext*, void*, void*);



int CRedisMgr::RedisAsyncCommand(redisCallbackFn* fn, CRefObj* pRefObj, const char* format, ...)；

int redisvAsyncCommand(redisAsyncContext* ac, redisCallbackFn* fn, void* privdata, const char* format, va_list ap);

int __redisAsyncCommand(redisAsyncContext* ac, redisCallbackFn* fn, void* privdata, char* cmd, size_t len);
typedef struct _buffer {
    size_t size;
    char* data;
} Buffer;

typedef struct _response {
    long code;
    Buffer* data;
} Response;

Response* getsite(char* type, char* time);
void cleanup(Response* r);

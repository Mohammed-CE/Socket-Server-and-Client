typedef enum {
    cmd_upload,
    cmd_list,
    cmd_receive,
} command;

struct messages_st {
    command type;
    char filename [128];
    int size;
};
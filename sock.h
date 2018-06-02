#ifndef __SOCK_H_
#define __SOCK_H_


#ifdef  __cplusplus
#define SOCK_EXTERN extern  "C"
#else
#define SOCK_EXTERN extern
#endif//


typedef int     sock_errno;
struct  sock_inst_t;
struct  sock_msg_t;


#define SOCK_OK     (0)



SOCK_EXTERN sock_errno  sock_open(char* addr, struct sock_inst_t** inst);
SOCK_EXTERN void        sock_close(struct sock_inst_t* inst);

SOCK_EXTERN sock_errno  sock_post(struct sock_inst_t* inst, struct sock_msg_t* msg);
SOCK_EXTERN sock_errno  sock_pick(struct sock_inst_t* inst, struct sock_msg_t** msg);


SOCK_EXTERN struct sock_msg_t*  sock_msg_new(int size);
SOCK_EXTERN struct sock_msg_t*  sock_msg_del(struct sock_msg_t* msg);
SOCK_EXTERN struct sock_msg_t*  sock_msg_write(struct sock_msg_t* msg, void* data, int size);
SOCK_EXTERN void*               sock_msg_data (struct sock_msg_t* msg);
SOCK_EXTERN int                 sock_msg_len  (struct sock_msg_t* msg);



#endif//__SOCK_H_



#include "sock.h"

#include <stdlib.h>

#include "uv.h"


#define     SOCK_ERR_MUTEX_INIT_FAILED  (1)

struct  sock_node_t
{
    struct sock_node_t* next;
};


struct  sock_queue_t
{
    uv_mutex_t          mutex;
    struct sock_node_t* first;
    struct sock_node_t* last;
    int                 size;
};


static  int sock_queue_init(struct sock_queue_t* q)
{
    int ret = uv_mutex_init(&(q->mutex));
    if (0 != ret)
    {
        return SOCK_ERR_MUTEX_INIT_FAILED;
    }

    q->first = NULL;
    q->last  = NULL;
    q->size  = 0;
    return 0;
}

static  void sock_queue_push_back(struct sock_queue_t* q, struct sock_node_t* n)
{
    n->next       = NULL;

    uv_mutex_lock(&(q->mutex));
    if (NULL != q->last)
    {
        q->last->next = n;
        q->last       = n;
        q->size++;
    }
    else
    {
        q->last  = n;
        q->first = n;
        q->size = 1;
    }
    uv_mutex_unlock(&(q->mutex));
}

static  struct sock_node_t* sock_queue_pop_front(struct sock_queue_t* q)
{
    //  双检测优化
    if (NULL == q->first)
    {
        return NULL;
    }

    uv_mutex_lock(&(q->mutex));
    if (NULL == q->first)
    {
        return NULL;
    }
    struct sock_node_t* first = q->first;
    if (q->last != first)
    {
        q->first = first->next;
        q->size--;
    }
    else
    {
        q->first = NULL;
        q->last  = NULL;
        q->size  = 0;
    }
    uv_mutex_unlock(&(q->mutex));

    first->next = NULL;
    return first;
}


static  int sock_queue_size(struct sock_queue_t* q)
{
    return q->size; ///<    只读操作，虽然不准确，但是但是不影响正常功能
}



struct  sock_inst_t
{
    struct sock_queue_t send_queue;
    struct sock_queue_t recv_queue;
};


struct  sock_msg_t
{
    struct sock_node_t node;
    int     cap;
    int     len;
    char    data[0];
};


SOCK_EXTERN sock_errno  sock_open(char* addr, struct sock_inst_t** pinst)
{
    struct sock_inst_t* inst = (struct sock_inst_t*)malloc(sizeof(struct sock_inst_t));
}


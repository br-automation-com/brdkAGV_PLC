/*
Copyright (C) 2021 B&R Danmark
All rights reserved
*/

#ifndef _ZMQ_H_
#define _ZMQ_H_

#include <bur/plctypes.h>
#include <stddef.h>
#include <stdbool.h>

#define ZMQ_PUB 1
#define ZMQ_SUB 2
#define ZMQ_SUBSCRIBE 6
#define ZMQ_DONTWAIT 1

#define ZMQ_FIFO_SIZE 1
#define ZMQ_AFFINITY 2
#define ZMQ_THREAD_SCHED_POLICY 4
#define ZMQ_IO_THREADS 16

#ifndef SCHED_FIFO
#define SCHED_FIFO 1
#endif

typedef struct zmq_msg_t
{
    long magic;
    size_t size;
    void *data;
} zmq_msg_t;

void *zmq_ctx_new(void);
int zmq_ctx_term(void *ctx_);
int zmq_ctx_set(void *ctx_, int option_, int optval_);
typedef void(zmq_free_fn)(void *data);
void *zmq_socket(void *, int type_);
int zmq_close(void *s_);
int zmq_bind(void *s_, const char *addr_);
int zmq_connect(void *s_, const char *addr_);
int zmq_unbind(void *s_, const char *addr_);
int zmq_disconnect(void *s_, const char *addr_);
int zmq_send(void *s_, const void *buf_, size_t len_, int flags_);
int zmq_recv(void *s_, void *buf_, size_t len_, int flags_);
int zmq_msg_init(zmq_msg_t *msg_);
int zmq_msg_init_size(zmq_msg_t *msg_, size_t size_);
int zmq_msg_init_data(zmq_msg_t *msg_, void *data_, size_t size_, zmq_free_fn *ffn_, void *hint_);
int zmq_msg_send(zmq_msg_t *msg_, void *s_, int flags_);
int zmq_msg_recv(zmq_msg_t *msg_, void *s_, int flags_);
int zmq_msg_close(zmq_msg_t *msg_);
void *zmq_msg_data(zmq_msg_t *msg_);
size_t zmq_msg_size(const zmq_msg_t *msg_);
int zmq_setsockopt(void *s_, int option_, const void *optval_, size_t optvallen_);

#endif //_ZMQ_H_
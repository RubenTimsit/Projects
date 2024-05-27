#ifndef __REQUEST_H__

#define ERR 10
#define STATIC 20
#define DYNAMIC 30

int requestHandle(int fd, int thread_id, struct timeval arrival_time, struct timeval dispatch_time,
                                                                    int req, int dyn_req, int stat_req);

#endif

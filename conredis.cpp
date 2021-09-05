//
// Created by wy on 2021/9/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <hiredis/hiredis.h>

int main() {
//    if (argc < 3) {
//        printf("usage: connRedis hostname port password\n");
//        return 1;
//    }
//    char *hostname = argv[1];
//    int port = atoi(argv[2]);
//    char *password = argv[3];

    char *hostname = "127.0.0.1";
    int port = 6379;
    char *password = "root";

    redisContext *conn;
    redisReply *reply;
    struct timeval timeout = {1, 500000};
    conn = redisConnectWithTimeout(hostname, port, timeout);
    // conn erro
    if (conn == NULL || conn->err) {
        if (conn) {
            printf("connection error %s\n", conn->errstr);
            exit(1);
        } else {
            printf("cannot alloc redis context\n");
            exit(1);
        }
    }

    // auth
    redisCommand(conn, "AUTH %s", password);
    printf("auth is %s\n", reply->str);
    freeReplyObject(reply);

    // set
    redisCommand(conn, "set %s %s", "name", "hello world");
    printf("set is %s\n", reply->str);
    freeReplyObject(reply);

    // get
    redisCommand(conn, "get name");
    printf("name :%s\n", reply->str);
    freeReplyObject(reply);

    // free conn
    redisFree(conn);
    return 0;
}
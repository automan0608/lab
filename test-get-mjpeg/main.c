
#include "prefix_core.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <event2/event.h>

static void main_sigint_cb(evutil_socket_t fd, short event, void *arg);
static void main_fifo_read_cb(evutil_socket_t fd, short event, void *arg);
static void main_http_read_cb(evutil_socket_t fd, short event, void *arg);
static int main_connect_server(char *host, int port);
static int main_send_http_req(int fd, char *req);

static char httpReq[] =
"GET /stream/video/mjpeg?resolution=VGA&&Username=admin&&Password=YWRtaW4&&tempid=0.75 HTTP/1.1\r\n"
"Host: 192.168.0.100:8080\r\n"
"Connection: keep-alive\r\n"
"User-Agent:Mozilla/5.0 zhoaosheng\r\n\r\n";

int main()
{
    printf("in main\n");

    const char *fifo = "/tmp/event.fifo";
    int fdfifo = 0;

    struct event_base *base;
    struct event *evsigint;
    struct event *evsigterm;
    struct event *evfifo;

    int sockfd;
    int result;

    unlink(fifo);

    DEBUG("will mkfifo");

    result = mkfifo(fifo, 0600);
    if (0 != result)
    {
        DEBUG("mkfifo error, %s", strerror(errno));
        exit(-1);
    }
    DEBUG("mkfifo success");

    fdfifo = open(fifo, O_RDONLY | O_NONBLOCK, 0);
//    fdfifo = open(fifo, O_RDONLY, 0);
    if (0 >= fdfifo)
    {
        DEBUG("open fifo error");
        exit(-1);
    }
    DEBUG("open fifo success");

#if 0
    char buf[256] = {0};
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        result = read(fdfifo, buf, sizeof(buf));
        if (0 > result)
        {
            if (EAGAIN == errno || EWOULDBLOCK == errno)
            {
                DEBUG("EAGAIN | EWOULDBLOCK");
                continue;
            }

            DEBUG("read error, %s", strerror(errno));
            exit(-1);
        }
        else if (0 == result)
        {
            DEBUG("read FIN");
            exit(-1);
        }

        DEBUG("%s", buf);
    }
#endif

    base = event_base_new();

    sockfd = main_connect_server("192.168.0.100", 8080);
    if (0 >= sockfd)
    {
        DEBUG("connect media-service error");
        exit(-1);
    }

    result = main_send_http_req(sockfd, httpReq);
    if (SUCCESS != result)
    {
        DEBUG("send http req error");
        exit(-1);
    }

//    evsigint = evsignal_new(base, SIGINT, main_sigint_cb, event_self_cbarg());
    evsigint = evsignal_new(base, SIGINT, main_sigint_cb, NULL);
    event_add(evsigint, NULL);

//    evsigterm = evsignal_new(base, SIGTERM, main_sigint_cb, NULL);
//    event_add(evsigterm, NULL);

    evfifo = event_new(base, fdfifo, EV_READ | EV_PERSIST, main_fifo_read_cb, NULL);
    event_add(evfifo, NULL);

    evfifo = event_new(base, sockfd, EV_READ | EV_PERSIST, main_http_read_cb, NULL);
    event_add(evfifo, NULL);

    event_base_dispatch(base);
    event_base_free(base);
}

static void main_sigint_cb(evutil_socket_t fd, short event, void *arg)
{
//    struct event* sig = (struct event *)arg;

    DEBUG("receive sigint/sigterm, event:%d", event);

//    DEBUG("got signal:%d\n", event_get_signal(sig));
}

static void main_fifo_read_cb(evutil_socket_t fd, short event, void *arg)
{
    DEBUG("fifo read ok, event:%d", event);

    int len = 0;
    char buf[256] = {0};

    len = read(fd, buf, sizeof(buf));
    if (0 > len)
    {
            DEBUG("read error, %s", strerror(errno));
    }
    else if (0 == len)
    {
        DEBUG("read FIN, %s", strerror(errno));
    }

    DEBUG("%s", buf);
}

static void main_http_read_cb(evutil_socket_t fd, short event, void *arg)
{
    DEBUG("http read ok, event:%d", event);

    int len = 0;
    char buf[256] = {0};

    len = read(fd, buf, sizeof(buf));
    if (0 > len)
    {
            DEBUG("read error, %s", strerror(errno));
    }
    else if (0 == len)
    {
        DEBUG("read FIN, %s", strerror(errno));
    }

    DEBUG("%s", buf);
}

static int main_connect_server(char *host, int port)
{
    DEBUG("in main connect server, host:%s, port:%d", host, port);

    int sockfd, n;
    struct sockaddr_in addr;

    if (sockfd = socket(AF_INET,SOCK_STREAM, 0), sockfd < 0)
    {
        DEBUG("socket call error\n");
        exit(-1);
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &addr.sin_addr) <= 0)
    {
        DEBUG("inet_pton call error\n");
        exit(-1);
    }

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        DEBUG("connect call error\n");
        exit(-1);
    }

    return sockfd;
}

static int main_send_http_req(int fd, char *req)
{
    DEBUG("will send http req");

    int len = write(fd, req, strlen(req));
    if (0 >= len)
    {
        DEBUG("send http req error");
        exit(-1);
    }

    DEBUG("send http req success");

    return SUCCESS;
}

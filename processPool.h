//
//  ProcessPool.h
//  demo
//
//  Created by shiyi on 2016/11/25.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#ifndef ProcessPool_H
#define ProcessPool_H

#include <stdio.h>
#include <iostream>
#include "Util.h"
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

//信号通信的管道
static int sigPipefd[2];

//将套接字设置为非阻塞
static int setNoBlocking(int fd)
{
    int oldOption = fcntl(fd, F_GETFL);
    int newOption = oldOption | O_NONBLOCK;
    fcntl(fd, F_SETFL, newOption);
    return oldOption;
}

//信号回调函数
static void sigHandler(int sig)
{
    int saveErrno = errno;
    send(sigPipefd[1], (char*)&sig, 1, 0);
    errno = saveErrno;
}

//添加信号回调
static void addSig(int sig, void(handler)(int), bool restart = true)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    if(restart)
        sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    if(-1 == sigaction(sig, &sa, NULL))
        Util::outError("sigaction");
}

//添加epoll监听事件
static void addFd(int epollfd, int fd, int type)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = type;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
}

//移除epoll事件表fd的所有事件并关闭fd
static void removeFd(int epollfd, int fd)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}


//进程类
class Process
{
public:
    Process() : m_pid(-1) {};

    //本进程的pid
    int m_pid;
    //与父进程通信的管道
    int m_pipefd[2];
};


template <typename T>
class ProcessPool
{
public:

    ProcessPool( int listenfd, int processNumber = 4);
    ~ProcessPool();
    
    //启动进程池
    void run();
  
private:
    void setupSigPipe();
    void runParent();
    void runChild();
    
private:
    //最大进程数
    static const int MAX_PROCESS_NUMBER = 16;
    //每个进程能处理的最大连接数
    static const int USER_PROCESS = 655536;
    //epoll能监听的最大事件
    static const int MAX_EVENT_NUMBER = 10000;
    //进程池的进程总数
    int m_processNum;
    //子进程在池中的编号 父进程为-1 子进程>=0
    int m_idx;
    int m_epollfd;
    //监听socket
    int m_listenfd;
    //判断是否终止运行
    int m_isRunning;
    //保存所有子进程的描述信息
    Process* m_subProcess;
};

template<typename T>
ProcessPool<T>::ProcessPool(int listenfd, int processNumber)
    : m_listenfd(listenfd), m_processNum(processNumber), m_idx(-1), m_isRunning(true)
{

    assert((processNumber > 0) && (processNumber <= MAX_PROCESS_NUMBER));

    m_subProcess = new Process[processNumber];
    assert( m_subProcess );

    //创建processNumber个进程，并建立其与父进程之间的管道
    for(int i=0; i<processNumber; i++)
    {
        int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, m_subProcess[i].m_pipefd);
        assert(ret == 0);


        int pid = fork();
        if(pid < 0)
            Util::outError("fork");


        //双端通道因fork的原因变为四个端口，父子进程各关闭一端
        if(pid == 0)
        {
            close(m_subProcess[i].m_pipefd[1]);
            m_idx = i;
            break;
        }
        else if(pid > 0)
        {   
            m_subProcess[i].m_pid = pid;            
            close(m_subProcess[i].m_pipefd[0]);
        }
    }
}

template<typename T>
ProcessPool<T>::~ProcessPool()
{
    delete[] m_subProcess;
}

template<typename T>
void ProcessPool<T>::setupSigPipe()
{
    //新建epoll监听表和事件管道
    m_epollfd = epoll_create(USER_PROCESS);
    if(m_epollfd == -1)
        Util::outError("epoll_create");

    int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, sigPipefd);
    assert(ret == 0);

    //将写设置为非阻塞
    setNoBlocking(sigPipefd[1]);
    addFd(m_epollfd, sigPipefd[0], EPOLLIN | EPOLLET);
    setNoBlocking(sigPipefd[0]);

    //设置信号处理函数
    addSig(SIGCHLD, sigHandler);
    addSig(SIGTERM, sigHandler);
    addSig(SIGINT, sigHandler);
    // addSig(SIGPIPE, sigHandler);

}

//启动进程池
template<typename T>
void ProcessPool<T>::run()
{
    if(m_idx == -1)
        runParent();
    else
        runChild();    
}

template<typename T>
void ProcessPool<T>::runParent()
{
    //统一事件源
    setupSigPipe();

    epoll_event events[MAX_EVENT_NUMBER];
    addFd(m_epollfd, m_listenfd, EPOLLIN | EPOLLET);
    // setNoBlocking(m_listenfd);

    //当前要分配连接的子进程编号
    int now_process = 0;

    while(m_isRunning)
    {

        int num = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1);
        //如果错误原因不是被中断，则循环退出
        if((num < 0) && (errno != EINTR))
        {
            Util::outError("epoll_wait failure");
            break;
        }

        for(int i=0; i<num; i++)
        {
            int sockfd = events[i].data.fd;
            //处理新的请求
            if(sockfd == m_listenfd)
            {
                int msg = 1;
                send(m_subProcess[now_process].m_pipefd[1], (char*)&msg, sizeof(msg), 0);
                Util::outMsg("send request to process:%d\n", now_process);
                now_process = (now_process+1)%m_processNum;
            }
            //处理信号
            else if((sockfd == sigPipefd[0]) && (events[i].events & EPOLLIN)) 
            {
                char sigMsg[1024];
                int ret = recv(sockfd, sigMsg, sizeof(sigMsg), 0);
                if(ret <= 0)
                {
                    continue;
                }

                for(int j=0; j<ret; j++)
                {
                    //循环处理每个信号
                    switch(sigMsg[j])
                    {
                        case SIGCHLD:
                        {
                            int pid, stat;
                            while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
                            {
                                for(int k=0; k<m_processNum; k++)
                                {
                                    if(pid == m_subProcess[k].m_pid)
                                    {
                                        //将退出的子进程pid赋为-1，关闭其管道
                                        m_subProcess[k].m_pid = -1;
                                        close(m_subProcess[k].m_pipefd[1]);
                                        break;
                                    }
                                }
                            }
                            int num = 0;
                            for(int k=0; k<m_processNum; k++)
                            {
                                if(m_subProcess[k].m_pid == -1)
                                    num++;
                            }

                            if(num == m_processNum)
                            {
                                m_isRunning = false;
                                Util::outMsg("process idx=%d pid=%d SIGINT\n", m_idx, m_subProcess[m_idx].m_pid);
                            }

                            break;
                        }
                        case SIGTERM:
                        case SIGINT:
                        {   
                            //通知子进程退出
                            int msg = -1;
                            for(int k=0; k<m_processNum; k++)
                            {
                                send(m_subProcess[k].m_pipefd[1], (char*)&msg, sizeof(msg), 0);
                            }
                            break;
                        }
                    }
                }
            }
            //处理子进程的消息
            else if(events[i].events & EPOLLIN)
            {
                for(int j=0; j<m_processNum; j++)
                {
                    if(sockfd == m_subProcess[j].m_pipefd[0])
                    {

                    }
                }
            }
        }
    }

    close(sigPipefd[0]);
    close(sigPipefd[1]);
    close(m_epollfd);
}

template<typename T>
void ProcessPool<T>::runChild()
{
    //统一事件源
    setupSigPipe();

    epoll_event events[MAX_EVENT_NUMBER];
    T* users = new T[USER_PROCESS];
    assert(users != NULL);

    //找到子进程与父进程通信的管道，将其添加监听
    int pipefd = m_subProcess[m_idx].m_pipefd[0];
    addFd(m_epollfd, pipefd, EPOLLIN | EPOLLET);
    setNoBlocking(pipefd);

    while(m_isRunning)
    {
        int num = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1);
        if((num < 0) && (errno != EINTR))
        {
            Util::outError("process:%d epoll_wait failure", m_idx);
            break;
        }

        for(int i=0; i<num; i++)
        {
            int sockfd = events[i].data.fd;
            //父进程事件
            if((sockfd == pipefd) && (events[i].events & EPOLLIN))
            {
                int msg;
                int ret = recv(sockfd, (char*)&msg, sizeof(msg), 0);
                if((ret < 0 && errno != EAGAIN) || ret == 0)
                {
                    continue;
                }
                switch(msg)
                {
                    //子进程退出
                    case -1:
                    {
                        m_isRunning = false;
                        Util::outMsg("process idx=%d pid=%d EXIT\n", m_idx, m_subProcess[m_idx].m_pid);
                        break;
                    }
                    case 1:
                    {
                        //连接新的请求
                        struct sockaddr_in clientAddr;
                        socklen_t clientLen = sizeof(clientAddr);
                        int connfd = accept(m_listenfd, (struct sockaddr*)&clientAddr, &clientLen);

                        if(connfd < 0)
                        {              
                            Util::outError("accept");
                            break;
                        }

                        Util::outMsg("process idx=%d pid=%d accept a new client : %s\n", m_idx, m_subProcess[m_idx].m_pid, inet_ntoa(clientAddr.sin_addr));

                        addFd(m_epollfd, connfd, EPOLLIN | EPOLLET);
                        setNoBlocking(connfd);
                        //初始化客户端链接
                        users[connfd].init(m_epollfd, connfd, clientAddr);
                        break;
                    }
                    default:
                        break;
                }
            }
            //信号事件
            else if((sockfd == sigPipefd[0]) && (events[i].events & EPOLLIN))
            {
                char sigMsg[1024];
                int ret = recv(sockfd, sigMsg, sizeof(sigMsg), 0);
                if(ret <= 0)
                {
                    continue;
                }

                for(int j=0; j<ret; j++)
                {
                    //循环处理每个信号
                    switch(sigMsg[j])
                    {
                        case SIGCHLD:
                        {
                            Util::outMsg("process idx=%d pid=%d SIGCHLD\n", m_idx, m_subProcess[m_idx].m_pid);
                            break;
                        }
                        case SIGTERM:
                        case SIGINT:
                        {   
                            m_isRunning = false;
                            Util::outMsg("process idx=%d pid=%d SIGINT\n", m_idx, m_subProcess[m_idx].m_pid);
                            break;
                        }
                    }
                }
            }
            //客户端事件
            else if(events[i].events & EPOLLIN)
            {
                users[sockfd].doRecv();
                sleep(1);
            }
        }
    }

    delete[] users;
    users = NULL;
    close(pipefd);
    close(m_epollfd);
}



#endif /* ProcessPool_H */

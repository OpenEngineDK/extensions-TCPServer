#include "TCPOutgoingMessageThread.h"

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Network {

    TCPOutgoingMessageThread::TCPOutgoingMessageThread(TCPSocket *socket)
    {
        sock = socket;
    }

    TCPOutgoingMessageThread::~TCPOutgoingMessageThread()
    {
        delete sock;
    }

    void TCPOutgoingMessageThread::Handle(TCPString arg)
    {
        if(arg.Sender == sock || arg.Sender == 0)
        {
            lock.Lock();
            OutgoingMessages.push_back(arg.Message);
            sem.Post();
            lock.Unlock();
        }
    }

    void TCPOutgoingMessageThread::Run()
    {
        while(sock->IsOpen())
        {
            sem.Wait();
            lock.Lock();
            sock->SendLine(OutgoingMessages.front());
            OutgoingMessages.erase(OutgoingMessages.begin());
            lock.Unlock();
        }
    }

    void TCPOutgoingMessageThread::Stop()
    {
    }
}}

#include "TCPOutgoingMessageThread.h"

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Network {

    TCPOutgoingMessageThread::TCPOutgoingMessageThread(TCPSocket *socket, IEvent<TCPDeallocType*> *initdealloc)
    {
        sock = socket;
        dealloc = initdealloc;
    }

    TCPOutgoingMessageThread::~TCPOutgoingMessageThread()
    {
    }

    void TCPOutgoingMessageThread::Handle(TCPString arg)
    {
        if(arg.Sender == sock || arg.Sender == 0)
        {
            lock.Lock();
            OutgoingMessages.push_back(arg.Message);
            sem.Unlock();
            lock.Unlock();
        }
    }

    void TCPOutgoingMessageThread::Run()
    {
        while(sock->IsOpen())
        {
            sem.Lock();
                sem.Lock();
            lock.Lock();
            sock->SendLine(OutgoingMessages.front());
            OutgoingMessages.erase(OutgoingMessages.begin());
            lock.Unlock();
            sem.Unlock();
        }
        dealloc->Notify(this);
    }

    void TCPOutgoingMessageThread::Stop()
    {
        sock->Close();
    }
}}

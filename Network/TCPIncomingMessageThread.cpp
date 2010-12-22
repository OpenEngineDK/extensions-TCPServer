#include "TCPIncomingMessageThread.h"

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Network {

    TCPIncomingMessageThread::TCPIncomingMessageThread(TCPSocket *socket, IEvent<TCPString> *MessageQueue, IEvent<TCPDeallocType*> *initdealloc)
    {
        sock = socket;
        dealloc = initdealloc;
        TCPMessage = MessageQueue;
    }

    TCPIncomingMessageThread::~TCPIncomingMessageThread()
    {
        Stop();
        delete sock;
    }

    void TCPIncomingMessageThread::Run()
    {
        while(sock->IsOpen())
        {
            TCPString string;
            string.Message = sock->ReadLine();
            string.Sender = sock;
            if(string.Message == "")
                break;
            //TCPMessage->Notify(string);
        }
        dealloc->Notify(this);
    }

    void TCPIncomingMessageThread::Stop()
    {
        sock->Close();
    }
}}

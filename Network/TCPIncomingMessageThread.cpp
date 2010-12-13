#include "TCPIncomingMessageThread.h"

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Network {

    TCPIncomingMessageThread::TCPIncomingMessageThread(TCPSocket *socket, LockedQueuedEvent<TCPString> *MessageQueue)
    {
        sock = socket;
        TCPMessage = MessageQueue;
    }

    TCPIncomingMessageThread::~TCPIncomingMessageThread()
    {
        delete sock;
    }

    void TCPIncomingMessageThread::Run()
    {
        while(sock->IsOpen())
        {
            TCPString string;
            string.Message = sock->ReadLine();
            string.Sender = sock;
            TCPMessage->Notify(string);
        }
    }

    void TCPIncomingMessageThread::Stop()
    {
    }
}}

#include "TCPServer.h"

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Network {

    TCPServer::TCPServer(int p)
    {
        sock = new TCPServerSocket(p);
        sock->Listen();
        TCPIncomingMessage = new LockedQueuedEvent<TCPString>();
        TCPOutgoingMessage = new LockedQueuedEvent<TCPString>();
        dealloc = new LockedQueuedEvent<TCPDeallocType*>();
        dealloc->Attach(*this);
    }

    TCPServer::~TCPServer()
    {
        delete sock;
        delete TCPIncomingMessage;
        delete TCPOutgoingMessage;
        delete dealloc;
    }

    void TCPServer::Run()
    {
        while(sock->IsOpen())
        {
            TCPSocket *socket = sock->Accept();
            TCPIncomingMessageThread *incoming = new TCPIncomingMessageThread(socket, TCPIncomingMessage, dealloc);
            //TCPOutgoingMessageThread *outgoing = new TCPOutgoingMessageThread(socket, dealloc);
            incoming->Start();
            //outgoing->Start();
        }
    }

    void TCPServer::Stop()
    {
        sock->Close();
    }
}}

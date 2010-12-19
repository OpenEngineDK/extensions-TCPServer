#include "TCPServer.h"

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Network {

    TCPServer::TCPServer(int p)
    {
        sock = new TCPServerSocket(p);
        TCPIncomingMessage = new LockedQueuedEvent<TCPString>();
        TCPOutgoingMessage = new LockedQueuedEvent<TCPString>();
    }

    TCPServer::~TCPServer()
    {
        delete sock;
        delete TCPIncomingMessage;
        delete TCPOutgoingMessage;
    }

    void TCPServer::Run()
    {
        while(sock->IsOpen())
        {
            TCPSocket *socket = sock->Accept();
            TCPIncomingMessageThread incoming(socket, TCPIncomingMessage);
            TCPOutgoingMessageThread outgoing(socket);
            incoming.Start();
            outgoing.Start();
            threads.push_back(make_pair(incoming, outgoing));
        }
    }

    void TCPServer::Stop()
    {
        sock->Close();
    }
}}

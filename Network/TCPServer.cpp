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

    void TCPServer::Handle(TCPDeallocType* arg)
    {
        logger.info << "DEALLOC CALLED!" << logger.end;
        delete arg;
        /*
        for(unsigned int x=0; x<threads.size(); x++)
        {
            if(threads[x].first == arg || threads[x].second == arg)
            {
                logger.info << "DELETE HAPPEND!" << logger.end;
                delete threads[x].first;
                //delete threads[x].second;
                threads.erase(threads.begin() + x);
                x--;
            }
        }
        */
    }

    void TCPServer::Run()
    {
        while(sock->IsOpen())
        {
            TCPSocket *socket = sock->Accept();
            TCPIncomingMessageThread *incoming = new TCPIncomingMessageThread(socket, TCPIncomingMessage, dealloc);
            TCPOutgoingMessageThread *outgoing;// = new TCPOutgoingMessageThread(socket, dealloc);
            incoming->Start();
            //outgoing->Start();
            threads.push_back(make_pair(incoming, outgoing));
        }
    }

    void TCPServer::Stop()
    {
        sock->Close();
    }
}}

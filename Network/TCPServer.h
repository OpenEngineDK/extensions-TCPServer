// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------
#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H

#include <Network/TCPSocket.h>
#include <Network/TCPServerSocket.h>
#include <Core/Thread.h>
#include <Core/IListener.h>
#include <Core/EngineEvents.h>
#include <Core/LockedQueuedEvent.h>

#include "TCPIncomingMessageThread.h"
#include "TCPOutgoingMessageThread.h"

#include "TCPString.h"
#include "TCPDeallocType.h"

#include <vector>

using namespace OpenEngine::Core;

namespace OpenEngine {
namespace Network {

    using namespace std;

    typedef pair<TCPIncomingMessageThread*, TCPOutgoingMessageThread*> threadPair;

    class TCPServer : public Thread,
                      public IListener<TCPDeallocType*>
    {
        private:
            TCPServerSocket *sock;

            LockedQueuedEvent<TCPString> *TCPIncomingMessage;
            LockedQueuedEvent<TCPString> *TCPOutgoingMessage;

            LockedQueuedEvent<TCPDeallocType*> *dealloc;

        public:
            TCPServer(int port);
            ~TCPServer();

            void Stop();
            void Run();

            void Handle(TCPDeallocType* arg)
            {
                //Make a vector<pair<threads> > and dealloc both threads
                delete arg;
            }

            IEvent<TCPString>& IncomingMessageEvent()
            {
                return *TCPIncomingMessage;
            }
            IEvent<TCPString>& OutgoingMessageEvent()
            {
                return *TCPOutgoingMessage;
            }
    };
} // NS Network
} // NS OpenEngine

#endif

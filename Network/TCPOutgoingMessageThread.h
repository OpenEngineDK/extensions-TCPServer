// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------
#ifndef _TCP_OUTGOING_MESSAGE_THREAD_H
#define _TCP_OUTGOING_MESSAGE_THREAD_H

#include <Network/TCPSocket.h>
#include <Network/TCPServerSocket.h>
#include <Core/Thread.h>
#include <Core/IListener.h>
#include <Core/EngineEvents.h>
#include <Core/LockedQueuedEvent.h>

#include "TCPString.h"
#include "TCPDeallocType.h"

#include <vector>

using namespace OpenEngine::Core;

namespace OpenEngine {
namespace Network {

    using namespace std;

    class TCPOutgoingMessageThread 
        : public Thread,
          public IListener<TCPString>,
          public TCPDeallocType
    {
        private:
            TCPSocket *sock;
            Mutex lock;
            Mutex sem;
            IEvent<TCPDeallocType*> *dealloc;
            std::vector<string> OutgoingMessages;

        public:
            TCPOutgoingMessageThread(TCPSocket *socket, IEvent<TCPDeallocType*> *initdealloc);
            ~TCPOutgoingMessageThread();

            void Handle(TCPString arg);

            void Stop();
            void Run();
    };
} // NS Network
} // NS OpenEngine

#endif

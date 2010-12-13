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
#include <Core/Semaphore.h>

#include "TCPString.h"

#include <vector>

using namespace OpenEngine::Core;

namespace OpenEngine {
namespace Network {

    using namespace std;

    class TCPOutgoingMessageThread 
        : public Thread,
          public IListener<TCPString>
    {
        private:
            TCPSocket *sock;
            Mutex lock;
            Semaphore sem;
            std::vector<string> OutgoingMessages;

        public:
            TCPOutgoingMessageThread(TCPSocket *socket);
            ~TCPOutgoingMessageThread();

            void Handle(TCPString arg);

            void Stop();
            void Run();
    };
} // NS Network
} // NS OpenEngine

#endif

#ifndef _TCP_STRING_H
#define _TCP_STRING_H

#include <string>
#include <Network/TCPSocket.h>

namespace OpenEngine {
namespace Network {

    typedef struct
    {
        string Message;
        TCPSocket *Sender;
    } TCPString;

}}

#endif //_TCP_STRING_H

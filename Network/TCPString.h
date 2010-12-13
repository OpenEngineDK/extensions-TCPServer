#ifndef _TCP_STRING
#define _TCP_STRING

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

#endif //_TCP_STRING

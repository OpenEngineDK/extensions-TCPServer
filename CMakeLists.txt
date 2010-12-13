SET( EXTENSION_NAME "Extensions_TCPServer")

# Create the extension library
ADD_LIBRARY(${EXTENSION_NAME}
    Network/TCPString.h
    Network/TCPServer.h
    Network/TCPServer.cpp
    Network/TCPIncomingMessageThread.h
    Network/TCPIncomingMessageThread.cpp
    Network/TCPOutgoingMessageThread.h
    Network/TCPOutgoingMessageThread.cpp
)

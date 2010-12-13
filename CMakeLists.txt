SET( EXTENSION_NAME "Extensions_TCPServer")

# Create the extension library
ADD_LIBRARY(${EXTENSION_NAME}
  Network/TCPServer.h
  Network/TCPServer.cpp
)

TARGET_LINK_LIBRARIES(${EXTENSION_NAME}
    ${Extensions_Sockets}
    ${Extensions_pThreadSemaphore}
)

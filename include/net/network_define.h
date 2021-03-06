#pragma once

#ifndef NETWORK_DEFINDE_H_
#define NETWORK_DEFINDE_H_
#include <boost/shared_ptr.hpp>

class AsyncSessionImpl;

typedef struct PacketInfo
{
public:
	typedef boost::shared_ptr<AsyncSessionImpl> AsyncSessionImplPtr;

	PacketInfo() {};
	PacketInfo(AsyncSessionImplPtr& ptrsession, const int protocol_no, char* buffer, const size_t buffer_size) : 
		m_pAsyncSessionImp(ptrsession),
		m_protocolNo(protocol_no),
		m_pBuffer(buffer),
		m_sizeOfBuffer(buffer_size)
	{
		
	}
	AsyncSessionImplPtr m_pAsyncSessionImp;
	int32_t m_protocolNo;
	char * m_pBuffer;
	size_t m_sizeOfBuffer;
}PacketInfo;

#endif //  NETWORK_DEFINDE_H_



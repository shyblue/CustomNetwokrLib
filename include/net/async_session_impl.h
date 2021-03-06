#pragma once

#ifndef _SESSION_H_
#define _SESSION_H_		1

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "common.h"
#include "session_base.h"
#include "util/buffer.h"

const uint16_t HEADER_ERROR		= 200;
const uint32_t MAX_PACKET_SIZE	= 65536;
const uint16_t PROTOCOL_MIN		= 100;
const uint16_t PROTOCOL_MAX		= 50000;

class PacketWorkerManager;
class Header;

template<typename T>
class SessionPool;
class AsyncSessionPool;

class AsyncSessionImpl : public boost::enable_shared_from_this<AsyncSessionImpl>, public SessionBase
{
public:
	
	typedef boost::shared_ptr<PacketWorkerManager>	PacketWorkerManagerPtr;
	typedef boost::shared_ptr<Header>				HeaderPtr;

	enum SessionPoolState
	{
		kNoneRegister,
		kAcquire,
		kRestore,
	};

	explicit AsyncSessionImpl(boost::asio::io_service* io_service, Header* p_header, const PacketWorkerManagerPtr& packetdeliver_factory);
	~AsyncSessionImpl();

	virtual bool Recv(char* buffer = 0, size_t buffer_size = 0);
	virtual bool Send(const char* data, const size_t data_length);
	virtual bool Close();

	void SetSessionPool(AsyncSessionPool* p_session_pool);
	void SetSessionPoolState(SessionPoolState state) { m_nSessionPoolState = (uint8_t)state; };

	void SetId(size_t id) {m_id = id;}
	size_t GetId() {return m_id;}

	bool BufferRelease(char* buffer, uint32_t buffer_size);

private :		
	void RecvProcess();
	bool ReadHeader(const boost::system::error_code & error, size_t byte_transferred );
	bool ReadBody(const boost::system::error_code & error, size_t byte_transferred );

	void SendProcess(const char* data, const size_t data_length);
	void PacketSend(const boost::system::error_code & error);

	void MakeHexCode();

	AsyncSessionPool*			m_pSessionPool;
	HeaderPtr					m_spHeader;
	PacketWorkerManagerPtr		m_spWorkerManager;

	char*						m_szHeaderBuffer;
	char*						m_szBodyBuffer;

	size_t						m_id;
	size_t						m_sizeOfBodyBuffer;
	size_t						m_sizeOfPrevBodyBuffer;
	size_t						m_sizeOfMaxBuffer;

	uint8_t						m_nSessionPoolState;
	boost::asio::strand			m_strand;
};

#endif // _SESSION_H_
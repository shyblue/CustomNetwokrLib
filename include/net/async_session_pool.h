#pragma once

#ifndef NETWORK_POOL_ASYNSESSIONPOOL_H_
#define NETWORK_POOL_ASYNSESSIONPOOL_H_

#include <boost/shared_ptr.hpp>
#include <boost/asio/io_service.hpp>

#include "session_pool.h"
#include "async_session_impl.h"

class AsyncSessionPool : public SessionPool<boost::shared_ptr<AsyncSessionImpl>>
{
public:
	typedef boost::shared_ptr<PacketWorkerManager>		PacketWorkerManagerPtr;
	typedef boost::shared_ptr<AsyncSessionImpl>			AsyncSessionImplPtr;

	AsyncSessionPool(boost::asio::io_service* pio_service,const PacketWorkerManagerPtr& packet_worker_manager, const size_t count);
	~AsyncSessionPool(void);
private:
	void Initialize(const PacketWorkerManagerPtr& packet_worker_manager, const size_t count);

	boost::asio::io_service *					m_ioService;	
};

#endif // NETWORK_POOL_ASYNSESSIONPOOL_H_



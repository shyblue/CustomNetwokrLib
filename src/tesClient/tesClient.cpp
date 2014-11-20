// tesClient.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <string>
#include <boost/asio.hpp>
#include "net/sync_session_impl.h"
#include "util/logger.h"
#include "header_cct.h"
#include "util/memory_manager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ST_LOGGER.Create("log4cpp.xml");
	ST_LOGGER.Info("Test Client Start!!!");

	timeval tm;
	tm.tv_sec = 90000;
	tm.tv_usec = 0;

	boost::asio::io_service ioService;
	HeaderCCT* pHeader = new HeaderCCT();

	SyncSessionImpl testClient(&ioService,dynamic_cast<Header*>(pHeader));

	testClient.SetSendTimeout(tm);
	testClient.SetRecvTimeout(tm);

	if(!testClient.Connect(std::string("127.0.0.1"),std::string("12800")))
	{
		ST_LOGGER.Error("Can't connect to server.");
		return -1;
	}

	ST_LOGGER.Info("Connect to server success");

	uint16_t nProtocol=101;
	char sendbuffer[20] = {0,};
	size_t sendbuffersize = 20;
	char recvBuffer[20]={0,};
	size_t recvBufferSize = 20;

//	size_t HeaderCCT::Serialize(char &version,char &sign1,char &sign2,uint16_t &protocolNo,uint16_t &dataLen,int32_t &handle,char &find_sig)
	pHeader->Set('S','M','C',nProtocol,(uint16_t)4,(int32_t)1,0x01);
	pHeader->Serialize(sendbuffer,pHeader->GetTotalSize());

	size_t index = 0;
	int sendValue=0;
	int recvValue=0;
	for(int i=0;i<10;i++)
	{
		sendValue = i+1;
		index = pHeader->GetHeaderSize();

		MEMORY_MANAGER::WriteToBuffer(sendbuffer,sendbuffersize,index,&sendValue,sizeof(sendValue));
		testClient.Send(sendbuffer,index);
		
		testClient.Recv(recvBuffer,recvBufferSize);

		pHeader->SetDataSize(sizeof(sendValue));
		pHeader->Deserialize(recvBuffer,recvBufferSize);
		index = pHeader->GetHeaderSize();
		MEMORY_MANAGER::ReadFromBuffer(recvBuffer,recvBufferSize,index,&recvValue,sizeof(recvValue));
		ST_LOGGER.Info("[Test Client][Recv Data] [%d]", recvValue);

		Sleep(100);
	}

	testClient.Close();

	return 0;
}

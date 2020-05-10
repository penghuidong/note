# xlrpc 结构体概览

```c
struct tagXLrpcGlobal
{
	unsigned int dwInitStatus; /*   全局信息结构是否 */
	pthread_mutex_t tMutex;	/**<互斥读写锁进行互斥访问本全局数据去和实现一些线程安全操作*/
	int	iBussId;/**<业务ID*/
	int iFlag;
	unsigned int dwDyedMsgID; /*   染色消息的ID */
	unsigned int dwHandleCnt; /*   new field, xlrpc handle count */

	XLRPCHANDLE *pastXLrpcHandle[HANDLE_COUNT];/*   new field, xlrpc interface */
	volatile unsigned int dwGCIMVersion;/**< version of GCIM in share memory*/
	XLRPCSHMGCIM *pstGCIM;	/*   global channel info map */
	LPXLDRMETA	pstHeadMeta;/*meta of xlrpc head*/

	XLRPCHEAD stCounterfeitPkg;/*为方便xlrpc处理，而在数据通道尾部添加的伪造数据包*/
	int iCounterfeitPkgLen;/*伪造数据包的的长度*/
    void *pvAgentMng;/* save agent mng data ptr<malloced> */

    struct timeval stCurTime;/* 记录当前时间，用于发送消息时记录时间戳 */
};
typedef struct tagXLrpcGlobal                       	 XLRPCGLOBAL;
typedef struct tagXLrpcGlobal                       	*LPXLRPCGLOBAL;
```



```c
struct tagXLrpcHead
{
    uint8_t bVer;                                    
    uint8_t bHeadLen;                                
    int16_t nCheckSum;                               
    int32_t iBodyLen;                                
    int32_t iDst;                                    
    int32_t iSrc;                                    
    int32_t iSeq; 
    /* 在通常数据包包中，此字段存储数据包的序列号，在握手数据包中此字段存储发送数据包的序列号 */
    uint8_t bFlag;/*   bit set: LOG_TRACE,XLRPC_HEAD_FLAG_SYN  */
    uint8_t bCmd; /*   存储令字段 */
    int32_t iRecvSeq; /*  Ver.1  */
    THEADEXT stExtHead;                              
    XLRPCTIMESTAMPINTERNAL stTimeStamp;/*  Ver.2  */
    int32_t iHeartBeatMsgType; /*  Ver.2  */
};
typedef struct tagXLrpcHead                                        	XLRPCHEAD;
typedef struct tagXLrpcHead                                        	*LPXLRPCHEAD;
```



### GCIM: Global Channel Information Map

* 全局通道信息表，保存channel配置信息（通道两端的TBUS地址、数据队列大小等属性）
* GCIM保存在共享内存中，每台物理机器仅需要一份

```c
struct tagXLrpcShmGCIMHead
{
	volatile unsigned int dwVersion;                       	
    /*   当shm中的数据更新后，需要更新该数值，以方便应用模块进行进行重新加载 */
	unsigned int dwShmKey;/*   GCIM共享内存key，主要做校验用 */
	unsigned int dwShmSize;/*   共享内存大小 */
	unsigned int dwMaxCnt;/*   共享内存中最大可容纳的channel信息的slot数 */
	unsigned int dwUsedCnt;/*   共享内存已用的slot数 */
	time_t dwCreateTime;/*  共享内存创建时间 */
	time_t dwLastStamp;/*  共享内存最后修改时间戳 */
	unsigned int dwBusiID;/**<使用xlrpc系统的业务的ID*/
	unsigned int dwCRC; /*  共享内存检验码 */
	int iAlign;/*通道数据对齐方式*/
	int iAlignLevel;/*通道数据对齐值的对数值,其值通过iAlign计算出来*/
	pthread_rwlock_t stRWLock;/**< XLRPC配置共享内存中，通过互斥读写锁进行互斥访问*/
	XLRPCADDRTEMPLET	stAddrTemplet;/**< 本bus系统所使用的点分十进制地址模板*/
    unsigned int dwBuild;   /*GCIM数据结构的版本*/
	unsigned int aiReserved[XLRPC_SHM_GCIM_HEAD_RESERV_NUM]; 	/*预留数据区*/
};
typedef struct tagXLrpcShmGCIMHead XLRPCSHMGCIMHEAD;
typedef struct tagXLrpcShmGCIMHead *LPXLRPCSHMGCIMHEAD;
```



```c
struct tagShmChannelCnf
{
	unsigned int dwFlag;/*   bit set: 0001 -- route valid */
	unsigned int dwPriority;
	HANDLE iShmID;	/*id of share memory for channel*/
	XLRPCADDR astAddrs[2];
	/* 通道两端的地址  original ip format: xxx.xxx.xxx.xxx, converted by xlrpc_addr_aton() */

	unsigned int dwRecvSize;/*对于astAddrs[0]来说其接收队列的大小, default is 2M */
	unsigned int dwSendSize;/*对于astAddrs[0]来说其发送队列的大小, default is 2M */

	time_t dwCTime;
	time_t dwInvalidTime;	/*此通道被设置为失效的起始时间*/

    /* 2.6.2版本开始，为了支持跨机通信时WAN DSCP特性（设置IP首部TOS字段）,
     * 启用了预留空间中的一个字节，此前总预留空间为16字节*/
    unsigned char bWanQos;
    unsigned char bUnused[XLRPC_CHANNEL_UNUSED_CHAR_NUM];
	int aiReserved[XLRPC_CHANNEL_RESERVER_NUM];
};
typedef struct tagShmChannelCnf                         	XLRPCSHMCHANNELCNF;
typedef struct tagShmChannelCnf                         	*LPXLRPCSHMCHANNELCNF;
```

### 具体通道的配置信息

```c
struct tagXLrpcShmGCIM
{
	XLRPCSHMGCIMHEAD	stHead;
	XLRPCSHMCHANNELCNF astChannels[XLRPC_MAX_CHANNEL_NUM_PREHOST]; /*具体通道的配置信息*/
};
typedef struct tagXLrpcShmGCIM	XLRPCSHMGCIM;
typedef struct tagXLrpcShmGCIM	*LPXLRPCSHMGCIM;
```





### xlrpc系统通信地址

```c
typedef  int    XLRPCADDR;
typedef  int    *LPXLRPCADDR;
```



### Bus通道

```c
struct tagXLrpcChannel
{
	unsigned int dwFlag;		/**<标志信息位*/
	int iRecvSide;              /*通道数据接收端，其对应地址为对端的地址其值为0或1*/
	int iSendSide;               /*通道数据发送端，其对应地址为对端的地址，其值为(iRecvSide+1)%2*/
	HANDLE iShmID;	/*id of share memory for channel*/

	/*通道信息头部，本成员指向共享内存中通道头部，pstHead->astAddr[iRecvSide]为本地地址*/
	CHANNELHEAD *pstHead;

	/*读写消息队列, 本成员指向共享内存中通道的两个队列*/
    /*pszQueues[iRecvSide]为读队列，pszQueues[iSendSide]为写队列*/
	char *pszQueues[2];

    /*控制消息读写队列，本成员指向共享内存中通道的两个控制消息队列*/
    /*pszCtrlQueues[iRecvSide]为读队列，pszCtrlQueues[iSendSide]为写队列*/
    char *pszCtrlQueues[2];

    LPXLRPCPROCESSSTATE pstPeerState;

	time_t tBeginDisable;		/*开始失效的起始时间*/
    int iHandle;                /*保存所属的句柄索引*/

    XLRPCPROCESSSTATE stPeerState; /*用于Channel模式，防止访问pstPeerState时程序core*/
	XLRPCHEAD stHead;            /*用于Channel模式 支持forward和backward操作的数据结构*/

    size_t tReadThreadID;
    size_t tWriteThreadID;
};
typedef struct tagXLrpcChannel                          	XLRPCCHANNEL;
typedef struct tagXLrpcChannel                              *LPXLRPCCHANNEL;
```





```c
struct tagXLrpcHandle
{
	unsigned int dwFlag;/* 标志位 */
	unsigned int dwChannelCnt;/* 此句柄管理的通道数据 */
	XLRPCCHANNEL *pastChannelSet[TUBS_MAX_CHANNEL_COUNT_PREHANDLE];/*通道信息数据 */

    unsigned int dwPeerCnt;
    XLRPCPROCESSSTATE astPeerState[TUBS_MAX_CHANNEL_COUNT_PREHANDLE];

	int iRecvPos;/*new field, current received address position */
	unsigned int dwRecvPkgCnt;/*   received packages count in one channel */
	XLRPCHEAD stRecvHead;/*   head of recv Pkg  package */
	XLRPCHEAD stHeadBak;/*  backup of the head of send Pkg  package */

	volatile unsigned int dwGCIMVersion;/**< version of GCIM in share memory*/
	int iBindAddrNum;/*此句柄上已经绑定的地址数, 标识aiBindAddr已使用大小*/
	XLRPCADDR aiBindAddr[XLRPC_MAX_BIND_ADDR_NUM_PREHANDLE]; /*此句柄上已经bind的地址数*/
};
struct tagXLrpcHandle;
typedef struct tagXLrpcHandle                        	XLRPCHANDLE;
typedef struct tagXLrpcHandle                        	*LPXLRPCHANDLE;
```



```c
struct tagXLrpcProcessState
{
    long long llLastBeatTime;
    int iIsAlive;
    int iIsAvailable;
    int iTimeOutGap;
    XLRPCADDR iPeerAddr;
    int iBindedChnnlNum;
};
typedef struct tagXLrpcProcessState                      XLRPCPROCESSSTATE;
typedef struct tagXLrpcProcessState                   *LPXLRPCPROCESSSTATE;
```



### **GRM**: Global Route Map

* 全局路由表，供TBUSD使用，用于判断哪些**channel**中的消息需要由TBUSD中转
* GRM保存在共享内存中，每台物理机器仅需要一份
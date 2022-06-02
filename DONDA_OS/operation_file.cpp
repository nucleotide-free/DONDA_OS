#include "OS.h"

//为创建文件或目录 初始化i结点
void createInitINode(int iNode_id, int type)
{
	fileSystem.iNode[iNode_id].id = iNode_id;//i节点的id，即在数组里的id
	fileSystem.iNode[iNode_id].type = type;	 //文件类型 0-普通 1-目录
	fileSystem.iNode[iNode_id].owner = user.user_id;//文件创立者
	for (int i = 1; i <= 8; i++) 
		fileSystem.iNode[iNode_id].auth[i] = 0;//全部user都无权限
	fileSystem.iNode[iNode_id].auth[user.user_id] = 1;//仅创立者有权限

	fileSystem.iNode[iNode_id].file_len = 0;//文件长度
	fileSystem.iNode[iNode_id].link_count = 0;//链接次数 = 0
	fileSystem.iNode[iNode_id].last_visited_time = getTime();//最后一次存取时间（当前时间）
	for (int i = 0; i < ADDR_NUM; i++)
		fileSystem.iNode[iNode_id].i_addr[i] = -1;//使用的磁盘资源
}

//为新创建的文件分配一个i结点，返回i节点编号，-1为没找到
int createiNode(int type)
{
	int iNode_id = -1;//新的i节点编号
	for (int i = 0; i < INODE_BITMAP_ROW; i++) {
		for (int j = 0; j < INODE_BITMAP_COL; j++) {
			if (fileSystem.superBlock.iNode_bitmap[i][j] == 0) {//查位示图，找到一个空闲的i节点
				fileSystem.superBlock.iNode_bitmap[i][j] = 1;//设置为被占用
				iNode_id = i * INODE_BITMAP_COL + j;
				fileSystem.superBlock.free_iNode_num--;//空闲i节点数 -1
				break;
			}
		}
		if (iNode_id != -1)break;
	}
	createInitINode(iNode_id, type);//为创建文件或目录初始化i结点，类型为0，表示文件，长度为0，初始化i结点
	return iNode_id;
}

//分配SFD目录项
void createSFD(int iNode_id, string name) {
	SFD_ITEM temp;
	temp.file_name = name;		//文件名输入
	temp.file_id = iNode_id;			//SFD_ITEM的id等于i节点的id
	fileSystem.SFD[sfd_pointer].sfd_list.push_back(temp);		//将这个sfd_item放入当前目录的SFD下的sfd_list当中
	fileSystem.SFD[sfd_pointer].sfd_num++;		//当前目录的SFD下的sfd_item数量
}

//创建文件，1-成功，0-失败
int createFile(string fileName)
{
	if (fileSystem.superBlock.free_diskblock_num == 0 || fileSystem.superBlock.free_iNode_num == 0) {
		return 1;//没有空闲磁盘块或者空闲i节点！
	}
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {//查询是否重名
		if (fileName == fileSystem.SFD[sfd_pointer].sfd_list[i].file_name) {
			return 2;//文件名冲突
		}
	}
	int iNode_id = createiNode(0);//分配到一个i节点
	createSFD(iNode_id, fileName);
	return 0;
}

//删除文件
void deleteFile(string fileName) 
{
	int iNode_id = findiNodeByName(fileName);
	deleteDiskBlock(iNode_id);//回收磁盘块
	deleteiNode(iNode_id);//回收i节点
	deleteSFD_ITEM(iNode_id);//回收SFD子项
}

//回收磁盘块
void deleteDiskBlock(int iNode_id)
{
	for (int i = 0; i < 10; i++) {//回收直接地址的磁盘块
		if (fileSystem.iNode[iNode_id].i_addr[i] != -1) {//磁盘块被用了
			int diskBlock_id = fileSystem.iNode[iNode_id].i_addr[i];
			fileSystem.diskBlock[diskBlock_id].content = "";//清空磁盘块内容
			fileSystem.diskBlock[diskBlock_id].content_len = 0;
			FreeABlock(diskBlock_id);//回收磁盘块
		}
	}
	int diskBlock_id;
	if ((diskBlock_id = fileSystem.iNode[iNode_id].i_addr[10]) != -1) {//一级索引
		vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[diskBlock_id].content);//读取一级索引中的磁盘块块号
		for (int i = 0; i < index_block_level1.size(); i++) {//每一个块号
			fileSystem.diskBlock[index_block_level1[i]].content = "";//清空磁盘块内容
			fileSystem.diskBlock[index_block_level1[i]].content_len = 0;
			FreeABlock(index_block_level1[i]);	//回收磁盘块
			
		}
	}
	if ((diskBlock_id = fileSystem.iNode[iNode_id].i_addr[11]) != -1) {//二级索引
		vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[diskBlock_id].content);//读取一级索引中的磁盘块块号
		for (int i = 0; i < index_block_level1.size(); i++) {//每一个块号
			vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);//读取二级索引中的磁盘块块号
			for (int j = 0; j < index_block_level2.size(); j++) {
				fileSystem.diskBlock[index_block_level2[j]].content = "";//清空磁盘块内容
				fileSystem.diskBlock[index_block_level2[j]].content_len = 0;
				FreeABlock(index_block_level2[j]);	//回收磁盘块
			}
		}
	}
	if ((diskBlock_id = fileSystem.iNode[iNode_id].i_addr[12]) != -1) {//三级索引
		vector<int> index_block_level1 = ReadIndexBlock(fileSystem.diskBlock[diskBlock_id].content);//读取一级索引中的磁盘块块号
		for (int i = 0; i < index_block_level1.size(); i++) {//每一个块号
			vector<int> index_block_level2 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);//读取二级索引中的磁盘块块号
			for (int j = 0; j < index_block_level2.size(); j++) {
				vector<int> index_block_level3 = ReadIndexBlock(fileSystem.diskBlock[index_block_level1[i]].content);//读取三级索引中的磁盘块块号
				for (int k = 0; k < index_block_level3.size(); k++) {
					fileSystem.diskBlock[index_block_level3[k]].content = "";//清空磁盘块内容
					fileSystem.diskBlock[index_block_level3[k]].content_len = 0;
					FreeABlock(index_block_level3[k]);	//回收磁盘块
				}
			}
		}
	}
}

//删除待i结点
void deleteiNode(int iNode_id)      
{	
	
	createInitINode(iNode_id, 0);
	fileSystem.iNode[iNode_id].id = 0;//i节点的id，即在数组里的id
	fileSystem.iNode[iNode_id].owner = 0;//文件创立者
	for (int i = 1; i <= 8; i++)
		fileSystem.iNode[iNode_id].auth[i] = 0;//全部user都无权限
	fileSystem.iNode[iNode_id].last_visited_time = "";//最后一次存取时间（当前时间）

	fileSystem.superBlock.free_iNode_num++;//空闲节点++
	fileSystem.superBlock.iNode_bitmap[iNode_id / INODE_BITMAP_COL][iNode_id % INODE_BITMAP_COL] = 0;//释放位示图资源
}

//回收SFD子项
void deleteSFD_ITEM(int file_id)
{
	for (int i = 0; i < fileSystem.SFD[sfd_pointer].sfd_num; i++) {
		if (fileSystem.SFD[sfd_pointer].sfd_list[i].file_id == file_id) {
			fileSystem.SFD[sfd_pointer].sfd_list.erase(fileSystem.SFD[sfd_pointer].sfd_list.begin() + i);//删除该sfd项
			fileSystem.SFD[sfd_pointer].sfd_num--;
		}
	}
}

//遍历删除与待删除文件共享的文件目录
void findSinglesfd(int inodeNo) {

}

//获取当前时间
string getTime() {		
	time_t time_seconds = time(0);
	tm now_time;
	localtime_s(&now_time, &time_seconds);

	std::stringstream ss;
	ss << now_time.tm_year + 1900 << "/" << now_time.tm_mon + 1 << "/"
		<< now_time.tm_mday << "," << now_time.tm_hour << ":"
		<< now_time.tm_min << ":" << now_time.tm_sec;
	return  ss.str();
}

//打开文件
void openFile(string fileName) 
{
	int diNode_id = findiNodeByName(fileName);		//找到磁盘iNode_id
	if (checkOpen(diNode_id)) {
		cout << "文件已经被打开" << endl;
		return;
	}
	if (fileSystem.iNode[diNode_id].type == 1)
	{
		cout << "目录文件不可打开" << endl;
		return;
	}
	MEM_BFD_ITEM m_iNode;
	initMEM_iNode(m_iNode, diNode_id);		//初始化内存i节点
	MEM_BFD_ITEM* m_iNode_pointer = (MEM_BFD_ITEM*)malloc(sizeof(MEM_BFD_ITEM) * 1); //内存i节点指针
	m_iNode_pointer = &mem_iNode[m_iNode.id % NHINO];		//指向要插入的iNode的hash链表中

	while(m_iNode_pointer->next){
		m_iNode_pointer = m_iNode_pointer->next;		//遍历到链表的最后
	}
	m_iNode_pointer->next = &m_iNode;	//插入iNode
	m_iNode.prev = m_iNode_pointer;		//双向链表插入prev指针

	updateFileOpened(m_iNode, fileName);//修改用户打开文件表和系统打开文件表
	free(m_iNode_pointer);
}

//检查文件是否被打开
int checkOpen(int iNode_id)		
{
	MEM_BFD_ITEM* temp = NULL;
	MEM_BFD_ITEM* m_iNode_pointer= (MEM_BFD_ITEM*)malloc(sizeof(MEM_BFD_ITEM) * 1); //内存i节点指针
	temp = m_iNode_pointer;
	m_iNode_pointer = &mem_iNode[iNode_id % NHINO];		//指向要插入的iNode的hash链表中
	while (m_iNode_pointer->next)
	{
		if (iNode_id == m_iNode_pointer->id)
		{
			free(temp);
			return 1;
		}
		m_iNode_pointer = m_iNode_pointer->next;		//遍历到链表的最后
	}
	free(temp);
	return 0;
}


//初始化内存i节点
void initMEM_iNode(MEM_BFD_ITEM m_iNode, int iNode_id) {
	m_iNode.id = fileSystem.iNode[iNode_id].id;//i节点的id，即在数组里的id
	m_iNode.type = 0;		//文件类型 0-普通 1-目录
	m_iNode.owner = fileSystem.iNode[iNode_id].owner;//文件创立者
	for (int i = 1; i <= 8; i++)
		m_iNode.auth[i] = fileSystem.iNode[iNode_id].auth[i];//权限

	m_iNode.file_len = fileSystem.iNode[iNode_id].file_len; // 文件长度
	m_iNode.link_count = fileSystem.iNode[iNode_id].link_count;//链接次数
	m_iNode.last_visited_time = getTime();//最后一次存取时间（当前时间）
	for (int i = 0; i < ADDR_NUM; i++)
		m_iNode.i_addr[i] = fileSystem.iNode[iNode_id].i_addr[i];//使用的磁盘资源

	m_iNode.index_num = m_iNode.id % NHINO;//hash索引节点编号
	m_iNode.status_lock = 0;//未上锁
	m_iNode.status_mod = 0;//尚未被修改
	m_iNode.shared_count = 0;//共享次数=0

	m_iNode.next = NULL;
}

//修改用户打开文件表和系统打开文件表
void updateFileOpened(MEM_BFD_ITEM m_iNode, string fileName)
{
	user.file_Uopened.push_back(m_iNode.id);//用户打开文件表，里面放的是iNode_id

	FILE_OPEND file_opened;	//系统打开表
	file_opened.fileName = fileName;//文件名
	int f_count = 0;//访问次数 = 0
	file_opened.f_inode = m_iNode.id;//储存内存i节点的地址
	file_opend_list.push_back(file_opened);
}


//关闭文件
void closeFIle(string fileName)
{

}
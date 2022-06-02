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
	temp.type = 0;				//生成的是普通目录项
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
	if (fileSystem.iNode[diNode_id].type == 1){
		cout << "目录文件不可打开！" << endl;
		return;
	}
	if (checkOpen(diNode_id))
	{
		for (int i = 0; i < user.file_Uopened.size(); i++)//当前用户的用户打开表下有没有该iNode_id
		{
			if (diNode_id == user.file_Uopened[i])//该用户打开过这个文件
			{
				return;
			}
		}
		user.file_Uopened.push_back(diNode_id);//当前用户打开文件表，里面放的是iNode_id
		userList[user.user_id].file_Uopened.push_back(diNode_id);//全体用户打开文件表，里面放的是iNode_id
	}
	else{
	MEM_BFD_ITEM m_iNode = initMEM_iNode(diNode_id);	//初始化内存i节点;
	mem_iNode[m_iNode.id % NHINO] = m_iNode;		//指向要插入的iNode的hash链表中
	user.file_Uopened.push_back(m_iNode.id);//当前用户打开文件表，里面放的是iNode_id
	userList[user.user_id].file_Uopened.push_back(m_iNode.id);//全体用户打开文件表，里面放的是iNode_id
	FILE_OPEND file_opened = { fileName ,0,m_iNode.id };	//修改系统打开文件表
	file_opend_list.push_back(file_opened);
	}
}

//检查文件是否被打开
int checkOpen(int iNode_id)
{
	if (iNode_id == mem_iNode[iNode_id % NHINO].id)
	{
		return 1;
	}
	return 0;
}

//检查用户打开文件表的被打开次数
int checkUserOpen(int iNode_id)
{
	int count = 0;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 0; j < userList[i].file_Uopened.size(); j++)
		{
			if (userList[i].file_Uopened[j] == iNode_id) {
				count++;
			}
		}
	}
	return count;
}

//初始化内存i节点
MEM_BFD_ITEM  initMEM_iNode(int iNode_id) {
	MEM_BFD_ITEM m_iNode;
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
	m_iNode.shared_count = 1;//共享次数=1，被一个用户打开

	return m_iNode;
}

//关闭文件
void closeFIle(string fileName)
{
	int diNode_id = findiNodeByName(fileName);	//找到磁盘iNode_id

	if (fileSystem.iNode[diNode_id].type == 1){	//试图关闭目录文件
		cout << "目录文件不可关闭" << endl;
		return;
	}
	int count = checkUserOpen(diNode_id);//文件被打开的次数
	if (count == 0) {
		cout << "没有打开该文件！\n";
		return;
	}
	for (int j = 0; j < userList[user.user_id].file_Uopened.size(); j++){
		if (userList[user.user_id].file_Uopened[j] == diNode_id) {
			userList[user.user_id].file_Uopened.erase(userList[user.user_id].file_Uopened.begin() + j);//用户列表中该用户的用户打开文件表
			user.file_Uopened.erase(user.file_Uopened.begin() + j);//修改当前用户的用户打开文件表

			if (count > 1)return;//不是最后一个关闭该文件的人，不需要进行下列操作，直接返回
		}
	}
	//仅当前用户打开了该文件
	
	MEM_BFD_ITEM m_iNode = mem_iNode[diNode_id % NHINO];//找到该iNode_id对应的hash表中的内存iNode

	//放入磁盘，更新磁盘i Node的数据
	fileSystem.iNode[diNode_id].last_visited_time = m_iNode.last_visited_time;//最后一次访问时间

	for (int i = 0; i < file_opend_list.size(); i++) {//更新系统打开表
		if (file_opend_list[i].fileName == fileName&& diNode_id== file_opend_list[i].f_inode) {
			file_opend_list.erase(file_opend_list.begin() + i);
			break;
		}
	}
	mem_iNode[diNode_id % NHINO].id = 0;//清除hash表中的该数据
}

//展示系统打开文件表
void showSystemFileOpen()
{
	cout << "\n\t\t系统打开文件表\n";
	cout << "┌───────────────────────────────────────┐\n"; 
	cout << "│ 文件名        访问次数      i节点号   │\n";
	for (int i = 0; i < file_opend_list.size(); i++) {
		cout << "│ " + file_opend_list[i].fileName + "\t\t    " << file_opend_list[i].f_count << "\t\t" << file_opend_list[i].f_inode << "\t│\n";
	}
	cout << "└───────────────────────────────────────┘\n\n";
	
}
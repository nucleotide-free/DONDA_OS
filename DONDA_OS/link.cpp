#include "OS.H"

//新建连接
void createLink(string fileName)
{
	cout << "准备link文件" << fileName << endl;

	int iNode_id = findiNodeByName(fileName);
	link_board.file_id = iNode_id;//更新链接包里的内容
	link_board.file_name = fileName;
	link_board.type = 1;//新建表项为链接类型
}

//粘贴链接文件到当前目录
void pasteLink()
{
	fileSystem.SFD[sfd_pointer].sfd_list.push_back(link_board);//将这个sfd_item放入当前目录的SFD下的sfd_list当中
	fileSystem.SFD[sfd_pointer].sfd_num++;//当前目录的SFD下的sfd_item数量
	link_board.file_id = -1;//清空链接数据
	cout << "创建连接文件成功！\n";
}

//删除连接
void deleteLink(string fileName)
{
	deleteSFD_ITEM(findiNodeByName(fileName));
}
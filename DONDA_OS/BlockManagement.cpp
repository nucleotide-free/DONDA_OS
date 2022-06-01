#include "OS.h"

//成组链接--分配空闲块
int AllocateOneBlock() {
	int free_block;		//空闲块块号
	if (fileSystem.superBlock.stack_size == 1)
	{
		if (fileSystem.superBlock.free_block_stack.top() == -1) {
			//cout << "分配失败,进程等待" << endl;
			return -1;
		}
		else {
			free_block= ReadABlock(fileSystem.superBlock.free_block_stack, fileSystem.superBlock.free_block_stack.top());
			int index = 0;
			for (int i = 0; i < fileSystem.superBlock.free_diskblock_id.size(); i++) {
				if (free_block == fileSystem.superBlock.free_diskblock_id[i]) {
					index = i;
				}
			}
			fileSystem.superBlock.free_diskblock_id.erase(fileSystem.superBlock.free_diskblock_id.begin() + index);//删除该元素		fileSystem.superBlock.free_block_stack.pop();

			return free_block;
		}
	}
	else {
		free_block=fileSystem.superBlock.free_block_stack.top();
		fileSystem.superBlock.free_diskblock_num--;		//空闲块数量--

		int index=0;
		for (int i = 0; i < fileSystem.superBlock.free_diskblock_id.size(); i++) {
			if (free_block== fileSystem.superBlock.free_diskblock_id[i]) {
				index = i;
			}
		}
		fileSystem.superBlock.free_diskblock_id.erase(fileSystem.superBlock.free_diskblock_id.begin() + index);//删除该元素		fileSystem.superBlock.free_block_stack.pop();

		return free_block;
	}
}

int ReadABlock(stack<int> free_block_stack,int block_num) {		//读组长块中的内容
	int temp=0;
	fileSystem.superBlock.free_block_stack.pop();
	for (int i = 0; i < fileSystem.diskBlock[block_num].content.size(); i++) {
		if (fileSystem.diskBlock[block_num].content[i]!=' ')
		{
			temp *= 10;
			temp = fileSystem.diskBlock[block_num].content[i] - '0';
		}
		else {
			fileSystem.superBlock.free_block_stack.push(temp);
			temp = 0;
		}
	}
	return temp;
}

//成组链接--回收空闲块
void FreeABlock(int BlockNo) 
{
	if (fileSystem.superBlock.stack_size < 50) {
		fileSystem.superBlock.stack_size++;
		fileSystem.superBlock.free_block_stack.push(BlockNo);//放入
	}
	else {//存成组长块，放入磁盘
		for (int j = 0; j < 50; j++) {
			fileSystem.diskBlock[BlockNo].content += to_string(fileSystem.superBlock.free_block_stack.top()) + " ";//存入磁盘文件
			fileSystem.superBlock.free_block_stack.pop();//弹栈
			fileSystem.diskBlock[BlockNo].content_len++;//修改文件长度
		}
		fileSystem.superBlock.stack_size = 1;//初始化超级块
		fileSystem.superBlock.free_block_stack.push(BlockNo);
	}
	fileSystem.superBlock.free_diskblock_num++;//空闲块数+1
	fileSystem.superBlock.free_diskblock_id.push_back(BlockNo);		//把对应的空闲块
}
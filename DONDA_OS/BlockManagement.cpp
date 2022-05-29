#include "OS.h"

//成组链接--分配空闲块
int AllocateOneBlock() {

}

//成组链接--回收空闲块
int FreeABlock(int BlockNo) 
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
}
#include "OS.h"

int AllocateOneBlock() {
	if (fileSystem.superBlock.stack_size == 1)
	{
		if (fileSystem.superBlock.free_block_stack.top() == 0) {
			cout << "分配失败,进程等待" << endl;
		}
		else {
			int free_block=ReadABlock(fileSystem.superBlock.free_block_stack, fileSystem.superBlock.free_block_stack.top());
			return free_block;
		}
	}
	else {
		return;
	}
}

int ReadABlock(stack<int> free_block_stack,int block_num) {
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
}

int FreeABlock() {

}
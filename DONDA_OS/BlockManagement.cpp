#include "OS.h"

//��������--������п�
int AllocateOneBlock() {

}

//��������--���տ��п�
int FreeABlock(int BlockNo) 
{
	if (fileSystem.superBlock.stack_size < 50) {
		fileSystem.superBlock.stack_size++;
		fileSystem.superBlock.free_block_stack.push(BlockNo);//����
	}
	else {//����鳤�飬�������
		for (int j = 0; j < 50; j++) {
			fileSystem.diskBlock[BlockNo].content += to_string(fileSystem.superBlock.free_block_stack.top()) + " ";//��������ļ�
			fileSystem.superBlock.free_block_stack.pop();//��ջ
			fileSystem.diskBlock[BlockNo].content_len++;//�޸��ļ�����
		}
		fileSystem.superBlock.stack_size = 1;//��ʼ��������
		fileSystem.superBlock.free_block_stack.push(BlockNo);
	}
	fileSystem.superBlock.free_diskblock_num++;//���п���+1
}
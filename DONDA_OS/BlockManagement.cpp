#include "OS.h"

//��������--������п�
int AllocateOneBlock() {
	int free_block;		//���п���
	if (fileSystem.superBlock.stack_size == 1)
	{
		if (fileSystem.superBlock.free_block_stack.top() == -1) {
			//cout << "����ʧ��,���̵ȴ�" << endl;
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
			fileSystem.superBlock.free_diskblock_id.erase(fileSystem.superBlock.free_diskblock_id.begin() + index);//ɾ����Ԫ��		fileSystem.superBlock.free_block_stack.pop();

			return free_block;
		}
	}
	else {
		free_block=fileSystem.superBlock.free_block_stack.top();
		fileSystem.superBlock.free_diskblock_num--;		//���п�����--

		int index=0;
		for (int i = 0; i < fileSystem.superBlock.free_diskblock_id.size(); i++) {
			if (free_block== fileSystem.superBlock.free_diskblock_id[i]) {
				index = i;
			}
		}
		fileSystem.superBlock.free_diskblock_id.erase(fileSystem.superBlock.free_diskblock_id.begin() + index);//ɾ����Ԫ��		fileSystem.superBlock.free_block_stack.pop();

		return free_block;
	}
}

int ReadABlock(stack<int> free_block_stack,int block_num) {		//���鳤���е�����
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

//��������--���տ��п�
void FreeABlock(int BlockNo) 
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
	fileSystem.superBlock.free_diskblock_id.push_back(BlockNo);		//�Ѷ�Ӧ�Ŀ��п�
}
#ifndef HASH_H_
#define HASH_H_

#include "hash.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

#define HASH_TABLE_MAX_SIZE 10000  
typedef struct HashNode_Struct HashNode;  
struct HashNode_Struct  {  
    char* sKey;  
    int nValue;  
    HashNode* pNext;  
};  //��ϣ�����ݽṹ 

HashNode* hashTable[HASH_TABLE_MAX_SIZE]; 
int hash_table_size;  //��ϣ���м�ֵ�Ե����� 

void hash_table_init();  //��ʼ����ϣ�� 
unsigned int hash_table_hash_str(const char* skey);	//ȥ���Ż���ϣ�� 
void hash_table_insert(const char* skey, int nvalue);  //���� 
void hash_table_remove(const char* skey);	//ɾ�� 
HashNode* hash_table_lookup(const char* skey); //���� 
void hash_table_print();	//��ӡ 
void hash_table_release();	//�ͷ��ڴ� 

#endif // !HASH_H_


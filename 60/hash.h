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
};  //哈希表数据结构 

HashNode* hashTable[HASH_TABLE_MAX_SIZE]; 
int hash_table_size;  //哈希表中键值对的数量 

void hash_table_init();  //初始化哈希表 
unsigned int hash_table_hash_str(const char* skey);	//去符号化哈希表 
void hash_table_insert(const char* skey, int nvalue);  //插入 
void hash_table_remove(const char* skey);	//删除 
HashNode* hash_table_lookup(const char* skey); //查找 
void hash_table_print();	//打印 
void hash_table_release();	//释放内存 

#endif // !HASH_H_


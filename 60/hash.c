#include "hash.h"

//初始化哈希表 
void hash_table_init()  
{  
    hash_table_size = 0;  
    memset(hashTable, 0, sizeof(HashNode*) * HASH_TABLE_MAX_SIZE);
    //memset(void *s,int c,size_t n); 
    //将s中后n个字节换成c所代表的内容 
    //该函数是对较大结构体或数组进行清零操作的一种最快的方法 
}  


//去符号化哈希表  
unsigned int hash_table_hash_str(const char* skey)  
{  //无符号unsigned能保存2倍与有符号类型的正整型数据 
    const signed char *p = (const signed char*)skey; //常量 
    unsigned int h = *p;  
    if(h)
    {  
        for(p += 1; *p != '\0'; ++p)  
            h = (h << 5) - h + *p;  
    }  
    return h;  
}
//插入 
void hash_table_insert(const char* skey, int nvalue)  
{  
    if(hash_table_size >= HASH_TABLE_MAX_SIZE) //如果定义的哈希表长度大于等于最大长度 
    {  
        printf("内存溢出!\n");
        return;  
    }  

    unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;  
  //用于解决冲突，pos为哈希函数 
    HashNode* pHead = hashTable[pos];
    while(pHead)
    {  
        if(strcmp(pHead->sKey, skey) == 0)  
        {  
            printf("%s发生冲突!\n", skey);
            return ;  
        }  
        pHead = pHead->pNext;  
    }  
    //动态建立结点，初始化，分配内存空间 
    HashNode* pNewNode = (HashNode*)malloc(sizeof(HashNode));  
    memset(pNewNode, 0, sizeof(HashNode));  
    pNewNode->sKey = (char*)malloc(sizeof(char) * (strlen(skey) + 1));  
    strcpy(pNewNode->sKey, skey);  
    pNewNode->nValue = nvalue;  

    //指针后移 
    pNewNode->pNext = hashTable[pos];  
    hashTable[pos] = pNewNode;  
    //表长增加 
    hash_table_size++;  
}  
//删除 
void hash_table_remove(const char* skey)  
{  
    unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE; 

    if(hashTable[pos])  
    {  
        HashNode* pHead = hashTable[pos];  
        HashNode* pLast = NULL;  
        HashNode* pRemove = NULL;  
        while(pHead)  
        {  
            if(strcmp(skey, pHead->sKey) == 0)  
            {   //若str1==str2，则返回零;
                //若str1>str2，则返回正数;
                //若str1<str2，则返回负数。 
                pRemove = pHead;//若相等，用pRemove记录  
                break; 
            }  
            pLast = pHead;  //若不相等，不断后移 
            pHead = pHead->pNext;  
        }  
        if(pRemove)  
        {  
            if(pLast)
                pLast->pNext = pRemove->pNext;//实现删除1 
            else  
                hashTable[pos] = NULL;//实现删除2

            free(pRemove->sKey);  
            free(pRemove);  
        }  
    }  
}  

//查找 
HashNode* hash_table_lookup(const char* skey)  
{  
    unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;  

    if(hashTable[pos])  
    {  
        HashNode* pHead = hashTable[pos];  
        while(pHead)  
        {  
            if(strcmp(skey, pHead->sKey) == 0)  
                return pHead;//查找成功 

            pHead = pHead->pNext;  
        }  
    }  
    return NULL;  
}  

//打印 
void hash_table_print()  
{ 
    int i;  
    for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i)  
        if(hashTable[i])//表不空 
        {  
            HashNode* pHead = hashTable[i];  
            printf("%d=>", i);  
            while(pHead)  
            {  
                printf("%s:%d  ", pHead->sKey, pHead->nValue);  
                pHead = pHead->pNext;  
            }  
            printf("\n");  
        }  
}  

//释放内存 
void hash_table_release()  
{  
    int i;  
    for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i)  
    {  
        if(hashTable[i])  
        {  
            HashNode* pHead = hashTable[i];  
            while(pHead)  
            {  
                HashNode* pTemp = pHead;  
                pHead = pHead->pNext;  
                if(pTemp)  
                {  
                    free(pTemp->sKey);  
                    free(pTemp);  
                }  
                //逐个释放 
            }  
        }  
    }  
}  

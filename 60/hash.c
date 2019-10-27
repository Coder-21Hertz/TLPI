#include "hash.h"

//��ʼ����ϣ�� 
void hash_table_init()  
{  
    hash_table_size = 0;  
    memset(hashTable, 0, sizeof(HashNode*) * HASH_TABLE_MAX_SIZE);
    //memset(void *s,int c,size_t n); 
    //��s�к�n���ֽڻ���c����������� 
    //�ú����ǶԽϴ�ṹ�������������������һ�����ķ��� 
}  


//ȥ���Ż���ϣ��  
unsigned int hash_table_hash_str(const char* skey)  
{  //�޷���unsigned�ܱ���2�����з������͵����������� 
    const signed char *p = (const signed char*)skey; //���� 
    unsigned int h = *p;  
    if(h)
    {  
        for(p += 1; *p != '\0'; ++p)  
            h = (h << 5) - h + *p;  
    }  
    return h;  
}
//���� 
void hash_table_insert(const char* skey, int nvalue)  
{  
    if(hash_table_size >= HASH_TABLE_MAX_SIZE) //�������Ĺ�ϣ���ȴ��ڵ�����󳤶� 
    {  
        printf("�ڴ����!\n");
        return;  
    }  

    unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;  
  //���ڽ����ͻ��posΪ��ϣ���� 
    HashNode* pHead = hashTable[pos];
    while(pHead)
    {  
        if(strcmp(pHead->sKey, skey) == 0)  
        {  
            printf("%s������ͻ!\n", skey);
            return ;  
        }  
        pHead = pHead->pNext;  
    }  
    //��̬������㣬��ʼ���������ڴ�ռ� 
    HashNode* pNewNode = (HashNode*)malloc(sizeof(HashNode));  
    memset(pNewNode, 0, sizeof(HashNode));  
    pNewNode->sKey = (char*)malloc(sizeof(char) * (strlen(skey) + 1));  
    strcpy(pNewNode->sKey, skey);  
    pNewNode->nValue = nvalue;  

    //ָ����� 
    pNewNode->pNext = hashTable[pos];  
    hashTable[pos] = pNewNode;  
    //������ 
    hash_table_size++;  
}  
//ɾ�� 
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
            {   //��str1==str2���򷵻���;
                //��str1>str2���򷵻�����;
                //��str1<str2���򷵻ظ����� 
                pRemove = pHead;//����ȣ���pRemove��¼  
                break; 
            }  
            pLast = pHead;  //������ȣ����Ϻ��� 
            pHead = pHead->pNext;  
        }  
        if(pRemove)  
        {  
            if(pLast)
                pLast->pNext = pRemove->pNext;//ʵ��ɾ��1 
            else  
                hashTable[pos] = NULL;//ʵ��ɾ��2

            free(pRemove->sKey);  
            free(pRemove);  
        }  
    }  
}  

//���� 
HashNode* hash_table_lookup(const char* skey)  
{  
    unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;  

    if(hashTable[pos])  
    {  
        HashNode* pHead = hashTable[pos];  
        while(pHead)  
        {  
            if(strcmp(skey, pHead->sKey) == 0)  
                return pHead;//���ҳɹ� 

            pHead = pHead->pNext;  
        }  
    }  
    return NULL;  
}  

//��ӡ 
void hash_table_print()  
{ 
    int i;  
    for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i)  
        if(hashTable[i])//���� 
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

//�ͷ��ڴ� 
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
                //����ͷ� 
            }  
        }  
    }  
}  

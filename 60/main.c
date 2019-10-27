#include <stdio.h>
#include "hash.h"

#define MAX_STR_LEN 20  
#define MIN_STR_LEN 10  
int main()
{

    hash_table_init();     
 
    char str[MAX_STR_LEN + 1]; 
    const char *key1 = "aaa111";  
    const char *key2 = "bbb222";  
    const char *key3 = "ccc333";

    printf("����ǰ\n");
    hash_table_print(); 

    hash_table_insert(key1, 1);  
    hash_table_insert(key2, 2);  
    hash_table_insert(key3, 2);   

    printf("�����\n");
    hash_table_print();  

    HashNode* pNode = hash_table_lookup(key1);  
    printf("���ҽ��:%d\n", pNode->nValue);  
    pNode = hash_table_lookup(key2);  
    printf("���ҽ��:%d\n", pNode->nValue);

    printf("ɾ��֮ǰ:\n");  
    hash_table_print();  
    hash_table_remove(key3);  
    printf("ɾ��֮��:\n");  
    hash_table_print();  

    hash_table_release();  

    return 0;  
}

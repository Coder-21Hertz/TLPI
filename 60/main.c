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

    printf("插入前\n");
    hash_table_print(); 

    hash_table_insert(key1, 1);  
    hash_table_insert(key2, 2);  
    hash_table_insert(key3, 2);   

    printf("插入后\n");
    hash_table_print();  

    HashNode* pNode = hash_table_lookup(key1);  
    printf("查找结果:%d\n", pNode->nValue);  
    pNode = hash_table_lookup(key2);  
    printf("查找结果:%d\n", pNode->nValue);

    printf("删除之前:\n");  
    hash_table_print();  
    hash_table_remove(key3);  
    printf("删除之后:\n");  
    hash_table_print();  

    hash_table_release();  

    return 0;  
}

#include <stdio.h>
#include <stdlib.h>
#define Size 5
typedef struct Table{
    int * head;
    int length;
    int size;
}table;
table initTable(){
    table t;
    t.head=(int*)malloc(Size*sizeof(int));//malloc函数返回一个指针，指向已分配大小的内存。如果请求失败，则返回NULL
    if (!t.head)
    {
        printf("初始化失败\n");
        exit(0);
    }
    t.length=0;
    t.size=Size;
    return t;
}
// 插入函数，elem为插入的元素，add为插入到顺序表的位置
table addTable(table t,int elem,int add)
{
    // 判断插入本身是否存在问题，或者插入的位置本身不存在，程序作为提示并自动退出
    if (add>t.length+1||add<1) {
        printf("插入位置有问题\n");
        return t;
    }
    // 做插入操作时首先看顺序表是否有多余的存储空间提供给插入的元素，如果没有，需要申请
    if (t.length>=t.size) {
        t.head=(int *)realloc(t.head, (t.size+1)*sizeof(int));
        if (!t.head) {
            printf("存储分配失败\n");
        }
        t.size+=1;
    }
    // 插入操作，需要将从插入位置开始的后继元素逐个后移
    for (int i=t.length-1; i>=add-1; i--) {
        t.head[i+1]=t.head[i];
    }
    // 后移完成后，直接将所需元素插入，添加到顺序表的相应位置
    t.head[add-1]=elem;
    // 由于添加了元素所以长度加1
    t.length++;
    return t;
}
// 顺序表删除元素
table delTable(table t,int add){
    if (add>t.length || add<1) {
        printf("被删除元素的位置有误\n");
        return t;
    }
    // 删除操作
    for (int i=add; i<t.length; i++) {
        t.head[i-1]=t.head[i];
    }
    t.length--;
    return t;
}
// 顺序查找算法，查找函数，其中elem表示要查找的数据元素的值
int selectTable(table t,int elem){
    for (int i=0; i<t.length; i++) {
        if (t.head[i]==elem) {
            return i+1;
        }
    }
    return -1;//如果查找失败，返回-1
}
// 更改函数，其中elem为要更改的元素，newElem为新的数据元素
table amendTable(table t,int elem,int newElem){
    int add=selectTable(t, elem);
    t.head[add-1]=newElem;//由于返回的是元素在顺序表中的位置，所以-1就是该元素在数组中的下标
    return t;
}
void displayTable(table t){
    for (int i=0;i<t.length;i++) {
        printf("%d ",t.head[i]);
    }
    printf("\n");
}
int main(){
    table t1=initTable();
    for (int i=1; i<=Size; i++) {
        t1.head[i-1]=i;
        t1.length++;
    }
    printf("原顺序表：\n");
    displayTable(t1);
  
    printf("删除元素1:\n");
    t1=delTable(t1, 1);
    displayTable(t1);
  
    printf("在第2的位置插入元素5:\n");
    t1=addTable(t1, 5, 2);
    displayTable(t1);
  
    printf("查找元素3的位置:\n");
    int add=selectTable(t1, 3);
    printf("%d\n",add);
  
    printf("将元素3改为6:\n");
    t1=amendTable(t1, 3, 6);
    displayTable(t1);
    return 0;
}

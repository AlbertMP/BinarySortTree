//
//  main.cpp
//  binarySortTree
//
//  Created by 苗芃 on 2019/3/23.
//  Copyright © 2019 苗芃. All rights reserved.
//

//【选做内容】
// (1) 创建一棵二叉排序树；
// (2) 查找二叉排序树中一个指定结点；
// (3) 输出查找指定结点过程中所需比较的次数。

#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define TRUE 1
#define OVERFLOW -2
#define FALSE 0
#define ERROR 0
#define MAXSIZE 100

typedef bool Status;
typedef int KeyType;
typedef struct{
    KeyType key; // 用于存放编码
}ElemType;
typedef struct BiTNode{
    ElemType data; // 结点的数据域
    struct BiTNode *lchild, *rchild; // 左右孩子指针
}BiTNode, *BiTree;

int count=0;
BiTree SearchBST(BiTree T, KeyType key){
    if ((!T)||(key==T->data.key)){
        count++;
        printf("查找成功！\n");
        printf("查找次数：%d\n",count);
        printf("要查找的节点及其后续子节点为：\n");
        return T;
    }
    else if (key<T->data.key){
        count++;
        return SearchBST(T->lchild, key);
    }
    else{
        count++;
        return SearchBST(T->rchild, key);
    }
}


Status RSearchBST(BiTree T, KeyType key, BiTree f, BiTree &p){
    // 返回插入位置的二叉排序树查找算法
    if (!T) {p = f; return FALSE;} // 查找不成功
    else if (key == T->data.key){ p=T; return TRUE;} // 查找成功
    else if (key < T->data.key) return RSearchBST(T->lchild, key, T, p); // 在左子树中继续查找
    else return RSearchBST(T->rchild, key, T, p); // 在右子树中继续查找
}

Status InsertBST(BiTree &T, ElemType e){
    // 在二叉排序树中插入关键字值为key, 记录为e的新结点
    // 若成功，则返回TRUE；否则返回FAISE
    BiTree p,s;
    if (!RSearchBST(T, e.key, NULL, p)) {
        s=(BiTree)malloc(sizeof(BiTNode));
        s->data=e;
        s->lchild=s->rchild=NULL;
        if (!p) T=s;
        else if (e.key<p->data.key) p->lchild=s;
        else p->rchild=s;
        return TRUE;
    }
    else
        return FALSE;
}

Status CreateBST(BiTree &T, ElemType items[], int n){
    for (int i=0; i<n; i++) {
        InsertBST(T, items[i]); // 调用二叉排序树的插入算法
    }
    printf("创建完成！\n");
    return OK;
}

void PreRootTraverse(BiTree T){
    // 先序遍历
    if (T!=NULL) {
        printf("%d ",T->data.key);
        PreRootTraverse(T->lchild);
        PreRootTraverse(T->rchild);
    }
}

void InRootTraverse(BiTree T){
    // 中序遍历
    if (T!=NULL) {
        InRootTraverse(T->lchild);
        printf("%d ", T->data.key);
        InRootTraverse(T->rchild);
    }
}

Status IsSame(ElemType array[], int count){
    for (int i=0; i<count; i++) {
        int temp = array[i].key;
        for (int j=i+1; j<count; j++) {
            if (temp==array[j].key) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int levelOfNode(BiTree T, KeyType key){
    int n = 1;
    BiTree q;
    q=T;
    if (T==NULL)
        return 0; // 空树
    while (q) {
        if (key==q->data.key) {
            return n;
        }else{
            if (key<q->data.key)
                q=q->lchild;
            else
                q=q->rchild;
            n++;
        }
    }
    return -1; // 不存在，未查询到
}

void Menu(){
    printf("-----二叉排序树的操作-----\n");
    printf("请选择要进行的操作：(1-5)\n");
    printf("1. 生成二叉树\n");
    printf("2. 中序遍历二叉树\n");
    printf("3. 先序遍历二叉树\n");
    printf("4. 查找节点\n");
    printf("5. 退出进程\n");
    printf("-----------------------\n");
}

int main() {
    Menu();
    int operation;
    while (true) {
        BiTree T;
        printf("选择你的操作：");
        scanf("%d",&operation);
        switch (operation) {
            case 1:
                int count, n;
                printf("-----------------------\n");
                printf("创建开始，请输入元素个数:");
                scanf("%d", &count);
                printf("输入元素：\n");
                ElemType items[count];
                for (int i=0; i<count; i++) {
                    scanf("%d",&n);
                    items[i].key=n;
                }
                if (IsSame(items, count)) {
                    printf("输入的元素不允许重复！\n");
                    printf("-----------------------\n");
                    break;
                }
                //    ElemType items[7]={2,4,1,3,6,7,5};
                CreateBST(T, items, count);
                printf("-----------------------\n");
                break;
            case 2:
//                if (T==NULL) {
//                    printf("请先建立二叉排序树！\n");
//                    printf("-----------------------\n");
//                    break;
//                }
                printf("-----------------------\n");
                printf("中序遍历：\n");
                InRootTraverse(T);
                printf("\n");
                printf("-----------------------\n");
                break;
            case 3:
//                if (T==NULL) {
//                    printf("请先建立二叉排序树！\n");
//                    printf("-----------------------\n");
//                    break;
//                }
                printf("-----------------------\n");
                printf("先序遍历：\n");
                PreRootTraverse(T);
                printf("\n");
                printf("-----------------------\n");
                break;
            case 4:
//                if (T==NULL) {
//                    printf("请先建立二叉排序树！\n");
//                    printf("-----------------------\n");
//                    break;
//                }
                printf("-----------------------\n");
                printf("请输入要查找的节点：");
                int findnum;
                scanf("%d",&findnum);
                PreRootTraverse(SearchBST(T, findnum));
                printf("\n");
                printf("该节点位于第%d层。\n",levelOfNode(T, findnum));
                printf("-----------------------\n");
                break;
            case 5:
                printf("再会！\n");
                return 0;
            default:
                printf("请输入正确的操作码！\n");
                printf("-----------------------\n");
                printf("选择你的操作：");
                break;
        }
    }
}

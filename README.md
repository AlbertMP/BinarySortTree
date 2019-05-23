# BinarySortTree

## 数据结构描述
## 考虑到结点内容的可拓展性，定义一个ElemType结构体，暂时只存放了key值，未来可根据需求扩充。
```c++
typedef struct{
    KeyType key; // 用于存放数值
}ElemType;

typedef struct BiTNode{
    ElemType data; // 结点的数据域
    struct BiTNode *lchild, *rchild; // 左右孩子指针
}BiTNode, *BiTree;
```

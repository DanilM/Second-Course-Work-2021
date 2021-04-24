#ifndef NODE_H
#define NODE_H

#include<QList>
#include<QString>
#include<QDebug>

class Node
{
public:
    Node(QString name);
    Node(QString name, Node* parent);
    QList<Node*> getChildren();
    Node* getParent();
    QString getName();
    void addChild(Node* child);
    void setChildrenList(QList<Node*> children);
    void setParent(Node* parent);
    void showTree();
    int getTreeLevel();
    int getMaxChildren();
    ~Node();
private:
    QList<Node*> _children;
    Node* _parent;
    QString _name;
    const int maxChildren = 2;
    int getMaxSubLevel(int array[]);
};

#endif // NODE_H

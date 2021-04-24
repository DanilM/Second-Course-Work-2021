#include "node.h"

Node::Node(QString name)
{
    _parent = nullptr;
    _name = name;
}

Node::Node(QString name, Node *parent)
{
    _parent = parent;
    _name = name;
}

QList<Node*> Node::getChildren()
{
    return _children;
}

Node *Node::getParent()
{
    return _parent;
}

QString Node::getName()
{
    return _name;
}

void Node::addChild(Node *child)
{
    if(_children.size() < maxChildren)
        _children.append(child);
}

void Node::setChildrenList(QList<Node *> children)
{
    for(int i = _children.size(); i < maxChildren; i++)
    {
        _children.append(children.at(i));
    }
}

void Node::setParent(Node *parent)
{
    _parent = parent;
}

void Node::showTree()
{
    for(Node* child : _children)
    {
        qDebug() << child->getName() << " ";
        child->showTree();
    }
}

int Node::getTreeLevel()
{
    int level = 1;
    int subLevels[maxChildren];
    for(int i = 0; i < maxChildren; i++)
        subLevels[i] = 0;


    if(!_children.isEmpty())
    {
        int j = 0;
        for(Node* child : _children)
        {
            subLevels[j] = child->getTreeLevel();
            ++j;
        }
    }
    return level + getMaxSubLevel(subLevels);
}

int Node::getMaxChildren()
{
    return maxChildren;
}

int Node::getMaxSubLevel(int array[])
{
    int max = 0;
    for(int i = 0; i < maxChildren; i++)
    {
        if(array[i] > max)
            max = array[i];
    }
    return max;
}


Node::~Node()
{
    for(Node* item : _children)
    {
        delete item;
    }
}

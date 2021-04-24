#include "parser.h"

Parser::Parser(QString path)
{
    _file.setFileName(path);
    readFile();
}

bool Parser::readFile()
{
    if(!_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    _val = _file.readAll();
    _file.close();
    return true;
}

Node* Parser::setBinaryTree()
{
    if(!readFile())
        return nullptr;
    QJsonParseError error;
    QJsonDocument jsonValue = QJsonDocument::fromJson(_val.toUtf8(), &error);
    if(error.error == 0)
    {
        if(jsonValue.isObject())
        {
            root = new Node(jsonValue["_name"].toString());
            QJsonArray jsonArray = jsonValue["_children"].toArray();
            setChildren(root, jsonArray);
        }
        return root;
    }
    else
    {
        return nullptr;
    }
}

Parser::~Parser()
{
}

void Parser::setChildren(Node* parent, QJsonArray children)
{
    if(children.isEmpty())
        return;

    foreach(const QJsonValue & value, children)
    {
        if(value.isObject())
        {
            QJsonObject obj = value.toObject();
            QString name = obj["_name"].toString();
            Node* currentNode = new Node(name, parent);
            parent->addChild(currentNode);
            QJsonArray currentChildren = obj["_children"].toArray();
            setChildren(currentNode, currentChildren);
        }
    }

}

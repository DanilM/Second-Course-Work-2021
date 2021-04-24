#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include <QFile>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QDebug>

class Parser
{
public:
    Parser(QString path);
    Node* setBinaryTree();
    ~Parser();
private:
    QString _val;
    QFile _file;
    QJsonDocument jsonValue;
    Node* root;
    void setChildren(Node* parent, QJsonArray children);
    void setNode();
    bool readFile();
};

#endif // PARSER_H

#ifndef PAINTER_H
#define PAINTER_H

#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <cmath>
#include "node.h"

class Painter : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = 0);
    ~Painter();
    void setRoot(Node* root);

signals:

private slots:
    void slotAlarmTimer();
private:
    Node* _root;
    QGraphicsScene* scene;
    QGraphicsItemGroup* group;
    QTimer* timer;
    qreal blockWidth;
    qreal blockHeight;
    int maxChildrenTree;
    qreal widthSpaceBetweenNodes;
    qreal heightSpaceBetweenNodes;
    void resizeEvent(QResizeEvent *event);
    void showSubTree(qreal xCenter, qreal yTop, qreal levelWidth, qreal xStartSpace, Node *node);
    void printNode(qreal pointX1, qreal pointY1, qreal pointX2, qreal pointY2, QString nameNode);
    void printRelation(qreal pointX1, qreal pointY1, qreal pointX2, qreal pointY2);

    void deleteItemsFromGroup(QGraphicsItemGroup* group);
};

#endif // PAINTER_H

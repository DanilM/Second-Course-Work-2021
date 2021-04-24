#include "painter.h"



Painter::Painter(QWidget *parent) : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    scene = new QGraphicsScene();
    this->setScene(scene);

    group = new QGraphicsItemGroup();

    scene->addItem(group);

    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(slotAlarmTimer()));

    timer->start(50);

}

Painter::~Painter()
{
    delete _root;
}

void Painter::setRoot(Node *root)
{
    _root = root;
}

void Painter::slotAlarmTimer()
{
    this->deleteItemsFromGroup(group);

    int levelTree = _root->getTreeLevel();
    int width = this->width();
    int height = this->height();
    maxChildrenTree = _root->getMaxChildren();

    blockWidth = width/((pow(maxChildrenTree, levelTree)) + 1);
    blockHeight = height/(2*levelTree + 1);
    heightSpaceBetweenNodes = blockHeight;
    widthSpaceBetweenNodes = blockWidth;

    scene->setSceneRect(0,0,width,height);


    showSubTree(width/2, heightSpaceBetweenNodes,width, 0, _root);
}

void Painter::resizeEvent(QResizeEvent *event)
{
    timer->start(50);
    QGraphicsView::resizeEvent(event);
}

void Painter::showSubTree(qreal xCenter, qreal yTop, qreal levelWidth, qreal xStartSpace, Node *node)
{
    qreal pointX1 = xCenter - (blockWidth/2);
    qreal pointX2 = xCenter + (blockWidth/2);
    qreal pointY1 = yTop;
    qreal pointY2 = yTop + blockHeight;
    printNode(pointX1, pointY1, pointX2, pointY2, node->getName());
    if(node->getChildren().isEmpty())
        return;

    int i = 0;
    for(Node* child : node->getChildren())
    {
        qreal childXCenter = xStartSpace + ((levelWidth/maxChildrenTree)*(2*i+1))/2;
        qreal childYTop = yTop + heightSpaceBetweenNodes + blockHeight;
        showSubTree(childXCenter, childYTop, levelWidth/maxChildrenTree, childXCenter - (levelWidth/(2*maxChildrenTree)), child);
        printRelation(xCenter, pointY2, childXCenter, childYTop);
        ++i;
    }
}

void Painter::printNode(qreal pointX1, qreal pointY1, qreal pointX2, qreal pointY2, QString nameNode)
{
    QPen penBlack(Qt::black);
    QFont font;
    font.setPixelSize(2*(pointX2 - pointX1)/nameNode.length());
    font.setBold(false);
    font.setFamily("Calibri");
    QPainterPath path;
    path.addText(pointX1, pointY2 - (blockHeight/2), font,  nameNode);

    group->addToGroup(scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black)));
    group->addToGroup(scene->addLine(pointX1, pointY1,
                                     pointX2, pointY1,
                                     penBlack));
    group->addToGroup(scene->addLine(pointX1, pointY1,
                                     pointX1, pointY2,
                                     penBlack));
    group->addToGroup(scene->addLine(pointX2, pointY1,
                                     pointX2, pointY2,
                                     penBlack));
    group->addToGroup(scene->addLine(pointX1, pointY2,
                                     pointX2, pointY2,
                                     penBlack));
}

void Painter::printRelation(qreal pointX1, qreal pointY1, qreal pointX2, qreal pointY2)
{
    QPen penBlack(Qt::black);
    group->addToGroup(scene->addLine(pointX1, pointY1,
                                     pointX2, pointY2,
                                     penBlack));
}

void Painter::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect()))
    {
        if(item->group() == group)
        {
            delete item;
        }
    }
}

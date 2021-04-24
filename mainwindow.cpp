#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    painter = nullptr;
}

MainWindow::~MainWindow()
{
    delete painter;
    delete ui;
}


void MainWindow::on_action_triggered()
{
    if(painter != nullptr)
        delete painter;

    QString path = QFileDialog::getOpenFileName(0,QObject::tr("Укажите JSON файл"),QDir::homePath(), QObject::tr("JSON файл (*.json);;Все файлы (*.*)"));

    if(path.isEmpty())
        return;

    parser = new Parser(path);
    Node* root;
    root = parser->setBinaryTree();
    if(root != nullptr)
    {
        painter = new Painter();
        painter->setRoot(root);

        ui->gridLayout->addWidget(painter);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не удается открыть JSON файл");
    }
    delete parser;
}

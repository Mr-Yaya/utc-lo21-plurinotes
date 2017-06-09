#include "main.h"
#include "v_mainwindow.h"
#include "ui_v_mainwindow.h"
#include "ui_v_multiplenotes.h"

V_Mainwindow::V_Mainwindow(QWidget *parent, C_Mainwindow*c) :
    QMainWindow(parent),
    ui(new Ui::V_Mainwindow)
{
    ui->setupUi(this);
    controller = c;

    labelActiveNotes = new QLabel("Active Notes");
    labelActiveNotes->setFixedSize(200,20);
    labelActiveNotes->setAlignment(Qt::AlignCenter);

    labelArchivedNotes = new QLabel("Archived Notes");
    labelArchivedNotes->setFixedSize(200,20);
    labelArchivedNotes->setAlignment(Qt::AlignCenter);

    labelTasks = new QLabel("Tasks");
    labelTasks->setFixedSize(200,20);
    labelTasks->setAlignment(Qt::AlignCenter);

    activeNotes = new V_Multiplenotes;
    tasks = new V_Multiplenotes;
    archivedNotes = new V_Multiplenotes;

    centralLayout = new QHBoxLayout;
    leftWidget = new QWidget;
    leftLayout = new QVBoxLayout;

    leftLayout->addWidget(labelActiveNotes);
    leftLayout->addWidget(activeNotes);
    leftLayout->addWidget(labelTasks);
    leftLayout->addWidget(tasks);
    leftLayout->addWidget(labelArchivedNotes);
    leftLayout->addWidget(archivedNotes);

    leftWidget->setLayout(leftLayout);
    centralLayout->addWidget(leftWidget);
    centralWidget()->setLayout(centralLayout);
}

void V_Mainwindow::openNewArticle() {
    articleForm = new V_ArticleForm(0,this);
    articleForm->show();
}

V_Mainwindow::~V_Mainwindow()
{
    delete ui;
}
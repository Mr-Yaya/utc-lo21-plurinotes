/********************************************************************************
** Form generated from reading UI file 'v_multiplerelation.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_V_MULTIPLERELATION_H
#define UI_V_MULTIPLERELATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_v_multiplerelation
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelDescendants;
    QTreeWidget *treeDescendant;
    QLabel *labelAscendants;
    QTreeWidget *treeAscendant;

    void setupUi(QWidget *v_multiplerelation)
    {
        if (v_multiplerelation->objectName().isEmpty())
            v_multiplerelation->setObjectName(QString::fromUtf8("v_multiplerelation"));
        v_multiplerelation->resize(210, 560);
        verticalLayoutWidget = new QWidget(v_multiplerelation);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 211, 561));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelDescendants = new QLabel(verticalLayoutWidget);
        labelDescendants->setObjectName(QString::fromUtf8("labelDescendants"));
        labelDescendants->setMinimumSize(QSize(0, 20));
        labelDescendants->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(labelDescendants);

        treeDescendant = new QTreeWidget(verticalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeDescendant->setHeaderItem(__qtreewidgetitem);
        treeDescendant->setObjectName(QString::fromUtf8("treeDescendant"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeDescendant->sizePolicy().hasHeightForWidth());
        treeDescendant->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(treeDescendant);

        labelAscendants = new QLabel(verticalLayoutWidget);
        labelAscendants->setObjectName(QString::fromUtf8("labelAscendants"));
        labelAscendants->setMinimumSize(QSize(0, 20));
        labelAscendants->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(labelAscendants);

        treeAscendant = new QTreeWidget(verticalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        treeAscendant->setHeaderItem(__qtreewidgetitem1);
        treeAscendant->setObjectName(QString::fromUtf8("treeAscendant"));
        sizePolicy.setHeightForWidth(treeAscendant->sizePolicy().hasHeightForWidth());
        treeAscendant->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(treeAscendant);


        retranslateUi(v_multiplerelation);

        QMetaObject::connectSlotsByName(v_multiplerelation);
    } // setupUi

    void retranslateUi(QWidget *v_multiplerelation)
    {
        v_multiplerelation->setWindowTitle(QApplication::translate("v_multiplerelation", "Form", 0, QApplication::UnicodeUTF8));
        labelDescendants->setText(QApplication::translate("v_multiplerelation", "Descendants", 0, QApplication::UnicodeUTF8));
        labelAscendants->setText(QApplication::translate("v_multiplerelation", "Ascendants", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class v_multiplerelation: public Ui_v_multiplerelation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_V_MULTIPLERELATION_H

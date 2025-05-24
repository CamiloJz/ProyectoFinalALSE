/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutTop;
    QLineEdit *searchLineEdit;
    QSpinBox *lowStockSpinBox;
    QLabel *lowStockLabel;
    QPushButton *checkLowStockButton;
    QTableView *componentsTableView;
    QHBoxLayout *horizontalLayoutBottom;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *exportCSVButton;
    QPushButton *exportPDFButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayoutTop = new QHBoxLayout();
        horizontalLayoutTop->setObjectName(QString::fromUtf8("horizontalLayoutTop"));
        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        horizontalLayoutTop->addWidget(searchLineEdit);

        lowStockSpinBox = new QSpinBox(centralwidget);
        lowStockSpinBox->setObjectName(QString::fromUtf8("lowStockSpinBox"));
        lowStockSpinBox->setMinimum(0);
        lowStockSpinBox->setValue(5);

        horizontalLayoutTop->addWidget(lowStockSpinBox);

        lowStockLabel = new QLabel(centralwidget);
        lowStockLabel->setObjectName(QString::fromUtf8("lowStockLabel"));

        horizontalLayoutTop->addWidget(lowStockLabel);

        checkLowStockButton = new QPushButton(centralwidget);
        checkLowStockButton->setObjectName(QString::fromUtf8("checkLowStockButton"));

        horizontalLayoutTop->addWidget(checkLowStockButton);


        verticalLayout->addLayout(horizontalLayoutTop);

        componentsTableView = new QTableView(centralwidget);
        componentsTableView->setObjectName(QString::fromUtf8("componentsTableView"));

        verticalLayout->addWidget(componentsTableView);

        horizontalLayoutBottom = new QHBoxLayout();
        horizontalLayoutBottom->setObjectName(QString::fromUtf8("horizontalLayoutBottom"));
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayoutBottom->addWidget(addButton);

        editButton = new QPushButton(centralwidget);
        editButton->setObjectName(QString::fromUtf8("editButton"));

        horizontalLayoutBottom->addWidget(editButton);

        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        horizontalLayoutBottom->addWidget(deleteButton);

        exportCSVButton = new QPushButton(centralwidget);
        exportCSVButton->setObjectName(QString::fromUtf8("exportCSVButton"));

        horizontalLayoutBottom->addWidget(exportCSVButton);

        exportPDFButton = new QPushButton(centralwidget);
        exportPDFButton->setObjectName(QString::fromUtf8("exportPDFButton"));

        horizontalLayoutBottom->addWidget(exportPDFButton);


        verticalLayout->addLayout(horizontalLayoutBottom);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Buscar...", nullptr));
        lowStockLabel->setText(QCoreApplication::translate("MainWindow", "Alerta Stock <=", nullptr));
        checkLowStockButton->setText(QCoreApplication::translate("MainWindow", "Ver Baja Existencia", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "Agregar", nullptr));
        editButton->setText(QCoreApplication::translate("MainWindow", "Editar", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Eliminar", nullptr));
        exportCSVButton->setText(QCoreApplication::translate("MainWindow", "Exportar CSV", nullptr));
        exportPDFButton->setText(QCoreApplication::translate("MainWindow", "Exportar PDF", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

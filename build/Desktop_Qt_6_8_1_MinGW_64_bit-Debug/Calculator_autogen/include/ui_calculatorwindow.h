/********************************************************************************
** Form generated from reading UI file 'calculatorwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATORWINDOW_H
#define UI_CALCULATORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalculatorWindow
{
public:

    void setupUi(QWidget *CalculatorWindow)
    {
        if (CalculatorWindow->objectName().isEmpty())
            CalculatorWindow->setObjectName("CalculatorWindow");
        CalculatorWindow->resize(400, 300);

        retranslateUi(CalculatorWindow);

        QMetaObject::connectSlotsByName(CalculatorWindow);
    } // setupUi

    void retranslateUi(QWidget *CalculatorWindow)
    {
        CalculatorWindow->setWindowTitle(QCoreApplication::translate("CalculatorWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalculatorWindow: public Ui_CalculatorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATORWINDOW_H

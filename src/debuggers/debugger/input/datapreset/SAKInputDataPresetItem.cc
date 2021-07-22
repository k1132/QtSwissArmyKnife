﻿/******************************************************************************
 * Copyright 2018-2021 Qter(qsaker@qq.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#include <QMenu>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>

#include "SAKDebuggerInput.hh"
#include "SAKCommonCrcInterface.hh"
#include "SAKCommonDataStructure.hh"
#include "SAKInputDataPresetItem.hh"
#include "SAKCommonDataStructure.hh"

#include "ui_SAKInputDataPresetItem.h"

SAKInputDataPresetItem::SAKInputDataPresetItem(QWidget *parent)
    :QWidget(parent)
    ,mItemId(QDateTime::currentMSecsSinceEpoch())
    ,mUi(new Ui::SAKInputDataPresetItem)
{
    initializingItem();
}

SAKInputDataPresetItem::SAKInputDataPresetItem(
        SAKStructDataPresetItemContext context,
        QWidget *parent)
    :QWidget(parent)
    ,mItemId(context.id)
    ,mUi(new Ui::SAKInputDataPresetItem)
{
    initializingItem();
    mUi->textFormatComboBox->setCurrentIndex(context.format);
    mUi->descriptionLineEdit->setText(context.description);
    mUi->dataLineEdit->setText(context.text);
}

SAKInputDataPresetItem::~SAKInputDataPresetItem()
{
    delete mUi;
}

quint64 SAKInputDataPresetItem::itemID()
{
    return mItemId;
}

QString SAKInputDataPresetItem::itemDescription()
{
    return mUi->descriptionLineEdit->text();
}

QString SAKInputDataPresetItem::itemText()
{
    return mUi->dataLineEdit->text();
}

int SAKInputDataPresetItem::itemTextFromat()
{
    return mUi->textFormatComboBox->currentData().toInt();
}

void SAKInputDataPresetItem::initializingItem()
{
    mUi->setupUi(this);
    SAKCommonDataStructure::setComboBoxTextInputFormat(
                mUi->textFormatComboBox);
    setLineEditTextFormat(mUi->dataLineEdit,
                          mUi->textFormatComboBox->currentData().toInt());



    connect(mUi->textFormatComboBox, &QComboBox::currentTextChanged,
            this, [=](const QString &text){
        Q_UNUSED(text);
        mUi->dataLineEdit->clear();
        int format = mUi->textFormatComboBox->currentData().toInt();
        emit formatChanged(mItemId, format);

        setLineEditTextFormat(mUi->dataLineEdit,
                              mUi->textFormatComboBox->currentData().toInt());
    });


    connect(mUi->descriptionLineEdit, &QLineEdit::textChanged,
            this, [=](const QString &text){
        emit descriptionChanged(mItemId, text);
    });


    connect(mUi->dataLineEdit, &QLineEdit::textChanged,
            this, [=](){
        QString text = mUi->dataLineEdit->text();
        emit textChanged(mItemId, text);
    });
}

void SAKInputDataPresetItem::setLineEditTextFormat(QLineEdit *lineEdit,
                                                   int format)
{
    auto cookedFormat =
            static_cast<SAKCommonDataStructure::SAKEnumTextInputFormat>(
                format
                );
    SAKCommonDataStructure::setLineEditTextFormat(lineEdit,
                                                  cookedFormat);
}

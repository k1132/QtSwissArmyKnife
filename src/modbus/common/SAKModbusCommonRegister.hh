﻿/*
 * Copyright 2020 Qter(qsaker@qq.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 */
#ifndef SAKMODBUSCOMMONREGISTER_HH
#define SAKMODBUSCOMMONREGISTER_HH

#include <QWidget>
#include <QModbusDataUnit>

namespace Ui {
    class SAKModbusCommonRegister;
}

class SAKModbusCommonRegister : public QWidget
{
    Q_OBJECT
public:
    explicit SAKModbusCommonRegister(QModbusDataUnit::RegisterType type, quint16 address, quint16 value, QWidget *parent = Q_NULLPTR);
    ~SAKModbusCommonRegister();

    QModbusDataUnit::RegisterType type();
    quint16 address();
    quint16 value();
private:
    QModbusDataUnit::RegisterType mType;
    quint16 mAddress;
    quint16 mValue;
private:
    Ui::SAKModbusCommonRegister *ui;
};

#endif // SAKMODBUSCOMMONREGISTER_HH

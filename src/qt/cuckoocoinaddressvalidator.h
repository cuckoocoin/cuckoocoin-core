// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2017-2018 The Cuckoocoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CUCKOOCOIN_QT_CUCKOOCOINADDRESSVALIDATOR_H
#define CUCKOOCOIN_QT_CUCKOOCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class CuckoocoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit CuckoocoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Cuckoocoin address widget validator, checks for a valid cuckoocoin address.
 */
class CuckoocoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit CuckoocoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // CUCKOOCOIN_QT_CUCKOOCOINADDRESSVALIDATOR_H

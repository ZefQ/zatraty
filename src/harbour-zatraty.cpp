/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QGuiApplication>
#include <QDebug>
#include <QQuickView>
#include <QDir>
#include <QFile>
#include <QTranslator>
#include <QLocale>
#include <QtQml>

#include "database.h"
#include "category.h"
#include "expense.h"
#include "settings.h"
#include "models/backuplistmodel.h"
#include "models/categorylistmodel.h"
#include "models/categorymodel.h"
#include "models/datelistmodel.h"
#include "models/expenselistmodel.h"
#include "models/expensemodel.h"

void qmlRegisterTypes()
{
    qmlRegisterSingletonType<DataBase>("harbour.zatraty", 1, 0, "DataBase", &DataBase::qinstance);
    qmlRegisterSingletonType<Settings>("harbour.zatraty", 1, 0, "Settings", &Settings::qinstance);

    qmlRegisterType<Category>("harbour.zatraty", 1, 0, "Category");
    qmlRegisterType<Expense>("harbour.zatraty", 1, 0, "Expense");

    qmlRegisterType<BackupListModel>("harbour.zatraty", 1, 0, "BackupListModel");
    qmlRegisterType<CategoryListModel>("harbour.zatraty", 1, 0, "CategoryListModel");
    qmlRegisterType<ExpenseListModel>("harbour.zatraty", 1, 0, "ExpenseListModel");
    qmlRegisterType<DateListModel>("harbour.zatraty", 1, 0, "DateListModel");
}

int main(int argc, char *argv[])
{
    QGuiApplication *app = SailfishApp::application(argc, argv);
    app->setApplicationName("zatraty");
    app->setApplicationVersion("0.5");

    QString locale = QLocale::system().name();
    qDebug() << "detected locale is " << locale;
    QTranslator translator;
    /* the ":/" is a special directory Qt uses to
    * distinguish resources;
    * NB this will look for a filename matching locale + ".qm";
    * if that's not found, it will truncate the locale to
    * the first two characters (e.g. "en_GB" to "en") and look
    * for that + ".qm"; if not found, it will look for a
    * qml-translations.qm file; if not found, no translation is done
    */
    if (translator.load("harbour-zatraty." + locale, SailfishApp::pathTo("translations").path()))
        app->installTranslator(&translator);

    qmlRegisterTypes();

    QQuickView* viewer = SailfishApp::createView();
    viewer->rootContext()->setContextProperty("CategoryModel", &CategoryModel::instance());
    viewer->rootContext()->setContextProperty("ExpenseModel", &ExpenseModel::instance());

    viewer->setSource(SailfishApp::pathTo("qml/harbour-zatraty.qml"));
    viewer->show();

    return app->exec();
}

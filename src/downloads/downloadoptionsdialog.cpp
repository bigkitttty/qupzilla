/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2011  nowrep
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "downloadoptionsdialog.h"
#include "ui_downloadoptionsdialog.h"

DownloadOptionsDialog::DownloadOptionsDialog(const QString &fileName, const QPixmap &fileIcon, const QString &mimeType, const QUrl &url, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DownloadOptionsDialog)
{
    ui->setupUi(this);
    ui->fileName->setText("<b>"+fileName+"</b>");
    ui->fileIcon->setPixmap(fileIcon);
    ui->fileType->setText(mimeType);
    ui->fromServer->setText(url.host());
    setWindowTitle(tr("Opening %1").arg(fileName));

    setFixedHeight(sizeHint().height());

    connect(this, SIGNAL(finished(int)), this, SLOT(emitDialogFinished(int)));
}

void DownloadOptionsDialog::emitDialogFinished(int status)
{
    if (status != 0) {
        if (ui->radioOpen->isChecked())
            status =  1;
        else if (ui->radioSave->isChecked())
            status =  2;
    }
    emit dialogFinished(status);
}

DownloadOptionsDialog::~DownloadOptionsDialog()
{
    delete ui;
}

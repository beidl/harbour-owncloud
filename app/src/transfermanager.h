#ifndef TRANSFERMANAGER_H
#define TRANSFERMANAGER_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QStandardPaths>

#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>
#include <sys/stat.h>

#include "owncloudbrowser.h"
#include "../common/src/transferentry.h"
#include "entryinfo.h"

class TransferManager : public QObject
{
    Q_OBJECT
public:
    TransferManager(QObject *parent = 0, OwnCloudBrowser *browser = 0);

    Q_PROPERTY(bool transfering READ isTransfering NOTIFY transferingChanged)

    Q_INVOKABLE TransferEntry* enqueueDownload(EntryInfo* entry, bool open);
    Q_INVOKABLE void enqueueUpload(QString localPath, QString remotePath);
    Q_INVOKABLE bool isNotEnqueued(EntryInfo* entry);
    Q_INVOKABLE QVariantList getTransfers();

private:
    OwnCloudBrowser *browser;
    QQueue<TransferEntry *> downloadQueue;
    QQueue<TransferEntry *> uploadQueue;
    QMutex downloadMutex;
    QMutex uploadMutex;

    QString destinationFromMIME(QString mime);

    bool isTransfering();

signals:
    void transferAdded();
    void transferingChanged();
    void downloadComplete(TransferEntry* entry);
    void downloadFailed(TransferEntry* entry);
    void uploadComplete(TransferEntry* entry, QString remotePath); // Retain remotePath for QML magic
    void uploadFailed(TransferEntry* entry);
    void localMtimeFailed(int status);
    void remoteMtimeFailed(int status);

public slots:
    void handleDownloadCompleted();
    void handleUploadCompleted();
    void setLocalLastModified(TransferEntry* entry);
    void setRemoteLastModified(TransferEntry* entry, QString remotePath);
    void setRemoteMtimeFinished(QNetworkReply* networkReply);
};

#endif // TRANSFERMANAGER_H

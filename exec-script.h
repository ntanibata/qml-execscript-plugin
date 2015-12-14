#pragma once

#include <QtCore/qobject.h>
#include <QtCore/qprocess.h>
#include <QtCore/qdebug.h>
#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>

class ExecScript : public QObject
{
Q_OBJECT

public:
    ExecScript() : m_exec(new QProcess())
    {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        m_exec->setProcessEnvironment(env);

        connect(m_exec, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            [](int exitCode) { qDebug() << "ExitCode:" << exitCode; });
    }

    ~ExecScript() { delete m_exec; }

    Q_INVOKABLE void execute(const QString file)
    {
        qDebug() << __func__ << file;

        m_exec->start(file);
        bool ret = m_exec->waitForFinished();
        if (!ret)
            qDebug() << "timeout";
    }

private:
    QProcess *m_exec;
};

class QmlExecScriptPlugin : public QQmlExtensionPlugin
{
Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.automotive.qmlplugin")

public:
        void registerTypes(const char *uri)
        {
            Q_ASSERT(uri == QLatin1String("execScript"));

            qmlRegisterType<ExecScript>(uri, 1, 0, "ExecScript");
        }
};

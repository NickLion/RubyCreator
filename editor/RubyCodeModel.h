#ifndef Ruby_CodeModel_h
#define Ruby_CodeModel_h

#include <QDateTime>
#include <QMetaType>
#include <QIODevice>
#include <QObject>
#include <QHash>

#include "RubySymbol.h"

namespace Ruby {

class CodeModel : QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(CodeModel)

public:
    CodeModel();
    ~CodeModel();

    static CodeModel *instance();
    void removeSymbolsFrom(const QString &file);
    void addFile(const QString &file);
    // pass a QIODevice because the file may not be saved on file system.
    void updateFile(const QString &fileName, const QString &contents);

    QList<Symbol> methodsIn(const QString &file) const;
    QSet<QString> identifiersIn(const QString &file) const;
    QSet<QString> constantsIn(const QString &file) const;
    QSet<QString> symbolsIn(const QString &file) const;
    QList<Symbol> allMethods() const;
    QList<Symbol> allClasses() const;
    QList<Symbol> allMethodsNamed(const QString &name) const;
    QList<Symbol> allClassesAndConstantsNamed(const QString &name) const;

private:

    class Data;
    QHash<QString, Data*> m_model;
};

}

#endif

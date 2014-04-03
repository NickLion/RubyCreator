#include "RubyCodeModel.h"

#include <QElapsedTimer>
#include <QFile>
#include <QDebug>

namespace RubyEditor {

RubySymbol::RubySymbol(const QString& name, int line, int column)
    : name(name), line(line), column(column)
{
}

RubyCodeModel::RubyCodeModel()
{
    RUBY_INIT_STACK;
    ruby_init();
    ruby_init_loadpath();
    const char*  options[]  =  { "", "/home/hugo/src/rubyeditor/RubyParser.rb", 0 };
    ruby_exec_node(ruby_options(2, const_cast<char**>(options)));

    m_getMethodDeclarations = rb_intern("get_method_declarations");
    Q_ASSERT(m_getMethodDeclarations);
}

RubyCodeModel::~RubyCodeModel()
{
    ruby_cleanup(0);
}

RubyCodeModel* RubyCodeModel::instance()
{
    static RubyCodeModel model;
    return &model;
}

void RubyCodeModel::updateModel(const QString& file)
{
    QElapsedTimer timer;
    timer.start();

    QFile f(file);
    if (!f.open(QFile::ReadOnly))
        return;

    QByteArray data = f.readAll();
    VALUE input = rb_str_new(data.data(), data.length());
    VALUE result = rb_funcall(rb_cObject, m_getMethodDeclarations, 1, input);
    char* resultData = StringValuePtr(result);

    QList<RubySymbol> symbols;

    QByteArray foo(resultData);
    foreach (QByteArray line, foo.split('\n')) {
        if (line.isEmpty())
            continue;
        QList<QByteArray> d = line.split(' ');
        symbols << RubySymbol(d[2], atoi(d[0]), atoi(d[1]));
    }
    m_symbols[file] = symbols;
    qDebug() << "Code model updated in" << timer.elapsed() << "ms";
}

QList<RubySymbol> RubyCodeModel::methodsIn(const QString& file)
{
    return m_symbols[file];
}

}

#include "RubyCodeModel.moc"

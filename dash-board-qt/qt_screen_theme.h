#ifndef QT_SCREEN_THEME_H
#define QT_SCREEN_THEME_H

#include <QObject>
#include <QQmlEngine>
#include "user.h"

class QtScreenTheme : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QString theme READ get_theme WRITE set_theme NOTIFY themeChanged FINAL)
    Q_PROPERTY(QString name READ get_name NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString id READ get_id NOTIFY idChanged FINAL)

public:
    explicit QtScreenTheme(QObject *parent = nullptr);
    // Singletons should not be cloneable.
    QtScreenTheme(QtScreenTheme &other) = delete;
    // Singletons should not be assignable.
    void operator=(const QtScreenTheme &) = delete;

    // get the only instance created of QtScreenTheme
    static QtScreenTheme *GetInstance(QObject *parent)
    {
        if(_this == nullptr)
        {
            _this = new QtScreenTheme(parent);
        }
        return _this;
    }

    // connect functions
    QString get_theme();
    QString get_name();
    QString get_id();

    // signal functions
    Q_INVOKABLE void set_theme(QString);

    // set functions
    void set_user(User *user);

signals:
    void themeChanged(); // theme changed
    void nameChanged();
    void idChanged();

protected:
    static QtScreenTheme* _this;
    User* _user;

private:
    QString _theme;
    QString _name;
    QString _id;
};


#endif // QT_SCREEN_THEME_H

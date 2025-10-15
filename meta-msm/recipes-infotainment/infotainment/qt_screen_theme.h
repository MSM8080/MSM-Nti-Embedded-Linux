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

    // signal & connect functions
    QString get_theme();
    Q_INVOKABLE void set_theme(QString);


    // set functions
    void set_user(User *user);

signals:
    void themeChanged(); // theme changed
protected:
    static QtScreenTheme* _this;
    User* _user;

private:
    QString _theme;
    QString _id;
    QString _name;
};


#endif // QT_SCREEN_THEME_H

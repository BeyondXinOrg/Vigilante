#ifndef MACRO_H
#define MACRO_H

// 通用宏处理

#define QDATEYEARS QDate::currentDate().toString("yyyy").toInt()
#define QDATESTRING QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss")
#define QDATESecsSinceEpoch QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch())

// get/set
#define QUICK_GETSET(name, type)              \
    virtual void Set_##name(const type& _arg) \
    {                                         \
        this->name = _arg;                    \
    }                                         \
    virtual type Get_##name() const           \
    {                                         \
        return this->name;                    \
    }

#define QUICK_INITIAL_VAR(name, type)         \
public:                                       \
    virtual void Set_##name(const type& _arg) \
    {                                         \
        this->name = _arg;                    \
    }                                         \
    virtual type Get_##name() const           \
    {                                         \
        return this->name;                    \
    }                                         \
                                              \
private:                                      \
    type name;

#define QUICK_GETSET_OBJECT(name, type) \
    virtual type* Get_##name() const    \
    {                                   \
        return this->name;              \
    }                                   \
    virtual void Set_##name(type* _arg) \
    {                                   \
        this->name = _arg;              \
    }

#endif // MACRO_H

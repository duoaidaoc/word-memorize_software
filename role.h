#ifndef ROLE_H
#define ROLE_H

#include "table.h"
#include <QString>
#include <QVariant>

namespace db {
class Role : public Table {
private:
    qint64 id_;
    QString name_;
    QString password_;
    QString profile_photo_url_;

public:
    explicit Role(Database& db) : Table(db) {}
    virtual QVariant registerRole() = 0;
    virtual void cancelRole() = 0;
    virtual void displayInfo() = 0;

    void SetId(const qint64& id) { id_ = id; }
    void SetName(const QString& name) { name_ = name; }
    void SetPassword(const QString& password) { password_ = password; }
    void SetProfilePhotoUrl(const QString& url) { profile_photo_url_ = url; }

    const qint64 GetId() const { return id_; }
    const QString GetName() const { return name_; }
    const QString GetPassword() const { return password_; }
    const QString GetProfilePhotoUrl() const { return profile_photo_url_; }
};

class Teacher : public Role {

private:
    QList<qint64> class_ids_;                  // 老师的班级管理，多值属性
    const QLatin1String insertTeacherTable = QLatin1String(R"(
        insert into teachers(id, name, password, profile_photo_url) values(?, ?, ?, ?)
    )");
    const QLatin1String deleteTeacherRole = QLatin1String(R"(
        DELETE FROM teachers WHERE id = ?
    )");
    const QLatin1String dispalyTeacherRole = QLatin1String(R"(
        SELECT * FROM teachers WHERE id = ?
    )");

    // 教师语义操作
    static QVariant addTeacher(QSqlQuery &q, const qint64 &id, const QString &name, const QString &password, const QString &profile_photo_url);
    static bool deleteTeacher(QSqlQuery &q, const qint64 &id);
    static void displayTeacher(QSqlQuery &q, const qint64 &id);

public:
    explicit Teacher(Database& db) : Role(db) {}

    // 增删改查
    QVariant registerRole() override;
    void cancelRole() override;
    void displayInfo() override;

    // 扩展操作
    QVariant createClass();
    QVariant deleteClass();
};

class Student : public Role {
private:
    QList<qint64> class_ids_;                  // 学生添加班级。
    const QLatin1String insertStudentTable = QLatin1String(R"(
        insert into students(id, name, password, profile_photo_url) values(?, ?, ?, ?)
    )");
    const QLatin1String deleteStudentRole = QLatin1String(R"(
        DELETE FROM students WHERE id = ?
    )");
    const QLatin1String dispalyStduentRole = QLatin1String(R"(
        SELECT * FROM students WHERE id = ?
    )");

    // 学生语义操作
    static QVariant addStudent(QSqlQuery &q, const qint64 &id, const QString &name, const QString &password, const QString &profile_photo_url);
    static bool deleteStudent(QSqlQuery &q, const qint64 &id);
    static void displayStudent(QSqlQuery &q, const qint64 &id);

public:
    explicit Student(Database& db) : Role(db) {}

    // 增删改查
    QVariant registerRole() override;
    void cancelRole() override;
    void displayInfo() override;

    // 扩展操作
    QVariant joinClass();
    QVariant leaveClass();
};
} // end db

#endif // ROLE_H


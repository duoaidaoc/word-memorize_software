
#ifndef CLASS_FRAME_H
  #define CLASS_FRAME_H

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include "word.h"

class class_frame : public QFrame
{
  Q_OBJECT
public:
  class_frame(QWidget* parent = nullptr);
  ~class_frame();
  void setclass(CClass &_cls);
  void add_connect(QMetaObject::Connection con);
protected:
  void mousePressEvent(QMouseEvent* event)override;
private:
  CClass cls;
  QLabel* classinfo;
  QHBoxLayout* hb;
  std::vector<QMetaObject::Connection>connections;
signals:
  void set_display_content(CClass _cls);
};

#endif // CLASS_FRAME_H
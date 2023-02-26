#include "BufferSize.h"

namespace shshare::widgets::settings {

BufferSize::BufferSize(const QString& title, quint64 value, QWidget *parent) :
    Number{title, value, parent}
{
    setMinimum(8);
    setMaximum(1024);
    setSuffix("Kb");
}

} //namespace shshare::widgets::settings


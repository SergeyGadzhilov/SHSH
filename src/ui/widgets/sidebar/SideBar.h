#ifndef WIDGETS_SIDEBAR_H
#define WIDGETS_SIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include "Button.h"
#include "ui/widgets/StyledWidget.h"
#include "ui/pages/Pages.h"

namespace shshare::widgets {

class SideBar : public StyledWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);

signals:
    void openSettings();
    void openPage(shshare::pages::Page page);
    void showAboutQt();

private:
    void addLogo();
    void addSpacer();
    void resetAllButtons();
    void addButton(sidebar::Button& button, pages::Page page);
    void activateButton(sidebar::Button& button, pages::Page page);

    sidebar::Button m_about;
    sidebar::Button m_uploads;
    sidebar::Button m_settings;
    sidebar::Button m_downloads;

    QVBoxLayout m_layout;
};

} //namespace shshare::widgets

#endif // WIDGETS_SIDEBAR_H

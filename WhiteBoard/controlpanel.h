#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

/*================= Includes ==================*/
#include <QMainWindow>
#include <QPropertyAnimation>

#include "subpanel.h"

/*=============================================*/

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QMainWindow
{
    Q_OBJECT

public:

/*------------------ 构造/析构函数 ----------------------*/
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();
/*-----------------------------------------------------*/

/*------------------ 初始化函数 ----------------------*/
    void initButtonStytle();    //初始化按钮样式
/*-----------------------------------------------------*/

protected:

/*------------------ 鼠标事件 ----------------------*/
    void mouseMoveEvent(QMouseEvent *event);
/*-----------------------------------------------------*/

/*------------------ 事件过滤器 ----------------------*/
    void buttonInstallFilter();     //按钮安装事件过滤器
    bool eventFilter(QObject *obj, QEvent *event); //事件过滤器
/*-----------------------------------------------------*/

private slots:

/*------------------ 槽函数 ----------------------*/
    void showSubPanel();        //调出子控制面板
    void setIfThrough();        //鼠标穿透
    void closeWindow();         //关闭
    void cleanScreen();         //清屏
    void withdrawOperation();   //撤回
/*-----------------------------------------------------*/

private:
    Ui::ControlPanel *ui;

    /*
     * 标记鼠标是否穿透画板
     */
    bool m_ifThrough;

    /*
     * 标记子控制面板是否显示
     */
    bool m_ifSubPanelShow;


    /*
     * 子控制面板对象
     */
    SubPanel subPanel;
};

#endif // CONTROLPANEL_H

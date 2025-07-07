
import QtQuick
import QtQuick.Controls
import QtQuick.Window  // 导入 Window 模块

ApplicationWindow {
    id: root
    visible: true
    width: 1280
    height: 720
    title: "三国杀"

    // 添加最小尺寸限制
    minimumWidth: 800
    minimumHeight: 600

    // 添加全屏切换支持
    Shortcut {
        sequence: "F11"
        onActivated: {
            if (root.visibility === Window.FullScreen) {
                root.visibility = Window.Windowed
            } else {
                root.visibility = Window.FullScreen
            }
        }
    }

    // 全局组件定义
    Component {
        id: mainMenuScreen
        MainMenu {
            onStartGame: stackView.push(gameScreen)
            onShowSettings: stackView.push(settingsScreen)
        }
    }

    Component {
        id: gameScreen
        GameScreen {
            // 确保游戏屏幕填充整个可用空间
            anchors.fill: parent
            onBackToMenu: stackView.pop()
        }
    }

    Component {
        id: settingsScreen
        SettingsScreen {
            onBackToMenu: stackView.pop()
        }
    }

    // 主界面栈
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: mainMenuScreen

        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 200
            }
        }
        popExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 200
            }
        }
    }

    // 窗口大小变化时打印调试信息
    onWidthChanged: console.log("窗口宽度变化:", width)
    onHeightChanged: console.log("窗口高度变化:", height)
}

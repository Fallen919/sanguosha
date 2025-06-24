import QtQuick
import QtQuick.Controls
ApplicationWindow {
    id: root
    visible: true
    width: 1280
    height: 720
    title: "三国杀"

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
}

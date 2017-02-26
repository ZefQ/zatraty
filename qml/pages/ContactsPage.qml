import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.zatraty 1.0

Page {
    id: contactsPage

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column {
            id: column
            width: contactsPage.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("About")
            }

            Label {
                text: Settings.appName
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeExtraLarge*1.5
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                source: "/usr/share/icons/hicolor/86x86/apps/harbour-zatraty.png"
                width: parent.width *0.2
                height: width
            }

            Label {
                text: qsTr("Version %1").arg(Settings.appVersion)
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryHighlightColor
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Label {
                text: qsTr("A simple app to manage your money. This software is open source:")
                color: Theme.secondaryHighlightColor
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.WordWrap
                horizontalAlignment: TextInput.AlignHCenter
                width: parent.width*0.8
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "<a href=\"https://github.com/ckazzku/zatraty/\">Github</a>";
                onLinkActivated: Qt.openUrlExternally(link)
            }
        }
    }
}

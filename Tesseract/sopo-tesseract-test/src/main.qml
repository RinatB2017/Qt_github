import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import org.tal.tesser 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Tesseract test")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("Edit")
            MenuItem {
                text: qsTr("Select all")
                onTriggered: textResult.selectAll();
            }
            MenuItem {
                text: qsTr("Copy")
                onTriggered: textResult.copy();
            }
        }
    }

    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            ProgressBar {
                width: 200
                indeterminate: ocr.running
            }
            Label { text: ocr.running ? "OCR is running, please wait..." : "" }
        }
    }

    TesseractOCR {
        id: ocr
        onTextAvailable: {
            console.debug("OCR Done")
            textResult.text=ocr.getText();
        }
    }

    ItemSelectionModel {
        id: sel
        model: fileSystemModel
    }

    RowLayout {
        anchors.fill: parent;
        spacing: 8
        TreeView {
            id: view
            anchors.top: parent.top
            width: parent.width/4
            anchors.bottom: parent.bottom
            model: fileSystemModel
            TableViewColumn {
                title: "Name"
                role: "fileName"
                resizable: true
            }
            onActivated: {
                console.debug(index)
                var data=fileSystemModel.data(index);

                console.debug(fileSystemModel.columnCount())
                console.debug(data);
                var path=filePicturesPath+"/"+data;
                sourceImage.source="file://"+path;
                ocr.ocr(path);
            }
        }

        Flickable {
            id: imageContainer
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentHeight: sourceImage.height
            contentWidth: sourceImage.width
            Layout.preferredWidth: 400
            Image {
                id: sourceImage
                asynchronous: true
                fillMode: Image.PreserveAspectFit
                onStatusChanged: {
                    console.debug(status);
                }
            }
        }

        Flickable {
            id: textContainer
            Layout.preferredWidth: 400
            clip: true
            contentHeight: textResult.height
            contentWidth: textResult.width
            Layout.fillHeight: true
            Layout.fillWidth: true
            TextEdit {
                id: textResult
                text: "Select image file to OCR first"
                textFormat: TextEdit.PlainText
            }
        }
    }

}


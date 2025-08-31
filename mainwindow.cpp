#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "handleText.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->statusbar->showMessage("© 2025 Jake Bohman");

    // Handle input
    ui->inputStack->setCurrentWidget(ui->pageText);
    connect(ui->actionFromText, &QAction::triggered, this, [=](){
        ui->inputStack->setCurrentWidget(ui->pageText);
    });
    connect(ui->actionFromFile, &QAction::triggered, this, [=](){
        ui->inputStack->setCurrentWidget(ui->pageFile);
    });
    connect(ui->fileButton, &QPushButton::clicked, this, [=](){
        QString fileName = QFileDialog::getOpenFileName(this, "Select File", "", "Text Files (*.txt);;All Files (*)");
        if (!fileName.isEmpty()) {
            ui->fileLabel->setText(fileName);
        }
    });

    // Copy/paste
    connect(ui->pasteButton, &QPushButton::clicked, this, [=]() {
        ui->inputText->paste();
    });
    connect(ui->copyButton, &QPushButton::clicked, this, [=]() {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(ui->outputText->toPlainText());
    });

    // "Generate output" button
    connect(ui->processButton, &QPushButton::clicked, this, [=]() {
        QString text;

        // Determine input source
        if (ui->inputStack->currentWidget() == ui->pageText) {
            text = ui->inputText->toPlainText();
        } else if (ui->inputStack->currentWidget() == ui->pageFile) {
            QString fileName = ui->fileLabel->text();
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                text = in.readAll();
                file.close();
            } else {
                ui->statusbar->showMessage("Failed to open file: " + fileName);
                return;
            }
        }

        // Call scanText from analyzeLine.cpp
        QString type = ui->outputType->currentText();
        QString result = scanText(text, type);
        ui->outputText->setPlainText(result);
    });
}

MainWindow::~MainWindow(){
    delete ui;
}

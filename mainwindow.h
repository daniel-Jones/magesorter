#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QMovie>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		QString directory;
		QString path;
		QImage  *oimage;
		QPixmap image;
		QGraphicsScene *scene;
		QStringList files;
		QStringList filters;
		int index;
		void setup();
		void update();
		int show_question_box(QString message, QString omessage);

		private slots:
			void on_directory_button_clicked();

		void on_save_button_clicked();

        void on_back_button_clicked();

        void on_forward_button_clicked();

        void on_delete_button_clicked();

private:
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

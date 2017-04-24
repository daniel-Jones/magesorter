#include "mainwindow.h" 
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	index = 0;
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_directory_button_clicked()
{
	directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
			"/",
			QFileDialog::ShowDirsOnly
			| QFileDialog::DontResolveSymlinks);
	if (directory != "")
		ui->directory_input->setText(directory);
	setup();
}

void MainWindow::on_save_button_clicked()
{
}

void MainWindow::on_back_button_clicked()
{
	if (index != 0)
	{
		index--;
		update();
	}
}

void MainWindow::on_forward_button_clicked()
{
	if (index < files.size() - 1)
	{
		index++;
		update();
	}
}

void MainWindow::setup()
{
	index = 0;
	directory = ui->directory_input->text();
	QDir f(directory);
	filters << "*.png" << "*.jpg" << "*.gif";
	f.setNameFilters(filters);
	files = f.entryList();
	qDebug() << files;
	if (files.size() > 0)
		update();
}

void MainWindow::update()
{
	QString txt = QString::number(files.size()) + " files to sort";
	ui->image_count_label->setText(txt);
	scene = new QGraphicsScene(this);
	oimage = new QImage();
	ui->image_view->setScene(scene);
	oimage->load(directory + "/" + files.at(index));
	if (files.at(index).endsWith(".gif"))
	{
		QLabel *gif_anim = new QLabel();
		QMovie *movie = new QMovie(directory + "/" + files.at(index));
		gif_anim->setMovie(movie);
		movie->start();
		QGraphicsProxyWidget *proxy = scene->addWidget(gif_anim);
		ui->current_file_label->setText(files.at(index));
	}
	else if (oimage)
	{
		image = QPixmap::fromImage(*oimage);
		scene->addPixmap(image);
		scene->setSceneRect(image.rect());
		ui->current_file_label->setText(files.at(index));
	}
}

int MainWindow::show_question_box(QString message, QString omessage)
{
	QMessageBox qbox;
	qbox.setText(message);
	qbox.setInformativeText(omessage);
	qbox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	qbox.setDefaultButton(QMessageBox::Cancel);
	return qbox.exec();
}

void MainWindow::on_delete_button_clicked()
{
	if (files.size() > 0)
	{
		QString msg = "Are you sure you want to delete " + directory + "/" + files.at(index) + "?";
		int ret = show_question_box(msg, "This process cannot be reverted.");
		switch (ret) 
		{
			case QMessageBox::Ok:
				{
					QFile::remove(directory + "/" + files.at(index));
					setup();
					break;
				}
			case QMessageBox::Cancel:
				qDebug() << "cancelled";
				break;
			default:
				qDebug() << "unknown";
				break;
		}
	}
}

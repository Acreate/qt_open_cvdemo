#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PLUGINS_SUBFOLDER                   "/cvplugins/"
#define LANGUAGES_SUBFOLDER                 "/languages/"
#define THEMES_SUBFOLDER                    "/themes/"
#define FILE_ON_DISK_DYNAMIC_PROPERTY       "absolute_file_path"

MainWindow::MainWindow( QWidget *parent ) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	loadSettings();// First thing's first, load settings

	populatePluginsMenu();
	populateLanguagesMenu();
	populateThemesMenu();

	ui->graphicsView->setScene(&scene);
	scene.addItem(&originalPixmap);
	scene.addItem(&processedPixmap);

	ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

MainWindow::~MainWindow( ) {
	delete currentPlugin;
	delete ui;
}

void MainWindow::loadSettings( ) {
	QSettings settings("Packt", "Computer_Vision", this);
	currentThemeFile = settings.value("currentThemeFile", "").toString();
	currentLanguageFile = settings.value("currentLanguageFile", "").toString();
	currentPluginFile = settings.value("currentPluginFile", "").toString();
}

void MainWindow::saveSettings( ) {
	QSettings settings("Packt", "Computer_Vision", this);
	settings.setValue("currentThemeFile", currentThemeFile);
	settings.setValue("currentLanguageFile", currentLanguageFile);
	settings.setValue("currentPluginFile", currentPluginFile);
}

void MainWindow::changeEvent( QEvent *event ) {
	if( event->type() == QEvent::LanguageChange ) {
		ui->retranslateUi(this);
	} else {
		QMainWindow::changeEvent(event);
	}
}

void MainWindow::closeEvent( QCloseEvent *event ) {
	int result = QMessageBox::warning(this, tr("Exit"), tr("Are you sure you want to exit?"), QMessageBox::Yes, QMessageBox::No);
	if( result == QMessageBox::Yes ) {
		saveSettings();
		event->accept();
	} else {
		event->ignore();
	}
}

void MainWindow::populatePluginsMenu( ) {
	// Load all plugins and populate the menus
	QDir pluginsDir(qApp->applicationDirPath() + PLUGINS_SUBFOLDER);
	QFileInfoList pluginFiles = pluginsDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
	foreach(QFileInfo pluginFile, pluginFiles) {
		QString absoluteFilePath = pluginFile.absoluteFilePath();
		if( QLibrary::isLibrary(absoluteFilePath) ) {
			QPluginLoader pluginLoader(absoluteFilePath, this);
			if( !pluginLoader.load() ) {
				QMessageBox::warning(this, tr("Warning"),
					QString(tr("%1 无法加载")).arg(pluginFile.fileName()));
			} else {
				QObject *instance = pluginLoader.instance();
				openCVInterface::OpenCVInterface002 *plugin = dynamic_cast<openCVInterface::OpenCVInterface002 *>(instance);
				if( plugin ) {
					QAction *pluginAction = ui->menu_Plugins->addAction(plugin->title());
					pluginAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, absoluteFilePath);
					connect(pluginAction, SIGNAL(triggered(bool)), this, SLOT(onPluginActionTriggered(bool)));
					if( currentPluginFile == absoluteFilePath ) {
						pluginAction->trigger();
					}
				} else {
					QMessageBox::warning(this, tr("Warning"),
						QString(tr("%1 虽然是个 dll，但是并不是一个插件")).arg(pluginFile.fileName()));
				}
			}
		}
	}

	if( ui->menu_Plugins->actions().count() <= 0 ) {
		QMessageBox::critical(this, tr("No Plugins"), QString(tr("%1 目录找不到插件")).arg(PLUGINS_SUBFOLDER));
		qApp->exit(-1);
		this->setEnabled(false);
	}
}

void MainWindow::populateLanguagesMenu( ) {
	QMenu *languagesMenu = new QMenu(this);
	// Add default (english) language
	QAction *defaultLanguageAction = languagesMenu->addAction("English - US");
	defaultLanguageAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, "");
	connect(defaultLanguageAction, SIGNAL(triggered(bool)), this, SLOT(onLanguageActionTriggered(bool)));

	// Load all languages and populate the menus
	QDir languagesDir(qApp->applicationDirPath() + LANGUAGES_SUBFOLDER);
	QFileInfoList languageFiles = languagesDir.entryInfoList(QStringList() << "*.qm", QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
	foreach(QFileInfo languageFile, languageFiles) {
		QAction *languageAction = languagesMenu->addAction(languageFile.baseName());
		languageAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, languageFile.absoluteFilePath());
		connect(languageAction, SIGNAL(triggered(bool)), this, SLOT(onLanguageActionTriggered(bool)));

		if( currentLanguageFile == languageFile.absoluteFilePath() ) {
			languageAction->trigger();
		}
	}
	ui->actionLanguage->setMenu(languagesMenu);
}

void MainWindow::populateThemesMenu( ) {
	QMenu *themesMenu = new QMenu(this);
	// Add default (native) theme
	QAction *defaultThemeAction = themesMenu->addAction("Default");
	defaultThemeAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, "");
	connect(defaultThemeAction, SIGNAL(triggered(bool)), this, SLOT(onThemeActionTriggered(bool)));

	// Load all themes and populate the menus
	QDir themesDir(qApp->applicationDirPath() + THEMES_SUBFOLDER);
	QFileInfoList themeFiles = themesDir.entryInfoList(QStringList() << "*.thm", QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
	foreach(QFileInfo themeFile, themeFiles) {
		QAction *themeAction = themesMenu->addAction(themeFile.baseName());
		themeAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, themeFile.absoluteFilePath());
		connect(themeAction, SIGNAL(triggered(bool)), this, SLOT(onThemeActionTriggered(bool)));

		if( currentThemeFile == themeFile.absoluteFilePath() ) {
			themeAction->trigger();
		}
	}
	ui->actionTheme->setMenu(themesMenu);
}

void MainWindow::on_actionAboutQt_triggered( ) {
	qApp->aboutQt();
}

void MainWindow::on_actionExit_triggered( ) {
	close();
}

void MainWindow::onPluginActionTriggered( bool ) {
	if( !currentPlugin.isNull() ) {
		delete currentPlugin;
		delete currentPluginGui;
	}

	currentPluginFile = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
	currentPlugin = new QPluginLoader(currentPluginFile, this);
	currentPluginGui = new QWidget(this);
	ui->pluginLayout->addWidget(currentPluginGui);
	openCVInterface::OpenCVInterface002 *currentPluginInstance = dynamic_cast<openCVInterface::OpenCVInterface002 *>(currentPlugin->instance());

	if( currentPluginInstance ) {
		currentPluginInstance->setupUi(currentPluginGui);
		connect(currentPlugin->instance(), SIGNAL(updateNeeded()), this, SLOT(onCurrentPluginUpdateNeeded()));
		connect(currentPlugin->instance(), SIGNAL(infoMessage(QString)), this, SLOT(onCurrentPluginInfoMessage(QString)));
		connect(currentPlugin->instance(), SIGNAL(errorMessage(QString)), this, SLOT(onCurrentPluginErrorMessage(QString)));

	}
}

void MainWindow::onLanguageActionTriggered( bool ) {
	currentLanguageFile = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
	qApp->removeTranslator(&translator);
	if( !currentLanguageFile.isEmpty() ) {
		translator.load(currentLanguageFile);
		qApp->installTranslator(&translator);
		ui->retranslateUi(this);
	}
}

void MainWindow::onThemeActionTriggered( bool ) {
	currentThemeFile = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
	QFile themeFile(currentThemeFile);
	if( currentThemeFile.isEmpty() ) {
		qApp->setStyleSheet("");
	} else {
		themeFile.open(QFile::ReadOnly | QFile::Text);
		QString styleSheet = themeFile.readAll();
		qApp->setStyleSheet(styleSheet);
		themeFile.close();
	}
}

void MainWindow::on_actionOpenImage_triggered( ) {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Input Image"),
		QDir::currentPath(),
		tr("Images") + " (*.jpg *.png *.bmp)");

	using namespace cv;
	originalMat = imread(fileName.toStdString());
	if( !originalMat.empty() ) {
		onCurrentPluginUpdateNeeded();
	} else if( !fileName.trimmed().isEmpty() ) {
		QMessageBox::critical(this,
			tr("Error"),
			tr("Make sure the image file exists "
				"and it is accessible!"));
	}
}

void MainWindow::on_viewOriginalCheck_toggled( bool checked ) {
	originalPixmap.setVisible(checked);
	processedPixmap.setVisible(!checked);
}

void MainWindow::onCurrentPluginUpdateNeeded( ) {
	if( !originalMat.empty() ) {
		if( !currentPlugin.isNull() ) {
			openCVInterface::OpenCVInterface002 *currentPluginInstance = dynamic_cast<openCVInterface::OpenCVInterface002 *>(currentPlugin->instance());
			if( currentPluginInstance ) {
				cv::TickMeter meter;
				meter.start();
				currentPluginInstance->processImage(originalMat, processedMat);
				meter.stop();
				qDebug() << "The process took " << meter.getTimeMilli() << "milliseconds";
			}
		} else {
			processedMat = originalMat.clone();
		}

		originalImage = QImage(originalMat.data, originalMat.cols, originalMat.rows, originalMat.step, QImage::Format_RGB888);
		originalPixmap.setPixmap(QPixmap::fromImage(originalImage.rgbSwapped()));

		processedImage = QImage(processedMat.data, processedMat.cols, processedMat.rows, processedMat.step, QImage::Format_RGB888);
		processedPixmap.setPixmap(QPixmap::fromImage(processedImage.rgbSwapped()));
	}
}

void MainWindow::on_actionSaveImage_triggered( ) {
	if( !ui->viewOriginalCheck->isChecked() && !processedMat.empty() ) {
		QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
		if( !fileName.isEmpty() ) {
			cv::imwrite(fileName.toStdString(), processedMat);
		}
	} else if( ui->viewOriginalCheck->isChecked() && !originalMat.empty() ) {
		QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
		if( !fileName.isEmpty() ) {
			cv::imwrite(fileName.toStdString(), originalMat);
		}
	} else {
		QMessageBox::warning(this, tr("Warning"), tr("There is nothing to be saved!"));
	}
}

void MainWindow::onCurrentPluginErrorMessage( QString msg ) {
	qDebug() << "Plugin Error Message : " << msg;
}

void MainWindow::onCurrentPluginInfoMessage( QString msg ) {
	qDebug() << "Plugin Info Message : " << msg;
}

void MainWindow::on_action_Camera_triggered( ) {}
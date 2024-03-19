#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

#include <qnite.h>

int main(int argc, char *argv[]) {
  Q_INIT_RESOURCE(qnite);

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.addImportPath(QStringLiteral("qrc:/qml"));
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}

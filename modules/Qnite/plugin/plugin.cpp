#include "plugin.h"

#include "qniteaxis.h"
#include "qniteaxes.h"
#include "qniteartist.h"
#include "qnitecurve.h"
#include "qnitemapper.h"
#include "qniteticker.h"
#include "qnitelinearticker.h"

#include <QtQml>

void QnitePlugin::registerTypes(const char *uri)
{
  // @uri qnite
  qmlRegisterType<QniteCurve>(uri, 1, 0, "Curve");
  qmlRegisterType<QniteMapper>(uri, 1, 0, "Mapper");
  qmlRegisterType<QniteArtist>(uri, 1, 0, "Artist");
  qmlRegisterType<QniteAxes>(uri, 1, 0, "BasicAxes");
  qmlRegisterType<QniteAxis>(uri, 1, 0, "BasicAxis");
  qmlRegisterType<QniteAxisTick>(uri, 1, 0, "AxisTick");
  qmlRegisterUncreatableType<QniteTicker>(uri, 1, 0, "Ticker",
    "Cannot create objects of base type Ticker");
  qmlRegisterType<QniteLinearTicker>(uri, 1, 0, "LinearTicker");
}


#include "qnitelinearticker.h"

#include <algorithm>
#include <QDebug>

// defines
#define DEFAULT_NUM_STEPS 10
#define DEFAULT_LOOSENESS true
#define UPSCALE_FACTOR 10.

namespace {

  double nice(double x, bool round)
  {
    int exp;
    double f;
    double nicef;

    exp = floor(log10(x));
    f = x / pow(10., exp);

    if (round) {
      if (f<1.5) nicef=1.;
      else if (f<3.) nicef=2.;
      else if (f<7.) nicef=5.;
      else nicef=10.;
    }
    else {
      if (f<=1.) nicef=1.;
      else if (f<=2.) nicef=2.;
      else if (f<=5.) nicef=5.;
      else nicef=10.;
    }

    return nicef*pow(10., exp);
  }

  void fill(QList<qreal>& ticks, qreal min, qreal max, int steps)
  {
    double range = nice(max-min, false);
    double d = nice(range/(steps-1), true);
    double graph_min = floor(min/d) * d;  // loose version of the algo
    double graph_max = ceil(max/d) * d;  // loose version of the algo
    // nFrac is the number of decimal numbers it'd be nice to show
    double nFrac = std::max(-floor(log10(d)), 0.);
    // we use it to better approximate values
    double precision = pow(10, nFrac);

    for (double x=graph_min; x<=graph_max + .5*d; x+=d) {
      // round to the "precision" decimal place
      double val = round(x*precision);
      ticks.append(val/precision);
      //ticks.append(x);
    }
  }


}


QniteLinearTicker::QniteLinearTicker(QObject *parent)
  : QniteTicker(parent),
    m_loose{DEFAULT_LOOSENESS}
{
  setNumSteps(DEFAULT_NUM_STEPS);
}

void QniteLinearTicker::buildTicks()
{
  qreal u = upper();
  qreal l = lower();
  qreal delta = u-l;
  bool upscale = false;

  if (delta <= 0) {
    qWarning() << QString("Illegal values for ticker bounds: %1,%2")
                          .arg(lower()).arg(upper());
    return;
  }
  else if (delta < 10) {
    upscale = true;
    u *= UPSCALE_FACTOR;
    l *= UPSCALE_FACTOR;
  }

  // build major ticks
  QList<qreal> majors;
  fill(majors, l, u, numSteps());

  // build min ticks
  QList<qreal> mins;
  for (int i=0; i<majors.size()-1; i++) {
    fill(mins, majors[i], majors[i+1], ceil(numSteps()/2.));
  }

  // remove duplicates
  mins = mins.toSet().subtract(majors.toSet()).toList();
  std::sort(mins.begin(), mins.end(), std::less<qreal>());

  // perform downscale if needed
  if (upscale) {
    auto downScale = [](qreal &n){ n /= UPSCALE_FACTOR; };
    std::for_each(mins.begin(), mins.end(), downScale);
    std::for_each(majors.begin(), majors.end(), downScale);
  }

  // set tick series
  setMinorTicks(mins);
  setMajorTicks(majors);
}

void QniteLinearTicker::setLooseNiceness(bool is_loose)
{
  m_loose = is_loose;
}

bool QniteLinearTicker::looseNiceness() const
{
  return m_loose;
}

void QniteLinearTicker::reset()
{
  QniteTicker::reset();
  m_loose = DEFAULT_LOOSENESS;
  setNumSteps(DEFAULT_NUM_STEPS);
}

void QniteLinearTicker::setNumSteps(int steps)
{
  if (steps < 2) {
    qWarning() << "Number of steps must be at least 2";
    return;
  }

  QniteTicker::setNumSteps(steps);
}

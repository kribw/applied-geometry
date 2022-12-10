#ifndef SCENARIO_H
#define SCENARIO_H

#include "application/gmlibwrapper.h"

// qt
#include <QObject>

class Scenario : public GMlibWrapper {
  Q_OBJECT
public:
  using GMlibWrapper::GMlibWrapper;

  void initializeScenario() override;
  void cleanupScenario() override;
  void bSpline();
  void bSplineLeastSquares();
  void closedSubDiv();
  void astroidCurve();
  void epitrochoidCurve();
  void nephroidCurve();
  void blendingSpline();
  void blendingSplineSurface();

public slots:
  void callDefferedGL();
};

#endif // SCENARIO_H

#include "scenario.h"
#include "application/femobject.h"
#include "testtorus.h"

// hidmanager
#include "hidmanager/defaulthidmanager.h"

// gmlib
#include <scene/light/gmpointlight.h>
#include <scene/sceneobjects/gmpathtrack.h>
#include <scene/sceneobjects/gmpathtrackarrows.h>
#include <parametrics/curves/gmpcircle.h>

// qt
#include <QQuickItem>

// applied_geometry
#include "appliedgeometry/bspline.h"
#include "appliedgeometry/pclosedsubdivcurve.h"
#include "appliedgeometry/modelcurves/pastroidcurve.h"
#include "appliedgeometry/modelcurves/pepitrochoidcurve.h"
#include "appliedgeometry/modelcurves/pnephroidcurve.h"

// stl
#include <cmath>

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
{
    out << v.size() << std::endl;
    for (uint i = 0; i < v.size(); i++) out << " " << v[i];
    out << std::endl;
    return out;
}

// FEMObject *_femObject;

void Scenario::initializeScenario()
{

    // Insert a light
    GMlib::Point<GLfloat, 3> init_light_pos(2.0, 4.0, 10);
    GMlib::PointLight*       light
      = new GMlib::PointLight(GMlib::GMcolor::white(), GMlib::GMcolor::white(),
                              GMlib::GMcolor::white(), init_light_pos);
    light->setAttenuation(0.8f, 0.002f, 0.0008f);
    this->scene()->insertLight(light, false);

    // Insert Sun
    this->scene()->insertSun();

    // Default camera parameters
    int                     init_viewport_size = 600;
    GMlib::Point<float, 3>  init_cam_pos(0.0f, 0.0f, 0.0f);
    GMlib::Vector<float, 3> init_cam_dir(0.0f, 1.0f, 0.0f);
    GMlib::Vector<float, 3> init_cam_up(1.0f, 0.0f, 0.0f);

    // Projection cam
    auto proj_rcpair = createRCPair("Projection");
    proj_rcpair.camera->set(init_cam_pos, init_cam_dir, init_cam_up);
    proj_rcpair.camera->setCuttingPlanes(1.0f, 8000.0f);
    proj_rcpair.camera->rotateGlobal(GMlib::Angle(-45),
                                     GMlib::Vector<float, 3>(1.0f, 0.0f, 0.0f));
    proj_rcpair.camera->translateGlobal(
      GMlib::Vector<float, 3>(0.0f, -20.0f, 20.0f));
    scene()->insertCamera(proj_rcpair.camera.get());
    proj_rcpair.renderer->reshape(
      GMlib::Vector<int, 2>(init_viewport_size, init_viewport_size));

    /***************************************************************************
     *                                                                         *
     * Standar example, including path track and path track arrows             *
     *                                                                         *
     ***************************************************************************/

    GMlib::Material mm(GMlib::GMmaterial::polishedBronze());
    mm.set(45.0);



    GMlib::DVector<GMlib::Vector<float, 3>> points;
    GMlib::Vector<float, 3>                 p;
    const float                             scale = 1.0;

    p = (0.0, 0.0, 0.0);
    points.push_back(p);

    p = {0.0, 3.0, 0.0};
    points.push_back(p);

    p = {1.0, 2.0, 0.0};
    points.push_back(p);

    p = {2.0, 3.0, 0.0};
    points.push_back(p);

    p = {2.0, 0.0, 0.0};
    points.push_back(p);

    p = {1.0, 1.0, 0.0};
    points.push_back(p);


    //// Create b-spline
    // auto bspline = new kwi::BSpline<float>(points);
    // bspline->toggleDefaultVisualizer();
    // bspline->setMaterial(GMlib::GMmaterial::polishedGreen());
    // bspline->sample(50, 0);
    // this->scene()->insert(bspline);

    // Use circle to approx points
    // auto circle = new GMlib::PCircle<float>(2.0);
    // circle->toggleDefaultVisualizer();
    // circle->sample(50, 0);
    // this->scene()->insert(circle);

    // auto const m     = 30;
    // auto       p_2   = GMlib::DVector<GMlib::Vector<float, 3>>(m);
    // auto       delta = circle->getParDelta() / (m - 1);

    // for (int i = 0; i < m; ++i) {
    //     p_2[i] = circle->getPosition(circle->getParStart() + i * delta);
    // }

    // auto bspline2 = new kwi::BSpline<float>(p_2, 20);
    // bspline2->toggleDefaultVisualizer();
    // bspline2->setMaterial(GMlib::GMmaterial::polishedGreen());
    // bspline2->sample(50, 0);
    // this->scene()->insert(bspline2);


    // DVector<Vector<float, 3>> p_3;
    // auto closed_curve = new kwi::PClosedSubDivCurve<float>(points, 2);
    // closed_curve->toggleDefaultVisualizer();
    // closed_curve->sample(4, 0);
    // this->scene()->insert(closed_curve);


    // auto astroid_curve = new kwi::PAstroidCurve<float>(4.0);
    // astroid_curve->toggleDefaultVisualizer();
    // astroid_curve->sample(30, 0);
    // this->scene()->insert(astroid_curve);

    //auto epitrochoid_curve = new kwi::PEpitrochoidCurve<float>(10.0, 0.5, 6.0);
    //epitrochoid_curve->toggleDefaultVisualizer();
    //epitrochoid_curve->sample(600, 0);
    //this->scene()->insert(epitrochoid_curve);

    auto nephroid = new kwi::PNephroidCurve<float>(0.5);
    nephroid->toggleDefaultVisualizer();
    nephroid->sample(600, 0);
    this->scene()->insert(nephroid);
}

void Scenario::cleanupScenario() {}

void Scenario::callDefferedGL()
{
    // For some reason this does not replot objects properly
    GMlib::Array<const GMlib::SceneObject*> e_obj;
    this->scene()->getEditedObjects(e_obj);
    for (int i = 0; i < e_obj.getSize(); i++)
        //    if (e_obj(i)->isVisible())
        e_obj[i]->replot();

    //  _femObject->replot();
}

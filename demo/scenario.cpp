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
#include "applied_geometry/bspline.h"

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



    //    GMlib::DVector<GMlib::Vector<float, 3>> points;
    //    GMlib::Vector<float, 3>                 p;
    //    const float                             scale = 1.0;

    //    p = (0.0, 0.0, 0.0);
    //    points.push_back(p);

    //    p = {1.0 * scale, 1.0 * scale, 1.0};
    //    points.push_back(p);

    //    p = {2.0 * scale, 0.0, 2.0};
    //    points.push_back(p);

    //    p = {3.0 * scale, 1.0 * scale, 3.0};
    //    points.push_back(p);

    //    p = {4.0 * scale, 0.0, 0.0};
    //    points.push_back(p);

    //    p = {5.0 * scale, 3.0 * scale, 0.0};
    //    points.push_back(p);

    //    std::cout << points << std::endl;

    //    auto bspline = new kwi::BSpline<float>(points);
    //    bspline->toggleDefaultVisualizer();
    //    bspline->setMaterial(GMlib::GMmaterial::polishedGreen());
    //    bspline->sample(50, 0);
    //    this->scene()->insert(bspline);

    //     Use circle to approx points
    auto const m      = 30;
    auto       circle = new GMlib::PCircle<float>(2.0);
    auto       p      = GMlib::DVector<GMlib::Vector<float, 3>>(m);
    auto       delta  = circle->getParDelta() / (m - 1);

    for (int i = 0; i < m; ++i) {
        p[i] = circle->getPosition(circle->getParStart() + i * delta);
    }
    auto bspline = new kwi::BSpline<float>(p, 6);
    bspline->toggleDefaultVisualizer();
    bspline->setMaterial(GMlib::GMmaterial::polishedGreen());
    bspline->sample(50, 0);
    this->scene()->insert(bspline);
    //    std::cout << "delta: " << delta << std::endl;
    //    std::cout << "start: " << circle.getParStart() << std::endl;
    //    std::cout << "end: " << circle.getParEnd() << std::endl;
    //    std::cout << "p: " << p << std::endl;
    //for (int i = circle.getParStart(); i < circle.getParEnd(); i += delta) {
        //        vec[i] = circle.get
    //}
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

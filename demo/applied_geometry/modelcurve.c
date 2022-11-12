namespace kwi
{
    // *************************
    // Public functions
    // *************************
    //using namespace GMlib;

    template <typename T>
    ModelCurve<T>::ModelCurve()
    {
    }

    template <typename T>
    ModelCurve<T>::~ModelCurve()
    {
    }

    template <typename T>
    inline bool ModelCurve<T>::isClosed() const
    {
        return false;
    }

    template <typename T>
    inline void ModelCurve<T>::sample(int depth, int d)
    {
        // m = no. samples
        // d = derivatives in each sample = 0
        _visu.resize(1);
        _checkSampleVal(depth, d);   // depth = m
        //this->_visu
        qDebug() << std::pow(2, 5);
        //        laneRiesenfeldClosed(std::vector<DVector<Vector<T, 3>>>&)
        // preSample <-> ClosedSubDivCurveClosed()?
        // this.visu[0].sample_val, this.visu[0].surrounding_sphere
        //        setEditDone
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void ModelCurve<T>::eval(T t, int d, bool /*l*/) const
    {
        // Set p[0] = model curve formula here?
    }

    template <typename T>
    inline T ModelCurve<T>::getStartP() const
    {
        return 0;
    }

    template <typename T>
    inline T ModelCurve<T>::getEndP() const
    {
        return 1;
    }

    // *************************
    // ** Private functions   **
    // *************************



}   // END namespace kwi

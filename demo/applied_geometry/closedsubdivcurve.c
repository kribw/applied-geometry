namespace kwi
{
    // *************************
    // Public functions
    // *************************
    using namespace GMlib;

    template <typename T>
    ClosedSubDivCurve<T>::ClosedSubDivCurve(const DVector<Vector<T, 3>>& p,
                                            int                          d)
    {
        _d      = d;
        _points = p;
    }

    template <typename T>
    ClosedSubDivCurve<T>::~ClosedSubDivCurve()
    {
    }

    template <typename T>
    inline bool ClosedSubDivCurve<T>::isClosed() const
    {
        return true;
    }

    template <typename T>
    inline void ClosedSubDivCurve<T>::sample(int depth, int d)
    {
        // m = no. samples
        // d = derivatives in each sample = 0
        _visu.resize(1);
        _checkSampleVal(depth, d); // depth = m

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
    void ClosedSubDivCurve<T>::eval(T t, int d, bool /*l*/) const
    {
        // Not used, just needs to be declared
    }

    template <typename T>
    inline T ClosedSubDivCurve<T>::getStartP() const
    {
        return 0;
    }

    template <typename T>
    inline T ClosedSubDivCurve<T>::getEndP() const
    {
        return 1;
    }



    // Resample
    // p[i][0]
    // s.reset
    // computeSurroundingSphere(p, s)

    // *************************
    // ** Private functions   **
    // *************************

    template <typename T>
    inline DVector<Vector<float, 3>>
    ClosedSubDivCurve<T>::laneRiesenfeldClosed(DVector<Vector<float, 3>> p,
                                               int k, int d)
    {
        // p = initial points
        // k = level of refinement
        // d = degree
        int n = p.getDim();
        int m = 2 ^ k(n - d) + d;
        //        DVector<Vector<float, 3>>

        return null;
    }


    template <typename T>
    inline int ClosedSubDivCurve<T>::doublePart(DVector<Vector<float, 3>> p,
                                                int                       n)
    {
        return 0;
    }

    template <typename T>
    void ClosedSubDivCurve<T>::smoothPartClosed(DVector<Vector<float, 3>> p,
                                                int n, int d)
    {
    }



}   // END namespace kwi

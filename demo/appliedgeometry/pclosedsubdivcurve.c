namespace kwi
{
    // *************************
    // Public functions
    // *************************
    using namespace GMlib;

    template <typename T>
    PClosedSubDivCurve<T>::PClosedSubDivCurve(const DVector<Vector<T, 3>>& p,
                                            int                          d)
    {
        _d      = d;
        _points = p;
    }

    template <typename T>
    PClosedSubDivCurve<T>::~PClosedSubDivCurve()
    {
    }

    template <typename T>
    inline bool PClosedSubDivCurve<T>::isClosed() const
    {
        return true;
    }

    template <typename T>
    inline void PClosedSubDivCurve<T>::sample(int depth, int d)
    {
        // depth = number of times to double points
        // m = no. samples
        // d = derivatives in each sample = 0
        _visu.resize(1);
        _checkSampleVal(depth, d);   // depth = m

        laneRiesenfeldClosed(this->_visu[0].sample_val, depth, d);
        std::cout << "sample_val" << std::endl;
        std::cout << this->_visu[0].sample_val << std::endl;
        std::cout << "sample_val" << std::endl;
        
        this->setEditDone();
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void PClosedSubDivCurve<T>::eval(T t, int d, bool /*l*/) const
    {
        // Not used, just needs to be declared
    }

    template <typename T>
    inline T PClosedSubDivCurve<T>::getStartP() const
    {
        return 0;
    }

    template <typename T>
    inline T PClosedSubDivCurve<T>::getEndP() const
    {
        return 1;
    }


    // *************************
    // ** Private functions   **
    // *************************

    template <typename T>
    inline void PClosedSubDivCurve<T>::laneRiesenfeldClosed(
      std::vector<DVector<Vector<T, 3>>>& p, int k, int d) const
    {
        // p = initial points
        // k = level of refinement / no. times to double points
        // d = degree
        int n = _points.getDim();
        int m = pow(2, k) * n + 1;

        p.resize(m);

        for (int i = 0; i < p.size(); ++i) {
            p[i].setDim(d + 1);
        }

        for (int i = 0; i < n; ++i) {
            p[i][0] = _points[i];
        }
        p[n++] = p[0]; // Close the curve

        for (int i = 0; i < k; ++i) {
            n = doublePart(p, n);
            smoothPartClosed(p, n, _d);
        }

        Sphere<T, 3>& s = this->_visu[0].sur_sphere;
        s.reset();
        computeSurroundingSphere(p, s);

        if (d > 0)
            DD::compute1D(p, double(n - 1) / (p.size() - 1), isClosed(), d, 0);
    }


    template <typename T>
    inline int
    PClosedSubDivCurve<T>::doublePart(std::vector<DVector<Vector<T, 3>>>& p,
                                     int                                 n) const
    {
        for (int i = n - 1; i > 0; --i) {
            p[2 * i][0]    = p[i][0];
            p[(2 * i) - 1][0] = 0.5 * (p[i][0] + p[i - 1][0]);
        }

        return (2 * n) - 1;
    }

    template <typename T>
    void PClosedSubDivCurve<T>::smoothPartClosed(
      std::vector<DVector<Vector<T, 3>>>& p, int n, int d) const
    {
        for (int j = 1; j < d; ++j) {
            for (int i = 0; i < n - 1; ++i) {
                p[i][0] = 0.5 * (p[i][0] + p[i + 1][0]);
            }
            p[n - 1][0] = p[0][0];
        }
    }



}   // END namespace kwi

namespace kwi
{
    // *************************
    // Public functions
    // *************************
    using namespace GMlib;

    template <typename T>
    LaneRiesenfeld<T>::LaneRiesenfeld()
    {
    }

    template <typename T>
    LaneRiesenfeld<T>::LaneRiesenfeld(const DVector<Vector<T, 3>>& c)
    {
        _c = c;        // control points
        _d = 2;        // dimension should always be 2
        _k = _d + 1;   // order
        //        create_knot_vector(c.getDim());   // generate knot vector
    }

    template <typename T>
    LaneRiesenfeld<T>::~LaneRiesenfeld()
    {
    }

    template <typename T>
    inline bool LaneRiesenfeld<T>::isClosed() const
    {
        return true;
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void LaneRiesenfeld<T>::eval(T t, int d, bool /*l*/) const
    {
        // Set dim (derivatives + 1)
        this->_p.setDim(d + 1);
        //        this->_p[0] = x * _c[i - 2] + y * _c[i - 1] + z * _c[i];
    }

    template <typename T>
    inline T LaneRiesenfeld<T>::getStartP() const
    {
        return _t[_d];
    }

    template <typename T>
    inline T LaneRiesenfeld<T>::getEndP() const
    {
        return _t[_c.getDim()];
    }

    // *************************
    // ** Private functions   **
    // *************************

    template <typename T>
    inline T LaneRiesenfeld<T>::getDeltaP() const
    {
        return getEndP() - getStartP();
    }

    template <typename T>
    inline DVector<Vector<float, 3>>
    LaneRiesenfeld<T>::lane_riesenfeld_closed(DVector<Vector<float, 3>> p,
                                              int k, int d) const
    {
        // p = initial points
        // k = level of refinement
        // d = degree
        int n = p.getDim();
        int m = 2^k (n - d) + d;
        DVector<Vector<float, 3>>

        return null;
    }


    template <typename T>
    inline int LaneRiesenfeld<T>::double_part(DVector<Vector<float, 3>> p,
                                              int                       n) const
    {
        return 0;
    }

    template <typename T>
    void LaneRiesenfeld<T>::smooth_part_closed(DVector<Vector<float, 3>> p,
                                               int n, int d)
    {
        //
    }



}   // END namespace kwi

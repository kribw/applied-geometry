namespace kwi
{
    // *************************
    // Public functions
    // *************************
    // using namespace GMlib;

    template <typename T>
    PEpitrochoidCurve<T>::PEpitrochoidCurve(T a = T(1), T b = T(1),
                                            T c = T(1))
    {
        _a = a;
        _b = b;
        _c = c;
    }

    template <typename T>
    PEpitrochoidCurve<T>::~PEpitrochoidCurve()
    {
    }

    template <typename T>
    inline bool PEpitrochoidCurve<T>::isClosed() const
    {
        return true;
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void PEpitrochoidCurve<T>::eval(T t, int d, bool /*l*/) const
    {
        this->_p.setDim(d + 1);
        this->_p[0][0]
          = ((_a + _b) * std::cos(t)) - (_c * std::cos((_a / (_b + t)) * t));
        this->_p[0][1]
          = ((_a + _b) * std::sin(t)) - (_c * std::sin((_a / (_b + 1)) * t));
        this->_p[0][2] = T(0);
    }

    template <typename T>
    inline T PEpitrochoidCurve<T>::getStartP() const
    {
        return 0;
    }

    template <typename T>
    inline T PEpitrochoidCurve<T>::getEndP() const
    {
        return M_2PI;
    }

    // *************************
    // ** Private functions   **
    // *************************

}   // END namespace kwi

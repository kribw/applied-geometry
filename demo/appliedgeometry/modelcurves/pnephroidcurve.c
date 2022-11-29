namespace kwi
{
    // *************************
    // Public functions
    // *************************
    // using namespace GMlib;

    template <typename T>
    PNephroidCurve<T>::PNephroidCurve(T a = T(1))
    {
        _a = a;
    }

    template <typename T>
    PNephroidCurve<T>::~PNephroidCurve()
    {
    }

    template <typename T>
    inline bool PNephroidCurve<T>::isClosed() const
    {
        return true;
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void PNephroidCurve<T>::eval(T t, int d, bool /*l*/) const
    {
        this->_p.setDim(d + 1);
        this->_p[0][0] = _a * (3 * std::cos(t) - std::cos(3 * t));
        this->_p[0][1] = _a * (3 * std::sin(t) - std::sin(3 * t));
        this->_p[0][2] = T(0);
    }

    template <typename T>
    inline T PNephroidCurve<T>::getStartP() const
    {
        return 0;
    }

    template <typename T>
    inline T PNephroidCurve<T>::getEndP() const
    {
        return M_2PI;
    }

    // *************************
    // ** Private functions   **
    // *************************

}   // END namespace kwi

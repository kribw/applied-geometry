namespace kwi
{
    // *************************
    // Public functions
    // *************************
    //using namespace GMlib;

    template <typename T>
    ModelCurve<T>::ModelCurve(T a = T(1))
    {
        _a = a;
    }

    template <typename T>
    ModelCurve<T>::~ModelCurve()
    {
    }

    template <typename T>
    inline bool ModelCurve<T>::isClosed() const
    {
        return true;
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void ModelCurve<T>::eval(T t, int d, bool /*l*/) const
    {
        this->_p.setDim(d + 1);
        this->_p[0][0] = _a * pow(std::cos(t), 3);
        this->_p[0][1] = _a * pow(std::sin(t), 3);
        this->_p[0][2] = T(0);
    }

    template <typename T>
    inline T ModelCurve<T>::getStartP() const
    {
        return 0;
    }

    template <typename T>
    inline T ModelCurve<T>::getEndP() const
    {
        return M_2PI;
    }

    // *************************
    // ** Private functions   **
    // *************************

}   // END namespace kwi

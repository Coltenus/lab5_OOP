//
// Created by coltenus on 17.02.23.
//

#ifndef LAB5_SLIDERCOMMAND_H
#define LAB5_SLIDERCOMMAND_H

namespace l5 {

    /*
     * Class which connects slider class and its values.
     */
    template<typename T>
    class SliderCommand {
    private:
        T _min, _max, *_dest;

    public:
        SliderCommand(T* dest, T min, T max);
        ~SliderCommand() = default;
        void MakeAction(int value, int start, int end);
        T GetMin();
        T GetMax();
        T GetCurrent();
    };

    template<typename T>
    SliderCommand<T>::SliderCommand(T *dest, T min, T max)
    : _min(min), _max(max), _dest(dest) {}

    template<typename T>
    void SliderCommand<T>::MakeAction(int value, int start, int end) {
        float buf;
        if(end > start && value <= end && value >= start) {
            buf = value - start;
            buf /= end - start;
            buf *= _max - _min;
            buf += _min;
            *_dest = buf;
        }
    }

    template<typename T>
    T SliderCommand<T>::GetMin() {
        return _min;
    }

    template<typename T>
    T SliderCommand<T>::GetMax() {
        return _max;
    }

    template<typename T>
    T SliderCommand<T>::GetCurrent() {
        return *_dest;
    }

} // l5

#endif //LAB5_SLIDERCOMMAND_H

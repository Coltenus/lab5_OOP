//
// Created by colte on 16.02.2023.
//

#ifndef LAB5_VALUESETBC_H
#define LAB5_VALUESETBC_H

#include "ButtonCommand.h"

namespace l5 {

    template<typename T>
    class ValueSetBC : public ButtonCommand {
    private:
        T* _dest;
        T _value;

    public:
        ValueSetBC(T* dest, T value) : ButtonCommand(), _dest(dest), _value(value) {}
        ~ValueSetBC() override = default;
        void MakeAction() override;
    };

    template<typename T>
    void ValueSetBC<T>::MakeAction() {
        *_dest = _value;
    }

} // l5

#endif //LAB5_VALUESETBC_H

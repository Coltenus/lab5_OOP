//
// Created by colte on 16.02.2023.
//

#ifndef LAB5_BUTTONCOMMAND_H
#define LAB5_BUTTONCOMMAND_H

namespace l5 {

    class ButtonCommand {
    public:
        ButtonCommand() = default;
        virtual ~ButtonCommand() = default;
        virtual void MakeAction() = 0;
    };

} // l5

#endif //LAB5_BUTTONCOMMAND_H

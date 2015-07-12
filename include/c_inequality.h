#ifndef C_INEQUALITY_H
#define C_INEQUALITY_H

#include <stdlib.h>

enum class binary_relation { GEQ, LEQ };

class c_inequality {
    public:
        c_inequality(size_t dim, float val, binary_relation bin);
        virtual ~c_inequality();

        size_t get_dim();
        float get_val();
        binary_relation get_binary_relation();

    protected:
    private:
};

#endif // C_INEQUALITY_H

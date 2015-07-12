#ifndef C_INEQUALITY_H
#define C_INEQUALITY_H

#include <stdlib.h>

enum class binary_relation { GEQ, LEQ };

class c_inequality {
    public:
        c_inequality(size_t dim, float val, binary_relation bin);
        virtual ~c_inequality();
    protected:
    private:
};

#endif // C_INEQUALITY_H

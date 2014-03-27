#ifndef BLOCKI_H_INCLUDED
#define BLOCKI_H_INCLUDED
#include "BlockPiece.h"

class BlockI: public BlockPiece{
    public:
        BlockI();

        void Turn(int Block[20][10]);
};

#endif // BLOCKI_H_INCLUDED

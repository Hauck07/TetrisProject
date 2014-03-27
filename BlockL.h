#ifndef BLOCKL_H_INCLUDED
#define BLOCKL_H_INCLUDED
#include "BlockPiece.h"

class BlockL: public BlockPiece{
    public:
        BlockL();

        void Turn(int Block[20][10]);

};

#endif // BLOCKL_H_INCLUDED

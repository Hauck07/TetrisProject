#ifndef RETURNPARAMETER_H_INCLUDED
#define RETURNPARAMETER_H_INCLUDED

class ReturnParameter{
    public:
        bool Empty;

        virtual bool IsEmpty(){
            return Empty;
        }
};


#endif // RETURNPARAMETER_H_INCLUDED

#ifndef _EXER07_ITASK_HPP_
#define _EXER07_ITASK_HPP_



// interface ITask
class ITask {
public:
    virtual ~ITask() = default;
    virtual void run() = 0;
};



#endif // _EXER07_ITASK_HPP_

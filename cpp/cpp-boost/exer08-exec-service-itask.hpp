#ifndef _MY_EXEC_SERVICE_ITASK_HPP_
#define _MY_EXEC_SERVICE_ITASK_HPP_



// interface ITask
class ITask {
public:
    virtual ~ITask() { }
    virtual void run() = 0;
};



#endif // _MY_EXEC_SERVICE_ITASK_HPP_

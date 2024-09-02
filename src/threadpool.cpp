#include "../include/threadpool.hpp"

/*
@brief create the threadpool
@param threadNumber the number of the thread, its default value is std::thread::hardware_concurrency()
*/
ThreadPool::ThreadPool(int threadsNumber) {
    // initalize threads count
    m_threadsNumber = threadsNumber;
    _createPool(m_threadsNumber);
}

/*
@brief destroy and stop the threadpool
*/
ThreadPool::~ThreadPool()
{
    _disposePools(m_threadsNumber);
}

/*
@brief create the pool
@param numOfThreads Number of threads to be created, not necessarily to be the total number of threads
*/
void ThreadPool::_createPool(int numOfThreads) {

    //fill the pool
    for (int i = 0; i < numOfThreads; i++) {
        m_threads.emplace_back(
            //create thread number i
            std::thread(
                [this]()
                {
                    {
                        while (true) {
                            std::function<void()> currentTask;
                            //critical section
                            {
                                std::unique_lock<std::mutex> lk{ m_mutex };

                                m_cv.wait(lk, [this]() {
                                    //block waiting if a task exists, or stop stopping
                                    return  !m_tasks.empty() || m_stop;
                                    }
                                );
                                
                                if (m_stop && m_tasks.empty()) {
                                    return;
                                }

                                currentTask = std::move(m_tasks.front());
                                m_tasks.pop();
                            }

                            //execute in parallel, no need for sync
                            currentTask();
                        }
                    }

                }
            )

        );
    }
}

/*
@brief dispose pools, stops `numOfDisposedPools` threads starting from the end of the pool
@param numOfDisposedPools number of pools that will be stopped and removed from the pool
*/
void ThreadPool::_disposePools(int numOfDisposedPools) {
    if (numOfDisposedPools < 0) {
        numOfDisposedPools = m_threadsNumber;
    }
    _stopThreads(numOfDisposedPools);
    _freeMemory(numOfDisposedPools);
  
}


/*
@brief stop serving new thread and join the victim threads until they finish 
*/
void ThreadPool::_stopThreads(int count) {
    //stop receiving new requests (critical section)
    {
        std::unique_lock<std::mutex> lk{ m_mutex };
        m_stop = true;

    }
    m_cv.notify_all();

    //serve the threads to be removed
    for (int i = m_threads.size() - 1; i > (int)(m_threads.size() - 1 - count); i--) {
        m_threads[i].join();
    }
 
    
}

//purpose: to be used in re-initalize threads pool by using the exisitng threads to avoid the headach of initalization
//condition: all threads should be finished their execiton
//pre: threads vector is initalized
//post: the length of the threads vector will be max(0, oldLength - numOfRemovedThreads)
void ThreadPool::_freeMemory(int numOfRemovedThreads) {
    int count{ numOfRemovedThreads };
    while (!m_threads.empty() && count > 0) {
        m_threads.pop_back();
        count--;
    }
}



/*
@brief resize the threads number, in case of expansion a new threads will be added to the current working threads, else in case of shrinking working threads will be removed without affecting on the other
*/
void ThreadPool::expandPool(int newNumber) {
    if (newNumber <= m_threadsNumber) {//shrink threads or just resarting them (number of deleted pools = 0)
        _disposePools(m_threadsNumber - newNumber);
    }
    else { //expanding
        _createPool(newNumber - m_threadsNumber); //add new threads
    }
    m_threadsNumber = newNumber;
    m_stop = false;
}

/*
@brief add a new task to the next available thread
*/
void ThreadPool::addTask(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lk{ m_mutex };
        m_tasks.push(task);
    }
    m_cv.notify_one();
}

// setters and getters
int ThreadPool::getThreadsNumber() const
{
    return m_threadsNumber;
}



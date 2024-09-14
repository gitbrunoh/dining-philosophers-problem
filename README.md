# dining-philosophers-problem

<iframe width="560" height="315" src="https://www.youtube.com/embed/HbBYHRBJ47Q" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

# Key concepts

## Thread 

A program can have several processes and each **process** can have a certain number of **threads** running in it.

A **thread** is a basic unit of execution within a **process**.

**Threads** are like little workers inside a program. They help to do several tasks at the same time, as if they were several hands working together. This can make the program faster and more efficient.

Each **thread** has a unique **id** within a **process** and also has its own stack. There is also a Register Set which contains all the registers needed to run the thread, including the Program Counter, which is responsible for storing the address of the next instruction to be executed in the **thread**.

**Threads** do not execute anything other than the function passed as a parameter in pthread_create.

## Mutex 

**Mutex** (mutual exclusion) is a synchronization tool that ensures that only one thread or process can access a shared resource at a time, preventing data races and guaranteeing data consistency.

In this project, the forks needed for the philosopher to eat are mutexes. And they are used to ensure that a fork is not being used by another philosopher. When a philosopher tries to take a fork, it tries to acquire (lock) the mutex associated with that fork. If the mutex is already locked by another thread, the current thread will have to wait until the mutex is released. This is a fundamental feature of mutexes and is what guarantees mutual exclusion, i.e. that only one thread can access a critical resource (in this case, a fork) at a time.
In the context of my code, when a thread (representing a philosopher) tries to take a fork, it calls pthread_mutex_lock for the mutex associated with that fork. If the mutex is already blocked by another philosopher, the current thread will be blocked until the mutex is freed.

### Data races

Condition: Two or more threads simultaneously accessing a memory location AND one of them is a write AND there are no synchronization mechanisms.

### Deadlocks

The number of forks is equal to the number of philosophers and each philosopher needs 2 forks to eat. So, if all the philosophers try to pick up the forks at the same time, there could be a deadlock situation. A **deadlock** occurs when each philosopher holds one fork and waits for the other, resulting in a situation where no philosopher can continue. To contain this, a usleep() is inserted into the execution of threads with odd ids.

There is another way to contain this **deadlock**. Reversing the priority of picking up the forks to the last philosopher is also an effective technique for avoiding deadlocks in the philosopher problem. But I used the first option.
